"""
schema_generator.py

Builds an XSD schema for one mission file, combining:
  - BehaviorTree.CPP's built-in nodes (node_catalog.BUILTIN_NODES), and
  - the custom Action/Condition/Control/Decorator nodes declared in that
    specific file's own <TreeNodesModel> block (model_parser).

The structure deliberately mirrors BT::writeTreeXSD() in BT.CPP's
xml_parsing.cpp (master branch, as of July 2026) -- same simple types,
same attribute groups, same per-node complexType generation strategy --
so the output is recognizable to anyone who has seen BT.CPP's own
Groot-oriented schema output. Two corrections are layered on top, since
this is meant to be actually run in CI rather than eyeballed in an editor:

  1. `_description` and `_autoremap` are added to the common attribute
     group (see node_catalog.py for why the stock generator omits them).
  2. `std::vector<float>`, `std::vector<bool>`, `std::vector<int>` ports
     get real regex-validated simple types instead of being left
     unrestricted (which is what BT.CPP's own xsdAttributeType() does,
     since it only special-cases int/double/bool/std::string).

Only the "compact" XML syntax (e.g. <Sequence>, <DriveToWorldWaypoint .../>)
is supported, matching both BT.CPP's own generator and every sample mission
file provided.
"""

from __future__ import annotations

from lxml import etree

from .node_catalog import (
    NodeSpec, NodeKind, PortType,
    PRECONDITION_ATTRIBUTES, POSTCONDITION_ATTRIBUTES,
    KNOWN_METADATA_ATTRIBUTES,
)

XS = "http://www.w3.org/2001/XMLSchema"
NSMAP = {"xs": XS}


def _qn(tag: str) -> str:
    return f"{{{XS}}}{tag}"


_PORT_TYPE_TO_XSD_TYPE = {
    PortType.INT: "integerOrBlackboardType",
    PortType.DOUBLE: "decimalOrBlackboardType",
    PortType.BOOL: "booleanOrBlackboardType",
    PortType.STRING: "stringOrBlackboardType",
    PortType.VECTOR_INT: "vectorIntOrBlackboardType",
    PortType.VECTOR_DOUBLE: "vectorDoubleOrBlackboardType",
    PortType.VECTOR_BOOL: "vectorBoolOrBlackboardType",
    # NODE_STATUS / UNKNOWN -> no restriction, same as stock BT.CPP behavior
}

_COMMON_TYPES_XML = """
<xs:simpleType name="blackboardType">
    <xs:restriction base="xs:string">
        <xs:pattern value="\\{.*\\}"/>
    </xs:restriction>
</xs:simpleType>
<xs:simpleType name="booleanOrBlackboardType">
  <xs:union memberTypes="xs:boolean blackboardType"/>
</xs:simpleType>
<xs:simpleType name="integerOrBlackboardType">
  <xs:union memberTypes="xs:integer blackboardType"/>
</xs:simpleType>
<xs:simpleType name="decimalOrBlackboardType">
  <xs:union memberTypes="xs:decimal blackboardType"/>
</xs:simpleType>
<xs:simpleType name="stringOrBlackboardType">
  <xs:union memberTypes="xs:string blackboardType"/>
</xs:simpleType>
<xs:simpleType name="descriptionType">
    <xs:restriction base="xs:string">
      <xs:whiteSpace value="preserve"/>
    </xs:restriction>
</xs:simpleType>

<!-- Extensions beyond BT.CPP's stock generator: comma-separated numeric /
     boolean vectors are how [6x1] pose/mask/tolerance ports are encoded in
     these mission files (e.g. world_waypoint="10,0,0,0,0,0"). BT.CPP itself
     leaves std::vector<T> ports completely unrestricted in the XSD it
     generates; we validate the textual shape here instead. -->
<xs:simpleType name="rawVectorIntType">
  <xs:restriction base="xs:string">
    <xs:pattern value="-?[0-9]+(,\\s*-?[0-9]+)*"/>
  </xs:restriction>
</xs:simpleType>
<xs:simpleType name="vectorIntOrBlackboardType">
  <xs:union memberTypes="rawVectorIntType blackboardType"/>
</xs:simpleType>
<xs:simpleType name="rawVectorDoubleType">
  <xs:restriction base="xs:string">
    <xs:pattern value="-?[0-9]+(\\.[0-9]+)?(,\\s*-?[0-9]+(\\.[0-9]+)?)*"/>
  </xs:restriction>
</xs:simpleType>
<xs:simpleType name="vectorDoubleOrBlackboardType">
  <xs:union memberTypes="rawVectorDoubleType blackboardType"/>
</xs:simpleType>
<xs:simpleType name="rawVectorBoolType">
  <xs:restriction base="xs:string">
    <xs:pattern value="(true|false|0|1)(,\\s*(true|false|0|1))*"/>
  </xs:restriction>
</xs:simpleType>
<xs:simpleType name="vectorBoolOrBlackboardType">
  <xs:union memberTypes="rawVectorBoolType blackboardType"/>
</xs:simpleType>

<xs:complexType name="inputPortType">
  <xs:simpleContent>
    <xs:extension base="xs:string">
      <xs:attribute name="name" type="xs:string" use="required"/>
      <xs:attribute name="type" type="xs:string" use="optional"/>
      <xs:attribute name="default" type="xs:string" use="optional"/>
    </xs:extension>
  </xs:simpleContent>
</xs:complexType>
<xs:complexType name="outputPortType">
  <xs:simpleContent>
    <xs:extension base="xs:string">
      <xs:attribute name="name" type="xs:string" use="required"/>
      <xs:attribute name="type" type="xs:string" use="optional"/>
    </xs:extension>
  </xs:simpleContent>
</xs:complexType>
<xs:attributeGroup name="preconditionAttributeGroup">
  __PRECOND_ATTRS__
</xs:attributeGroup>
<xs:attributeGroup name="postconditionAttributeGroup">
  __POSTCOND_ATTRS__
</xs:attributeGroup>
"""

_COMMON_ATTR_GROUP_XML = """
<xs:attributeGroup name="commonAttributeGroup">
  <xs:attribute name="name" type="xs:string" use="optional"/>
  __METADATA_ATTRS__
  <xs:attributeGroup ref="preconditionAttributeGroup"/>
  <xs:attributeGroup ref="postconditionAttributeGroup"/>
</xs:attributeGroup>
"""

_MODEL_TYPES_XML = """
<xs:complexType name="treeNodesModelNodeType">
  <xs:sequence>
    <xs:choice minOccurs="0" maxOccurs="unbounded">
      <xs:element name="input_port" type="inputPortType"/>
      <xs:element name="output_port" type="outputPortType"/>
    </xs:choice>
    <xs:element name="description" type="descriptionType" minOccurs="0" maxOccurs="1"/>
  </xs:sequence>
  <xs:attribute name="ID" type="xs:string" use="required"/>
</xs:complexType>
<xs:group name="treeNodesModelNodeGroup">
  <xs:choice>
    <xs:element name="Action" type="treeNodesModelNodeType"/>
    <xs:element name="Condition" type="treeNodesModelNodeType"/>
    <xs:element name="Control" type="treeNodesModelNodeType"/>
    <xs:element name="Decorator" type="treeNodesModelNodeType"/>
  </xs:choice>
</xs:group>
"""

_ROOT_ELEMENT_XML = """
<xs:element name="root">
  <xs:complexType>
    <xs:sequence>
      <xs:choice minOccurs="0" maxOccurs="unbounded">
        <xs:element ref="include"/>
        <xs:element ref="BehaviorTree"/>
      </xs:choice>
      <xs:element ref="TreeNodesModel" minOccurs="0" maxOccurs="1"/>
    </xs:sequence>
    <xs:attribute name="BTCPP_format" type="xs:string" use="required"/>
    <xs:attribute name="main_tree_to_execute" type="xs:string" use="optional"/>
  </xs:complexType>
</xs:element>
"""

_INCLUDE_ELEMENT_XML = """
<xs:element name="include">
  <xs:complexType>
    <xs:attribute name="path" type="xs:string" use="required"/>
    <xs:attribute name="ros_pkg" type="xs:string" use="optional"/>
  </xs:complexType>
</xs:element>
"""

_BEHAVIORTREE_ELEMENT_XML = """
<xs:element name="BehaviorTree">
  <xs:complexType>
    <xs:group ref="oneNodeGroup"/>
    <xs:attribute name="ID" type="xs:string" use="required"/>
  </xs:complexType>
</xs:element>
"""

_TREENODESMODEL_ELEMENT_XML = """
<xs:element name="TreeNodesModel">
  <xs:complexType>
    <xs:group ref="treeNodesModelNodeGroup" minOccurs="0" maxOccurs="unbounded"/>
  </xs:complexType>
</xs:element>
"""


def _attr_group_lines(names: list[str]) -> str:
    return "\n  ".join(
        f'<xs:attribute name="{n}" type="xs:string" use="optional"/>' for n in names
    )


def _parse_fragment(xml_string: str) -> list[etree._Element]:
    wrapper = f"<wrap xmlns:xs='{XS}'>{xml_string}</wrap>"
    root = etree.fromstring(wrapper.encode("utf-8"))
    return list(root)


def generate_schema(all_nodes: dict[str, NodeSpec], *, root_comment: str = "") -> etree._ElementTree:
    """Build the full XSD document (as an lxml ElementTree) for the given
    combined node catalog (built-ins + this file's custom nodes)."""

    schema_el = etree.Element(_qn("schema"), nsmap=NSMAP)
    schema_el.set("elementFormDefault", "qualified")

    if root_comment:
        schema_el.append(etree.Comment(root_comment))

    metadata_attrs = _attr_group_lines(KNOWN_METADATA_ATTRIBUTES)
    precond_attrs = _attr_group_lines(PRECONDITION_ATTRIBUTES)
    postcond_attrs = _attr_group_lines(POSTCONDITION_ATTRIBUTES)

    common_types_xml = (
        _COMMON_TYPES_XML
        .replace("__PRECOND_ATTRS__", precond_attrs)
        .replace("__POSTCOND_ATTRS__", postcond_attrs)
    )
    for el in _parse_fragment(common_types_xml):
        schema_el.append(el)

    common_attr_group_xml = _COMMON_ATTR_GROUP_XML.replace("__METADATA_ATTRS__", metadata_attrs)
    for el in _parse_fragment(common_attr_group_xml):
        schema_el.append(el)

    for el in _parse_fragment(_MODEL_TYPES_XML):
        schema_el.append(el)

    for el in _parse_fragment(_ROOT_ELEMENT_XML):
        schema_el.append(el)

    # oneNodeGroup: choice over every known node ID (builtins + custom)
    one_node_group = etree.SubElement(schema_el, _qn("group"))
    one_node_group.set("name", "oneNodeGroup")
    choice = etree.SubElement(one_node_group, _qn("choice"))
    for node_id in sorted(all_nodes.keys()):
        el = etree.SubElement(choice, _qn("element"))
        el.set("name", node_id)
        el.set("type", f"{node_id}Type")

    for el in _parse_fragment(_INCLUDE_ELEMENT_XML):
        schema_el.append(el)
    for el in _parse_fragment(_BEHAVIORTREE_ELEMENT_XML):
        schema_el.append(el)
    for el in _parse_fragment(_TREENODESMODEL_ELEMENT_XML):
        schema_el.append(el)

    # Per-node complexType definitions
    for node_id in sorted(all_nodes.keys()):
        spec = all_nodes[node_id]
        type_el = etree.SubElement(schema_el, _qn("complexType"))
        type_el.set("name", f"{node_id}Type")

        if spec.kind in (NodeKind.ACTION, NodeKind.CONDITION, NodeKind.SUBTREE):
            pass  # no children
        elif spec.kind is NodeKind.DECORATOR:
            group = etree.SubElement(type_el, _qn("group"))
            group.set("ref", "oneNodeGroup")
            group.set("minOccurs", "1")
            group.set("maxOccurs", "1")
        else:  # CONTROL
            group = etree.SubElement(type_el, _qn("group"))
            group.set("ref", "oneNodeGroup")
            group.set("minOccurs", str(spec.min_children))
            group.set("maxOccurs", "unbounded" if spec.max_children is None
                       else str(spec.max_children))

        common_attr = etree.SubElement(type_el, _qn("attributeGroup"))
        common_attr.set("ref", "commonAttributeGroup")

        for port in spec.ports:
            attr = etree.SubElement(type_el, _qn("attribute"))
            attr.set("name", port.name)
            xsd_type = _PORT_TYPE_TO_XSD_TYPE.get(port.port_type)
            if xsd_type:
                attr.set("type", xsd_type)
            if port.default is not None:
                attr.set("default", port.default)
            else:
                attr.set("use", "required")

        if node_id == "SubTree":
            for el in _parse_fragment(
                '<xs:attribute name="ID" type="xs:string" use="required"/>'
                '<xs:anyAttribute processContents="skip"/>'
            ):
                type_el.append(el)

    return etree.ElementTree(schema_el)


def schema_to_string(tree: etree._ElementTree) -> str:
    return etree.tostring(
        tree, pretty_print=True, xml_declaration=True, encoding="UTF-8"
    ).decode("utf-8")
