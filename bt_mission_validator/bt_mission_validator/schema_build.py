"""
schema_build.py

The ONLY place in this tool that generates a schema. Invoked explicitly
(via `cli.py generate-schema`), never implicitly during validation.

Takes one or more existing BehaviorTree.CPP mission files that already have
a populated <TreeNodesModel> (e.g. your existing mission files, or a
dedicated "node registry" file if your team wants to maintain one), merges
their custom node declarations with the built-in BT.CPP catalog, and
produces the single canonical mission_schema.xsd that `validate` checks
every mission file against.
"""

from __future__ import annotations

from dataclasses import dataclass, field
from pathlib import Path

from lxml import etree

from .node_catalog import BUILTIN_NODES, NodeSpec
from .model_parser import parse_tree_nodes_model, merge_model_results, MergeConflict
from .schema_generator import generate_schema, schema_to_string


@dataclass
class SchemaBuildResult:
    schema_xml: str
    all_nodes: dict[str, NodeSpec]
    conflicts: list[MergeConflict] = field(default_factory=list)
    warnings: list[str] = field(default_factory=list)
    source_files: list[str] = field(default_factory=list)
    redeclared_builtins: list[str] = field(default_factory=list)


def build_master_schema(mission_paths: list[str | Path]) -> SchemaBuildResult:
    per_file_results = {}
    for p in mission_paths:
        p = Path(p)
        tree = etree.parse(str(p))
        root = tree.getroot()
        per_file_results[str(p)] = parse_tree_nodes_model(root)

    merged = merge_model_results(per_file_results)

    all_nodes: dict[str, NodeSpec] = dict(BUILTIN_NODES)
    redeclared_builtins: list[str] = []
    for node_id, spec in merged.nodes.items():
        if node_id in BUILTIN_NODES:
            redeclared_builtins.append(node_id)
            continue
        all_nodes[node_id] = spec

    schema_tree = generate_schema(
        all_nodes,
        root_comment=(
            f"Canonical mission schema. Regenerate with: "
            f"python -m bt_mission_validator.cli generate-schema <mission files...>"
        ),
    )

    return SchemaBuildResult(
        schema_xml=schema_to_string(schema_tree),
        all_nodes=all_nodes,
        conflicts=merged.conflicts,
        warnings=merged.warnings,
        source_files=[str(Path(p)) for p in mission_paths],
        redeclared_builtins=redeclared_builtins,
    )
