/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                             C.E. Jones                                     *
 *                              17.12.24                                      *
 ******************************************************************************/

// FairRoot
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairTask.h"

// c4
#include "FrsNearlineSpectra.h"
#include "FrsHitData.h"
#include "c4Logger.h"
#include "AnalysisTools.h"

// ROOT
#include "TClonesArray.h"
#include <vector>
#include "TDirectory.h"


FrsNearlineSpectra::FrsNearlineSpectra() : FrsNearlineSpectra("FrsNearlineSpectra", 1)
{
    frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
    mw = frs_config->MW();
    tpc = frs_config->TPC();
    music = frs_config->MUSIC();
    labr = frs_config->LABR();
    sci = frs_config->SCI();
    id = frs_config->ID();
    si = frs_config->SI();
    mrtof = frs_config->MRTOF();
    range = frs_config->Range();
}

FrsNearlineSpectra::FrsNearlineSpectra(std::vector<FrsGate*> fg)
    :   FairTask()
    ,   fNEvents()
    ,   header(nullptr)
    ,   hitArray(nullptr)
    ,   multihitArray(nullptr)
{
    exp_config = TExperimentConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
    mw = frs_config->MW();
    tpc = frs_config->TPC();
    music = frs_config->MUSIC();
    labr = frs_config->LABR();
    sci = frs_config->SCI();
    id = frs_config->ID();
    si = frs_config->SI();
    mrtof = frs_config->MRTOF();
    range = frs_config->Range();
    FrsGates = fg;

}

FrsNearlineSpectra::FrsNearlineSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents()
    ,   header(nullptr)
    ,   hitArray(nullptr)
    ,   multihitArray(nullptr)
{
}

FrsNearlineSpectra::~FrsNearlineSpectra()
{
    c4LOG(info, "Deleting FrsNearlineSpectra task.");
}

InitStatus FrsNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = mgr->InitObjectAs<decltype(header)>("EventHeader.");
    c4LOG_IF(warn, !header, "EventHeader. not found!");

    hitArray = mgr->InitObjectAs<decltype(hitArray)>("FrsHitData");
    c4LOG_IF(fatal, !hitArray, "Branch FrsHitData not found!");
    multihitArray = mgr->InitObjectAs<decltype(multihitArray)>("FrsMultiHitData");
    c4LOG_IF(fatal, !multihitArray, "Branch FrsMultiHitData not found!");

    dir_frs = (TDirectory*)mgr->GetObject("FRS");
    if (dir_frs == nullptr) 
    {
        LOG(info) << "Creating FRS Directory";
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_frs = gDirectory->mkdir("FRS");
        mgr->Register("FRS", "FRS Directory", dir_frs, false); // allow other tasks to find this
        found_dir_frs = false;
    }

    if (frs_config->plot_tac_1d || frs_config->plot_tac_2d) dir_tac = dir_frs->mkdir("TAC");
    if (frs_config->plot_mhtdc_1d || frs_config->plot_mhtdc_2d) dir_mhtdc = dir_frs->mkdir("MHTDC");
    
    dir_scalers = dir_frs->mkdir("Scalers");
    dir_rates = dir_frs->mkdir("Rate Monitors");
    dir_drifts = dir_frs->mkdir("Drift Monitors");

    // ::::: Scalers :::::::: // on/off with switch?
    h1_tpat = MakeTH1(dir_scalers, "I", "h1_tpat", "Trigger Pattern", 20, 0, 20, "Trigger Pattern", kRed-3, kBlack);
    for (int i = 0; i < 66; i++) hScaler_per_s[i] = MakeTH1(dir_scalers, "D", Form("hScaler_per_s_%s", frs_config->ScalerName(i).c_str()), Form("Scaler %s per 1s ", frs_config->ScalerName(i).c_str()), 1000, 0., 1000., "Time [s]", kCyan, kViolet);
    for (int i = 0; i < 66; i++) hScaler_per_100ms[i] = MakeTH1(dir_scalers, "D", Form("hScaler_per_100ms_%s", frs_config->ScalerName(i).c_str()), Form("Scaler %s per 0.1s", frs_config->ScalerName(i).c_str()), 4000, 0, 400, "Time [100 ms]", kCyan, kViolet);
    for (int i = 0; i < 66; i++) hScaler_per_spill[i] = MakeTH1(dir_scalers, "D", Form("hScaler_per_spill_%s", frs_config->ScalerName(i).c_str()), Form("Scaler %s per spill ", frs_config->ScalerName(i).c_str()), 1000, 0, 1000, "Spill", kCyan, kViolet);

    if (frs_config->plot_tac_2d)
    {
        dir_tac_2d = dir_tac->mkdir("2D PIDs");

        // directory, type, name, title, xbins, xmin, xmax, ybins, ymin, ymax, xtitle, ytitle
        h2_Z_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_AoQ", "Z1 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
        h2_Z_vs_AoQ_driftcorr = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_AoQ_driftcorr", "Z1 vs. A/Q DriftCorr", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q DriftCorr", "Z DriftCorr(MUSIC 1)");
        h2_Z_vs_AoQ_corr = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_AoQ_corr", "Z1 vs. A/Q (corr)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z,"A/Q", "Z (MUSIC 1)");
        h2_Z_vs_Z2 = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_Z2", "Z1 vs. Z2", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z (MUSIC 1)", "Z (MUSIC 2)");
        h2_Z_vs_AoQ_Zsame = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_AoQ_Zsame", "Z1 vs. A/Q [ABS (Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
        h2_x2_vs_AoQ_Zsame = MakeTH2(dir_tac_2d, "D", "h2_x2_vs_AoQ_Zsame", "x2 vs A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
        h2_x4_vs_AoQ_Zsame = MakeTH2(dir_tac_2d, "D", "h2_x4_vs_AoQ_Zsame", "x4 vs A/Q - [ABS(Z1 - Z2) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
        h2_x2_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_x2_vs_AoQ", "x2 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
        h2_x4_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_x4_vs_AoQ", "x4 vs. A/Q", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
        h2_dEdegoQ_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_dEdegoQ_vs_Z", "dE in S2 degrader / Q vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "dE in S2 degrader / Q", "Z (MUSIC 1)");
        h2_dEdeg_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_dEdeg_vs_Z", "dE in S2 degrader vs. Z1", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dE, frs_config->fMax_dE, "dE in S2 degrader", "Z (MUSIC 1)");
        h2_a2_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_a2_vs_AoQ", "A/Q vs. AngleX (S2)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a2, frs_config->fMax_a2, "A/Q", "AngleX (S2)");
        h2_a4_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_a4_vs_AoQ", "A/Q vs. AngleX (S4)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a4, frs_config->fMax_a4, "A/Q", "AngleX (S4)");
        h2_Z_vs_dE2 = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_dE2", "Z1 vs. dE in MUSIC2", 400, frs_config->fMin_Z, frs_config->fMax_Z, 250, frs_config->fMin_dE_Music2, frs_config->fMax_dE_Music2, "Z (MUSIC 1)", "dE in MUSIC 2");
        h2_x2_vs_x4 = MakeTH2(dir_tac_2d, "D", "h2_x2_vs_x4", "x2 vs. x4", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_x4, frs_config->fMax_x4, "S2 x-position", "S4 x-position");
        h2_SC41dE_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_SC41dE_vs_AoQ", "A/Q vs. dE in SC41", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000., "A/Q", "dE in SC41");
        h2_SC42dE_vs_AoQ = MakeTH2(dir_tac_2d, "D", "h2_SC42dE_vs_AoQ", "A/Q vs. dE in SC42", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000., "A/Q", "dE in SC42");
        h2_SC41dE_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_SC41dE_vs_Z", "Z (MUSIC 1) vs. dE in SC41", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, 0., 4000., "Z (MUSIC 1)", "dE in SC41");
        h2_SC42dE_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_SC42dE_vs_Z", "Z (MUSIC 1) vs. dE in SC42", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, 0., 4000., "Z (MUSIC 1)", "dE in SC42");
        h2_dE_vs_ToF_21_41 = MakeTH2(dir_tac_2d, "D", "h2_dE_vs_ToF_21_41", "ToF 21 - 41 vs. dE in MUSIC1", 2000, 0., 70000., 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "Time of Flight (21 - 41)", "dE in MUSIC 1");
        h2_x2_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_x2_vs_Z", "x2 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x2, frs_config->fMax_x2, "Z (MUSIC 1)", "S2 x-position");
        h2_x4_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_x4_vs_Z", "x4 vs. Z1", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x4, frs_config->fMax_x4, "Z (MUSIC 1)", "S4 x-position");
        h2_dE1_vs_x2 = MakeTH2(dir_tac_2d, "D", "h2_dE1_vs_x2", "x2 vs. dE in MUSIC1", 200, frs_config->fMin_x2, frs_config->fMax_x2, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "S2 x-position", "dE in MUSIC 1");
        h2_dE1_vs_x4 = MakeTH2(dir_tac_2d, "D", "h2_dE1_vs_x4", "x4 vs. dE in MUSIC1", 200, frs_config->fMin_x4, frs_config->fMax_x4, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "S4 x-position", "dE in MUSIC 1");
        h2_x2_vs_a2 = MakeTH2(dir_tac_2d, "D", "h2_x2_vs_a2", "x2 vs. AngleX (S2)", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_a2, frs_config->fMax_a2, "S2 x-position", "AngleX (S2)");
        h2_y2_vs_b2 = MakeTH2(dir_tac_2d, "D", "h2_y2_vs_b2", "y2 vs. AngleY (S2)", 200, frs_config->fMin_y2, frs_config->fMax_y2, 200, frs_config->fMin_b2, frs_config->fMax_b2, "S2 y-position", "AngleY (S2)");
        h2_x4_vs_a4 = MakeTH2(dir_tac_2d, "D", "h2_x4_vs_a4", "x4 vs. AngleX (S4)", 200, frs_config->fMin_x4, frs_config->fMax_x4, 200, frs_config->fMin_a4, frs_config->fMax_a4, "S4 x-position", "AngleX (S4)");
        h2_y4_vs_b4 = MakeTH2(dir_tac_2d, "D", "h2_y4_vs_b4", "y4 vs. AngleY (S4)", 200, frs_config->fMin_y4, frs_config->fMax_y4, 200, frs_config->fMin_b4, frs_config->fMax_b4, "S4 y-position", "AngleY (S4)");
        h2_Z_vs_Sc21E = MakeTH2(dir_tac_2d, "D", "h2_Z_vs_Sc21E", "Z1 vs. SQRT(Sc21_L * Sc21_R)", 300, frs_config->fMin_Z, frs_config->fMax_Z, 400, 0., 4000., "Z (MUSIC 1)", "Sc21 E");

        // Gated
        if (!FrsGates.empty())
        {   
            dir_gated_tac = dir_tac->mkdir("Gated 2D PIDs");
            dir_ZvsAoQ_tac = dir_gated_tac->mkdir("ZvsAoQ Gated");
            dir_Z1vsZ2_tac = dir_gated_tac->mkdir("Z1vsZ1 Gated");
            dir_x2vsAoQ_tac = dir_gated_tac->mkdir("x2vsAoQ Gated");
            dir_x4vsAoQ_tac = dir_gated_tac->mkdir("x4vsAoQ Gated");
            dir_dEdegvsZ_tac =  dir_gated_tac->mkdir("dEdegvsZ Gated");

            h2_Z_vs_AoQ_ZAoQgate.resize(FrsGates.size());
            h2_Z1_vs_Z2_ZAoQgate.resize(FrsGates.size());
            h2_x2_vs_AoQ_ZAoQgate.resize(FrsGates.size());
            h2_x4_vs_AoQ_ZAoQgate.resize(FrsGates.size());
            h2_dEdeg_vs_Z_ZAoQgate.resize(FrsGates.size());
            h2_dedegoQ_vs_Z_ZAoQgate.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2gate.resize(FrsGates.size());
            h2_dEdegoQ_vs_Z_Z1Z2gate.resize(FrsGates.size());
            h2_Z1_vs_Z2_Z1Z2gate.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
            h2_Z_vs_AoQ_Z1Z2gate.resize(FrsGates.size());
            h2_x2_vs_AoQ_x2AoQgate.resize(FrsGates.size());
            h2_Z1_vs_Z2_x2AoQgate.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
            h2_Z_vs_AoQ_Z1Z2x2AoQgate.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2x2AoQgate.resize(FrsGates.size());
            h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate.resize(FrsGates.size());
            h2_x4_vs_AoQ_x4AoQgate.resize(FrsGates.size());
            h2_Z1_vs_Z2_x4AoQgate.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
            h2_Z_vs_AoQ_Z1Z2x4AoQgate.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2x4AoQgate.resize(FrsGates.size());
            h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate.resize(FrsGates.size());
            h2_Z_vs_AoQ_dEdegZgate.resize(FrsGates.size());
            h2_Z1_vs_Z2_dEdegZgate.resize(FrsGates.size());
            h2_x2_vs_AoQ_dEdegZgate.resize(FrsGates.size());
            h2_x4_vs_AoQ_dEdegZgate.resize(FrsGates.size());
            h2_Z_vs_AoQ_Zsame_dEdegZgate.resize(FrsGates.size());

            for (int gate = 0; gate < FrsGates.size(); gate++)
            {
                h2_Z_vs_AoQ_ZAoQgate[gate] = MakeTH2(dir_ZvsAoQ_tac, "I", Form("h2_Z_vs_AoQ_ZAoQgate%d",gate), Form("Z vs. A/Q - ZAoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);
                h2_Z1_vs_Z2_ZAoQgate[gate] = MakeTH2(dir_ZvsAoQ_tac, "I", Form("h2_Z1_vs_Z2_ZAoQgate%d", gate), Form("Z1 vs. Z2 - ZAoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);
                h2_x2_vs_AoQ_ZAoQgate[gate] = MakeTH2(dir_ZvsAoQ_tac, "I", Form("h2_x2_vs_AoQ_ZAoQgate%d", gate), Form("x2 vs. A/Q - ZAoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_x4_vs_AoQ_ZAoQgate[gate] = MakeTH2(dir_ZvsAoQ_tac, "I", Form("h2_x4_vs_AoQ_ZAoQgate%d", gate), Form("x4 vs. A/Q - ZAoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_dEdeg_vs_Z_ZAoQgate[gate] = MakeTH2(dir_ZvsAoQ_tac, "I", Form("h2_dEdeg_vs_Z_ZAoQgate%d", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);
                h2_dedegoQ_vs_Z_ZAoQgate[gate] = MakeTH2(dir_ZvsAoQ_tac, "I", Form("h2_dedegoQ_vs_Z_ZAoQgate%d", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);
                
                h2_dEdeg_vs_Z_Z1Z2gate[gate] = MakeTH2(dir_Z1vsZ2_tac, "I", Form("h2_dEdeg_vs_Z_Z1Z2gate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);            
                h2_dEdegoQ_vs_Z_Z1Z2gate[gate] = MakeTH2(dir_Z1vsZ2_tac, "I", Form("h2_dEdegoQ_vs_Z_Z1Z2gate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);            
                h2_Z1_vs_Z2_Z1Z2gate[gate] = MakeTH2(dir_Z1vsZ2_tac, "I", Form("h2_Z1_vs_Z2_Z1Z2gate%d", gate), Form("Z1 vs. Z2 - Z1Z2 Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);            
                h2_x2_vs_AoQ_Z1Z2gate[gate] = MakeTH2(dir_Z1vsZ2_tac, "I", Form("h2_x2_vs_AoQ_Z1Z2gate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);            
                h2_x4_vs_AoQ_Z1Z2gate[gate] = MakeTH2(dir_Z1vsZ2_tac, "I", Form("h2_x4_vs_AoQ_Z1Z2gate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);            
                h2_Z_vs_AoQ_Z1Z2gate[gate] = MakeTH2(dir_Z1vsZ2_tac, "I", Form("h2_Z_vs_AoQ_Z1Z2gate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);

                h2_x2_vs_AoQ_x2AoQgate[gate] = MakeTH2(dir_x2vsAoQ_tac, "I", Form("h2_x2_vs_AoQ_x2AoQgate%d", gate), Form("x2 vs. A/Q - x2AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_Z1_vs_Z2_x2AoQgate[gate] = MakeTH2(dir_x2vsAoQ_tac, "I", Form("h2_Z1_vs_Z2_x2AoQgate%d", gate), Form("Z1 vs. Z2 - x2AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);
                // these have additional gate
                h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate] = MakeTH2(dir_x2vsAoQ_tac, "I", Form("h2_x2_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);                
                h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate] = MakeTH2(dir_x2vsAoQ_tac, "I", Form("h2_x4_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);                
                h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate] = MakeTH2(dir_x2vsAoQ_tac, "I", Form("h2_Z_vs_AoQ_Z1Z2x2AoQgate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);                
                h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate] =MakeTH2(dir_x2vsAoQ_tac, "I", Form("h2_dEdeg_vs_Z_Z1Z2x2AoQgate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);                
                h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate] = MakeTH2(dir_x2vsAoQ_tac, "I", Form("h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);

                h2_x4_vs_AoQ_x4AoQgate[gate] = MakeTH2(dir_x4vsAoQ_tac, "I", Form("h2_x4_vs_AoQ_x4AoQgate%d", gate), Form("x4 vs. A/Q - x4AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);            
                h2_Z1_vs_Z2_x4AoQgate[gate] = MakeTH2(dir_x4vsAoQ_tac, "I", Form("h2_Z1_vs_Z2_x4AoQgate%d", gate), Form("Z1 vs. Z2 - x4AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);
                // as above
                h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate] = MakeTH2(dir_x4vsAoQ_tac, "I", Form("h2_x2_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);        
                h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate] = MakeTH2(dir_x4vsAoQ_tac, "I", Form("h2_x4_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);      
                h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate] = MakeTH2(dir_x4vsAoQ_tac, "I", Form("h2_Z_vs_AoQ_Z1Z2x4AoQgate%d", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);         
                h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate] = MakeTH2(dir_x4vsAoQ_tac, "I", Form("h2_dEdeg_vs_Z_Z1Z2x4AoQgate%d", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);
                h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate] = MakeTH2(dir_x4vsAoQ_tac, "I", Form("h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate%d", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);

                h2_Z_vs_AoQ_dEdegZgate[gate] = MakeTH2(dir_dEdegvsZ_tac, "I", Form("h2_Z_vs_AoQ_dEdegZgate%d", gate), Form("Z1 vs. A/Q - dEdegZ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);            
                h2_Z1_vs_Z2_dEdegZgate[gate] = MakeTH2(dir_dEdegvsZ_tac, "I", Form("h2_Z1_vs_Z2_dEdegZgate%d", gate), Form("Z1 vs. Z2 - dEdegZ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);            
                h2_x2_vs_AoQ_dEdegZgate[gate] = MakeTH2(dir_dEdegvsZ_tac, "I", Form("h2_x2_vs_AoQ_dEdegZgate%d", gate), Form("x2 vs. A/Q - dEdegZ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);   
                h2_x4_vs_AoQ_dEdegZgate[gate] = MakeTH2(dir_dEdegvsZ_tac, "I", Form("h2_x4_vs_AoQ_dEdegZgate%d", gate), Form("x4 vs. A/Q - dEdegZ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_Z_vs_AoQ_Zsame_dEdegZgate[gate] = MakeTH2(dir_dEdegvsZ_tac, "I", Form("h2_Z_vs_AoQ_Zsame_dEdegZgate%d", gate), Form("Z vs. A/Q [ABS(Z1 - Z2) < 0.4] - dEdegZ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);

            }

        }
    }

    if (frs_config->plot_tac_1d)
    {   
        dir_tac_1d = dir_tac->mkdir("1D Spectra");

        // preset wide ranges to "always" see peak, in case there's something funky with the FRS
        h1_Z = MakeTH1(dir_tac_1d, "D", "h1_Z", "Z (MUSIC 1)", 500, 10, 100, "Z (MUSIC 1)", kPink-3, kBlue+2);
        h1_Z_driftcorr = MakeTH1(dir_tac_1d, "D", "h1_Z_driftcorr", "Z DriftCorr (MUSIC 1)", 500, 10, 100, "Z DriftCorr (MUSIC 1)", kPink-3, kBlue+2);
        h1_Z2 = MakeTH1(dir_tac_1d, "D", "h1_Z2", "Z (MUSIC 2)", 500, 10, 100, "Z (MUSIC 2)", kPink-3, kBlue+2);
        h1_AoQ = MakeTH1(dir_tac_1d, "D", "h1_AoQ", "A/Q", 500, 1.0, 4.0, "A/Q", kPink-3, kBlue+2); 
        h1_AoQ_driftcorr = MakeTH1(dir_tac_1d, "D", "h1_AoQ_driftcorr", "A/Q DriftCorr", 500, 1, 4.0, "A/Q DriftCorr", kPink-3, kBlue+2); 
        h1_AoQ_corr = MakeTH1(dir_tac_1d, "D", "h1_AoQ_corr", "A/Q (corr)", 500, 1.0, 4.0, "A/Q", kPink-3, kBlue+2);
        h1_x2 = MakeTH1(dir_tac_1d, "D", "h1_x2", "S2 x-position", 200, -100, 100, "S2 x-position", kYellow-7, kBlack);
        h1_x4 = MakeTH1(dir_tac_1d, "D", "h1_x4", "S4 x-position", 200, -100, 100, "S4 x-position",kYellow-7, kBlack);
        h1_a2 = MakeTH1(dir_tac_1d, "D", "h1_a2", "AngleX S2", 200, -100, 100, "AngleX S2", kYellow-7, kBlack);
        h1_a4 = MakeTH1(dir_tac_1d, "D", "h1_a4", "AngleX S4", 200, -100, 100, "AngleX S4", kYellow-7, kBlack);
        h1_y2 = MakeTH1(dir_tac_1d, "D", "h1_y2", "S2 y-position", 200, -100, 100, "S2 y-position", kYellow-7, kBlack);
        h1_y4 = MakeTH1(dir_tac_1d, "D", "h1_y4", "S4 y-position", 200, -100, 100, "S4 y-position", kYellow-7, kBlack);
        h1_b2 = MakeTH1(dir_tac_1d, "D", "h1_b2", "AngleY S2", 200, -100, 100, "AngleY S2", kYellow-7, kBlack);
        h1_b4 = MakeTH1(dir_tac_1d, "D", "h1_b4", "AngleY S4", 200, -100, 100, "AngleY S4", kYellow-7, kBlack);
        h1_beta = MakeTH1(dir_tac_1d, "D", "h1_beta", "Beta", 500, 0.0, 1.0, "Beta", kPink-3, kBlue+2);
        h1_dEdeg = MakeTH1(dir_tac_1d, "D", "h1_dEdeg", "dE in S2 degrader", 1000, 0.0, 1000., "dE", kPink-3, kBlue+2);
        h1_dEdegoQ = MakeTH1(dir_tac_1d, "D", "h1_dEdegoQ", "dE in S2 degrader / Q", 1000, 0.0, 10.0, "dE / Q", kPink-3, kBlue+2);
        for (int i = 0; i < 2; i++) h1_rho[i] = MakeTH1(dir_tac_1d, "D", Form("h1_rho_%i", i), Form("rho %i", i), 100, 0.0, 1.0, Form("rho %i", i), kPink-3, kBlue+2); 
        for (int i = 0; i < 2; i++) h1_brho[i] = MakeTH1(dir_tac_1d, "D", Form("h1_brho_%i", i), Form("brho %i", i), 100, 0.0, 1.0, Form("brho %i", i), kPink-3, kBlue+2);
        h1_music41_dE = MakeTH1(dir_tac_1d, "D", "h1_music41_dE", "Energy loss in MUSIC 41", 1000, 0.0, 4000.0, "dE MUSIC 41", kPink-3, kBlue+2);
        h1_music42_dE = MakeTH1(dir_tac_1d, "D", "h1_music42_dE", "Energy loss in MUSIC 41", 1000, 0.0, 4000.0, "dE MUSIC 42", kPink-3, kBlue+2);
        h1_music41_dE_cor = MakeTH1(dir_tac_1d, "D", "h1_music41_dE_cor", "Energy loss (cor) in MUSIC 41", 4000, 0.0, 4000.0, "dE (cor) MUSIC 41", kPink-3, kBlue+2);
        h1_music42_dE_cor = MakeTH1(dir_tac_1d, "D", "h1_music42_dE_cor", "Energy loss (cor) in MUSIC 42", 4000, 0.0, 4000.0, "dE (cor) MUSIC 42", kPink-3, kBlue+2);

        h1_sci_e_21 = MakeTH1(dir_tac_1d, "F", "h1_sci_e_21", "SCI 21 E", 4000, 0.0, 4000.0, "SCI 21 E", kPink-3, kBlue+2);
        h1_sci_e_22 = MakeTH1(dir_tac_1d, "F", "h1_sci_e_22", "SCI 22 E", 4000, 0.0, 4000.0, "SCI 22 E", kPink-3, kBlue+2);
        h1_sci_e_31 = MakeTH1(dir_tac_1d, "F", "h1_sci_e_31", "SCI 31 E", 4000, 0.0, 4000.0, "SCI 31 E", kPink-3, kBlue+2);
        h1_sci_e_41 = MakeTH1(dir_tac_1d, "F", "h1_sci_e_41", "SCI 41 E", 4000, 0.0, 4000.0, "SCI 41 E", kPink-3, kBlue+2);
        h1_sci_e_42 = MakeTH1(dir_tac_1d, "F", "h1_sci_e_42", "SCI 42 E", 4000, 0.0, 4000.0, "SCI 42 E", kPink-3, kBlue+2);
        h1_sci_e_43 = MakeTH1(dir_tac_1d, "F", "h1_sci_e_43", "SCI 43 E", 4000, 0.0, 4000.0, "SCI 43 E", kPink-3, kBlue+2);
        h1_sci_e_81 = MakeTH1(dir_tac_1d, "F", "h1_sci_e_81", "SCI 81 E", 4000, 0.0, 4000.0, "SCI 81 E", kPink-3, kBlue+2);
        h1_sci_x_21 = MakeTH1(dir_tac_1d, "F", "h1_sci_x_21", "SCI 21 PosX", 4000, 0.0, 4000.0, "SCI 21 X", kYellow-7, kBlack);
        h1_sci_x_22 = MakeTH1(dir_tac_1d, "F", "h1_sci_x_22", "SCI 22 PosX", 4000, 0.0, 4000.0, "SCI 22 X", kYellow-7, kBlack);
        h1_sci_x_31 = MakeTH1(dir_tac_1d, "F", "h1_sci_x_31", "SCI 31 PosX", 4000, 0.0, 4000.0, "SCI 31 X", kYellow-7, kBlack);
        h1_sci_x_41 = MakeTH1(dir_tac_1d, "F", "h1_sci_x_41", "SCI 41 PosX", 4000, 0.0, 4000.0, "SCI 41 X", kYellow-7, kBlack);
        h1_sci_x_42 = MakeTH1(dir_tac_1d, "F", "h1_sci_x_42", "SCI 42 PosX", 4000, 0.0, 4000.0, "SCI 42 X", kYellow-7, kBlack);
        h1_sci_x_43 = MakeTH1(dir_tac_1d, "F", "h1_sci_x_43", "SCI 43 PosX", 4000, 0.0, 4000.0, "SCI 43 X", kYellow-7, kBlack);
        h1_sci_x_81 = MakeTH1(dir_tac_1d, "F", "h1_sci_x_81", "SCI 81 PosX", 4000, 0.0, 4000.0, "SCI 81 X", kYellow-7, kBlack);
        h1_sci_tof_21_41 = MakeTH1(dir_tac_1d, "F", "h1_sci_tof_21_41", "SCI TOF 21 - 41", 4000, 0.0, 200000.0, "SCI TOF 21 - 41", kPink-3, kBlue+2);
        h1_sci_tof_21_41_calib = MakeTH1(dir_tac_1d, "F", "h1_sci_tof_21_41_calib", "SCI TOF 21 - 41 (Calib)", 4000, 0.0, 200000.0, "SCI TOF 21 - 41 (Calib)", kPink-3, kBlue+2);
        h1_sci_tof_21_42 = MakeTH1(dir_tac_1d, "F", "h1_sci_tof_21_42", "SCI TOF 21 - 42", 4000, 0.0, 200000.0, "SCI TOF 21 - 42", kPink-3, kBlue+2);
        h1_sci_tof_21_42_calib = MakeTH1(dir_tac_1d, "F", "h1_sci_tof_21_42_calib", "SCI TOF 21 - 42 (Calib)", 4000, 0.0, 200000.0, "SCI TOF 21 - 42 (Calib)", kPink-3, kBlue+2);
        h1_sci_tof_21_81 = MakeTH1(dir_tac_1d, "F", "h1_sci_tof_21_81", "SCI TOF 21 - 81", 4000, 0.0, 200000.0, "SCI TOF 21 - 81", kPink-3, kBlue+2);
        h1_sci_tof_21_81_calib = MakeTH1(dir_tac_1d, "F", "h1_sci_tof_21_81_calib", "SCI TOF 21 - 81 (Calib)", 4000, 0.0, 200000.0, "SCI TOF 21 - 81 (Calib)", kPink-3, kBlue+2);
        h1_sci_tof_22_41 = MakeTH1(dir_tac_1d, "F", "h1_sci_tof_22_41", "SCI TOF 22 - 41", 4000, 0.0, 200000.0, "SCI TOF 22 - 41", kPink-3, kBlue+2);
        h1_sci_tof_22_41_calib = MakeTH1(dir_tac_1d, "F", "h1_sci_tof_22_41_calib", "SCI TOF 22 - 41 (Calib)", 4000, 0.0, 200000.0, "SCI TOF 22 - 41 (Calib)", kPink-3, kBlue+2);
        h1_sci_tof_22_81 = MakeTH1(dir_tac_1d, "F", "h1_sci_tof_22_81", "SCI TOF 22 - 81", 4000, 0.0, 200000.0, "SCI TOF 22 - 81", kPink-3, kBlue+2);
        h1_sci_tof_22_81_calib = MakeTH1(dir_tac_1d, "F", "h1_sci_tof_22_81_calib", "SCI TOF 22 - 81 (Calib)", 4000, 0.0, 200000.0, "SCI TOF 22 - 81 (Calib)", kPink-3, kBlue+2);

        // Are Gated 1D desired?
    }

    if (frs_config->plot_mhtdc_2d)
    {
        dir_mhtdc_2d = dir_mhtdc->mkdir("2D PIDs");

        // directory, type, name, title, xbins, xmin, xmax, ybins, ymin, ymax, xtitle, ytitle
        h2_Z_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_AoQ_mhtdc", "Z1 vs. A/Q (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
        h2_Z_vs_AoQ_corr_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_AoQ_corr_mhtdc", "Z1 vs. A/Q (corr) (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z,"A/Q", "Z (MUSIC 1)");
        h2_Z_vs_Z2_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_Z2_mhtdc", "Z1 vs. Z2 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z (MUSIC 1)", "Z (MUSIC 2)");
        h2_Z_vs_AoQ_Zsame_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_AoQ_Zsame_mhtdc", "Z1 vs. A/Q [ABS (Z1 - Z2) < 0.4] (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q", "Z (MUSIC 1)");
        h2_x2_vs_AoQ_Zsame_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x2_vs_AoQ_Zsame_mhtdc", "x2 vs A/Q - [ABS(Z1 - Z2) < 0.4] (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
        h2_x4_vs_AoQ_Zsame_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x4_vs_AoQ_Zsame_mhtdc", "x4 vs A/Q - [ABS(Z1 - Z2) < 0.4] (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
        h2_x2_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x2_vs_AoQ_mhtdc", "x2 vs. A/Q (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q", "S2 x-position");
        h2_x4_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x4_vs_AoQ_mhtdc", "x4 vs. A/Q (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q", "S4 x-position");
        h2_dEdegoQ_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_dEdegoQ_vs_Z_mhtdc", "dE in S2 degrader / Q vs. Z1 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "dE in S2 degrader / Q", "Z (MUSIC 1)");
        h2_dEdeg_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_dEdeg_vs_Z_mhtdc", "dE in S2 degrader vs. Z1 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dE, frs_config->fMax_dE, "dE in S2 degrader", "Z (MUSIC 1)");
        h2_a2_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_a2_vs_AoQ_mhtdc", "A/Q vs. AngleX (S2) (MHTDC)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a2, frs_config->fMax_a2, "A/Q", "AngleX (S2)");
        h2_a4_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_a4_vs_AoQ_mhtdc", "A/Q vs. AngleX (S4) (MHTDC)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a4, frs_config->fMax_a4, "A/Q", "AngleX (S4)");
        h2_Z_vs_dE2_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_dE2_mhtdc", "Z1 vs. dE in MUSIC2 (MHTDC)", 400, frs_config->fMin_Z, frs_config->fMax_Z, 250, frs_config->fMin_dE_Music2, frs_config->fMax_dE_Music2, "Z (MUSIC 1)", "dE in MUSIC 2");
        h2_SC41dE_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_SC41dE_vs_AoQ_mhtdc", "A/Q vs. dE in SC41 (MHTDC)", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000., "A/Q", "dE in SC41");
        h2_SC42dE_vs_AoQ_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_SC42dE_vs_AoQ_mhtdc", "A/Q vs. dE in SC42 (MHTDC)", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000., "A/Q", "dE in SC42");
        h2_SC41dE_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_SC41dE_vs_Z_mhtdc", "Z vs. dE in SC41 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, 0., 4000., "Z", "dE in SC41");
        h2_SC42dE_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_SC42dE_vs_Z_mhtdc", "Z vs. dE in SC42 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, 0., 4000., "Z", "dE in SC42");
        h2_x2_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x2_vs_Z_mhtdc", "x2 vs. Z1 (MHTDC)", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x2, frs_config->fMax_x2, "Z (MUSIC 1)", "S2 x-position");
        h2_x4_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_x4_vs_Z_mhtdc", "x4 vs. Z1 (MHTDC)", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x4, frs_config->fMax_x4, "Z (MUSIC 1)", "S4 x-position");
        h2_Z_vs_Sc21E_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_Z_vs_Sc21E_mhtdc", "Z1 vs. SQRT(Sc21_L * Sc21_R) (MHTDC)", 300, frs_config->fMin_Z, frs_config->fMax_Z, 400, 0., 4000., "Z (MUSIC 1)", "Sc21 E");

        // neither TAC nor MHTDC, don't plot twice..
        if (!frs_config->plot_tac_2d)
        {
            h2_x2_vs_x4 = MakeTH2(dir_mhtdc_2d, "D", "h2_x2_vs_x4", "x2 vs. x4", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_x4, frs_config->fMax_x4, "S2 x-position", "S4 x-position");
            h2_dE_vs_ToF_21_41 = MakeTH2(dir_mhtdc_2d, "D", "h2_dE_vs_ToF_21_41", "ToF 21 - 41 vs. dE in MUSIC1", 2000, 0., 70000., 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "Time of Flight (21 - 41)", "dE in MUSIC 1");
            h2_dE1_vs_x2 = MakeTH2(dir_mhtdc_2d, "D", "h2_dE1_vs_x2", "x2 vs. dE in MUSIC1", 200, frs_config->fMin_x2, frs_config->fMax_x2, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "S2 x-position", "dE in MUSIC 1");
            h2_dE1_vs_x4 = MakeTH2(dir_mhtdc_2d, "D", "h2_dE1_vs_x4", "x4 vs. dE in MUSIC1", 200, frs_config->fMin_x4, frs_config->fMax_x4, 400, frs_config->fMin_dE_Music1, frs_config->fMax_dE_Music1, "S4 x-position", "dE in MUSIC 1");
            h2_x2_vs_a2 = MakeTH2(dir_mhtdc_2d, "D", "h2_x2_vs_a2", "x2 vs. AngleX (S2)", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_a2, frs_config->fMax_a2, "S2 x-position", "AngleX (S2)");
            h2_y2_vs_b2 = MakeTH2(dir_mhtdc_2d, "D", "h2_y2_vs_b2", "y2 vs. AngleY (S2)", 200, frs_config->fMin_y2, frs_config->fMax_y2, 200, frs_config->fMin_b2, frs_config->fMax_b2, "S2 y-position", "AngleY (S2)");
            h2_x4_vs_a4 = MakeTH2(dir_mhtdc_2d, "D", "h2_x4_vs_a4", "x4 vs. AngleX (S4)", 200, frs_config->fMin_x4, frs_config->fMax_x4, 200, frs_config->fMin_a4, frs_config->fMax_a4, "S4 x-position", "AngleX (S4)");
            h2_y4_vs_b4 = MakeTH2(dir_mhtdc_2d, "D", "h2_y4_vs_b4", "y4 vs. AngleY (S4)", 200, frs_config->fMin_y4, frs_config->fMax_y4, 200, frs_config->fMin_b4, frs_config->fMax_b4, "S4 y-position", "AngleY (S4)");
        }

        // Gated
        if (!FrsGates.empty())
        {  
            dir_gated_mhtdc = dir_mhtdc->mkdir("Gated 2D");
            dir_ZvsAoQ_mhtdc = dir_gated_mhtdc->mkdir("ZvsAoQ Gated");
            dir_Z1vsZ2_mhtdc = dir_gated_mhtdc->mkdir("Z1vsZ1 Gated");
            dir_x2vsAoQ_mhtdc = dir_gated_mhtdc->mkdir("x2vsAoQ Gated");
            dir_x4vsAoQ_mhtdc = dir_gated_mhtdc->mkdir("x4vsAoQ Gated");
            dir_dEdegvsZ_mhtdc =  dir_gated_mhtdc->mkdir("dEdegvsZ Gated");

            h2_x2_vs_AoQ_ZAoQgate_mhtdc.resize(FrsGates.size());
            h2_x4_vs_AoQ_ZAoQgate_mhtdc.resize(FrsGates.size());
            h2_Z_vs_AoQ_ZAoQgate_mhtdc.resize(FrsGates.size());
            h2_Z1_vs_Z2_ZAoQgate_mhtdc.resize(FrsGates.size());
            h2_dEdeg_vs_Z_ZAoQgate_mhtdc.resize(FrsGates.size());
            h2_dedegoQ_vs_Z_ZAoQgate_mhtdc.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_Z1_vs_Z2_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_Z_vs_AoQ_Z1Z2gate_mhtdc.resize(FrsGates.size());
            h2_x2_vs_AoQ_x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_Z1_vs_Z2_x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc.resize(FrsGates.size());
            h2_x4_vs_AoQ_x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_Z1_vs_Z2_x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_Z_vs_AoQ_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc.resize(FrsGates.size());
            h2_Z_vs_dEdeg_dEdegZgate_mhtdc.resize(FrsGates.size());
            h2_Z_vs_AoQ_dEdegZgate_mhtdc.resize(FrsGates.size());
            h2_Z1_vs_Z2_dEdegZgate_mhtdc.resize(FrsGates.size());
            h2_x2_vs_AoQ_dEdegZgate_mhtdc.resize(FrsGates.size());
            h2_x4_vs_AoQ_dEdegZgate_mhtdc.resize(FrsGates.size());
            h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc.resize(FrsGates.size());

            for (int gate = 0; gate < FrsGates.size(); gate++)
            {
                h2_x2_vs_AoQ_ZAoQgate_mhtdc[gate] = MakeTH2(dir_ZvsAoQ_mhtdc, "I", Form("h2_x2_vs_AoQ_ZAoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - ZAoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);    
                h2_x4_vs_AoQ_ZAoQgate_mhtdc[gate] = MakeTH2(dir_ZvsAoQ_mhtdc, "I", Form("h2_x4_vs_AoQ_ZAoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - ZAoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_Z_vs_AoQ_ZAoQgate_mhtdc[gate] = MakeTH2(dir_ZvsAoQ_mhtdc, "I", Form("h2_Z_vs_AoQ_ZAoQgate%d_mhtdc",gate), Form("Z vs. A/Q - ZAoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot); // CEJ: why are we using 750 like this here?
                h2_Z1_vs_Z2_ZAoQgate_mhtdc[gate] = MakeTH2(dir_ZvsAoQ_mhtdc, "I", Form("h2_Z1_vs_Z2_ZAoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - ZAoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);            
                h2_dEdeg_vs_Z_ZAoQgate_mhtdc[gate] = MakeTH2(dir_ZvsAoQ_mhtdc, "I", Form("h2_dEdeg_vs_Z_ZAoQgate%d_mhtdc", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);            
                h2_dedegoQ_vs_Z_ZAoQgate_mhtdc[gate] = MakeTH2(dir_ZvsAoQ_mhtdc, "I", Form("h2_dedegoQ_vs_Z_ZAoQgate%d_mhtdc", gate), Form("Z1 vs. dE in S2 degrader - ZAoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);          

                h2_dEdeg_vs_Z_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_Z1vsZ2_mhtdc, "I", Form("h2_dEdeg_vs_Z_Z1Z2gate%d_mhtdc", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);            
                h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_Z1vsZ2_mhtdc, "I", Form("h2_dEdegoQ_vs_Z_Z1Z2gate%d_mhtdc", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);            
                h2_Z1_vs_Z2_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_Z1vsZ2_mhtdc, "I", Form("h2_Z1_vs_Z2_Z1Z2gate%d_mhtdc", gate), Form("Z1 vs. Z2 - Z1Z2 Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);            
                h2_x2_vs_AoQ_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_Z1vsZ2_mhtdc, "I", Form("h2_x2_vs_AoQ_Z1Z2gate%d_mhtdc", gate), Form("x2 vs. A/Q - Z1Z2 Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);            
                h2_x4_vs_AoQ_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_Z1vsZ2_mhtdc, "I", Form("h2_x4_vs_AoQ_Z1Z2gate%d_mhtdc", gate), Form("x4 vs. A/Q - Z1Z2 Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);            
                h2_Z_vs_AoQ_Z1Z2gate_mhtdc[gate] = MakeTH2(dir_Z1vsZ2_mhtdc, "I", Form("h2_Z_vs_AoQ_Z1Z2gate%d_mhtdc", gate), Form("Z1 vs. A/Q - Z1Z2 Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);

                h2_x2_vs_AoQ_x2AoQgate_mhtdc[gate] = MakeTH2(dir_x2vsAoQ_mhtdc, "I", Form("h2_x2_vs_AoQ_x2AoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - x2AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_Z1_vs_Z2_x2AoQgate_mhtdc[gate] = MakeTH2(dir_x2vsAoQ_mhtdc, "I", Form("h2_Z1_vs_Z2_x2AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - x2AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);
                h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate] = MakeTH2(dir_x2vsAoQ_mhtdc, "I", Form("h2_x2_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);                
                h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate] = MakeTH2(dir_x2vsAoQ_mhtdc, "I", Form("h2_x4_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);                
                h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate] = MakeTH2(dir_x2vsAoQ_mhtdc, "I", Form("h2_Z_vs_AoQ_Z1Z2x2AoQgate%d_mhtdc", gate), Form("Z1 vs. A/Q - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);              
                h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc[gate] = MakeTH2(dir_x2vsAoQ_mhtdc, "I", Form("h2_Z1_vs_Z2_Z1Z2x2AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);                
                h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc[gate] = MakeTH2(dir_x2vsAoQ_mhtdc, "I", Form("h2_dEdeg_vs_Z_Z1Z2x2AoQgate%d_mhtdc", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);                
                h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc[gate] = MakeTH2(dir_x2vsAoQ_mhtdc, "I", Form("h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate%d_mhtdc", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x2AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);                

                h2_x4_vs_AoQ_x4AoQgate_mhtdc[gate] = MakeTH2(dir_x4vsAoQ_mhtdc, "I", Form("h2_x4_vs_AoQ_x4AoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - x4AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);            
                h2_Z1_vs_Z2_x4AoQgate_mhtdc[gate] = MakeTH2(dir_x4vsAoQ_mhtdc, "I", Form("h2_Z1_vs_Z2_x4AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - x4AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);
                h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate] = MakeTH2(dir_x4vsAoQ_mhtdc, "I", Form("h2_x2_vs_AoQ_Z1Z2x4AoQgate%d_mhtdc", gate), Form("x2 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);                
                h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate] = MakeTH2(dir_x4vsAoQ_mhtdc, "I", Form("h2_x4_vs_AoQ_Z1Z2x4AoQgate%d_mhtdc", gate), Form("x4 vs. A/Q - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);               
                h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc[gate] = MakeTH2(dir_x4vsAoQ_mhtdc, "I", Form("h2_Z1_vs_Z2_Z1Z2x4AoQgate%d_mhtdc", gate), Form("Z1 vs. Z2 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);
                h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc[gate] = MakeTH2(dir_x4vsAoQ_mhtdc, "I", Form("h2_dEdeg_vs_Z_Z1Z2x4AoQgate%d_mhtdc", gate), Form("dE in S2 degrader vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);                
                h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc[gate] = MakeTH2(dir_x4vsAoQ_mhtdc, "I", Form("h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate%d_mhtdc", gate), Form("dE in S2 degrader / Q vs. Z1 - Z1Z2 Gate 0, x4AoQ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);                

                h2_Z_vs_dEdeg_dEdegZgate_mhtdc[gate] = MakeTH2(dir_dEdegvsZ_mhtdc, "I", Form("h2_Z_vs_dEdeg_dEdegZgate%d_mhtdc", gate), Form("Z1 vs. dE in S2 degrader - dEdegZ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, 10., 100.);            
                h2_Z_vs_AoQ_dEdegZgate_mhtdc[gate] = MakeTH2(dir_dEdegvsZ_mhtdc, "I", Form("h2_Z_vs_AoQ_dEdegZgate%d_mhtdc", gate), Form("Z1 vs. A/Q - dEdegZ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);       
                h2_Z1_vs_Z2_dEdegZgate_mhtdc[gate] = MakeTH2(dir_dEdegvsZ_mhtdc, "I", Form("h2_Z1_vs_Z2_dEdegZgate%d_mhtdc", gate), Form("Z1 vs. Z2 - dEdegZ Gate: %d", gate), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);            
                h2_x2_vs_AoQ_dEdegZgate_mhtdc[gate] = MakeTH2(dir_dEdegvsZ_mhtdc, "I", Form("h2_x2_vs_AoQ_dEdegZgate%d_mhtdc", gate), Form("x2 vs. A/Q - dEdegZ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);     
                h2_x4_vs_AoQ_dEdegZgate_mhtdc[gate] = MakeTH2(dir_dEdegvsZ_mhtdc, "I", Form("h2_x4_vs_AoQ_dEdegZgate%d_mhtdc", gate), Form("x4 vs. A/Q - dEdegZ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);   
                h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc[gate] = MakeTH2(dir_dEdegvsZ_mhtdc, "I", Form("h2_Z_vs_AoQ_Zsame_dEdegZgate%d_mhtdc", gate), Form("Z vs. A/Q [ABS(Z1 - Z2) < 0.4] - dEdegZ Gate: %d", gate), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);
            }
        }
    }

    if (frs_config->plot_mhtdc_1d)
    {
        dir_mhtdc_1d = dir_mhtdc->mkdir("1D Spectra");

        h1_beta_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_beta_mhtdc", "Beta (MHTDC)", 500, 0.0, 1.0, "Beta", kPink-3, kBlue+2);
        h1_AoQ_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_AoQ_mhtdc", "A/Q (MHTDC)", 500, 1.0, 4.0, "A/Q", kPink-3, kBlue+2);
        h1_AoQ_corr_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_AoQ_corr_mhtdc", "A/Q (corr) (MHTDC)", 500, 1.0, 4.0, "A/Q", kPink-3, kBlue+2);
        h1_z_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_z_mhtdc", "Z (MUSIC 1) (MHTDC)", 1000, 0, 100, "Z (MUSIC 1)", kPink-3, kBlue+2);
        h1_z2_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_z2_mhtdc", "Z (MUSIC 2) (MHTDC)", 1000, 0, 100, "Z (MUSIC 2)", kPink-3, kBlue+2);
        h1_dEdeg_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_dEdeg_mhtdc", "dE in S2 degrader (MHTDC)", 1000, 0, 100, "dE", kPink-3, kBlue+2);
        h1_dEdegoQ_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_dEdegoQ_mhtdc", "dE in S2 degrader / Q (MHTDC)", 1000, 0.0, 2.0, "dE / Q", kPink-3, kBlue+2);

        if (!frs_config->plot_tac_1d)
        {
            h1_x2 = MakeTH1(dir_tac_1d, "D", "h1_x2", "S2 x-position", 200, -100, 100, "x2", kYellow-7, kBlack);
            h1_x4 = MakeTH1(dir_tac_1d, "D", "h1_x4", "S4 x-position", 200, -100, 100, "x4", kYellow-7, kBlack);
            h1_a2 = MakeTH1(dir_tac_1d, "D", "h1_a2", "AngleX S2", 200, -100, 100, "a2", kYellow-7, kBlack);
            h1_a4 = MakeTH1(dir_tac_1d, "D", "h1_a4", "AngleX S4", 200, -100, 100, "a4", kYellow-7, kBlack);
            h1_y2 = MakeTH1(dir_tac_1d, "D", "h1_y2", "S2 y-position", 200, -100, 100, "y2", kYellow-7, kBlack);
            h1_y4 = MakeTH1(dir_tac_1d, "D", "h1_y4", "S4 y-position", 200, -100, 100, "y4", kYellow-7, kBlack);
            h1_b2 = MakeTH1(dir_tac_1d, "D", "h1_b2", "AngleY S2", 200, -100, 100, "b2", kYellow-7, kBlack);
            h1_b4 = MakeTH1(dir_tac_1d, "D", "h1_b4", "AngleY S4", 200, -100, 100, "b4", kYellow-7, kBlack);
        }
    }

    // :::::: Rates ::::::: //
    h1_tpc21_rate = MakeTH1(dir_rates, "I", "h1_tpc21_rate", "TPC 21 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    h1_tpc22_rate = MakeTH1(dir_rates, "I", "h1_tpc22_rate", "TPC 22 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    h1_tpc23_rate = MakeTH1(dir_rates, "I", "h1_tpc23_rate", "TPC 23 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    h1_tpc24_rate = MakeTH1(dir_rates, "I", "h1_tpc24_rate", "TPC 24 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    h1_tpc41_rate = MakeTH1(dir_rates, "I", "h1_tpc41_rate", "TPC 41 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
    h1_tpc42_rate = MakeTH1(dir_rates, "I", "h1_tpc42_rate", "TPC 42 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);


    // Drifts
    h2_Z1_vs_T = MakeTH2(dir_drifts, "D", "h2_Z1_vs_T", "Z1 vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z1_driftcorr_vs_T = MakeTH2(dir_drifts, "D", "h2_Z1_driftcorr_vs_T", "Z1 DriftCorr vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_AoQ_vs_T = MakeTH2(dir_drifts, "D", "h2_AoQ_vs_T", "A/Q vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ);
    h2_AoQ_driftcorr_vs_T = MakeTH2(dir_drifts, "D", "h2_AoQ_driftcorr_vs_T", "A/Q DriftCorr vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ);
    h2_Z1_vs_T_mhtdc = MakeTH2(dir_drifts, "D", "h2_Z1_vs_T_mhtdc", "Z1 (MHTDC) vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_AoQ_vs_T_mhtdc = MakeTH2(dir_drifts, "D", "h2_AoQ_vs_T_mhtdc", "A/Q (MHTDC) vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ);
    h2_sci_tof_21_41_vs_T = MakeTH2(dir_drifts, "F", "h2_sci_tof_21_42_vs_T", "TOF 21 - 41 vs. Time [mins]", 500, 0, 10000, 4000, 0.0, 200000.0);
    h2_sci_tof_21_42_vs_T = MakeTH2(dir_drifts, "F", "h2_sci_tof_21_42_vs_T", "TOF 21 - 42 vs. Time [mins]", 500, 0, 10000, 4000, 0.0, 200000.0);
    h2_sci_tof_21_81_vs_T = MakeTH2(dir_drifts, "F", "h2_sci_tof_21_81_vs_T", "TOF 21 - 81 vs. Time [mins]", 500, 0, 10000, 4000, 0.0, 200000.0);
    h2_sci_tof_22_41_vs_T = MakeTH2(dir_drifts, "F", "h2_sci_tof_22_41_vs_T", "TOF 22 - 41 vs. Time [mins]", 500, 0, 10000, 4000, 0.0, 200000.0);
    h2_sci_tof_22_81_vs_T = MakeTH2(dir_drifts, "F", "h2_sci_tof_22_81_vs_T", "TOF 22 - 81 vs. Time [mins]", 500, 0, 10000, 4000, 0.0, 200000.0);
    for (int i = 0; i < 6; i++) h2_tpc_vs_T[i] = MakeTH2(dir_drifts, "D", Form("h2_tpc_vs_T_%i", i), Form("TPC %i X vs. T", i), 500,0, 10000, 200, -100, 100);
    

    return kSUCCESS;

}

void FrsNearlineSpectra::Exec(Option_t* option)
{   
    int64_t frs_wr = 0; int64_t trav_mus_wr = 0;
    if (hitArray->size() <= 0) return;

    fNEvents++;

    Long64_t FRS_time_mins = 0;
    auto const & hitItem = hitArray->at(0); // should only be size=1! check
    if(hitItem.Get_wr_t() > 0) FRS_time_mins = (hitItem.Get_wr_t() - exp_config->exp_start_time)/ 60E9;

    // Get the minimum and maximum FRS_time_mins
    if (FRS_time_mins > 0) 
    {
        frs_time_min = std::min(frs_time_min, static_cast<double>(FRS_time_mins));
        frs_time_max = std::max(frs_time_max, static_cast<double>(FRS_time_mins));
    }


    // :::::::::: TAC ::::::::::::: //
    // ---------------------------- //
    if (frs_config->plot_tac_2d)
    {

        if (hitItem.Get_ID_AoQ_s2s4() > 0 && hitItem.Get_ID_z41() > 0) h2_Z_vs_AoQ->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_z41());
        if (hitItem.Get_ID_AoQ_driftcorr() > 0 && hitItem.Get_ID_z_driftcorr() > 0) h2_Z_vs_AoQ_driftcorr->Fill(hitItem.Get_ID_AoQ_driftcorr(), hitItem.Get_ID_z_driftcorr());
        
        if (hitItem.Get_ID_AoQ_corr_s2s4() > 0 && hitItem.Get_ID_z41() > 0) h2_Z_vs_AoQ_corr->Fill(hitItem.Get_ID_AoQ_corr_s2s4(), hitItem.Get_ID_z41());
        if (hitItem.Get_ID_z41() > 0 && hitItem.Get_ID_z42() > 0) h2_Z_vs_Z2->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_z42());
        if (TMath::Abs(hitItem.Get_ID_z41() - hitItem.Get_ID_z42()) < 0.4) // CEJ: should we .config this condition?
        {
            h2_Z_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_z41());
            h2_x4_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x4());
            h2_x2_vs_AoQ_Zsame->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x2());
        }

        if (hitItem.Get_ID_AoQ_s2s4() > 0 && hitItem.Get_ID_x2() > -100 && hitItem.Get_ID_x2() < 100) h2_x2_vs_AoQ->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x2());
        if (hitItem.Get_ID_AoQ_s2s4() > 0 && hitItem.Get_ID_x4() > -100 && hitItem.Get_ID_x4() < 100) h2_x4_vs_AoQ->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x4());
        if (hitItem.Get_ID_z41() > 0 && hitItem.Get_ID_dEdegoQ() != 0) h2_dEdegoQ_vs_Z->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdegoQ());
        if (hitItem.Get_ID_z41() > 0 && hitItem.Get_ID_dEdeg_z41() != 0) h2_dEdeg_vs_Z->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdeg_z41());
        if (hitItem.Get_ID_AoQ_s2s4() != 0 && hitItem.Get_ID_a2() != 0) h2_a2_vs_AoQ->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_a2());
        if (hitItem.Get_ID_AoQ_s2s4() != 0 && hitItem.Get_ID_a4() != 0) h2_a4_vs_AoQ->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_a4());
        if (hitItem.Get_ID_z41() != 0 && hitItem.Get_music42_dE() != 0) h2_Z_vs_dE2->Fill(hitItem.Get_ID_z41(), hitItem.Get_music42_dE());
        if (hitItem.Get_ID_x2() != 0 && hitItem.Get_ID_x4() != 0) h2_x2_vs_x4->Fill(hitItem.Get_ID_x2(), hitItem.Get_ID_x4());


        if (hitItem.Get_ID_AoQ_s2s4() != 0 && hitItem.Get_sci_e_41() != 0) h2_SC41dE_vs_AoQ->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_sci_e_41());
        if (hitItem.Get_ID_AoQ_s2s4() != 0 && hitItem.Get_sci_e_42() != 0) h2_SC42dE_vs_AoQ->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_sci_e_42());
        if (hitItem.Get_ID_z41() != 0 && hitItem.Get_sci_e_41() != 0) h2_SC41dE_vs_Z->Fill(hitItem.Get_ID_z41(), hitItem.Get_sci_e_41());
        if (hitItem.Get_ID_z41() != 0 && hitItem.Get_sci_e_42() != 0) h2_SC42dE_vs_Z->Fill(hitItem.Get_ID_z41(), hitItem.Get_sci_e_42());
        if (hitItem.Get_sci_tof_21_41() != 0 && hitItem.Get_music41_dE() != 0) h2_dE_vs_ToF_21_41->Fill(hitItem.Get_sci_tof_21_41(), hitItem.Get_music41_dE());
        if (hitItem.Get_ID_z41() != 0 && hitItem.Get_ID_x2() != 0) h2_x2_vs_Z->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_x2());
        if (hitItem.Get_ID_z41() != 0 && hitItem.Get_ID_x4() != 0) h2_x4_vs_Z->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_x4());
        if (hitItem.Get_ID_x2() != 0 && hitItem.Get_music41_dE() != 0) h2_dE1_vs_x2->Fill(hitItem.Get_ID_x2(), hitItem.Get_music41_dE());
        if (hitItem.Get_ID_x4() != 0 && hitItem.Get_music41_dE() != 0) h2_dE1_vs_x4->Fill(hitItem.Get_ID_x4(), hitItem.Get_music41_dE());
        if (hitItem.Get_ID_x2() != 0 && hitItem.Get_ID_a2() != 0) h2_x2_vs_a2->Fill(hitItem.Get_ID_x2(), hitItem.Get_ID_a2());
        if (hitItem.Get_ID_y2() != 0 && hitItem.Get_ID_b2() != 0) h2_y2_vs_b2->Fill(hitItem.Get_ID_y2(), hitItem.Get_ID_b2());
        if (hitItem.Get_ID_x4() != 0 && hitItem.Get_ID_a4() != 0) h2_x4_vs_a4->Fill(hitItem.Get_ID_x4(), hitItem.Get_ID_a4());
        if (hitItem.Get_ID_y4() != 0 && hitItem.Get_ID_b4() != 0) h2_y4_vs_b4->Fill(hitItem.Get_ID_y4(), hitItem.Get_ID_b4());
        if (hitItem.Get_ID_z41() != 0 && hitItem.Get_sci_e_21() != 0) h2_Z_vs_Sc21E->Fill(hitItem.Get_ID_z41(), hitItem.Get_sci_e_21());

        if (!FrsGates.empty())
        {
            for (int gate = 0; gate < FrsGates.size(); gate++)
            {   
                if (FrsGates[gate]->Passed_ZvsAoQ(hitItem.Get_ID_z41(), hitItem.Get_ID_AoQ_s2s4()))
                {
                    h2_Z_vs_AoQ_ZAoQgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_z41());
                    h2_Z1_vs_Z2_ZAoQgate[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_z42());
                    h2_x2_vs_AoQ_ZAoQgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x2());
                    h2_x4_vs_AoQ_ZAoQgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x4());
                    h2_dEdeg_vs_Z_ZAoQgate[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdeg_z41());
                    h2_dedegoQ_vs_Z_ZAoQgate[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdegoQ());
                }
            
                if (FrsGates[gate]->Passed_ZvsZ2(hitItem.Get_ID_z41(), hitItem.Get_ID_z42()))
                {
                    h2_dEdeg_vs_Z_Z1Z2gate[gate]->Fill(hitItem.Get_ID_z41(),hitItem.Get_ID_dEdeg_z41());
                    h2_dEdegoQ_vs_Z_Z1Z2gate[gate]->Fill(hitItem.Get_ID_z41(),hitItem.Get_ID_dEdegoQ());
                    h2_Z1_vs_Z2_Z1Z2gate[gate]->Fill(hitItem.Get_ID_z41(),hitItem.Get_ID_z42());

                    if(hitItem.Get_ID_AoQ_s2s4() > 1 && hitItem.Get_ID_AoQ_s2s4() < 3 && hitItem.Get_ID_x2() > -100 && hitItem.Get_ID_x2() < 100) h2_x2_vs_AoQ_Z1Z2gate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x2());
                    if(hitItem.Get_ID_AoQ_s2s4() > 1 && hitItem.Get_ID_AoQ_s2s4() < 3 && hitItem.Get_ID_x4() > -100 && hitItem.Get_ID_x4() < 100) h2_x4_vs_AoQ_Z1Z2gate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x4());
                    if(hitItem.Get_ID_AoQ_s2s4() > 1 && hitItem.Get_ID_AoQ_s2s4() < 3) h2_Z_vs_AoQ_Z1Z2gate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_z41());
                }
                
                if (FrsGates[gate]->Passed_x2vsAoQ(hitItem.Get_ID_x2(), hitItem.Get_ID_AoQ_s2s4()))
                {
                    h2_x2_vs_AoQ_x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x2());
                    h2_Z1_vs_Z2_x2AoQgate[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_z42());
                    
                    if (FrsGates[gate]->Passed_ZvsZ2(hitItem.Get_ID_z41(), hitItem.Get_ID_z42()))
                    {
                        h2_x2_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x2());
                        h2_x4_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x4());
                        h2_Z_vs_AoQ_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_z41());
                        h2_dEdeg_vs_Z_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdeg_z41());
                        h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdegoQ());
                    }
                }

                if (FrsGates[gate]->Passed_x4vsAoQ(hitItem.Get_ID_x4(), hitItem.Get_ID_AoQ_s2s4()))
                {
                    h2_x4_vs_AoQ_x4AoQgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x4());
                    h2_Z1_vs_Z2_x4AoQgate[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_z42());
                    
                    if (FrsGates[gate]->Passed_ZvsZ2(hitItem.Get_ID_z41(), hitItem.Get_ID_z42()))
                    {
                        h2_x2_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x2());
                        h2_x4_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x4());
                        h2_Z_vs_AoQ_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_z41());
                        h2_dEdeg_vs_Z_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdeg_z41());
                        h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdegoQ());
                    }
                }
                        
                if (FrsGates[gate]->Passed_dEdegvsZ(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdeg_z41()))
                {
                    h2_Z_vs_AoQ_dEdegZgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_z41());
                    h2_Z1_vs_Z2_dEdegZgate[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_z42());
                    h2_x2_vs_AoQ_dEdegZgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x2());
                    h2_x4_vs_AoQ_dEdegZgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x4());
                
                    if(fabs(hitItem.Get_ID_z42() - hitItem.Get_ID_z41()) < 0.4) h2_Z_vs_AoQ_Zsame_dEdegZgate[gate]->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_z41());
                }
            }
        }

    }

    if (frs_config->plot_tac_1d)
    {
        if (hitItem.Get_ID_z41() > 0) h1_Z->Fill(hitItem.Get_ID_z41());
        if (hitItem.Get_ID_z_driftcorr() > 0) h1_Z_driftcorr->Fill(hitItem.Get_ID_z_driftcorr());
        if (hitItem.Get_ID_z42() > 0) h1_Z2->Fill(hitItem.Get_ID_z42());
        if (hitItem.Get_ID_AoQ_s2s4() > 0) h1_AoQ->Fill(hitItem.Get_ID_AoQ_s2s4());
        if (hitItem.Get_ID_AoQ_driftcorr() > 0) h1_AoQ_driftcorr->Fill(hitItem.Get_ID_AoQ_driftcorr());
        if (hitItem.Get_ID_AoQ_corr_s2s4() > 0) h1_AoQ_corr->Fill(hitItem.Get_ID_AoQ_corr_s2s4());
        h1_x2->Fill(hitItem.Get_ID_x2());
        h1_x4->Fill(hitItem.Get_ID_x4());
        h1_a2->Fill(hitItem.Get_ID_a2());
        h1_a4->Fill(hitItem.Get_ID_a4());
        h1_y2->Fill(hitItem.Get_ID_y2());
        h1_y4->Fill(hitItem.Get_ID_y4());
        h1_b2->Fill(hitItem.Get_ID_b2());
        h1_b4->Fill(hitItem.Get_ID_b4());
        if (hitItem.Get_ID_beta_s2s4() > 0) h1_beta->Fill(hitItem.Get_ID_beta_s2s4()); 
        if (hitItem.Get_ID_dEdeg_z41() > 0) h1_dEdeg->Fill(hitItem.Get_ID_dEdeg_z41());
        if (hitItem.Get_ID_dEdegoQ() > 0) h1_dEdegoQ->Fill(hitItem.Get_ID_dEdegoQ());
        for (int i = 0; i < 2; i++) if (hitItem.Get_ID_rho()[i] > 0) h1_rho[i]->Fill(hitItem.Get_ID_rho()[i]);
        for (int i = 0; i < 2; i++) if (hitItem.Get_ID_brho()[i] > 0) h1_brho[i]->Fill(hitItem.Get_ID_brho()[i]);
        if (hitItem.Get_music41_dE() > 0) h1_music41_dE->Fill(hitItem.Get_music41_dE());
        if (hitItem.Get_music42_dE() > 0) h1_music42_dE->Fill(hitItem.Get_music42_dE());
        if (hitItem.Get_music41_dE_cor() > 0) h1_music41_dE_cor->Fill(hitItem.Get_music41_dE_cor());
        if (hitItem.Get_music42_dE_cor() > 0) h1_music42_dE_cor->Fill(hitItem.Get_music42_dE_cor());

        if (hitItem.Get_sci_e_21() > 0) h1_sci_e_21->Fill(hitItem.Get_sci_e_21());
        if (hitItem.Get_sci_e_22() > 0) h1_sci_e_22->Fill(hitItem.Get_sci_e_22());
        if (hitItem.Get_sci_e_41() > 0) h1_sci_e_41->Fill(hitItem.Get_sci_e_41());
        if (hitItem.Get_sci_e_42() > 0) h1_sci_e_42->Fill(hitItem.Get_sci_e_42());
        if (hitItem.Get_sci_e_43() > 0) h1_sci_e_43->Fill(hitItem.Get_sci_e_43());
        if (hitItem.Get_sci_e_81() > 0) h1_sci_e_81->Fill(hitItem.Get_sci_e_81());
        if (hitItem.Get_sci_x_21() > 0) h1_sci_x_21->Fill(hitItem.Get_sci_x_21());
        if (hitItem.Get_sci_x_22() > 0) h1_sci_x_22->Fill(hitItem.Get_sci_x_22());
        if (hitItem.Get_sci_x_41() > 0) h1_sci_x_41->Fill(hitItem.Get_sci_x_41());
        if (hitItem.Get_sci_x_42() > 0) h1_sci_x_42->Fill(hitItem.Get_sci_x_42());
        if (hitItem.Get_sci_x_43() > 0) h1_sci_x_43->Fill(hitItem.Get_sci_x_43());
        if (hitItem.Get_sci_x_81() > 0) h1_sci_x_81->Fill(hitItem.Get_sci_x_81());
        if (hitItem.Get_sci_tof_21_41() > 0) h1_sci_tof_21_41->Fill(hitItem.Get_sci_tof_21_41());
        if (hitItem.Get_sci_tof_21_41_calib() > 0) h1_sci_tof_21_41_calib->Fill(hitItem.Get_sci_tof_21_41_calib());
        if (hitItem.Get_sci_tof_21_42() > 0) h1_sci_tof_21_42->Fill(hitItem.Get_sci_tof_21_42());
        if (hitItem.Get_sci_tof_21_42_calib() > 0) h1_sci_tof_21_42_calib->Fill(hitItem.Get_sci_tof_21_42_calib());
        if (hitItem.Get_sci_tof_21_81() > 0) h1_sci_tof_21_81->Fill(hitItem.Get_sci_tof_21_81());
        if (hitItem.Get_sci_tof_21_81_calib() > 0) h1_sci_tof_21_81_calib->Fill(hitItem.Get_sci_tof_21_81_calib());
        if (hitItem.Get_sci_tof_22_41() > 0) h1_sci_tof_22_41->Fill(hitItem.Get_sci_tof_22_41());
        if (hitItem.Get_sci_tof_22_41_calib() > 0) h1_sci_tof_22_41_calib->Fill(hitItem.Get_sci_tof_22_41_calib());
        if (hitItem.Get_sci_tof_22_81() > 0) h1_sci_tof_22_81->Fill(hitItem.Get_sci_tof_22_81());
        if (hitItem.Get_sci_tof_22_81_calib() > 0) h1_sci_tof_22_81_calib->Fill(hitItem.Get_sci_tof_22_81_calib());

        // 1D Gated?
    }
    

    int a = 0;

    // :::::: Multi-hit TDC ::::::: //
    // ---------------------------- //
    if (multihitArray->size() <= 0) return;
    auto const & multiHitItem = multihitArray->at(0);
    std::vector<Float_t> beta_s2s4_mhtdc = multiHitItem.Get_ID_beta_s2s4_mhtdc();
    std::vector<Float_t> AoQ_s2s4_mhtdc = multiHitItem.Get_ID_AoQ_s2s4_mhtdc();
    std::vector<Float_t> AoQ_corr_s2s4_mhtdc = multiHitItem.Get_ID_AoQ_corr_s2s4_mhtdc();
    std::vector<Float_t> z41_mhtdc = multiHitItem.Get_ID_z41_mhtdc();
    std::vector<Float_t> z42_mhtdc = multiHitItem.Get_ID_z42_mhtdc();
    std::vector<Float_t> dEdegoQ_mhtdc = multiHitItem.Get_ID_dEdegoQ_mhtdc();
    std::vector<Float_t> dEdeg_z41_mhtdc = multiHitItem.Get_ID_dEdeg_z41_mhtdc();


    for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
    {
        if (frs_config->plot_mhtdc_2d)
        {
            if (a == 0) multihit_counter++;

            if(AoQ_s2s4_mhtdc.at(i) > 0 && z41_mhtdc.at(i) > 0) h2_Z_vs_AoQ_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
            if(AoQ_corr_s2s4_mhtdc.at(i) > 0 && z41_mhtdc.at(i) > 0) h2_Z_vs_AoQ_corr_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
            if(z41_mhtdc.at(i) > 0 && z42_mhtdc.at(i) > 0) h2_Z_vs_Z2_mhtdc->Fill(z41_mhtdc.at(i), z42_mhtdc.at(i));

            if(TMath::Abs(z41_mhtdc.at(i) - z42_mhtdc.at(i)) < 0.4)
            {
                h2_Z_vs_AoQ_Zsame_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
                h2_x4_vs_AoQ_Zsame_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
                h2_x2_vs_AoQ_Zsame_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
            }

            if(AoQ_s2s4_mhtdc.at(i) > 0 && hitItem.Get_ID_x2() > -100 && hitItem.Get_ID_x2() < 100)  h2_x2_vs_AoQ_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
            if(AoQ_s2s4_mhtdc.at(i) > 0 && hitItem.Get_ID_x4() > -100 && hitItem.Get_ID_x4() < 100)  h2_x4_vs_AoQ_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
            if(z41_mhtdc.at(i) > 0 && dEdegoQ_mhtdc.at(i) != 0) h2_dEdegoQ_vs_Z_mhtdc->Fill(z41_mhtdc.at(i), dEdegoQ_mhtdc.at(i));
            if(z41_mhtdc.at(i) > 0 && dEdeg_z41_mhtdc.at(i) != 0) h2_dEdeg_vs_Z_mhtdc->Fill(z41_mhtdc.at(i), dEdeg_z41_mhtdc.at(i));
            if(AoQ_s2s4_mhtdc.at(i) != 0 && hitItem.Get_ID_a2() != 0) h2_a2_vs_AoQ_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_a2());
            if(AoQ_s2s4_mhtdc.at(i) != 0 && hitItem.Get_ID_a4() != 0) h2_a4_vs_AoQ_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_a4());
            if(z41_mhtdc.at(i) != 0 && hitItem.Get_music42_dE()  != 0) h2_Z_vs_dE2_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_music42_dE());
            if(z41_mhtdc.at(i) != 0 && hitItem.Get_sci_e_21() != 0) h2_Z_vs_Sc21E_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_sci_e_21());
            h2_x2_vs_Z_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_ID_x2());
            h2_x4_vs_Z_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_ID_x4());
            if (AoQ_s2s4_mhtdc.at(i) != 0 && hitItem.Get_sci_e_41() != 0) h2_SC41dE_vs_AoQ_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_sci_e_41());
            if (AoQ_s2s4_mhtdc.at(i) != 0 && hitItem.Get_sci_e_42() != 0) h2_SC42dE_vs_AoQ_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_sci_e_42());
            if (z41_mhtdc.at(i) != 0 && hitItem.Get_sci_e_41() != 0) h2_SC41dE_vs_Z_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_sci_e_41());
            if (z41_mhtdc.at(i) != 0 && hitItem.Get_sci_e_42() != 0) h2_SC42dE_vs_Z_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_sci_e_42()); 

            // Gated PIDs
            if (!FrsGates.empty())
            {
                for (int gate = 0; gate < FrsGates.size(); gate++)
                {
                    if (FrsGates[gate]->Passed_ZvsAoQ(z41_mhtdc.at(i), AoQ_s2s4_mhtdc.at(i)))
                    {
                        h2_x2_vs_AoQ_ZAoQgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
                        h2_x4_vs_AoQ_ZAoQgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
                        h2_Z_vs_AoQ_ZAoQgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
                        h2_Z1_vs_Z2_ZAoQgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), z42_mhtdc.at(i));
                        h2_dEdeg_vs_Z_ZAoQgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdeg_z41_mhtdc.at(i));
                        h2_dedegoQ_vs_Z_ZAoQgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdegoQ_mhtdc.at(i));
                    }
                    
                    if (FrsGates[gate]->Passed_ZvsZ2(z41_mhtdc.at(i), z42_mhtdc.at(i)))
                    {
                        h2_dEdeg_vs_Z_Z1Z2gate_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdeg_z41_mhtdc.at(i));
                        h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdegoQ_mhtdc.at(i));
                        h2_Z1_vs_Z2_Z1Z2gate_mhtdc[gate]->Fill(z41_mhtdc.at(i), z42_mhtdc.at(i));

                        if(hitItem.Get_ID_x2() > -100 && hitItem.Get_ID_x2() < 100)
                        {
                            h2_x2_vs_AoQ_Z1Z2gate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
                        }
                        
                        if(hitItem.Get_ID_x4() > -100 && hitItem.Get_ID_x4() < 100)
                        {
                            h2_x4_vs_AoQ_Z1Z2gate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
                            if(AoQ_s2s4_mhtdc.at(i) != 0 && z41_mhtdc.at(i) != 0) h2_Z_vs_AoQ_Z1Z2gate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
                        }
                    }
                    
                    if (FrsGates[gate]->Passed_x2vsAoQ(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x2()))
                    {
                        h2_x2_vs_AoQ_x2AoQgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
                        h2_Z1_vs_Z2_x2AoQgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), z42_mhtdc.at(i));
                        
                        if (FrsGates[gate]->Passed_ZvsZ2(z41_mhtdc.at(i), z42_mhtdc.at(i)))
                        {      
                            h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
                            h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
                            h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), z42_mhtdc.at(i));
                            h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdeg_z41_mhtdc.at(i));
                            h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdegoQ_mhtdc.at(i));
                        }
                    }
                        
                    if (FrsGates[gate]->Passed_x4vsAoQ(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x4()))
                    {
                        h2_x4_vs_AoQ_x4AoQgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
                        h2_Z1_vs_Z2_x4AoQgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), z42_mhtdc.at(i));
                        
                        if (FrsGates[gate]->Passed_ZvsZ2(z41_mhtdc.at(i), z42_mhtdc.at(i)))
                        {      
                            h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
                            h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
                            h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), z42_mhtdc.at(i));
                            h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdeg_z41_mhtdc.at(i));
                            h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdegoQ_mhtdc.at(i));                        
                        }
                    }
                        
                    if (FrsGates[gate]->Passed_dEdegvsZ(z41_mhtdc.at(i), hitItem.Get_ID_dEdeg_z41()))
                    {
                        h2_Z_vs_dEdeg_dEdegZgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdeg_z41_mhtdc.at(i));
                        h2_Z_vs_AoQ_dEdegZgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
                        h2_Z1_vs_Z2_dEdegZgate_mhtdc[gate]->Fill(z41_mhtdc.at(i), z41_mhtdc.at(i));
                        h2_x2_vs_AoQ_dEdegZgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
                        h2_x4_vs_AoQ_dEdegZgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
                
                        if (fabs(z42_mhtdc.at(i) - z41_mhtdc.at(i)) < 0.4) h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc[gate]->Fill(AoQ_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
                    }
                }
            }
        }

        if (frs_config->plot_mhtdc_1d)
        {
            if (beta_s2s4_mhtdc.at(i) > 0) h1_beta_mhtdc->Fill(beta_s2s4_mhtdc.at(i));
            if (AoQ_s2s4_mhtdc.at(i) > 0) h1_AoQ_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i));
            if (AoQ_corr_s2s4_mhtdc.at(i) > 0) h1_AoQ_corr_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i));
            if (z41_mhtdc.at(i) > 0) h1_z_mhtdc->Fill(z41_mhtdc.at(i));
            if (z42_mhtdc.at(i) > 0) h1_z2_mhtdc->Fill(z42_mhtdc.at(i));
            if (dEdeg_z41_mhtdc.at(i) > 0) h1_dEdeg_mhtdc->Fill(dEdeg_z41_mhtdc.at(i));
            if (dEdegoQ_mhtdc.at(i) > 0) h1_dEdegoQ_mhtdc->Fill(dEdegoQ_mhtdc.at(i));

            if (!frs_config->plot_tac_1d)
            {
                h1_x2->Fill(hitItem.Get_ID_x2());
                h1_x4->Fill(hitItem.Get_ID_x4());
                h1_a2->Fill(hitItem.Get_ID_a2());
                h1_a4->Fill(hitItem.Get_ID_a4());
                h1_y2->Fill(hitItem.Get_ID_y2());
                h1_y4->Fill(hitItem.Get_ID_y4());
                h1_b2->Fill(hitItem.Get_ID_b2());
                h1_b4->Fill(hitItem.Get_ID_b4());
            }
        }
    
    }

    // :::::::: Scalers ::::::::::: //
    // ---------------------------- //
    h1_tpat->Fill(hitItem.Get_tpat());

    // CEJ:: SCALER analysis to be updated...
    // for (int i = 0; i < 32; i++)
    // {
    //     hScaler_per_s[i]->AddBinContent(hitItem.Get_ibin_for_s(), hitItem.Get_increase_sc_temp_user(i));
    //     hScaler_per_s[i+32]->AddBinContent(hitItem.Get_ibin_for_s(), hitItem.Get_increase_sc_temp_main(i));
    //     hScaler_per_100ms[i]->AddBinContent(hitItem.Get_ibin_for_100ms(), hitItem.Get_increase_sc_temp_user(i));
    //     hScaler_per_100ms[i+32]->AddBinContent(hitItem.Get_ibin_for_100ms(), hitItem.Get_increase_sc_temp_main(i));
    //     hScaler_per_spill[i]->AddBinContent(hitItem.Get_ibin_for_spill(), hitItem.Get_increase_sc_temp_user(i));
    //     hScaler_per_spill[i+32]->AddBinContent(hitItem.Get_ibin_for_spill(), hitItem.Get_increase_sc_temp_main(i));
    // }

    // Int_t ratio_product = int(0.95 * hitItem.Get_increase_sc_temp2() + 0.05 * ratio_previous);
    // hScaler_per_s[64]->SetBinContent(hitItem.Get_ibin_for_s(), ratio_product);
    // hScaler_per_100ms[64]->SetBinContent(hitItem.Get_ibin_for_100ms(), ratio_product);
    // hScaler_per_spill[64]->SetBinContent(hitItem.Get_ibin_for_spill(), ratio_product);
    // Int_t ratio_product2 = int(0.95 * hitItem.Get_increase_sc_temp3() + 0.05 * ratio_previous2);
    // hScaler_per_s[65]->SetBinContent(hitItem.Get_ibin_for_s(), ratio_product2);
    // hScaler_per_100ms[65]->SetBinContent(hitItem.Get_ibin_for_100ms(), ratio_product2);
    // hScaler_per_spill[65]->SetBinContent(hitItem.Get_ibin_for_spill(), ratio_product2);

    // for (int i = 0; i < 32; i++)
    // {
    //     hScaler_per_s[i]->SetBinContent(hitItem.Get_ibin_clean_for_s(), 0);
    //     hScaler_per_s[i+32]->SetBinContent(hitItem.Get_ibin_clean_for_s(),0);
    //     hScaler_per_100ms[i]->SetBinContent(hitItem.Get_ibin_clean_for_100ms(), 0);
    //     hScaler_per_100ms[i+32]->SetBinContent(hitItem.Get_ibin_clean_for_100ms(), 0);
    //     hScaler_per_spill[i]->SetBinContent(hitItem.Get_ibin_clean_for_spill(), 0);
    //     hScaler_per_spill[i+32]->SetBinContent(hitItem.Get_ibin_clean_for_spill(), 0);
    // }

    // ::::: Detector Drifts :::::: //
    // ---------------------------- //
    if (hitItem.Get_ID_z41() > 0 && FRS_time_mins > 0) h2_Z1_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_z41());
    if (hitItem.Get_ID_z_driftcorr() > 0 && FRS_time_mins > 0) h2_Z1_driftcorr_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_z_driftcorr());
    if (hitItem.Get_ID_AoQ_s2s4() > 0 && FRS_time_mins > 0) h2_AoQ_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_AoQ_s2s4());
    if (hitItem.Get_ID_AoQ_driftcorr() > 0 && FRS_time_mins > 0) h2_AoQ_driftcorr_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_AoQ_driftcorr());
    //if (z41_mhtdc.at(i) > 0 && FRS_time_mins > 0) h2_Z1_vs_T_mhtdc->Fill(FRS_time_mins, z41_mhtdc.at(i));
    //if (AoQ_s2s4_mhtdc.at(i) > 0 && FRS_time_mins > 0) h2_AoQ_vs_T_mhtdc->Fill(FRS_time_mins, AoQ_s2s4_mhtdc.at(i));
    h2_sci_tof_21_41_vs_T->Fill(FRS_time_mins, hitItem.Get_sci_tof_21_41()); // calib??
    h2_sci_tof_21_42_vs_T->Fill(FRS_time_mins, hitItem.Get_sci_tof_21_42()); // calib??
    h2_sci_tof_21_81_vs_T->Fill(FRS_time_mins, hitItem.Get_sci_tof_21_81()); // calib??
    h2_sci_tof_22_41_vs_T->Fill(FRS_time_mins, hitItem.Get_sci_tof_22_41()); // calib??
    h2_sci_tof_22_81_vs_T->Fill(FRS_time_mins, hitItem.Get_sci_tof_22_81()); // calib??

    

    // :::::::: TPC Rates ::::::::: //
    // ---------------------------- //
    // if (tpcCalArray)
    // {
    //     auto const & tpcCalItem = tpcCalArray->at(0);
    //     tpc_x = tpcCalItem.Get_tpc_x();
    //     for (int i = 0; i < 6; i++) h2_tpc_vs_T[i]->Fill(FRS_time_mins, tpc_x[i]);

    //     int64_t wr_dt = (frs_wr - saved_frs_wr) / 1e9; // conv to s

    //     if (wr_dt < 2 && saved_frs_wr != 0)
    //     {
    //         for (int i = 0; i < 6; i++)
    //         {
    //             if (tpc_x[i]) tpc_counters[i]++;
    //         }
    //     }
    //     else 
    //     {
    //         for (int i = 0; i < 6; i++)
    //         {
    //             tpc_rates[i] = tpc_counters[i] / wr_dt;
    //             tpc_counters[i] = 0;

    //             if (i == 0) h1_tpc21_rate->SetBinContent(tpc_running_count, tpc_rates[i]);
    //             else if (i == 1) h1_tpc22_rate->SetBinContent(tpc_running_count, tpc_rates[i]);
    //             else if (i == 2) h1_tpc23_rate->SetBinContent(tpc_running_count, tpc_rates[i]);
    //             else if (i == 3) h1_tpc24_rate->SetBinContent(tpc_running_count, tpc_rates[i]);
    //             else if (i == 4) h1_tpc41_rate->SetBinContent(tpc_running_count, tpc_rates[i]);
    //             else if (i == 5) h1_tpc42_rate->SetBinContent(tpc_running_count, tpc_rates[i]);

    //         }

    //         saved_frs_wr = frs_wr;
    //         tpc_running_count++;
    //         if (tpc_running_count == 1800) tpc_running_count = 0;
    //     }
    // }

}


void FrsNearlineSpectra::FinishEvent()
{
    
}

void FrsNearlineSpectra::FinishTask()
{
    if (found_dir_frs == false)
    {
        TDirectory* tmp = gDirectory;
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_frs->Write();
        gDirectory = tmp;
        c4LOG(info, "Written FRS analysis histograms to file.");
        c4LOG(info, "Multi Hit events from FRS : " << multihit_counter << " FRS events : " << fNEvents );
    }
    
}

ClassImp(FrsNearlineSpectra)
