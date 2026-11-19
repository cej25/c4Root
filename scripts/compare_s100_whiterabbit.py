#!/usr/bin/env python3
"""Replay one S100 LMD input with two unpackers and compare White Rabbit data."""

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
EVENT = re.compile(r"^Event +([0-9]+) +Trigger +([0-9]+)\s*$")
SUMMARY = re.compile(r"^Events:[ \t]+(\d+)[ \t]+(\d+)(?:[ \t]+\((\d+) errors?\))?[ \t]*$")


def read_events(stream, label):
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
            if name not in WR_FIELDS:
                continue
            if header is None or name in words:
                raise ValueError(f"{label}: unexpected or duplicate {name} at event {header}")
            try:
                # DATA12 and DATA16 print hex differently, but both end in =decimal.
                words[name] = int(value.rsplit("=", 1)[-1])
            except ValueError as exc:
                raise ValueError(f"{label}: invalid {name} at event {header}: {value.strip()}") from exc
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


def compare_streams(reference, candidate):
    labels = ("reference", "candidate")
    counts = [Counter(), Counter()]
    differences, shown = 0, []
    for pair in zip_longest(read_events(reference, labels[0]), read_events(candidate, labels[1])):
        for index, event in enumerate(pair):
            if event is None:
                continue
            header, words = event
            count = counts[index]
            count["headers"] += 1
            if words:
                if words.keys() != WR_FIELDS:
                    missing = ", ".join(sorted(WR_FIELDS - words.keys()))
                    raise ValueError(f"{labels[index]}: incomplete White Rabbit dump at {header}: {missing}")
                count["decoded"] += 1
                count["words"] += len(words)
                for route in ROUTES:
                    if words[f".UNPACK.{route}.subsystem_id"] or any(
                        words[f".UNPACK.{route}.{field}"] for field in FIELDS[1:]
                    ):
                        count[route] += 1
        if pair[0] != pair[1]:
            differences += 1
            if len(shown) < 10:
                left, right = pair
                if left is None or right is None or left[0] != right[0]:
                    shown.append(f"Event headers differ: {left and left[0]} vs {right and right[0]}")
                else:
                    name = next(name for name in sorted(WR_FIELDS) if left[1].get(name) != right[1].get(name))
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


def replay(reference, candidate, lmd, limit):
    with TemporaryFile() as filtered:
        with TemporaryFile(mode="w+t", encoding="utf-8", errors="replace") as dump:
            print("Running reference unpacker...", flush=True)
            reference_summary = capture(reference, lmd, limit, dump, "reference")
            with gzip.open(filtered, "wt", encoding="utf-8", compresslevel=1) as trace:
                for line in dump:
                    if line.startswith("Event ") or (
                        line.startswith(".UNPACK.") and line.partition(":")[0] in WR_FIELDS
                    ):
                        trace.write(line)
        with TemporaryFile(mode="w+t", encoding="utf-8", errors="replace") as dump:
            print("Running candidate unpacker...", flush=True)
            candidate_summary = capture(candidate, lmd, limit, dump, "candidate")
            filtered.seek(0)
            with gzip.open(filtered, "rt", encoding="utf-8") as trace:
                counts, differences, shown = compare_streams(trace, dump)

    failures = list(shown)
    print("Counts below are reference / candidate.")
    for index, label in enumerate(("Input events", "Decoded events", "Unpack errors")):
        print(f"{label}: {reference_summary[index]} / {candidate_summary[index]}")
    print(f"Compared event headers: {counts[0]['headers']} / {counts[1]['headers']}")
    print(f"White Rabbit fields: {counts[0]['words']} / {counts[1]['words']}")
    print(f"Events with differences: {differences}")
    for route in ROUTES:
        print(f"  {route}: {counts[0][route]} / {counts[1][route]} nonzero records")
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
    if failures:
        for message in failures:
            print(f"FAIL: {message}")
        return 1
    print("PASS: event headers, White Rabbit fields and unpack error counts match")
    return 0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("reference", type=Path)
    parser.add_argument("candidate", type=Path)
    parser.add_argument("lmd", type=Path)
    parser.add_argument("--max-events", type=int, default=100_000)
    args = parser.parse_args()
    if args.max_events <= 0:
        parser.error("--max-events must be positive")
    print(f"Replaying {args.max_events:,} S100 events with each unpacker.", flush=True)
    try:
        return replay(args.reference, args.candidate, args.lmd, args.max_events)
    except (OSError, ValueError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
