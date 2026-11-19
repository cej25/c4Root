"""Static safeguards for FATIMA VME reader capacity and spare handling.

The generated EXT_STR headers remain UCESB-owned.
"""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
READER = (ROOT / "c4source/fatima/FatimaVmeReader.cxx").read_text()
LEGACY_HEADER = (ROOT / "c4source/fatima/ext_h101_fatimavme.h").read_text()
S100_HEADER = (ROOT / "c4source/fatima/ext_h101_fatimavme_s100.h").read_text()


class FatimaVmeReaderCapacityTests(unittest.TestCase):
    def test_reader_uses_compiled_header_dimensions(self):
        self.assertIn("std::extent<decltype(data->fatimavme_qdc)>::value", READER)
        self.assertIn("std::extent<decltype(data->fatimavme_tdc)>::value", READER)
        self.assertNotRegex(READER, r"for\s*\(\s*int\s+(?:qdc|tdc)\s*=\s*0;\s*(?:qdc|tdc)\s*<\s*[25]")

    def test_spare_banks_and_unmapped_channels_are_skipped(self):
        self.assertIn("if (board_id == 0) continue;", READER)
        self.assertIn("if (geo == 0) continue;", READER)
        self.assertIn("dets_qdc.find(", READER)
        self.assertIn("dets_tdc.find(", READER)
        self.assertNotIn("dets_qdc[std::make_pair(", READER)
        self.assertNotIn("dets_tdc[std::make_pair(", READER)

    def test_production_and_legacy_layouts_have_separate_native_headers(self):
        for header, qdc, tdc in ((LEGACY_HEADER, 5, 2), (S100_HEADER, 6, 6)):
            self.assertIn("Do not edit - automatically generated", header)
            self.assertRegex(header, rf"\}}\s*fatimavme_qdc\[{qdc}\];")
            self.assertRegex(header, rf"\}}\s*fatimavme_tdc\[{tdc}\];")
        self.assertIn("EXT_STR_h101_fatimavme_s100_ITEMS_INFO", READER)


if __name__ == "__main__":
    unittest.main()
