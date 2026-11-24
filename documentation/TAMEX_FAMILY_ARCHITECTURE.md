# TAMEX digitiser family

## Readout and calibration

The S100 FATIMA, bPlast and BGO readers register their native UCESB structures.
They share the electronics transfer in `TamexReader.h`, which reads the board
columns and writes `TamexRawData` records with board and trigger metadata, White
Rabbit time, epoch words and edges. The format traits describe TAMEX4 and are
independent of the physical board slot.

`TamexFineTimeCalibration` builds the fine-time tables. Its implementation reads
the ROOT histogram files used by the detector tasks. `TamexPulseBuilder.h` uses
those tables to pair leading and trailing edges and supplies the per-channel
Twinpeaks records consumed by the existing fast/slow matching in Raw2Cal.

Detector mapping and detector calibration stay in the detector tasks. Compare
event-level results against recorded legacy outputs when migrating an experiment.

## Test

Run its test from the repository root:

```bash
g++ -std=c++17 -O1 -g -Wall -Wextra -Werror -pedantic \
  -fsanitize=undefined -fno-sanitize-recover=all \
  tests/tamex_family_decoder_test.cxx -o /tmp/tamex_family_decoder_test
/tmp/tamex_family_decoder_test
```
