#!/usr/bin/env python3
"""Check S100 configuration or rebuild the unpacker and refresh its TAMEX headers."""

import argparse
import os
from pathlib import Path
import subprocess
import sys
import tempfile

from validate_experiment import (
    MAX_BOARDS, ROOT, S100_TAMEX_MEMBERS, board_list, check_s100_routing,
    compiled_tamex_slots, read_array_size, read_yaml, s100_routes, validate,
)

CONFIG = ROOT / "config/s100/experiment.yaml"
UNPACK_DIR = ROOT / "unpack/exps/s100"
SPEC = UNPACK_DIR / "s100.spec"


def installed_layouts(config):
    routes = s100_routes(config)
    layouts = {}
    for member in sorted(S100_TAMEX_MEMBERS):
        detector, item = routes[member]
        slots = compiled_tamex_slots(detector, item)
        boards = board_list(item.get("boards"), detector, MAX_BOARDS["tamex"])
        sfp = item.get("sfp")
        if type(sfp) is not int or not 0 <= sfp <= 15:
            raise ValueError(f"{detector}: invalid installed SFP")
        missing = sorted({(sfp, card) for card in boards} - set(slots))
        if missing:
            raise ValueError(f"{detector}: add unsupported installed addresses {missing} to compiled_slots")
        layouts[member] = slots
    return layouts


def stale_headers(layouts, root=ROOT):
    stale = {}
    for member, slots in layouts.items():
        target = root / f"c4source/{member}/ext_h101_{member}.h"
        try:
            capacity = read_array_size(target.read_text(), f"{member}_tamex")
        except (FileNotFoundError, ValueError):
            capacity = None
        if capacity != len(slots):
            stale[member] = target
    return stale


def regenerate_headers(layouts, targets):
    # Validate every native header before replacing any checked-in header.
    staged = {}
    with tempfile.TemporaryDirectory(prefix="c4root-ucesb-") as directory:
        for member, target in targets.items():
            command = [
                str(UNPACK_DIR / "s100"), "/dev/null",
                f"--ntuple=NOTRIGEVENTNO,UNPACK:{member},STRUCT_HH,id=h101_{member},{target.name}",
            ]
            subprocess.run(command, cwd=directory, check=True)
            generated = (Path(directory) / target.name).read_bytes()
            layout = generated.decode()
            if (read_array_size(layout, f"{member}_tamex") != len(layouts[member])
                    or f"EXT_STR_h101_{member}_onion" not in layout):
                raise ValueError(f"UCESB generated an unexpected layout for {member}")
            staged[target] = generated
    for target, generated in staged.items():
        with tempfile.NamedTemporaryFile(mode="wb", dir=target.parent, delete=False) as output:
            temporary = Path(output.name)
            try:
                output.write(generated)
                output.close()
                temporary.chmod(0o644)
                os.replace(temporary, target)
            finally:
                temporary.unlink(missing_ok=True)
        print(f"Updated {target.relative_to(ROOT)}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--experiment", default="s100", choices=["s100"])
    action = parser.add_mutually_exclusive_group()
    action.add_argument("--check", action="store_true", help="check only (default)")
    action.add_argument("--fix", action="store_true", help="rebuild S100 and refresh stale TAMEX headers")
    action.add_argument("--dry-run", action="store_true", help="preview the compiled layouts and header updates")
    args = parser.parse_args()
    try:
        if not args.fix and not args.dry_run:
            warnings, notes = validate(args.experiment)
            for note in notes:
                print(note)
            for warning in warnings:
                print(f"WARNING: {warning}")
            if warnings:
                return 1
            print(f"OK: {args.experiment} installed boards fit the current UCESB layout")
            return 0

        config = read_yaml(CONFIG)
        layouts = installed_layouts(config)
        issues = check_s100_routing(SPEC.read_text(), config)
        if issues:
            raise ValueError("\n".join(issues))
        targets = stale_headers(layouts)
        for member, slots in layouts.items():
            print(f"{member}: {slots}")
        for target in targets.values():
            print(f"Header to regenerate: {target.relative_to(ROOT)}")
        if args.dry_run:
            return 0
        subprocess.run(["make", "-C", str(UNPACK_DIR), "s100"], check=True)
        regenerate_headers(layouts, targets)
        if not targets:
            print("The TAMEX header dimensions already match the configured layout.")
        return 0
    except subprocess.CalledProcessError as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return exc.returncode
    except (ValueError, OSError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
