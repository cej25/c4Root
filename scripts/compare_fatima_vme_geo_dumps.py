#!/usr/bin/env python3
"""Compare FATIMA VME UCESB dumps across positional vs GEO-matched V1290 banks.

Use filtered --dump=UNPACK stdout or pass two executable paths with --lmd.
QDC1..QDC5 become qdc[0]..qdc[4]. V1290 fields are grouped by the
decoded physical GEO, not an assumed bank index. Blank TDC banks with only geo=0 are omitted. Additional QDC reserve slots
(qdc[5] onwards) are omitted only if all their exported values are zero.
Extra data on an unassigned bank is an error.
"""
import argparse
import re
import sys
from itertools import chain, zip_longest
from pathlib import Path
from tempfile import TemporaryDirectory, TemporaryFile

from compare_fatima_vme_dumps import iter_events
from compare_s100_whiterabbit import capture

BANK = re.compile(r"^(tdc(?:\d+|\[\d+\]))\.(.+)$")
GEO = re.compile(r"^(?:0x[0-9a-fA-F]+|[+-]?\d+)=([+-]?\d+)$")
SPARE_QDC = re.compile(r"^qdc\[(\d+)\]\.([^ ]+)$")


def canonical(fields):
    other = []
    qdc_spares = {}
    banks = {}
    for name, value in fields:
        match = BANK.match(name)
        if match:
            bank, field = match.groups()
            banks.setdefault(bank, []).append((field, value))
        else:
            spare = SPARE_QDC.match(name)
            if spare and int(spare.group(1)) >= 5:
                qdc_spares.setdefault(int(spare.group(1)), []).append((spare.group(2), value))
            else:
                other.append((name, value))
    for slot, entries in qdc_spares.items():
        if not {name for name, _ in entries}.issuperset(
            {"board_id", "board_time", "channels", "dm", "extras"}
        ):
            raise ValueError(f"qdc[{slot}]: reserve bank is missing expected fields")
        for name, value in entries:
            match = GEO.match(value.strip())
            if match is None or int(match.group(1)) != 0:
                raise ValueError(
                    f"qdc[{slot}].{name}: reserve bank is not empty ({value!r})")
    by_geo = {}
    for bank, entries in banks.items():
        geo_fields = [value for field, value in entries if field == "geo"]
        if len(geo_fields) != 1:
            raise ValueError(f"{bank}: expected exactly one GEO field, got {geo_fields}")
        match = GEO.match(geo_fields[0].strip())
        if match is None:
            raise ValueError(f"{bank}: cannot read GEO from {geo_fields[0]!r}")
        geo = int(match.group(1))
        if geo == 0 and len(entries) == 1:
            continue
        if geo == 0:
            raise ValueError(f"{bank}: GEO=0 bank contains data; refusing to treat it as empty")
        if geo in by_geo:
            raise ValueError(f"Duplicate active GEO={geo} in {bank} and another bank")
        by_geo[geo] = [(f"tdc_geo[{geo}].{field}", value) for field, value in entries]
    return sorted(other + [item for geo in sorted(by_geo) for item in by_geo[geo]], key=lambda item: item[0])


def compare(original_path, new_path, max_differences=20):
    missing = object()
    original_count = new_count = compared = active_events = 0
    differences = []
    for old, new in zip_longest(iter_events(original_path, True),
                                iter_events(new_path, True), fillvalue=missing):
        if old is not missing:
            original_count += 1
        if new is not missing:
            new_count += 1
        if old is missing or new is missing:
            differences.append("One dump ended before the other")
            break
        event_old, fields_old = old
        event_new, fields_new = new
        if any(
            (match := GEO.fullmatch(value)) and int(match.group(1))
            for name, value in chain(fields_old, fields_new)
            if name in ("ts.subsystem_id", "scalers.n") or name.endswith((".board_id", ".geo"))
        ):
            active_events += 1
        if event_old != event_new and len(differences) < max_differences:
            differences.append(f"Event IDs differ: {event_old} vs {event_new}")
        try:
            a, b = canonical(fields_old), canonical(fields_new)
        except ValueError as error:
            if len(differences) < max_differences:
                differences.append(f"Event {event_old}: {error}")
            continue
        compared += min(len(a), len(b))
        if len(a) != len(b) and len(differences) < max_differences:
            differences.append(
                f"Event {event_old}: field counts differ: original={len(a)}, new={len(b)}")
        for i, (left, right) in enumerate(zip(a, b)):
            if left != right and len(differences) < max_differences:
                differences.append(
                    f"Event {event_old}, field {i+1}: original {left!r} != new {right!r}")
    if not original_count or not new_count:
        differences.append("No event headers found")
    if not active_events:
        differences.append("No FATIMA VME fields found")
    return differences, (original_count, new_count, compared, active_events)


def replay(reference, candidate, lmd, limit, max_differences):
    with TemporaryDirectory(prefix="s100-vme-replay-") as directory:
        paths, summaries = [], []
        for label, binary in (("reference", reference), ("candidate", candidate)):
            print(f"Replaying {limit:,} events with the {label} unpacker...", flush=True)
            target = Path(directory) / f"{label}.dump"
            with TemporaryFile(mode="w+t", encoding="utf-8", errors="replace") as dump:
                summaries.append(capture(binary, lmd, limit, dump, label))
                with target.open("w", encoding="utf-8") as filtered:
                    filtered.writelines(line for line in dump if line.startswith(("Event ", ".UNPACK.fatimavme.")))
            paths.append(target)
        for index, label in enumerate(("Input events", "Decoded events", "Unpack errors")):
            print(f"{label}: {summaries[0][index]} / {summaries[1][index]}")
        differences, counts = compare(*paths, max_differences)
        if summaries[0] != summaries[1]:
            differences.append("UCESB event or error totals differ")
        if counts[:2] != (limit, limit) or any(summary[0] != limit for summary in summaries):
            differences.append(f"Expected {limit} events from each unpacker")
        return differences, counts


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("reference", type=Path)
    parser.add_argument("geo_variant", type=Path)
    parser.add_argument("--lmd", type=Path, help="replay this file using two unpacker binaries")
    parser.add_argument("--max-events", type=int, default=25_000)
    parser.add_argument("--max-differences", type=int, default=20)
    args = parser.parse_args()
    try:
        if args.max_events <= 0:
            parser.error("--max-events must be positive")
        limit = max(1, args.max_differences)
        if args.lmd:
            differences, (old, new, fields, active) = replay(
                args.reference, args.geo_variant, args.lmd, args.max_events, limit)
        else:
            differences, (old, new, fields, active) = compare(args.reference, args.geo_variant, limit)
    except (OSError, ValueError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2
    print(f"Event headers: {old} reference / {new} GEO variant")
    print(f"Events with FATIMA VME fields: {active}")
    print(f"Comparable decoded fields: {fields}")
    if differences:
        for error in differences:
            print(f"DIFFERENCE: {error}")
        return 1
    print("PASS: all FATIMA VME fields match by V1290 physical GEO")
    return 0


if __name__ == "__main__":
    sys.exit(main())
