"""
semantic_checks.py

Checks that are either impossible or awkward to express in XSD, run as a
second pass after schema validation:

  - <SubTree ID="X"/> must reference a <BehaviorTree ID="X"> defined
    somewhere in the same file (these mission files are self-contained --
    no <include>, confirmed by inspection of all provided samples).
  - `main_tree_to_execute` (or the single-tree special case) must resolve
    to a real <BehaviorTree ID=...>.
  - No two <BehaviorTree> elements share an ID.
  - No <BehaviorTree> is unreachable (defined but never used as the main
    tree or referenced by any SubTree) -- reported as a warning, not an
    error: an unused tree isn't necessarily a mistake, but is worth a
    human's attention.
  - A <TreeNodesModel> entry that's never actually used by any tree in the
    file -- warning only, same reasoning as above.
"""

from __future__ import annotations

from collections import defaultdict
from dataclasses import dataclass, field
from lxml import etree

from .node_catalog import NodeSpec, PortType

_VECTOR_TYPES = (PortType.VECTOR_INT, PortType.VECTOR_DOUBLE, PortType.VECTOR_BOOL)


@dataclass
class Finding:
    severity: str   # "error" | "warning"
    line: int | None
    message: str


@dataclass
class SemanticReport:
    findings: list[Finding] = field(default_factory=list)

    def error(self, line, message):
        self.findings.append(Finding("error", line, message))

    def warning(self, line, message):
        self.findings.append(Finding("warning", line, message))

    @property
    def errors(self):
        return [f for f in self.findings if f.severity == "error"]

    @property
    def warnings(self):
        return [f for f in self.findings if f.severity == "warning"]


def run_semantic_checks(root: etree._Element, all_nodes: dict[str, NodeSpec]) -> SemanticReport:
    report = SemanticReport()

    bt_elements = root.findall("BehaviorTree")
    tree_ids: dict[str, etree._Element] = {}
    for bt in bt_elements:
        tid = bt.get("ID")
        if not tid:
            continue  # XSD/structural layer already flags missing ID
        if tid in tree_ids:
            report.error(bt.sourceline,
                         f"Duplicate <BehaviorTree ID=\"{tid}\">: a tree with "
                         f"this ID was already defined at line "
                         f"{tree_ids[tid].sourceline}.")
        else:
            tree_ids[tid] = bt

    # main_tree_to_execute resolution
    main_tree_id = root.get("main_tree_to_execute")
    if main_tree_id is None:
        if len(bt_elements) > 1:
            report.error(root.sourceline,
                         "Root has more than one <BehaviorTree> but no "
                         "[main_tree_to_execute] attribute -- BT.CPP "
                         "wouldn't know which tree to run.")
        elif len(bt_elements) == 0:
            report.error(root.sourceline, "No <BehaviorTree> defined in this file.")
    elif main_tree_id not in tree_ids:
        report.error(root.sourceline,
                     f"[main_tree_to_execute=\"{main_tree_id}\"] does not "
                     f"match any defined <BehaviorTree ID>. Defined trees: "
                     f"{sorted(tree_ids) or '(none)'}.")

    # SubTree reference resolution + reachability tracking
    referenced_ids: set[str] = set()
    if main_tree_id in tree_ids:
        referenced_ids.add(main_tree_id)
    elif len(tree_ids) == 1:
        referenced_ids.add(next(iter(tree_ids)))

    for subtree_el in root.iter("SubTree"):
        ref_id = subtree_el.get("ID")
        if not ref_id:
            continue  # structural layer already flags this
        referenced_ids.add(ref_id)
        if ref_id not in tree_ids:
            report.error(subtree_el.sourceline,
                         f"<SubTree ID=\"{ref_id}\"/> does not match any "
                         f"<BehaviorTree ID=\"{ref_id}\"> defined in this "
                         f"file. Defined trees: {sorted(tree_ids) or '(none)'}.")

    for tid, bt in tree_ids.items():
        if tid not in referenced_ids:
            report.warning(bt.sourceline,
                            f"<BehaviorTree ID=\"{tid}\"> is defined but never "
                            f"used (not the main tree and not referenced by "
                            f"any <SubTree>). Dead tree, or a typo elsewhere?")

    # Unused TreeNodesModel entries (declared but never placed in a tree body)
    used_node_names: set[str] = set()
    for bt in bt_elements:
        for el in bt.iter():
            if isinstance(el.tag, str):
                used_node_names.add(el.tag)
    # SubTree elements are counted under tag "SubTree" already; that's fine
    # since "SubTree" itself is a builtin node id, not a custom model entry.

    models_root = root.find("TreeNodesModel")
    if models_root is not None:
        for node_el in models_root:
            node_id = node_el.get("ID")
            if node_id and node_id not in used_node_names:
                report.warning(node_el.sourceline,
                                f"<TreeNodesModel> declares node '{node_id}' "
                                f"but no tree in this file actually uses it.")

    # Vector-port length consistency. The declared type (e.g.
    # std::vector<float>) doesn't encode a fixed length, but a port like
    # `world_waypoint` almost always represents a fixed-size pose (commonly
    # [6x1] here). If the same port on the same node type shows up with a
    # different number of comma-separated values elsewhere in the file,
    # that's a strong smell of a copy-paste typo -- worth a human's
    # attention even though it isn't a schema violation on its own.
    lengths_seen: dict[tuple[str, str], dict[int, list[int]]] = defaultdict(lambda: defaultdict(list))
    for bt in bt_elements:
        for el in bt.iter():
            if not isinstance(el.tag, str):
                continue
            spec = all_nodes.get(el.tag)
            if spec is None:
                continue
            for port in spec.ports:
                if port.port_type not in _VECTOR_TYPES:
                    continue
                value = el.get(port.name)
                if not value or (value.startswith("{") and value.endswith("}")):
                    continue  # blackboard reference, length not knowable statically
                length = len(value.split(","))
                lengths_seen[(el.tag, port.name)][length].append(el.sourceline)

    for (node_tag, port_name), by_length in lengths_seen.items():
        if len(by_length) > 1:
            detail = "; ".join(
                f"{length} value(s) at line(s) {sorted(lines)}"
                for length, lines in sorted(by_length.items())
            )
            report.warning(None,
                            f"Port '{port_name}' on node '{node_tag}' has "
                            f"inconsistent vector length across this file: "
                            f"{detail}. Possible copy-paste mistake.")

    return report
