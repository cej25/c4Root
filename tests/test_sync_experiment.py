"""Focused checks for the opt-in s100 UCESB synchroniser (no UCESB needed)."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
SCRIPT = ROOT / "scripts" / "sync_experiment.py"
spec = importlib.util.spec_from_file_location("sync_experiment", SCRIPT)
sync = importlib.util.module_from_spec(spec)
spec.loader.exec_module(sync)

CONFIG = {
    "FATIMA": {"digitiser": "tamex", "version": 4, "procid": 75,
               "whiterabbit": 0x1600, "sfp": 0, "boards": [0, 1, 2, 3]},
    "bPlast": {"digitiser": "tamex", "version": 4, "procid": 80,
               "whiterabbit": 0x500, "sfp": 0, "boards": list(range(9))},
    "BGO": {"digitiser": "tamex", "version": 4, "procid": 100,
            "whiterabbit": 0x1900, "sfp": 1, "boards": [0, 1, 2]},
}


class SyncExperimentTests(unittest.TestCase):
    def setUp(self):
        self.source = sync.SPEC.read_text()

    def test_current_layout_is_stable(self):
        self.assertEqual(sync.regenerate_declarations(self.source, CONFIG), self.source)

    def test_add_two_fatima_boards_without_touching_other_subevents(self):
        config = {key: dict(value) for key, value in CONFIG.items()}
        config["FATIMA"]["boards"] = [0, 1, 2, 3, 4, 5]
        changed = sync.regenerate_declarations(self.source, config)
        self.assertIn("tamex[5] = TAMEX4_SFP(sfp = 0, card = 5);", changed)
        a, b, _ = sync.subevent(self.source, "bplast_subev")
        x, y, _ = sync.subevent(changed, "bplast_subev")
        self.assertEqual(self.source[a:b], changed[x:y])

    def test_detect_changed_sfp(self):
        config = {key: dict(value) for key, value in CONFIG.items()}
        config["BGO"]["sfp"] = 2
        changed = sync.regenerate_declarations(self.source, config)
        self.assertIn("TAMEX4_SFP(sfp = 2, card = 0)", changed)
        self.assertEqual(sync.regenerate_declarations(changed, config), changed)

    def test_refuse_proc_id_mismatch(self):
        config = {key: dict(value) for key, value in CONFIG.items()}
        config["FATIMA"]["procid"] = 999
        with self.assertRaisesRegex(ValueError, "procid"):
            sync.regenerate_declarations(self.source, config)

    def test_refuse_white_rabbit_mismatch(self):
        config = {key: dict(value) for key, value in CONFIG.items()}
        config["FATIMA"]["whiterabbit"] = 0x999
        with self.assertRaisesRegex(ValueError, "White Rabbit"):
            sync.regenerate_declarations(self.source, config)

    def test_vme_capacity_expansion_is_idempotent(self):
        enlarged = sync.expand_vme_capacity(self.source, {
            "FATIMA_VME": {
                "v1751": {"boards": [6, 7, 8, 9, 10]},
                "v1290": {"boards": [12, 13]},
            }
        })
        self.assertIn("qdc6 = VME_CAEN_V1751(board=11)", enlarged)
        self.assertIn("tdc6 = VME_CAEN_V1290_N()", enlarged)
        self.assertEqual(sync.expand_vme_capacity(enlarged, {
            "FATIMA_VME": {
                "v1751": {"boards": [6, 7, 8, 9, 10]},
                "v1290": {"boards": [12, 13]},
            }
        }), enlarged)

    def test_tamex_standard_capacity_target_is_twelve(self):
        proposed = sync.target_capacity_config(CONFIG)
        self.assertEqual(len(proposed["FATIMA"]["boards"]), 12)
        self.assertEqual(len(proposed["bPlast"]["boards"]), 12)
        self.assertEqual(len(proposed["BGO"]["boards"]), 12)
        expanded = sync.regenerate_declarations(self.source, proposed)
        self.assertIn("tamex[11] = TAMEX4_SFP(sfp = 0, card = 11);", expanded)

    def test_committed_header_board_dimensions(self):
        self.assertEqual(sync.stale_headers(CONFIG), [])


if __name__ == "__main__":
    unittest.main()
