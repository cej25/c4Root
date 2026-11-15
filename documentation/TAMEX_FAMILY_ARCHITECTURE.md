# TAMEX digitiser family — architecture and legacy audit

Status: **initial specification / non-production prototype**. The old detector readers
remain in use. Do not switch experiments to the new decoder without event-level
comparison against recorded legacy outputs.

## Goal and pipeline

`UCESB -> TamexReader (family + selected format) -> TamexRawData ->
 detector Raw2Cal -> detector Cal -> Hit -> analysis`

- A reader understands **electronics**, not the connected detector. Detector
  identity, channel mapping, physical calibration and detector-specific hit
  building first appear at **Raw2Cal**.
- A version-specific format describes how words are encoded. Shared parsing,
  validation and timing/calibration helpers are implemented once in the TAMEX
  family, rather than copied for TAMEX4 and future supported versions.
- Treat a **format version** and a **physical module instance** separately:
  multiple modules can use identical decoder code but distinct identities,
  calibration tables and clock configuration.

## Test

Run its test from the repository root:

```bash
g++ -std=c++17 -O1 -g -Wall -Wextra -Werror -pedantic \
  -fsanitize=undefined -fno-sanitize-recover=all \
  tests/tamex_family_decoder_test.cxx -o /tmp/tamex_family_decoder_test
/tmp/tamex_family_decoder_test
```
