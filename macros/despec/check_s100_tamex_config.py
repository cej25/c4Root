#!/usr/bin/env python3
"""Check or explicitly synchronize s100 TAMEX routing against experiment.yaml.

No third-party YAML dependency: this deliberately accepts only the flat schema
used by experiment.yaml, and refuses unfamiliar content rather than guessing.
Only the three named TAMEX detectors are in scope; all other unpacker routing
remains untouched. An update always shows a unified diff first.
"""

import argparse
import difflib
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve()
ROOT = HERE.parents[2]
CONFIG = ROOT / "config/s100/experiment.yaml"
SPEC = ROOT / "unpack/exps/s100/s100.spec"

# (YAML detector, EVENT member, SUBEVENT definition)
ROUTES = (
    ("FATIMA", "fatima", "fatima_tamex_subev"),
    ("bPlast", "bplast", "bplast_subev"),
    ("BGO", "bgo", "bgo_tamex_subevent"),
)
KEYS = {"digitiser", "version", "procid", "whiterabbit"}


def number(value):
    if not re.fullmatch(r"(?:0[xX][0-9a-fA-F]+|[0-9]+)", value):
        raise ValueError(f"Invalid numeric value: {value}")
    return int(value, 0) if value.lower().startswith("0x") else int(value)


def load_config(path):
    sections = {}
    current = None
    for lineno, line in enumerate(path.read_text().splitlines(), 1):
        clean = line.split("#", 1)[0].rstrip()
        if not clean.strip():
            continue
        head = re.fullmatch(r"([A-Za-z][A-Za-z0-9_-]*):", clean)
        if head:
            current = head.group(1)
            if current in sections:
                raise ValueError(f"Duplicate detector {current} on line {lineno}")
            sections[current] = {}
            continue
        field = re.fullmatch(r"[ \t]+([a-z]+):[ \t]*([^ \t]+)[ \t]*", clean)
        if not field or current is None:
            raise ValueError(f"Unsupported YAML syntax on line {lineno}: {line}")
        key, value = field.groups()
        if key not in KEYS or key in sections[current]:
            raise ValueError(f"Unknown/duplicate {current}.{key} on line {lineno}")
        sections[current][key] = value

    result = {}
    for detector, _, _ in ROUTES:
        fields = sections.get(detector)
        if fields is None or set(fields) != KEYS:
            raise ValueError(f"Missing/extra configuration fields for {detector}")
        if fields["digitiser"] != "tamex" or number(fields["version"]) != 4:
            raise ValueError(f"Unsupported electronics for {detector} (requires TAMEX4)")
        procid, wr = number(fields["procid"]), number(fields["whiterabbit"])
        if not (0 <= procid <= 65535 and 0 <= wr <= 65535):
            raise ValueError(f"{detector}: numeric identifier exceeds uint16 range")
        result[detector] = (procid, wr)
    if len({v[0] for v in result.values()}) != len(result):
        raise ValueError("Duplicate TAMEX procids in experiment.yaml")
    return result


def unique_match(pattern, text, label, flags=0):
    matches = list(re.finditer(pattern, text, flags))
    if len(matches) != 1:
        raise ValueError(f"Expected exactly one {label}, found {len(matches)}")
    return matches[0]


def event_span(spec):
    start = unique_match(r"(?m)^EVENT[ \t]*\{", spec, "EVENT block")
    begin = start.end()
    depth = 1
    for i in range(begin, len(spec)):
        if spec[i] == "{":
            depth += 1
        elif spec[i] == "}":
            depth -= 1
            if depth == 0:
                return begin, i
    raise ValueError("Unterminated EVENT block")


def subevent_span(spec, name):
    match = unique_match(
        r"(?m)^SUBEVENT[ \t]*\([ \t]*" + re.escape(name) + r"[ \t]*\)[ \t]*\{",
        spec, f"SUBEVENT({name})")
    depth = 1
    for i in range(match.end(), len(spec)):
        if spec[i] == "{":
            depth += 1
        elif spec[i] == "}":
            depth -= 1
            if depth == 0:
                return match.end(), i
    raise ValueError(f"Unterminated SUBEVENT({name})")


def plan(spec, config):
    edits = []
    eb, ee = event_span(spec)
    event = spec[eb:ee]
    for detector, member, subevent in ROUTES:
        desired_procid, desired_wr = config[detector]
        routing = unique_match(
            r"(?m)^[ \t]*" + re.escape(member)
            + r"[ \t]*=[ \t]*" + re.escape(subevent)
            + r"[ \t]*\([^;]*\)[ \t]*;",
            event, f"EVENT routing for {detector}")
        call = routing.group(0)
        procid = unique_match(r"\bprocid[ \t]*=[ \t]*(0[xX][0-9a-fA-F]+|[0-9]+)",
                              call, f"{detector} procid")
        before = procid.group(1)
        if number(before) != desired_procid:
            edits.append((eb + routing.start() + procid.start(1),
                          eb + routing.start() + procid.end(1),
                          str(desired_procid), f"{detector} procid {before} -> {desired_procid}"))

        sb, se = subevent_span(spec, subevent)
        body = spec[sb:se]
        # Both normal and EXTENDED timestamp encodings are supported.
        stamp = unique_match(
            r"TIMESTAMP_WHITERABBIT(?:_EXTENDED)?[ \t]*\([ \t]*id[ \t]*=[ \t]*(0[xX][0-9a-fA-F]+|[0-9]+)[ \t]*\)",
            body, f"{detector} WR timestamp")
        before_wr = stamp.group(1)
        if number(before_wr) != desired_wr:
            # Restrict edits to the numeric token, not timestamp function type.
            edits.append((sb + stamp.start(1), sb + stamp.end(1),
                          hex(desired_wr), f"{detector} WR {before_wr} -> {hex(desired_wr)}"))

    # Never silently create duplicate procids with unrelated EVENT members.
    event_procids = [
        (number(m.group(1)), m.group(0)) for m in
        re.finditer(r"\bprocid[ \t]*=[ \t]*(0[xX][0-9a-fA-F]+|[0-9]+)", event)
    ]
    for detector, _, _ in ROUTES:
        expected = config[detector][0]
        # A desired procid may not collide with an unchanged, unrelated route.
        original = next((number(re.search(
            r"\bprocid[ \t]*=[ \t]*(0[xX][0-9a-fA-F]+|[0-9]+)",
            unique_match(r"(?m)^[ \t]*" + re.escape(member) + r"[ \t]*=[^;]*;",
                         event, member).group(0)).group(1))
            for name, member, _ in ROUTES if name == detector), None)
        for pid, row in event_procids:
            if pid == expected and pid != original:
                raise ValueError(f"{detector}: desired procid {pid} is already used in EVENT: {row.strip()}")

    updated = spec
    for begin, end, replacement, _ in sorted(edits, reverse=True):
        updated = updated[:begin] + replacement + updated[end:]
    return updated, [item[3] for item in edits]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply", action="store_true",
                        help="Update s100.spec in place after showing the exact diff")
    args = parser.parse_args()
    try:
        config = load_config(CONFIG)
        original = SPEC.read_text()
        updated, changes = plan(original, config)
        for detector, member, subevent in ROUTES:
            pid, wr = config[detector]
            print(f"{detector}: EVENT {member} -> {subevent}, procid={pid}, WR={hex(wr)}")
        if not changes:
            print("OK: experiment.yaml and s100.spec agree for all three TAMEX detectors.")
            return 0
        print("\nDifferences: " + "; ".join(changes))
        print("".join(difflib.unified_diff(original.splitlines(keepends=True),
                    updated.splitlines(keepends=True),
                    fromfile=str(SPEC), tofile=str(SPEC) + " (proposed)")))
        if not args.apply:
            print("No files changed. Run again with --apply to update s100.spec.")
            return 1
        SPEC.write_text(updated)
        print("Updated s100.spec. Review with git diff, then rebuild the s100 UCESB unpacker.")
        return 0
    except (ValueError, OSError) as exc:
        print(f"ERROR: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
