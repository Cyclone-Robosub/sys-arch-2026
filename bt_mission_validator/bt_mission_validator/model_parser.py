"""
model_parser.py

Reads the <TreeNodesModel> block embedded in a BehaviorTree.CPP mission XML
file and turns it into NodeSpec / PortSpec objects (see node_catalog.py).

Per the project's chosen design (confirmed with the controls team):
    Ground truth for "which nodes/ports are legal" = each mission file's
    OWN <TreeNodesModel> block. This mirrors how BehaviorTree.CPP itself
    generates a schema per-factory (see writeTreeXSD() in xml_parsing.cpp) --
    the schema is only ever as good as what's declared for that specific
    file, nothing external (e.g. the .action/ROS files) is cross-checked.
"""

from __future__ import annotations

import re
from dataclasses import dataclass
from lxml import etree

from .node_catalog import NodeSpec, NodeKind, PortSpec, PortType

_TAG_TO_KIND = {
    "Action": NodeKind.ACTION,
    "Condition": NodeKind.CONDITION,
    "Control": NodeKind.CONTROL,
    "Decorator": NodeKind.DECORATOR,
    "SubTree": NodeKind.SUBTREE,
}

# child-count rules for locally-declared node kinds (mirrors BT::VerifyXML)
_KIND_CHILD_RULES = {
    NodeKind.ACTION: dict(min_children=0, max_children=0),
    NodeKind.CONDITION: dict(min_children=0, max_children=0),
    NodeKind.DECORATOR: dict(min_children=1, max_children=1),
    NodeKind.CONTROL: dict(min_children=1, max_children=None),
    NodeKind.SUBTREE: dict(min_children=0, max_children=0),
}


def classify_port_type(raw_type: str) -> PortType:
    """Map a C++ type string (as written in TreeNodesModel/@type) to a
    coarse PortType category used to choose an XSD restriction.

    Mirrors xsdAttributeType() in BT.CPP's xml_parsing.cpp, extended with
    vector categories (BT.CPP's own generator leaves those unrestricted;
    this tool adds regex-based checks for them since they're heavily used
    in these mission files -- see schema_generator.py).
    """
    t = raw_type.strip()
    t_norm = t.lower()

    is_vector = bool(re.search(r"vector|array", t_norm))

    if is_vector:
        if "bool" in t_norm:
            return PortType.VECTOR_BOOL
        if "float" in t_norm or "double" in t_norm:
            return PortType.VECTOR_DOUBLE
        if re.search(r"\bint\b|int8|int16|int32|int64|uint", t_norm):
            return PortType.VECTOR_INT
        return PortType.UNKNOWN

    if t_norm in ("bool",):
        return PortType.BOOL
    if t_norm in ("float", "double"):
        return PortType.DOUBLE
    if re.fullmatch(r"(unsigned\s+)?(u?int(8|16|32|64)?_t|u?int)", t_norm):
        return PortType.INT
    if t_norm in ("string", "std::string"):
        return PortType.STRING
    if "nodestatus" in t_norm:
        return PortType.NODE_STATUS
    return PortType.UNKNOWN


@dataclass
class ModelParseResult:
    nodes: dict[str, NodeSpec]
    duplicate_ids: list[str]
    warnings: list[str]


@dataclass
class MergeConflict:
    node_id: str
    detail: str


@dataclass
class MergedModel:
    nodes: dict[str, NodeSpec]
    conflicts: list[MergeConflict]
    warnings: list[str]
    source_counts: dict[str, int]   # node_id -> number of files that declared it


def _ports_signature(ports: list[PortSpec]) -> tuple:
    return tuple(sorted((p.name, p.port_type, p.required, p.default) for p in ports))


def merge_model_results(results: dict[str, ModelParseResult]) -> MergedModel:
    """Merge the <TreeNodesModel> of several mission files into a single
    catalog, for building one canonical master schema.

    `results` maps a label (typically the source file path, used in
    diagnostics) to that file's ModelParseResult.

    If the same node ID is declared with different ports/types in two
    files, that's flagged as a conflict (the first-seen definition wins in
    the merged catalog, but you should resolve the conflict by hand --
    two different port lists for the same node ID almost always means one
    of the files has a stale or hand-edited model).
    """
    merged: dict[str, NodeSpec] = {}
    signatures: dict[str, tuple] = {}
    sources: dict[str, list[str]] = {}
    conflicts: list[MergeConflict] = []
    warnings: list[str] = []
    source_counts: dict[str, int] = {}

    for label, result in results.items():
        warnings += [f"{label}: {w}" for w in result.warnings]
        for node_id, spec in result.nodes.items():
            sig = _ports_signature(spec.ports)
            source_counts[node_id] = source_counts.get(node_id, 0) + 1
            if node_id not in merged:
                merged[node_id] = spec
                signatures[node_id] = sig
                sources[node_id] = [label]
            elif sig != signatures[node_id]:
                conflicts.append(MergeConflict(
                    node_id=node_id,
                    detail=(f"declared with different ports in "
                            f"{sources[node_id][0]} versus {label}; kept "
                            f"the definition from {sources[node_id][0]}."),
                ))
            else:
                sources[node_id].append(label)

    return MergedModel(merged, conflicts, warnings, source_counts)


def parse_tree_nodes_model(root: etree._Element) -> ModelParseResult:
    """Parse the (at most one) <TreeNodesModel> child of <root>.

    Returns a dict of {node_id: NodeSpec} plus any duplicate-ID or
    unrecognized-type warnings, so the caller can decide how to report them.
    """
    nodes: dict[str, NodeSpec] = {}
    duplicates: list[str] = []
    warnings: list[str] = []

    models_root = root.find("TreeNodesModel")
    if models_root is None:
        return ModelParseResult(nodes, duplicates, warnings)

    for node_el in models_root:
        tag = node_el.tag
        if tag not in _TAG_TO_KIND:
            warnings.append(
                f"Line {node_el.sourceline}: unexpected <{tag}> inside "
                f"<TreeNodesModel> (expected Action/Condition/Control/"
                f"Decorator/SubTree) -- ignored."
            )
            continue

        node_id = node_el.get("ID")
        if not node_id:
            warnings.append(
                f"Line {node_el.sourceline}: <{tag}> in <TreeNodesModel> is "
                f"missing the required [ID] attribute -- skipped."
            )
            continue

        if node_id in nodes:
            duplicates.append(node_id)

        kind = _TAG_TO_KIND[tag]
        ports: list[PortSpec] = []
        for port_el in node_el:
            if port_el.tag not in ("input_port", "output_port", "inout_port"):
                continue
            pname = port_el.get("name")
            if not pname:
                warnings.append(
                    f"Line {port_el.sourceline}: <{port_el.tag}> on node "
                    f"'{node_id}' is missing the required [name] attribute "
                    f"-- skipped."
                )
                continue
            pname = pname.strip()  # tolerate stray trailing space, e.g. "end_waypoint_body "
            raw_type = port_el.get("type", "")
            ptype = classify_port_type(raw_type) if raw_type else PortType.UNKNOWN
            if raw_type and ptype is PortType.UNKNOWN:
                warnings.append(
                    f"Line {port_el.sourceline}: port '{pname}' on node "
                    f"'{node_id}' has type '{raw_type}', which this tool "
                    f"doesn't recognize -- no value-format check will be "
                    f"applied to it (BT.CPP's own XSD generator does the "
                    f"same for non-primitive types)."
                )
            default = port_el.get("default")
            ports.append(PortSpec(
                name=pname,
                port_type=ptype,
                required=(default is None),
                default=default,
                description=(port_el.text or "").strip(),
            ))

        rules = _KIND_CHILD_RULES[kind]
        nodes[node_id] = NodeSpec(
            id=node_id, kind=kind, ports=ports,
            min_children=rules["min_children"],
            max_children=rules["max_children"],
        )

    return ModelParseResult(nodes, duplicates, warnings)
