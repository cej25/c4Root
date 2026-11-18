#!/usr/bin/env python3
"""Regression for the FATIMA VME payload that exposed the V1751/TDC boundary bug.

Words are copied verbatim from the failing procid 70 subevent. This tests
boundary arithmetic, NOT compilation or execution of the UCESB .spec parser.
"""
import pathlib
import re

WORDS = """
00001500 03e17af8 04e12d82 05e1419d 06e117ca 7a001000 75a641aa e2a44be1
00000000 c98595e1 7f872348 6fe6896e 5f3275d4 00000000 00000000 0ef4e010
19cec478 b4aada95 00513675 0fc3a51f 6714da5a 00000000 7c000000 a0000004
34000000 00000000 00001e9d a0000004 3c000000 00000000 00001e67 a0000004
44000000 00000000 00001e6d a0000004 4c000000 00000000 00001e7b a000000a
50000040 00000000 00001e87 40000006 70000000 00000082 00007854 00000097
0aeb072f 462ab42c 01bf9f15 8000006c 426bb12d 02bfb376 02c043e3 8000008d
"""
words = [int(token, 16) for token in WORDS.split()]
board_pos = words.index(0xA0000004)
assert board_pos == 23
for board_id in range(6, 11):
    word = words[board_pos]
    assert word >> 28 == 0xA
    size = word & 0x0FFFFFFF
    assert 4 <= size <= 10
    mask_and_id = words[board_pos + 1]
    assert (mask_and_id >> 27) == board_id
    mask = mask_and_id & 0xFF
    if board_id < 10:
        assert size == 4 and mask == 0
    else:
        assert size == 10 and mask == 0x40
        # One six-word channel aggregate, no waveform, with timing,
        # extras and charge fields, exactly within the board boundary.
        channel = words[board_pos + 4:board_pos + 10]
        assert channel[0] == 0x40000006
        assert channel[1] == 0x70000000
        assert channel[2] == 0x00000082
        assert channel[3] == 0x00007854
        assert channel[4] == 0x00000097
        assert channel[5] == 0x0AEB072F
        assert mask.bit_count() == 1
    board_pos += size

# The next word, *after* the V1751 aggregate, really is a V1290 header.
assert words[board_pos] == 0x462AB42C
assert words[board_pos + 2] == 0x8000006C
assert words[board_pos + 3] == 0x426BB12D
assert words[-1] == 0x8000008D

# Prevent accidental reintroduction of the known fixed-width expression.
spec = pathlib.Path(__file__).resolve().parents[1] / "unpack/common/vme_caen_v1751.spec"
text = spec.read_text()
assert "(6+TRACE_LENGTH)" not in text
assert "format_one.no_wave_samples * 12" in text
print("PASS: FATIMA VME payload aligns V1751 boards and both V1290 events")
