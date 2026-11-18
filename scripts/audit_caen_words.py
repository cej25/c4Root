#!/usr/bin/env python3
"""Independent CAEN V1751 DPP-PSD and V1290 event-boundary audit.

Input is a TEXT file containing one 32-bit hex word per line, taken from one
module block (not an entire LMD or MBS subevent). Lines may use 0x prefixes
or contain trailing # comments. Does not modify data or c4Root headers.

V1751: checks board-aggregate and channel-aggregate word lengths. The format
and event layout need to be confirmed against the firmware used at acquisition.
V1290: checks global headers/trailers, GEO consistency and word counts; it
reports optional TDC headers/trailers, errors and trigger-time-tag words.
"""
import argparse
from pathlib import Path
import re
import sys


def read_words(path):
    result = []
    for line_no, line in enumerate(path.read_text().splitlines(), 1):
        line = line.split("#", 1)[0].strip()
        if not line:
            continue
        token = line.split()
        if len(token) != 1:
            raise ValueError(f"line {line_no}: expected exactly one hex word")
        word = token[0]
        if not re.fullmatch(r"(?:0[xX])?[0-9a-fA-F]{1,8}", word):
            raise ValueError(f"line {line_no}: invalid 32-bit hexadecimal word {word!r}")
        result.append(int(word, 16))
    if not result:
        raise ValueError("no data words")
    return result


def audit_v1751(words):
    findings = []
    cursor = 0
    boards = []
    while cursor < len(words):
        base = cursor
        header = words[cursor]
        if header >> 28 != 0xA:
            findings.append(f"word {base}: expected V1751 board aggregate marker 0xA")
            break
        size = header & 0x0FFFFFFF
        if size < 4 or size > len(words) - base:
            findings.append(f"word {base}: invalid board aggregate size {size} (remaining {len(words) - base})")
            break
        board_id = (words[base + 1] >> 27) & 0x1F
        mask = words[base + 1] & 0xFF
        board_end = base + size
        cursor += 4
        channels = []
        for channel in range(8):
            if not (mask & (1 << channel)):
                continue
            if cursor >= board_end:
                findings.append(f"board {board_id}: channel mask requires channel {channel}, but aggregate ended")
                break
            channel_header = words[cursor]
            channel_size = channel_header & 0x003FFFFF
            fmt = channel_header >> 28
            if channel_size < 2 or cursor + channel_size > board_end:
                findings.append(f"board {board_id} channel {channel}: invalid aggregate size {channel_size}")
                break
            channels.append((channel, cursor - base, channel_size, fmt))
            cursor += channel_size
        if cursor != board_end:
            findings.append(f"board {board_id}: consumed {cursor - base} words, expected {size}")
            cursor = board_end
        boards.append((board_id, mask, size, channels))
    if cursor < len(words):
        findings.append(f"{len(words) - cursor} trailing words not parsed as V1751 board aggregates")
    return boards, findings



def audit_v1751_slots(records, board_ids):
    """Map decoded aggregates to stable hardware-ID slots.

    This is a reference check, not a replacement for UCESB's parser. An absent
    board leaves a vacant slot; a reordered aggregate retains its physical slot.
    """
    slots = {board_id: index for index, board_id in enumerate(board_ids)}
    occupied = {}
    findings = []
    for record in records:
        board_id = record[0]
        if board_id not in slots:
            findings.append(f"unexpected V1751 board ID {board_id}")
            continue
        slot = slots[board_id]
        if slot in occupied:
            findings.append(f"duplicate V1751 board ID {board_id}")
        else:
            occupied[slot] = record
    return occupied, findings


def audit_v1290(words):
    findings, events = [], []
    cursor = 0
    while cursor < len(words):
        base = cursor
        header = words[cursor]
        if header >> 27 != 0b01000:
            findings.append(f"word {base}: expected V1290 global header (01000)")
            break
        geo = header & 0x1F
        cursor += 1
        counts = {"measurement": 0, "tdc_header": 0, "tdc_trailer": 0,
                  "tdc_error": 0, "trigger_tag": 0}
        found_trailer = False
        while cursor < len(words):
            word = words[cursor]
            kind = word >> 27
            if kind == 0b10000:
                if (word & 0x1F) != geo:
                    findings.append(f"V1290 at word {base}: trailer GEO differs from header")
                expected = (word >> 5) & 0xFFFF
                actual = cursor - base + 1
                if actual != expected:
                    findings.append(f"V1290 GEO {geo}: trailer word count {expected}, observed {actual}")
                cursor += 1
                found_trailer = True
                break
            if kind == 0b10001:
                counts["trigger_tag"] += 1
            elif kind == 0b00000:
                counts["measurement"] += 1
            elif kind == 0b00001:
                counts["tdc_header"] += 1
            elif kind == 0b00011:
                counts["tdc_trailer"] += 1
            elif kind == 0b00100:
                counts["tdc_error"] += 1
            else:
                findings.append(f"V1290 GEO {geo}: unknown internal word type {kind:05b} at {cursor}")
            cursor += 1
        if not found_trailer:
            findings.append(f"V1290 GEO {geo}: missing global trailer")
            break
        events.append((geo, cursor - base, counts))
    if cursor < len(words):
        findings.append(f"{len(words) - cursor} trailing words not parsed as V1290 events")
    return events, findings


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("type", choices=["v1751", "v1290"])
    parser.add_argument("words", type=Path, help="text file with one hexadecimal 32-bit word per line")
    args = parser.parse_args()
    try:
        words = read_words(args.words)
        records, findings = (audit_v1751(words) if args.type == "v1751"
                             else audit_v1290(words))
    except (OSError, ValueError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2
    print(f"Parsed {len(words)} 32-bit words, {len(records)} {args.type} record(s)")
    for record in records:
        print(record)
    for warning in findings:
        print(f"WARNING: {warning}")
    return 1 if findings else 0


if __name__ == "__main__":
    sys.exit(main())
