"""
node_catalog.py

Catalog of BehaviorTree.CPP v4.x *built-in* node types (Sequence, Fallback,
Repeat, SubTree, etc.) that ship with the library itself and therefore never
appear in a mission file's own <TreeNodesModel> block.

Sourced from:
  - https://github.com/BehaviorTree/BehaviorTree.CPP  (src/xml_parsing.cpp,
    src/basic_types.cpp, include/behaviortree_cpp/tree_node.h -- master
    branch, checked July 2026)
  - https://www.behaviortree.dev/docs/nodes-library/  (v4.8 docs)

This is intentionally a *data* module (no XML parsing here) so it can be
reused by both the schema generator and the semantic validator.
"""

from dataclasses import dataclass, field
from enum import Enum


class NodeKind(Enum):
    CONTROL = "Control"       # 1..N children (rules vary, see notes)
    DECORATOR = "Decorator"   # exactly 1 child
    ACTION = "Action"         # leaf, 0 children
    CONDITION = "Condition"   # leaf, 0 children
    SUBTREE = "SubTree"       # leaf w.r.t. XML nesting, but references another tree


class PortType(Enum):
    """Coarse port-value categories used to pick an XSD restriction."""
    INT = "int"
    DOUBLE = "double"
    BOOL = "bool"
    STRING = "string"
    VECTOR_INT = "vector_int"
    VECTOR_DOUBLE = "vector_double"
    VECTOR_BOOL = "vector_bool"
    NODE_STATUS = "node_status"     # e.g. SUCCESS/FAILURE/RUNNING -- no native XSD check
    UNKNOWN = "unknown"             # custom C++ type BT.CPP itself can't map to XSD either


@dataclass
class PortSpec:
    name: str
    port_type: PortType
    required: bool = True
    default: str | None = None
    description: str = ""


@dataclass
class NodeSpec:
    id: str
    kind: NodeKind
    ports: list[PortSpec] = field(default_factory=list)
    min_children: int = 0
    max_children: int | None = None   # None == unbounded
    notes: str = ""


# ---------------------------------------------------------------------------
# Attributes that are NEVER ports, regardless of node type.
#
# Ground truth: BT::IsReservedAttribute() in src/basic_types.cpp only
# reserves: "name", "ID", "_autoremap", plus the 4 precondition and 4
# postcondition script attributes below.
#
# HOWEVER: BT::IsAllowedPortName() rejects any attribute whose *first*
# character is not a letter before it even checks the reserved list. That
# means EVERY underscore-prefixed attribute (not just the ones officially
# "reserved") silently bypasses port validation in the real C++ parser and
# is stored as an opaque "other attribute" -- this is how `_description`
# works even though it's not in IsReservedAttribute().
#
# BT.CPP's own generated XSD (writeTreeXSD()) does NOT model this "other
# attributes" bucket -- it only whitelists the 8 pre/post-condition
# attributes plus `name`. Run as-is, the stock generator would reject every
# node in these mission files, since all of them use `_description`.
#
# This tool corrects that gap by explicitly whitelisting the underscore
# attributes actually observed in your mission files (`_description`,
# `_autoremap`) rather than blanket-allowing any `_xxx` attribute -- which
# keeps validation strict enough to catch a typo'd metadata attribute
# (e.g. `_descriptoin`) as an error, at the cost of being slightly stricter
# than the real BT.CPP runtime. Add to KNOWN_METADATA_ATTRIBUTES below if
# your team adopts other underscore-prefixed conventions.
# ---------------------------------------------------------------------------

PRECONDITION_ATTRIBUTES = ["_failureIf", "_successIf", "_skipIf", "_while"]
POSTCONDITION_ATTRIBUTES = ["_onHalted", "_onFailure", "_onSuccess", "_post"]

# Attributes handled specially by the C++ parser, never treated as ports.
CORE_RESERVED_ATTRIBUTES = ["name", "ID", "_autoremap"]

# Underscore-prefixed metadata attributes actually seen in real BT.CPP usage
# / your mission files, that the stock generator omits. Extend as needed.
KNOWN_METADATA_ATTRIBUTES = ["_description"]

ALL_NON_PORT_ATTRIBUTES = (
    set(CORE_RESERVED_ATTRIBUTES)
    | set(PRECONDITION_ATTRIBUTES)
    | set(POSTCONDITION_ATTRIBUTES)
    | set(KNOWN_METADATA_ATTRIBUTES)
)

# Names that can never be used as a node/model ID (BT::validateModelName).
RESERVED_MODEL_NAMES = {"Root", "root"}

# Max XML nesting depth enforced by BT.CPP's VerifyXML (kMaxNestingDepth).
MAX_NESTING_DEPTH = 256


# ---------------------------------------------------------------------------
# Built-in node catalog (v4.8). Only nodes plausibly relevant to a mission
# file are included; this list can be extended freely -- it's pure data.
# ---------------------------------------------------------------------------

def _p(name, ptype, required=True, default=None, desc=""):
    return PortSpec(name, ptype, required, default, desc)


BUILTIN_NODES: dict[str, NodeSpec] = {}


def _register(spec: NodeSpec):
    BUILTIN_NODES[spec.id] = spec


# --- Control nodes (children come from the tree body, not ports) ---
_register(NodeSpec("Sequence", NodeKind.CONTROL, min_children=1))
_register(NodeSpec("SequenceWithMemory", NodeKind.CONTROL, min_children=1))
_register(NodeSpec("ReactiveSequence", NodeKind.CONTROL, min_children=1,
                    notes="At most one asynchronous child is allowed."))
_register(NodeSpec("Fallback", NodeKind.CONTROL, min_children=1))
_register(NodeSpec("ReactiveFallback", NodeKind.CONTROL, min_children=1))
_register(NodeSpec("Parallel", NodeKind.CONTROL, min_children=1, ports=[
    _p("success_count", PortType.INT, required=False, default="-1"),
    _p("failure_count", PortType.INT, required=False, default="1"),
]))
_register(NodeSpec("ParallelAll", NodeKind.CONTROL, min_children=1, ports=[
    _p("max_failures", PortType.INT, required=False, default="1"),
]))
_register(NodeSpec("IfThenElse", NodeKind.CONTROL, min_children=2, max_children=3))
_register(NodeSpec("WhileDoElse", NodeKind.CONTROL, min_children=2, max_children=3))
for _n in (2, 3, 4, 5, 6):
    _ports = [_p("variable", PortType.STRING)]
    _ports += [_p(f"case_{i}", PortType.STRING, required=False) for i in range(1, _n + 1)]
    _register(NodeSpec(f"Switch{_n}", NodeKind.CONTROL, ports=_ports,
                        min_children=_n, max_children=_n + 1))
_register(NodeSpec("TryCatch", NodeKind.CONTROL, min_children=2,
                    notes="Must have at least 2 children."))

# --- Decorator nodes (exactly 1 child) ---
_register(NodeSpec("Inverter", NodeKind.DECORATOR, min_children=1, max_children=1))
_register(NodeSpec("ForceSuccess", NodeKind.DECORATOR, min_children=1, max_children=1))
_register(NodeSpec("ForceFailure", NodeKind.DECORATOR, min_children=1, max_children=1))
_register(NodeSpec("Repeat", NodeKind.DECORATOR, min_children=1, max_children=1, ports=[
    _p("num_cycles", PortType.INT, desc="Number of repetitions. -1 for infinite loop."),
]))
_register(NodeSpec("RetryUntilSuccessful", NodeKind.DECORATOR, min_children=1, max_children=1, ports=[
    _p("num_attempts", PortType.INT, desc="Number of attempts. -1 for infinite retries."),
]))
_register(NodeSpec("RetryUntilSuccesful", NodeKind.DECORATOR, min_children=1, max_children=1, ports=[
    _p("num_attempts", PortType.INT),
], notes="Deprecated alias (single 's') kept for backward compatibility."))
_register(NodeSpec("KeepRunningUntilFailure", NodeKind.DECORATOR, min_children=1, max_children=1))
_register(NodeSpec("Delay", NodeKind.DECORATOR, min_children=1, max_children=1, ports=[
    _p("delay_msec", PortType.INT),
]))
_register(NodeSpec("Timeout", NodeKind.DECORATOR, min_children=1, max_children=1, ports=[
    _p("msec", PortType.INT),
]))
_register(NodeSpec("RunOnce", NodeKind.DECORATOR, min_children=1, max_children=1, ports=[
    _p("then_skip", PortType.BOOL, required=False, default="true"),
]))
_register(NodeSpec("Precondition", NodeKind.DECORATOR, min_children=1, max_children=1, ports=[
    _p("if", PortType.STRING),
    _p("else", PortType.NODE_STATUS, required=False, default="FAILURE"),
]))

# --- SubTree (0 XML children; references another <BehaviorTree ID=...>) ---
# NOTE: `ID` is added by schema_generator.py as a special case (along with
# an <xs:anyAttribute> to allow arbitrary port-remapping attributes), not
# listed here, to avoid declaring it twice.
_register(NodeSpec("SubTree", NodeKind.SUBTREE, min_children=0, max_children=0, ports=[]))
