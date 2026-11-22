#!/usr/bin/env python3
"""Check an experiment's UCESB routing and declared board layouts.

S100 also checks the installed hardware and generated reader headers.
"""
import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
MAX_BOARDS = {"tamex": 12, "v1751": 6, "v1290": 6}
FEBEX_MAX_BOARDS = 12
TAMEX = re.compile(r"\btamex\[(\d+)\]\s*=\s*TAMEX4_SFP\(\s*sfp\s*=\s*(\d+)\s*,\s*card\s*=\s*(\d+)\s*\)")
V1751 = re.compile(r"\bqdc(\[\d+\]|\d+)\s*=\s*VME_CAEN_V1751\(\s*board\s*=\s*(\d+)\s*\)")
V1290_GEO = re.compile(r"\btdc(\d+)\s*=\s*VME_CAEN_V1290_GEO\(\s*geom_expected\s*=\s*(\d+)\s*\)")
FEBEX = re.compile(r"\bdata\[(\d+)\]\s*=\s*FEBEX_EVENT(_TRACES)?\(\s*card\s*=\s*(\d+)\s*\)")
V775 = re.compile(r"\bv7x5(?:_module)?\[(\d+)\]\s*=\s*VME_CAEN_V775(?:_RAW)?\(\s*geom\s*=\s*(\d+)\s*\)")
CLOCK_TDC = re.compile(r"\bCLOCK_TDC_EVENT_16PH\(\s*sfp_id\s*=\s*(\d+)\s*,\s*tdc_id\s*=\s*(\d+)\s*\)")
MEMBER = {"fatima": "fatima", "bplast": "bplast", "bgo": "bgo", "fatimavme": "fatimavme"}

S100_CONFIG_INCLUDE = "s100_config.gen.spec"
S100_WR_MEMBERS = {"aida", "beammonitor", "bgo", "bplast", "fatima", "fatimavme", "frstpat", "germanium"}
S100_EVENT_MEMBERS = S100_WR_MEMBERS | {"frsmain", "frstpc", "frsuser"}
S100_TAMEX_MEMBERS = {"fatima", "bplast", "bgo"}
S100_VME_MODELS = {
    "v1751": ("S100_V1751_BANKS", "qdc", "VME_CAEN_V1751", "board"),
    "v1290": ("S100_V1290_BANKS", "tdc", "VME_CAEN_V1290_GEO", "geom_expected"),
}
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


def procid_symbol(member):
    return f"S100_PROCID_{member.upper()}"


def tamex_cards_symbol(member):
    return f"S100_TAMEX_CARDS_{member.upper()}"


def compiled_tamex_slots(detector, item):
    if item.get("digitiser") != "tamex" or item.get("version") != 4:
        raise ValueError(f"{detector}: compiled slots require TAMEX4")
    slots = item.get("compiled_slots")
    if not isinstance(slots, list) or not 1 <= len(slots) <= MAX_BOARDS["tamex"]:
        raise ValueError(f"{detector}: compiled_slots must contain 1–{MAX_BOARDS['tamex']} pairs")
    addresses = []
    for index, pair in enumerate(slots):
        if (not isinstance(pair, list) or len(pair) != 2
                or any(type(value) is not int for value in pair)
                or not 0 <= pair[0] <= 15 or not 0 <= pair[1] <= 255):
            raise ValueError(f"{detector}: compiled_slots[{index}] must be [SFP 0–15, card 0–255]")
        addresses.append(tuple(pair))
    if len(set(addresses)) != len(addresses):
        raise ValueError(f"{detector}: duplicate compiled TAMEX address")
    return addresses


def compiled_febex_slots(detector, item):
    if item.get("digitiser") != "febex" or item.get("version") != 4:
        raise ValueError(f"{detector}: the summary RAW mapping requires FEBEX4")
    slots = board_list(item.get("compiled_slots"), f"{detector} compiled_slots", FEBEX_MAX_BOARDS)
    if any(card > 255 for card in slots):
        raise ValueError(f"{detector}: compiled card IDs must be in 0–255")
    return slots


def compiled_vme_slots(item, model):
    config = item.get(model)
    slots = config.get("compiled_slots") if isinstance(config, dict) else None
    capacity = MAX_BOARDS[model]
    if not isinstance(slots, list) or len(slots) != capacity:
        raise ValueError(f"FATIMA_VME/{model}: compiled_slots must contain exactly {capacity} addresses")
    if any(type(address) is not int or not 1 <= address <= 31 for address in slots):
        raise ValueError(f"FATIMA_VME/{model}: compiled addresses must be integers in 1–31")
    if len(set(slots)) != len(slots):
        raise ValueError(f"FATIMA_VME/{model}: duplicate compiled address")
    return slots


def s100_routes(configuration):
    routes, seen_procids = {}, {}
    for detector, item in configuration.items():
        if not isinstance(item, dict) or ("member" not in item and "procid" not in item):
            continue
        member, subevent = item.get("member"), item.get("subevent")
        if not isinstance(member, str) or not re.fullmatch(r"[a-z][a-z0-9_]*", member):
            raise ValueError(f"{detector}: invalid EVENT member")
        if not isinstance(subevent, str) or not re.fullmatch(r"[A-Za-z_][A-Za-z0-9_]*", subevent):
            raise ValueError(f"{detector}: invalid subevent")
        if member in routes:
            raise ValueError(f"{detector}: duplicate EVENT member {member}")
        procid = item.get("procid")
        if type(procid) is not int or not 0 <= procid <= 0xffff:
            raise ValueError(f"{detector}: procid must be an integer in 0–65535")
        if procid in seen_procids:
            raise ValueError(f"{detector}: procid {procid} duplicates {seen_procids[procid]}")
        seen_procids[procid] = detector
        routes[member] = (detector, item)
    missing = S100_EVENT_MEMBERS - routes.keys()
    if missing:
        raise ValueError(f"Missing EVENT routing for {', '.join(sorted(missing))}")
    return routes


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


def check_s100_routing(spec, configuration):
    routes = s100_routes(configuration)
    ids = wr_ids(configuration)
    if f'#include "{S100_CONFIG_INCLUDE}"' not in spec:
        raise ValueError(f"Spec must include {S100_CONFIG_INCLUDE}")
    event = re.search(r"(?m)^EVENT\s*\{([^{}]*)\}", spec)
    if event is None:
        raise ValueError("UCESB EVENT block not found")
    warnings = []
    for member, (detector, item) in routes.items():
        subevent = item["subevent"]
        procid = re.findall(
            rf"(?m)^[ \t]*(?:revisit[ \t]+)?{member}\s*=\s*{subevent}\s*\("
            r"[^;]*?\bprocid\s*=\s*(\w+)(?=\s*[,\)])",
            event.group(1),
        )
        if procid != [procid_symbol(member)]:
            warnings.append(f"{detector}: UCESB EVENT must use {procid_symbol(member)}")
        if member in ids:
            body = read_subevent(spec, subevent)
            if WR_ARGUMENT.findall(body) != [wr_symbol(member)]:
                warnings.append(f"{detector}: UCESB must use White Rabbit ID {wr_symbol(member)}")
            if member in S100_TAMEX_MEMBERS:
                slots = re.findall(r"\bS100_TAMEX_CARDS_\w+\b", body)
                if slots != [tamex_cards_symbol(member)] or TAMEX.search(body):
                    warnings.append(f"{detector}: UCESB must use {tamex_cards_symbol(member)}")
            if member == "germanium":
                slots = re.findall(r"\bS100_DEGAS_CARDS\b", body)
                if slots != ["S100_DEGAS_CARDS"] or FEBEX.search(body):
                    warnings.append(f"{detector}: UCESB must use S100_DEGAS_CARDS")
            if member == "fatimavme":
                for model, (symbol, _, _, _) in S100_VME_MODELS.items():
                    compiled_vme_slots(item, model)
                    if len(re.findall(rf"(?m)^\s*{symbol}\s*$", body)) != 1:
                        warnings.append(f"{detector}/{model}: UCESB must use {symbol}")
                if V1751.search(body) or V1290_GEO.search(body):
                    warnings.append(f"{detector}: use the generated VME bank declarations")
    return warnings


def spec_inventory(spec):
    """Read the active, literal declarations used by the older experiment specs."""
    spec = re.sub(r"/\*.*?\*/|//[^\n]*", "", spec, flags=re.S)
    event = re.search(r"(?m)^EVENT\s*\{([^{}]*)\}", spec)
    if event is None:
        raise ValueError("UCESB EVENT block not found")
    inventory = {}
    for binding in event[1].split(";"):
        binding = binding.strip()
        if binding in ("", "ignore_unknown_subevent"):
            continue
        match = re.fullmatch(r"(?:(revisit)\s+)?(\w+)\s*=\s*(\w+)\(([^()]*)\)", binding)
        if match is None:
            raise ValueError(f"Unsupported UCESB EVENT binding: {binding}")
        revisit, member, subevent, selectors = match.groups()
        route = {"subevent": subevent, "member": member}
        for selector in selectors.split(","):
            name, value = selector.split("=", 1)
            route[name.strip()] = int(value, 0)
        if revisit:
            route["revisit"] = True
        body = read_subevent(spec, subevent)
        wr = WR_ARGUMENT.search(body)
        if wr:
            route["whiterabbit"] = int(wr[1], 0)
        tamex, febex, v775, clock = (pattern.findall(body) for pattern in (TAMEX, FEBEX, V775, CLOCK_TDC))
        if tamex:
            route.update(digitiser="tamex", version=4, compiled_slots=[
                [int(sfp), int(card)] for _, sfp, card in sorted(tamex, key=lambda slot: int(slot[0]))
            ])
        elif febex:
            route.update(digitiser="febex", version=4, traces=any(mode for _, mode, _ in febex),
                         compiled_slots=[int(card) for _, _, card in sorted(febex, key=lambda slot: int(slot[0]))])
        elif v775:
            route.update(digitiser="v775",
                         compiled_slots=[int(geo) for _, geo in sorted(v775, key=lambda slot: int(slot[0]))])
        elif clock:
            route.update(digitiser="clock_tdc", compiled_slots=[[int(sfp), int(tdc)] for sfp, tdc in clock])
        elif member == "fatimavme":
            route["digitiser"] = "vme"
            for model, regex in (("v1751", V1751), ("v1290", V1290_GEO)):
                slots = sorted((int(slot.strip("[]")), int(address)) for slot, address in regex.findall(body))
                route[model] = {"compiled_slots": [address for _, address in slots]}
        inventory[member] = route
    return inventory


def check_spec_inventory(spec, configuration):
    remaining = spec_inventory(spec)
    warnings = []
    for detector, item in configuration.items():
        if not isinstance(item, dict):
            raise ValueError(f"{detector}: expected a detector mapping")
        member = item.get("member")
        route = remaining.pop(member, None)
        if route is None:
            warnings.append(f"{detector}: no unmatched active UCESB EVENT binding for {member}")
            continue
        selectors = {"procid", "whiterabbit", "type", "subtype", "control", "subcrate", "revisit"}
        for key in sorted(route.keys() | (item.keys() & selectors)):
            if key in ("v1751", "v1290"):
                slots = compiled_vme_slots(item, key)
                bank = item[key]
                if slots != route[key]["compiled_slots"]:
                    warnings.append(f"{detector}/{key}: compiled_slots differs from UCESB")
                if "boards" in bank:
                    installed = board_list(bank["boards"], f"{detector}/{key}", MAX_BOARDS[key])
                    if not set(installed) <= set(route[key]["compiled_slots"]):
                        warnings.append(f"{detector}/{key}: installed board addresses are missing from UCESB")
            elif item.get(key) != route.get(key):
                warnings.append(f"{detector}: {key} differs from UCESB")
    warnings.extend(f"Missing YAML entry for UCESB EVENT member {member}" for member in remaining)
    return warnings


def validate(experiment, root=ROOT):
    config_file = root / "config" / experiment / "experiment.yaml"
    spec_file = root / "unpack" / "exps" / experiment / f"{experiment}.spec"
    if not config_file.is_file() or not spec_file.is_file():
        raise ValueError(f"Cannot find experiment.yaml and unpacker spec for {experiment}")
    configuration = read_yaml(config_file)
    spec = spec_file.read_text()
    if experiment != "s100":
        return check_spec_inventory(spec, configuration), []
    warnings = check_s100_routing(spec, configuration)
    notes = []
    for detector, item in configuration.items():
        if not isinstance(item, dict):
            continue
        digitiser = item.get("digitiser")
        if digitiser not in ("tamex", "vme", "febex"):
            continue
        subevent = item.get("subevent")
        member = item.get("member")
        if not isinstance(subevent, str) or not isinstance(member, str):
            raise ValueError(f"{detector}: specify subevent and member in experiment.yaml")
        body = read_subevent(spec, subevent)
        directory = "fatima" if member in ("fatima", "fatimavme") else member
        if digitiser == "febex":
            directory, header_name = "degas", "ext_h101_degas.h"
        else:
            header_name = f"ext_h101_{member}.h"
        header_path = root / "c4source" / directory / header_name
        if not header_path.is_file():
            warnings.append(f"{detector}: missing generated structure header {header_path}")
            continue
        header = header_path.read_text()
        if digitiser == "febex":
            slots = compiled_febex_slots(detector, item)
            capacity = read_array_size(header, f"{member}_data")
            if capacity != len(slots):
                warnings.append(f"{detector}: generated header has {capacity} FEBEX slots, "
                                f"but unpacker declares {len(slots)}")
            notes.append(f"{detector}: {len(slots)} FEBEX cards, {capacity} UNPACK board slots")
        elif digitiser == "tamex":
            if item.get("version") != 4:
                raise ValueError(f"{detector}: only TAMEX4 is supported by this validator")
            installed = board_list(item.get("boards"), detector, MAX_BOARDS["tamex"])
            sfp = item.get("sfp")
            if type(sfp) is not int:
                raise ValueError(f"{detector}: missing SFP ID")
            if member in S100_TAMEX_MEMBERS:
                addresses = compiled_tamex_slots(detector, item)
            else:
                declared = [(int(idx), int(fiber), int(card)) for idx, fiber, card in TAMEX.findall(body)]
                if not declared:
                    warnings.append(f"{detector}: no TAMEX4 board declarations found")
                    continue
                if [x[0] for x in declared] != list(range(len(declared))):
                    warnings.append(f"{detector}: UCESB TAMEX array indices are not consecutive")
                addresses = [(fiber, card) for _, fiber, card in declared]
            capacity = read_array_size(header, f"{member}_tamex")
            if capacity != len(addresses):
                warnings.append(f"{detector}: structure header contains {capacity} TAMEX slots, "
                                f"but unpacker declares {len(addresses)}")
            missing = sorted({(sfp, card) for card in installed} - set(addresses))
            if missing:
                warnings.append(f"{detector}: TAMEX hardware addresses unsupported: {missing}")
            notes.append(f"{detector}: {len(installed)} installed, {capacity} TAMEX slots "
                         f"(policy maximum {MAX_BOARDS['tamex']})")
        else:
            fixed_vme = member == "fatimavme"
            for model, regex, member_name in (
                ("v1751", V1751, f"{member}_qdc"),
                ("v1290", V1290_GEO, f"{member}_tdc"),
            ):
                installed = board_list(item.get(model, {}).get("boards"), f"{detector}/{model}", MAX_BOARDS[model])
                if fixed_vme:
                    declared = list(enumerate(compiled_vme_slots(item, model), 1))
                else:
                    declared = regex.findall(body)
                capacity = read_array_size(header, member_name)
                if capacity != len(declared):
                    warnings.append(f"{detector}/{model}: header has {capacity} slots, "
                                    f"but UCESB declares {len(declared)}")
                addresses = {int(addr) for _, addr in declared}
                missing = sorted(set(installed) - addresses)
                if missing:
                    warnings.append(f"{detector}/{model.upper()}: unsupported board addresses: {missing}")
                notes.append(f"{detector}/{model}: {len(installed)} installed, {capacity} slots "
                             f"(policy maximum {MAX_BOARDS[model]})")
    return warnings, notes


def emit_whiterabbit(config, include_procids=False):
    configuration = read_yaml(config)
    ids = wr_ids(configuration)
    routes = s100_routes(configuration) if include_procids else {}
    layouts = {
        member: compiled_tamex_slots(detector, item)
        for member, (detector, item) in routes.items() if member in S100_TAMEX_MEMBERS
    }
    vme = {
        model: compiled_vme_slots(routes["fatimavme"][1], model)
        for model in S100_VME_MODELS
    } if routes else {}
    print("// Generated from config/s100/experiment.yaml.")
    for member, wr in sorted(ids.items()):
        print(f"#define {wr_symbol(member)} 0x{wr:x}")
    for member, (_, item) in sorted(routes.items()):
        print(f"#define {procid_symbol(member)} {item['procid']}")
    for member, slots in sorted(layouts.items()):
        cards = " ".join(
            f"tamex[{index}] = TAMEX4_SFP(sfp = {sfp}, card = {card});"
            for index, (sfp, card) in enumerate(slots)
        )
        print(f"#define {tamex_cards_symbol(member)} {cards}")
    for model, slots in vme.items():
        symbol, bank, decoder, parameter = S100_VME_MODELS[model]
        names = (f"{bank}[{slot}]" if model == "v1751" else f"{bank}{slot + 1}"
                 for slot in range(len(slots)))
        banks = " ".join(
            f"{name} = {decoder}({parameter} = {address});"
            for name, address in zip(names, slots)
        )
        print(f"#define {symbol} {banks}")

    if routes:
        detector, item = routes["germanium"]
        slots = compiled_febex_slots(detector, item)
        cards = " ".join(f"data[{slot}] = FEBEX_EVENT(card = {card});" for slot, card in enumerate(slots))
        print(f"#define S100_DEGAS_CARDS {cards}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    action = parser.add_mutually_exclusive_group(required=True)
    action.add_argument("--experiment", help="experiment name under config/ and unpack/exps/")
    action.add_argument("--emit-whiterabbit", type=Path, metavar="S100_YAML",
                        help="print the S100 White Rabbit spec include")
    action.add_argument("--emit-s100-routing", type=Path, metavar="S100_YAML",
                        help="print the S100 procids, White Rabbit IDs, and compiled layouts")
    args = parser.parse_args()
    config = args.emit_s100_routing or args.emit_whiterabbit
    if config:
        try:
            emit_whiterabbit(config, include_procids=args.emit_s100_routing is not None)
        except (ValueError, OSError) as exc:
            parser.exit(2, f"ERROR generating S100 routing constants: {exc}\n")
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
        return 1
    if args.experiment == "s100":
        print("OK: s100 installed boards fit the current unpacker and structure headers")
    else:
        print(f"OK: {args.experiment} inventory matches the UCESB spec")
    return 0


if __name__ == "__main__":
    sys.exit(main())
