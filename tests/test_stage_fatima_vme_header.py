"""Check six-slot native UCESB header staging validation without UCESB installed."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "stage_fatima_vme_header", ROOT / "scripts/stage_fatima_vme_header.py")
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)

PREFIX = """#define EXT_STR_h101_fatimavme_s100_ITEMS_INFO(ok,si,offset,struct_t,printerr)
typedef struct EXT_STR_h101_fatimavme_s100_onion_t
{
  struct { unsigned _board_id; } fatimavme_qdc[6];
  struct { unsigned _geo; } fatimavme_tdc[6];
} EXT_STR_h101_fatimavme_s100_onion;
"""


class StageVmeHeaderTests(unittest.TestCase):
    def test_six_slot_header_accepted(self):
        self.assertEqual(module.validate_generated_header(PREFIX), {"qdc": 6, "tdc": 6})

    def test_incorrect_dimension_rejected(self):
        with self.assertRaisesRegex(ValueError, "expected six"):
            module.validate_generated_header(PREFIX.replace("fatimavme_tdc[6]", "fatimavme_tdc[2]"))

    def test_missing_layout_rejected(self):
        with self.assertRaisesRegex(ValueError, "layout"):
            module.validate_generated_header(
                PREFIX.replace("EXT_STR_h101_fatimavme_s100_ITEMS_INFO", "MISSING_LAYOUT"))

    def test_installed_header_is_not_rewritten_by_this_module(self):
        self.assertFalse("write_text" in module.validate_generated_header.__code__.co_names)


if __name__ == "__main__":
    unittest.main()
