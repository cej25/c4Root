#!/usr/bin/env python3
"""Stage the UCESB-generated six-slot FATIMA VME header without installing it.

Build the production S100 unpacker first. The staged header contains the
client structures and item registration used by the S100 readers.
"""
import argparse
from pathlib import Path
import re
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
EXPERIMENT = ROOT / "unpack/exps/s100"
EXECUTABLE = EXPERIMENT / "s100"
STRUCTURE = "h101_fatimavme_s100"
CURRENT = ROOT / "c4source/fatima/ext_h101_fatimavme.h"
PRODUCTION = ROOT / "c4source/fatima/ext_h101_fatimavme_s100.h"


def validate_generated_header(text):
    """Examine native UCESB output, never substitute handwritten declarations."""
    if f"EXT_STR_{STRUCTURE}_onion" not in text:
        raise ValueError("UCESB output lacks FATIMA VME onion structure")
    if f"EXT_STR_{STRUCTURE}_ITEMS_INFO" not in text:
        raise ValueError("UCESB output lacks FATIMA VME layout/offset macro")
    start = text.find(f"typedef struct EXT_STR_{STRUCTURE}_onion_t")
    if start < 0:
        raise ValueError("UCESB output lacks onion typedef")
    end = text.find(f"EXT_STR_{STRUCTURE}_onion;", start)
    if end < 0:
        raise ValueError("UCESB output has an incomplete onion typedef")
    onion = text[start:end]
    dimensions = {}
    for name in ("qdc", "tdc"):
        match = re.search(r"\}\s*fatimavme_" + name + r"\[(\d+)\];", onion)
        if match is None:
            raise ValueError(f"UCESB onion has no fatimavme_{name} array")
        dimensions[name] = int(match.group(1))
        if dimensions[name] != 6:
            raise ValueError(
                f"UCESB onion fatimavme_{name} has {dimensions[name]} slots; expected six")
    return dimensions


def client_header(text):
    # c4Root registers through ITEMS_INFO. The standalone packed-offset table
    # is unused and alone accounts for several MiB of generated text.
    boundary = text.find("/********************************************************\n *\n * For internal use by the network data reader:")
    if boundary < 0:
        raise ValueError("UCESB output lacks the standalone layout boundary")
    guard = re.search(r"(?m)^#endif[^\n]*__GUARD_[^\n]+$", text[boundary:])
    if guard is None:
        raise ValueError("UCESB output lacks its closing include guard")
    return text[:boundary].rstrip() + "\n\n" + guard.group(0) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True,
                        help="destination for staged UCESB-generated header")
    parser.add_argument("--production", action="store_true", help=argparse.SUPPRESS)
    args = parser.parse_args()
    output = args.output.resolve()
    if output in (CURRENT.resolve(), PRODUCTION.resolve()):
        parser.error("refusing to overwrite the installed generated header")
    if not EXECUTABLE.is_file():
        parser.error(f"build {EXECUTABLE} first")
    if output.exists():
        parser.error(f"output already exists: {output}; choose a new filename")
    if not output.parent.is_dir():
        parser.error(f"output directory does not exist: {output.parent}")
    try:
        with tempfile.TemporaryDirectory(prefix="c4root-vme-header-") as staging:
            generated_path = Path(staging) / f"ext_{STRUCTURE}.h"
            command = [
                str(EXECUTABLE), "/dev/null",
                f"--ntuple=NOTRIGEVENTNO,UNPACK:fatimavme,STRUCT_HH,id={STRUCTURE},{generated_path.name}",
            ]
            print("UCESB:", " ".join(command), flush=True)
            result = subprocess.run(command, cwd=staging, check=False)
            if result.returncode:
                raise ValueError(f"native UCESB header generation failed: {result.returncode}")
            if not generated_path.is_file():
                raise ValueError("UCESB did not generate the requested header")
            content = generated_path.read_text()
            dimensions = validate_generated_header(content)
            output.write_text(client_header(content))
        print(f"STAGED: {output}")
        print(f"FATIMA VME structure capacity: QDC={dimensions['qdc']}, TDC={dimensions['tdc']}")
        return 0
    except (OSError, ValueError) as error:
        print(f"ERROR: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
