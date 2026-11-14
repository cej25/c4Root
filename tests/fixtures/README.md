# Detector regression fixtures

This directory holds small synthetic payloads with independently reviewed
expected outcomes. The standalone C++ tests are automatically compiled and
run by the detector safety GitHub Actions workflow.

## TAMEX payload cases

`tamex_payload_cases.txt` is a whitespace-delimited table. Every non-comment
row contains:

```text
case_name event_bytes hit_index epoch_count coarse_count fine_count channel_count edge_count channel_id fine_code expected_budget expected_complete expected_accepted
```

The corresponding `tests/detector_fixture_regression_test.cxx` exercises the
**production** `c4_tamex_packed_safety` helpers and checks their combined
boundary decisions. It covers empty and truncated events, each independently
short auxiliary array, illegal channel/fine-time codes, and maximum capacity.
Do not silently change expected outputs simply to make a regression pass;
review any changed semantics against the unpacker format.

Run from the repository root:

```bash
g++ -std=c++17 -O1 -g -Wall -Wextra -Werror -pedantic \
  -fsanitize=undefined -fno-sanitize-recover=all \
  tests/detector_fixture_regression_test.cxx -o /tmp/detector_fixtures
/tmp/detector_fixtures
```

## Scope and next step

These are **not** UCESB/FairRoot integration tests: they verify the shared
detector payload validation path using synthetic metadata. They do not unpack
LMD data, create real `TClonesArray` hits, measure physics spectra, or compare
experimental reconstruction outputs.

For a true end-to-end baseline, store a small reproducible run input (or a
synthetic UCESB event source), the exact configuration and code revision, and
reference output summaries for raw/cal/hit multiplicity, detector-channel
occupancy, energy and timing histograms. Never commit restricted experimental
data. Execute the reference run in an environment with matching
UCESB/ROOT/FairRoot and fail on unexplained differences. The present fixture
format is deliberately small so it can grow without ROOT-dependent CI.
