"""Check/fix six-slot VME capacity without changing the production unpacker."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "vme_lab_capacity", ROOT / "scripts/vme_lab_capacity.py")
capacity = importlib.util.module_from_spec(spec)
spec.loader.exec_module(capacity)
LAB = (ROOT / "unpack/exps/s100/s100_vme_tdc_lab.spec").read_text()
CONFIG = {"v1751": {"boards": [6, 7, 8, 9, 10]},
          "v1290": {"boards": [12, 13]}}


class FixedVMECapacityTests(unittest.TestCase):
    def test_six_slots_both_modules(self):
        repaired = capacity.repair(LAB, CONFIG)
        self.assertEqual(capacity.checked(repaired, CONFIG), [])
        self.assertEqual(capacity.declarations(repaired, capacity.QDC, "V1751"),
                         [(0, 6), (1, 7), (2, 8), (3, 9), (4, 10), (5, 31)])
        self.assertEqual(capacity.declarations(repaired, capacity.TDC, "V1290"),
                         [(0, 12), (1, 13), (2, 31), (3, 30), (4, 29), (5, 28)])
        self.assertEqual(capacity.repair(repaired, CONFIG), repaired)

    def test_missing_installed_geo_is_detected_then_repaired(self):
        enlarged = capacity.repair(LAB, CONFIG)
        changed_config = {"v1751": {"boards": [6, 7, 8, 9, 10]},
                          "v1290": {"boards": [12, 15]}}
        self.assertTrue(any("15" in line for line in capacity.checked(enlarged, changed_config)))
        changed = capacity.repair(enlarged, changed_config)
        self.assertEqual(capacity.checked(changed, changed_config), [])
        self.assertEqual(capacity.declarations(changed, capacity.TDC, "V1290")[0:2],
                         [(0, 12), (1, 15)])
        self.assertEqual(capacity.repair(changed, changed_config), changed)

    def test_missing_installed_qdc_id_detected_and_repaired(self):
        enlarged = capacity.repair(LAB, CONFIG)
        changed_config = {"v1751": {"boards": [6, 7, 8, 9, 14]},
                          "v1290": {"boards": [12, 13]}}
        self.assertTrue(capacity.checked(enlarged, changed_config))
        changed = capacity.repair(enlarged, changed_config)
        self.assertEqual(capacity.checked(changed, changed_config), [])
        self.assertEqual(len(capacity.declarations(changed, capacity.QDC, "V1751")), 6)

    def test_reject_illegal_and_duplicate_geo(self):
        with self.assertRaisesRegex(ValueError, "0..31"):
            capacity.addresses([32], "V1290")
        with self.assertRaisesRegex(ValueError, "duplicate"):
            capacity.addresses([12, 12], "V1290")
        with self.assertRaisesRegex(ValueError, "exceed"):
            capacity.addresses(list(range(7)), "V1290")

    def test_changes_are_local_to_vme_declarations(self):
        repaired = capacity.repair(LAB, CONFIG)
        self.assertEqual(repaired.count("SUBEVENT("), LAB.count("SUBEVENT("))
        self.assertEqual(repaired.count("error3 = ERR_WORD_SIX()"),
                         LAB.count("error3 = ERR_WORD_SIX()"))
        self.assertEqual(repaired.count("error2 = ERR_WORD_SIX()"),
                         LAB.count("error2 = ERR_WORD_SIX()"))
        self.assertIn("SUBEVENT(bplast_subev)", repaired)
        self.assertEqual(repaired[repaired.index("SUBEVENT(bplast_subev)"):],
                         LAB[LAB.index("SUBEVENT(bplast_subev)"):])


if __name__ == "__main__":
    unittest.main()
