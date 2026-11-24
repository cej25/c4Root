# c4Root S100 Dashboard

Start the dashboard from your c4Root checkout with Python 3. It listens on
`127.0.0.1:8050`.

```sh
python3 tools/s100-dashboard/dashboard.py --root-url http://127.0.0.1:6969
```

Open <http://127.0.0.1:8050>. Use `--root-url` to point the dashboard at the
monitoring address of an existing c4Root run. You can also forward the ROOT
port over SSH and use the forwarded local address. The browser loads Plotly.js
from its CDN by default. For an offline DAQ network, pass
`--plotly-js /path/to/plotly-2.35.2.min.js` with a local copy of the bundle.

## Live Monitor

Choose a subsystem tab, then select one TH1 spectrum and one TH2 matrix.
Tabs follow the top-level histogram folders published by the ROOT run. While
waiting for a run, the tabs are FRS, AIDA, bPlast, FATIMA and DEGAS.
Histogram selections are remembered per tab. The last discovered tabs remain
after ROOT exits, including after a page reload. The currently displayed
plots retain their last snapshots until you switch tabs or reload the page.
When available, the initial plots use the DEGAS summed energy and energy
versus detector index. The plot panels have independent refresh and pause
controls. Zoom is retained during refresh. The layout, selection, refresh
interval, count scale and palette are stored in the browser. Use **Reload
histograms** after connecting or starting a run that publishes new plots.
The display uses regular X and Y bins and omits underflow and overflow.
Only the monitor view polls histograms.

## Run Setup

Enter a stream or transport URL such as `stream://host:6002`, or the path to
an LMD replay on the machine running ROOT. Set the detector and diagnostic
switches, optionally override the config paths, and select **Preview macro**.
Download the macro as `s100_tests.C` and run it from an environment where
the c4Root libraries are available.

```sh
root -l /path/to/downloaded/s100_tests.C
```

The export uses this checkout's `macros/tests/s100_tests.C` as its template.
The repository path must point to the c4Root checkout on the run machine,
including the generated S100 unpacker headers and built unpacker. Config
overrides are interpreted on that machine. The S100 UCESB command requires
repository and input paths without spaces. The exported macro uses FairRoot
online tasks for both live input and replay. Start it manually, then point
the dashboard at its ROOT port.

### Launch from the dashboard

Start the Python dashboard from the same shell environment you use to run
ROOT. Under **Macro source**, choose **Generate from settings** or **Use an
existing macro**. The existing macro picker lists `.C` files
under the checkout's `macros/` directory. Choose **Preview macro** to read it
before running. For a macro with arguments, enter a JSON array in the order
expected by that macro, such as `["stream://host:6002", 10000]`. Leave the field
empty to use its defaults.

**Start run** launches ROOT on the dashboard machine and shows the latest
output. Existing macros run with their containing directory as the working
directory. Generated macros run from the checkout root. **Stop run** sends SIGTERM to the dashboard run and its process
group. The dashboard manages one run at a time. Use the ROOT HTTP port
configured by `--root-url` and reload the histogram list after ROOT starts.
