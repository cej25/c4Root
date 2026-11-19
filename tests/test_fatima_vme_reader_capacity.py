"""Static safeguards for FATIMA VME reader capacity and spare handling.

The generated EXT_STR header remains UCESB-owned; compiling the real reader
against the regenerated six-slot header must be done on a FairRoot machine.
"""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
READER = (ROOT / "c4source/fatima/FatimaVmeReader.cxx").read_text()
HEADER = (ROOT / "c4source/fatima/ext_h101_fatimavme.h").read_text()


class FatimaVmeReaderCapacityTests(unittest.TestCase):
    def test_reader_uses_compiled_header_dimensions(self):
        self.assertIn("std::extent<decltype(fData->fatimavme_qdc)>::value", READER)
        self.assertIn("std::extent<decltype(fData->fatimavme_tdc)>::value", READER)
        self.assertNotRegex(READER, r"for\s*\(\s*int\s+(?:qdc|tdc)\s*=\s*0;\s*(?:qdc|tdc)\s*<\s*[25]")

    def test_spare_banks_and_unmapped_channels_are_skipped(self):
        self.assertIn("if (board_id == 0) continue;", READER)
        self.assertIn("if (geo == 0) continue;", READER)
        self.assertIn("dets_qdc.find(", READER)
        self.assertIn("dets_tdc.find(", READER)
        self.assertNotIn("dets_qdc[std::make_pair(", READER)
        self.assertNotIn("dets_tdc[std::make_pair(", READER)

    def test_header_still_legacy_until_native_regeneration(self):
        # Protect against accidentally committing manually fabricated headers.
        self.assertIn("Do not edit - automatically generated", HEADER)
        self.assertRegex(HEADER, r"\}\s*fatimavme_qdc\[5\];")
        self.assertRegex(HEADER, r"\}\s*fatimavme_tdc\[2\];")


if __name__ == "__main__":
    unittest.main()
