#!/usr/bin/env python3
"""Serve the c4Root S100 dashboard and translate ROOT histogram snapshots."""

import argparse
import json
import os
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
import re
import signal
import subprocess
from tempfile import TemporaryDirectory
from threading import Lock
from urllib.parse import parse_qs, quote, urlsplit
from urllib.request import HTTPRedirectHandler, build_opener


HERE = Path(__file__).resolve().parent
REPO = HERE.parents[1]
MACRO = REPO / "macros/tests/s100_tests.C"
FLAGS = re.compile(r"(?m)^(#define (\w+) )([01])$")
CONFIG = re.compile(r'config_path \+ "(/[^"]+)"')
INCLUDES = re.compile(r'(?m)^(\s*#include )"(\.\./[^"]+)"')
SIGNATURE = re.compile(r"void s100_tests\([^{}]*?\)\s*\{")
SAFE_PATH = re.compile(r"[\w./:@%+=,~-]+", re.ASCII)


def setup_defaults():
    source = MACRO.read_text()
    return {
        "repository": str(REPO),
        "subsystems": {name: value == "1" for _, name, value in FLAGS.findall(source)},
        "files": list(dict.fromkeys(CONFIG.findall(source))),
    }


def export_macro(settings):
    defaults = setup_defaults()
    source = MACRO.read_text()
    repository = settings["repository"].rstrip("/")
    input_path = settings["input"]
    output = settings.get("output", "")
    events = settings["events"]
    port = settings["port"]
    if not repository.startswith("/") or not SAFE_PATH.fullmatch(repository):
        raise ValueError("Use an absolute repository path without spaces or shell metacharacters.")
    if not SAFE_PATH.fullmatch(input_path) or input_path.startswith("-"):
        raise ValueError("Enter a stream:// or trans:// address or an LMD path without spaces.")
    if not (re.fullmatch(r"(stream|trans)://[^/]+", input_path) or input_path.endswith(".lmd")):
        raise ValueError("Enter a stream:// or trans:// address or an LMD path.")
    if type(events) is not int or not -1 <= events <= 2147483647 or events == 0:
        raise ValueError("Event limit must be -1 or a positive integer.")
    if type(port) is not int or not 1 <= port <= 65535:
        raise ValueError("ROOT server port must be between 1 and 65535.")
    if not isinstance(output, str) or (output and not (output.isascii() and output.isprintable())):
        raise ValueError("Use a plain ASCII path for the optional ROOT output file.")
    flags = settings["subsystems"]
    overrides = settings["files"]
    if set(flags) != set(defaults["subsystems"]) or any(type(v) is not bool for v in flags.values()):
        raise ValueError("Subsystem selections do not match this checkout's S100 macro.")
    if not set(overrides) <= set(defaults["files"]):
        raise ValueError("Unknown S100 configuration path.")
    if any(not isinstance(v, str) or not v.isascii() or not v.isprintable()
           for v in overrides.values()):
        raise ValueError("Use a plain ASCII path for each configuration override.")
    source = FLAGS.sub(lambda m: m[1] + str(int(flags[m[2]])), source)
    source = CONFIG.sub(lambda m: json.dumps(overrides[m[1]]) if m[1] in overrides else m[0], source)
    source = INCLUDES.sub(lambda m: m[1] + json.dumps(
        repository + "/" + str((MACRO.parent / m[2]).resolve().relative_to(REPO))), source)
    signature = (f"void s100_tests(const char* input = {json.dumps(input_path)},\n"
                 f"                Int_t nev = {events}, const char* repository = {json.dumps(repository)},\n"
                 f"                const char* output = {json.dumps(output)})\n{{")
    source, signatures = SIGNATURE.subn(lambda _: signature, source)
    source, ports = re.subn(r"(?m)^(\s*Int_t port = )\d+;", lambda m: f"{m[1]}{port};", source)
    if signatures != 1 or ports != 1:
        raise ValueError("The S100 macro structure has changed. Review the dashboard exporter.")
    return source


MACROS = REPO / "macros"


def existing_macros():
    for path in sorted(MACROS.rglob("*.C")):
        if (re.fullmatch(r"[A-Za-z0-9_.+-]+\.C", path.name) and path.is_file()
                and path.resolve().is_relative_to(MACROS)):
            yield path.relative_to(MACROS).as_posix()


def existing_macro(name):
    if name not in existing_macros():
        raise ValueError("Select a .C macro under the checkout's macros directory.")
    return (MACROS / name).resolve()


class Run:
    def __init__(self, directory):
        self.directory = Path(directory)
        self.log = self.directory / "run.log"
        self.process = None
        self.lock = Lock()

    def start(self, settings):
        with self.lock:
            if self.process and self.process.poll() is None:
                raise ValueError("A dashboard run is already active.")
            if settings["source"] == "generated":
                macro = self.directory / "s100_tests.C"
                macro.write_text(export_macro(settings["settings"]))
                expression = str(macro)
                working_directory = REPO
            elif settings["source"] == "existing":
                macro = existing_macro(settings["macro"])
                args = settings.get("arguments", [])
                if not isinstance(args, list) or len(args) > 20 or any(
                    type(arg) not in (int, str) or
                    (isinstance(arg, str) and arg and not SAFE_PATH.fullmatch(arg)) or
                    (type(arg) is int and not -(2**31) <= arg < 2**31)
                    for arg in args
                ):
                    raise ValueError("Use a JSON array of integers or plain strings without spaces.")
                working_directory = macro.parent
                expression = macro.name + "(" + ", ".join(json.dumps(arg) for arg in args) + ")"
            else:
                raise ValueError("Select a macro source.")
            with self.log.open("wb") as log:
                self.process = subprocess.Popen(
                    ["root", "-l", "-b", "-q", expression],
                    cwd=working_directory, stdin=subprocess.DEVNULL, stdout=log,
                    stderr=subprocess.STDOUT, start_new_session=True,
                )

    def stop(self):
        with self.lock:
            if self.process and self.process.poll() is None:
                try:
                    os.killpg(self.process.pid, signal.SIGTERM)
                except ProcessLookupError:
                    pass

    def status(self):
        with self.lock:
            code = self.process.poll() if self.process else None
            log = ""
            if self.log.exists():
                with self.log.open("rb") as file:
                    file.seek(max(0, self.log.stat().st_size - 16000))
                    log = file.read(16000).decode(errors="replace")
            return {"running": self.process is not None and code is None, "exitCode": code, "log": log}


def axis_data(axis):
    count = axis["fNbins"]
    variable = axis.get("fXbins") or []
    if variable and len(variable) != count + 1:
        raise ValueError("Invalid variable bin edges.")
    if variable:
        edges = variable
    else:
        low, high = axis["fXmin"], axis["fXmax"]
        width = (high - low) / count
        edges = [low + i * width for i in range(count)] + [high]
    return {"title": axis.get("fTitle", ""), "edges": edges}


def histogram(data):
    kind = data["_typename"]
    if not re.fullmatch(r"TH[12][CSIFDL]", kind):
        raise ValueError(f"Unsupported ROOT object {kind}. Select a TH1 or TH2.")
    dimensions = int(kind[2])
    x = axis_data(data["fXaxis"])
    nx = len(x["edges"]) - 1
    stride = nx + 2
    bins = data["fArray"]
    result = {"dimensions": dimensions, "x": x, "title": data["fTitle"],
              "entries": data["fEntries"], "y": {"title": data["fYaxis"].get("fTitle") or "Counts"}}
    if dimensions == 1 and len(bins) == stride:
        result["bins"] = bins[1:-1]
    elif dimensions == 2:
        y = axis_data(data["fYaxis"])
        ny = len(y["edges"]) - 1
        if len(bins) != stride * (ny + 2):
            raise ValueError("Invalid TH2 bin storage.")
        result["y"] = y
        result["bins"] = [bins[row * stride + 1:row * stride + 1 + nx] for row in range(1, ny + 1)]
    else:
        raise ValueError("Invalid TH1 bin storage.")
    return result


def histogram_paths(node, parent=""):
    for child in node.get("_childs", []):
        name = child["_name"]
        path = f"{parent}/{name}" if parent else name
        if re.fullmatch(r"ROOT.TH[12][CSIFDL]", child.get("_kind", "")):
            yield {"path": path, "title": child.get("_title") or name,
                   "dimensions": int(child["_kind"][7])}
        yield from histogram_paths(child, path)


class NoRedirect(HTTPRedirectHandler):
    def redirect_request(self, *args, **kwargs):
        return None


def root_json(server, endpoint):
    with build_opener(NoRedirect).open(f"{server}/{endpoint}", timeout=8) as reply:
        payload = reply.read(64 * 1024 * 1024 + 1)
        if len(payload) > 64 * 1024 * 1024:
            raise ValueError("ROOT response exceeds 64 MiB. Select a smaller histogram.")
        return json.loads(payload)


class Dashboard(BaseHTTPRequestHandler):
    def send_data(self, status, data, content_type="application/json"):
        body = json.dumps(data, allow_nan=False).encode() if content_type == "application/json" else data
        self.send_response(status)
        self.send_header("Content-Type", content_type)
        self.send_header("Cache-Control", "no-store")
        self.send_header("Content-Length", str(len(body)))
        self.end_headers()
        self.wfile.write(body)

    def check_local_request(self):
        port = self.server.server_port
        hosts = {f"127.0.0.1:{port}", f"localhost:{port}"}
        host = self.headers.get("Host")
        origin = self.headers.get("Origin")
        if host not in hosts or origin not in (None, f"http://{host}"):
            self.send_data(403, {"error": "Open the dashboard using its local address."})
            return False
        return True

    def do_GET(self):
        if not self.check_local_request():
            return
        url = urlsplit(self.path)
        assets = {"/": ("index.html", "text/html"), "/app.js": ("app.js", "text/javascript"),
                  "/style.css": ("style.css", "text/css")}
        try:
            if url.path in assets:
                name, mime = assets[url.path]
                self.send_data(200, (HERE / name).read_bytes(), f"{mime}; charset=utf-8")
            elif url.path == "/plotly.js" and self.server.plotly:
                self.send_data(200, self.server.plotly.read_bytes(), "text/javascript")
            elif url.path == "/api/setup":
                self.send_data(200, setup_defaults())
            elif url.path == "/api/macros":
                self.send_data(200, list(existing_macros()))
            elif url.path == "/api/macro-preview":
                name = parse_qs(url.query).get("path", [""])[0]
                self.send_data(200, {"macro": existing_macro(name).read_text(errors="replace")})
            elif url.path == "/api/run":
                self.send_data(200, self.server.run.status())
            elif url.path == "/api/status":
                self.send_data(200, {"root": self.server.root_url, "localPlotly": bool(self.server.plotly)})
            elif url.path == "/api/histograms":
                tree = root_json(self.server.root_url, "h.json")
                self.send_data(200, sorted(histogram_paths(tree), key=lambda item: item["path"]))
            elif url.path == "/api/histogram":
                path = parse_qs(url.query).get("path", [""])[0]
                parts = path.split("/")
                if any(part in ("", ".", "..") for part in parts) or "\\" in path:
                    raise ValueError("Select a valid histogram path.")
                endpoint = "/".join(quote(part, safe="") for part in parts)
                self.send_data(200, histogram(root_json(self.server.root_url, endpoint + "/root.json?compact=3")))
            else:
                self.send_data(404, {"error": "Page not found."})
        except (OSError, KeyError, ValueError, TypeError) as error:
            self.send_data(502, {"error": str(error)})

    def do_POST(self):
        if not self.check_local_request():
            return
        if self.path not in ("/api/macro", "/api/run/start", "/api/run/stop"):
            self.send_data(404, {"error": "Page not found."})
            return
        try:
            if self.headers.get_content_type() != "application/json":
                raise ValueError("Expected JSON run settings.")
            size = int(self.headers.get("Content-Length", "0"))
            if not 0 < size <= 65536:
                raise ValueError("Invalid run settings size.")
            settings = json.loads(self.rfile.read(size))
            if self.path == "/api/macro":
                self.send_data(200, {"macro": export_macro(settings)})
                return
            if self.path == "/api/run/start":
                self.server.run.start(settings)
            else:
                self.server.run.stop()
            self.send_data(200, self.server.run.status())
        except (OSError, KeyError, AttributeError, ValueError, TypeError) as error:
            self.send_data(400, {"error": str(error)})


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root-url", default="http://127.0.0.1:6969")
    parser.add_argument("--port", type=int, default=8050)
    parser.add_argument("--plotly-js", type=Path, help="Local Plotly.js bundle for offline use")
    args = parser.parse_args()
    upstream = urlsplit(args.root_url)
    if upstream.scheme not in ("http", "https") or not upstream.hostname or upstream.query or upstream.fragment:
        parser.error("--root-url must be an HTTP(S) server URL without a query or fragment")
    if args.plotly_js and not args.plotly_js.is_file():
        parser.error("--plotly-js must point to a JavaScript bundle")
    with TemporaryDirectory(prefix="c4root-run-") as directory, \
            ThreadingHTTPServer(("127.0.0.1", args.port), Dashboard) as server:
        server.run = Run(directory)
        server.root_url = args.root_url.rstrip("/")
        server.plotly = args.plotly_js
        print(f"c4Root Dashboard at http://127.0.0.1:{server.server_port}", flush=True)
        try:
            server.serve_forever()
        except KeyboardInterrupt:
            pass
        finally:
            server.run.stop()


if __name__ == "__main__":
    main()
