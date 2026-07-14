"""
Test suite for bt_mission_validator.

Run with:
    cd bt_mission_validator
    python3 -m unittest discover -s tests -v
"""

import subprocess
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent.parent))

from bt_mission_validator.validator import validate_file, DEFAULT_SCHEMA_PATH
from bt_mission_validator.schema_build import build_master_schema

MISSIONS_DIR = Path(__file__).resolve().parent.parent / "missions"
FIXTURES_DIR = Path(__file__).resolve().parent / "fixtures"


def _schema_from(*fixture_paths, tmp_dir: Path) -> Path:
    """Build a schema from the given fixture file(s) (mirrors the real
    `generate-schema` step) and write it to a temp file, so each negative
    test exercises the same generate -> validate pipeline as production
    use, without depending on the real (unrelated) master schema."""
    build = build_master_schema(list(fixture_paths))
    out = tmp_dir / "test_schema.xsd"
    out.write_text(build.schema_xml)
    return out


class TestRealMissionFiles(unittest.TestCase):
    """Validate against the master schema shipped in the package (built
    from all 5 real mission files -- see bt_mission_validator/schemas/)."""

    def test_fallback_tree_passes(self):
        result = validate_file(MISSIONS_DIR / "Fallback_Tree.xml")
        self.assertTrue(result.ok, msg=[e.message for e in result.errors])

    def test_mission_file_passes_with_one_warning(self):
        result = validate_file(MISSIONS_DIR / "Mission_File.xml")
        self.assertTrue(result.ok, msg=[e.message for e in result.errors])
        self.assertTrue(any("Idle" in w.message for w in result.warnings))

    def test_station_keep_passes(self):
        result = validate_file(MISSIONS_DIR / "StationKeep.xml")
        self.assertTrue(result.ok, msg=[e.message for e in result.errors])

    def test_trial_dropper_mission_file_passes(self):
        result = validate_file(MISSIONS_DIR / "Trial_Dropper_Mission_File.xml")
        self.assertTrue(result.ok, msg=[e.message for e in result.errors])

    # def test_trial_mission_file_correctly_fails_on_undeclared_node(self):
    #     """DurationTrick is used in the tree body but never declared in any
    #     mission file's <TreeNodesModel> -- so it's absent from the master
    #     schema too. This is a real bug in the sample data, and the whole
    #     point of the tool is to catch exactly this before flight."""
    #     result = validate_file(MISSIONS_DIR / "Trial_Mission_File.xml")
    #     self.assertFalse(result.ok)
    #     self.assertTrue(
    #         any("DurationTrick" in e.message for e in result.errors),
    #         msg=[e.message for e in result.errors],
    #     )

    def test_default_schema_path_is_the_shipped_master_schema(self):
        self.assertTrue(DEFAULT_SCHEMA_PATH.exists())


class TestSchemaGeneration(unittest.TestCase):

    def setUp(self):
        self._tmp = tempfile.TemporaryDirectory()
        self.tmp_dir = Path(self._tmp.name)

    def tearDown(self):
        self._tmp.cleanup()

    def test_merging_all_real_mission_files_has_no_conflicts(self):
        build = build_master_schema(sorted(MISSIONS_DIR.glob("*.xml")))
        self.assertEqual(build.conflicts, [], msg=build.conflicts)
        # every custom node across the 5 files should show up exactly once
        self.assertIn("DriveToWorldWaypoint", build.all_nodes)
        self.assertIn("Dropper", build.all_nodes)
        self.assertIn("DistanceTrick", build.all_nodes)
        # DurationTrick is used by Trial_Mission_File.xml but was never
        # declared in ANY file's TreeNodesModel, so it correctly does NOT
        # appear in the merged catalog either.
        self.assertNotIn("DurationTrick", build.all_nodes)

    def test_generated_schema_is_well_formed_xml(self):
        from lxml import etree
        build = build_master_schema([MISSIONS_DIR / "Mission_File.xml"])
        etree.fromstring(build.schema_xml.encode("utf-8"))  # raises if malformed

    def test_conflicting_port_definitions_are_reported(self):
        conflict_a = FIXTURES_DIR / "conflict_a.xml"
        conflict_b = FIXTURES_DIR / "conflict_b.xml"
        build = build_master_schema([conflict_a, conflict_b])
        self.assertEqual(len(build.conflicts), 1)
        self.assertEqual(build.conflicts[0].node_id, "Dive")


class TestNegativeCases(unittest.TestCase):
    """Each fixture builds its OWN schema (mirroring the real generate ->
    validate workflow) and is then validated against it."""

    def setUp(self):
        self._tmp = tempfile.TemporaryDirectory()
        self.tmp_dir = Path(self._tmp.name)

    def tearDown(self):
        self._tmp.cleanup()

    def test_undeclared_attribute_rejected(self):
        fixture = FIXTURES_DIR / "bad_attribute.xml"
        schema = _schema_from(fixture, tmp_dir=self.tmp_dir)
        result = validate_file(fixture, schema_path=schema)
        self.assertFalse(result.ok)
        self.assertTrue(any("speeed" in e.message for e in result.errors))

    def test_missing_required_port_rejected(self):
        fixture = FIXTURES_DIR / "missing_required_port.xml"
        schema = _schema_from(fixture, tmp_dir=self.tmp_dir)
        result = validate_file(fixture, schema_path=schema)
        self.assertFalse(result.ok)
        self.assertTrue(any("timeout" in e.message for e in result.errors))

    def test_malformed_vector_value_rejected(self):
        fixture = FIXTURES_DIR / "bad_vector_format.xml"
        schema = _schema_from(fixture, tmp_dir=self.tmp_dir)
        result = validate_file(fixture, schema_path=schema)
        self.assertFalse(result.ok)
        self.assertTrue(any("waypoint" in e.message for e in result.errors))

    def test_dangling_subtree_reference_rejected(self):
        fixture = FIXTURES_DIR / "dangling_subtree.xml"
        schema = _schema_from(fixture, tmp_dir=self.tmp_dir)
        result = validate_file(fixture, schema_path=schema)
        self.assertFalse(result.ok)
        self.assertTrue(any("DoesNotExist" in e.message for e in result.errors))

    def test_duplicate_behaviortree_id_rejected(self):
        fixture = FIXTURES_DIR / "duplicate_tree_id.xml"
        schema = _schema_from(fixture, tmp_dir=self.tmp_dir)
        result = validate_file(fixture, schema_path=schema)
        self.assertFalse(result.ok)
        self.assertTrue(any("Duplicate" in e.message for e in result.errors))

    def test_inconsistent_vector_length_warns_but_does_not_fail(self):
        fixture = FIXTURES_DIR / "inconsistent_vector_length.xml"
        schema = _schema_from(fixture, tmp_dir=self.tmp_dir)
        result = validate_file(fixture, schema_path=schema)
        self.assertTrue(result.ok)  # this is a warning, not an error
        self.assertTrue(any("inconsistent vector length" in w.message for w in result.warnings))

    def test_missing_schema_file_is_a_clean_error_not_a_crash(self):
        fixture = FIXTURES_DIR / "bad_attribute.xml"
        result = validate_file(fixture, schema_path=self.tmp_dir / "does_not_exist.xsd")
        self.assertFalse(result.ok)
        self.assertTrue(any("not found" in e.message for e in result.errors))


class TestLocalModelDriftWarning(unittest.TestCase):
    """A mission file's own <TreeNodesModel> can drift from the master
    schema (e.g. someone hand-edits Groot metadata) -- this should warn,
    not fail, since the master schema is what actually governs validity."""

    def setUp(self):
        self._tmp = tempfile.TemporaryDirectory()
        self.tmp_dir = Path(self._tmp.name)

    def tearDown(self):
        self._tmp.cleanup()

    def test_stale_local_model_warns(self):
        stale = FIXTURES_DIR / "stale_local_model.xml"
        canonical = FIXTURES_DIR / "stale_local_model_canonical.xml"
        schema = _schema_from(canonical, tmp_dir=self.tmp_dir)
        result = validate_file(stale, schema_path=schema)
        self.assertTrue(result.ok)
        self.assertTrue(any("stale" in w.message.lower() for w in result.warnings))


class TestCliOutput(unittest.TestCase):
    """The CLI should always say explicitly whether there were errors/
    warnings, never just silently print nothing for the zero-findings case."""

    def _run_cli(self, *args):
        return subprocess.run(
            [sys.executable, "-m", "bt_mission_validator.cli", *args],
            cwd=str(Path(__file__).resolve().parent.parent),
            capture_output=True, text=True,
        )

    def test_passing_file_explicitly_states_no_errors_and_no_warnings(self):
        proc = self._run_cli("validate", "missions/Fallback_Tree.xml")
        self.assertEqual(proc.returncode, 0)
        self.assertIn("No errors.", proc.stdout)
        self.assertIn("No warnings.", proc.stdout)

    def test_failing_file_lists_every_error_and_still_states_no_warnings(self):
        proc = self._run_cli("validate", "missions/Trial_Mission_File.xml")
        self.assertEqual(proc.returncode, 1)
        self.assertIn("[ERROR]", proc.stdout)
        self.assertIn("DurationTrick", proc.stdout)
        self.assertIn("No warnings.", proc.stdout)

    def test_quiet_mode_suppresses_the_explicit_lines(self):
        proc = self._run_cli("validate", "--quiet", "missions/Fallback_Tree.xml")
        self.assertEqual(proc.returncode, 0)
        self.assertNotIn("No errors.", proc.stdout)


if __name__ == "__main__":
    unittest.main()
