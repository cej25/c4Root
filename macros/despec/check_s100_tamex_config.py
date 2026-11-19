#!/usr/bin/env python3
"""Check that S100 TAMEX routing is supplied by experiment.yaml."""

import argparse
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[2]
CONFIG = ROOT / "config/s100/experiment.yaml"
SPEC = ROOT / "unpack/exps/s100/s100.spec"
sys.path.insert(0, str(ROOT / "scripts"))

from validate_experiment import check_s100_routing, read_yaml


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply", action="store_true",
                        help="Compatibility option. Rebuild S100 to apply routing changes.")
    args = parser.parse_args()
    try:
        config = read_yaml(CONFIG)
        issues = check_s100_routing(SPEC.read_text(), config)
        if issues:
            for issue in issues:
                print(f"ERROR: {issue}", file=sys.stderr)
            return 1
        for detector in ("FATIMA", "bPlast", "BGO"):
            route = config[detector]
            if route.get("digitiser") != "tamex" or route.get("version") != 4:
                raise ValueError(f"Unsupported electronics for {detector} (requires TAMEX4)")
            print(f"{detector}: EVENT {route['member']} -> {route['subevent']}, "
                  f"procid={route['procid']}, WR={hex(route['whiterabbit'])}")
        print("OK: S100 uses experiment.yaml for procids and White Rabbit IDs.")
        if args.apply:
            print("Rebuild the S100 unpacker to apply routing changes.")
        return 0
    except (KeyError, ValueError, OSError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
