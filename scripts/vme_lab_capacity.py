#!/usr/bin/env python3
"""Check or update fixed six-slot FATIMA VME lab address matching.

Works on the *experimental* s100_vme_tdc_lab.spec, never on production s100.spec.
Configured installed GEO/board IDs must be represented in the six fixed slots.
Unused slots receive deterministic, non-colliding placeholder IDs in the
hardware-supported 5-bit address range (31, 30, ...). The user must regenerate
UCESB to apply address changes; this does not edit generated headers.
"""
import argparse
import difflib
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CAPACITY = 6
MAX_ADDRESS = 31
QDC = re.compile(
    r"(?P<lead>\bqdc\[(?P<slot>\d+)\]\s*=\s*VME_CAEN_V1751\(\s*board\s*=\s*)"
    r"(?P<addr>\d+)(?P<trail>\s*\)\s*;)"
)
TDC = re.compile(
    r"(?P<lead>\btdc\[(?P<slot>\d+)\]\s*=\s*VME_CAEN_V1290_GEO\(\s*geom_expected\s*=\s*)"
    r"(?P<addr>\d+)(?P<trail>\s*\)\s*;)"
)


def addresses(boards, label):
    if not isinstance(boards, list) or not boards:
        raise ValueError(f"{label}: expected a non-empty installed board list")
    if any(type(x) is not int or not 0 <= x <= MAX_ADDRESS for x in boards):
        raise ValueError(f"{label}: hardware IDs must be 0..{MAX_ADDRESS}")
    if len(boards) != len(set(boards)):
        raise ValueError(f"{label}: duplicate hardware IDs")
    if len(boards) > CAPACITY:
        raise ValueError(f"{label}: {len(boards)} installed modules exceed {CAPACITY} slots")
    return boards


def declarations(text, pattern, label):
    found = list(pattern.finditer(text))
    slots = [(int(m.group("slot")), int(m.group("addr"))) for m in found]
    if [slot for slot, _ in slots] != list(range(CAPACITY)):
        raise ValueError(f"{label}: expected exactly six consecutive slots, found {slots}")
    if any(not 0 <= address <= MAX_ADDRESS for _, address in slots):
        raise ValueError(f"{label}: declaration contains hardware ID outside 0..31")
    if len(set(addr for _, addr in slots)) != CAPACITY:
        raise ValueError(f"{label}: duplicate hardware IDs in unpacker")
    return slots


def checked(text, config):
    errors = []
    for label, pattern, configured in (
        ("V1751", QDC, addresses(config["v1751"]["boards"], "V1751")),
        ("V1290", TDC, addresses(config["v1290"]["boards"], "V1290")),
    ):
        try:
            installed = [address for _, address in declarations(text, pattern, label)]
            missing = sorted(set(configured) - set(installed))
            if missing:
                errors.append(f"{label}: installed hardware IDs not declared: {missing}")
        except ValueError as exc:
            errors.append(str(exc))
    return errors


def replacement_ids(current, required):
    """Preserve all currently declared required IDs in their slots.

    Replace only slots whose IDs are not installed. Keep spare IDs if they do
    not collide with required IDs; allocate other spares deterministically.
    """
    result = list(current)
    required_set = set(required)
    missing = [value for value in required if value not in result]
    replaceable = [i for i, value in enumerate(result) if value not in required_set]
    if len(missing) > len(replaceable):
        raise ValueError("Too few slots available for installed addresses")
    for slot, address in zip(replaceable, missing):
        result[slot] = address
    used = set(result)
    for slot in replaceable[len(missing):]:
        address = result[slot]
        # Existing spare values remain valid unless they now collide.
        if result.count(address) == 1:
            continue
        choices = (x for x in range(MAX_ADDRESS, -1, -1) if x not in used)
        chosen = next(choices, None)
        if chosen is None:
            raise ValueError("No free placeholder IDs")
        used.add(chosen)
        result[slot] = chosen
    return result


def repair(text, config):
    updated = text
    for label, pattern, required in (
        ("V1751", QDC, addresses(config["v1751"]["boards"], "V1751")),
        ("V1290", TDC, addresses(config["v1290"]["boards"], "V1290")),
    ):
        found = list(pattern.finditer(updated))
        # Handle a partially populated template without changing structure
        # definitions or removing anything outside the module declarations.
        current = [(int(m.group("slot")), int(m.group("addr"))) for m in found]
        if [i for i, _ in current] != list(range(len(current))) or len(current) > CAPACITY:
            raise ValueError(f"{label}: expected ordered contiguous module slots")
        if len({x for _, x in current}) != len(current):
            raise ValueError(f"{label}: duplicate hardware IDs in template")
        if any(addr > MAX_ADDRESS or addr < 0 for _, addr in current):
            raise ValueError(f"{label}: invalid module ID in template")
        original = [addr for _, addr in current]
        required_set = set(required)
        # Keep installed addresses already present, then fill empty slots.
        occupied = list(original)
        remaining = [x for x in required if x not in occupied]
        for i, current_id in enumerate(occupied):
            if not remaining:
                break
            if current_id not in required_set:
                occupied[i] = remaining.pop(0)
        occupied.extend(remaining)
        # Exactly six fixed slots, with safe placeholder GEO/board IDs.
        used = set(occupied)
        if len(used) != len(occupied):
            raise ValueError(f"{label}: duplicate addresses during allocation")
        for candidate in range(MAX_ADDRESS, -1, -1):
            if len(occupied) >= CAPACITY:
                break
            if candidate not in used:
                occupied.append(candidate)
                used.add(candidate)
        if len(occupied) != CAPACITY:
            raise ValueError(f"{label}: unable to allocate six unique IDs")
        # Construct a full declaration group by using the last existing line
        # as a textual template, replacing only slot and physical ID.
        if not found:
            raise ValueError(f"{label}: no declaration template found")
        edits = []
        for match, desired in zip(found, occupied):
            if int(match.group("addr")) != desired:
                edits.append((match.start("addr"), match.end("addr"), str(desired)))
        template = found[-1]
        additions = "".join(
            f"\n        {label_to_name(label)}[{slot}] = {label_to_function(label)}({label_to_parameter(label)}={occupied[slot]});"
            for slot in range(len(found), CAPACITY)
        )
        edits.append((template.end(), template.end(), additions))
        for first, last, value in sorted(edits, reverse=True):
            updated = updated[:first] + value + updated[last:]
    if checked(updated, config):
        raise ValueError("Generated declarations do not cover installed hardware")
    return updated


def label_to_name(label):
    return "qdc" if label == "V1751" else "tdc"


def label_to_function(label):
    return "VME_CAEN_V1751" if label == "V1751" else "VME_CAEN_V1290_GEO"


def label_to_parameter(label):
    return "board" if label == "V1751" else "geom_expected"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--experiment", default="s100", choices=["s100"])
    parser.add_argument("--check", action="store_true")
    actions = parser.add_mutually_exclusive_group()
    actions.add_argument("--dry-run", action="store_true")
    actions.add_argument("--fix", action="store_true")
    args = parser.parse_args()
    try:
        import yaml
        config_path = ROOT / "config" / args.experiment / "experiment.yaml"
        spec_path = ROOT / "unpack/exps" / args.experiment / f"{args.experiment}_vme_tdc_lab.spec"
        config = yaml.safe_load(config_path.read_text())["FATIMA_VME"]
        current = spec_path.read_text()
        errors = checked(current, config)
        if args.check or not (args.dry_run or args.fix):
            if errors:
                for error in errors:
                    print(f"WARNING: {error}")
                return 1
            print("OK: six V1751 and six V1290 slots cover installed hardware IDs")
            return 0
        desired = repair(current, config)
        if current == desired:
            print("OK: six-slot VME lab declarations already match installed hardware")
            return 0
        diff = difflib.unified_diff(
            current.splitlines(keepends=True), desired.splitlines(keepends=True),
            fromfile=str(spec_path), tofile="six-slot lab candidate")
        sys.stdout.writelines(diff)
        if args.dry_run:
            print("Dry run only. No files changed.")
            return 0
        spec_path.write_text(desired)
        print("Updated experimental VME spec only; rebuild s100_vme_tdc_lab to apply.")
        return 0
    except (ValueError, OSError, ImportError, KeyError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
