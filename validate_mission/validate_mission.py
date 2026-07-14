#!/usr/bin/env python3

import argparse
import sys
from pathlib import Path

from lxml import etree


MISSION_DIR = Path("onboard/src/behaviortree_ros2/mission_tree_files")
DEFAULT_XML_NAME = "Trial Mission File.xml"
DEFAULT_XSD_FILE = Path("validate_mission/mission.xsd")


def validate_mission_xml(xml_path: Path, xsd_path: Path) -> tuple[bool, str]:
    try:
        schema_doc = etree.parse(str(xsd_path))
        schema = etree.XMLSchema(schema_doc)
        xml_doc = etree.parse(str(xml_path))
    except (OSError, etree.XMLSyntaxError, etree.XMLSchemaParseError) as exc:
        return False, str(exc)

    if schema.validate(xml_doc):
        return True, ""

    errors = "\n".join(
        f"{xml_path}:{error.line}:{error.column}: {error.level_name}: {error.message}"
        for error in schema.error_log
    )
    return False, errors


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Validate a mission XML file against mission.xsd."
    )
    parser.add_argument(
        "xml_file",
        nargs="?",
        type=Path,
        default=DEFAULT_XML_NAME,
        help=f"Name of mission XML file to validate. Default: {DEFAULT_XML_NAME}",
    )
    parser.add_argument(
        "--xsd_file",
        type=Path,
        default=DEFAULT_XSD_FILE,
        help=f"XML Schema file. Default: {DEFAULT_XSD_FILE}",
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    xml_path = MISSION_DIR / args.xml_file
    ok, error = validate_mission_xml(xml_path, args.xsd_file)

    if not ok:
        print(f"Mission XML failed schema validation: {xml_path}", file=sys.stderr)
        if error:
          print(error, file=sys.stderr)
        return 1
    print(f"Mission XML passed schema validation: {args.xml_file}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
