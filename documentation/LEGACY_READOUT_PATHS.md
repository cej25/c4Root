# Legacy readout paths

Inventory for the FATIMA/TAMEX migration branch, based on `ad3d8833`. It covers the legacy paths alongside the structured FATIMA, bPlast, BGO and DEGAS readouts. BB7 has already retired its legacy raw branches. Leave other detector pipelines and experiment-specific UCESB layouts in place until their migrations are validated.

A file listed for removal is a candidate once its callers and any required ROOT tree support have been migrated. Files listed for updates also serve current paths or consume their outputs.

## FATIMA TAMEX

`FatimaReader` writes `FatimaRawData`. `FatimaRaw2Cal` can still read a persisted `FatimaTwinpeaksData` branch. It can also read the older standalone `TamexRawData` branch through `UseTamexRawInput`. With the current `FatimaRawData.TAMEX` input, `BuildTamexLegacyHits` creates transient `FatimaTwinpeaksData` pulses for the same fast/slow matcher. Retiring old tree input alone leaves that internal dependency in place.

- **Remove after both dependencies are gone:** `c4data/fatimaData/FatimaTwinpeaksData.{h,cxx}`.
- **Update:** `c4source/fatima/FatimaRaw2Cal.{h,cxx}`. Move the matcher to the pulse representation used by the new path, then retire the old branch lookup, transient `TClonesArray` and standalone TAMEX input option when their callers have moved. Preserve `FatimaTwinpeaksCalData` and `FatimaTimeMachineData` for their consumers.
- **Review raw-type includes:** `analysis/correlations/FrsFatimaCorrelations.cxx`, `analysis/correlations/nearline/FrsFatimaCorrelationsNearline.cxx` and the commented example in `c4source/test/TestReader.cxx`.

## bPlast and BGO TAMEX

Both readers still default to the old path. On that path they do fine-time calibration and emit Twinpeaks pulses. With `UseTamexRawOutput` and `UseTamexRawInput`, the readers transfer raw boards and the calibration tasks build pulses in memory. The current pulse matcher still uses the same Twinpeaks classes.

| Detector | Candidate data files | Reader and calibration files to update | Branch transition |
| --- | --- | --- | --- |
| bPlast | `c4data/bplastData/bPlastTwinpeaksData.{h,cxx}` | `c4source/bplast/bPlastReader.{h,cxx}`, `c4source/bplast/bPlastRaw2Cal.{h,cxx}` | `bPlastTwinpeaksData` → `bPlastRawData`. Preserve `bPlastTwinpeaksCalData`. |
| BGO | `c4data/bgoData/BGOTwinpeaksData.{h,cxx}` | `c4source/bgo/BGOReader.{h,cxx}`, `c4source/bgo/BGORaw2Cal.{h,cxx}` | `BGOTwinpeaksData` → `BGORawData`. Preserve `BGOTwinpeaksCalData`. |

- Move the remaining macros to board input before removing the readers' old pulse and fine-time paths. Update the fast/slow matchers before deleting the data classes. Include bPlast trigger-3 records in comparisons, including events with no edges.
- Recheck `c4source/bgo/BGOPackedSafety.h` and its test coverage after removing the BGO reader’s pulse path.
- Keep the shared `c4data/digitisers/tamexData/TamexRawData.{h,cxx}`, `c4source/digitisers/tamex/TamexReader.h`, `TamexFineTimeCalibration.{h,cxx}` and `TamexPulseBuilder.h`. Review the Twinpeaks-specific adapter in `TamexPulseBuilder.h` once all three detectors use their new pulse representation. Preserve fine-time histogram compatibility and pairing behavior. `c4source/base/TamexPackedSafety.h` also serves the shared reader and MCP.
- Keep `tests/tamex_family_decoder_test.cxx` and `tests/fatima_tamex_raw_pipeline_test.cxx`. Update their pulse checks as the representation changes.

## FATIMA VME

`FatimaReader` decodes into `FatimaRawData.VMEChain`. Many macros still attach `FatimaVmeReader`, which publishes `FatimaVmeData`, `FatimaVmeQDCData` and `FatimaVmeTDCData` for `FatimaVmeRaw2Cal`. This includes `macros/tests/s100_tests.C`. Using `FatimaReader` by itself does not tell which calibration path the macro takes.

| Files | Work before retirement |
| --- | --- |
| `c4source/fatima/FatimaVmeReader.{h,cxx}`, `FatimaVmeRaw2Cal.{h,cxx}`, `c4data/fatimaData/FatimaVmeData.{h,cxx}` | Switch the macros and old-tree readers after validating the new output. These are removal candidates once those consumers are gone. |
| `c4source/fatima/FatimaRaw2Cal.{h,cxx}`, `FatimaVmeCalibrator.{h,cxx}` | Keep the detector raw path. Review `UseVmeRawInput` and the fallback for separate `V1751RawData` and `V1290RawData` ROOT branches. The underlying hit types also serve the structured FATIMA and BB7 paths. Keep `c4data/digitisers/vmeData/VmeDigitiserRawData.{h,cxx}`. |
| `c4data/fatimaData/FatimaVmeCalData.{h,cxx}` | Review individual types. This file pair holds the older calibrated types and the new `FatimaVmeQdcCalHit` and `FatimaVmeTdcCalHit` types. Keep the pair for the new output. |
| `analysis/online/fatima/FatimaVmeOnlineSpectra.{h,cxx}`, `analysis/nearline/fatima/FatimaVmeNearlineSpectra.{h,cxx}`, `analysis/correlations/nearline/WhiterabbitCorrelationNearline.{h,cxx}`, `analysis/correlations/online/WhiterabbitCorrelationOnline.{h,cxx}` | Review raw diagnostics and the old calibrated branches `FatimaVmeCalData`, `FatimaVmeQDCCalData`, `FatimaVmeTDCCalData`, `FatimaVmeResiduals` and `FatimaVmeTimeMachineData`. |

The new calibrator publishes separate QDC and TDC calibrated hits. Before removing the old task, check detector assignment, calibrated timing and spectra, residual signals, and Time Machine output used by the affected runs. Keep the common VME decoder, its safety helpers, `tests/vme_digitiser_decode_test.cxx` and `tests/s100_fatima_vme_subevent_test.py`.

## Germanium and DEGAS FEBEX

The legacy summary path uses `GermaniumReader` → `GermaniumFebexData` → `GermaniumRaw2Cal`. The DEGAS path uses `DegasReader` → `DegasRaw2Cal` → `DegasCal2Anl` with its own configuration, hit class, and analysis tasks. The existing `s100` unpacker serves legacy macros. The migrated S100 macro uses the `s100degas` unpacker and the DEGAS branches.

- **Removal candidates:** `c4source/germanium/`, `c4data/germaniumData/` (including `TGermaniumConfiguration`), and the legacy detector spectra, lab and resolution tasks. Keep the shared FEBEX decoder and the common BGO readout and calibration.
- **Trace path:** Legacy trace workflows use `GermaniumTraceReader` and `GermaniumLabTest`. The new trace bank is supported by `DegasReader` and can be monitored through `DegasLabTest`.
- **Calibrated outputs:** Existing Germanium trees and interim `DegasCalData` branches containing `GermaniumCalData` require the legacy dictionary. Rebuild the latter with `DegasRaw2Cal` from `DegasRawData` to use the new tasks. Check Time Machine task configuration for `DegasTimeMachineData`.
- **Analysis:** DEGAS has equivalents of the built detector and correlation tasks. Select `"Degas"` for the DEGAS input in shared White Rabbit tasks. Migrate and validate each legacy experiment macro before removing its tasks, generated banks or calibration files.

## Call sites to check

These are tracked references, including commented examples and tasks with selectable input. Review the control flags and branch names at each call site.

### FATIMA VME

- `macros/despec/old/` — `s100_online_new.C`, `s181_online.C`
- `macros/nearline_testing/` — `make_trees.C`, `nearline.C`
- `macros/tests/` — `Calums_test.C`, `c_fat_test_2025.C`, `c_fat_test_2025_histos.C`, `c_fat_test_2025_trees.C`, `despec_s100_tests.C`, `fatvme_online.C`, `make_trees.C`, `nearline.C`, `s100_tests.C`, `s181_tests.C`
- `macros/tests/old/` — `s100_online_thresholds.C`

### bPlast and BGO

- `macros/despec/old/` — `s100_online_new.C`, `s101_nearlineish.C`, `s101_nearlineish_histo.C`, `s101_online.C`, `s115_online.C`, `s181_online.C`
- `macros/despec/` — `s115_online.C`
- `macros/nearline_testing/` — `make_trees.C`
- `macros/tests/` — `Calums_test.C`, `bplast_make_trees.C`, `c_fat_test_2025.C`, `despec_s100_tests.C`, `fatvme_online.C`, `jb_s101.C`, `make_trees.C`, `run_online_bplast.C`, `run_online_jeroen.C`, `s100_tests.C`, `s101_tests.C`, `s115_make_trees.C`, `s115_tests.C`, `s181_tests.C`
- `macros/tests/old/` — `s100_online_thresholds.C`

### Germanium FEBEX

- `macros/despec/old/` — `s100_online_new.C`, `s101_nearlineish.C`, `s101_nearlineish_histo.C`, `s101_online.C`, `s115_online.C`, `s181_online.C`
- `macros/despec/` — `s115_online.C`
- `macros/tests/` — `Calums_test.C`, `c_fat_test_2025.C`, `despec_s100_tests.C`, `fatvme_online.C`, `jb_s101.C`, `run_aida_online.C`, `run_bb7_online.C`, `run_ge_online.C`, `s101_tests.C`, `s115_make_trees.C`, `s115_tests.C`, `s181_tests.C`
- `macros/tests/old/` — `s100_online_thresholds.C`

### Germanium and DEGAS analysis

- `analysis/correlations/` — `AidaGermaniumCorrelations.cxx`, `FrsGermaniumCorrelations.cxx`, `bPlastGermaniumCorrelations.cxx`
- `analysis/correlations/triplePlusCorrs/` — `BetaIonCorrelations.cxx`
- `analysis/nearline/bgo/` — `BGONearlineSpectra.cxx`
- `analysis/correlations/nearline/` — `FatimaTimingAnalysisSummedGeGated.cxx`, `FrsGermaniumCorrelationsNearline.cxx`
- `analysis/nearline/germanium/` — `GermaniumNearlineSpectra.cxx`, `GermaniumResolution.cxx`
- `analysis/correlations/nearline/` — `WhiterabbitCorrelationNearline.cxx`
- `analysis/online/bgo/` — `BGOOnlineSpectra.h`
- `analysis/online/germanium/` — `GermaniumLabTest.cxx`, `GermaniumOnlineSpectra.cxx`, `GermaniumOnlineSpectra.h`
- `analysis/correlations/online/` — `BB7GermaniumCorrelationsOnline.cxx`, `bPlastGermaniumCorrelationsOnline.h`
- `c4source/germanium/` — `GermaniumCal2Anl.cxx`, `GermaniumRaw2Cal.cxx`, `GermaniumReader.cxx`, `GermaniumTraceReader.cxx`

## Before deleting a path

1. Check which experiments and saved ROOT trees still require it. Use recorded events to compare the old and new outputs. Update online, nearline and offline call sites and keep any branches still needed for replay.
2. Search the repository for the retired class and branch names, including macro backups, tests and analysis headers. Update `c4source/CMakeLists.txt`, `c4source/SourceLinkDef.h`, `c4data/CMakeLists.txt`, `c4data/DataLinkDef.h`, and the corresponding analysis CMake and dictionary entries if a task is retired. Update [BranchList.txt](BranchList.txt) and [the TAMEX architecture note](TAMEX_FAMILY_ARCHITECTURE.md) for schema changes.
3. Check generated-header consumers before removing a header from the build. The FATIMA, bPlast and BGO native headers still feed the structured paths. The Germanium summary and trace headers are `c4source/germanium/ext_h101_germanium.h` and `c4source/germanium/ext_h101_germanium_traces.h`. If a UCESB layout needs to change, regenerate its header using the unpacker's `STRUCT_HH` output and verify the reader against it.
