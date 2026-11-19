"""Synthetic regression checks for FATIMA VME UCESB dump comparison."""
import importlib.util
from pathlib import Path
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "compare_fatima_vme_dumps", ROOT / "scripts/compare_fatima_vme_dumps.py")
compare = importlib.util.module_from_spec(spec)
spec.loader.exec_module(compare)


class DumpComparisonTests(unittest.TestCase):
    def parse(self, content, normalise=False):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "dump.txt"
            path.write_text(content)
            return compare.parse(path, normalise)

    def test_same_values_after_qdc_rename(self):
        base = ("Event 1 Trigger 1\n"
                ".UNPACK.fatimavme.qdc1.board_id: 0x06=6\n"
                ".UNPACK.fatimavme.qdc2.qshort[0]: 0x03=3\n"
                ".UNPACK.fatimavme.tdc1.geo: 0x0d=13\n"
                "Event 2 Trigger 1\n")
        lab = base.replace("qdc1", "qdc[0]").replace("qdc2", "qdc[1]")
        errors, n, vme = compare.compare(self.parse(base, True), self.parse(lab))
        self.assertEqual(errors, [])
        self.assertEqual((n, vme), (3, 1))

    def test_changed_charge_fails(self):
        a = self.parse("Event 1 Trigger 1\n.UNPACK.fatimavme.qdc1.qshort[0]: 5\n", True)
        b = self.parse("Event 1 Trigger 1\n.UNPACK.fatimavme.qdc[0].qshort[0]: 6\n")
        self.assertTrue(compare.compare(a, b)[0])

    def test_missing_field_fails(self):
        a = self.parse("Event 1 Trigger 1\n.UNPACK.fatimavme.qdc1.board_id: 6\n", True)
        b = self.parse("Event 1 Trigger 1\n")
        self.assertTrue(compare.compare(a, b)[0])

    def test_no_vme_fields_is_not_success(self):
        a = self.parse("Event 1 Trigger 1\n")
        self.assertTrue(compare.compare(a, a)[0])

    def test_missing_event_fails(self):
        a = self.parse("Event 1 Trigger 1\nEvent 2 Trigger 1\n")
        b = self.parse("Event 1 Trigger 1\n")
        self.assertTrue(compare.compare(a, b)[0])


if __name__ == "__main__":
    unittest.main()
