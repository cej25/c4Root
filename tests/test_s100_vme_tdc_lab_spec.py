"""Guard the separate V1290 GEO-matched experimental UCESB candidate.

This validates source structure only. Native UCESB compilation and full-run
field comparisons are required before using any generated outputs.
"""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
BASE = (ROOT / "unpack/exps/s100/s100_vme_lab.spec").read_text()
TRIAL = (ROOT / "unpack/exps/s100/s100_vme_tdc_lab.spec").read_text()
MODULE = (ROOT / "unpack/exps/s100/vme_caen_v1290_geo_lab.spec").read_text()
COMMON = (ROOT / "unpack/common/vme_caen_v1x90.spec").read_text()


def subevent(text):
    start = text.index("SUBEVENT(fatima_vme_subev)")
    end = text.index("SUBEVENT(bplast_subev)", start)
    return start, end, text[start:end]


class V1290LabTests(unittest.TestCase):
    def test_only_vme_and_local_module_include_differ(self):
        a, b, _ = subevent(BASE)
        c, d, _ = subevent(TRIAL)
        self.assertEqual(
            BASE[:a].replace(
                '#include "../frs/frs_s100.spec" //r3b frs',
                '#include "../frs/frs_s100.spec" //r3b frs\n'
                '#include "vme_caen_v1290_geo_lab.spec"'),
            TRIAL[:c])
        self.assertEqual(BASE[b:], TRIAL[d:])

    def test_tdc_geos_are_distinct_and_stable(self):
        block = subevent(TRIAL)[2]
        actual = re.findall(
            r"tdc\[(\d+)\]\s*=\s*VME_CAEN_V1290_GEO\(\s*geom_expected\s*=\s*(\d+)\s*\)",
            block)
        self.assertEqual(actual, [("0", "12"), ("1", "13")])
        self.assertEqual(block.count("error3 = ERR_WORD_SIX()"), 1)
        self.assertNotIn("tdc1 = VME_CAEN_V1290_N", block)
        self.assertNotIn("tdc2 = VME_CAEN_V1290_N", block)
        self.assertIn("qdc[0] = VME_CAEN_V1751(board=6)", block)

    def test_geo_is_matched_before_select_boundary(self):
        self.assertIn("VME_CAEN_V1290_GEO(geom_expected)", MODULE)
        self.assertIn("0_4: geom = MATCH(geom_expected);", MODULE)
        self.assertIn("27_31: type = MATCH(0b01000);", MODULE)
        self.assertLess(MODULE.index("MATCH(geom_expected)"), MODULE.index("MATCH_END;"))
        self.assertLess(MODULE.index("MATCH_END;"), MODULE.index("select several"))
        self.assertIn("VME_CAEN_V1290_N()", COMMON)
        self.assertNotIn("VME_CAEN_V1290_GEO", COMMON)

    def test_module_fields_match_production(self):
        # Changes limited to match conditions, discriminator and function name.
        original = COMMON[COMMON.index("VME_CAEN_V1290_N()"):
                          COMMON.index("VME_CAEN_V1190_N()")]
        derived = original.replace(
            "VME_CAEN_V1290_N()", "VME_CAEN_V1290_GEO(geom_expected)"
        ).replace(
            "0_4: geom;", "0_4: geom = MATCH(geom_expected);", 1
        ).replace(
            "        ENCODE(geo, (value=geom));\n    };",
            "        ENCODE(geo, (value=geom));\n    };\n\n"
            "    // Distinguish board GEO before UCESB selects between TDC alternatives.\n"
            "    MATCH_END;"
        )
        self.assertEqual(
            "// Experimental GEO-discriminated V1290. Keep the shared FRS V1290 unchanged.\n"
            "// Requires common vme_caen_v1x90.spec to have been included by frs_s100.spec.\n"
            + derived, MODULE)

    def test_separate_build_target(self):
        mk = (ROOT / "unpack/exps/s100/Makefile.vme_tdc_lab").read_text()
        self.assertIn("TARGETS:=s100_vme_tdc_lab", mk)
        self.assertNotIn("s100_vme_tdc_lab", (ROOT / "unpack/exps/s100/Makefile").read_text())


if __name__ == "__main__":
    unittest.main()
