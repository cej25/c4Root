#!/usr/bin/env python3
"""Validate a named experiment; optionally expand s100 TAMEX capacity using UCESB.

--check validates the installed layout; --fix explicitly expands TAMEX to 12 cards,\nupdates s100.spec then invokes its native
UCESB Makefile. Header generation is delegated entirely to UCESB.
"""
import argparse
import difflib
import re
import os
import subprocess
import tempfile
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
CONFIG = ROOT / "config" / "s100" / "experiment.yaml"
SPEC = ROOT / "unpack" / "exps" / "s100" / "s100.spec"
UNPACK_DIR = SPEC.parent
HEADERS = {
    "FATIMA": ROOT / "c4source/fatima/ext_h101_fatima.h",
    "bPlast": ROOT / "c4source/bplast/ext_h101_bplast.h",
    "BGO": ROOT / "c4source/bgo/ext_h101_bgo.h",
}
HEADER_MEMBERS = {"FATIMA": "fatima_tamex", "bPlast": "bplast_tamex", "BGO": "bgo_tamex"}
SUBEVENTS = {
    "FATIMA": "fatima_tamex_subev",
    "bPlast": "bplast_subev",
    "BGO": "bgo_tamex_subevent",
}
BOARD = re.compile(
    r"^([ \t]*)tamex\[(\d+)\]\s*=\s*TAMEX4_SFP\(\s*sfp\s*=\s*(\d+)\s*,"
    r"\s*card\s*=\s*(\d+)\s*\)\s*;[ \t]*$", re.M
)


def load_config():
    from validate_experiment import read_yaml, wr_ids

    data = read_yaml(CONFIG)
    wr_ids(data)
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
    procs = [data[d]["procid"] for d in SUBEVENTS]
    if len(set(procs)) != len(procs):
        raise ValueError("Duplicate TAMEX procids")
    return data


def subevent(text, name):
    # Locate a whole UCESB SUBEVENT using balanced braces, not a global regex
    # that might inadvertently touch another detector's declarations.
    match = re.search(r"\bSUBEVENT\(\s*" + re.escape(name) + r"\s*\)\s*\{", text)
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
        existing = [(int(m.group(2)), int(m.group(3)), int(m.group(4))) for m in entries]
        expected = [(index, item["sfp"], card) for index, card in enumerate(item["boards"])]
        if existing != expected:
            # Refuse to rewrite unrelated C++ / parsing grammar in the subevent.
            if BOARD.sub("", block[entries[0].start():entries[-1].end()]).strip():
                raise ValueError(f"{name}: TAMEX declarations contain non-board text; edit manually")
            indent = entries[0].group(1)
            replacement = "\n".join(
                f"{indent}tamex[{index}] = TAMEX4_SFP(sfp = {item['sfp']}, card = {card});"
                for index, card in enumerate(item["boards"])
            )
            block = block[:entries[0].start()] + replacement + block[entries[-1].end():]
        # White Rabbit IDs are generated from YAML by the unpacker build.
        updated = updated[:start] + block + updated[end:]
        event = re.search(
            r"\b" + ("fatima" if detector == "FATIMA" else "bplast" if detector == "bPlast" else "bgo") +
            r"\s*=\s*" + re.escape(name) + r"\([^;]*?procid\s*=\s*(\d+)",
            updated,
        )
        if not event or int(event.group(1)) != item["procid"]:
            raise ValueError(f"{detector}: procid in EVENT does not match experiment.yaml")
    return updated



def expand_vme_capacity(source, config):
    """Expand the s100 VME optional bank declarations to six slots per model."""
    item = config.get("FATIMA_VME", {})
    installed = set(item.get("v1751", {}).get("boards", []))
    if not installed.issubset(set(range(6, 12))):
        raise ValueError("FATIMA_VME: unsupported nonstandard V1751 board IDs")
    if len(item.get("v1290", {}).get("boards", [])) > 6:
        raise ValueError("FATIMA_VME: too many V1290 boards")
    start, end, block = subevent(source, "fatima_vme_subev")
    qdc = list(re.finditer(
        r"select\s+optional\s*\{\s*qdc(\d+)\s*=\s*VME_CAEN_V1751\(\s*board\s*=\s*(\d+)\s*\)\s*;\s*\}[ \t]*;?",
        block))
    tdc = list(re.finditer(
        r"select\s+optional\s*\{\s*tdc(\d+)\s*=\s*VME_CAEN_V1290_N\(\s*\)\s*;\s*\}[ \t]*;?",
        block))
    if not qdc or not tdc:
        raise ValueError("Missing existing s100 VME declarations")
    if [int(m.group(1)) for m in qdc] != list(range(1, len(qdc) + 1)):
        raise ValueError("Nonconsecutive V1751 slot indices")
    if [int(m.group(2)) for m in qdc] != list(range(6, 6 + len(qdc))):
        raise ValueError("Unexpected existing V1751 board IDs")
    if [int(m.group(1)) for m in tdc] != list(range(1, len(tdc) + 1)):
        raise ValueError("Nonconsecutive V1290 slot indices")
    if len(qdc) > 6 or len(tdc) > 6:
        raise ValueError("VME capacity already exceeds six slots")
    additions = []
    if len(qdc) < 6:
        new = "".join(
            f"\n    select optional {{ qdc{n} = VME_CAEN_V1751(board={n + 5}); }}\n"
            for n in range(len(qdc) + 1, 7))
        additions.append((qdc[-1].end(), new))
    if len(tdc) < 6:
        new = "".join(
            f"\n    select optional {{ tdc{n} = VME_CAEN_V1290_N(); }}\n"
            for n in range(len(tdc) + 1, 7))
        additions.append((tdc[-1].end(), new))
    for pos, addition in sorted(additions, reverse=True):
        block = block[:pos] + addition + block[pos:]
    return source[:start] + block + source[end:]


def stale_headers(config):
    problems = []
    for detector, path in HEADERS.items():
        try:
            source = path.read_text()
        except OSError as exc:
            problems.append(f"{path}: {exc}")
            continue
        match = re.search(
            r"\b" + HEADER_MEMBERS[detector] + r"\[(\d+)\]",
            source,
        )
        if not match:
            problems.append(f"{path}: TAMEX array not found")
        elif int(match.group(1)) != len(config[detector]["boards"]):
            problems.append(
                f"{path}: generated array has {match.group(1)} boards, "
                f"experiment.yaml requires {len(config[detector]['boards'])}"
            )
    vme_header = ROOT / "c4source/fatima/ext_h101_fatimavme.h"
    try:
        generated = vme_header.read_text()
        for name in ("fatimavme_qdc", "fatimavme_tdc"):
            match = re.search(r"\b" + name + r"\[(\d+)\]", generated)
            if not match or int(match.group(1)) != 6:
                problems.append(f"{vme_header}: {name} is not six slots")
    except OSError as exc:
        problems.append(f"{vme_header}: {exc}")
    return problems


def regenerate_headers(config):
    """Use UCESB itself for each subevent header; never write header definitions."""
    unpacker = UNPACK_DIR / "s100"
    if not unpacker.is_file():
        raise ValueError(f"UCESB unpacker executable not found: {unpacker}")
    staged = {}
    with tempfile.TemporaryDirectory(prefix="c4root-ucesb-") as directory:
        directory = Path(directory)
        for detector, target in HEADERS.items():
            member = {"FATIMA": "fatima", "bPlast": "bplast", "BGO": "bgo"}[detector]
            output = directory / target.name
            # UCESB's native STRUCT_HH generator selects the named UNPACK
            # subevent and uses id= for its exported C structure names.
            command = [
                str(unpacker),
                "/dev/null",
                f"--ntuple=UNPACK:{member},STRUCT_HH,id=h101_{member},{output}",
            ]
            print("UCESB:", " ".join(command), flush=True)
            result = subprocess.run(command, cwd=str(UNPACK_DIR), check=False)
            if result.returncode:
                raise ValueError(
                    f"UCESB failed generating {target.name} (exit {result.returncode})"
                )
            if not output.is_file():
                raise ValueError(f"UCESB did not produce {output}")
            generated = output.read_text()
            expected_name = HEADER_MEMBERS[detector]
            match = re.search(r"\b" + expected_name + r"\[(\d+)\]", generated)
            if not match or int(match.group(1)) != len(config[detector]["boards"]):
                raise ValueError(
                    f"UCESB generated an unexpected {expected_name} board layout "
                    f"for {detector}; refusing to install headers"
                )
            if f"EXT_STR_h101_{member}_onion" not in generated:
                raise ValueError(
                    f"UCESB generated header lacks EXT_STR_h101_{member}_onion"
                )
            staged[target] = generated
        # UCESB also owns the FATIMA VME structure-generation step.
        target = ROOT / "c4source/fatima/ext_h101_fatimavme.h"
        output = directory / target.name
        command = [
            str(unpacker), "/dev/null",
            f"--ntuple=UNPACK:fatimavme,STRUCT_HH,id=h101_fatimavme,{output}",
        ]
        print("UCESB:", " ".join(command), flush=True)
        result = subprocess.run(command, cwd=str(UNPACK_DIR), check=False)
        if result.returncode or not output.is_file():
            raise ValueError("UCESB failed generating FATIMA VME header")
        generated = output.read_text()
        for name in ("fatimavme_qdc", "fatimavme_tdc"):
            match = re.search(r"\b" + name + r"\[(\d+)\]", generated)
            if not match or int(match.group(1)) != 6:
                raise ValueError(f"UCESB generated unexpected {name} dimensions")
        if "EXT_STR_h101_fatimavme_onion" not in generated:
            raise ValueError("UCESB-generated FATIMA VME onion structure not found")
        staged[target] = generated
        # Install only once every UCESB invocation and structural check succeeds.
        # Use same-directory temporary files and atomic replacement.
        updated = []
        for target, generated in staged.items():
            if target.is_file() and target.read_text() == generated:
                continue
            temporary = target.with_name(target.name + ".sync-tmp")
            try:
                temporary.write_text(generated)
                os.replace(temporary, target)
            finally:
                temporary.unlink(missing_ok=True)
            updated.append(str(target.relative_to(ROOT)))
        for item in updated:
            print("Updated UCESB-generated:", item)
        if not updated:
            print("UCESB-generated headers already match")
    return updated


def target_capacity_config(config):
    """Explicit repair builds a reusable 12-slot TAMEX layout, not the installed count."""
    target = {name: dict(item) for name, item in config.items()}
    for detector in SUBEVENTS:
        actual = set(target[detector]["boards"])
        supported = set(range(12))
        if not actual.issubset(supported):
            raise ValueError(
                f"{detector}: physical cards {sorted(actual - supported)} are outside "
                "the standard 0-11 capacity; a custom UCESB layout is required"
            )
        target[detector]["boards"] = list(range(12))
    return target


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--experiment", default="s100", choices=["s100"])
    action = parser.add_mutually_exclusive_group()
    action.add_argument("--check", action="store_true", help="check only (default)")
    action.add_argument("--fix", action="store_true", help="explicitly update spec and invoke UCESB make")
    action.add_argument("--dry-run", action="store_true", help="show diff, make no changes")
    args = parser.parse_args()
    # The default check validates installed addresses against current capacity.
    # A smaller-but-sufficient compiled layout is not a mismatch.
    if args.check or (not args.fix and not args.dry_run):
        from validate_experiment import validate
        try:
            warnings, notes = validate(args.experiment)
        except (ValueError, OSError, ImportError) as exc:
            print(f"ERROR: {exc}", file=sys.stderr)
            return 2
        for note in notes:
            print(note)
        for warning in warnings:
            print(f"WARNING: {warning}")
        if warnings:
            print("To expand the supported TAMEX card range to 12, run --fix explicitly.")
            return 1
        print(f"OK: {args.experiment} installed boards fit the current UCESB layout")
        return 0

    try:
        config = target_capacity_config(load_config())
        current = SPEC.read_text()
        desired = expand_vme_capacity(regenerate_declarations(current, config), config)
        header_issues = stale_headers(config)
    except (ValueError, OSError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2

    if current == desired and not header_issues:
        print("OK: s100 TAMEX unpacker already supports the standard 12-slot layout")
        return 0

    if current != desired:
        print("The UCESB specification needs expansion to 12 TAMEX cards per subevent.")
    for issue in header_issues:
        print(f"Structure header: {issue}")
    diff = difflib.unified_diff(current.splitlines(keepends=True),
                                desired.splitlines(keepends=True),
                                fromfile=str(SPEC), tofile="expected s100.spec")
    sys.stdout.writelines(diff)
    if args.dry_run:
        print("Dry run only. No files were changed.")
        return 0

    # Only touch the known source declaration file after all checks have passed.
    if current != desired:
        SPEC.write_text(desired)
        print("Updated s100.spec")
    print("Invoking native UCESB make to regenerate the unpacker and generated structures.")
    result = subprocess.run(["make", "-C", str(UNPACK_DIR), "s100"], check=False)
    if result.returncode:
        print("ERROR: UCESB generation/build failed; inspect output. Spec changes remain visible.", file=sys.stderr)
        return result.returncode
    try:
        regenerate_headers(config)
    except (ValueError, OSError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2
    remaining = stale_headers(config)
    if remaining:
        for issue in remaining:
            print(f"ERROR: generated header verification failed: {issue}", file=sys.stderr)
        return 2
    print("UCESB regeneration complete; rebuild c4Root against the regenerated headers.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
