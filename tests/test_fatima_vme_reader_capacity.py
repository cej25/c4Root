"""Static safeguards for FATIMA VME reader capacity and spare handling.

The generated EXT_STR headers remain UCESB-owned.
"""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
READER = (ROOT / "c4source/fatima/FatimaVmeReader.cxx").read_text()
HEADER = (ROOT / "c4source/fatima/ext_h101_fatimavme.h").read_text()


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

    def test_shared_native_header_has_six_slots_per_module_type(self):
        self.assertIn("Do not edit - automatically generated", HEADER)
        for bank in ("qdc", "tdc"):
            self.assertRegex(HEADER, rf"\}}\s*fatimavme_{bank}\[6\];")
        self.assertIn("EXT_STR_h101_fatimavme_ITEMS_INFO", READER)


if __name__ == "__main__":
    unittest.main()
