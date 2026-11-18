"""Regression fixture from a real s100 FATIMA VME procid-70 subevent.

55 payload words, MBS subevent size 220 bytes. Supplied during the
UCESB VME audit; used to detect regressions before structural rewrites.
"""
import importlib.util
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("audit_caen_words", ROOT / "scripts/audit_caen_words.py")
audit = importlib.util.module_from_spec(spec)
spec.loader.exec_module(audit)

RAW = """
00001500 03e18e50 04e12d77 05e1419d 06e117ca 7a001000 75a64151 e2a44bdd
00000000 c98595dc 7f872346 6fe68969 5f3275cf 00000000 00000000 0ef4e00f
19cec477 b4aad986 00513675 0fc3a4c4 6714da56 00000000 7c000000 a0000004
34000000 00000000 0000cca4 a0000004 3c000000 00000000 0000cc6c a0000004
44000000 00000000 0000cc74 a000000a 4c000040 00000000 0000cc80 40000006
70000000 00000082 0005eaab 00000037 0f2d0a11 a0000004 50000000 00000000
0000cc93 06000000 426bb08d 00202e09 02a041c6 02c0aa32 800000ad
"""
WORDS = [int(word, 16) for word in RAW.split()]


class S100RealVmeBlockTests(unittest.TestCase):
    def test_complete_subevent_word_count(self):
        self.assertEqual(len(WORDS), 55)
        self.assertEqual(len(WORDS) * 4, 220)
        self.assertEqual(WORDS[0], 0x1500)

    def test_scaler_block_boundaries(self):
        self.assertEqual((WORDS[5] >> 27) & 0x1f, 15)
        self.assertEqual((WORDS[5] >> 8) & 0x1f, 16)
        self.assertEqual(WORDS[22], 0x7c000000)

    def test_five_qdc_boards_and_variable_channel(self):
        records, problems = audit.audit_v1751(WORDS[23:49])
        self.assertEqual(problems, [])
        self.assertEqual([record[0] for record in records], [6, 7, 8, 9, 10])
        self.assertEqual([record[2] for record in records], [4, 4, 4, 10, 4])
        self.assertEqual(records[3][1], 0x40)
        self.assertEqual(records[3][3], [(6, 4, 6, 4)])
        self.assertEqual(WORDS[39], 0x40000006)

    def test_missing_first_qdc_keeps_remaining_hardware_ids(self):
        # Synthetic variation of the supplied real event: omit the four
        # words belonging to board 6 (not a second observed event).
        qdc_words = WORDS[27:49]
        records, problems = audit.audit_v1751(qdc_words)
        self.assertEqual(problems, [])
        self.assertEqual([record[0] for record in records], [7, 8, 9, 10])
        self.assertEqual([record[2] for record in records], [4, 4, 10, 4])
        logical_slots = {board_id - 6: board_id for board_id, _, _, _ in records}
        self.assertEqual(logical_slots, {1: 7, 2: 8, 3: 9, 4: 10})
        # The empty slot is intentional: board 7 must never become board 6.
        self.assertNotIn(0, logical_slots)

    def test_error_marker_and_v1290(self):
        self.assertEqual(WORDS[49], 0x06000000)
        records, problems = audit.audit_v1290(WORDS[50:55])
        self.assertEqual(problems, [])
        self.assertEqual(len(records), 1)
        geo, length, counts = records[0]
        self.assertEqual((geo, length), (13, 5))
        self.assertEqual(counts["measurement"], 3)
        self.assertEqual(counts["tdc_header"], 0)
        self.assertEqual(counts["tdc_trailer"], 0)


if __name__ == "__main__":
    unittest.main()
