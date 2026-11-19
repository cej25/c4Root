"""Unit tests for physical-GEO comparison of V1290 banks."""
import importlib.util
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location(
    "compare_fatima_vme_geo_dumps", ROOT / "scripts/compare_fatima_vme_geo_dumps.py")
geo = importlib.util.module_from_spec(spec)
spec.loader.exec_module(geo)


class GeoComparisons(unittest.TestCase):
    def test_index_independence_and_empty_spares(self):
        a = [("qdc[0].board", "0x06=6"),
             ("tdc1.geo", "0x0d=13"),
             ("tdc1.measurement.data[1]", "0x64=100"),
             ("tdc2.geo", "0x00=0")]
        b = [("qdc[0].board", "0x06=6"),
             ("tdc[0].geo", "0x00=0"),
             ("tdc[1].geo", "0x0d=13"),
             ("tdc[1].measurement.data[1]", "0x64=100"),
             ("tdc[2].geo", "0x00=0")]
        self.assertEqual(geo.canonical(a), geo.canonical(b))

    def test_zero_qdc_reserve_is_ignored(self):
        base = [("qdc[0].board_id", "0x06=6"), ("scalers.data[0]", "0x10=16")]
        padded = base + [
            ("qdc[5].board_id", "0x00=0"),
            ("qdc[5].board_time", "0x00000000=0"),
            ("qdc[5].channels", "0x00=0"),
            ("qdc[5].dm", "0x0000=0"),
            ("qdc[5].extras", "0x0000=0"),
        ]
        self.assertEqual(geo.canonical(base), geo.canonical(padded))

    def test_nonempty_spare_qdc_is_not_ignored(self):
        spare = [
            ("qdc[5].board_id", "0x00=0"),
            ("qdc[5].board_time", "0x00000000=0"),
            ("qdc[5].channels", "0x00=0"),
            ("qdc[5].dm", "0x0000=0"),
            ("qdc[5].extras", "0x0000=0"),
        ]
        with self.assertRaisesRegex(ValueError, "not empty"):
            geo.canonical(spare + [("qdc[5].qshort[0]", "0x0001=1")])
        with self.assertRaisesRegex(ValueError, "not empty"):
            geo.canonical([("qdc[5].board_id", "0x0b=11")] + spare[1:])

    def test_incomplete_spare_qdc_is_not_ignored(self):
        with self.assertRaisesRegex(ValueError, "missing expected fields"):
            geo.canonical([("qdc[5].board_id", "0x00=0")])

    def test_changed_measurement_detected(self):
        with tempfile.TemporaryDirectory() as tmp:
            a, b = Path(tmp) / "a", Path(tmp) / "b"
            a.write_text("Event 1 Trigger 1\n.UNPACK.fatimavme.tdc1.geo: 0x0d=13\n"
                         ".UNPACK.fatimavme.tdc1.measurement.data[1]: 0x64=100\n")
            b.write_text("Event 1 Trigger 1\n.UNPACK.fatimavme.tdc[1].geo: 0x0d=13\n"
                         ".UNPACK.fatimavme.tdc[1].measurement.data[1]: 0x65=101\n")
            self.assertTrue(geo.compare(a, b)[0])

    def test_fail_on_active_zero_geo(self):
        with self.assertRaisesRegex(ValueError, "GEO=0"):
            geo.canonical([("tdc[2].geo", "0x00=0"),
                           ("tdc[2].measurement.data[1]", "0x22=34")])

    def test_repeated_measurements_retain_their_order(self):
        fields = [("tdc1.geo", "0x0d=13"),
                  ("tdc1.measurement.data", "0x64=100"),
                  ("tdc1.measurement.data", "0x65=101")]
        self.assertNotEqual(geo.canonical(fields), geo.canonical([fields[0], fields[2], fields[1]]))

    def test_fail_on_duplicate_geo(self):
        with self.assertRaisesRegex(ValueError, "Duplicate active GEO"):
            geo.canonical([("tdc[0].geo", "0x0d=13"),
                           ("tdc[1].geo", "0x0d=13")])


if __name__ == "__main__":
    unittest.main()
