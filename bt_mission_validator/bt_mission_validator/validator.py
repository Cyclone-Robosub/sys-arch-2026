"""
validator.py

Given a mission XML file and a path to an already-built mission_schema.xsd
(see schema_build.py for the only place that ever creates one), this:

  1. Parses the mission file.
  2. Runs a few structural checks that are simpler in Python than XSD
     (BTCPP_format presence, reserved names, nesting depth).
  3. Validates the file against the given schema with lxml.
  4. Reconstructs the node catalog from that same schema (schema_reader) and
     runs semantic/cross-reference checks XSD can't express (SubTree
     resolution, duplicate tree IDs, vector-length consistency, etc.).
  5. As an informational (non-blocking) extra, diffs the mission file's own
     <TreeNodesModel> -- which is Groot-facing metadata, not validated
     against here -- against the master schema, so you notice if a file's
     local model has drifted from the canonical one.

`validate_file` never writes anything and never calls schema_generator.
"""

from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path

from lxml import etree

from .node_catalog import RESERVED_MODEL_NAMES, MAX_NESTING_DEPTH
from .model_parser import parse_tree_nodes_model
from .schema_reader import read_node_catalog
from .semantic_checks import run_semantic_checks, Finding

DEFAULT_SCHEMA_PATH = Path(__file__).parent / "schemas" / "mission_schema.xsd"


@dataclass
class ValidationResult:
    file_path: str
    schema_path: str
    ok: bool
    errors: list[Finding] = field(default_factory=list)
    warnings: list[Finding] = field(default_factory=list)

    def summary_line(self) -> str:
        status = "PASS" if self.ok else "FAIL"
        return (f"[{status}] {self.file_path}  "
                f"({len(self.errors)} error(s), {len(self.warnings)} warning(s))")


def _pre_xsd_structural_checks(root: etree._Element) -> list[Finding]:
    """A handful of BT.CPP structural rules simpler to check in Python than
    to encode in XSD (mirrors BT::VerifyXML in xml_parsing.cpp)."""
    findings: list[Finding] = []

    if root.tag != "root":
        findings.append(Finding("error", getattr(root, "sourceline", None),
                                 f"Document root element must be <root>, found <{root.tag}>."))
        return findings

    if root.get("BTCPP_format") is None:
        findings.append(Finding(
            "warning", root.sourceline,
            "Root <root> is missing [BTCPP_format=\"4\"]. BT.CPP only warns "
            "(doesn't fail) on this, but every mission file should set it "
            "explicitly for forward compatibility."))

    def walk(el, depth):
        if depth > MAX_NESTING_DEPTH:
            findings.append(Finding(
                "error", el.sourceline,
                f"Maximum XML nesting depth ({MAX_NESTING_DEPTH}) exceeded."))
            return
        node_id = el.get("ID")
        if el.tag == "BehaviorTree" and node_id in RESERVED_MODEL_NAMES:
            findings.append(Finding(
                "error", el.sourceline,
                f"'{node_id}' is a reserved name and cannot be used as a "
                f"<BehaviorTree ID>."))
        for child in el:
            if isinstance(child.tag, str):
                walk(child, depth + 1)

    for bt in root.findall("BehaviorTree"):
        walk(bt, 0)

    return findings


def _diff_local_model_against_master(root: etree._Element,
                                      master_nodes: dict) -> list[Finding]:
    """Informational only: flags when a mission file's own (Groot-facing)
    <TreeNodesModel> disagrees with the master schema. Never affects `ok`."""
    findings: list[Finding] = []
    local = parse_tree_nodes_model(root)
    for w in local.warnings:
        findings.append(Finding("warning", None, f"(local TreeNodesModel) {w}"))
    for node_id, local_spec in local.nodes.items():
        master_spec = master_nodes.get(node_id)
        if master_spec is None:
            findings.append(Finding(
                "warning", None,
                f"This file's own <TreeNodesModel> declares '{node_id}', "
                f"which is not in the master schema. If this node is "
                f"actually used and legitimate, regenerate the master "
                f"schema to include it; otherwise this local entry may be "
                f"stale."))
            continue
        local_names = {p.name for p in local_spec.ports}
        master_names = {p.name for p in master_spec.ports}
        if local_names != master_names:
            findings.append(Finding(
                "warning", None,
                f"This file's own <TreeNodesModel> for '{node_id}' declares "
                f"ports {sorted(local_names)}, but the master schema has "
                f"{sorted(master_names)} -- local Groot metadata may be "
                f"stale."))
    return findings


def validate_file(mission_path: str | Path,
                   schema_path: str | Path = DEFAULT_SCHEMA_PATH) -> ValidationResult:
    mission_path = Path(mission_path)
    schema_path = Path(schema_path)
    result = ValidationResult(file_path=str(mission_path), schema_path=str(schema_path), ok=True)

    if not schema_path.exists():
        result.ok = False
        result.errors.append(Finding(
            "error", None,
            f"Schema file not found: {schema_path}. Generate it first with: "
            f"python -m bt_mission_validator.cli generate-schema <mission files...> "
            f"-o {schema_path}"))
        return result

    try:
        mission_tree = etree.parse(str(mission_path))
    except etree.XMLSyntaxError as e:
        result.ok = False
        result.errors.append(Finding("error", e.lineno, f"XML is not well-formed: {e.msg}"))
        return result

    root = mission_tree.getroot()

    struct_findings = _pre_xsd_structural_checks(root)
    result.errors += [f for f in struct_findings if f.severity == "error"]
    result.warnings += [f for f in struct_findings if f.severity == "warning"]
    if root.tag != "root":
        result.ok = False
        return result

    schema_tree = etree.parse(str(schema_path))
    try:
        xsd = etree.XMLSchema(schema_tree)
    except etree.XMLSchemaParseError as e:
        result.ok = False
        result.errors.append(Finding("error", None, f"Schema file is invalid: {e}"))
        return result

    if not xsd.validate(mission_tree):
        for err in xsd.error_log:
            result.errors.append(Finding("error", err.line, err.message))

    master_nodes = read_node_catalog(schema_tree.getroot())

    semantic_report = run_semantic_checks(root, master_nodes)
    result.errors += semantic_report.errors
    result.warnings += semantic_report.warnings

    result.warnings += _diff_local_model_against_master(root, master_nodes)

    result.ok = len(result.errors) == 0
    return result
