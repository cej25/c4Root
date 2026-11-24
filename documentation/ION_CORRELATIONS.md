# Ion correlations

Use `IonCorrelationsOnline` in an online run and `IonCorrelationsNearline` in a nearline run. Each calls the corresponding standalone detector spectra implementation after an event passes the selection. A gate gets its own histogram directories, for example `IonCorrelationsNearline_164Gd_DEGAS`. Keep the ordinary detector spectra tasks in the run for the inclusive comparison.

```cpp
auto* ions = new IonCorrelationsNearline();
ions->SetGates(frsGates);
ions->CorrelateGammas("DEGAS", "FATIMA");
run->AddTask(ions);
```

Supply `FrsGate` objects that remain alive throughout the run. The initial PID path uses `FrsHitData` and `FrsGate::PassedGate`. Each matching gate receives the event once. With no gates, the task requires an FRS hit and writes an `AnyFRS` group.

```cpp
auto* decays = new IonCorrelationsNearline("AidaDecays");
decays->RequireFrs(false);
decays->CorrelateTargetStack("AIDA");
decays->CorrelateImplantBetas(std::chrono::milliseconds{600});
decays->CorrelateGammas("DEGAS");
decays->CorrelatePlastic();
run->AddTask(decays);
```

- Set the implant–beta window in units of time. The example uses three half-lives for a 200 ms isotope.
- `CorrelateImplants()` selects stopped implants. With FRS enabled, the FRS hit and implant must be in the same event. AIDA also uses the time window described below. `CorrelateImplantBetas(window)` also tracks implants and uses the beta event to fill gamma and bPlast spectra. The history starts empty at the beginning of the run. Replay assumes target timestamps are ordered across events.
- The initial beta association uses the latest preceding stopped implant in the same DSSD whose X and Y strip ranges overlap the decay, within the requested window. A newer implant outside the selected PID gate blocks an older gated implant at that position. An implant remains eligible for later decays during the window. The decay spectra count each match, and the detector spectra fill once per event and gate.
- DEGAS, FATIMA TAMEX and bPlast spectra use the hits in the selected event. This preserves detector multiplicity, internal gamma–gamma gates and any same-event reference hits used by the standalone implementation. Keep the selected-event rates distinct from live-time efficiencies.
- AIDA and BB7 provide implant and decay branches for the Target Stack selection. STEFAN provides implant hits. LISA is a future target. With `RequireFrs(false)` and no target selection, every event is eligible. This gives the same detector spectra an inclusive baseline.

## FRS-tagged AIDA Target Stack

`CorrelateTargetStack("AIDA")` with `CorrelateImplants()` or `CorrelateImplantBetas(window)` and FRS enabled uses `FRS_AIDA_WR` from the experiment's `correlations.dat`. Configure that file with `TCorrelationsConfiguration::SetCorrelationsFile` before task initialization. The window is in ns and is applied to `t_AIDA − t_FRS` with exclusive endpoints, as in the legacy tasks. S100 uses 10000–20000 ns.

The task requires a single FRS hit within the window for each entry in `AidaImplantHits` and applies the PID gates to that FRS hit. In each `DSSD<n>` directory, `target_hit_energy`, `target_hit_strip_xy` and `target_hit_pos_xy` include all matched hits. An ion crossing several planes can contribute a hit in each plane. The `implant_*` plots use AIDA's `Stopped` flag, which identifies the deepest reconstructed hit with upstream activity. Establishing punch-through requires downstream detector information.

The task reports stopped implants with zero or multiple FRS matches. Implant-selected gamma and bPlast spectra use stopped implants. In implant–beta mode the history records stopped implants and their PID tags for association with later beta hits. `RequireFrs(false)` uses AIDA without this timing or PID requirement.

For comparison, `macros/tests/s100_tests.C` adds the legacy and new online tasks side by side when FRS and AIDA are enabled. In `IonCorrelationsOnline_<gate>/DSSD<n>`, compare the entries in `implant_energy` and the bins in `implant_pos_xy` and `implant_strip_xy` against the legacy stopped-implant outputs and the inclusive plots in AIDA. Use the same gate predicates when comparing counts. For the legacy online stopped-energy and position spectra, a Z41–AoQ-only gate provides that comparison. The legacy online task's stopped-implant counter uses the full gate. Mixed-PID or multiple-hit events can differ because the legacy task always uses the first FRS hit. Compare the energy distributions at common binning.

## Histogram coverage before retiring existing tasks

“Shared fill” means identical histogram booking and filling to the corresponding ungated detector task, using only accepted events. The remaining rows identify existing outputs to retain until their selection and histogram contents are reproduced. “Inclusive” here means without the cross-subsystem gate. Detector-internal gates, such as a prompt flash cut, can still apply.

| Correlated spectra or diagnostics | Inclusive comparison | Coverage |
|---|---|---|
| DEGAS crystal and summed energies, energy vs crystal and run time, hit patterns, multiplicity, crystal-reference timing, gamma–gamma and SC41 spectra | `DegasOnlineSpectra` / `DegasNearlineSpectra` | Shared fill for FRS-tagged, implant-tagged and matched-beta events. Keep the legacy off-spill AIDA and bPlast selections and BB7 decay-only selection for direct comparisons. |
| FATIMA TAMEX energy and ToT, hit patterns, multiplicity, timing, energy drift, SC41 and gamma–gamma spectra | `FatimaOnlineSpectra` / `FatimaNearlineSpectra` | Shared fill. Keep the old AIDA–FATIMA decay-gated detector and multiplicity plots, decay-energy vs gamma-energy and SCI41 timing/anticoincidence until their exact selections are accounted for. |
| bPlast fast and slow ToT, fast vs slow ToT, hit patterns, timing and rates | `bPlastOnlineSpectra` / `bPlastNearlineSpectra` | Shared fill for the event selected by FRS, implant or beta. The old FRS charge vs bPlast ToT matrix needs both inputs. |
| Target Stack energy and position, decay energy | AIDA, BB7 and STEFAN detector spectra where available | FRS-tagged AIDA has per-DSSD energy, strip and physical position spectra for all hits and for stopped implants. Matched decay energy is available for AIDA or BB7. Retain legacy implant dead time, gate counters, FRS–implant time and position vs FRS tracking. Compare all-hit and stopped selections with the legacy gate predicates before retiring their plots. |
| Implant-to-beta elapsed time | All matched implant–beta candidates with no PID gate, using the same association | New `implant_beta_dt` in seconds. Keep the original beta-decay task for its candidate ranking, decay-to-gamma timing and background/subtracted gamma spectrum. |
| FRS PID after gamma energy or timing selection, and PID inside the ion gate | `FrsOnlineSpectra` / `FrsNearlineSpectra` PID plots | Retain the existing forward and reverse PID plots, including charge vs AoQ, tracking coordinates vs AoQ, charge–charge, energy loss and SCI42 energy where booked. |
| Legacy FRS–gamma prompt and delayed spectra, long-window energy–energy matrices, energy vs FRS/SC41 time, energy-gated time, multiplicity splits and post-window hit pattern | DEGAS/FATIMA standalone energy, time, multiplicity and gamma–gamma plots | Same-event fills exist. Keep the reference-specific windows and plots in the original FRS–DEGAS and FRS–FATIMA tasks. |
| FATIMA start–stop time and time vs energy with a DEGAS energy gate | `FatimaTimingAnalysisSummed` | Keep `FatimaTimingAnalysisSummedDegasGated`. Its DEGAS cascade condition is independent of the ion gate. |
| DEGAS energy surviving or rejected by BGO, BGO energy/time, BGO–DEGAS time differences | Combined inclusive DEGAS energy and the BGO singles from the diagnostics | Keep `DegasBGOOnlineSpectra` / `DegasBGONearlineSpectra` and the veto in `DegasCal2Anl`. |
| Pairwise WR differences, trigger-specific WR differences, subsystem intervals, and delayed/undelayed Time Machine spectra and matrices | Ungated trigger distributions, per-subsystem WR intervals and Time Machine singles from the same diagnostic tasks | Retained as separate online/nearline correlation diagnostics. Cross-subsystem time differences require the pair. |
| FATIMA VME spectra, lifetime and gamma matrices with FRS gates | `FatimaVmeOnlineSpectra` / `FatimaVmeNearlineSpectra` | VME singles exist. The former FRS task was outside the build. Its histogram identifiers below record the gate and start–stop variants. |
| LISA layer/channel energy and position with FRS gates, MUSIC–LISA and tracking matrices, WR/trigger plots | LISA and FRS standalone spectra | Keep LISA–FRS analysis. |
| FRS-gated MCP timing, position and maps | `H10MCPOnlineSpectra` / `H10MCPNearlineSpectra` | The former FRS task was outside the build. Its histogram identifiers are recorded below. |

Before removing any legacy correlation task, compare the selected events and histogram bins using the same data, gates and timing settings. An identical plot from standalone spectra establishes an inclusive baseline. Plots with quantities from both subsystems require both inputs even in their loosest selection.

## Legacy histogram identifiers

This index lists histogram members booked or filled in the correlation sources, including diagnostics and historical entries for removed tasks. One member can represent many per-gate, per-detector or per-trigger histograms. Use the coverage table above to identify the inclusive baseline and the legacy producer to retain.

<details>
<summary>AidaBplastCorrelations (removed, previously outside the build) (7 member identifiers)</summary>

`h1_bplast_abs_time`, `h1_bplast_fastToT`, `h1_bplast_fast_hitpatterns`, `h1_bplast_rel_time`, `h1_bplast_slowToT`, `h1_bplast_slow_hitpatterns`, `h2_bplast_slowToT_vs_fastToT`

</details>

<details>
<summary>AidaDegasCorrelations (2 member identifiers)</summary>

`h1_aida_degas_energy`, `h1_aida_degas_energy_time`

</details>

<details>
<summary>AidaFatimaCorrelations (9 member identifiers)</summary>

`h1_decay_e`, `h1_fatima_energy_anticoincidence_SCI41`, `h1_fatima_energy_decay_a_vary`, `h1_fatima_energy_decay_gated`, `h1_fatima_energy_decay_gated_mult2`, `h1_fatima_time_differences_SCI41_dt_detector`, `h1_fatima_time_differences_energy_SCI41_dt`, `h1_fatima_time_differences_energy_SCI41_gated`, `h1_implant_e`

</details>

<details>
<summary>AidaGermaniumCorrelations (2 member identifiers)</summary>

`h1_aida_germanium_energy`, `h1_aida_germanium_energy_time`

</details>

<details>
<summary>FrsAidaCorrelations (25 member identifiers)</summary>

`h1_AidaImplant_Deadtime`, `h1_AidaImplant_FRS_Z1Z2x2AoQgates_e`, `h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped`, `h1_AidaImplant_FRS_Z1Z2x4AoQgates_e`, `h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped`, `h1_AidaImplant_FRS_ZAoQgate_e`, `h1_AidaImplant_FRS_ZAoQgate_e_stopped`, `h1_AidaImplant_FRS_dT`, `h2_AidaImplant_FRS_Z1Z2gate_position`, `h2_AidaImplant_FRS_Z1Z2gate_position_stopped`, `h2_AidaImplant_FRS_Z1Z2gate_strip_xy`, `h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped`, `h2_AidaImplant_FRS_Z1Z2x2AoQgates_position`, `h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped`, `h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy`, `h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped`, `h2_AidaImplant_FRS_Z1Z2x4AoQgates_position`, `h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped`, `h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy`, `h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped`, `h2_AidaImplant_FRS_ZAoQgate_position`, `h2_AidaImplant_FRS_ZAoQgate_position_stopped`, `h2_AidaImplant_FRS_ZAoQgate_strip_xy`, `h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped`, `h2_AidaImplant_FRS_x_vs_x4`

</details>

<details>
<summary>FrsBplastCorrelations (removed, previously outside the build) (1 member identifiers)</summary>

`h2_Z_vs_slowToT`

</details>

<details>
<summary>FrsDegasCorrelations (19 member identifiers)</summary>

`h1_degas_energy_promptflash_cut`, `h1_degas_energy_promptflash_cut_energy_gated`, `h1_degas_energy_promptflash_cut_long`, `h1_degas_energy_promptflash_cut_long_energy_gated`, `h1_degas_energy_promptflash_cut_mhtdc_gated`, `h1_degas_tsci41_energy_gated`, `h1_degas_twr_sci41_energy_gated`, `h1_ge_time_ref_frs_wr`, `h2_degas_energy_energy_promptflash_cut`, `h2_degas_energy_energy_promptflash_cut_long`, `h2_degas_energy_vs_sci41_wr_long`, `h2_degas_energy_vs_tsci41`, `h2_frs_Z_vs_AoQ_gated`, `h2_frs_Z_vs_Z2_gated`, `h2_frs_Z_vs_dEdeg_gated`, `h2_frs_Z_vs_sci42E_gated`, `h2_frs_x2_vs_AoQ_gated`, `h2_frs_x4_vs_AoQ_gated`, `histograms`

</details>

<details>
<summary>FrsDegasCorrelationsNearline (25 member identifiers)</summary>

`h1_degas_energy_promptflash_cut`, `h1_degas_energy_promptflash_cut_energy_gated`, `h1_degas_energy_promptflash_cut_long`, `h1_degas_energy_promptflash_cut_long_energy_gated`, `h1_degas_hitpattern_post6us`, `h1_degas_tsci41_energy_gated`, `h1_degas_twr_sci41_energy_gated`, `h2_degas_energy_energy_promptflash_cut`, `h2_degas_energy_energy_promptflash_cut_long`, `h2_degas_energy_vs_sci41_wr_long`, `h2_degas_energy_vs_tsci41`, `h2_frs_Z_vs_AoQ_gated`, `h2_frs_Z_vs_AoQ_reverse_gated`, `h2_frs_Z_vs_AoQ_reverse_wr_gated`, `h2_frs_Z_vs_Z2_gated`, `h2_frs_Z_vs_Z2_reverse_gated`, `h2_frs_Z_vs_Z2_reverse_wr_gated`, `h2_frs_Z_vs_dEdeg_gated`, `h2_frs_Z_vs_sci42E_gated`, `h2_frs_x2_vs_AoQ_gated`, `h2_frs_x2_vs_AoQ_reverse_gated`, `h2_frs_x2_vs_AoQ_reverse_wr_gated`, `h2_frs_x4_vs_AoQ_gated`, `h2_frs_x4_vs_AoQ_reverse_gated`, `h2_frs_x4_vs_AoQ_reverse_wr_gated`

</details>

<details>
<summary>FrsFatimaCorrelations (39 member identifiers)</summary>

`h1_fatima_energy_promptflash_cut`, `h1_fatima_energy_promptflash_cut_energy_gated`, `h1_fatima_energy_promptflash_cut_long`, `h1_fatima_energy_promptflash_cut_long_energy_gated`, `h1_fatima_energy_promptflash_cut_long_mult1`, `h1_fatima_energy_promptflash_cut_long_mult2`, `h1_fatima_energy_promptflash_cut_long_mult3`, `h1_fatima_energy_promptflash_cut_long_mult4p`, `h1_fatima_energy_promptflash_cut_mult1`, `h1_fatima_energy_promptflash_cut_mult2`, `h1_fatima_energy_promptflash_cut_mult3`, `h1_fatima_energy_promptflash_cut_mult4p`, `h1_fatima_sci41_energy`, `h1_fatima_sci41_hits`, `h1_fatima_tsci41_energy_gated`, `h1_fatima_twr_sci41_energy_gated`, `h2_fatima_energy_energy_promptflash_cut`, `h2_fatima_energy_energy_promptflash_cut_long`, `h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut`, `h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long`, `h2_fatima_energy_vs_sci41_mult1`, `h2_fatima_energy_vs_sci41_mult2`, `h2_fatima_energy_vs_sci41_mult3`, `h2_fatima_energy_vs_sci41_mult4p`, `h2_fatima_energy_vs_sci41_wr_long`, `h2_fatima_energy_vs_sci41_wr_long_mult1`, `h2_fatima_energy_vs_sci41_wr_long_mult2`, `h2_fatima_energy_vs_sci41_wr_long_mult3`, `h2_fatima_energy_vs_sci41_wr_long_mult4p`, `h2_fatima_energy_vs_tsci41`, `h2_fatima_multiplicity_vs_sci41_wr_long`, `h2_fatima_multiplicity_vs_tsci41`, `h2_frs_Z_vs_AoQ_gated`, `h2_frs_Z_vs_Z2_gated`, `h2_frs_Z_vs_dEdeg_gated`, `h2_frs_Z_vs_sci42E_gated`, `h2_frs_x2_vs_AoQ_gated`, `h2_frs_x4_vs_AoQ_gated`, `histograms`

</details>

<details>
<summary>FrsFatimaCorrelationsNearline (38 member identifiers)</summary>

`h1_fatima_energy_promptflash_cut`, `h1_fatima_energy_promptflash_cut_energy_gated`, `h1_fatima_energy_promptflash_cut_long`, `h1_fatima_energy_promptflash_cut_long_energy_gated`, `h1_fatima_energy_promptflash_cut_long_mult1`, `h1_fatima_energy_promptflash_cut_long_mult2`, `h1_fatima_energy_promptflash_cut_long_mult3`, `h1_fatima_energy_promptflash_cut_long_mult4p`, `h1_fatima_energy_promptflash_cut_mult1`, `h1_fatima_energy_promptflash_cut_mult2`, `h1_fatima_energy_promptflash_cut_mult3`, `h1_fatima_energy_promptflash_cut_mult4p`, `h1_fatima_sci41_energy`, `h1_fatima_sci41_hits`, `h1_fatima_tsci41_energy_gated`, `h1_fatima_twr_sci41_energy_gated`, `h2_fatima_energy_energy_promptflash_cut`, `h2_fatima_energy_energy_promptflash_cut_long`, `h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut`, `h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long`, `h2_fatima_energy_vs_sci41_mult1`, `h2_fatima_energy_vs_sci41_mult2`, `h2_fatima_energy_vs_sci41_mult3`, `h2_fatima_energy_vs_sci41_mult4p`, `h2_fatima_energy_vs_sci41_wr_long`, `h2_fatima_energy_vs_sci41_wr_long_mult1`, `h2_fatima_energy_vs_sci41_wr_long_mult2`, `h2_fatima_energy_vs_sci41_wr_long_mult3`, `h2_fatima_energy_vs_sci41_wr_long_mult4p`, `h2_fatima_energy_vs_tsci41`, `h2_fatima_multiplicity_vs_sci41_wr_long`, `h2_fatima_multiplicity_vs_tsci41`, `h2_frs_Z_vs_AoQ_gated`, `h2_frs_Z_vs_Z2_gated`, `h2_frs_Z_vs_dEdeg_gated`, `h2_frs_Z_vs_sci42E_gated`, `h2_frs_x2_vs_AoQ_gated`, `h2_frs_x4_vs_AoQ_gated`

</details>

<details>
<summary>FrsFatimaVmeCorrelations (removed, previously outside the build) (21 member identifiers)</summary>

`h1_FRS_FatVME_E_Z1Z2x2AoQgate`, `h1_FRS_FatVME_E_Z1Z2x4AoQgate`, `h1_FRS_FatVME_E_ZAoQgate`, `h1_FRS_FatVME_LT1_start_stop`, `h1_FRS_FatVME_LT1_start_stop_ns`, `h1_FRS_FatVME_LT1_stop_start`, `h1_FRS_FatVME_LT1_stop_start_ns`, `h1_FRS_FatVME_LT2_start_stop`, `h1_FRS_FatVME_LT2_start_stop_ns`, `h1_FRS_FatVME_LT2_stop_start`, `h1_FRS_FatVME_LT2_stop_start_ns`, `h1_FRS_FatVME_LT3_start_stop`, `h1_FRS_FatVME_LT3_start_stop_ns`, `h1_FRS_FatVME_LT3_stop_start`, `h1_FRS_FatVME_LT3_stop_start_ns`, `h2_FRS_FatVME_E1vsE2_Z1Z2x2AoQgate`, `h2_FRS_FatVME_E1vsE2_Z1Z2x4AoQgate`, `h2_FRS_FatVME_E1vsE2_ZAoQgate`, `h2_FRS_FatVME_EvsT_Z1Z2x2AoQgate`, `h2_FRS_FatVME_EvsT_Z1Z2x4AoQgate`, `h2_FRS_FatVME_EvsT_ZAoQgate`

</details>

<details>
<summary>FrsGermaniumCorrelations (19 member identifiers)</summary>

`h1_ge_time_ref_frs_wr`, `h1_germanium_energy_promptflash_cut`, `h1_germanium_energy_promptflash_cut_energy_gated`, `h1_germanium_energy_promptflash_cut_long`, `h1_germanium_energy_promptflash_cut_long_energy_gated`, `h1_germanium_energy_promptflash_cut_mhtdc_gated`, `h1_germanium_tsci41_energy_gated`, `h1_germanium_twr_sci41_energy_gated`, `h2_frs_Z_vs_AoQ_gated`, `h2_frs_Z_vs_Z2_gated`, `h2_frs_Z_vs_dEdeg_gated`, `h2_frs_Z_vs_sci42E_gated`, `h2_frs_x2_vs_AoQ_gated`, `h2_frs_x4_vs_AoQ_gated`, `h2_germanium_energy_energy_promptflash_cut`, `h2_germanium_energy_energy_promptflash_cut_long`, `h2_germanium_energy_vs_sci41_wr_long`, `h2_germanium_energy_vs_tsci41`, `histograms`

</details>

<details>
<summary>FrsGermaniumCorrelationsNearline (25 member identifiers)</summary>

`h1_germanium_energy_promptflash_cut`, `h1_germanium_energy_promptflash_cut_energy_gated`, `h1_germanium_energy_promptflash_cut_long`, `h1_germanium_energy_promptflash_cut_long_energy_gated`, `h1_germanium_hitpattern_post6us`, `h1_germanium_tsci41_energy_gated`, `h1_germanium_twr_sci41_energy_gated`, `h2_frs_Z_vs_AoQ_gated`, `h2_frs_Z_vs_AoQ_reverse_gated`, `h2_frs_Z_vs_AoQ_reverse_wr_gated`, `h2_frs_Z_vs_Z2_gated`, `h2_frs_Z_vs_Z2_reverse_gated`, `h2_frs_Z_vs_Z2_reverse_wr_gated`, `h2_frs_Z_vs_dEdeg_gated`, `h2_frs_Z_vs_sci42E_gated`, `h2_frs_x2_vs_AoQ_gated`, `h2_frs_x2_vs_AoQ_reverse_gated`, `h2_frs_x2_vs_AoQ_reverse_wr_gated`, `h2_frs_x4_vs_AoQ_gated`, `h2_frs_x4_vs_AoQ_reverse_gated`, `h2_frs_x4_vs_AoQ_reverse_wr_gated`, `h2_germanium_energy_energy_promptflash_cut`, `h2_germanium_energy_energy_promptflash_cut_long`, `h2_germanium_energy_vs_sci41_wr_long`, `h2_germanium_energy_vs_tsci41`

</details>

<details>
<summary>FrsMCPCorrelations (removed, previously outside the build) (2 member identifiers)</summary>

`h1_test_histogram_FRSGated`, `histogram2_FRSGated`

</details>

<details>
<summary>LisaFrsCorrelations (76 member identifiers)</summary>

`h1_LISA_energy_LISA_s1s2_gated`, `h1_LISA_energy_LISA_s1s2_gated_M5`, `h1_LISA_energy_LISA_s1s2s4_gated`, `h1_LISA_energy_LISA_s1s2s4_gated_M5`, `h1_LISA_energy_MWD_LISA_s1s2_gated`, `h1_LISA_energy_MWD_LISA_s1s2_gated_M5`, `h1_LISA_energy_MWD_LISA_s1s2s4_gated`, `h1_LISA_energy_MWD_LISA_s1s2s4_gated_M5`, `h1_LISA_energy_MWD_s1s2_gated`, `h1_LISA_energy_MWD_s1s2s4_gated`, `h1_LISA_energy_MWD_xy_LISA_s1s2_gated`, `h1_LISA_energy_MWD_xy_LISA_s1s2_gated_M5`, `h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated`, `h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated_M5`, `h1_LISA_energy_MWD_xy_s1s2_gated`, `h1_LISA_energy_MWD_xy_s1s2s4_gated`, `h1_LISA_energy_s1s2_gated`, `h1_LISA_energy_s1s2s4_gated`, `h1_LISA_energy_xy_LISA_s1s2_gated`, `h1_LISA_energy_xy_LISA_s1s2_gated_M5`, `h1_LISA_energy_xy_LISA_s1s2s4_gated`, `h1_LISA_energy_xy_LISA_s1s2s4_gated_M5`, `h1_LISA_energy_xy_s1s2_gated`, `h1_LISA_energy_xy_s1s2s4_gated`, `h1_energy_MWD_layer_corr_sci21`, `h1_energy_MWD_layer_corr_sci41`, `h1_energy_layer_corr_sci21`, `h1_energy_layer_corr_sci41`, `h1_tpc_lisa_x`, `h1_tpc_lisa_y`, `h1_wr_diff`, `h1_wr_diff_tpat2`, `h1_wr_diff_tpat6`, `h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated`, `h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated_M5`, `h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated`, `h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated_M5`, `h2_LISA_energy_MWD_vs_layer_s1s2_gated`, `h2_LISA_energy_MWD_vs_layer_s1s2s4_gated`, `h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated`, `h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated_M5`, `h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated`, `h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated_M5`, `h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated`, `h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated`, `h2_LISA_energy_vs_layer_LISA_s1s2_gated`, `h2_LISA_energy_vs_layer_LISA_s1s2_gated_M5`, `h2_LISA_energy_vs_layer_LISA_s1s2s4_gated`, `h2_LISA_energy_vs_layer_LISA_s1s2s4_gated_M5`, `h2_LISA_energy_vs_layer_s1s2_gated`, `h2_LISA_energy_vs_layer_s1s2s4_gated`, `h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated`, `h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated_M5`, `h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated`, `h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated_M5`, `h2_LISA_energy_xy_vs_layer_s1s2_gated`, `h2_LISA_energy_xy_vs_layer_s1s2s4_gated`, `h2_MUSIC21_vs_LISA_MWD`, `h2_MUSIC21_vs_LISA_febex`, `h2_MUSIC41_vs_LISA_MWD`, `h2_MUSIC41_vs_LISA_febex`, `h2_MUSIC42_vs_LISA_MWD`, `h2_MUSIC42_vs_LISA_febex`, `h2_Z21_vs_AoQs1s2_LISA_MWD_gated`, `h2_Z21_vs_AoQs1s2_LISA_gated`, `h2_Z21_vs_AoQs1s2_s1s2_correlated`, `h2_Z21_vs_AoQs1s2_s1s2s4_correlated`, `h2_Z41_vs_AoQs2s4_LISA_MWD_gated`, `h2_Z41_vs_AoQs2s4_LISA_gated`, `h2_Z41_vs_AoQs2s4_s1s2s4_correlated`, `h2_Z42_vs_AoQs2s4_LISA_MWD_gated`, `h2_Z42_vs_AoQs2s4_LISA_gated`, `h2_Z42_vs_AoQs2s4_s1s2s4_correlated`, `h2_tpc_x_lisa_x`, `h2_tpc_xy_LISA`, `h2_tpc_y_lisa_y`

</details>

<details>
<summary>bPlastDegasCorrelations (2 member identifiers)</summary>

`h1_degas_energy_bplast_corr`, `h1_degas_energy_bplast_corr_sum`

</details>

<details>
<summary>bPlastGermaniumCorrelations (2 member identifiers)</summary>

`h1_germanium_energy_bplast_corr`, `h1_germanium_energy_bplast_corr_sum`

</details>

<details>
<summary>TimeMachineNearline (4 member identifiers)</summary>

`h1_time_delayed`, `h1_time_diff`, `h1_time_undelayed`, `h2_time_diff_corrs`

</details>

<details>
<summary>WhiterabbitCorrelationNearline (31 member identifiers)</summary>

`h1_whiterabbit_correlation_aida_bplast`, `h1_whiterabbit_correlation_aida_fatima`, `h1_whiterabbit_correlation_aida_fatimavme`, `h1_whiterabbit_correlation_aida_germanium`, `h1_whiterabbit_correlation_bplast_ge`, `h1_whiterabbit_correlation_fatima_bplast`, `h1_whiterabbit_correlation_fatima_fatimavme`, `h1_whiterabbit_correlation_fatima_ge`, `h1_whiterabbit_correlation_fatimavme_bplast`, `h1_whiterabbit_correlation_fatimavme_ge`, `h1_whiterabbit_trigger`, `h1_whiterabbit_trigger1_aida_bplast`, `h1_whiterabbit_trigger1_aida_fatima`, `h1_whiterabbit_trigger1_aida_fatimavme`, `h1_whiterabbit_trigger1_aida_germanium`, `h1_whiterabbit_trigger1_bplast_ge`, `h1_whiterabbit_trigger1_fatima_bplast`, `h1_whiterabbit_trigger1_fatima_fatimavme`, `h1_whiterabbit_trigger1_fatima_ge`, `h1_whiterabbit_trigger1_fatimavme_bplast`, `h1_whiterabbit_trigger1_fatimavme_ge`, `h1_whiterabbit_trigger3_aida_bplast`, `h1_whiterabbit_trigger3_aida_fatima`, `h1_whiterabbit_trigger3_aida_fatimavme`, `h1_whiterabbit_trigger3_aida_germanium`, `h1_whiterabbit_trigger3_bplast_ge`, `h1_whiterabbit_trigger3_fatima_bplast`, `h1_whiterabbit_trigger3_fatima_fatimavme`, `h1_whiterabbit_trigger3_fatima_ge`, `h1_whiterabbit_trigger3_fatimavme_bplast`, `h1_whiterabbit_trigger3_fatimavme_ge`

</details>

<details>
<summary>BB7DegasCorrelationsOnline (3 member identifiers)</summary>

`h1_degas_bb7_wr_dt`, `h1_gamma_after_decay`, `histograms`

</details>

<details>
<summary>BB7GermaniumCorrelationsOnline (3 member identifiers)</summary>

`h1_gamma_after_decay`, `h1_germanium_bb7_wr_dt`, `histograms`

</details>

<details>
<summary>FrsAidaCorrelationsOnline (6 member identifiers)</summary>

`h1_AidaImplant_ZvsAoQGated_energy`, `h1_AidaImplant_ZvsAoQGated_energy_stopped`, `h1_stopped_implanted_passed_gate`, `h2_AidaImplant_ZvsAoQGated_position`, `h2_AidaImplant_ZvsAoQGated_position_stopped`, `histograms`

</details>

<details>
<summary>LisaFrsCorrelationsOnline (15 member identifiers)</summary>

`h1_energy_MWD_layer_corr_sci41`, `h1_energy_layer_corr_sci41`, `h1_tpc_lisa_x`, `h1_tpc_lisa_y`, `h1_wr_diff`, `h1_wr_diff_tpat2`, `h1_wr_diff_tpat6`, `h2_MUSIC21_vs_LISA_MWD`, `h2_MUSIC21_vs_LISA_febex`, `h2_MUSIC41_vs_LISA_MWD`, `h2_MUSIC41_vs_LISA_febex`, `h2_tpc_x_lisa_x`, `h2_tpc_xy_LISA`, `h2_tpc_y_lisa_y`, `histograms`

</details>

<details>
<summary>TimeMachineOnline (5 member identifiers)</summary>

`h1_time_delayed`, `h1_time_diff`, `h1_time_undelayed`, `h2_time_diff_corrs`, `histograms`

</details>

<details>
<summary>WhiterabbitCorrelationOnline (46 member identifiers)</summary>

`h1_whiterabbit_correlation_aida_bplast`, `h1_whiterabbit_correlation_aida_fatima`, `h1_whiterabbit_correlation_aida_fatimavme`, `h1_whiterabbit_correlation_aida_frs`, `h1_whiterabbit_correlation_aida_germanium`, `h1_whiterabbit_correlation_bb7_bplast`, `h1_whiterabbit_correlation_bb7_fatima`, `h1_whiterabbit_correlation_bb7_fatimavme`, `h1_whiterabbit_correlation_bb7_frs`, `h1_whiterabbit_correlation_bb7_germanium`, `h1_whiterabbit_correlation_bplast_frs`, `h1_whiterabbit_correlation_bplast_ge`, `h1_whiterabbit_correlation_fatima_bplast`, `h1_whiterabbit_correlation_fatima_fatimavme`, `h1_whiterabbit_correlation_fatima_frs`, `h1_whiterabbit_correlation_fatima_ge`, `h1_whiterabbit_correlation_fatimavme_bplast`, `h1_whiterabbit_correlation_fatimavme_ge`, `h1_whiterabbit_correlation_germanium_frs`, `h1_whiterabbit_dt_bb7`, `h1_whiterabbit_dt_bplast`, `h1_whiterabbit_dt_fatima`, `h1_whiterabbit_dt_fatimavme`, `h1_whiterabbit_dt_germanium`, `h1_whiterabbit_trigger`, `h1_whiterabbit_trigger1_aida_bplast`, `h1_whiterabbit_trigger1_aida_fatima`, `h1_whiterabbit_trigger1_aida_fatimavme`, `h1_whiterabbit_trigger1_aida_germanium`, `h1_whiterabbit_trigger1_bplast_ge`, `h1_whiterabbit_trigger1_fatima_bplast`, `h1_whiterabbit_trigger1_fatima_fatimavme`, `h1_whiterabbit_trigger1_fatima_ge`, `h1_whiterabbit_trigger1_fatimavme_bplast`, `h1_whiterabbit_trigger1_fatimavme_ge`, `h1_whiterabbit_trigger3_aida_bplast`, `h1_whiterabbit_trigger3_aida_fatima`, `h1_whiterabbit_trigger3_aida_fatimavme`, `h1_whiterabbit_trigger3_aida_germanium`, `h1_whiterabbit_trigger3_bplast_ge`, `h1_whiterabbit_trigger3_fatima_bplast`, `h1_whiterabbit_trigger3_fatima_fatimavme`, `h1_whiterabbit_trigger3_fatima_ge`, `h1_whiterabbit_trigger3_fatimavme_bplast`, `h1_whiterabbit_trigger3_fatimavme_ge`, `histograms`

</details>

<details>
<summary>bPlastDegasCorrelationsOnline (2 member identifiers)</summary>

`h1_degas_energy_bplast_corr`, `h1_degas_energy_bplast_corr_sum`

</details>

<details>
<summary>bPlastGermaniumCorrelationsOnline (2 member identifiers)</summary>

`h1_germanium_energy_bplast_corr`, `h1_germanium_energy_bplast_corr_sum`

</details>

<details>
<summary>BetaIonCorrelations (24 member identifiers)</summary>

`h1_aida_germanium_dt`, `h1_all_gammas`, `h1_beta_gamma_bkg`, `h1_beta_gamma_corr_energy`, `h1_beta_gamma_diff`, `h1_cluster_size_x`, `h1_cluster_size_y`, `h1_decay_e`, `h1_decay_gamma_dt`, `h1_decay_mult`, `h1_gammas_inside_gate`, `h1_imp_decay_dt`, `h1_imp_mult`, `h1_imp_stopped_mult`, `h1_implant_e`, `h1_relevant_decay_mult`, `h1_relevant_decay_mult_less_than`, `h1_relevant_imps_per_decay`, `h1_strip_mult`, `h2_ZvsAoQ`, `h2_ZvsAoQ_inside_gate`, `h2_decay_pos_xy`, `h2_imp_stopped_pos_xy`, `h2_implant_pos_xy`

</details>

<details>
<summary>BetaIonDegasCorrelations (removed) (24 member identifiers)</summary>

`h1_aida_degas_dt`, `h1_all_gammas`, `h1_beta_gamma_bkg`, `h1_beta_gamma_corr_energy`, `h1_beta_gamma_diff`, `h1_cluster_size_x`, `h1_cluster_size_y`, `h1_decay_e`, `h1_decay_gamma_dt`, `h1_decay_mult`, `h1_gammas_inside_gate`, `h1_imp_decay_dt`, `h1_imp_mult`, `h1_imp_stopped_mult`, `h1_implant_e`, `h1_relevant_decay_mult`, `h1_relevant_decay_mult_less_than`, `h1_relevant_imps_per_decay`, `h1_strip_mult`, `h2_ZvsAoQ`, `h2_ZvsAoQ_inside_gate`, `h2_decay_pos_xy`, `h2_imp_stopped_pos_xy`, `h2_implant_pos_xy`

</details>

<details>
<summary>FrsAidaBplastGermaniumCorrelations (removed, previously outside the build) (14 member identifiers)</summary>

`h1_bplast_abs_time`, `h1_bplast_fastToT`, `h1_bplast_fast_hitpatterns`, `h1_bplast_rel_time`, `h1_bplast_slowToT`, `h1_bplast_slow_hitpatterns`, `h2_aida_implants_dssd1_frs_gated`, `h2_aida_implants_dssd2_frs_gated`, `h2_bplast_fast_vs_slow_gated`, `h2_bplast_slowToT_vs_fastToT`, `h2_frs_Z_vs_AoQ_gated`, `h2_frs_Z_vs_Z2_gated`, `h2_frs_x2_vs_AoQ_gated`, `h2_frs_x4_vs_AoQ_gated`

</details>

<details>
<summary>BGONearlineSpectra (5 member identifiers)</summary>

`h1_bgo_energy`, `h1_bgo_time`, `h1_germanium_bgo_veto_energy`, `h1_germanium_bgo_veto_timedifferences`, `h1_germanium_bgo_vetotrue_energy`

</details>

<details>
<summary>DegasBGONearlineSpectra (5 member identifiers)</summary>

`h1_bgo_energy`, `h1_bgo_time`, `h1_degas_bgo_veto_energy`, `h1_degas_bgo_veto_timedifferences`, `h1_degas_bgo_vetotrue_energy`

</details>

<details>
<summary>FatimaTimingAnalysisSummedDegasGated (2 member identifiers)</summary>

`h_energy_E1_E2_dt`, `h_energy_E1_dt_vs_E`

</details>

<details>
<summary>FatimaTimingAnalysisSummedGeGated (2 member identifiers)</summary>

`h_energy_E1_E2_dt`, `h_energy_E1_dt_vs_E`

</details>

<details>
<summary>BGOOnlineSpectra (6 member identifiers)</summary>

`h1_bgo_energy`, `h1_bgo_time`, `h1_germanium_bgo_veto_energy`, `h1_germanium_bgo_veto_timedifferences`, `h1_germanium_bgo_vetotrue_energy`, `histograms`

</details>

<details>
<summary>DegasBGOOnlineSpectra (6 member identifiers)</summary>

`h1_bgo_energy`, `h1_bgo_time`, `h1_degas_bgo_veto_energy`, `h1_degas_bgo_veto_timedifferences`, `h1_degas_bgo_vetotrue_energy`, `histograms`

</details>
