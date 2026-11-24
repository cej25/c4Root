"use strict";

const $ = (selector) => document.querySelector(selector);
const number = new Intl.NumberFormat();
const stateKey = "c4root.s100.monitor.v1";
let saved = {};
try { saved = JSON.parse(localStorage.getItem(stateKey)) || {}; } catch {}
let activeView = "monitor";
let rootLabel = "";
let macro = "";
let setupRevision = 0;
const defaultSubsystems = ["FRS", "AIDA", "bPlast", "FATIMA", "DEGAS"];
const subsystemAliases = new Map([
  ["frs online", "FRS"], ["fatima vme", "FATIMA VME"],
  ...defaultSubsystems.map(name => [name.toLowerCase(), name]),
]);
let subsystem = saved.subsystem || "DEGAS";
let groups = new Map(defaultSubsystems.map(name => [name, []]));
let selections = new Map(Object.entries(saved.selections || {}));
let connected = false;
let discoveredHistograms = false;
const flags = { FATIMA_ON: "FATIMA TAMEX", FATIMA_VME_ON: "FATIMA VME", AIDA_ON: "AIDA",
  BPLAST_ON: "bPlast", DEGAS_ON: "DEGAS", BGO_ON: "BGO", FRS_ON: "FRS",
  TIME_MACHINE_ON: "Time Machine", BEAMMONITOR_ON: "Beam Monitor", WHITE_RABBIT_CORS: "White Rabbit correlations" };
const specs = [
  { title: "Energy spectrum", dimension: 1, preferred: "h1_degas_energy_summed", refresh: "2",
    styleLabel: "Scale", styles: [["linear", "Linear"], ["log", "Log counts"]] },
  { title: "Detector matrix", dimension: 2, preferred: "h2_degas_energy_vs_detidx", refresh: "10",
    styleLabel: "Palette", styles: [["Viridis", "Viridis"], ["Cividis", "Cividis"], ["Inferno", "Inferno"]] },
];

async function api(path, options) {
  const response = await fetch(path, options);
  const value = await response.json();
  if (!response.ok) throw new Error(value.error || response.statusText);
  return value;
}

function persist() {
  const value = { subsystem, selections: Object.fromEntries(selections), layout: $("#layout").value, panels: panels.map((panel) => ({
    path: panel.path, refresh: panel.refresh.value, style: panel.style.value, colour: panel.colour.value,
  })) };
  try { localStorage.setItem(stateKey, JSON.stringify(value)); } catch {}
}

function panelFor(spec, index) {
  const card = $("#panel-template").content.firstElementChild.cloneNode(true);
  $("#plots").append(card);
  const find = (name) => card.querySelector(name);
  const { path = "", refresh, style, colour } = saved.panels?.[index] || {};
  const panel = { ...spec, card, path, select: find(".histogram"), chart: find(".chart"),
    status: find(".plot-status"), refresh: find(".refresh"), style: find(".plot-style"),
    colour: find(".line-colour"), epoch: 0 };
  find("h2").textContent = spec.title;
  panel.refresh.value = refresh || spec.refresh;
  if (!panel.refresh.value) panel.refresh.value = spec.refresh;
  find(".style-label").prepend(spec.styleLabel + " ");
  spec.styles.forEach(([value, label]) => panel.style.add(new Option(label, value)));
  panel.style.value = style || spec.styles[0][0];
  if (!panel.style.value) panel.style.value = spec.styles[0][0];
  find(".colour-label").hidden = spec.dimension !== 1;
  if (/^#[0-9a-f]{6}$/i.test(colour)) panel.colour.value = colour;
  panel.select.addEventListener("change", () => {
    panel.path = panel.select.value;
    panel.snapshot = null;
    selections.set(subsystem, panels.map(item => item.path));
    persist();
    restart(panel);
  });
  panel.refresh.addEventListener("change", () => { persist(); restart(panel); });
  const updateStyle = () => {
    persist();
    if (panel.snapshot) render(panel, panel.snapshot);
  };
  panel.style.addEventListener("change", updateStyle);
  panel.colour.addEventListener("change", updateStyle);
  const pause = find(".pause");
  pause.addEventListener("click", () => {
    panel.paused = !panel.paused;
    pause.textContent = panel.paused ? "Resume" : "Pause";
    pause.setAttribute("aria-pressed", String(panel.paused));
    restart(panel);
    if (panel.paused) panel.status.textContent = "Paused";
  });
  return panel;
}

const panels = specs.map(panelFor);
const plotlyReady = api("/api/status").then(({ root, localPlotly }) => {
  rootLabel = root;
  return new Promise((resolve, reject) => {
    const script = document.createElement("script");
    script.src = localPlotly ? "/plotly.js" : "https://cdn.plot.ly/plotly-2.35.2.min.js";
    script.onload = resolve;
    script.onerror = () => reject(new Error("Plotly failed to load. Use --plotly-js for offline use."));
    document.head.append(script);
  });
});
plotlyReady.catch(() => {});

const centers = (edges) => edges.slice(1).map((right, i) => (right + edges[i]) / 2);

async function render(panel, data) {
  const trace = data.dimensions === 1 ? {
    type: "scatter", mode: "lines", x: data.x.edges, y: [...data.bins, data.bins.at(-1)],
    line: { shape: "hv", color: panel.colour.value, width: 1.6 },
  } : {
    type: "heatmap", x: data.x.edges, y: data.y.edges, z: data.bins, colorscale: panel.style.value,
    colorbar: { title: "Counts" }, hoverongaps: false,
  };
  const layout = {
    autosize: true, uirevision: panel.path, paper_bgcolor: "#111a2a", plot_bgcolor: "#0b101a",
    font: { color: "#ccd9ee", family: "system-ui" },
    title: { text: data.title, font: { size: 13 } },
    margin: { l: 62, r: 16, t: 40, b: 56 },
    xaxis: { title: data.x.title, gridcolor: "#223049" },
    yaxis: { title: data.y.title, gridcolor: "#223049",
      ...(data.dimensions === 1 ? { type: panel.style.value, uirevision: panel.path + ":" + panel.style.value } : {}) },
  };
  if (data.dimensions === 1) {
    trace.customdata = [...centers(data.x.edges), null];
    trace.hovertemplate = "%{customdata:.5g}<br>%{y} counts<extra></extra>";
  }
  await Plotly.react(panel.chart, [trace], layout, { responsive: true, displaylogo: false });
}

function restart(panel) {
  clearTimeout(panel.timer);
  panel.request?.abort();
  const epoch = ++panel.epoch;
  if (activeView === "monitor" && !panel.paused && panel.path) refreshPlot(panel, epoch);
}

async function refreshPlot(panel, epoch) {
  panel.request = new AbortController();
  try {
    await plotlyReady;
    if (epoch !== panel.epoch) return;
    const data = await api("/api/histogram?" + new URLSearchParams({ path: panel.path }), { signal: panel.request.signal });
    if (epoch !== panel.epoch) return;
    panel.snapshot = data;
    await render(panel, data);
    if (epoch === panel.epoch) panel.status.textContent = number.format(data.entries) + " entries";
  } catch (error) {
    if (epoch === panel.epoch) {
      panel.status.textContent = error.message;
      discoveredHistograms = false;
    }
  } finally {
    if (epoch === panel.epoch) panel.timer = setTimeout(() => refreshPlot(panel, epoch), 1000 * Number(panel.refresh.value));
  }
}

function groupHistograms(items) {
  const result = new Map();
  for (const item of items) {
    const parts = item.path.split("/");
    const directory = parts[0] === "Histograms" ? parts.slice(1, -1) : parts.slice(0, -1);
    const folder = directory[0] || "Other";
    const name = subsystemAliases.get(folder.toLowerCase()) || folder;
    if (!result.has(name)) result.set(name, []);
    result.get(name).push(item);
  }
  return result;
}

function showSubsystem(name) {
  subsystem = name;
  for (const button of $("#subsystems").children) {
    button.setAttribute("aria-pressed", String(button.textContent === name));
  }
  const items = groups.get(name) || [];
  const remembered = selections.get(name);
  for (const [index, panel] of panels.entries()) {
    const choices = items.filter(({ dimensions }) => dimensions === panel.dimension);
    panel.select.replaceChildren(...choices.map(({ path, title }) => {
      const option = new Option(path, path);
      option.title = title;
      return option;
    }));
    const previous = remembered?.[index] || saved.panels?.[index]?.path;
    const selected = choices.find(({ path }) => path === previous)
      || choices.find(({ path }) => path.split("/").at(-1) === panel.preferred) || choices[0];
    const nextPath = selected?.path || "";
    if (nextPath !== panel.path) {
      panel.snapshot = null;
      if (panel.chart.data) Plotly.purge(panel.chart);
      panel.status.textContent = "";
    }
    panel.path = nextPath;
    panel.select.value = panel.path;
    panel.select.disabled = !selected;
    if (!selected) panel.status.textContent = connected ? "No matching histogram" : "Waiting for ROOT";
    restart(panel);
  }
  if (items.length) selections.set(name, panels.map(panel => panel.path));
  persist();
}

function showTabs() {
  const area = $("#subsystems");
  const names = [...groups.keys()].sort((a, b) => {
    const order = name => defaultSubsystems.includes(name) ? defaultSubsystems.indexOf(name) : defaultSubsystems.length;
    return order(a) - order(b) || a.localeCompare(b);
  });
  area.replaceChildren(...names.map(name => {
    const button = document.createElement("button");
    button.textContent = name;
    button.addEventListener("click", () => showSubsystem(name));
    return button;
  }));
  showSubsystem(groups.has(subsystem) ? subsystem : names[0]);
}

async function reloadHistograms() {
  const button = $("#reload");
  if (button.disabled) return;
  button.disabled = true;
  try {
    const items = await api("/api/histograms");
    connected = true;
    discoveredHistograms = items.length > 0;
    $("#connection").textContent = items.length ? `${rootLabel} · ${items.length} histograms`
      : "ROOT is reachable. No TH1 or TH2 histograms are available.";
    groups = items.length ? groupHistograms(items) : new Map(defaultSubsystems.map(name => [name, []]));
    showTabs();
  } catch (error) {
    connected = false;
    discoveredHistograms = false;
    $("#connection").textContent = "ROOT connection unavailable · " + error.message;
    groups = new Map(defaultSubsystems.map(name => [name, []]));
    showTabs();
  } finally {
    button.disabled = false;
  }
}

function setLayout(value) {
  $("#plots").className = "plots " + value;
  for (const panel of panels) {
    if (panel.chart.data && activeView === "monitor") requestAnimationFrame(() => Plotly.Plots.resize(panel.chart));
  }
}

$("#reload").addEventListener("click", reloadHistograms);
$("#layout").value = saved.layout || "columns";
if (!$("#layout").value) $("#layout").value = "columns";
setLayout($("#layout").value);
$("#layout").addEventListener("change", (event) => { setLayout(event.target.value); persist(); });

document.querySelectorAll("nav button").forEach((button) => button.addEventListener("click", () => {
  activeView = button.dataset.view;
  document.querySelectorAll("nav button").forEach((tab) => tab.removeAttribute("aria-current"));
  button.setAttribute("aria-current", "page");
  $("#monitor").hidden = activeView !== "monitor";
  $("#setup").hidden = activeView !== "setup";
  if (activeView === "monitor") setLayout($("#layout").value);
  panels.forEach(restart);
}));

const form = $("#run-form");
const existingForm = $("#existing-form");
const macroSource = $("#macro-source");
const existingChoice = $("#existing-macro");
const stopRun = $("#stop-run");
const runStatus = $("#run-status");
const runLog = $("#run-log");
const post = (path, value) => api(path, { method: "POST",
  headers: { "Content-Type": "application/json" }, body: JSON.stringify(value) });
let listedMacros;
let runActionPending = false;

function renderRun(status) {
  stopRun.disabled = !status.running || runActionPending;
  document.querySelectorAll('button[value="start"], #existing-form button[type="submit"]')
    .forEach(button => { button.disabled = status.running || runActionPending; });
  runStatus.textContent = status.running ? "ROOT is running"
    : status.exitCode === null ? "No run started" : `ROOT exited (${status.exitCode})`;
  runLog.textContent = status.log;
}

async function runAction(path, payload) {
  if (runActionPending) return;
  runActionPending = true;
  try {
    const status = await post(path, payload);
    runActionPending = false;
    renderRun(status);
  } finally {
    runActionPending = false;
  }
}

async function pollRun() {
  try {
    if (!runActionPending) {
      const status = await api("/api/run");
      if (!runActionPending) renderRun(status);
    }
  } catch (error) {
    runStatus.textContent = error.message;
  } finally {
    setTimeout(pollRun, 1500);
  }
}
pollRun();
const preview = $("#macro-preview");
const download = $("#download");
const setupStatus = $("#setup-status");
const setupReady = api("/api/setup").then((defaults) => {
  form.elements.repository.value = defaults.repository;
  for (const [name, checked] of Object.entries(defaults.subsystems)) {
    const label = document.createElement("label");
    const input = Object.assign(document.createElement("input"), { type: "checkbox", checked, name });
    label.append(input, flags[name] || name);
    $("#flags").append(label);
  }
  for (const path of defaults.files) {
    const label = document.createElement("label");
    const input = Object.assign(document.createElement("input"), { placeholder: "Use preset path", name: path });
    label.append(path.slice(1), input);
    $("#config-files").append(label);
  }
  return defaults;
});
setupReady.catch((error) => { setupStatus.textContent = error.message; });

function invalidateExport() {
  setupRevision++;
  macro = "";
  download.disabled = true;
}
form.addEventListener("input", invalidateExport);
form.addEventListener("submit", async (event) => {
  event.preventDefault();
  invalidateExport();
  setupStatus.textContent = "";
  const revision = setupRevision;
  try {
    const defaults = await setupReady;
    const values = form.elements;
    const settings = {
      repository: values.repository.value.trim(), input: values.input.value.trim(),
      output: values.output.value.trim(), events: values.events.valueAsNumber, port: values.port.valueAsNumber,
      subsystems: Object.fromEntries(Object.keys(defaults.subsystems).map((key) => [key, values[key].checked])),
      files: Object.fromEntries(defaults.files.map((key) => [key, values[key].value.trim()]).filter(([, value]) => value)),
    };
    if (event.submitter?.value === "start") {
      await runAction("/api/run/start", { source: "generated", settings });
      return;
    }
    const response = await post("/api/macro", settings);
    if (revision !== setupRevision) return;
    macro = response.macro;
    preview.textContent = macro;
    download.disabled = false;
    setupStatus.textContent = "Macro ready to download.";
  } catch (error) {
    if (revision !== setupRevision) return;
    preview.textContent = "";
    setupStatus.textContent = error.message;
  }
});
macroSource.addEventListener("change", async () => {
  invalidateExport();
  preview.textContent = "Select Preview macro to show the source.";
  setupStatus.textContent = "";
  const existing = macroSource.value === "existing";
  form.hidden = existing;
  existingForm.hidden = !existing;
  download.hidden = existing;
  if (existing && !listedMacros) {
    try {
      listedMacros = await api("/api/macros");
      existingChoice.replaceChildren(...listedMacros.map(path => new Option(path, path)));
    } catch (error) {
      setupStatus.textContent = error.message;
    }
  }
});
existingChoice.addEventListener("change", () => {
  setupRevision++;
  preview.textContent = "Select Preview macro to show the source.";
});
$("#existing-preview").addEventListener("click", async () => {
  if (!existingChoice.value) return;
  const revision = ++setupRevision;
  try {
    const { macro: source } = await api("/api/macro-preview?" + new URLSearchParams({ path: existingChoice.value }));
    if (revision === setupRevision) preview.textContent = source;
  } catch (error) {
    if (revision === setupRevision) setupStatus.textContent = error.message;
  }
});
existingForm.addEventListener("submit", async (event) => {
  event.preventDefault();
  setupStatus.textContent = "";
  try {
    const args = JSON.parse($("#macro-arguments").value.trim() || "[]");
    await runAction("/api/run/start", { source: "existing", macro: existingChoice.value, arguments: args });
  } catch (error) {
    setupStatus.textContent = error.message;
  }
});
stopRun.addEventListener("click", async () => {
  try {
    await runAction("/api/run/stop", {});
  } catch (error) {
    setupStatus.textContent = error.message;
  }
});
download.addEventListener("click", () => {
  if (!macro) return;
  const url = URL.createObjectURL(new Blob([macro], { type: "text/plain" }));
  const link = Object.assign(document.createElement("a"), { href: url, download: "s100_tests.C" });
  link.click();
  setTimeout(() => URL.revokeObjectURL(url), 1000);
});
showTabs();
reloadHistograms();
setInterval(() => {
  if (activeView === "monitor" && !discoveredHistograms) reloadHistograms();
}, 5000);
