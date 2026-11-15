# Legacy reader stabilisation and regression-test baseline

This document records the **end of the initial safety-hardening phase** before
digitiser-first reader development. It describes what the repository's tests
actually cover and how to avoid silently changing detector reconstruction.

FairRoot, ROOT, and UCESB are upstream dependencies. We do **not** attempt to
retest their internals. We do need to validate how **c4Root** interprets UCESB
data, owns ROOT objects, and constructs its data products.

## Automated CI: the current contract

The GitHub Actions workflow `.github/workflows/frs-safety-regressions.yml`
discovers every `tests/*_test.cxx` source and builds it with C++17,
`-Wall -Wextra -Werror -pedantic`, and UndefinedBehaviorSanitizer. Each
executable must exit successfully. New standalone tests are discovered
automatically; adding one should **not** require editing the workflow.

The current standalone tests exercise production helper logic for:

| Domain | Existing tests | Scope |
| --- | --- | --- |
| FRS | `frs_reader_safety_test.cxx` | Packed reader bounds |
| Germanium FEBEX | `germanium_packed_safety_test.cxx` | Channel/trace extent guards |
| BGO/TAMEX | `bgo_packed_safety_test.cxx` | Event/hit bound checking |
| Shared TAMEX | `tamex_packed_safety_test.cxx`, `detector_fixture_regression_test.cxx` | Short events, hit-array counts, channel/fine-time bounds |
| FATIMA VME | `fatima_vme_packed_safety_test.cxx`, `fatima_vme_qdc_safety_test.cxx`, `fimp_qdc_fixture_regression_test.cxx` | TDC block validity, independent QDC fields and waveform sample counts |
| FIMP | `fimp_fine_time_bins_test.cxx`, `fimp_multihit_safety_test.cxx`, `fimp_qdc_fixture_regression_test.cxx` | Fine-time bins, packed/multihit bounds |
| MCP | `mcp_timestamp_safety_test.cxx`, shared TAMEX tests | Unsigned WR assembly and TAMEX boundary decisions |
| BB7 | `bb7_febex_index_safety_test.cxx`, `cluster_time_overlap_test.cxx` | FEBEX indices and safe interval overlap |
| Stefan | `stefan_index_safety_test.cxx`, `stefan_packed_safety_test.cxx`, `stefan_timestamp_safety_test.cxx` | Indexing, payload counts and WR assembly |

Test and fixture expectations must be independently reviewed: do not update
expected values only to make a failing test pass.

## What green CI does **not** prove

- The full c4Root/FairRoot project compiles in a particular experiment's
  software environment, or ROOT dictionary generation succeeds.
- A reader's `Init`, `Read`, `Reset`, and destructor are lifecycle-safe.
- The ROOT calibration file read/write paths are free of ownership errors.
- A valid event yields the expected detector-specific channels, multiplicities,
  calibrated energies, or time correlations.
- Legacy and refactored digitiser readers agree event by event.
- Memory usage and throughput on long, high-rate runs are acceptable.

These are **c4Root integration and scientific regression checks** to add as
representative inputs and the software environment become available, not tests
of upstream FairRoot implementation.

## Suggested experiment-side acceptance checklist

Before merging a reader change affecting c4Root object ownership, event
interpretation, calibration, or reconstruction:

1. Configure and compile c4Root against the experiment's supported ROOT,
   FairRoot and UCESB installation (including dictionary generation).
2. Exercise reader initialisation, a **zero-event** run, a short run and
   orderly shutdown. For calibration code, exercise **both** histogram creation
   and loading from an existing file.
3. On a fixed, reproducible input and configuration, compare the existing and
   changed code's event counts, channel occupancy, raw/cal/hit multiplicities,
   WR timestamps, reconstructed times, and relevant energy spectra.
4. For performance-affecting changes, record events/s, peak RSS, and input
   size or event count. Repeat with identical compiler and configuration.
5. Inspect skipped/malformed-hit counters; explain discrepancies rather than
   automatically accepting them.
6. Record the input identity/checksum, configuration, commit SHA, compiler,
   ROOT/FairRoot/UCESB versions, and any known intentional output differences.

Do not commit collaboration-restricted experimental runs to the repository.
Synthetic UCESB structures or small authorised datasets are preferable for
shareable fixtures. A future c4Root smoke test should run the same input through
both the legacy and new digitiser paths and compare machine-readable summaries.

## Handover to digitiser-first architecture

The desired boundary is:

`UCESB -> digitiser-specific reader -> digitiser Raw -> detector Raw2Cal -> Cal -> Hit -> analysis`

The new shared TAMEX4 decoder must initially run alongside legacy readers.
Preserve the UCESB raw fine-time words, module identity, channel identity,
edge polarity and timestamp information; do not hide detector-specific
calibration or edge-matching assumptions in the generic decoder.

**Gate for a pilot migration:** demonstrate parity on deterministic tests for
valid and malformed TAMEX payloads, then compare c4Root output against the
legacy reader on representative events. Keep ROOT object names/branch schemas
unchanged unless an explicit migration is reviewed.

## Deferred, not forgotten

- Full reader lifecycle coverage and sanitizer-backed integration runs
  depend on a suitable experiment-side build/runtime.
- An ongoing audit may still find leaks or physics edge cases; this document
  is not a blanket claim that every detector is bug-free.
- Reader/Raw2Cal duplication and shared calibration storage are architectural
  topics for the TAMEX4 phase; avoid large changes during final hardening.
- Online Python monitoring, experiment configuration redesign and profiling
  remain separate later workstreams.
