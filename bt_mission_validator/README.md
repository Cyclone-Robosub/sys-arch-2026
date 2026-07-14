# BT Mission Validator

A Python utility that validates BehaviorTree.CPP v4 AUV mission XML files
against a single, checked-in `.xsd` schema, plus a separate, explicit
command to (re)build that schema from mission files with a populated
`<TreeNodesModel>`.

**Validation never generates a schema. Schema generation is a distinct,
deliberate step you run by hand.**

## Why this exists

Your mission files carry their own `<TreeNodesModel>` block (used by
Groot), but nothing currently checks that a mission file's tree bodies
actually match it. For example, `Trial_Mission_File.xml` as provided uses
a `<DurationTrick>` node that was never declared in `<TreeNodesModel>` --
in fact it's not declared in *any* of your mission files, so it's absent
from the canonical schema too, and the tool correctly rejects the file
(see `tests/test_validator.py::test_trial_mission_file_correctly_fails_on_undeclared_node`).

## Quick start

```bash
pip install -r requirements.txt   # just lxml
cd bt_mission_validator

# Validate against the schema shipped with this package
# (bt_mission_validator/schemas/mission_schema.xsd, built from all 5 of
# your sample mission files -- see "Regenerating the schema" below)
python3 -m bt_mission_validator.cli validate missions/*.xml

# CI-friendly: exit code is 0 iff every file passed (warnings don't fail the build)
python3 -m bt_mission_validator.cli validate --quiet missions/*.xml; echo "exit: $?"
```

Run the test suite:
```bash
python3 -m unittest discover -s tests -v
```

## Regenerating the schema

Whenever a node's ports change, or a new node type is introduced, rebuild
the canonical schema from whichever mission file(s) now have the correct
`<TreeNodesModel>` for it:

```bash
python -m bt_mission_validator.cli generate-schema missions/*.xml \
    -o bt_mission_validator/schemas/mission_schema.xsd
```

You can pass any number of mission files. Their `<TreeNodesModel>` blocks
are merged into one catalog (plus BT.CPP's built-in nodes: `Sequence`,
`Fallback`, `Repeat`, `SubTree`, etc.). If two files declare the *same*
node ID with *different* ports, that's reported as a conflict and the
command exits non-zero -- resolve it by hand (fix whichever file has the
stale model) and regenerate. This is exercised in
`tests/test_validator.py::TestSchemaGeneration::test_conflicting_port_definitions_are_reported`.

You don't have to point it at every mission file every time -- e.g. if
your team adopts a single canonical "node registry" file whose sole
purpose is a complete, correct `<TreeNodesModel>`, point `generate-schema`
at just that file. Multiple files are supported because your 5 samples
don't currently have one file with the full set.

## What `validate` checks

**Schema-level (against the checked-in `.xsd`):**
- Every node used in a tree body is either a BehaviorTree.CPP built-in
  (`Sequence`, `Fallback`, `Repeat`, `SubTree`, ...) or in the canonical
  schema's node catalog.
- Every attribute on a node is a declared port (or one of the handful of
  real BT.CPP metadata attributes: `name`, `_description`, `_autoremap`,
  the pre/post-condition script attributes) -- **unknown attributes are a
  hard error**, per your team's preference.
- Every port with no `default` is required and must be present.
- Decorators have exactly 1 child, Controls have >=1 (or the specific
  counts real BT.CPP built-ins require, e.g. `IfThenElse` needs 2-3),
  Actions/Conditions/SubTree have none.
- Port value *shape* is checked against its declared C++ type: `int`,
  `float`/`double`, `bool`, `string`, and (an addition described below)
  `std::vector<float>` / `std::vector<bool>` / `std::vector<int>`, or a
  blackboard reference like `{my_var}`.

**Semantic (Python, run after schema validation):**
- Every `<SubTree ID="X"/>` resolves to a `<BehaviorTree ID="X">` defined
  in the same file.
- `main_tree_to_execute` resolves to a real tree (or is unambiguous when
  there's only one tree).
- No duplicate `<BehaviorTree ID>`.
- *Warnings* (don't fail validation): a tree that's defined but never
  used; a vector-typed port whose length is inconsistent across its uses
  in the same file (a common copy-paste mistake); and -- since a mission
  file's own `<TreeNodesModel>` is Groot-facing metadata that this tool no
  longer treats as authoritative -- a warning if that local model has
  drifted from the canonical schema (declares a node/port the schema
  doesn't have, or vice versa), so stale Groot metadata doesn't go
  unnoticed even though it isn't a flight-safety issue on its own.

## Design decisions (as confirmed with the controls team)

1. **One canonical schema, checked in, never regenerated implicitly.**
   `validate` only ever reads `bt_mission_validator/schemas/mission_schema.xsd`
   (or whatever `--schema` you point it at) -- it does not parse or trust
   individual mission files' own `<TreeNodesModel>` for the pass/fail
   decision. `generate-schema` is the one explicit, separate command that
   writes that file, and you control exactly which mission file(s) feed it.

2. **The `.action` (ROS) files are still not wired into schema
   generation.** They don't map 1:1 to BT node names (e.g.
   `SeekObject.action` versus the `DriveToWorldWaypointSeeking` node), and
   a couple of their fields don't match what's declared as ports in the
   sample files. **Trade-off you're accepting:** if a `TreeNodesModel`
   block itself is wrong relative to the real C++ node registration, this
   tool won't catch that -- it only catches mission files that are
   inconsistent with whatever was last fed into `generate-schema`. If you
   want the `.action` files involved later, the mechanical path is to add
   a small loader that turns them into `NodeSpec`s (once someone confirms
   the name mapping) and feed those into `schema_build.build_master_schema`
   alongside the mission files.

3. **Unknown attributes / missing required ports are hard errors**, not
   warnings -- this falls directly out of using a closed-content-model XSD
   (no `xs:anyAttribute` except on `<SubTree>`, which needs it for port
   remapping).

## How this compares to BT.CPP's own schema generator

I cross-checked this against BehaviorTree.CPP's real source
(`src/xml_parsing.cpp`, `writeTreeXSD()` and `VerifyXML()`, master branch,
July 2026) rather than guessing at the XML format, and mirrored its
structure closely (same simple types, same attribute groups, same
per-node-type `complexType` generation). Two deliberate departures:

- **`_description` and `_autoremap` are added to the common attribute
  group.** BT.CPP's own generator omits them. In the real C++ parser
  they're silently accepted (any attribute starting with a non-letter
  character bypasses port validation), but the stock generated XSD doesn't
  model that -- run as-is, it would reject every node in your mission
  files, since all of them use `_description`. This is a genuine gap in
  BT.CPP's own tool, not a design choice on your end.
- **Vector ports get real regex validation** (`vectorFloatOrBlackboardType`,
  etc.) instead of being left unrestricted. BT.CPP's `xsdAttributeType()`
  only special-cases `int`/`double`/`bool`/`std::string`; anything else
  (including every `std::vector<float>` pose/mask/tolerance port in your
  files) gets no format check at all in the stock output.

## Project layout

```
bt_mission_validator/
  node_catalog.py       built-in BT.CPP node definitions + reserved attrs
  model_parser.py        reads/merges <TreeNodesModel> blocks from mission files
  schema_generator.py    builds the .xsd XML from a node catalog
  schema_build.py         ties model_parser + schema_generator together;
                           the ONLY code path that produces a schema
  schema_reader.py        reads an existing .xsd back into a node catalog
                           (used by `validate`, so it never regenerates)
  semantic_checks.py      SubTree/tree-ID/vector-length checks XSD can't do
  validator.py             validates one mission file against a given schema
  cli.py                    `generate-schema` and `validate` subcommands
  schemas/
    mission_schema.xsd      the canonical, checked-in schema (default)
missions/                 copies of your 5 sample mission files
tests/
  test_validator.py        17 automated tests: 6 on your real files
                            (incl. the DurationTrick regression), plus
                            schema-generation and negative-case tests
  fixtures/                 small synthetic XML files, one per test case
```

## Known limitations / good next steps

- No support for multi-file missions via `<include>` -- not needed for the
  files you provided (each is self-contained), but easy to add if that
  changes: `schema_build` would need to also resolve `<include>` when
  reading each source file's model.
- Vector length isn't checked against a fixed expected size (e.g. "must be
  exactly 6"), only checked for *consistency* within a file, since the
  `<TreeNodesModel>` type declarations (`std::vector<float>`) don't carry a
  length. If your team wants hard length enforcement, the port
  `description` text already has hints like `[6x1]` -- extracting and
  enforcing that is a small addition to `semantic_checks.py`.
- The `.action` files aren't used at all right now (see design decision
  #2 above).
