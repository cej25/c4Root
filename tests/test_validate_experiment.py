"""Tests of capacity-based experiment validation (no UCESB runtime required)."""
import importlib.util
import io
import tempfile
import unittest
from contextlib import redirect_stdout
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
        self.assertTrue(any("FATIMA_VME/v1751" in note for note in notes))
        self.assertTrue(any("FATIMA_VME/v1290" in note for note in notes))

    def test_yaml_generates_current_and_edited_white_rabbit_ids(self):
        config = (ROOT / "config/s100/experiment.yaml").read_text()
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "experiment.yaml"
            path.write_text(config.replace("whiterabbit: 0x500", "whiterabbit: 0x1abc"))
            output = io.StringIO()
            with redirect_stdout(output):
                module.emit_whiterabbit(path)
            self.assertIn("#define S100_WR_BPLAST 0x1abc\n", output.getvalue())
            self.assertIn("#define S100_WR_FATIMA 0x1600\n", output.getvalue())
            self.assertEqual(output.getvalue().count("#define S100_WR_"), 8)

            path.write_text(config.replace("whiterabbit: 0x500", "whiterabbit: 0x2000"))
            with self.assertRaisesRegex(ValueError, "bPlast: whiterabbit"):
                module.emit_whiterabbit(path)
            path.write_text(config.replace("  whiterabbit: 0x500\n", ""))
            with self.assertRaisesRegex(ValueError, "Missing White Rabbit IDs for bplast"):
                module.emit_whiterabbit(path)

    def test_s100_procid_constants_include_all_event_members(self):
        config = (ROOT / "config/s100/experiment.yaml").read_text()
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "experiment.yaml"
            path.write_text(config.replace("procid: 75", "procid: 175"))
            output = io.StringIO()
            with redirect_stdout(output):
                module.emit_whiterabbit(path, include_procids=True)
            self.assertIn("#define S100_PROCID_FATIMA 175\n", output.getvalue())
            self.assertIn("#define S100_PROCID_FRSTPC 20\n", output.getvalue())
            self.assertIn("#define S100_WR_FATIMA 0x1600\n", output.getvalue())
            self.assertEqual(output.getvalue().count("#define S100_PROCID_"), 11)

    def test_s100_rejects_invalid_and_duplicate_procids(self):
        config = module.read_yaml(ROOT / "config/s100/experiment.yaml")
        for invalid in (-1, 65536, True):
            with self.subTest(invalid=invalid):
                config["FATIMA"]["procid"] = invalid
                with self.assertRaisesRegex(ValueError, "FATIMA: procid must be"):
                    module.s100_routes(config)
        config["FATIMA"]["procid"] = 20
        with self.assertRaisesRegex(ValueError, "FRS_TPC: procid 20 duplicates FATIMA"):
            module.s100_routes(config)
        del config["FATIMA"]["procid"]
        with self.assertRaisesRegex(ValueError, "FATIMA: procid must be"):
            module.s100_routes(config)

    def test_s100_detects_hardcoded_procid(self):
        config = module.read_yaml(ROOT / "config/s100/experiment.yaml")
        spec = (ROOT / "unpack/exps/s100/s100.spec").read_text()
        warnings = module.check_s100_routing(spec.replace("S100_PROCID_FATIMA,", "75,"), config)
        self.assertEqual(warnings, ["FATIMA: UCESB EVENT must use S100_PROCID_FATIMA"])

    def test_limits(self):
        self.assertEqual(module.MAX_BOARDS, {"tamex": 12, "v1751": 6, "v1290": 6})
        self.assertEqual(len(module.board_list(list(range(12)), "TAMEX", 12)), 12)
        with self.assertRaisesRegex(ValueError, "exceeds"):
            module.board_list(list(range(13)), "TAMEX", 12)
        with self.assertRaisesRegex(ValueError, "duplicate"):
            module.board_list([0, 1, 1], "V1751", 6)

    def test_missing_physical_tamex_address_detected(self):
        original = module.read_yaml
        def missing_card(path):
            config = original(path)
            config["FATIMA"]["compiled_slots"][3] = [0, 8]
            return config
        with patch.object(module, "read_yaml", missing_card):
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
