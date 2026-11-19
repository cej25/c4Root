"""Regression checks for the fixed FATIMA VME layout in the S100 spec."""

from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
EXPERIMENT = ROOT / "unpack/exps/s100"
PRODUCTION = (EXPERIMENT / "s100.spec").read_text()
V1290 = (EXPERIMENT / "vme_caen_v1290_geo.spec").read_text()
COMMON = ROOT / "unpack/common"


class S100VmeSpecTests(unittest.TestCase):
    def test_hardware_addresses_stay_tied_to_numbered_output_slots(self):
        block = PRODUCTION.split("SUBEVENT(fatima_vme_subev)", 1)[1].split("SUBEVENT(", 1)[0]
        for bank, decoder, argument, addresses in (
            ("qdc", "VME_CAEN_V1751", "board", [6, 7, 8, 9, 10, 31]),
            ("tdc", "VME_CAEN_V1290_GEO", "geom_expected", [12, 13, 31, 30, 29, 28]),
        ):
            actual = re.findall(rf"\b{bank}(\d+)\s*=\s*{decoder}\({argument}\s*=\s*(\d+)\)", block)
            self.assertEqual(actual, [(str(slot), str(address)) for slot, address in enumerate(addresses, 1)])
        for marker in ("error1", "error2", "error3"):
            self.assertEqual(block.count(f"{marker} = ERR_WORD_SIX()"), 1)
        self.assertIn("scalers = FATIMA_VME_SCALERS();", block)

    def test_v1751_matches_the_physical_id_before_selecting_the_bank(self):
        v1751 = (COMMON / "vme_caen_v1751.spec").read_text()
        self.assertIn('#define C4_V1751_MATCH_BOARD\n#include "../../common/vme_caen_v1751.spec"\n'
                      '#undef C4_V1751_MATCH_BOARD', PRODUCTION)
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
