"use strict";

class MatrixProjections {
  constructor(panel) {
    this.panel = panel;
    this.states = new Map();
    this.region = document.createElement("section");
    this.region.className = "projection-grid";
    this.region.hidden = true;
    this.views = ["x", "y"].map(axis => this.makeView(axis));
    this.panel.card.append(this.region);
  }

  makeView(axis) {
    const card = document.createElement("div");
    card.className = "projection-card";
    const heading = document.createElement("h3");
    heading.textContent = axis.toUpperCase() + " projection";
    const mode = document.createElement("select");
    mode.setAttribute("aria-label", axis.toUpperCase() + " projection tool");
    for (const label of ["Zoom", "Gate", "Marker"]) mode.add(new Option(label));
    const clearGate = document.createElement("button");
    clearGate.textContent = "Clear gate";
    const clearMarkers = document.createElement("button");
    clearMarkers.textContent = "Clear markers";
    const actions = document.createElement("div");
    actions.className = "projection-actions";
    actions.append(mode, clearGate, clearMarkers);
    const chart = document.createElement("div");
    chart.className = "projection-chart";
    const summary = document.createElement("p");
    summary.className = "projection-summary";
    card.append(heading, actions, chart, summary);
    this.region.append(card);
    const view = { axis, chart, mode, summary, clearGate, clearMarkers };
    mode.addEventListener("change", () => this.drawView(view, this.panel.snapshot));
    clearGate.addEventListener("click", () => {
      this.state[axis].gate = null;
      this.update();
    });
    clearMarkers.addEventListener("click", () => {
      this.state[axis].markers.clear();
      this.update();
    });
    return view;
  }

  get state() {
    const path = this.panel.path;
    if (!this.states.has(path)) {
      this.states.set(path, {
        x: { gate: null, markers: new Set() },
        y: { gate: null, markers: new Set() },
      });
    }
    return this.states.get(path);
  }

  setOpen(open) {
    this.region.hidden = !open;
    if (open) this.update();
  }

  update() {
    const data = this.panel.snapshot;
    if (data && this.panel.chart.data) Plotly.relayout(this.panel.chart, { shapes: this.matrixShapes(data) });
    this.draw(data);
  }

  matrixShapes(data) {
    return ["x", "y"].flatMap(axis => {
      const gate = this.state[axis].gate;
      if (!gate) return [];
      const [i, j] = gate;
      const edges = data[axis].edges;
      if (j + 1 >= edges.length) return [];
      const shape = axis === "x"
        ? { x0: edges[i], x1: edges[j + 1], y0: 0, y1: 1, xref: "x", yref: "paper" }
        : { y0: edges[i], y1: edges[j + 1], x0: 0, x1: 1, yref: "y", xref: "paper" };
      return [{ ...shape, type: "rect", line: { color: axis === "x" ? "#7ce3d3" : "#ffb66b", width: 1 },
        fillcolor: axis === "x" ? "rgba(124,227,211,.15)" : "rgba(255,182,107,.15)" }];
    });
  }

  async draw(data) {
    if (this.region.hidden && data) return;
    await Promise.all(this.views.map(view => this.drawView(view, data)));
  }

  async drawView(view, data) {
    const { axis, chart, mode, summary, clearGate, clearMarkers } = view;
    if (!data) {
      if (chart.data) Plotly.purge(chart);
      view.bound = false;
      summary.textContent = "Select a matrix to view projections.";
      clearGate.disabled = clearMarkers.disabled = true;
      return;
    }
    const other = axis === "x" ? "y" : "x";
    const edges = data[axis].edges;
    const state = this.state;
    const orthogonalCount = data[other].edges.length - 1;
    const [first, last] = state[other].gate || [0, orthogonalCount - 1];
    const values = Array(edges.length - 1).fill(0);
    for (let y = 0; y < data.bins.length; y++) {
      if (axis === "x" && (y < first || y > last)) continue;
      const row = data.bins[y];
      const start = axis === "x" ? 0 : first;
      const end = axis === "x" ? row.length - 1 : Math.min(last, row.length - 1);
      for (let x = start; x <= end; x++) values[axis === "x" ? x : y] += row[x];
    }
    const positions = edges.slice(1).map((value, i) => (edges[i] + value) / 2);
    const colour = axis === "x" ? "#7ce3d3" : "#ffb66b";
    const gate = state[axis].gate;
    const marked = [...state[axis].markers].filter(i => i < positions.length);
    const shape = gate && gate[1] < positions.length ? [{
      type: "rect", x0: edges[gate[0]], x1: edges[gate[1] + 1], y0: 0, y1: 1, yref: "paper",
      line: { width: 1, color: colour }, fillcolor: "rgba(160,194,230,.17)",
    }] : [];
    const path = this.panel.path;
    await Plotly.react(chart, [{
      type: "scatter", mode: "lines", x: edges, y: [...values, values.at(-1)],
      line: { shape: "hv", color: colour }, hoverinfo: "skip",
    }, {
      type: "scatter", mode: "markers", x: positions, y: values,
      marker: { opacity: 0, size: 12 }, hovertemplate: "%{x:.6g}<br>%{y} counts<extra></extra>",
    }, {
      type: "scatter", mode: "markers+text", x: marked.map(i => positions[i]), y: marked.map(i => values[i]),
      text: marked.map(i => Number(positions[i].toPrecision(6))), textposition: "top center",
      marker: { color: colour, symbol: "diamond", size: 9 }, hoverinfo: "skip",
    }], {
      uirevision: path, selectionrevision: Date.now(), dragmode: mode.value === "Gate" ? "select" : "zoom",
      selectdirection: "h", showlegend: false, shapes: shape, paper_bgcolor: "#111a2a", plot_bgcolor: "#0b101a",
      font: { color: "#ccd9ee", family: "system-ui" }, margin: { l: 55, r: 15, t: 12, b: 48 },
      xaxis: { title: data[axis].title || axis.toUpperCase(), gridcolor: "#223049" },
      yaxis: { title: "Counts", gridcolor: "#223049" },
    }, { responsive: true, displaylogo: false });
    if (this.panel.path !== path) return;
    clearGate.disabled = !gate;
    clearMarkers.disabled = !marked.length;
    summary.textContent = gate && gate[1] < positions.length
      ? `Gate ${edges[gate[0]].toPrecision(6)} to ${edges[gate[1] + 1].toPrecision(6)}`
      : "No gate";
    if (view.bound) return;
    view.bound = true;
    chart.on("plotly_selected", event => {
      if (mode.value !== "Gate" || !event?.range?.x) return;
      const currentEdges = this.panel.snapshot[axis].edges;
      const [low, high] = [...event.range.x].sort((a, b) => a - b);
      const begin = currentEdges.findIndex((edge, i) => edge < high && currentEdges[i + 1] > low);
      if (begin < 0) return;
      let end = begin;
      while (end + 2 < currentEdges.length && currentEdges[end + 1] < high) end++;
      this.state[axis].gate = [begin, end];
      this.update();
    });
    chart.on("plotly_click", event => {
      if (mode.value !== "Marker") return;
      const point = event.points.find(item => item.curveNumber === 1);
      if (!point) return;
      const markers = this.state[axis].markers;
      if (markers.has(point.pointIndex)) markers.delete(point.pointIndex);
      else markers.add(point.pointIndex);
      this.update();
    });
  }
}
