"""
schema_reader.py

Reconstructs a {node_id: NodeSpec} catalog by reading an already-generated
mission_schema.xsd back in. This is what lets `validate` work from the
single checked-in schema file only -- it never needs to touch mission
files' own <TreeNodesModel> or regenerate anything. The only writer of
schema files in this whole tool is `generate-schema`
(see schema_generator.py / cli.py).

This only needs to understand the specific shape schema_generator.py
produces (it's not a general-purpose XSD reader) -- each node's
complexType is named "{ID}Type" and follows one of a few fixed patterns.
"""

from __future__ import annotations

from lxml import etree

from .node_catalog import NodeSpec, NodeKind, PortSpec, PortType

XS = "http://www.w3.org/2001/XMLSchema"
_NS = {"xs": XS}

_XSD_TYPE_TO_PORT_TYPE = {
    "integerOrBlackboardType": PortType.INT,
    "decimalOrBlackboardType": PortType.DOUBLE,
    "booleanOrBlackboardType": PortType.BOOL,
    "stringOrBlackboardType": PortType.STRING,
    "vectorIntOrBlackboardType": PortType.VECTOR_INT,
    "vectorDoubleOrBlackboardType": PortType.VECTOR_DOUBLE,
    "vectorBoolOrBlackboardType": PortType.VECTOR_BOOL,
}


def read_node_catalog(schema_root: etree._Element) -> dict[str, NodeSpec]:
    """Parse every '<xs:complexType name="XxxType">' in the schema back
    into a NodeSpec, keyed by node ID ("Xxx")."""
    nodes: dict[str, NodeSpec] = {}

    for type_el in schema_root.findall(f"{{{XS}}}complexType"):
        type_name = type_el.get("name", "")
        if not type_name.endswith("Type"):
            continue
        node_id = type_name[: -len("Type")]

        group_el = type_el.find(f"{{{XS}}}group")
        any_attr_el = type_el.find(f"{{{XS}}}anyAttribute")

        if group_el is not None:
            min_o = group_el.get("minOccurs", "1")
            max_o = group_el.get("maxOccurs", "1")
            min_children = int(min_o)
            max_children = None if max_o == "unbounded" else int(max_o)
            kind = NodeKind.DECORATOR if (min_children == 1 and max_children == 1) \
                else NodeKind.CONTROL
        elif any_attr_el is not None:
            kind = NodeKind.SUBTREE
            min_children = 0
            max_children = 0
        else:
            kind = NodeKind.ACTION  # ACTION/CONDITION are indistinguishable here;
            min_children = 0        # doesn't matter for any check this tool does.
            max_children = 0

        ports: list[PortSpec] = []
        for attr_el in type_el.findall(f"{{{XS}}}attribute"):
            pname = attr_el.get("name")
            if pname in (None, "ID"):
                continue  # SubTree's ID is handled specially, not a "port"
            xsd_type = attr_el.get("type")
            port_type = _XSD_TYPE_TO_PORT_TYPE.get(xsd_type, PortType.UNKNOWN)
            default = attr_el.get("default")
            ports.append(PortSpec(
                name=pname,
                port_type=port_type,
                required=(attr_el.get("use") == "required"),
                default=default,
            ))

        nodes[node_id] = NodeSpec(
            id=node_id, kind=kind, ports=ports,
            min_children=min_children, max_children=max_children,
        )

    return nodes
