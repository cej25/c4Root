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

    def test_fail_on_duplicate_geo(self):
        with self.assertRaisesRegex(ValueError, "Duplicate active GEO"):
            geo.canonical([("tdc[0].geo", "0x0d=13"),
                           ("tdc[1].geo", "0x0d=13")])


if __name__ == "__main__":
    unittest.main()
