"""Check six-slot native UCESB header staging validation without UCESB installed."""
import importlib.util
import sys
from tempfile import TemporaryDirectory
from pathlib import Path
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "stage_fatima_vme_header", ROOT / "scripts/stage_fatima_vme_header.py")
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)

PREFIX = """#define EXT_STR_h101_fatimavme_ITEMS_INFO(ok,si,offset,struct_t,printerr)
typedef struct EXT_STR_h101_fatimavme_onion_t
{
  struct { unsigned _board_id; } fatimavme_qdc[6];
  struct { unsigned _geo; } fatimavme_tdc[6];
} EXT_STR_h101_fatimavme_onion;
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
                PREFIX.replace("EXT_STR_h101_fatimavme_ITEMS_INFO", "MISSING_LAYOUT"))

    def test_staging_preserves_all_generator_output_bytes(self):
        generated = (PREFIX + "\n/* Native packed layout table */\n").replace("\n", "\r\n").encode()
        with TemporaryDirectory() as folder:
            directory = Path(folder)
            unpacker = directory / "ucesb"
            unpacker.touch()
            output = directory / "staged.h"

            def generate(command, cwd, check):
                (Path(cwd) / "ext_h101_fatimavme.h").write_bytes(generated)
                return module.subprocess.CompletedProcess(command, 0)

            argv = ["stage_fatima_vme_header", "--unpacker", str(unpacker),
                    "--output", str(output)]
            with patch.object(sys, "argv", argv), patch.object(module.subprocess, "run", generate):
                self.assertEqual(module.main(), 0)

            self.assertEqual(output.read_bytes(), generated)


if __name__ == "__main__":
    unittest.main()
