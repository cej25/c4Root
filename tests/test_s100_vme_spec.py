"""Regression checks for the fixed FATIMA VME layout in the S100 spec."""

from contextlib import redirect_stdout
import io
from pathlib import Path
import re
import sys
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from validate_experiment import compiled_vme_slots, emit_whiterabbit, read_yaml

EXPERIMENT = ROOT / "unpack/exps/s100"
PRODUCTION = (EXPERIMENT / "s100.spec").read_text()
COMMON = ROOT / "unpack/common"
V1290 = (COMMON / "vme_caen_v1290_geo.spec").read_text()
CONFIG = ROOT / "config/s100/experiment.yaml"


class S100VmeSpecTests(unittest.TestCase):
    def test_hardware_addresses_stay_tied_to_numbered_output_slots(self):
        block = PRODUCTION.split("SUBEVENT(fatima_vme_subev)", 1)[1].split("SUBEVENT(", 1)[0]
        generated = io.StringIO()
        with redirect_stdout(generated):
            emit_whiterabbit(CONFIG, include_procids=True)
        config = read_yaml(CONFIG)["FATIMA_VME"]
        for model, symbol, bank, decoder, argument in (
            ("v1751", "S100_V1751_BANKS", "qdc", "VME_CAEN_V1751", "board"),
            ("v1290", "S100_V1290_BANKS", "tdc", "VME_CAEN_V1290_GEO", "geom_expected"),
        ):
            addresses = config[model]["compiled_slots"]
            self.assertEqual(block.count(symbol), 1)
            line = next(line for line in generated.getvalue().splitlines() if line.startswith(f"#define {symbol} "))
            slot_pattern = r"\[(\d+)\]" if model == "v1751" else r"(\d+)"
            actual = re.findall(rf"\b{bank}{slot_pattern}\s*=\s*{decoder}\({argument}\s*=\s*(\d+)\)", line)
            first_slot = 0 if model == "v1751" else 1
            self.assertEqual(actual, [(str(slot), str(address)) for slot, address in enumerate(addresses, first_slot)])
        for marker in ("error1", "error2", "error3"):
            self.assertEqual(block.count(f"{marker} = ERR_WORD_SIX()"), 1)
        self.assertIn("scalers = FATIMA_VME_SCALERS();", block)

    def test_compiled_addresses_keep_the_six_slot_abi_and_reserve_zero(self):
        config = read_yaml(CONFIG)["FATIMA_VME"]
        slots = config["v1290"]["compiled_slots"]
        config["v1290"]["boards"] = config["v1290"]["boards"][:1]
        self.assertEqual(compiled_vme_slots(config, "v1290"), slots)
        for invalid, message in ((slots[:-1], "exactly 6"), ([0] + slots[1:], "integers in 1–31"),
                                 ([slots[1]] + slots[1:], "duplicate compiled address")):
            with self.subTest(invalid=invalid):
                config["v1290"]["compiled_slots"] = invalid
                with self.assertRaisesRegex(ValueError, message):
                    compiled_vme_slots(config, "v1290")

    def test_v1751_matches_the_physical_id_before_selecting_the_bank(self):
        v1751 = (COMMON / "vme_caen_v1751.spec").read_text()
        self.assertIn('#include "../../common/vme_caen_v1751.spec"', PRODUCTION)
        self.assertNotIn("#if", v1751[:v1751.index("MATCH_END;")])
        self.assertLess(v1751.index("id = MATCH(board)"), v1751.index("MATCH_END;"))
        self.assertLess(v1751.index("MATCH_END;"), v1751.index("UINT32 board_agg_counter"))

    def test_fixed_geo_uses_the_legacy_v1290_payload(self):
        common = (COMMON / "vme_caen_v1x90.spec").read_text()
        original = common[common.index("VME_CAEN_V1290_N()"):common.index("VME_CAEN_V1190_N()")]
        fixed = V1290[V1290.index("VME_CAEN_V1290_GEO(geom_expected)"):]
        self.assertLess(fixed.index("MATCH(geom_expected)"), fixed.index("MATCH_END;"))
        self.assertLess(fixed.index("MATCH_END;"), fixed.index("select several"))
        legacy = fixed.replace("VME_CAEN_V1290_GEO(geom_expected)", "VME_CAEN_V1290_N()")
        legacy = legacy.replace("0_4: geom = MATCH(geom_expected);", "0_4: geom;")
        legacy = re.sub(r"\s*// Distinguish board GEO[^\n]*\n\s*MATCH_END;", "", legacy)
        self.assertEqual(legacy, original)


if __name__ == "__main__":
    unittest.main()
