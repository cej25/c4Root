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
- A future `TamexRawData` ROOT class should be added to `c4data`. Its persistent
  schema will need review, including event/module identifiers, trigger and WR
  metadata, epoch markers, edge polarity and raw coarse/fine codes.
- Format differences should use traits/configuration when only constants
  differ; use a new parser strategy only when word layouts genuinely differ.
  Do not pre-emptively invent TAMEX5/TAMEX6 formats without specifications.

## Legacy source comparison (November 2026)

| Aspect | BGOReader | FatimaReader | bPlastReader | H10MCPReader |
| --- | --- | --- | --- | --- |
| Electronics input | `bgo_tamex` | `fatima_tamex` | `bplast_tamex` | `mcp_tamex` |
| Header and hit budget | 3 words; max 1024 entries | Same | Same | Same |
| Channel encoding | `& 0x7f`; 33 slots | Same | Same | Same |
| Epoch encoding | nonzero epoch word, `& 0x0fffffff` | Same | Same | Same |
| Coarse time | `& 0x7ff` | Same | Same | Same |
| Edge type | low bit: 1=lead | Same | Same | Same |
| Fine-time calibration | 1024-bin occupancy LUT, 5 ns period | Same algorithm | Same algorithm | Same algorithm |
| Channel zero | Accepted trigger-time fields | Same | Same | Same |
| Lead/trail output | Emit matched lead+trail | Emit matched lead+trail | Emit matched lead+trail | **Also emits on each lead** |
| Special output | Matched BGO Twinpeaks | Matched FATIMA Twinpeaks | **Trigger==3 creates a special raw object** | Leading and matched-trailing MCP Twinpeaks |
| Result schema | `BGOTwinpeaksData` | `FatimaTwinpeaksData` | `bPlastTwinpeaksData` | `H10MCPTwinpeaksData` |

All four currently check for descending channel order and track epoch changes,
fine-time faults and incomplete arrays. Their failure counters, calibration
lifecycle, and output-object construction are presently entangled with parsing.

**Critical compatibility points:**

1. MCP emits data upon the leading edge as well as after matching a trailing
   edge. That is *not* equivalent to the matched-pair-only pattern of BGO and
   FATIMA. Do not move that behaviour into the shared raw decoder.
2. bPlast emits a special Twinpeaks record for trigger code 3 even if the
   board has no time-hit payload. Preserve this event/trigger metadata through
   the generic interface, then reproduce the legacy behaviour downstream.
3. Existing readers use per-board state, a trigger channel zero, calibration
   histograms and WR subsystem/timestamp metadata. A future digitiser Raw
   event must preserve all this information.
4. The legacy code processes nonzero epoch words before interpreting a channel
   and treats `0x3ff` as a fine-time failure. Raw decoding should preserve
   invalid fine codes with explicit flags; detector migration must deliberately
   reproduce legacy **filtering** where intended.
5. The legacy channel-order assumption and epoch-on-channel-change checks
   are electronics diagnostics, but fatal reactions belong in configurable
   policy rather than in a reusable low-level parser.
6. The 1024-bin fine-time lookup uses the cumulative histogram midpoint,
   falling back to a linear mapping when there are no entries. The common
   algorithm can be extracted later without moving detector time offsets into
   the digitiser decoder.
7. Existing readers retain the last leading edge within the board, not a
   separate pending lead for each channel. Changing pairing state may fix edge
   cases but would be a **physics-sensitive behaviour change** requiring
   explicit reference-event evidence.

## First standalone component

`c4source/digitisers/tamex/TamexDecoder.h` introduces:

- `PackedBoardView`: borrowed UCESB-style column pointers and independently
  populated counts (no ROOT/FairRoot dependency).
- `Tamex4Format`: version-specific observed masks, capacities and
  invalid-fine marker, with no claims about other hardware generations.
- `Decoder<Format>`: shared, allocation-free iteration over the event,
  producing ordered epoch/edge `RawWord` records via a callback.
- `DecodeStats`: counters for incomplete words, invalid channels, fine-time
  anomalies, missing epoch-on-channel-change and decreasing channel order.

The prototype does **not** match edges, perform fine-time calibration, map
detectors, persist ROOT data, or replace any reader. It preserves raw fine
codes including invalid entries, and deliberately reports anomalous edges
rather than dropping them. That means the prototype is **not** claimed to
produce legacy Twinpeaks objects directly.

Run its test from the repository root:

```bash
g++ -std=c++17 -O1 -g -Wall -Wextra -Werror -pedantic \
  -fsanitize=undefined -fno-sanitize-recover=all \
  tests/tamex_family_decoder_test.cxx -o /tmp/tamex_family_decoder_test
/tmp/tamex_family_decoder_test
```

## Required follow-up gates

1. Validate the view-to-UCESB adapter against generated BGO/FATIMA/bPlast/MCP
   onion structs; validate board-count and physical module identifiers.
2. Add synthetic **event-stream** fixtures including repeated epochs, channel
   transitions, trigger code 3, missing epochs, multihit/lead-trail sequences,
   invalid fine words, partial arrays and WR metadata.
3. Specify ROOT-persisted `TamexRawData` schema and branch ownership before
   introducing a real `TamexReader`.
4. Introduce digitiser-level calibration helpers, then a **detector Raw2Cal
   adapter** that can reproduce its own legacy output on identical events.
5. Start migration with one detector in parallel with the old path. Compare
   event counts, ordered channel IDs, edge timestamps, matched hit multiplicity,
   trigger entries, calibrated fine times and relevant physics histograms.
6. Measure processing speed and peak RSS under identical configurations. Do
   not claim better performance merely because the code is shared.

The initial change is intentionally additive. The legacy reader paths and
LISA experiment-specific branches are untouched.
