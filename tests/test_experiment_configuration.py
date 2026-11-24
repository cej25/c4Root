"""Experiment routing, generated layouts and native header synchronisation."""

import io
import re
import sys
import tempfile
import unittest
from contextlib import redirect_stdout
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))

import sync_experiment as synchronizer
import validate_experiment as validator

S100_SPEC = ROOT / "unpack/exps/s100/s100.spec"
S100_CONFIG = ROOT / "config/s100/experiment.yaml"
COMMON = ROOT / "unpack/common"


class ExperimentValidationTests(unittest.TestCase):
    def test_s181_indexed_qdc_slots_preserve_the_board_order(self):
        spec = (ROOT / "unpack/exps/s181/s181.spec").read_text()
        route = validator.spec_inventory(spec)["fatimavme"]
        self.assertEqual(route["v1751"]["compiled_slots"], [6, 7, 8, 9, 10, 31])
        self.assertEqual(validator.validate("s181", ROOT), ([], []))

    def test_yaml_generates_current_and_edited_white_rabbit_ids(self):
        config = (S100_CONFIG).read_text()
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "experiment.yaml"
            path.write_text(config.replace("whiterabbit: 0x500", "whiterabbit: 0x1abc"))
            output = io.StringIO()
            with redirect_stdout(output):
                validator.emit_whiterabbit(path)
            self.assertIn("#define S100_WR_BPLAST 0x1abc\n", output.getvalue())
            self.assertIn("#define S100_WR_FATIMA 0x1600\n", output.getvalue())
            self.assertEqual(output.getvalue().count("#define S100_WR_"), 8)

            path.write_text(config.replace("whiterabbit: 0x500", "whiterabbit: 0x2000"))
            with self.assertRaisesRegex(ValueError, "bPlast: whiterabbit"):
                validator.emit_whiterabbit(path)
            path.write_text(config.replace("  whiterabbit: 0x500\n", ""))
            with self.assertRaisesRegex(ValueError, "Missing White Rabbit IDs for bplast"):
                validator.emit_whiterabbit(path)

    def test_s100_procid_constants_include_all_event_members(self):
        config = (S100_CONFIG).read_text()
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "experiment.yaml"
            path.write_text(config.replace("procid: 75", "procid: 175"))
            output = io.StringIO()
            with redirect_stdout(output):
                validator.emit_whiterabbit(path, include_procids=True)
            self.assertIn("#define S100_PROCID_FATIMA 175\n", output.getvalue())
            self.assertIn("#define S100_PROCID_FRSTPC 20\n", output.getvalue())
            self.assertIn("#define S100_WR_FATIMA 0x1600\n", output.getvalue())
            self.assertEqual(output.getvalue().count("#define S100_PROCID_"), 11)

    def test_s100_degas_cards_are_generated_in_slot_order(self):
        output = io.StringIO()
        with redirect_stdout(output):
            validator.emit_whiterabbit(S100_CONFIG, include_procids=True)
        cards = next(line for line in output.getvalue().splitlines() if line.startswith("#define S100_DEGAS_CARDS "))
        self.assertEqual(validator.FEBEX.findall(cards), [(str(slot), "", str(slot)) for slot in range(6)])

    def test_s100_rejects_invalid_and_duplicate_procids(self):
        config = validator.read_yaml(S100_CONFIG)
        for invalid in (-1, 65536, True):
            with self.subTest(invalid=invalid):
                config["FATIMA"]["procid"] = invalid
                with self.assertRaisesRegex(ValueError, "FATIMA: procid must be"):
                    validator.s100_routes(config)
        config["FATIMA"]["procid"] = 20
        with self.assertRaisesRegex(ValueError, "FRS_TPC: procid 20 duplicates FATIMA"):
            validator.s100_routes(config)
        del config["FATIMA"]["procid"]
        with self.assertRaisesRegex(ValueError, "FATIMA: procid must be"):
            validator.s100_routes(config)

    def test_s100_detects_hardcoded_procid(self):
        config = validator.read_yaml(S100_CONFIG)
        spec = S100_SPEC.read_text()
        warnings = validator.check_s100_routing(spec.replace("S100_PROCID_FATIMA,", "75,"), config)
        self.assertEqual(warnings, ["FATIMA: UCESB EVENT must use S100_PROCID_FATIMA"])

    def test_limits(self):
        self.assertEqual(validator.MAX_BOARDS, {"tamex": 12, "v1751": 6, "v1290": 6})
        self.assertEqual(len(validator.board_list(list(range(12)), "TAMEX", 12)), 12)
        with self.assertRaisesRegex(ValueError, "exceeds"):
            validator.board_list(list(range(13)), "TAMEX", 12)
        with self.assertRaisesRegex(ValueError, "duplicate"):
            validator.board_list([0, 1, 1], "V1751", 6)

    def test_missing_physical_tamex_address_detected(self):
        original = validator.read_yaml
        def missing_card(path):
            config = original(path)
            config["FATIMA"]["compiled_slots"][3] = [0, 8]
            return config
        with patch.object(validator, "read_yaml", missing_card):
            warnings, _ = validator.validate("s100", ROOT)
        self.assertTrue(any("TAMEX hardware addresses unsupported" in warning
                            for warning in warnings))

    def test_missing_v1751_address_detected(self):
        original = validator.read_yaml
        def missing_board(path):
            config = original(path)
            v1751 = config["FATIMA_VME"]["v1751"]
            slots = v1751["compiled_slots"]
            missing = v1751["boards"][0]
            slots[slots.index(missing)] = next(address for address in range(1, 32) if address not in slots)
            return config
        with patch.object(validator, "read_yaml", missing_board):
            warnings, _ = validator.validate("s100", ROOT)
        self.assertTrue(any("V1751: unsupported board addresses" in warning
                            for warning in warnings))


class S100VmeSpecTests(unittest.TestCase):
    def test_hardware_addresses_stay_tied_to_numbered_output_slots(self):
        block = S100_SPEC.read_text().split("SUBEVENT(fatima_vme_subev)", 1)[1].split("SUBEVENT(", 1)[0]
        generated = io.StringIO()
        with redirect_stdout(generated):
            validator.emit_whiterabbit(S100_CONFIG, include_procids=True)
        config = validator.read_yaml(S100_CONFIG)["FATIMA_VME"]
        for model, symbol, bank, decoder, argument in (
            ("v1751", "S100_V1751_BANKS", "qdc", "VME_CAEN_V1751", "board"),
            ("v1290", "S100_V1290_BANKS", "tdc", "VME_CAEN_V1290_GEO", "geom_expected"),
        ):
            addresses = config[model]["compiled_slots"]
            line = next(line for line in generated.getvalue().splitlines() if line.startswith(f"#define {symbol} "))
            slot_pattern = r"\[(\d+)\]" if model == "v1751" else r"(\d+)"
            actual = re.findall(rf"\b{bank}{slot_pattern}\s*=\s*{decoder}\({argument}\s*=\s*(\d+)\)", line)
            first_slot = 0 if model == "v1751" else 1
            self.assertEqual(actual, [(str(slot), str(address)) for slot, address in enumerate(addresses, first_slot)])
        for marker in ("error1", "error2", "error3"):
            self.assertEqual(block.count(f"{marker} = ERR_WORD_SIX()"), 1)
        self.assertIn("scalers = FATIMA_VME_SCALERS();", block)

    def test_compiled_addresses_keep_the_six_slot_abi_and_reserve_zero(self):
        config = validator.read_yaml(S100_CONFIG)["FATIMA_VME"]
        slots = config["v1290"]["compiled_slots"]
        config["v1290"]["boards"] = config["v1290"]["boards"][:1]
        self.assertEqual(validator.compiled_vme_slots(config, "v1290"), slots)
        for invalid, message in ((slots[:-1], "exactly 6"), ([0] + slots[1:], "integers in 1–31"),
                                 ([slots[1]] + slots[1:], "duplicate compiled address")):
            with self.subTest(invalid=invalid):
                config["v1290"]["compiled_slots"] = invalid
                with self.assertRaisesRegex(ValueError, message):
                    validator.compiled_vme_slots(config, "v1290")

    def test_v1751_matches_the_physical_id_before_selecting_the_bank(self):
        v1751 = (COMMON / "vme_caen_v1751.spec").read_text()
        self.assertIn('#include "../../common/vme_caen_v1751.spec"', S100_SPEC.read_text())
        self.assertNotIn("#if", v1751[:v1751.index("MATCH_END;")])
        self.assertLess(v1751.index("id = MATCH(board)"), v1751.index("MATCH_END;"))
        self.assertLess(v1751.index("MATCH_END;"), v1751.index("UINT32 board_agg_counter"))

    def test_v1290_matches_geo_before_accepting_the_bank(self):
        spec = (COMMON / "vme_caen_v1290_geo.spec").read_text()
        fixed = spec[spec.index("VME_CAEN_V1290_GEO(geom_expected)"):]
        self.assertLess(fixed.index("MATCH(geom_expected)"), fixed.index("MATCH_END;"))
        self.assertLess(fixed.index("MATCH_END;"), fixed.index("select several"))


class SyncExperimentTests(unittest.TestCase):
    def test_installed_subset_does_not_change_compiled_layout(self):
        config = validator.read_yaml(S100_CONFIG)
        original = synchronizer.installed_layouts(config)
        config["FATIMA"]["boards"] = [1, 3]
        self.assertEqual(synchronizer.installed_layouts(config), original)
        self.assertEqual(synchronizer.stale_headers(original), {})

    def test_compiled_order_and_addresses_drive_generation(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "experiment.yaml"
            yaml = (S100_CONFIG).read_text()
            path.write_text(yaml.replace("[[0, 0], [0, 1], [0, 2], [0, 3]]",
                                         "[[1, 9], [0, 1], [0, 2], [0, 3], [0, 0]]", 1))
            output = io.StringIO()
            with redirect_stdout(output):
                validator.emit_whiterabbit(path, include_procids=True)
            fatima = next(line for line in output.getvalue().splitlines()
                          if line.startswith("#define S100_TAMEX_CARDS_FATIMA "))
            self.assertIn("tamex[0] = TAMEX4_SFP(sfp = 1, card = 9);", fatima)
            self.assertIn("tamex[4] = TAMEX4_SFP(sfp = 0, card = 0);", fatima)
            layouts = synchronizer.installed_layouts(validator.read_yaml(path))
            self.assertEqual(set(synchronizer.stale_headers(layouts)), {"fatima"})

    def test_generated_header_is_installed_byte_for_byte(self):
        generated = (b"typedef struct { struct { unsigned entry; } fatima_tamex[1]; } "
                     b"EXT_STR_h101_fatima_onion;\r\n/* Native layout table */\r\n")
        with tempfile.TemporaryDirectory() as folder:
            target = Path(folder) / "ext_h101_fatima.h"

            def generate(command, cwd, check):
                (Path(cwd) / target.name).write_bytes(generated)

            with patch("sync_experiment.subprocess.run", generate), patch("sync_experiment.ROOT", Path(folder)):
                synchronizer.regenerate_headers({"fatima": [(0, 0)]}, {"fatima": target})

            self.assertEqual(target.read_bytes(), generated)

    def test_bad_or_uncompiled_addresses_are_rejected(self):
        config = validator.read_yaml(S100_CONFIG)
        config["FATIMA"]["boards"] = [0, 1, 2, 9]
        with self.assertRaisesRegex(ValueError, "FATIMA: add unsupported installed addresses"):
            synchronizer.installed_layouts(config)
        config["FATIMA"]["compiled_slots"].append([0, 0])
        with self.assertRaisesRegex(ValueError, "duplicate compiled TAMEX address"):
            synchronizer.installed_layouts(config)
        config["FATIMA"]["compiled_slots"][-1] = [16, 9]
        with self.assertRaisesRegex(ValueError, "SFP 0–15"):
            synchronizer.installed_layouts(config)


if __name__ == "__main__":
    unittest.main()
