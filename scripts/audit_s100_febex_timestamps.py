#!/usr/bin/env python3
"""Compare legacy and full-width FEBEX hit timing in a read-only S100 replay."""

import argparse
import csv
import re
from collections import Counter
from contextlib import nullcontext
from decimal import Decimal
from pathlib import Path
from tempfile import TemporaryFile

from compare_s100_whiterabbit import EVENT, capture

BOARD_FIELDS = {"trig", "event_trigger_time_hi", "event_trigger_time_lo", "hit_pattern"}
HIT_FIELDS = (
    "channel_trigger_time_hi", "channel_trigger_time_lo",
    "channel_cfd", "channel_energy", "pileup", "overflow",
)
WR_FIELDS = {"subsystem_id", "t1", "t2", "t3", "t4"}
CLOCK_NS = 10
LOW_MASK = (1 << 24) - 1
COUNTER_MODULUS = 1 << 48


def read_events(stream, member):
    unpack_prefix = f".UNPACK.{member}."
    wr_prefix = unpack_prefix + "ts."
    board_pattern = re.compile(re.escape(unpack_prefix) + r"data\[(\d+)\]\.(\w+)(?:\[(\d+)\])?$")
    event, wr, boards = None, {}, {}
    for line in stream:
        header = EVENT.fullmatch(line)
        if header:
            if event is not None:
                yield event, wr, boards
            event, wr, boards = tuple(map(int, header.groups())), {}, {}
            continue
        name, _, value = line.partition(":")
        board_field = board_pattern.fullmatch(name)
        if board_field:
            board, field, channel = board_field.groups()
            board_words, hits = boards.setdefault(int(board), ({}, {}))
            target = board_words if channel is None else hits.setdefault(int(channel), {})
        elif name.startswith(wr_prefix):
            field = name[len(wr_prefix):]
            target = wr
        else:
            continue
        if event is None or field in target:
            raise ValueError(f"Unexpected or duplicate field {name} at event {event}")
        # UCESB can print the decimal part of a DATA32 as signed.
        target[field] = int(value.split("=", 1)[0], 16)
    if event is not None:
        yield event, wr, boards


def audit(stream, writer=None, *, member="germanium"):
    counts = Counter()
    min_offset = max_offset = worst_difference = None
    for (event, trigger), wr, boards in read_events(stream, member):
        counts["event_headers"] += 1
        if not boards and not wr:
            continue
        if set(wr) != WR_FIELDS or not boards:
            raise ValueError(f"Incomplete {member} dump at event {event}")
        wr_time = sum(wr[f"t{i}"] << (16 * (i - 1)) for i in range(1, 5))
        for slot, (board, hits) in sorted(boards.items()):
            if not BOARD_FIELDS <= board.keys():
                raise ValueError(f"Incomplete FEBEX board {slot} at event {event}")
            if not any(board.values()) and not hits:
                continue
            counts["boards"] += 1
            event_ticks = (board["event_trigger_time_hi"] << 32) | board["event_trigger_time_lo"]
            for channel, fields in sorted(hits.items()):
                if set(fields) != set(HIT_FIELDS) or not 0 <= channel < 16:
                    raise ValueError(f"Incomplete or invalid FEBEX hit at {event}, slot {slot}, channel {channel}")
                channel_ticks = (fields["channel_trigger_time_hi"] << 32) | fields["channel_trigger_time_lo"]
                cfd = fields["channel_cfd"]

                # Legacy Raw2Cal casts the channel time to int64 before subtraction.
                legacy = None if event_ticks == 0 else (
                    ((channel_ticks & LOW_MASK) * CLOCK_NS + cfd * CLOCK_NS // 64)
                    - event_ticks * CLOCK_NS
                )
                # Signed modular subtraction handles hit times on either side of a
                # full counter rollover. Apply the CFD fraction after subtraction.
                half = COUNTER_MODULUS // 2
                delta_ticks = (channel_ticks - event_ticks + half) % COUNTER_MODULUS - half
                full = Decimal(delta_ticks * 64 + cfd) * CLOCK_NS / 64
                counts["hits"] += 1
                counts["legacy_zero_event_skips"] += legacy is None
                counts["channel_above_24_bits"] += channel_ticks > LOW_MASK
                counts["legacy_coarse_offsets_differ"] += (
                    legacy is not None and (channel_ticks & LOW_MASK) - event_ticks != delta_ticks
                )
                min_offset = full if min_offset is None else min(min_offset, full)
                max_offset = full if max_offset is None else max(max_offset, full)
                if legacy is not None:
                    difference = abs(legacy - full)
                    if worst_difference is None or difference > worst_difference[0]:
                        worst_difference = (difference, event, slot, channel, legacy, full)
                if writer:
                    writer.writerow((event, trigger, slot, channel, board["trig"], board["hit_pattern"],
                                     wr["subsystem_id"], wr_time, event_ticks, channel_ticks,
                                     cfd, fields["channel_energy"], fields["pileup"], fields["overflow"],
                                     legacy, full))
    return counts, min_offset, max_offset, worst_difference


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("unpacker", type=Path)
    parser.add_argument("lmd", type=Path)
    parser.add_argument("--max-events", type=int, default=25000)
    parser.add_argument("--member", default="germanium", help="UNPACK event member to inspect")
    parser.add_argument("--csv", type=Path, help="write one row per decoded hit")
    args = parser.parse_args()
    if args.max_events < 1:
        parser.error("--max-events must be positive")
    try:
        with TemporaryFile(mode="w+t", encoding="utf-8", errors="replace") as dump:
            input_events, decoded, errors = capture(
                args.unpacker, args.lmd, args.max_events, dump, "s100",
                levels="UNPACK",
            )
            print(f"Input events: {input_events:,} | Decoded: {decoded:,} | Unpack errors: {errors:,}")
            output = args.csv.open("x", encoding="utf-8", newline="") if args.csv else nullcontext()
            with output as stream:
                writer = csv.writer(stream) if stream else None
                if writer:
                    writer.writerow((
                        "event", "event_trigger", "slot", "channel", "board_trigger", "hit_pattern",
                        "wr_id", "wr_timestamp", "event_ticks", "channel_ticks", "cfd",
                        "energy_word", "pileup", "overflow", "legacy_offset_ns", "full_offset_ns",
                    ))
                counts, minimum, maximum, worst = audit(dump, writer, member=args.member)
        if counts["event_headers"] != input_events:
            raise ValueError(f"Expected {input_events:,} event headers, found {counts['event_headers']:,}")
        print(f"FEBEX boards seen: {counts['boards']:,} | Hits: {counts['hits']:,}")
        if not counts["hits"]:
            raise ValueError(f"No {args.member} hits in the replay")
        print(f"Hits with channel ticks above 24 bits: {counts['channel_above_24_bits']:,}")
        print(f"Hits the legacy reader skips at event counter zero: {counts['legacy_zero_event_skips']:,}")
        print(f"Hits with different coarse offsets: {counts['legacy_coarse_offsets_differ']:,}")
        print(f"Full-width hit minus event range: {minimum} to {maximum} ns")
        if worst:
            difference, event, slot, channel, legacy, full = worst
            print(f"Largest offset difference: {difference} ns (event {event}, slot {slot}, "
                  f"channel {channel}, legacy {legacy} ns, full {full} ns)")
        if errors or decoded != input_events:
            return 1
        return 0
    except (OSError, ValueError) as exc:
        parser.exit(2, f"ERROR: {exc}\n")


if __name__ == "__main__":
    raise SystemExit(main())
