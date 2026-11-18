#!/usr/bin/env python3
"""Check s100 TAMEX UCESB declarations against experiment.yaml.

--check never writes; --fix explicitly updates s100.spec then invokes its native
UCESB Makefile. Header generation is delegated entirely to UCESB.
"""
import argparse
import difflib
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / "config" / "s100" / "experiment.yaml"
SPEC = ROOT / "unpack" / "exps" / "s100" / "s100.spec"
UNPACK_DIR = SPEC.parent
SUBEVENTS = {
    "FATIMA": "fatima_tamex_subev",
    "bPlast": "bplast_subev",
    "BGO": "bgo_tamex_subevent",
}
BOARD = re.compile(
    r"^([ \\t]*)tamex\\[(\\d+)\\]\\s*=\\s*TAMEX4_SFP\\(\\s*sfp\\s*=\\s*(\\d+)\\s*,"
    r"\\s*card\\s*=\\s*(\\d+)\\s*\\)\\s*;[ \\t]*$", re.M
)


def load_config():
    try:
        import yaml
    except ImportError as exc:
        raise ValueError("PyYAML is required: python3 -m pip install pyyaml") from exc
    data = yaml.safe_load(CONFIG.read_text())
    if not isinstance(data, dict):
        raise ValueError("experiment.yaml must contain a detector mapping")
    for detector in SUBEVENTS:
        item = data.get(detector)
        if not isinstance(item, dict):
            raise ValueError(f"Missing configuration for {detector}")
        if item.get("digitiser") != "tamex" or item.get("version") != 4:
            raise ValueError(f"{detector}: this initial synchroniser supports TAMEX4 only")
        boards = item.get("boards")
        if (not isinstance(boards, list) or not boards or
            any(type(x) is not int or x < 0 or x > 65535 for x in boards) or
            len(set(boards)) != len(boards)):
            raise ValueError(f"{detector}: boards must be a nonempty list of distinct integers")
        # UCESB board arrays must be densely indexed; physical card IDs may vary.
        if len(boards) > 256:
            raise ValueError(f"{detector}: unreasonable number of boards")
        if type(item.get("sfp")) is not int or not 0 <= item["sfp"] <= 255:
            raise ValueError(f"{detector}: invalid sfp")
        if type(item.get("procid")) is not int or not 0 <= item["procid"] <= 65535:
            raise ValueError(f"{detector}: invalid procid")
        if type(item.get("whiterabbit")) is not int:
            raise ValueError(f"{detector}: invalid whiterabbit id")
    procs = [data[d]["procid"] for d in SUBEVENTS]
    if len(set(procs)) != len(procs):
        raise ValueError("Duplicate TAMEX procids")
    return data


def subevent(text, name):
    # Locate a whole UCESB SUBEVENT using balanced braces, not a global regex
    # that might inadvertently touch another detector's declarations.
    match = re.search(r"\\bSUBEVENT\\(\\s*" + re.escape(name) + r"\\s*\\)\\s*\\{", text)
    if not match:
        raise ValueError(f"Cannot find SUBEVENT({name}) in s100.spec")
    depth = 1
    i = match.end()
    while i < len(text) and depth:
        depth += (text[i] == "{") - (text[i] == "}")
        i += 1
    if depth:
        raise ValueError(f"Unbalanced SUBEVENT({name}) braces")
    return match.start(), i, text[match.start():i]


def regenerate_declarations(source, cfg):
    updated = source
    for detector, name in SUBEVENTS.items():
        start, end, block = subevent(updated, name)
        item = cfg[detector]
        entries = list(BOARD.finditer(block))
        if not entries:
            raise ValueError(f"{name}: cannot locate existing TAMEX4_SFP declarations")
        if [int(m.group(2)) for m in entries] != list(range(len(entries))):
            raise ValueError(f"{name}: existing logical TAMEX board indices are not consecutive")
        # Refuse to rewrite unrelated C++ / parsing grammar in the subevent.
        between = block[entries[0].end():entries[-1].start()]
        if BOARD.sub("", block[entries[0].start():entries[-1].end()]).strip():
            raise ValueError(f"{name}: TAMEX declarations contain non-board text; edit manually")
        indent = entries[0].group(1)
        replacement = "\\n".join(
            f"{indent}tamex[{index}] = TAMEX4_SFP(sfp = {item['sfp']}, card = {card});"
            for index, card in enumerate(item["boards"])
        )
        block = block[:entries[0].start()] + replacement + block[entries[-1].end():]
        # Procids and WR IDs can change the decoding interpretation:
        # validate these separately rather than silently rewriting all grammar.
        old = updated[start:end]
        if "TIMESTAMP_WHITERABBIT_EXTENDED" in old:
            wr = re.search(r"TIMESTAMP_WHITERABBIT_EXTENDED\\(id\\s*=\\s*(0x[0-9a-fA-F]+|\\d+)\\)", old)
        else:
            wr = re.search(r"TIMESTAMP_WHITERABBIT\\(id\\s*=\\s*(0x[0-9a-fA-F]+|\\d+)\\)", old)
        if not wr or int(wr.group(1), 0) != item["whiterabbit"]:
            raise ValueError(f"{detector}: White Rabbit ID in spec does not match experiment.yaml")
        updated = updated[:start] + block + updated[end:]
        event = re.search(
            r"\\b" + ("fatima" if detector == "FATIMA" else "bplast" if detector == "bPlast" else "bgo") +
            r"\\s*=\\s*" + re.escape(name) + r"\\([^;]*?procid\\s*=\\s*(\\d+)",
            updated,
        )
        if not event or int(event.group(1)) != item["procid"]:
            raise ValueError(f"{detector}: procid in EVENT does not match experiment.yaml")
    return updated


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--experiment", default="s100", choices=["s100"])
    action = parser.add_mutually_exclusive_group()
    action.add_argument("--check", action="store_true", help="check only (default)")
    action.add_argument("--fix", action="store_true", help="explicitly update spec and invoke UCESB make")
    action.add_argument("--dry-run", action="store_true", help="show diff, make no changes")
    args = parser.parse_args()
    try:
        desired = regenerate_declarations(SPEC.read_text(), load_config())
        current = SPEC.read_text()
    except (ValueError, OSError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2

    if current == desired:
        print("OK: s100 TAMEX declarations match experiment.yaml")
        return 0

    print("WARNING: s100 TAMEX unpacker declarations disagree with experiment.yaml")
    diff = difflib.unified_diff(current.splitlines(keepends=True),
                                desired.splitlines(keepends=True),
                                fromfile=str(SPEC), tofile="expected s100.spec")
    if args.dry_run or args.fix:
        sys.stdout.writelines(diff)
    if not args.fix:
        print("To regenerate with UCESB: python3 scripts/sync_experiment.py --experiment s100 --fix")
        return 1

    # Only touch the known source declaration file after all checks have passed.
    SPEC.write_text(desired)
    print("Updated s100.spec; invoking native UCESB make (headers are generated by UCESB).")
    result = subprocess.run(["make", "-C", str(UNPACK_DIR), "s100"], check=False)
    if result.returncode:
        print("ERROR: UCESB generation/build failed; inspect output. Spec changes remain visible.", file=sys.stderr)
        return result.returncode
    print("UCESB regeneration finished. Rebuild c4Root against the updated generated headers.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
