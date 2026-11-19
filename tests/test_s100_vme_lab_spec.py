"""Static safeguards for the isolated s100 VME UCESB lab variant.

This is not a substitute for compiling UCESB or replaying real LMD data.
"""
from pathlib import Path
import importlib.util
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]
BASE = ROOT / "unpack/exps/s100/s100.spec"
LAB = ROOT / "unpack/exps/s100/s100_vme_lab.spec"

spec = importlib.util.spec_from_file_location("sync_experiment", ROOT / "scripts/sync_experiment.py")
sync = importlib.util.module_from_spec(spec)
spec.loader.exec_module(sync)

audit_spec = importlib.util.spec_from_file_location(
    "audit_caen_words", ROOT / "scripts/audit_caen_words.py")
audit = importlib.util.module_from_spec(audit_spec)
audit_spec.loader.exec_module(audit)

fixture_spec = importlib.util.spec_from_file_location(
    "s100_vme_real_block", ROOT / "tests/test_s100_vme_real_block.py")
fixture = importlib.util.module_from_spec(fixture_spec)
fixture_spec.loader.exec_module(fixture)


class LabSpecTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.base = BASE.read_text()
        cls.lab = LAB.read_text()

    def test_everything_outside_vme_subevent_is_identical(self):
        a, b, _ = sync.subevent(self.base, "fatima_vme_subev")
        c, d, _ = sync.subevent(self.lab, "fatima_vme_subev")
        expected_prefix = self.base[:a].replace(
            '#include "../../common/vme_caen_v1751.spec"',
            '#include "vme_caen_v1751_lab.spec"')
        self.assertEqual(expected_prefix, self.lab[:c])
        self.assertEqual(self.base[b:], self.lab[d:])

    def test_qdc_array_keeps_physical_board_id_mapping(self):
        block = sync.subevent(self.lab, "fatima_vme_subev")[2]
        pairs = re.findall(
            r"\bqdc\[(\d+)\]\s*=\s*VME_CAEN_V1751\(\s*board\s*=\s*(\d+)\s*\)",
            block)
        self.assertEqual([(int(slot), int(board)) for slot, board in pairs],
                         [(0, 6), (1, 7), (2, 8), (3, 9), (4, 10)])

    def test_v1751_selection_discriminator_after_board_id(self):
        # The first V1751 aggregate word is the same across boards.
        # UCESB must see the MATCH(board) from the second word before
        # declaring multiple select branches ambiguous.
        lab = (ROOT / "unpack/exps/s100/vme_caen_v1751_lab.spec").read_text()
        common = (ROOT / "unpack/common/vme_caen_v1751.spec").read_text()
        self.assertIn('#include "vme_caen_v1751_lab.spec"', self.lab)
        self.assertIn('MATCH_END;', lab)
        self.assertNotIn('MATCH_END;', common)
        self.assertLess(lab.index('id = MATCH(board)'), lab.index('MATCH_END;'))
        self.assertLess(lab.index('MATCH_END;'), lab.index('UINT32 board_agg_counter'))

    def test_tdc_bank_selection_and_error_words(self):
        block = sync.subevent(self.lab, "fatima_vme_subev")[2]
        self.assertEqual(re.findall(
            r"\b(tdc\d+)\s*=\s*VME_CAEN_V1290_N", block), ["tdc1", "tdc2"])
        self.assertNotRegex(block, r"\btdc\[\d+\]\s*=")
        for name in ("error1", "error2", "error3"):
            self.assertIn(f"{name} = ERR_WORD_SIX()", block)
        self.assertEqual(block.count("ERR_WORD_SIX()"), 3)
        self.assertIn("scalers = FATIMA_VME_SCALERS()", block)

    def test_real_event_preserves_qdc_identity_and_tdc_words(self):
        words = fixture.WORDS
        qdc_records, qdc_errors = audit.audit_v1751(words[23:49])
        self.assertEqual(qdc_errors, [])
        slots, problems = audit.audit_v1751_slots(
            qdc_records, [6, 7, 8, 9, 10])
        self.assertEqual(problems, [])
        self.assertEqual({slot: record[0] for slot, record in slots.items()},
                         {0: 6, 1: 7, 2: 8, 3: 9, 4: 10})
        self.assertEqual(words[49], 0x06000000)
        tdc_records, tdc_errors = audit.audit_v1290(words[50:])
        self.assertEqual(tdc_errors, [])
        self.assertEqual(tdc_records[0][0:2], (13, 5))

    def test_separate_makefile(self):
        makefile = (ROOT / "unpack/exps/s100/Makefile.vme_lab").read_text()
        self.assertIn("TARGETS:=s100_vme_lab", makefile)
        self.assertNotIn("s100_vme_lab", (ROOT / "unpack/exps/s100/Makefile").read_text())


if __name__ == "__main__":
    unittest.main()
