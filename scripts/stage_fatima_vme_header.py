#!/usr/bin/env python3
"""Stage the UCESB-generated six-slot FATIMA VME header without installing it.

The default input is the production S100 unpacker. Any unpacker that exports
the same numbered six-slot FATIMA VME layout can supply the header.
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
STRUCTURE = "h101_fatimavme"
CLIENT_HEADER = ROOT / "c4source/fatima/ext_h101_fatimavme.h"


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


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, required=True,
                        help="destination for staged UCESB-generated header")
    parser.add_argument("--unpacker", type=Path, default=EXECUTABLE,
                        help="UCESB executable exporting six FATIMA VME slots per module type (default: S100)")
    parser.add_argument("--production", action="store_true", help=argparse.SUPPRESS)
    args = parser.parse_args()
    output = args.output.resolve()
    unpacker = args.unpacker.resolve()
    if output == CLIENT_HEADER.resolve():
        parser.error("refusing to overwrite the installed generated header")
    if not unpacker.is_file():
        parser.error(f"unpacker does not exist: {unpacker}")
    if output.exists():
        parser.error(f"output already exists: {output}; choose a new filename")
    if not output.parent.is_dir():
        parser.error(f"output directory does not exist: {output.parent}")
    try:
        with tempfile.TemporaryDirectory(prefix="fatima-vme-header-") as staging:
            generated_path = Path(staging) / f"ext_{STRUCTURE}.h"
            command = [
                str(unpacker), "/dev/null",
                f"--ntuple=NOTRIGEVENTNO,UNPACK:fatimavme,STRUCT_HH,id={STRUCTURE},{generated_path.name}",
            ]
            print("UCESB:", " ".join(command), flush=True)
            result = subprocess.run(command, cwd=staging, check=False)
            if result.returncode:
                raise ValueError(f"native UCESB header generation failed: {result.returncode}")
            if not generated_path.is_file():
                raise ValueError("UCESB did not generate the requested header")
            content = generated_path.read_bytes()
            dimensions = validate_generated_header(content.decode())
            with output.open("xb") as header:
                header.write(content)
        print(f"STAGED: {output}")
        print(f"FATIMA VME structure capacity: QDC={dimensions['qdc']}, TDC={dimensions['tdc']}")
        return 0
    except (OSError, ValueError) as error:
        print(f"ERROR: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
