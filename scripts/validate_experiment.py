#!/usr/bin/env python3
"""Validate one experiment's hardware against its UCESB spec and generated headers.

This tool is read-only and independent of the c4Root CMake build.
Configured installed boards may be a strict subset of unpacker capacity.
"""
import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MAX_BOARDS = {"tamex": 12, "v1751": 6, "v1290": 6}
TAMEX = re.compile(r"\btamex\[(\d+)\]\s*=\s*TAMEX4_SFP\(\s*sfp\s*=\s*(\d+)\s*,\s*card\s*=\s*(\d+)\s*\)")
V1751 = re.compile(r"\bqdc(\d+)\s*=\s*VME_CAEN_V1751\(\s*board\s*=\s*(\d+)\s*\)")
V1290 = re.compile(r"\btdc(\d+)\s*=\s*VME_CAEN_V1290_N\(\s*\)")
MEMBER = {"fatima": "fatima", "bplast": "bplast", "bgo": "bgo", "fatimavme": "fatimavme"}

S100_WR_INCLUDE = "s100_whiterabbit.generated.spec"
S100_WR_MEMBERS = {"aida", "beammonitor", "bgo", "bplast", "fatima", "fatimavme", "frstpat", "germanium"}
WR_ARGUMENT = re.compile(
    r"\b(?:TIMESTAMP_WHITERABBIT\(\s*id\s*=\s*|S100_TAMEX_PAYLOAD\(\s*)(\w+)(?=\s*[,)])"
)


def read_yaml(path):
    try:
        import yaml
    except ImportError as exc:
        raise ValueError("PyYAML is required. Install it with python3 -m pip install PyYAML.") from exc
    try:
        data = yaml.safe_load(path.read_text())
    except yaml.YAMLError as exc:
        raise ValueError(f"{path}: {exc}") from exc
    if not isinstance(data, dict):
        raise ValueError(f"{path}: expected a detector mapping")
    return data


def wr_symbol(member):
    return f"S100_WR_{member.upper()}"


def wr_ids(configuration):
    ids = {}
    for detector, item in configuration.items():
        if not isinstance(item, dict) or "whiterabbit" not in item:
            continue
        member = item.get("member")
        if not isinstance(member, str) or not re.fullmatch(r"[a-z][a-z0-9_]*", member):
            raise ValueError(f"{detector}: invalid White Rabbit EVENT member")
        if member in ids:
            raise ValueError(f"{detector}: duplicate White Rabbit member {member}")
        wr = item["whiterabbit"]
        if type(wr) is not int or not 0 <= wr <= 0x1fff:
            raise ValueError(f"{detector}: whiterabbit must be an integer in 0x0–0x1fff")
        ids[member] = wr
    missing = S100_WR_MEMBERS - ids.keys()
    if missing:
        raise ValueError(f"Missing White Rabbit IDs for {', '.join(sorted(missing))}")
    return ids


def read_subevent(spec, name):
    match = re.search(r"\bSUBEVENT\(\s*" + re.escape(name) + r"\s*\)\s*\{", spec)
    if not match:
        raise ValueError(f"UCESB subevent {name} not found")
    depth, pos = 1, match.end()
    while pos < len(spec) and depth:
        if spec[pos] == "{":
            depth += 1
        elif spec[pos] == "}":
            depth -= 1
        pos += 1
    if depth:
        raise ValueError(f"Unclosed UCESB subevent {name}")
    return spec[match.end():pos - 1]


def read_array_size(header, member):
    match = re.search(r"\b" + re.escape(member) + r"\[(\d+)\]", header)
    if not match:
        raise ValueError(f"Generated UCESB array {member} not found")
    return int(match.group(1))


def board_list(value, name, maximum):
    if not isinstance(value, list) or not value:
        raise ValueError(f"{name}: expected a nonempty board list")
    if any(type(board) is not int or board < 0 or board > 65535 for board in value):
        raise ValueError(f"{name}: board IDs must be nonnegative integers")
    if len(value) != len(set(value)):
        raise ValueError(f"{name}: duplicate board IDs")
    if len(value) > maximum:
        raise ValueError(f"{name}: {len(value)} installed boards exceeds the policy limit of {maximum}")
    return value


def validate(experiment, root=ROOT):
    config_file = root / "config" / experiment / "experiment.yaml"
    spec_file = root / "unpack" / "exps" / experiment / f"{experiment}.spec"
    if not config_file.is_file() or not spec_file.is_file():
        raise ValueError(f"Cannot find experiment.yaml and unpacker spec for {experiment}")
    configuration = read_yaml(config_file)
    spec = spec_file.read_text()
    yaml_wr = experiment == "s100"
    if yaml_wr:
        wr_ids(configuration)
        if f'#include "{S100_WR_INCLUDE}"' not in spec:
            raise ValueError(f"Spec must include {S100_WR_INCLUDE}")
    warnings, notes = [], []
    seen_procs = {}
    for detector, item in configuration.items():
        if not isinstance(item, dict):
            continue
        digitiser = item.get("digitiser")
        if digitiser not in ("tamex", "vme") and not (yaml_wr and "whiterabbit" in item):
            continue
        subevent = item.get("subevent")
        member = item.get("member")
        if not isinstance(subevent, str) or not isinstance(member, str):
            raise ValueError(f"{detector}: specify subevent and member in experiment.yaml")
        body = read_subevent(spec, subevent)
        procid = item.get("procid")
        if type(procid) is not int:
            raise ValueError(f"{detector}: invalid procid")
        if procid in seen_procs:
            raise ValueError(f"{detector}: procid {procid} duplicates {seen_procs[procid]}")
        seen_procs[procid] = detector
        event_match = re.search(
            r"\b" + re.escape(member) + r"\s*=\s*" + re.escape(subevent) +
            r"\([^;]*?\bprocid\s*=\s*(\d+)",
            spec,
        )
        if not event_match or int(event_match.group(1)) != procid:
            warnings.append(f"{detector}: procid does not match UCESB EVENT declaration")
        if yaml_wr:
            if WR_ARGUMENT.findall(body) != [wr_symbol(member)]:
                warnings.append(f"{detector}: UCESB must use White Rabbit ID {wr_symbol(member)}")
        else:
            ts = re.search(r"TIMESTAMP_WHITERABBIT(?:_EXTENDED)?\(\s*id\s*=\s*(0x[0-9a-fA-F]+|\d+)", body)
            wr = item.get("whiterabbit")
            if type(wr) is not int or not ts or int(ts.group(1), 0) != wr:
                warnings.append(f"{detector}: White Rabbit subsystem ID differs from UCESB")
        if digitiser not in ("tamex", "vme"):
            continue

        header_path = root / "c4source" / (
            "fatima" if member in ("fatima", "fatimavme") else member
        ) / f"ext_h101_{member}.h"
        if not header_path.is_file():
            warnings.append(f"{detector}: missing generated structure header {header_path}")
            continue
        header = header_path.read_text()
        if digitiser == "tamex":
            if item.get("version") != 4:
                raise ValueError(f"{detector}: only TAMEX4 is supported by this validator")
            installed = board_list(item.get("boards"), detector, MAX_BOARDS["tamex"])
            sfp = item.get("sfp")
            if type(sfp) is not int:
                raise ValueError(f"{detector}: missing SFP ID")
            declared = [(int(idx), int(fiber), int(card)) for idx, fiber, card in TAMEX.findall(body)]
            if not declared:
                warnings.append(f"{detector}: no TAMEX4 board declarations found")
                continue
            if [x[0] for x in declared] != list(range(len(declared))):
                warnings.append(f"{detector}: UCESB TAMEX array indices are not consecutive")
            capacity = read_array_size(header, f"{member}_tamex")
            if capacity != len(declared):
                warnings.append(f"{detector}: structure header contains {capacity} TAMEX slots, "
                                f"but spec declares {len(declared)}")
            missing = sorted(set((sfp, b) for b in installed) - set((f, c) for _, f, c in declared))
            if missing:
                warnings.append(f"{detector}: TAMEX hardware addresses unsupported: {missing}")
            notes.append(f"{detector}: {len(installed)} installed, {capacity} TAMEX slots "
                         f"(policy maximum {MAX_BOARDS['tamex']})")
        else:
            for model, regex, member_name in (
                ("v1751", V1751, f"{member}_qdc"),
                ("v1290", V1290, f"{member}_tdc"),
            ):
                installed = board_list(item.get(model, {}).get("boards"), f"{detector}/{model}", MAX_BOARDS[model])
                declared = regex.findall(body)
                capacity = read_array_size(header, member_name)
                if capacity != len(declared):
                    warnings.append(f"{detector}/{model}: header has {capacity} slots, "
                                    f"but UCESB declares {len(declared)}")
                if model == "v1751":
                    addresses = {int(addr) for _, addr in declared}
                    missing = sorted(set(installed) - addresses)
                    if missing:
                        warnings.append(f"{detector}/V1751: unsupported board addresses: {missing}")
                elif len(installed) > capacity:
                    # The V1290 geo is decoded from event data, rather than fixed in its declaration.
                    warnings.append(f"{detector}/V1290: {len(installed)} boards exceed {capacity} TDC slots")
                notes.append(f"{detector}/{model}: {len(installed)} installed, {capacity} slots "
                             f"(policy maximum {MAX_BOARDS[model]})")
    return warnings, notes


def emit_whiterabbit(config):
    ids = wr_ids(read_yaml(config))
    print("// Generated from config/s100/experiment.yaml.")
    for member, wr in sorted(ids.items()):
        print(f"#define {wr_symbol(member)} 0x{wr:x}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    action = parser.add_mutually_exclusive_group(required=True)
    action.add_argument("--experiment", help="experiment name under config/ and unpack/exps/")
    action.add_argument("--emit-whiterabbit", type=Path, metavar="S100_YAML",
                        help="print the S100 White Rabbit spec include")
    args = parser.parse_args()
    if args.emit_whiterabbit:
        try:
            emit_whiterabbit(args.emit_whiterabbit)
        except (ValueError, OSError) as exc:
            parser.exit(2, f"ERROR generating S100 White Rabbit constants: {exc}\n")
        return 0
    if not re.fullmatch(r"[A-Za-z0-9_-]+", args.experiment):
        parser.error("invalid experiment name")
    try:
        warnings, notes = validate(args.experiment)
    except (ValueError, OSError, ImportError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2
    for note in notes:
        print(note)
    if warnings:
        for warning in warnings:
            print(f"WARNING: {warning}")
        print("This experiment needs unpacker configuration review; do not assume the current header can decode its hardware.")
        return 1
    print(f"OK: {args.experiment} hardware is supported by its unpacker and structure headers")
    return 0


if __name__ == "__main__":
    sys.exit(main())
