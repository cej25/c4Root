# FATIMA TAMEX migration — validation setup (draft PR #302)

The legacy `FatimaReader` is still the default. The alternative path is
`TamexReader → TamexRawData → FatimaRaw2Cal → FatimaTwinpeaksCalData`.
Do not merge the migration until a full build and event-by-event comparison pass.

## Opt in using an existing experiment macro

The existing `macros/despec/old/s181_online.C` (similarly s100/s143) constructs
FATIMA from `ucesb_struct.fatima`. To test the new path in a **copy** of that
macro, replace the existing `FatimaReader` construction and registration:

```cpp
constexpr std::uint16_t fatima_source = 10; // unique among TAMEX readers
TamexReader* unpackfatima = new TamexReader(
    (EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima,
    offsetof(EXT_STR_h101, fatima),
    fatima_source);
unpackfatima->SetOnline(true);
source->AddReader(unpackfatima);
```

Keep the experiment's existing FATIMA `Raw2Cal` task, and configure it **before**
`run->AddTask(calfatima)`:

```cpp
FatimaRaw2Cal* calfatima = new FatimaRaw2Cal();
calfatima->UseTamexRawInput(
    fatima_source,
    config_path + "/fatima/fine_time_s181_8June.root");
run->AddTask(calfatima);
```

Do **not** register both `FatimaReader` and `TamexReader` on the same
UCESB FATIMA bank in the same run: both readers initialise the unpacker's
memory and the two paths would not produce a controlled comparison.
Instead run the legacy and new configurations separately over the **same**
input events and use separate output filenames.

The initial opt-in path **requires** pre-existing, unweighted legacy
`fine_time_hits_<board>_<channel>` histograms (1024 bins for each of the
4 boards × 33 channels). Online fine-time calibration is not yet supported
for this path. Avoid enabling it for production until validation is complete.

## Compare

Start with an identical short event range and fixed calibration file. Compare:

- per-event raw pulse and calibrated hit multiplicities, board/channel IDs,
  trigger timestamps and White Rabbit timestamps
- fine-time lookup values (including empty channels), leading/trailing edges,
  fast and slow ToT, detector mapping and calibrated energy
- timestamp differences, coincidence spectra, and any channel-ordering or
  invalid-fine discrepancies

Current CI only runs ROOT-free unit tests. A successful full ROOT/FairRoot build,
matching generated dictionaries and real FATIMA event-parity checks are still
required before this migration can be merged.
