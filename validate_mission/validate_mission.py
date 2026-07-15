#!/usr/bin/env python3

import argparse
import re
import sys
from pathlib import Path

from lxml import etree


MISSION_DIR = Path("onboard/src/behaviortree_ros2/mission_tree_files")
DEFAULT_XML_NAME = "Trial Mission File.xml"
DEFAULT_XSD_FILE = Path("validate_mission/mission.xsd")
XS_NS = {"xs": "http://www.w3.org/2001/XMLSchema"}


def find_open_element_at_line(xml_path: Path, line_number: int | None) -> str | None:
    if line_number is None:
        return None

    try:
        lines = xml_path.read_text(encoding="utf-8").splitlines()
    except OSError:
        return None

    for line in reversed(lines[:line_number]):
        match = re.search(r"<\s*([A-Za-z_][A-Za-z0-9_.:-]*)\b", line)
        if match and not line.lstrip().startswith(("</", "<?", "<!")):
            return match.group(1)
    return None


def find_attribute_name_for_syntax_error(
    message: str, xml_path: Path, line_number: int | None
) -> str | None:
    attr_match = re.search(r"Specification mandates value for attribute (\w+)", message)
    if attr_match:
        return attr_match.group(1)

    if "AttValue:" not in message or line_number is None:
        return None

    try:
        lines = xml_path.read_text(encoding="utf-8").splitlines()
    except OSError:
        return None

    for line in reversed(lines[:line_number]):
        attr_match = re.search(r"([A-Za-z_][A-Za-z0-9_.:-]*)\s*=\s*$", line)
        if attr_match:
            return attr_match.group(1)
    return None


def allowed_attributes(schema_doc: etree._ElementTree, element_name: str) -> list[str]:
    element = schema_doc.xpath(
        f"//xs:element[@name=$name]",
        namespaces=XS_NS,
        name=element_name,
    )
    if not element:
        return []

    node_type = element[0].get("type")
    if not node_type:
        return []

    complex_type = schema_doc.xpath(
        f"//xs:complexType[@name=$name]",
        namespaces=XS_NS,
        name=node_type,
    )
    if not complex_type:
        return []

    return sorted(
        attr.get("name")
        for attr in complex_type[0].xpath("./xs:attribute", namespaces=XS_NS)
        if attr.get("name")
    )


def add_port_hint_for_xml_syntax_error(
    exc: etree.XMLSyntaxError, xml_path: Path, schema_doc: etree._ElementTree
) -> str:
    message = str(exc)
    attr_name = find_attribute_name_for_syntax_error(message, xml_path, exc.lineno)
    if not attr_name:
        return message

    element_name = find_open_element_at_line(xml_path, exc.lineno)
    if not element_name:
        return message

    ports = allowed_attributes(schema_doc, element_name)
    if attr_name in ports or not ports:
        return message

    return (
        f"{message}\n"
        f"{xml_path}:{exc.lineno}: ERROR: '{attr_name}' is not a provided port "
        f"of {element_name}. Provided ports: {', '.join(ports)}"
    )


def validate_mission_xml(xml_path: Path, xsd_path: Path) -> tuple[bool, str]:
    try:
        schema_doc = etree.parse(str(xsd_path))
        schema = etree.XMLSchema(schema_doc)
    except (OSError, etree.XMLSchemaParseError) as exc:
        return False, str(exc)

    try:
        xml_doc = etree.parse(str(xml_path))
    except OSError as exc:
        return False, str(exc)
    except etree.XMLSyntaxError as exc:
        return False, add_port_hint_for_xml_syntax_error(exc, xml_path, schema_doc)

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
        print(f"Mission XML failed schema validation: {args.xml_file}", file=sys.stderr)
        if error:
          print(error, file=sys.stderr)
        return 1
    print(f"Mission XML passed schema validation: {args.xml_file}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
