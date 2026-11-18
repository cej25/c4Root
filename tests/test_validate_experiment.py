"""Tests of capacity-based experiment validation (no UCESB runtime required)."""
import importlib.util
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
SPEC = importlib.util.spec_from_file_location("validate_experiment", ROOT / "scripts/validate_experiment.py")
module = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(module)


class ExperimentValidationTests(unittest.TestCase):
    def test_s100_installed_hardware_is_supported(self):
        warnings, notes = module.validate("s100", ROOT)
        self.assertEqual(warnings, [])
        self.assertTrue(any("FATIMA/v1751" in note for note in notes))
        self.assertTrue(any("FATIMA/v1290" in note for note in notes))

    def test_limits(self):
        self.assertEqual(module.MAX_BOARDS, {"tamex": 12, "v1751": 6, "v1290": 6})
        self.assertEqual(len(module.board_list(list(range(12)), "TAMEX", 12)), 12)
        with self.assertRaisesRegex(ValueError, "exceeds"):
            module.board_list(list(range(13)), "TAMEX", 12)
        with self.assertRaisesRegex(ValueError, "duplicate"):
            module.board_list([0, 1, 1], "V1751", 6)

    def test_missing_physical_tamex_address_detected(self):
        original = module.read_subevent
        def missing_card(spec, name):
            body = original(spec, name)
            if name == "fatima_tamex_subev":
                return body.replace("card = 3", "card = 8")
            return body
        with patch.object(module, "read_subevent", missing_card):
            warnings, _ = module.validate("s100", ROOT)
        self.assertTrue(any("TAMEX hardware addresses unsupported" in warning
                            for warning in warnings))

    def test_missing_v1751_address_detected(self):
        original = module.read_subevent
        def missing_board(spec, name):
            body = original(spec, name)
            if name == "fatima_vme_subev":
                return body.replace("board=10", "board=11")
            return body
        with patch.object(module, "read_subevent", missing_board):
            warnings, _ = module.validate("s100", ROOT)
        self.assertTrue(any("V1751: unsupported board addresses" in warning
                            for warning in warnings))


if __name__ == "__main__":
    unittest.main()
