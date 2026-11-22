"""S100 layout and native-header synchronisation checks without building UCESB."""
import io
from contextlib import redirect_stdout
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))

from sync_experiment import installed_layouts, regenerate_headers, stale_headers
from validate_experiment import emit_whiterabbit, read_yaml


class SyncExperimentTests(unittest.TestCase):
    def test_installed_subset_does_not_change_compiled_layout(self):
        config = read_yaml(ROOT / "config/s100/experiment.yaml")
        original = installed_layouts(config)
        config["FATIMA"]["boards"] = [1, 3]
        self.assertEqual(installed_layouts(config), original)
        self.assertEqual(stale_headers(original), {})

    def test_compiled_order_and_addresses_drive_generation(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "experiment.yaml"
            yaml = (ROOT / "config/s100/experiment.yaml").read_text()
            path.write_text(yaml.replace("[[0, 0], [0, 1], [0, 2], [0, 3]]",
                                         "[[1, 9], [0, 1], [0, 2], [0, 3], [0, 0]]", 1))
            output = io.StringIO()
            with redirect_stdout(output):
                emit_whiterabbit(path, include_procids=True)
            fatima = next(line for line in output.getvalue().splitlines()
                          if line.startswith("#define S100_TAMEX_CARDS_FATIMA "))
            self.assertIn("tamex[0] = TAMEX4_SFP(sfp = 1, card = 9);", fatima)
            self.assertIn("tamex[4] = TAMEX4_SFP(sfp = 0, card = 0);", fatima)
            self.assertEqual(set(stale_headers(installed_layouts(read_yaml(path)))), {"fatima"})

    def test_generated_header_is_installed_byte_for_byte(self):
        generated = (b"typedef struct { struct { unsigned entry; } fatima_tamex[1]; } "
                     b"EXT_STR_h101_fatima_onion;\r\n/* Native layout table */\r\n")
        with tempfile.TemporaryDirectory() as folder:
            target = Path(folder) / "ext_h101_fatima.h"

            def generate(command, cwd, check):
                (Path(cwd) / target.name).write_bytes(generated)

            with patch("sync_experiment.subprocess.run", generate), patch("sync_experiment.ROOT", Path(folder)):
                regenerate_headers({"fatima": [(0, 0)]}, {"fatima": target})

            self.assertEqual(target.read_bytes(), generated)

    def test_bad_or_uncompiled_addresses_are_rejected(self):
        config = read_yaml(ROOT / "config/s100/experiment.yaml")
        config["FATIMA"]["boards"] = [0, 1, 2, 9]
        with self.assertRaisesRegex(ValueError, "FATIMA: add unsupported installed addresses"):
            installed_layouts(config)
        config["FATIMA"]["compiled_slots"].append([0, 0])
        with self.assertRaisesRegex(ValueError, "duplicate compiled TAMEX address"):
            installed_layouts(config)
        config["FATIMA"]["compiled_slots"][-1] = [16, 9]
        with self.assertRaisesRegex(ValueError, "SFP 0–15"):
            installed_layouts(config)


if __name__ == "__main__":
    unittest.main()
