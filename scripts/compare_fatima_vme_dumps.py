#!/usr/bin/env python3
"""Compare UCESB --dump=UNPACK FATIMA VME fields from production and lab.

Normalise only the intentionally changed V1751 bank paths:
  .UNPACK.fatimavme.qdc1.* -> .UNPACK.fatimavme.qdc[0].*
  ...
  .UNPACK.fatimavme.qdc5.* -> .UNPACK.fatimavme.qdc[4].*

All values, ordering, presence, and V1290 fields must match exactly.
Logs must be captured with the same event limit and input LMD.
"""
import argparse
import re
import sys
from pathlib import Path

EVENT = re.compile(r"^Event\s+(\d+)\b")
FIELD = re.compile(r"^\s*\.UNPACK\.fatimavme\.(\S+?):\s*(.*?)\s*$")
QDC = re.compile(r"^qdc([1-9]\d*)(?=\.|\[|$)")


def parse(path, normalise=False):
    events = []
    current = None
    fields = []
    with path.open(encoding="utf-8", errors="replace") as stream:
        for lineno, line in enumerate(stream, 1):
            line = line.rstrip("\r\n")
            event = EVENT.match(line)
            if event:
                if current is not None:
                    events.append((current, fields))
                current, fields = int(event.group(1)), []
                continue
            if ".UNPACK.fatimavme." not in line:
                continue
            match = FIELD.match(line)
            if match is None:
                raise ValueError(f"{path}:{lineno}: unrecognised FATIMA VME field: {line}")
            if current is None:
                raise ValueError(f"{path}:{lineno}: FATIMA VME data before first event")
            name, value = match.groups()
            if normalise:
                name = QDC.sub(lambda m: f"qdc[{int(m.group(1))-1}]", name, count=1)
            fields.append((name, value))
    if current is not None:
        events.append((current, fields))
    return events


def compare(original, lab, max_differences=20):
    if not original or not lab:
        return ["no event headers found in one or both logs"], 0, 0
    differences = []
    if len(original) != len(lab):
        differences.append(f"Event count differs: original={len(original)}, lab={len(lab)}")
    compared = 0
    with_data = 0
    for index, (a, b) in enumerate(zip(original, lab), 1):
        event_a, fields_a = a
        event_b, fields_b = b
        if event_a != event_b:
            differences.append(f"Event #{index}: event IDs differ: {event_a} vs {event_b}")
        if fields_a or fields_b:
            with_data += 1
        if len(fields_a) != len(fields_b):
            differences.append(
                f"Event {event_a}: FATIMA VME field counts differ: "
                f"original={len(fields_a)}, lab={len(fields_b)}")
        for position, (field_a, field_b) in enumerate(zip(fields_a, fields_b), 1):
            compared += 1
            if field_a != field_b:
                differences.append(
                    f"Event {event_a}, field #{position}: "
                    f"original {field_a!r} != lab {field_b!r}")
            if len(differences) >= max_differences:
                return differences, compared, with_data
        if len(differences) >= max_differences:
            return differences, compared, with_data
    if with_data == 0:
        differences.append("No decoded FATIMA VME fields appeared in either log; cannot validate QDC/TDC")
    return differences, compared, with_data


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("original", type=Path)
    parser.add_argument("experimental", type=Path)
    parser.add_argument("--max-differences", type=int, default=20)
    args = parser.parse_args()
    try:
        original = parse(args.original, normalise=True)
        lab = parse(args.experimental)
        differences, compared, with_data = compare(
            original, lab, max(1, args.max_differences))
    except (OSError, ValueError) as error:
        print(f"ERROR: {error}", file=sys.stderr)
        return 2
    print(f"Event headers: {len(original)} original / {len(lab)} experimental")
    print(f"Events containing FATIMA VME fields: {with_data}")
    print(f"Compared FATIMA VME fields: {compared}")
    if differences:
        print(f"FAIL: {len(differences)} difference(s) shown:")
        for difference in differences:
            print(f"  {difference}")
        return 1
    print("PASS: all decoded FATIMA VME fields match after QDC bank-name normalisation")
    return 0


if __name__ == "__main__":
    sys.exit(main())
