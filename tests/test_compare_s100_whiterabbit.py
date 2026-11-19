import io
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
from compare_s100_whiterabbit import TAMEX_ARRAYS, TAMEX_DETECTORS, WR_FIELDS, compare_streams, read_summary


class CompareWhiteRabbitTests(unittest.TestCase):
    def dump(self, *, id_repr="0x0500=1280", t4=17, omit=None):
        lines = ["Event 789 Trigger 1"]
        for field in sorted(WR_FIELDS):
            if field == omit:
                continue
            value = "0x0000=0"
            if field == ".UNPACK.bplast.ts.subsystem_id":
                value = id_repr
            if field == ".UNPACK.bplast.ts.t4":
                value = f"0x{t4:04x}={t4}"
            lines.append(f"{field}: {value}")
        lines += ["Event 790 Trigger 1", ""]
        return io.StringIO("\n".join(lines))

    def test_same_values_across_dump_formats(self):
        counts, differences, _ = compare_streams(self.dump(id_repr="0x500  =1280"), self.dump())
        self.assertEqual(differences, 0)
        self.assertEqual(counts[0], counts[1])
        self.assertEqual(counts[0]["headers"], 2)
        self.assertEqual(counts[0]["decoded"], 1)
        self.assertEqual(counts[0]["bplast.ts"], 1)

    def test_identifies_exact_event_and_changed_timestamp_word(self):
        _, differences, shown = compare_streams(self.dump(), self.dump(t4=18))
        self.assertEqual(differences, 1)
        self.assertEqual(shown, ["Event 789, .UNPACK.bplast.ts.t4: 17 vs 18"])

    def test_rejects_partial_timestamp_fields(self):
        with self.assertRaisesRegex(ValueError, "incomplete White Rabbit dump"):
            compare_streams(self.dump(), self.dump(omit=".UNPACK.bplast.ts.t4"))

    def tamex_dump(self, edge=(1, 0)):
        fields = []
        for detector in TAMEX_DETECTORS:
            prefix = f".UNPACK.{detector}.tamex[0]."
            fields.extend((f"{prefix}trig: 0x0001=1", f"{prefix}event_size: 0x00000014=20"))
            for field in TAMEX_ARRAYS:
                for value in edge if field == "time_edge" else (0, 1):
                    fields.append(f"{prefix}{field}: 0x{value:03x}={value}")
        return io.StringIO(self.dump().getvalue().replace("Event 790", "\n".join(fields) + "\nEvent 790"))

    def test_tamex_array_order_is_compared_within_each_card(self):
        counts, differences, _ = compare_streams(self.tamex_dump(), self.tamex_dump(), include_tamex=True)
        self.assertEqual(differences, 0)
        self.assertEqual(counts[0]["bplast"], 2)
        _, differences, shown = compare_streams(self.tamex_dump(), self.tamex_dump(edge=(0, 1)), include_tamex=True)
        self.assertEqual(differences, 1)
        self.assertIn(".UNPACK.bgo.tamex[0].time_edge", shown[0])

    def test_tamex_incomplete_arrays_are_rejected(self):
        with self.assertRaisesRegex(ValueError, "incomplete .* TAMEX arrays"):
            compare_streams(self.tamex_dump(), self.tamex_dump(edge=(1,)), include_tamex=True)

    def test_error_totals_follow_the_carriage_return(self):
        stream = io.StringIO("Processed: 1 (1/s)\rEvents: 12  10  (2 errors)   \n", newline=None)
        self.assertEqual(read_summary(stream, "candidate"), (12, 10, 2))
