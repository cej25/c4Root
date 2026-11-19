#!/usr/bin/env python3
"""Replay one S100 LMD input and compare White Rabbit data and optional TAMEX hits."""

import argparse
import gzip
import re
import subprocess
import sys
from collections import Counter
from itertools import zip_longest
from pathlib import Path
from tempfile import TemporaryFile

ROUTES = (
    "aida.ts", "germanium.ts", "fatima.ts", "fatimavme.ts", "bplast.ts",
    "bgo.ts", "frstpat.wr", "beammonitor.ts",
)
FIELDS = ("subsystem_id", "t1", "t2", "t3", "t4")
WR_FIELDS = {f".UNPACK.{route}.{field}" for route in ROUTES for field in FIELDS}
TAMEX_DETECTORS = ("fatima", "bplast", "bgo")
TAMEX_PREFIXES = tuple(f".UNPACK.{detector}.tamex[" for detector in TAMEX_DETECTORS)
TAMEX_FIELD = re.compile(
    r"^\.UNPACK\.(fatima|bplast|bgo)\.tamex\[\d+\]\."
    r"(trig|event_size|time_coarse|time_fine|time_edge|time_channel|time_epoch)$"
)
TAMEX_ARRAYS = ("time_coarse", "time_fine", "time_edge", "time_channel", "time_epoch")
EVENT = re.compile(r"^Event +([0-9]+) +Trigger +([0-9]+)\s*$")
SUMMARY = re.compile(r"^Events:[ \t]+(\d+)[ \t]+(\d+)(?:[ \t]+\((\d+) errors?\))?[ \t]*$")


def is_tamex_field(name):
    return name.startswith(TAMEX_PREFIXES) and TAMEX_FIELD.fullmatch(name)


def read_events(stream, label, include_tamex=False):
    header, words = None, {}
    for line in stream:
        if line.startswith("Event "):
            match = EVENT.fullmatch(line)
            if match:
                if header is not None:
                    yield header, words
                header, words = tuple(map(int, match.groups())), {}
        elif line.startswith(".UNPACK."):
            name, _, value = line.partition(":")
            tamex = include_tamex and is_tamex_field(name)
            if name not in WR_FIELDS and not tamex:
                continue
            is_array = tamex and tamex.group(2) in TAMEX_ARRAYS
            if header is None or (name in words and not is_array):
                raise ValueError(f"{label}: unexpected or duplicate {name} at event {header}")
            try:
                # DATA12 and DATA16 print hex differently, but both end in =decimal.
                decoded = int(value.rsplit("=", 1)[-1])
            except ValueError as exc:
                raise ValueError(f"{label}: invalid {name} at event {header}: {value.strip()}") from exc
            if is_array:
                # UCESB dumps NO_INDEX_LIST values as repeated field names.
                words.setdefault(name, []).append(decoded)
            else:
                words[name] = decoded
    if header is not None:
        yield header, words


def read_summary(stream, label):
    stream.seek(0)
    summary, last_line = None, ""
    for line in stream:
        match = SUMMARY.fullmatch(line.rstrip())
        if match:
            summary = tuple(int(value or 0) for value in match.groups())
        if line.strip():
            last_line = line.strip()
    if summary is None:
        raise ValueError(f"{label}: UCESB summary missing (last diagnostic: {last_line!r})")
    return summary


def count_tamex(words, count, label, header):
    slots = {name.rsplit(".", 1)[0] for name in words if name.startswith(TAMEX_PREFIXES)}
    for detector, prefix in zip(TAMEX_DETECTORS, TAMEX_PREFIXES):
        boards = [slot for slot in slots if slot.startswith(prefix)]
        if not boards:
            raise ValueError(f"{label}: missing {detector} TAMEX cards at event {header}")
        for board in boards:
            size = words.get(f"{board}.event_size")
            if size is None or f"{board}.trig" not in words:
                raise ValueError(f"{label}: incomplete {board} at event {header}")
            lengths = [len(words.get(f"{board}.{field}", ())) for field in TAMEX_ARRAYS]
            expected = max(size // 4 - 3, 0)
            if lengths != [expected] * len(TAMEX_ARRAYS):
                raise ValueError(f"{label}: incomplete {board} TAMEX arrays at event {header}")
            count[detector] += expected


def compare_streams(reference, candidate, include_tamex=False):
    labels = ("reference", "candidate")
    counts = [Counter(), Counter()]
    differences, shown = 0, []
    for pair in zip_longest(read_events(reference, labels[0], include_tamex),
                           read_events(candidate, labels[1], include_tamex)):
        for index, event in enumerate(pair):
            if event is None:
                continue
            header, words = event
            count = counts[index]
            count["headers"] += 1
            if words:
                missing = WR_FIELDS - words.keys()
                if missing:
                    missing = ", ".join(sorted(missing))
                    raise ValueError(f"{labels[index]}: incomplete White Rabbit dump at {header}: {missing}")
                count["decoded"] += 1
                count["words"] += len(WR_FIELDS)
                for route in ROUTES:
                    if words[f".UNPACK.{route}.subsystem_id"] or any(
                        words[f".UNPACK.{route}.{field}"] for field in FIELDS[1:]
                    ):
                        count[route] += 1
                if include_tamex:
                    count_tamex(words, count, labels[index], header)
        if pair[0] != pair[1]:
            differences += 1
            if len(shown) < 10:
                left, right = pair
                if left is None or right is None or left[0] != right[0]:
                    shown.append(f"Event headers differ: {left and left[0]} vs {right and right[0]}")
                else:
                    names = left[1].keys() | right[1].keys()
                    name = next(name for name in sorted(names) if left[1].get(name) != right[1].get(name))
                    shown.append(f"Event {left[0][0]}, {name}: {left[1].get(name)} vs {right[1].get(name)}")
    return counts, differences, shown


def capture(executable, lmd, limit, dump, label):
    command = [str(executable.resolve()), str(lmd.resolve()), "--dump=UNPACK",
               "--allow-errors", f"--max-events={limit}"]
    with TemporaryFile(mode="w+t", encoding="utf-8", errors="replace") as diagnostics:
        # Older UCESB releases can lose stdout when their progress timer
        # interrupts a blocked pipe write. Capture directly to a regular file.
        status = subprocess.run(command, stdout=dump, stderr=diagnostics).returncode
        if status:
            diagnostics.seek(0)
            tail = diagnostics.readlines()[-4:]
            raise ValueError(f"{label}: UCESB exited with status {status}\n{''.join(tail).strip()}")
        dump.seek(0)
        return read_summary(diagnostics, label)


def replay(reference, candidate, lmd, limit, include_tamex=False):
    with TemporaryFile() as filtered:
        with TemporaryFile(mode="w+t", encoding="utf-8", errors="replace") as dump:
            print("Running reference unpacker...", flush=True)
            reference_summary = capture(reference, lmd, limit, dump, "reference")
            with gzip.open(filtered, "wt", encoding="utf-8", compresslevel=1) as trace:
                for line in dump:
                    name = line.partition(":")[0]
                    if line.startswith("Event ") or name in WR_FIELDS or (
                        include_tamex and is_tamex_field(name)
                    ):
                        trace.write(line)
        with TemporaryFile(mode="w+t", encoding="utf-8", errors="replace") as dump:
            print("Running candidate unpacker...", flush=True)
            candidate_summary = capture(candidate, lmd, limit, dump, "candidate")
            filtered.seek(0)
            with gzip.open(filtered, "rt", encoding="utf-8") as trace:
                counts, differences, shown = compare_streams(trace, dump, include_tamex)

    failures = list(shown)
    print("Counts below are reference / candidate.")
    for index, label in enumerate(("Input events", "Decoded events", "Unpack errors")):
        print(f"{label}: {reference_summary[index]} / {candidate_summary[index]}")
    print(f"Compared event headers: {counts[0]['headers']} / {counts[1]['headers']}")
    print(f"White Rabbit fields: {counts[0]['words']} / {counts[1]['words']}")
    print(f"Events with differences: {differences}")
    for route in ROUTES:
        print(f"  {route}: {counts[0][route]} / {counts[1][route]} nonzero records")
    if include_tamex:
        for detector in TAMEX_DETECTORS:
            print(f"  {detector}: {counts[0][detector]} / {counts[1][detector]} TAMEX time and epoch entries")
    if reference_summary != candidate_summary:
        failures.append("UCESB event or error totals differ")
    if (reference_summary[0], candidate_summary[0]) != (limit, limit):
        failures.append(f"Expected {limit} input events from each unpacker")
    if (counts[0]["headers"], counts[1]["headers"]) != (reference_summary[0], candidate_summary[0]):
        failures.append("Event headers do not cover every processed event")
    if (counts[0]["decoded"], counts[1]["decoded"]) != (reference_summary[1], candidate_summary[1]):
        failures.append("Complete event dumps do not match the UCESB decoded-event totals")
    if not any(counts[0][route] and counts[1][route] for route in ROUTES):
        failures.append("No nonzero White Rabbit records were compared")
    if include_tamex and not any(counts[0][detector] and counts[1][detector] for detector in TAMEX_DETECTORS):
        failures.append("No TAMEX time or epoch entries were compared")
    if failures:
        for message in failures:
            print(f"FAIL: {message}")
        return 1
    fields = "White Rabbit fields and TAMEX hits" if include_tamex else "White Rabbit fields"
    print(f"PASS: event headers, {fields}, and unpack error counts match")
    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("reference", type=Path)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("lmd", type=Path)
    parser.add_argument("--max-events", type=int, default=100_000)
    parser.add_argument("--tamex", action="store_true", help="also compare FATIMA, bPlast, and BGO TAMEX data")
    args = parser.parse_args()
    if args.max_events <= 0:
        parser.error("--max-events must be positive")
    print(f"Replaying {args.max_events:,} S100 events with each unpacker.", flush=True)
    try:
        return replay(args.reference, args.candidate, args.lmd, args.max_events, args.tamex)
    except (OSError, ValueError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
