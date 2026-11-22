"""Static safeguards for FATIMA VME reader capacity and spare handling.

The generated EXT_STR headers remain UCESB-owned.
"""
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
READER = (ROOT / "c4source/fatima/FatimaReader.cxx").read_text()
ADAPTER = (ROOT / "c4source/fatima/FatimaVmeReader.cxx").read_text()
HEADER = (ROOT / "c4source/fatima/ext_h101_fatimavme.h").read_text()


class FatimaVmeReaderCapacityTests(unittest.TestCase):
    def test_reader_uses_compiled_header_dimensions(self):
        self.assertIn("std::size(input.fatimavme_qdc)", READER)
        self.assertIn("std::size(input.fatimavme_tdc)", READER)
        self.assertNotRegex(READER, r"for\s*\(\s*int\s+(?:qdc|tdc)\s*=\s*0;\s*(?:qdc|tdc)\s*<\s*[25]")

    def test_spare_banks_and_unmapped_channels_are_skipped(self):
        for module, address, mapping in (("QDC", "board_id", "dets_qdc"),
                                         ("TDC", "geo", "dets_tdc")):
            self.assertIn(f"fFatimaRaw->VMEChain.{module}", ADAPTER)
            self.assertIn(f"if (raw.{address} == 0) continue;", ADAPTER)
            self.assertIn(f"{mapping}.find({{raw.{address}, raw.channel}})", ADAPTER)
            self.assertNotIn(f"{mapping}[", ADAPTER)

    def test_shared_native_header_has_six_slots_per_module_type(self):
        self.assertIn("Do not edit - automatically generated", HEADER)
        for bank in ("qdc", "tdc"):
            self.assertRegex(HEADER, rf"\}}\s*fatimavme_{bank}\[6\];")
        self.assertIn("EXT_STR_h101_fatimavme_ITEMS_INFO", READER)
        self.assertNotIn("EXT_STR_h101_fatimavme_ITEMS_INFO", ADAPTER)


if __name__ == "__main__":
    unittest.main()
