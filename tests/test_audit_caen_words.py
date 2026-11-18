"""Synthetic boundary tests for the independent CAEN word-sequence auditor."""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("audit_caen_words", ROOT / "scripts/audit_caen_words.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)


class CaenAuditTests(unittest.TestCase):
    def test_v1751_one_six_word_channel_aggregate(self):
        # Four board-header words plus a six-word channel aggregate.
        words = [0xA000000A, 0x30000001, 0, 0,
                 0x40000006, 0, 0, 0, 0, 0]
        records, errors = audit.audit_v1751(words)
        self.assertEqual(errors, [])
        self.assertEqual(len(records), 1)
        self.assertEqual(records[0][3][0][2], 6)

    def test_v1751_detect_missing_channel_words(self):
        words = [0xA000000A, 0x30000001, 0, 0,
                 0x40000009, 0, 0, 0, 0, 0]
        _, errors = audit.audit_v1751(words)
        self.assertTrue(any("invalid aggregate size" in item for item in errors))

    def test_v1290_global_word_count_and_geo(self):
        geo = 12
        words = [(8 << 27) | geo, (0 << 27) | (2 << 21) | 77,
                 (16 << 27) | (3 << 5) | geo]
        events, errors = audit.audit_v1290(words)
        self.assertEqual(errors, [])
        self.assertEqual(events[0][2]["measurement"], 1)

    def test_v1290_detect_global_word_count_mismatch(self):
        words = [(8 << 27) | 7, (0 << 27) | 4,
                 (16 << 27) | (4 << 5) | 7]
        _, errors = audit.audit_v1290(words)
        self.assertTrue(any("word count" in item for item in errors))

    def test_v1290_detect_geo_mismatch(self):
        words = [(8 << 27) | 7, (16 << 27) | (2 << 5) | 8]
        _, errors = audit.audit_v1290(words)
        self.assertTrue(any("GEO differs" in item for item in errors))


if __name__ == "__main__":
    unittest.main()
