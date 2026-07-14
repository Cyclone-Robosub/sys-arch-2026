"""
cli.py -- command line interface.

Two explicit, separate actions:

  generate-schema   Build/update the single canonical mission_schema.xsd
                     from one or more mission files that have a populated
                     <TreeNodesModel>. This is the ONLY command that writes
                     a schema. Run it by hand whenever a node's ports
                     change or a new node is introduced.

  validate           Check mission file(s) against an existing schema
                      (defaults to the one shipped in this package). Never
                      generates or modifies a schema.

Examples:
    # Rebuild the canonical schema from your current mission files
    python -m bt_mission_validator.cli generate-schema missions/*.xml \\
        -o bt_mission_validator/schemas/mission_schema.xsd

    # Validate against that schema (the default, if -o above wasn't changed)
    python -m bt_mission_validator.cli validate missions/*.xml

    # Validate against a specific/alternate schema
    python -m bt_mission_validator.cli validate --schema my_schema.xsd missions/*.xml

Exit code for `validate` is 0 only if every given file passed (0 errors).
Warnings never affect the exit code.
"""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

from .validator import validate_file, DEFAULT_SCHEMA_PATH
from .schema_build import build_master_schema


def _print_findings(findings, kind: str, empty_message: str):
    if not findings:
        print(f"    {empty_message}")
        return
    for f in findings:
        loc = f"line {f.line}" if f.line else "\u2014"
        print(f"    [{kind}] ({loc}) {f.message}")


def _cmd_validate(args) -> int:
    all_ok = True
    for file_path in args.files:
        result = validate_file(file_path, schema_path=args.schema)
        all_ok = all_ok and result.ok
        print(result.summary_line())
        if not args.quiet:
            _print_findings(result.errors, "ERROR", "No errors.")
            _print_findings(result.warnings, "WARN", "No warnings.")
    return 0 if all_ok else 1


def _cmd_generate_schema(args) -> int:
    build = build_master_schema(args.files)

    out_path = Path(args.output)
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(build.schema_xml)

    print(f"Wrote {out_path}  ({len(build.all_nodes)} node types total)")
    print(f"  from {len(build.source_files)} source file(s):")
    for f in build.source_files:
        print(f"    - {f}")

    if build.redeclared_builtins:
        print(f"  Note: ignored {len(build.redeclared_builtins)} redundant "
              f"redeclaration(s) of built-in nodes: {build.redeclared_builtins}")

    if build.warnings:
        print(f"  {len(build.warnings)} warning(s) while parsing source models:")
        for w in build.warnings:
            print(f"    - {w}")

    if build.conflicts:
        print(f"  {len(build.conflicts)} CONFLICT(s) -- same node ID declared "
              f"with different ports in different files (first one seen was kept; "
              f"resolve by hand and regenerate):")
        for c in build.conflicts:
            print(f"    - {c.node_id}: {c.detail}")
        return 1

    return 0


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(
        prog="bt_mission_validator",
        description="Validate BehaviorTree.CPP AUV mission XML files against "
                     "a single canonical schema.",
    )
    subparsers = parser.add_subparsers(dest="command", required=True)

    p_validate = subparsers.add_parser(
        "validate", help="Validate mission file(s) against an existing schema.")
    p_validate.add_argument("files", nargs="+", help="Mission XML file(s) to validate")
    p_validate.add_argument("--schema", default=str(DEFAULT_SCHEMA_PATH),
                             help=f"Path to the .xsd to validate against "
                                  f"(default: the schema shipped with this "
                                  f"package, {DEFAULT_SCHEMA_PATH})")
    p_validate.add_argument("--quiet", action="store_true",
                             help="Only print the pass/fail summary line per file")
    p_validate.set_defaults(func=_cmd_validate)

    p_gen = subparsers.add_parser(
        "generate-schema",
        help="(Re)build the canonical schema from mission file(s) with a "
             "populated <TreeNodesModel>.")
    p_gen.add_argument("files", nargs="+",
                        help="Mission XML file(s) whose <TreeNodesModel> "
                             "blocks should be merged into the schema")
    p_gen.add_argument("-o", "--output", default=str(DEFAULT_SCHEMA_PATH),
                        help=f"Where to write the schema (default: {DEFAULT_SCHEMA_PATH})")
    p_gen.set_defaults(func=_cmd_generate_schema)

    args = parser.parse_args(argv)
    return args.func(args)


if __name__ == "__main__":
    sys.exit(main())
