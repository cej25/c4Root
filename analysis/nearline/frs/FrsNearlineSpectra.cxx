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

    num_frs_gates = FrsGates.size();


    // :::: ID ::::
    dir_id = dir_frs->mkdir("ID");
    dir_id_s1s2 = dir_id->mkdir("S1S2");
    dir_id_s1s2_1d = dir_id_s1s2->mkdir("1D");
    dir_id_s1s2_2d = dir_id_s1s2->mkdir("2D");
    dir_id_s2s4 = dir_id->mkdir("S2S4");
    dir_id_s2s4_1d = dir_id_s2s4->mkdir("1D");
    dir_id_s2s4_2d = dir_id_s2s4->mkdir("2D");
    
    h1_x1 = MakeTH1(dir_id_s1s2_1d, "D", "h1_x1", "S1 x-position", 200, -100, 100, "x1", kYellow-7, kBlack);
    h1_a1 = MakeTH1(dir_id_s1s2_1d, "D", "h1_a1", "AngleX S1", 200, -100, 100, "a1", kYellow-7, kBlack);
    h1_y1 = MakeTH1(dir_id_s1s2_1d, "D", "h1_y1", "S1 y-position", 200, -100, 100, "y1", kYellow-7, kBlack);
    h1_b1 = MakeTH1(dir_id_s1s2_1d, "D", "h1_b1", "AngleY S1", 200, -100, 100, "b1", kYellow-7, kBlack);
    h1_x2 = MakeTH1(dir_id_s2s4_1d, "D", "h1_x2", "S2 x-position", 200, -100, 100, "x2", kYellow-7, kBlack);
    h1_a2 = MakeTH1(dir_id_s2s4_1d, "D", "h1_a2", "AngleX S2", 200, -100, 100, "a2", kYellow-7, kBlack);
    h1_y2 = MakeTH1(dir_id_s2s4_1d, "D", "h1_y2", "S2 y-position", 200, -100, 100, "y2", kYellow-7, kBlack);
    h1_b2 = MakeTH1(dir_id_s2s4_1d, "D", "h1_b2", "AngleY S2", 200, -100, 100, "b2", kYellow-7, kBlack);
    h1_x4 = MakeTH1(dir_id_s2s4_1d, "D", "h1_x4", "S4 x-position", 200, -100, 100, "x4", kYellow-7, kBlack);
    h1_a4 = MakeTH1(dir_id_s2s4_1d, "D", "h1_a4", "AngleX S4", 200, -100, 100, "a4", kYellow-7, kBlack);
    h1_y4 = MakeTH1(dir_id_s2s4_1d, "D", "h1_y4", "S4 y-position", 200, -100, 100, "y4", kYellow-7, kBlack);    
    h1_b4 = MakeTH1(dir_id_s2s4_1d, "D", "h1_b4", "AngleY S4", 200, -100, 100, "b4", kYellow-7, kBlack);
    h1_dEdegoQ = MakeTH1(dir_id_s2s4_1d, "D", "h1_dEdegoQ", "dE in S2 degrader / Q", 1000, 0.0, 10.0, "dE / Q", kPink-3, kBlue+2);
    for (int i = 0; i < 2; i++) h1_rho[i] = MakeTH1(dir_id_s2s4_1d, "D", Form("h1_rho_%i", i), Form("rho %i", i), 100, 0.0, 1.0, Form("rho %i", i), kPink-3, kBlue+2); 
    for (int i = 0; i < 2; i++) h1_brho[i] = MakeTH1(dir_id_s2s4_1d, "D", Form("h1_brho_%i", i), Form("brho %i", i), 100, 0.0, 1.0, Form("brho %i", i), kPink-3, kBlue+2);

    h2_x2_vs_x4 = MakeTH2(dir_id_s2s4_2d, "D", "h2_x2_vs_x4", "x2 vs. x4", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_x4, frs_config->fMax_x4, "S2 x-position", "S4 x-position");
    h2_x2_vs_a2 = MakeTH2(dir_id_s2s4_2d, "D", "h2_x2_vs_a2", "x2 vs. AngleX (S2)", 200, frs_config->fMin_x2, frs_config->fMax_x2, 200, frs_config->fMin_a2, frs_config->fMax_a2, "S2 x-position", "AngleX (S2)");
    h2_y2_vs_b2 = MakeTH2(dir_id_s2s4_2d, "D", "h2_y2_vs_b2", "y2 vs. AngleY (S2)", 200, frs_config->fMin_y2, frs_config->fMax_y2, 200, frs_config->fMin_b2, frs_config->fMax_b2, "S2 y-position", "AngleY (S2)");
    h2_x4_vs_a4 = MakeTH2(dir_id_s2s4_2d, "D", "h2_x4_vs_a4", "x4 vs. AngleX (S4)", 200, frs_config->fMin_x4, frs_config->fMax_x4, 200, frs_config->fMin_a4, frs_config->fMax_a4, "S4 x-position", "AngleX (S4)");
    h2_y4_vs_b4 = MakeTH2(dir_id_s2s4_2d, "D", "h2_y4_vs_b4", "y4 vs. AngleY (S4)", 200, frs_config->fMin_y4, frs_config->fMax_y4, 200, frs_config->fMin_b4, frs_config->fMax_b4, "S4 y-position", "AngleY (S4)");
    h2_dE41_vs_ToF_21_41 = MakeTH2(dir_id_s2s4_2d, "D", "h2_dE41_vs_ToF_21_41", "ToF 21 - 41 vs. dE in MUSIC 41", 2000, 0., 70000., 400, frs_config->fMin_dE_music41, frs_config->fMax_dE_music41, "Time of Flight (21 - 41)", "dE in MUSIC 41");
    h2_dE41_vs_x2 = MakeTH2(dir_id_s2s4_2d, "D", "h2_dE41_vs_x2", "x2 vs. dE in MUSIC 41", 200, frs_config->fMin_x2, frs_config->fMax_x2, 400, frs_config->fMin_dE_music41, frs_config->fMax_dE_music41, "S2 x-position", "dE in MUSIC 41");
    h2_dE41_vs_x4 = MakeTH2(dir_id_s2s4_2d, "D", "h2_dE41_vs_x4", "x4 vs. dE in MUSIC 41", 200, frs_config->fMin_x4, frs_config->fMax_x4, 400, frs_config->fMin_dE_music41, frs_config->fMax_dE_music41, "S4 x-position", "dE in MUSIC 41");

    if (frs_config->plot_tac)
    {
        // ::::: 2D :::::
        // S1S2

        // S2S4
        h2_Z41_vs_AoQs2s4 = MakeTH2(dir_id_s2s4_2d, "D", "h2_Z41_vs_AoQs2s4", "Z41 vs. A/Q (S2-S4)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q (S2-S4)", "Z41");
        h2_Z41_vs_AoQs2s4_driftcorr = MakeTH2(dir_id_s2s4_2d, "D", "h2_Z41_vs_Ao4s2s4_driftcorr", "Z41 vs. A/Q (S2-S4) DriftCorr", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q DriftCorr", "Z DriftCorr(MUSIC 1)");
        h2_Z41_vs_AoQs2s4_corr = MakeTH2(dir_id_s2s4_2d, "D", "h2_Z_vs_AoQs2s4_corr", "Z41 vs. A/Q corr (S2-S4)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z,"A/Q (S2-S4)", "Z41");
        h2_Z41_vs_Z42 = MakeTH2(dir_id_s2s4_2d, "D", "h2_Z41_vs_Z42", "Z41 vs. Z42", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z41", "Z42");
        h2_Z41_vs_AoQs2s4_Zsame = MakeTH2(dir_id_s2s4_2d, "D", "h2_Z41_vs_AoQs2s4_Zsame", "Z41 vs. A/Q (S2-S4) [ABS (Z41 - Z42) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q (S2-S4)", "Z41");
        h2_x2_vs_AoQs2s4_Zsame = MakeTH2(dir_id_s2s4_2d, "D", "h2_x2_vs_AoQs2s4_Zsame", "x2 vs A/Q (S2-S4) - [ABS(Z41 - Z42) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q (S2-S4)", "S2 x-position");
        h2_x4_vs_AoQs2s4_Zsame = MakeTH2(dir_id_s2s4_2d, "D", "h2_x4_vs_AoQs2s4_Zsame", "x4 vs A/Q (S2-S4) - [ABS(Z41 - Z42) < 0.4]", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q (S2-S4)", "S4 x-position");
        h2_x2_vs_AoQs2s4 = MakeTH2(dir_id_s2s4_2d, "D", "h2_x2_vs_AoQs2s4", "x2 vs. A/Q (S2-S4)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q (S2-S4)", "S2 x-position");
        h2_x4_vs_AoQs2s4 = MakeTH2(dir_id_s2s4_2d, "D", "h2_x4_vs_AoQs2s4", "x4 vs. A/Q (S2-S4)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q (S2-S4)", "S4 x-position");
        h2_dEdegoQ_vs_Z41 = MakeTH2(dir_id_s2s4_2d, "D", "h2_dEdegoQ_vs_Z41", "dE in S2 degrader / Q vs. Z41", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "dE in S2 degrader / Q", "Z41");
        h2_dEdegZ41_vs_Z41 = MakeTH2(dir_id_s2s4_2d, "D", "h2_dEdegZ41_vs_Z41", "dE in S2 degrader vs. Z41", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dE, frs_config->fMax_dE, "dE in S2 degrader", "Z41");
        h2_a2_vs_AoQs2s4 = MakeTH2(dir_id_s2s4_2d, "D", "h2_a2_vs_AoQs2s4", "A/Q (S2-S4) vs. AngleX (S2)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a2, frs_config->fMax_a2, "A/Q (S2-S4)", "AngleX (S2)");
        h2_a4_vs_AoQs2s4 = MakeTH2(dir_id_s2s4_2d, "D", "h2_a4_vs_AoQs2s4", "A/Q (S2-S4) vs. AngleX (S4)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a4, frs_config->fMax_a4, "A/Q (S2-S4)", "AngleX (S4)");
        h2_Z41_vs_dE42 = MakeTH2(dir_id_s2s4_2d, "D", "h2_Z41_vs_dE42", "Z41 vs. dE in MUSIC 42", 400, frs_config->fMin_Z, frs_config->fMax_Z, 250, frs_config->fMin_dE_music42, frs_config->fMax_dE_music42, "Z41", "dE in MUSIC 42");
        h2_SC41dE_vs_AoQs2s4 = MakeTH2(dir_id_s2s4_2d, "D", "h2_SC41dE_vs_AoQs2s4", "A/Q (S2-S4) vs. dE in SC41", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000., "A/Q (S2-S4)", "dE in SC41");
        h2_SC42dE_vs_AoQs2s4 = MakeTH2(dir_id_s2s4_2d, "D", "h2_SC42dE_vs_AoQs2s4", "A/Q (S2-S4) vs. dE in SC42", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000., "A/Q (S2-S4)", "dE in SC42");
        h2_SC41dE_vs_Z41 = MakeTH2(dir_id_s2s4_2d, "D", "h2_SC41dE_vs_Z41", "Z41 vs. dE in SC41", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, 0., 4000., "Z41", "dE in SC41");
        h2_SC42dE_vs_Z41 = MakeTH2(dir_id_s2s4_2d, "D", "h2_SC42dE_vs_Z41", "Z41 vs. dE in SC42", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, 0., 4000., "Z41", "dE in SC42");
        h2_x2_vs_Z41 = MakeTH2(dir_id_s2s4_2d, "D", "h2_x2_vs_Z41", "x2 vs. Z41", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x2, frs_config->fMax_x2, "Z41", "S2 x-position");
        h2_x4_vs_Z41 = MakeTH2(dir_id_s2s4_2d, "D", "h2_x4_vs_Z41", "x4 vs. Z41", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x4, frs_config->fMax_x4, "Z41", "S4 x-position");
        h2_Z41_vs_Sc21E = MakeTH2(dir_id_s2s4_2d, "D", "h2_Z41_vs_Sc21E", "Z41 vs. SQRT(Sc21_L * Sc21_R)", 300, frs_config->fMin_Z, frs_config->fMax_Z, 400, 0., 4000., "Z41", "Sc21 E");

        // ::::::  1D ::::::::
        // S1S2
        h1_beta_s1s2 = MakeTH1(dir_id_s1s2_1d, "D", "h1_beta_s1s2", "Beta (S1-S2)", 500, 0.0, 1.0, "Beta (S1-S2)", kPink-3, kBlue+2);
        h1_AoQs1s2 = MakeTH1(dir_id_s1s2_1d, "D", "h1_AoQs1s2", "A/Q (S1-S2)", 500, 1.0, 4.0, "A/Q (S1-S2)", kPink-3, kBlue+2); 
        h1_AoQs1s2_corr = MakeTH1(dir_id_s1s2_1d, "D", "h1_AoQs1s2_corr", "A/Q corr (S1-S2)", 500, 1.0, 4.0, "A/Q (S1-S2)", kPink-3, kBlue+2);
        h1_Z21 = MakeTH1(dir_id_s1s2_1d, "D", "h1_Z21", "Z21", 500, 10, 100, "Z21", kPink-3, kBlue+2);
        h1_Z22 = MakeTH1(dir_id_s1s2_1d, "D", "h1_Z22", "Z22", 500, 10, 100, "Z22", kPink-3, kBlue+2);

        // S2S4
        h1_beta_s2s4 = MakeTH1(dir_id_s2s4_1d, "D", "h1_beta_s2s4", "Beta (S2-S4)", 500, 0.0, 1.0, "Beta (S2-S4)", kPink-3, kBlue+2);
        h1_AoQs2s4 = MakeTH1(dir_id_s2s4_1d, "D", "h1_AoQs2s4", "A/Q (S2-S4)", 500, 1.0, 4.0, "A/Q (S2-S4)", kPink-3, kBlue+2); 
        h1_AoQs2s4_driftcorr = MakeTH1(dir_id_s2s4_1d, "D", "h1_AoQs2s4_driftcorr", "A/Q (S2-S4) DriftCorr", 500, 1, 4.0, "A/Q (S2-S4)", kPink-3, kBlue+2); 
        h1_AoQs2s4_corr = MakeTH1(dir_id_s2s4_1d, "D", "h1_AoQs2s4_corr", "A/Q corr (S2-S4)", 500, 1.0, 4.0, "A/Q (S2-S4)", kPink-3, kBlue+2);
        h1_Z41 = MakeTH1(dir_id_s2s4_1d, "D", "h1_Z41", "Z41", 500, 10, 100, "Z41", kPink-3, kBlue+2);
        h1_Z41_driftcorr = MakeTH1(dir_id_s2s4_1d, "D", "h1_Z_driftcorr", "Z41 DriftCorr", 500, 10, 100, "Z41", kPink-3, kBlue+2);
        h1_Z42 = MakeTH1(dir_id_s2s4_1d, "D", "h1_Z42", "Z42", 500, 10, 100, "Z42", kPink-3, kBlue+2);
        h1_Z43 = MakeTH1(dir_id_s2s4_1d, "D", "h1_Z43", "Z43", 500, 10, 100, "Z43", kPink-3, kBlue+2);
        h1_dEdegZ41 = MakeTH1(dir_id_s2s4_1d, "D", "h1_dEdegZ41", "dE in S2 degrader", 1000, 0.0, 1000., "dEdegZ41", kPink-3, kBlue+2);

        // Gated
        if (num_frs_gates > 0)
        {
            dir_id_s1s2_gated = dir_id_s1s2->mkdir("Gated");
            dir_id_s1s2_gates = new TDirectory*[num_frs_gates];
            dir_id_s2s4_gated = dir_id_s2s4->mkdir("Gated");
            dir_id_s2s4_gates = new TDirectory*[num_frs_gates];
            dir_id_sequential = dir_id->mkdir("Sequential");
            dir_id_sequential_gates = new TDirectory*[num_frs_gates];

            // **** CEJ: Currently don't actually have any S1S2/TAC combo, add histos in future when desired ****

            // ---- 2D ------
            // S1S2
       
            // S2S4
            h2_Z41_vs_AoQs2s4_S2S4Gated.resize(num_frs_gates);
            h2_Z41_vs_Z42_S2S4Gated.resize(num_frs_gates);
            h2_x2_vs_AoQs2s4_S2S4Gated.resize(num_frs_gates);
            h2_x4_vs_AoQs2s4_S2S4Gated.resize(num_frs_gates);
            h2_dEdegoQ_vs_Z41_S2S4Gated.resize(num_frs_gates);
            h2_dEdegZ41_vs_Z41_S2S4Gated.resize(num_frs_gates);

            // Sequential


            // ------ 1D --------
            // S2S4
            h1_beta_s2s4_S2S4Gated.resize(num_frs_gates);
            h1_AoQs2s4_S2S4Gated.resize(num_frs_gates);
            h1_Z41_S2S4Gated.resize(num_frs_gates);
            h1_Z42_S2S4Gated.resize(num_frs_gates);
     

            for (int gate = 0; gate < num_frs_gates; gate++)
            {
                std::string gname = "" + FrsGates.at(gate)->GetName();
                dir_id_s2s4_gates[gate] = dir_id_s2s4_gated->mkdir(gname.c_str());
                // ----- 2D -----
                // S2S4
                h2_Z41_vs_AoQs2s4_S2S4Gated[gate] =  MakeTH2(dir_id_s2s4_gates[gate], "I", Form("h2_Z41_vs_AoQs2s4_S2S4Gated_%s)", gname.c_str()), Form("Z41 vs AoQs2s4 - S2S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);
                h2_Z41_vs_Z42_S2S4Gated[gate] = MakeTH2(dir_id_s2s4_gates[gate], "I", Form("h2_Z41_vs_Z42_S2S4Gated_%s", gname.c_str()), Form("Z41 vs Z42 - S2S4 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);
                h2_x2_vs_AoQs2s4_S2S4Gated[gate] = MakeTH2(dir_id_s2s4_gates[gate], "I", Form("h2_x2_vs_AoQs2s4_S2S4Gated_%s", gname.c_str()), Form("X2 vs AoQs2s4 - S2S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_x4_vs_AoQs2s4_S2S4Gated[gate] = MakeTH2(dir_id_s2s4_gates[gate], "I", Form("h2_x4_vs_AoQs2s4_S2S4Gated_%s", gname.c_str()), Form("X4 vs AoQs2s4 - S2S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_dEdegoQ_vs_Z41_S2S4Gated[gate] = MakeTH2(dir_id_s2s4_gates[gate], "I", Form("h2_dEdegoQ_vs_Z41_S2S4Gated_%s", gname.c_str()), Form("Z41 vs. dE in S2 degrader / Q - S2S4 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);
                h2_dEdegZ41_vs_Z41_S2S4Gated[gate] = MakeTH2(dir_id_s2s4_gates[gate], "I", Form("h2_dEdegZ41_vs_Z41_S2S4Gated_%s", gname.c_str()), Form("Z41 vs. dE in S2 degrader - S2S4 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);

                // ---- 1D ----
                // S2S4
                h1_beta_s2s4_S2S4Gated[gate] = MakeTH1(dir_id_s2s4_gates[gate], "D", Form("h1_beta_s2s4_S2S4Gated_%s", gname.c_str()), Form("Beta (S2-S4) - S2S4 Gate: %s", gname.c_str()), 500, 0.0, 1.0, "Beta (S2-S4)", kPink-3, kBlue+2);
                h1_AoQs2s4_S2S4Gated[gate] = MakeTH1(dir_id_s2s4_gates[gate], "D", Form("h1_AoQs2s4_S2S4Gated_%s", gname.c_str()), Form("A/Q (S2-S4) - S2S4 Gate: %s", gname.c_str()), 500, 1.0, 4.0, "A/Q (S2-S4)", kPink-3, kBlue+2);
                h1_Z41_S2S4Gated[gate] = MakeTH1(dir_id_s2s4_gates[gate], "D", Form("h1_Z41_S2S4Gated_%s", gname.c_str()), Form("Z41 - S2S4 Gate: %s", gname.c_str()), 1000, 0, 100, "Z41", kPink-3, kBlue+2);
                h1_Z42_S2S4Gated[gate] = MakeTH1(dir_id_s2s4_gates[gate], "D", Form("h1_Z42_S2S4Gated_%s", gname.c_str()), Form("Z42 - S2S4 Gate: %s", gname.c_str()), 1000, 0, 100, "Z42", kPink-3, kBlue+2);

            }
        }
    }

    
    // :::: ID_MHTDC ::::
    if (frs_config->plot_mhtdc)
    {
        dir_mhtdc = dir_frs->mkdir("ID_MHTDC");
        dir_mhtdc_s1s2 = dir_mhtdc->mkdir("S1S2");
        dir_mhtdc_s1s2_1d = dir_mhtdc_s1s2->mkdir("1D");
        dir_mhtdc_s1s2_2d = dir_mhtdc_s1s2->mkdir("2D");
        dir_mhtdc_s2s4 = dir_mhtdc->mkdir("S2S4");
        dir_mhtdc_s2s4_1d = dir_mhtdc_s2s4->mkdir("1D");
        dir_mhtdc_s2s4_2d = dir_mhtdc_s2s4->mkdir("2D");

        // ------ 2D ------ 
        // S1S2
        h2_Z21_vs_AoQs1s2_mhtdc = MakeTH2(dir_mhtdc_s1s2_2d, "D", "h2_Z21_vs_AoQs1s2_mhtdc", "Z21 vs. A/Q (S1-S2) (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q (S1-S2)", "Z (MUSIC 21)");
        h2_Z21_vs_AoQs1s2_corr_mhtdc = MakeTH2(dir_mhtdc_s1s2_2d, "D", "h2_Z21_vs_AoQs1s2_corr_mhtdc", "Z21 vs. A/Q corr (S1-S2) (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z,"A/Q (S1-S2)", "Z (MUSIC 21)");
        h2_Z21_vs_Z22_mhtdc = MakeTH2(dir_mhtdc_s1s2_2d, "D", "h2_Z21_vs_Z22_mhtdc", "Z21 vs. Z22 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z (MUSIC 21)", "Z (MUSIC 22)");
        h2_x2_vs_AoQs1s2_mhtdc = MakeTH2(dir_mhtdc_s1s2_2d, "D", "h2_x2_vs_AoQs1s2_mhtdc", "x2 vs. A/Q (S1-S2) (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q (S1-S2)", "S2 x-position");
        h2_a2_vs_AoQs1s2_mhtdc = MakeTH2(dir_mhtdc_s1s2_2d, "D", "h2_a2_vs_AoQs1s2_mhtdc", "A/Q (S1-S2) vs. AngleX (S2) (MHTDC)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a2, frs_config->fMax_a2, "A/Q (S1-S2)", "AngleX (S2)");
        h2_Z21_vs_dE21_mhtdc = MakeTH2(dir_mhtdc_s1s2_2d, "D", "h2_Z21_vs_dE21_mhtdc", "Z21 vs. dE in MUSIC 21 (MHTDC)", 400, frs_config->fMin_Z, frs_config->fMax_Z, 250, frs_config->fMin_dE_music41, frs_config->fMax_dE_music41, "Z (MUSIC 21)", "dE in MUSIC 21");
        h2_x2_vs_Z21_mhtdc = MakeTH2(dir_mhtdc_s1s2_2d, "D", "h2_x2_vs_Z21_mhtdc", "x2 vs. Z21 (MHTDC)", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x2, frs_config->fMax_x2, "Z (MUSIC 21)", "S2 x-position");
        h2_Z21_vs_Sc21E_mhtdc = MakeTH2(dir_mhtdc_s1s2_2d, "D", "h2_Z21_vs_Sc21E_mhtdc", "Z21 vs. SCI 21 E (MHTDC)", 300, frs_config->fMin_Z, frs_config->fMax_Z, 400, 0., 4000., "Z (MUSIC 21)", "SCI 21 E");

        // S2S4
        h2_Z41_vs_AoQs2s4_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_Z41_vs_AoQs2s4_mhtdc", "Z41 vs. A/Q (S2-S4) (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q (S2-S4)", "Z41");
        h2_Z41_vs_AoQs2s4_corr_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_Z41_vs_AoQs2s4_corr_mhtdc", "Z41 vs. A/Q corr (S2-S4) (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z,"A/Q (S2-S4)", "Z41");
        h2_Z41_vs_Z42_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_Z41_vs_Z42_mhtdc", "Z41 vs. Z42 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z41", "Z42");        
        h2_Z21_vs_Z41_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_Z21_vs_Z41_mhtdc", "Z21 (MHTDC) vs. Z41 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z (MUSIC 21)", "Z (MUSIC 41)");
        h2_Z41_vs_AoQs2s4_Zsame_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_Z41_vs_AoQs2s4_Zsame_mhtdc", "Z41 vs. A/Q (S2-S4) [ABS (Z41 - Z42) < 0.4] (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z, "A/Q (S2-S4)", "Z41");
        h2_x2_vs_AoQs2s4_Zsame_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_x2_vs_AoQs2s4_Zsame_mhtdc", "x2 vs A/Q (S2-S4) - [ABS(Z41 - Z42) < 0.4] (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q (S2-S4)", "S2 x-position");
        h2_x4_vs_AoQs2s4_Zsame_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_x4_vs_AoQs2s4_Zsame_mhtdc", "x4 vs A/Q (S2-S4) - [ABS(Z41 - Z42) < 0.4] (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q (S2-S4)", "S4 x-position");
        h2_x2_vs_AoQs2s4_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_x2_vs_AoQs2s4_mhtdc", "x2 vs. A/Q (S2-S4) (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x2, frs_config->fMax_x2, "A/Q (S2-S4)", "S2 x-position");
        h2_x4_vs_AoQs2s4_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_x4_vs_AoQs2s4_mhtdc", "x4 vs. A/Q (S2-S4) (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 200, frs_config->fMin_x4, frs_config->fMax_x4, "A/Q (S2-S4)", "S4 x-position");
        h2_dEdegoQ_vs_Z41_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_dEdegoQ_vs_Z41_mhtdc", "dE in S2 degrader / Q vs. Z41 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dEoQ, frs_config->fMax_dEoQ, "dE in S2 degrader / Q", "Z41");
        h2_dEdegZ41_vs_Z41_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_dEdegZ41_vs_Z41_mhtdc", "dE in S2 degrader vs. Z41 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, frs_config->fMin_dE, frs_config->fMax_dE, "dE in S2 degrader", "Z41");
        h2_a2_vs_AoQs2s4_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_a2_vs_AoQs2s4_mhtdc", "A/Q (S2-S4) vs. AngleX (S2) (MHTDC)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a2, frs_config->fMax_a2, "A/Q (S2-S4)", "AngleX (S2)");
        h2_a4_vs_AoQs2s4_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_a4_vs_AoQs2s4_mhtdc", "A/Q (S2-S4) vs. AngleX (S4) (MHTDC)", 500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 500, frs_config->fMin_a4, frs_config->fMax_a4, "A/Q (S2-S4)", "AngleX (S4)");
        h2_Z41_vs_dE42_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_Z41_vs_dE42_mhtdc", "Z41 vs. dE in MUSIC 42 (MHTDC)", 400, frs_config->fMin_Z, frs_config->fMax_Z, 250, frs_config->fMin_dE_music42, frs_config->fMax_dE_music42, "Z41", "dE in MUSIC 2");
        h2_SC41dE_vs_AoQs2s4_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_SC41dE_vs_AoQs2s4_mhtdc", "A/Q (S2-S4) vs. dE in SC41 (MHTDC)", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000., "A/Q (S2-S4)", "dE in SC41");
        h2_SC42dE_vs_AoQs2s4_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_SC42dE_vs_AoQs2s4_mhtdc", "A/Q (S2-S4) vs. dE in SC42 (MHTDC)", 1000, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, 0., 4000., "A/Q (S2-S4)", "dE in SC42");
        h2_SC41dE_vs_Z41_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_SC41dE_vs_Z41_mhtdc", "Z41 vs. dE in SC41 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, 0., 4000., "Z41", "dE in SC41");
        h2_SC42dE_vs_Z41_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_SC42dE_vs_Z41_mhtdc", "Z41 vs. dE in SC42 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 1000, 0., 4000., "Z41", "dE in SC42");
        h2_x2_vs_Z41_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_x2_vs_Z41_mhtdc", "x2 vs. Z41 (MHTDC)", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x2, frs_config->fMax_x2, "Z41", "S2 x-position");
        h2_x4_vs_Z41_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_x4_vs_Z41_mhtdc", "x4 vs. Z41 (MHTDC)", 400, frs_config->fMin_Z, frs_config->fMax_Z, 200, frs_config->fMin_x4, frs_config->fMax_x4, "Z41", "S4 x-position");
        h2_Z41_vs_Sc21E_mhtdc = MakeTH2(dir_mhtdc_s2s4_2d, "D", "h2_Z41_vs_Sc21E_mhtdc", "Z41 vs. SQRT(Sc21_L * Sc21_R) (MHTDC)", 300, frs_config->fMin_Z, frs_config->fMax_Z, 400, 0., 4000., "Z41)", "Sc21 E");

        // ----- 1D ------ 
        h1_beta_s1s2_mhtdc = MakeTH1(dir_mhtdc_s1s2_1d, "D", "h1_beta_s1s2_mhtdc", "Beta (S1-S2) (MHTDC)", 500, 0.0, 1.0, "Beta (S1-S2)", kPink-3, kBlue+2);
        h1_AoQs1s2_mhtdc = MakeTH1(dir_mhtdc_s1s2_1d, "D", "h1_AoQs1s2_mhtdc", "A/Q (S1-S2) (MHTDC)", 500, 1.0, 4.0, "A/Q (S1-S2)", kPink-3, kBlue+2);
        h1_AoQs1s2_corr_mhtdc = MakeTH1(dir_mhtdc_s1s2_1d, "D", "h1_AoQs1s2_corr_mhtdc", "A/Q corr (S1-S2) (MHTDC)", 500, 1.0, 4.0, "A/Q (S1-S2)", kPink-3, kBlue+2);
        h1_Z21_mhtdc = MakeTH1(dir_mhtdc_s1s2_1d, "D", "h1_Z21_mhtdc", "Z21 (MHTDC)", 1000, 0, 100, "Z21", kPink-3, kBlue+2);
        h1_Z22_mhtdc = MakeTH1(dir_mhtdc_s1s2_1d, "D", "h1_Z22_mhtdc", "Z22 (MHTDC)", 1000, 0, 100, "Z22", kPink-3, kBlue+2);

        h1_beta_s2s4_mhtdc = MakeTH1(dir_mhtdc_s2s4_1d, "D", "h1_beta_s2s4_mhtdc", "Beta (S2-S4) (MHTDC)", 500, 0.0, 1.0, "Beta (S2-S4)", kPink-3, kBlue+2);
        h1_AoQs2s4_mhtdc = MakeTH1(dir_mhtdc_s2s4_1d, "D", "h1_AoQs2s4_mhtdc", "A/Q (S2-S4) (MHTDC)", 500, 1.0, 4.0, "A/Q (S2-S4)", kPink-3, kBlue+2);
        h1_AoQs2s4_corr_mhtdc = MakeTH1(dir_mhtdc_s2s4_1d, "D", "h1_AoQs2s4_corr_mhtdc", "A/Q corr (S2-S4) (MHTDC)", 500, 1.0, 4.0, "A/Q (S2-S4)", kPink-3, kBlue+2);
        h1_Z41_mhtdc = MakeTH1(dir_mhtdc_s2s4_1d, "D", "h1_Z41_mhtdc", "Z41 (MHTDC)", 1000, 0, 100, "Z41", kPink-3, kBlue+2);
        h1_Z42_mhtdc = MakeTH1(dir_mhtdc_s2s4_1d, "D", "h1_Z42_mhtdc", "Z42 (MHTDC)", 1000, 0, 100, "Z42", kPink-3, kBlue+2);
        h1_Z43_mhtdc = MakeTH1(dir_mhtdc_s2s4_1d, "D", "h1_Z43_mhtdc", "Z43 (MHTDC)", 1000, 0, 100, "Z43", kPink-3, kBlue+2);
        h1_dEdegZ41_mhtdc = MakeTH1(dir_mhtdc_s2s4_1d, "D", "h1_dEdegZ41_mhtdc", "dEZ41 in S2 degrader (MHTDC)", 1000, 0, 100, "dEZ41", kPink-3, kBlue+2);

        // Gated
        if (num_frs_gates)
        {
            dir_mhtdc_s1s2_gated = dir_mhtdc_s1s2->mkdir("Gated");
            dir_mhtdc_s1s2_gates = new TDirectory*[num_frs_gates];
            dir_mhtdc_s2s4_gated = dir_mhtdc_s2s4->mkdir("Gated");
            dir_mhtdc_s2s4_gates = new TDirectory*[num_frs_gates];
            dir_mhtdc_sequential = dir_mhtdc->mkdir("Sequential");
            dir_mhtdc_sequential_gates = new TDirectory*[num_frs_gates];
            dir_mhtdc_sequential_rates = new TDirectory*[num_frs_gates];

            // S1S2
            h2_Z21_vs_AoQs1s2_S1S2Gated_mhtdc.resize(num_frs_gates);
            h2_x1_vs_AoQs1s2_S1S2Gated_mhtdc.resize(num_frs_gates);
            h2_x2_vs_AoQs1s2_S1S2Gated_mhtdc.resize(num_frs_gates);
            h2_Z41_vs_AoQs2s4_S1S2Gated_mhtdc.resize(num_frs_gates);
            h2_Z41_vs_Z42_S1S2Gated_mhtdc.resize(num_frs_gates);
            h2_x2_vs_AoQs2s4_S1S2Gated_mhtdc.resize(num_frs_gates);
            h2_x4_vs_AoQs2s4_S1S2Gated_mhtdc.resize(num_frs_gates);
            h2_dEdegoQ_vs_Z41_S1S2Gated_mhtdc.resize(num_frs_gates);
            h2_dEdegZ41_vs_Z41_S1S2Gated_mhtdc.resize(num_frs_gates);

            // S2S4
            h2_Z21_vs_AoQs1s2_S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_x1_vs_AoQs1s2_S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_x2_vs_AoQs1s2_S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_Z41_vs_AoQs2s4_S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_Z41_vs_Z42_S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_x2_vs_AoQs2s4_S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_x4_vs_AoQs2s4_S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_dEdegoQ_vs_Z41_S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_dEdegZ41_vs_Z41_S2S4Gated_mhtdc.resize(num_frs_gates);

            // Sequential
            h2_Z21_Z41_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_Z21_vs_AoQs1s2_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_x1_vs_AoQs1s2_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_x2_vs_AoQs1s2_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_Z41_vs_AoQs2s4_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_Z41_vs_Z42_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_x2_vs_AoQs2s4_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_x4_vs_AoQs2s4_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_dEdegoQ_vs_Z41_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h2_dEdegZ41_vs_Z41_S1S2S4Gated_mhtdc.resize(num_frs_gates);

            // --- 1D ---- 
            h1_beta_s1s2_S1S2Gated_mhtdc.resize(num_frs_gates);
            h1_AoQs1s2_S1S2Gated_mhtdc.resize(num_frs_gates);
            h1_Z21_S1S2Gated_mhtdc.resize(num_frs_gates);
            h1_beta_s2s4_S1S2Gated_mhtdc.resize(num_frs_gates);
            h1_AoQs2s4_S1S2Gated_mhtdc.resize(num_frs_gates);
            h1_Z41_S1S2Gated_mhtdc.resize(num_frs_gates);
            h1_Z42_S1S2Gated_mhtdc.resize(num_frs_gates);

            h1_beta_s1s2_S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_AoQs1s2_S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_Z21_S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_beta_s2s4_S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_AoQs2s4_S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_Z41_S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_Z42_S2S4Gated_mhtdc.resize(num_frs_gates);

            h1_beta_s1s2_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_AoQs1s2_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_Z21_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_beta_s2s4_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_AoQs2s4_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_Z41_S1S2S4Gated_mhtdc.resize(num_frs_gates);
            h1_Z42_S1S2S4Gated_mhtdc.resize(num_frs_gates);

            // --- Rates/Ratio ---- 
            h1_ratio_S2_S4_Gates_mhtdc.resize(num_frs_gates);
            h1_integral_S2_Gates_mhtdc.resize(num_frs_gates);
            h1_integral_S4_Gates_mhtdc.resize(num_frs_gates);

        
            for (int gate = 0; gate < num_frs_gates; gate++)
            {
                std::string gname = "" + FrsGates.at(gate)->GetName();
                dir_mhtdc_s1s2_gates[gate] = dir_mhtdc_s1s2_gated->mkdir(gname.c_str());
                dir_mhtdc_s2s4_gates[gate] = dir_mhtdc_s2s4_gated->mkdir(gname.c_str());
                dir_mhtdc_sequential_gates[gate] = dir_mhtdc_sequential->mkdir(gname.c_str());
                dir_mhtdc_sequential_rates[gate] = dir_mhtdc_sequential_gates[gate]->mkdir("Rates");
                
                // ----- 2D ------
                // S1S2
                h2_Z21_vs_AoQs1s2_S1S2Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s1s2_gates[gate], "I", Form("h2_Z21_vs_AoQs1s2_S1S2Gated_mhtdc_%s", gname.c_str()), Form("Z21 vs AoQs1s2 - S1S2 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);
                h2_x1_vs_AoQs1s2_S1S2Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s1s2_gates[gate], "I", Form("h2_x1_vs_AoQs1s2_S1S2Gated_mhtdc_%s", gname.c_str()), Form("X1 vs AoQs1s2 - S1S2 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_x2_vs_AoQs1s2_S1S2Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s1s2_gates[gate], "I", Form("h2_x2_vs_AoQs1s2_S1S2Gated_mhtdc_%s", gname.c_str()), Form("X2 vs AoQs1s2 - S1S2 Gate: %s", gname.c_str()), 50, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_Z41_vs_AoQs2s4_S1S2Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s1s2_gates[gate], "I", Form("h2_Z41_vs_AoQs2s4_S1S2Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs AoQs2s4 - S1S2 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);
                h2_Z41_vs_Z42_S1S2Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s1s2_gates[gate], "I", Form("h2_Z41_vs_Z42_S1S2Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs Z42 - S1S2 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);
                h2_x2_vs_AoQs2s4_S1S2Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s1s2_gates[gate], "I", Form("h2_x2_vs_AoQs2s4_S1S2Gated_mhtdc_%s", gname.c_str()), Form("X2 vs AoQs2s4 - S1S2 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_x4_vs_AoQs2s4_S1S2Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s1s2_gates[gate], "I", Form("h2_x4_vs_AoQs2s4_S1S2Gated_mhtdc_%s", gname.c_str()), Form("X4 vs AoQs2s4 - S1S2 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_dEdegoQ_vs_Z41_S1S2Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s1s2_gates[gate], "I", Form("h2_dEdegoQ_vs_Z41_S1S2Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs. dE in S2 degrader / Q - S1S2 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);
                h2_dEdegZ41_vs_Z41_S1S2Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s1s2_gates[gate], "I", Form("h2_dEdegZ41_vs_Z41_S1S2Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs. dE in S2 degrader - S1S2 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);

                // S2S4
                h2_Z21_vs_AoQs1s2_S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s2s4_gates[gate], "I", Form("h2_Z21_vs_AoQs1s2_S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z21 vs AoQs1s2 - S2S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);
                h2_x1_vs_AoQs1s2_S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s2s4_gates[gate], "I", Form("h2_x1_vs_AoQs1s2_S2S4Gated_mhtdc_%s", gname.c_str()), Form("X1 vs AoQs1s2 - S2S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_x2_vs_AoQs1s2_S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s2s4_gates[gate], "I", Form("h2_x2_vs_AoQs1s2_S2S4Gated_mhtdc_%s", gname.c_str()), Form("X2 vs AoQs1s2 - S2S4 Gate: %s", gname.c_str()), 50, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_Z41_vs_AoQs2s4_S2S4Gated_mhtdc[gate] =  MakeTH2(dir_mhtdc_s2s4_gates[gate], "I", Form("h2_Z41_vs_AoQs2s4_S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs AoQs2s4 - S2S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);
                h2_Z41_vs_Z42_S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s2s4_gates[gate], "I", Form("h2_Z41_vs_Z42_S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs Z42 - S2S4 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);
                h2_x2_vs_AoQs2s4_S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s2s4_gates[gate], "I", Form("h2_x2_vs_AoQs2s4_S2S4Gated_mhtdc_%s", gname.c_str()), Form("X2 vs AoQs2s4 - S2S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_x4_vs_AoQs2s4_S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s2s4_gates[gate], "I", Form("h2_x4_vs_AoQs2s4_S2S4Gated_mhtdc_%s", gname.c_str()), Form("X4 vs AoQs2s4 - S2S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_dEdegoQ_vs_Z41_S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s2s4_gates[gate], "I", Form("h2_dEdegoQ_vs_Z41_S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs. dE in S2 degrader / Q - S2S4 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);
                h2_dEdegZ41_vs_Z41_S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_s2s4_gates[gate], "I", Form("h2_dEdegZ41_vs_Z41_S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs. dE in S2 degrader - S2S4 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);

                // Sequential
                h2_Z21_Z41_S1S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_sequential_gates[gate], "I", Form("h2_Z21_Z41_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z21 vs Z41 - S1-S2-S4 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);
                h2_Z21_vs_AoQs1s2_S1S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_sequential_gates[gate], "I", Form("h2_Z21_vs_AoQs1s2_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z21 vs AoQs1s2 - S1-S2-S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);
                h2_x1_vs_AoQs1s2_S1S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_sequential_gates[gate], "I", Form("h2_x1_vs_AoQs1s2_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("X1 vs AoQs1s2 - S1-S2-S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_x2_vs_AoQs1s2_S1S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_sequential_gates[gate], "I", Form("h2_x2_vs_AoQs1s2_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("X2 vs AoQs1s2 - S1-S2-S4 Gate: %s", gname.c_str()), 50, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_Z41_vs_AoQs2s4_S1S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_sequential_gates[gate], "I", Form("h2_Z41_vs_AoQs2s4_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs AoQs2s4 - S1-S2-S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 750, id->min_z_plot, id->max_z_plot);
                h2_Z41_vs_Z42_S1S2S4Gated_mhtdc[gate] =  MakeTH2(dir_mhtdc_sequential_gates[gate], "I", Form("h2_Z41_vs_Z42_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs Z42 - S1-S2-S4 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, id->min_z_plot, id->max_z_plot);
                h2_x2_vs_AoQs2s4_S1S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_sequential_gates[gate], "I", Form("h2_x2_vs_AoQs2s4_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("X2 vs AoQs2s4 - S1-S2-S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_x4_vs_AoQs2s4_S1S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_sequential_gates[gate], "I", Form("h2_x4_vs_AoQs2s4_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("X4 vs AoQs2s4 - S1-S2-S4 Gate: %s", gname.c_str()), 750, id->min_aoq_plot, 3.0, 200, -100., 100.);
                h2_dEdegoQ_vs_Z41_S1S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_sequential_gates[gate], "I", Form("h2_dEdegoQ_vs_Z41_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs. dE in S2 degrader / Q - S1-S2-S4 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);
                h2_dEdegZ41_vs_Z41_S1S2S4Gated_mhtdc[gate] = MakeTH2(dir_mhtdc_sequential_gates[gate], "I", Form("h2_dEdegZ41_vs_Z41_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z41 vs. dE in S2 degrader - S1-S2-S4 Gate: %s", gname.c_str()), 750, id->min_z_plot, id->max_z_plot, 750, 10., 50.);

                // ----- 1D ------ 
                h1_beta_s1s2_S1S2Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s1s2_gates[gate], "D", Form("h1_beta_s1s2_S1S2Gated_mhtdc_%s",gname.c_str()), Form("Beta (S1-S2) (MHTDC) - S1S2 Gate: %s", gname.c_str()), 500, 0.0, 1.0, "Beta (S1-S2)", kPink-3, kBlue+2);
                h1_AoQs1s2_S1S2Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s1s2_gates[gate], "D", Form("h1_AoQs1s2_S1S2Gated_mhtdc_%s", gname.c_str()), Form("A/Q (S1-S2) (MHTDC) - S1S2 Gate: %s", gname.c_str()), 500, 1.0, 4.0, "A/Q (S1-S2)", kPink-3, kBlue+2);
                h1_Z21_S1S2Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s1s2_gates[gate], "D", Form("h1_Z21_S1S2Gated_mhtdc_%s", gname.c_str()), Form("Z21 (MHTDC) - S1S2 Gate: %s", gname.c_str()), 1000, 0, 100, "Z21", kPink-3, kBlue+2);
                h1_beta_s2s4_S1S2Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s1s2_gates[gate], "D", Form("h1_beta_s2s4_S1S2Gated_mhtdc_%s", gname.c_str()), Form("Beta (S2-S4) (MHTDC) - S1S2 Gate: %s", gname.c_str()), 500, 0.0, 1.0, "Beta (S2-S4)", kPink-3, kBlue+2);
                h1_AoQs2s4_S1S2Gated_mhtdc[gate] =  MakeTH1(dir_mhtdc_s1s2_gates[gate], "D", Form("h1_AoQs2s4_S1S2Gated_mhtdc_%s", gname.c_str()), Form("A/Q (S2-S4) (MHTDC) - S1S2 Gate: %s", gname.c_str()), 500, 1.0, 4.0, "A/Q (S2-S4)", kPink-3, kBlue+2);
                h1_Z41_S1S2Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s1s2_gates[gate], "D", Form("h1_Z41_S1S2Gated_mhtdc_%s", gname.c_str()), Form("Z41 (MHTDC) - S1S2 Gate: %s", gname.c_str()), 1000, 0, 100, "Z41", kPink-3, kBlue+2);
                h1_Z42_S1S2Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s1s2_gates[gate], "D", Form("h1_Z42_S1S2Gated_mhtdc_%s", gname.c_str()), Form("Z42 (MHTDC) - S1S2 Gate: %s", gname.c_str()), 1000, 0, 100, "Z42", kPink-3, kBlue+2);

                h1_beta_s1s2_S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s2s4_gates[gate], "D", Form("h1_beta_s1s2_S2S4Gated_mhtdc_%s",gname.c_str()), Form("Beta (S1-S2) (MHTDC) - S2S4 Gate: %s", gname.c_str()), 500, 0.0, 1.0, "Beta (S1-S2)", kPink-3, kBlue+2);
                h1_AoQs1s2_S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s2s4_gates[gate], "D", Form("h1_AoQs1s2_S2S4Gated_mhtdc_%s", gname.c_str()), Form("A/Q (S1-S2) (MHTDC) - S2S4 Gate: %s", gname.c_str()), 500, 1.0, 4.0, "A/Q (S1-S2)", kPink-3, kBlue+2);
                h1_Z21_S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s2s4_gates[gate], "D", Form("h1_Z21_S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z21 (MHTDC) - S2S4 Gate: %s", gname.c_str()), 1000, 0, 100, "Z21", kPink-3, kBlue+2);
                h1_beta_s2s4_S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s2s4_gates[gate], "D", Form("h1_beta_s2s4_S2S4Gated_mhtdc_%s", gname.c_str()), Form("Beta (S2-S4) (MHTDC) - S2S4 Gate: %s", gname.c_str()), 500, 0.0, 1.0, "Beta (S2-S4)", kPink-3, kBlue+2);
                h1_AoQs2s4_S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s2s4_gates[gate], "D", Form("h1_AoQs2s4_S2S4Gated_mhtdc_%s", gname.c_str()), Form("A/Q (S2-S4) (MHTDC) - S2S4 Gate: %s", gname.c_str()), 500, 1.0, 4.0, "A/Q (S2-S4)", kPink-3, kBlue+2);
                h1_Z41_S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s2s4_gates[gate], "D", Form("h1_Z41_S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z41 (MHTDC) - S2S4 Gate: %s", gname.c_str()), 1000, 0, 100, "Z41", kPink-3, kBlue+2);
                h1_Z42_S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_s2s4_gates[gate], "D", Form("h1_Z42_S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z42 (MHTDC) - S2S4 Gate: %s", gname.c_str()), 1000, 0, 100, "Z42", kPink-3, kBlue+2);

                h1_beta_s1s2_S1S2S4Gated_mhtdc[gate] =  MakeTH1(dir_mhtdc_sequential_gates[gate], "D", Form("h1_beta_s1s2_S1S2S4Gated_mhtdc_%s",gname.c_str()), Form("Beta (S1-S2) (MHTDC) - S1-S2-S4 Gate: %s", gname.c_str()), 500, 0.0, 1.0, "Beta (S1-S2)", kPink-3, kBlue+2);
                h1_AoQs1s2_S1S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_sequential_gates[gate], "D", Form("h1_AoQs1s2_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("A/Q (S1-S2) (MHTDC) - S1-S2-S4 Gate: %s", gname.c_str()), 500, 1.0, 4.0, "A/Q (S1-S2)", kPink-3, kBlue+2);
                h1_Z21_S1S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_sequential_gates[gate], "D", Form("h1_Z21_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z21 (MHTDC) - S1-S2-S4 Gate: %s", gname.c_str()), 1000, 0, 100, "Z21", kPink-3, kBlue+2);
                h1_beta_s2s4_S1S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_sequential_gates[gate], "D", Form("h1_beta_s2s4_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("Beta (S2-S4) (MHTDC) - S1-S2-S4 Gate: %s", gname.c_str()), 500, 0.0, 1.0, "Beta (S2-S4)", kPink-3, kBlue+2);
                h1_AoQs2s4_S1S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_sequential_gates[gate], "D", Form("h1_AoQs2s4_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("A/Q (S2-S4) (MHTDC) - S1-S2-S4 Gate: %s", gname.c_str()), 500, 1.0, 4.0, "A/Q (S2-S4)", kPink-3, kBlue+2);
                h1_Z41_S1S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_sequential_gates[gate], "D", Form("h1_Z41_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z41 (MHTDC) - S1-S2-S4 Gate: %s", gname.c_str()), 1000, 0, 100, "Z41", kPink-3, kBlue+2);
                h1_Z42_S1S2S4Gated_mhtdc[gate] = MakeTH1(dir_mhtdc_sequential_gates[gate], "D", Form("h1_Z42_S1S2S4Gated_mhtdc_%s", gname.c_str()), Form("Z42 (MHTDC) - S1-S2-S4 Gate: %s", gname.c_str()), 1000, 0, 100, "Z42", kPink-3, kBlue+2);

                // --- Rates/Ratio ---- 
                h1_ratio_S2_S4_Gates_mhtdc[gate] = MakeTH1(dir_mhtdc_sequential_rates[gate], "I", Form("h1_ratio_S2_S4_Gates_mhtdc_%s", gname.c_str()), Form("Ratio S2 / S4 (*1000) - S1-S2-S4 Gate: %s", gname.c_str()), 1801, 0, 1800, "Time [s]", kRed-3, kBlack);
                h1_integral_S2_Gates_mhtdc[gate] = MakeTH1(dir_mhtdc_sequential_rates[gate], "I", Form("h1_integral_S2_Gates_mhtdc_%s", gname.c_str()), Form("S1S2 PID Integral - S1S2 Gate: %s", gname.c_str()), 1801, 0, 1800, "Time [s]", kRed-3, kBlack);
                h1_integral_S4_Gates_mhtdc[gate] = MakeTH1(dir_mhtdc_sequential_rates[gate], "I", Form("h1_integral_S4_Gates_mhtdc_%s", gname.c_str()), Form("S2S4 PID Integral - S2S4 Gate: %s", gname.c_str()), 1801, 0, 1800, "Time [s]", kRed-3, kBlack);

            }
        }
    }

    // :::: SCI :::::: 
    dir_sci = dir_frs->mkdir("SCI");
    dir_sci_e = dir_sci->mkdir("E");
    dir_sci_x = dir_sci->mkdir("X");
    dir_sci_tof = dir_sci->mkdir("TOF");
    h1_sci_e_11 = MakeTH1(dir_sci_e, "F", "h1_sci_e_11", "SCI 11 E", 4000, 0.0, 4000.0, "SCI 11 E", kPink-3, kBlue+2);
    h1_sci_e_21 = MakeTH1(dir_sci_e, "F", "h1_sci_e_21", "SCI 21 E", 4000, 0.0, 4000.0, "SCI 21 E", kPink-3, kBlue+2);
    h1_sci_e_22 = MakeTH1(dir_sci_e, "F", "h1_sci_e_22", "SCI 22 E", 4000, 0.0, 4000.0, "SCI 22 E", kPink-3, kBlue+2);
    h1_sci_e_31 = MakeTH1(dir_sci_e, "F", "h1_sci_e_31", "SCI 31 E", 4000, 0.0, 4000.0, "SCI 31 E", kPink-3, kBlue+2);
    h1_sci_e_41 = MakeTH1(dir_sci_e, "F", "h1_sci_e_41", "SCI 41 E", 4000, 0.0, 4000.0, "SCI 41 E", kPink-3, kBlue+2);
    h1_sci_e_42 = MakeTH1(dir_sci_e, "F", "h1_sci_e_42", "SCI 42 E", 4000, 0.0, 4000.0, "SCI 42 E", kPink-3, kBlue+2);
    h1_sci_e_43 = MakeTH1(dir_sci_e, "F", "h1_sci_e_43", "SCI 43 E", 4000, 0.0, 4000.0, "SCI 43 E", kPink-3, kBlue+2);
    h1_sci_e_81 = MakeTH1(dir_sci_e, "F", "h1_sci_e_81", "SCI 81 E", 4000, 0.0, 4000.0, "SCI 81 E", kPink-3, kBlue+2);
    h1_sci_x_11 = MakeTH1(dir_sci_x, "F", "h1_sci_x_11", "SCI 11 PosX", 4000, 0.0, 4000.0, "SCI 11 X", kYellow-7, kBlack);
    h1_sci_x_21 = MakeTH1(dir_sci_x, "F", "h1_sci_x_21", "SCI 21 PosX", 4000, 0.0, 4000.0, "SCI 21 X", kYellow-7, kBlack);
    h1_sci_x_22 = MakeTH1(dir_sci_x, "F", "h1_sci_x_22", "SCI 22 PosX", 4000, 0.0, 4000.0, "SCI 22 X", kYellow-7, kBlack);
    h1_sci_x_31 = MakeTH1(dir_sci_x, "F", "h1_sci_x_31", "SCI 31 PosX", 4000, 0.0, 4000.0, "SCI 31 X", kYellow-7, kBlack);
    h1_sci_x_41 = MakeTH1(dir_sci_x, "F", "h1_sci_x_41", "SCI 41 PosX", 4000, 0.0, 4000.0, "SCI 41 X", kYellow-7, kBlack);
    h1_sci_x_42 = MakeTH1(dir_sci_x, "F", "h1_sci_x_42", "SCI 42 PosX", 4000, 0.0, 4000.0, "SCI 42 X", kYellow-7, kBlack);
    h1_sci_x_43 = MakeTH1(dir_sci_x, "F", "h1_sci_x_43", "SCI 43 PosX", 4000, 0.0, 4000.0, "SCI 43 X", kYellow-7, kBlack);
    h1_sci_x_81 = MakeTH1(dir_sci_x, "F", "h1_sci_x_81", "SCI 81 PosX", 4000, 0.0, 4000.0, "SCI 81 X", kYellow-7, kBlack);
    h1_sci_tof_11_21 = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_11_21", "SCI TOF 11 - 21", 4000, 0.0, 200000.0, "SCI TOF 11 - 21", kPink-3, kBlue+2);
    h1_sci_tof_11_21_calib = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_11_21_calib", "SCI TOF 11 - 21 (Calib)", 4000, 0.0, 200000.0, "SCI TOF 11 - 21 (Calib)", kPink-3, kBlue+2);
    h1_sci_tof_21_41 = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_21_41", "SCI TOF 21 - 41", 4000, 0.0, 200000.0, "SCI TOF 21 - 41", kPink-3, kBlue+2);
    h1_sci_tof_21_41_calib = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_21_41_calib", "SCI TOF 21 - 41 (Calib)", 4000, 0.0, 200000.0, "SCI TOF 21 - 41 (Calib)", kPink-3, kBlue+2);
    h1_sci_tof_21_42 = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_21_42", "SCI TOF 21 - 42", 4000, 0.0, 200000.0, "SCI TOF 21 - 42", kPink-3, kBlue+2);
    h1_sci_tof_21_42_calib = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_21_42_calib", "SCI TOF 21 - 42 (Calib)", 4000, 0.0, 200000.0, "SCI TOF 21 - 42 (Calib)", kPink-3, kBlue+2);
    h1_sci_tof_21_81 = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_21_81", "SCI TOF 21 - 81", 4000, 0.0, 200000.0, "SCI TOF 21 - 81", kPink-3, kBlue+2);
    h1_sci_tof_21_81_calib = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_21_81_calib", "SCI TOF 21 - 81 (Calib)", 4000, 0.0, 200000.0, "SCI TOF 21 - 81 (Calib)", kPink-3, kBlue+2);
    h1_sci_tof_22_41 = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_22_41", "SCI TOF 22 - 41", 4000, 0.0, 200000.0, "SCI TOF 22 - 41", kPink-3, kBlue+2);
    h1_sci_tof_22_41_calib = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_22_41_calib", "SCI TOF 22 - 41 (Calib)", 4000, 0.0, 200000.0, "SCI TOF 22 - 41 (Calib)", kPink-3, kBlue+2);
    h1_sci_tof_22_81 = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_22_81", "SCI TOF 22 - 81", 4000, 0.0, 200000.0, "SCI TOF 22 - 81", kPink-3, kBlue+2);
    h1_sci_tof_22_81_calib = MakeTH1(dir_sci_tof, "F", "h1_sci_tof_22_81_calib", "SCI TOF 22 - 81 (Calib)", 4000, 0.0, 200000.0, "SCI TOF 22 - 81 (Calib)", kPink-3, kBlue+2);

    // :::: MUSIC :::: 
    dir_music = dir_frs->mkdir("MUSIC");
    dir_music_e = dir_music->mkdir("E");
    h1_music21_dE = MakeTH1(dir_music_e, "D", "h1_music21_dE", "Energy loss in MUSIC 21", 1000, 0.0, 4000.0, "dE MUSIC 21", kPink-3, kBlue+2);
    h1_music22_dE = MakeTH1(dir_music_e, "D", "h1_music22_dE", "Energy loss in MUSIC 22", 1000, 0.0, 4000.0, "dE MUSIC 22", kPink-3, kBlue+2);
    h1_music21_dE_cor = MakeTH1(dir_music_e, "D", "h1_music21_dE_cor", "Energy loss (cor) in MUSIC 21", 4000, 0.0, 4000.0, "dE (cor) MUSIC 21", kPink-3, kBlue+2);
    h1_music22_dE_cor = MakeTH1(dir_music_e, "D", "h1_music22_dE_cor", "Energy loss (cor) in MUSIC 22", 4000, 0.0, 4000.0, "dE (cor) MUSIC 22", kPink-3, kBlue+2);
    h1_music41_dE = MakeTH1(dir_music_e, "D", "h1_music41_dE", "Energy loss in MUSIC 41", 1000, 0.0, 4000.0, "dE MUSIC 41", kPink-3, kBlue+2);
    h1_music42_dE = MakeTH1(dir_music_e, "D", "h1_music42_dE", "Energy loss in MUSIC 42", 1000, 0.0, 4000.0, "dE MUSIC 42", kPink-3, kBlue+2);
    h1_music41_dE_cor = MakeTH1(dir_music_e, "D", "h1_music41_dE_cor", "Energy loss (cor) in MUSIC 41", 4000, 0.0, 4000.0, "dE (cor) MUSIC 41", kPink-3, kBlue+2);
    h1_music42_dE_cor = MakeTH1(dir_music_e, "D", "h1_music42_dE_cor", "Energy loss (cor) in MUSIC 42", 4000, 0.0, 4000.0, "dE (cor) MUSIC 42", kPink-3, kBlue+2);


    // ::: Monitors :::::
    if (frs_config->plot_monitors)
    {
        dir_monitors = dir_frs->mkdir("Monitors");
        dir_scalers = dir_monitors->mkdir("Scalers");
        dir_rates = dir_monitors->mkdir("Monitors");
        dir_drifts = dir_monitors->mkdir("Drifts");

        // :::::: Scalers ::::::
        h1_tpat = MakeTH1(dir_scalers, "I", "h1_tpat", "Trigger Pattern", 20, 0, 20, "Trigger Pattern", kRed-3, kBlack);
        for (int i = 0; i < 66; i++) hScaler_per_s[i] = MakeTH1(dir_scalers, "D", Form("hScaler_per_s_%s", frs_config->ScalerName(i).c_str()), Form("Scaler %s per 1s ", frs_config->ScalerName(i).c_str()), 1000, 0., 1000., "Time [s]", kCyan, kViolet);
        for (int i = 0; i < 66; i++) hScaler_per_100ms[i] = MakeTH1(dir_scalers, "D", Form("hScaler_per_100ms_%s", frs_config->ScalerName(i).c_str()), Form("Scaler %s per 0.1s", frs_config->ScalerName(i).c_str()), 4000, 0, 400, "Time [100 ms]", kCyan, kViolet);
        for (int i = 0; i < 66; i++) hScaler_per_spill[i] = MakeTH1(dir_scalers, "D", Form("hScaler_per_spill_%s", frs_config->ScalerName(i).c_str()), Form("Scaler %s per spill ", frs_config->ScalerName(i).c_str()), 1000, 0, 1000, "Spill", kCyan, kViolet);

        // :::::: Rates :::::::
        h1_tpc21_rate = MakeTH1(dir_rates, "I", "h1_tpc21_rate", "TPC 21 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
        h1_tpc22_rate = MakeTH1(dir_rates, "I", "h1_tpc22_rate", "TPC 22 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
        h1_tpc23_rate = MakeTH1(dir_rates, "I", "h1_tpc23_rate", "TPC 23 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
        h1_tpc24_rate = MakeTH1(dir_rates, "I", "h1_tpc24_rate", "TPC 24 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
        h1_tpc41_rate = MakeTH1(dir_rates, "I", "h1_tpc41_rate", "TPC 41 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);
        h1_tpc42_rate = MakeTH1(dir_rates, "I", "h1_tpc42_rate", "TPC 42 Rate", 1800, 0, 1800, "Time [2s]", kCyan, kBlue+2);

        // ::::: Drifts :::::::
        h2_Z41_vs_T = MakeTH2(dir_drifts, "D", "h2_Z41_vs_T", "Z41 vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_Z, frs_config->fMax_Z);
        h2_Z41_driftcorr_vs_T = MakeTH2(dir_drifts, "D", "h2_Z41_driftcorr_vs_T", "Z41 DriftCorr vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_Z, frs_config->fMax_Z);
        h2_AoQs2s4_vs_T = MakeTH2(dir_drifts, "D", "h2_AoQs2s4_vs_T", "A/Q (S2-S4) vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ);
        h2_AoQs2s4_driftcorr_vs_T = MakeTH2(dir_drifts, "D", "h2_AoQs2s4_driftcorr_vs_T", "A/Q (S2-S4) DriftCorr vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ);
        h2_Z41_vs_T_mhtdc = MakeTH2(dir_drifts, "D", "h2_Z41_vs_T_mhtdc", "Z41 (MHTDC) vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_Z, frs_config->fMax_Z);
        h2_AoQs2s4_vs_T_mhtdc = MakeTH2(dir_drifts, "D", "h2_AoQs2s4_vs_T_mhtdc", "A/Q (S2-S4) (MHTDC) vs. Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ);
        h2_sci_tof_11_21_vs_T = MakeTH2(dir_drifts, "F", "h2_sci_tof_11_21_vs_T", "TOF 11 - 21 vs. Time [mins]", 500, 0, 10000, 4000, 0.0, 200000.0);
        h2_sci_tof_21_41_vs_T = MakeTH2(dir_drifts, "F", "h2_sci_tof_21_41_vs_T", "TOF 21 - 41 vs. Time [mins]", 500, 0, 10000, 4000, 0.0, 200000.0);
        h2_sci_tof_21_42_vs_T = MakeTH2(dir_drifts, "F", "h2_sci_tof_21_42_vs_T", "TOF 21 - 42 vs. Time [mins]", 500, 0, 10000, 4000, 0.0, 200000.0);
        h2_sci_tof_21_81_vs_T = MakeTH2(dir_drifts, "F", "h2_sci_tof_21_81_vs_T", "TOF 21 - 81 vs. Time [mins]", 500, 0, 10000, 4000, 0.0, 200000.0);
        h2_sci_tof_22_41_vs_T = MakeTH2(dir_drifts, "F", "h2_sci_tof_22_41_vs_T", "TOF 22 - 41 vs. Time [mins]", 500, 0, 10000, 4000, 0.0, 200000.0);
        h2_sci_tof_22_81_vs_T = MakeTH2(dir_drifts, "F", "h2_sci_tof_22_81_vs_T", "TOF 22 - 81 vs. Time [mins]", 500, 0, 10000, 4000, 0.0, 200000.0);
        for (int i = 0; i < 6; i++) h2_tpc_vs_T[i] = MakeTH2(dir_drifts, "D", Form("h2_tpc_vs_T_%i", i), Form("TPC %i X vs. T", i), 500,0, 10000, 200, -100, 100);

    }
    
    passed_s1s2.resize(num_frs_gates);
    std::fill(passed_s1s2.begin(), passed_s1s2.end(), false);
    passed_s2s4.resize(num_frs_gates);
    std::fill(passed_s2s4.begin(), passed_s2s4.end(), false);
    passed_s1s2s4.resize(num_frs_gates);
    std::fill(passed_s1s2s4.begin(), passed_s1s2s4.end(), false);
    count_passed_s1s2.resize(num_frs_gates);
    std::fill(count_passed_s1s2.begin(), count_passed_s1s2.end(), 0);
    count_passed_s2s4 = new int[num_frs_gates];
    for (int i = 0; i < num_frs_gates; i++) count_passed_s2s4[i] = 0;
    count_passed_s1s2s4 = new int[num_frs_gates];
    for (int i = 0; i < num_frs_gates; i++) count_passed_s1s2s4[i] = 0;

    
    return kSUCCESS;

}


void FrsNearlineSpectra::Exec(Option_t* option)
{   
    wr_frs = 0; trav_mus_wr = 0;
    if (hitArray->size() <= 0) return;

    fNEvents++;
    
    FRS_time_mins = 0;
    hitItem = hitArray->at(0); // should only be size=1! check
    wr_frs = hitItem.Get_wr_t();
    if(wr_frs > 0) FRS_time_mins = (wr_frs - exp_config->exp_start_time)/ 60E9;

    // Get the minimum and maximum FRS_time_mins
    if (FRS_time_mins > 0) 
    {
        frs_time_min = std::min(frs_time_min, static_cast<double>(FRS_time_mins));
        frs_time_max = std::max(frs_time_max, static_cast<double>(FRS_time_mins));
    }

    // :::::: No TAC/MHTDC distinction :::::: 
    // ----- 2D ----- 
    if (hitItem.Get_ID_x2() != 0 && hitItem.Get_music41_dE() != 0) h2_dE41_vs_x2->Fill(hitItem.Get_ID_x2(), hitItem.Get_music41_dE());
    if (hitItem.Get_ID_x4() != 0 && hitItem.Get_music41_dE() != 0) h2_dE41_vs_x4->Fill(hitItem.Get_ID_x4(), hitItem.Get_music41_dE());
    if (hitItem.Get_ID_x2() != 0 && hitItem.Get_ID_a2() != 0) h2_x2_vs_a2->Fill(hitItem.Get_ID_x2(), hitItem.Get_ID_a2());
    if (hitItem.Get_ID_y2() != 0 && hitItem.Get_ID_b2() != 0) h2_y2_vs_b2->Fill(hitItem.Get_ID_y2(), hitItem.Get_ID_b2());
    if (hitItem.Get_ID_x4() != 0 && hitItem.Get_ID_a4() != 0) h2_x4_vs_a4->Fill(hitItem.Get_ID_x4(), hitItem.Get_ID_a4());
    if (hitItem.Get_ID_y4() != 0 && hitItem.Get_ID_b4() != 0) h2_y4_vs_b4->Fill(hitItem.Get_ID_y4(), hitItem.Get_ID_b4());
    if (hitItem.Get_ID_x2() != 0 && hitItem.Get_ID_x4() != 0) h2_x2_vs_x4->Fill(hitItem.Get_ID_x2(), hitItem.Get_ID_x4());
    if (hitItem.Get_sci_tof_21_41() != 0 && hitItem.Get_music41_dE() != 0) h2_dE41_vs_ToF_21_41->Fill(hitItem.Get_sci_tof_21_41(), hitItem.Get_music41_dE());

    // --- 1D ---
    h1_x1->Fill(hitItem.Get_ID_x1());
    h1_x2->Fill(hitItem.Get_ID_x2());
    h1_x4->Fill(hitItem.Get_ID_x4());
    h1_a1->Fill(hitItem.Get_ID_a1());
    h1_a2->Fill(hitItem.Get_ID_a2());
    h1_a4->Fill(hitItem.Get_ID_a4());
    h1_y1->Fill(hitItem.Get_ID_y1());
    h1_y2->Fill(hitItem.Get_ID_y2());
    h1_y4->Fill(hitItem.Get_ID_y4());
    h1_b1->Fill(hitItem.Get_ID_b1());
    h1_b2->Fill(hitItem.Get_ID_b2());
    h1_b4->Fill(hitItem.Get_ID_b4());
    if (hitItem.Get_ID_dEdegoQ() > 0) h1_dEdegoQ->Fill(hitItem.Get_ID_dEdegoQ());
    for (int i = 0; i < 2; i++) if (hitItem.Get_ID_rho()[i] > 0) h1_rho[i]->Fill(hitItem.Get_ID_rho()[i]);
    for (int i = 0; i < 2; i++) if (hitItem.Get_ID_brho()[i] > 0) h1_brho[i]->Fill(hitItem.Get_ID_brho()[i]);
    if (hitItem.Get_sci_e_11() > 0) h1_sci_e_11->Fill(hitItem.Get_sci_e_11());
    if (hitItem.Get_sci_e_21() > 0) h1_sci_e_21->Fill(hitItem.Get_sci_e_21());
    if (hitItem.Get_sci_e_22() > 0) h1_sci_e_22->Fill(hitItem.Get_sci_e_22());
    if (hitItem.Get_sci_e_41() > 0) h1_sci_e_41->Fill(hitItem.Get_sci_e_41());
    if (hitItem.Get_sci_e_42() > 0) h1_sci_e_42->Fill(hitItem.Get_sci_e_42());
    if (hitItem.Get_sci_e_43() > 0) h1_sci_e_43->Fill(hitItem.Get_sci_e_43());
    if (hitItem.Get_sci_e_81() > 0) h1_sci_e_81->Fill(hitItem.Get_sci_e_81());
    if (hitItem.Get_sci_x_11() > 0) h1_sci_x_11->Fill(hitItem.Get_sci_x_11());
    if (hitItem.Get_sci_x_21() > 0) h1_sci_x_21->Fill(hitItem.Get_sci_x_21());
    if (hitItem.Get_sci_x_22() > 0) h1_sci_x_22->Fill(hitItem.Get_sci_x_22());
    if (hitItem.Get_sci_x_41() > 0) h1_sci_x_41->Fill(hitItem.Get_sci_x_41());
    if (hitItem.Get_sci_x_42() > 0) h1_sci_x_42->Fill(hitItem.Get_sci_x_42());
    if (hitItem.Get_sci_x_43() > 0) h1_sci_x_43->Fill(hitItem.Get_sci_x_43());
    if (hitItem.Get_sci_x_81() > 0) h1_sci_x_81->Fill(hitItem.Get_sci_x_81());
    if (hitItem.Get_sci_tof_11_21() > 0) h1_sci_tof_11_21->Fill(hitItem.Get_sci_tof_11_21());
    if (hitItem.Get_sci_tof_11_21_calib() > 0) h1_sci_tof_11_21_calib->Fill(hitItem.Get_sci_tof_11_21_calib());
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
    if (hitItem.Get_music21_dE() > 0) h1_music21_dE->Fill(hitItem.Get_music21_dE());
    if (hitItem.Get_music22_dE() > 0) h1_music22_dE->Fill(hitItem.Get_music22_dE());
    if (hitItem.Get_music21_dE_cor() > 0) h1_music21_dE_cor->Fill(hitItem.Get_music21_dE_cor());
    if (hitItem.Get_music22_dE_cor() > 0) h1_music22_dE_cor->Fill(hitItem.Get_music22_dE_cor());
    if (hitItem.Get_music41_dE() > 0) h1_music41_dE->Fill(hitItem.Get_music41_dE());
    if (hitItem.Get_music42_dE() > 0) h1_music42_dE->Fill(hitItem.Get_music42_dE());
    if (hitItem.Get_music41_dE_cor() > 0) h1_music41_dE_cor->Fill(hitItem.Get_music41_dE_cor());
    if (hitItem.Get_music42_dE_cor() > 0) h1_music42_dE_cor->Fill(hitItem.Get_music42_dE_cor());



    // ::::: TAC specific :::::::
    if (frs_config->plot_tac) Process_TAC();

    if (multihitArray->size() <= 0) return;
    multiHitItem = multihitArray->at(0);

    // :::::: MHTDC specific ::::::
    if (frs_config->plot_mhtdc) Process_MHTDC();

    // :::::: Plot monitors ::::::
    if (frs_config->plot_monitors) Process_Monitors();
        
}


void FrsNearlineSpectra::Process_TAC()
{
    // S1S4
    // ----- 2D -----


    // ----- 1D -----
    if (hitItem.Get_ID_beta_s1s2() > 0) h1_beta_s1s2->Fill(hitItem.Get_ID_beta_s1s2()); 
    if (hitItem.Get_ID_AoQ_corr_s1s2() > 0) h1_AoQs1s2_corr->Fill(hitItem.Get_ID_AoQ_corr_s1s2());
    if (hitItem.Get_ID_AoQ_s1s2() > 0) h1_AoQs1s2->Fill(hitItem.Get_ID_AoQ_s1s2());
    if (hitItem.Get_ID_z21() > 0) h1_Z21->Fill(hitItem.Get_ID_z21());
    if (hitItem.Get_ID_z22() > 0) h1_Z22->Fill(hitItem.Get_ID_z22());

    // S2S4
    // ----- 2D -----
    if (hitItem.Get_ID_AoQ_s2s4() > 0 && hitItem.Get_ID_z41() > 0) h2_Z41_vs_AoQs2s4->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_z41());
    if (hitItem.Get_ID_AoQs2s4_driftcorr() > 0 && hitItem.Get_ID_z41_driftcorr() > 0) h2_Z41_vs_AoQs2s4_driftcorr->Fill(hitItem.Get_ID_AoQs2s4_driftcorr(), hitItem.Get_ID_z41_driftcorr());
    if (hitItem.Get_ID_AoQ_corr_s2s4() > 0 && hitItem.Get_ID_z41() > 0) h2_Z41_vs_AoQs2s4_corr->Fill(hitItem.Get_ID_AoQ_corr_s2s4(), hitItem.Get_ID_z41());
    if (hitItem.Get_ID_z41() > 0 && hitItem.Get_ID_z42() > 0) h2_Z41_vs_Z42->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_z42());
    if (TMath::Abs(hitItem.Get_ID_z41() - hitItem.Get_ID_z42()) < 0.4)
    {
        h2_Z41_vs_AoQs2s4_Zsame->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_z41());
        h2_x4_vs_AoQs2s4_Zsame->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x4());
        h2_x2_vs_AoQs2s4_Zsame->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x2());
    }
    if (hitItem.Get_ID_AoQ_s2s4() > 0 && hitItem.Get_ID_x2() > -100 && hitItem.Get_ID_x2() < 100) h2_x2_vs_AoQs2s4->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x2());
    if (hitItem.Get_ID_AoQ_s2s4() > 0 && hitItem.Get_ID_x4() > -100 && hitItem.Get_ID_x4() < 100) h2_x4_vs_AoQs2s4->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_x4());
    if (hitItem.Get_ID_z41() > 0 && hitItem.Get_ID_dEdegoQ() != 0) h2_dEdegoQ_vs_Z41->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdegoQ());
    if (hitItem.Get_ID_z41() > 0 && hitItem.Get_ID_dEdeg_z41() != 0) h2_dEdegZ41_vs_Z41->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdeg_z41());
    if (hitItem.Get_ID_AoQ_s2s4() != 0 && hitItem.Get_ID_a2() != 0) h2_a2_vs_AoQs2s4->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_a2());
    if (hitItem.Get_ID_AoQ_s2s4() != 0 && hitItem.Get_ID_a4() != 0) h2_a4_vs_AoQs2s4->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_ID_a4());
    if (hitItem.Get_ID_z41() != 0 && hitItem.Get_music42_dE() != 0) h2_Z41_vs_dE42->Fill(hitItem.Get_ID_z41(), hitItem.Get_music42_dE());
    if (hitItem.Get_ID_AoQ_s2s4() != 0 && hitItem.Get_sci_e_41() != 0) h2_SC41dE_vs_AoQs2s4->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_sci_e_41());
    if (hitItem.Get_ID_AoQ_s2s4() != 0 && hitItem.Get_sci_e_42() != 0) h2_SC42dE_vs_AoQs2s4->Fill(hitItem.Get_ID_AoQ_s2s4(), hitItem.Get_sci_e_42());
    if (hitItem.Get_ID_z41() != 0 && hitItem.Get_sci_e_41() != 0) h2_SC41dE_vs_Z41->Fill(hitItem.Get_ID_z41(), hitItem.Get_sci_e_41());
    if (hitItem.Get_ID_z41() != 0 && hitItem.Get_sci_e_42() != 0) h2_SC42dE_vs_Z41->Fill(hitItem.Get_ID_z41(), hitItem.Get_sci_e_42());
    if (hitItem.Get_ID_z41() != 0 && hitItem.Get_ID_x2() != 0) h2_x2_vs_Z41->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_x2());
    if (hitItem.Get_ID_z41() != 0 && hitItem.Get_ID_x4() != 0) h2_x4_vs_Z41->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_x4());
    if (hitItem.Get_ID_z41() != 0 && hitItem.Get_sci_e_21() != 0) h2_Z41_vs_Sc21E->Fill(hitItem.Get_ID_z41(), hitItem.Get_sci_e_21());

    // ----- 1D -----
    if (hitItem.Get_ID_z41() > 0) h1_Z41->Fill(hitItem.Get_ID_z41());
    if (hitItem.Get_ID_z41_driftcorr() > 0) h1_Z41_driftcorr->Fill(hitItem.Get_ID_z41_driftcorr());
    if (hitItem.Get_ID_z42() > 0) h1_Z42->Fill(hitItem.Get_ID_z42());
    if (hitItem.Get_ID_z43() > 0) h1_Z43->Fill(hitItem.Get_ID_z43());
    if (hitItem.Get_ID_AoQ_s2s4() > 0) h1_AoQs2s4->Fill(hitItem.Get_ID_AoQ_s2s4());
    if (hitItem.Get_ID_AoQs2s4_driftcorr() > 0) h1_AoQs2s4_driftcorr->Fill(hitItem.Get_ID_AoQs2s4_driftcorr());
    if (hitItem.Get_ID_AoQ_corr_s2s4() > 0) h1_AoQs2s4_corr->Fill(hitItem.Get_ID_AoQ_corr_s2s4());
    if (hitItem.Get_ID_beta_s2s4() > 0) h1_beta_s2s4->Fill(hitItem.Get_ID_beta_s2s4()); 
    if (hitItem.Get_ID_dEdeg_z41() > 0) h1_dEdegZ41->Fill(hitItem.Get_ID_dEdeg_z41());

    if (num_frs_gates > 0)
    {
        for (int gate = 0; gate < num_frs_gates; gate++)
        {   
            // S2S4
            if (FrsGates[gate]->PassedS2S4(hitItem.Get_ID_z41(), hitItem.Get_ID_z42(), hitItem.Get_ID_x2(), hitItem.Get_ID_x4(), hitItem.Get_ID_AoQ_corr_s2s4(), hitItem.Get_ID_dEdeg_z41(), hitItem.Get_sci_e_42()))
            {
                // ----- 2D -----
                h2_Z41_vs_AoQs2s4_S2S4Gated[gate]->Fill(hitItem.Get_ID_AoQ_corr_s2s4(), hitItem.Get_ID_z41());
                h2_Z41_vs_Z42_S2S4Gated[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_z42());
                h2_x2_vs_AoQs2s4_S2S4Gated[gate]->Fill(hitItem.Get_ID_AoQ_corr_s2s4(), hitItem.Get_ID_x2());
                h2_x4_vs_AoQs2s4_S2S4Gated[gate]->Fill(hitItem.Get_ID_AoQ_corr_s2s4(), hitItem.Get_ID_x4());
                h2_dEdegoQ_vs_Z41_S2S4Gated[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdegoQ());
                h2_dEdegZ41_vs_Z41_S2S4Gated[gate]->Fill(hitItem.Get_ID_z41(), hitItem.Get_ID_dEdeg_z41());

                // ----- 1D------
                h1_beta_s2s4_S2S4Gated[gate]->Fill(hitItem.Get_ID_beta_s2s4());
                h1_AoQs2s4_S2S4Gated[gate]->Fill(hitItem.Get_ID_AoQ_corr_s2s4());
                h1_Z41_S2S4Gated[gate]->Fill(hitItem.Get_ID_z41());
                h1_Z42_S2S4Gated[gate]->Fill(hitItem.Get_ID_z42());
            }
        }
    }
}


void FrsNearlineSpectra::Process_MHTDC()
{
    int a = 0;

    std::vector<Float_t> beta_s1s2_mhtdc = multiHitItem.Get_ID_beta_s1s2_mhtdc();
    std::vector<Float_t> beta_s2s4_mhtdc = multiHitItem.Get_ID_beta_s2s4_mhtdc();
    std::vector<Float_t> AoQ_s1s2_mhtdc = multiHitItem.Get_ID_AoQ_s1s2_mhtdc();
    std::vector<Float_t> AoQ_s2s4_mhtdc = multiHitItem.Get_ID_AoQ_s2s4_mhtdc();
    std::vector<Float_t> AoQ_corr_s1s2_mhtdc = multiHitItem.Get_ID_AoQ_corr_s1s2_mhtdc();
    std::vector<Float_t> AoQ_corr_s2s4_mhtdc = multiHitItem.Get_ID_AoQ_corr_s2s4_mhtdc();
    std::vector<Float_t> z21_mhtdc = multiHitItem.Get_ID_z21_mhtdc();
    std::vector<Float_t> z22_mhtdc = multiHitItem.Get_ID_z22_mhtdc();
    std::vector<Float_t> z41_mhtdc = multiHitItem.Get_ID_z41_mhtdc();
    std::vector<Float_t> z42_mhtdc = multiHitItem.Get_ID_z42_mhtdc();
    std::vector<Float_t> z43_mhtdc = multiHitItem.Get_ID_z43_mhtdc();
    std::vector<Float_t> dEdegoQ_mhtdc = multiHitItem.Get_ID_dEdegoQ_mhtdc();
    std::vector<Float_t> dEdeg_z41_mhtdc = multiHitItem.Get_ID_dEdeg_z41_mhtdc();

    // ::::: S1S2 Loop ::::: 
    for (int i = 0; i < AoQ_s1s2_mhtdc.size(); i++)
    {   
        // ---- 2D ------
        if (z21_mhtdc.at(i) > 0 && AoQ_s1s2_mhtdc.at(i) > 0) h2_Z21_vs_AoQs1s2_mhtdc->Fill(AoQ_s1s2_mhtdc.at(i), z21_mhtdc.at(i));
        if (z21_mhtdc.at(i) > 0 && AoQ_corr_s1s2_mhtdc.at(i) > 0) h2_Z21_vs_AoQs1s2_corr_mhtdc->Fill(AoQ_corr_s1s2_mhtdc.at(i), z21_mhtdc.at(i));
        if (z21_mhtdc.at(i) > 0 && z22_mhtdc.at(i) > 0) h2_Z21_vs_Z22_mhtdc->Fill(z21_mhtdc.at(i), z22_mhtdc.at(i));
        if (AoQ_corr_s1s2_mhtdc.at(i) > 0) h2_x2_vs_AoQs1s2_mhtdc->Fill(AoQ_corr_s1s2_mhtdc.at(i), hitItem.Get_ID_x2());
        if (AoQ_corr_s1s2_mhtdc.at(i) > 0) h2_a2_vs_AoQs1s2_mhtdc->Fill(AoQ_corr_s1s2_mhtdc.at(i), hitItem.Get_ID_a2());
        if (z21_mhtdc.at(i) > 0) h2_x2_vs_Z21_mhtdc->Fill(z21_mhtdc.at(i), hitItem.Get_ID_x2());
        if (z21_mhtdc.at(i) > 0 && hitItem.Get_sci_e_21()) h2_Z21_vs_Sc21E_mhtdc->Fill(z21_mhtdc.at(i), hitItem.Get_sci_e_21());
        if (z21_mhtdc.at(i) > 0 && hitItem.Get_music21_dE() > 0) h2_Z21_vs_dE21_mhtdc->Fill(z21_mhtdc.at(i), hitItem.Get_music21_dE());

        // ---- 1D ------
        if (beta_s1s2_mhtdc.at(i) > 0.2) h1_beta_s1s2_mhtdc->Fill(beta_s1s2_mhtdc.at(i)); // 0.2 for now
        if (AoQ_s1s2_mhtdc.at(i) > 0) h1_AoQs1s2_mhtdc->Fill(AoQ_s1s2_mhtdc.at(i));
        if (AoQ_corr_s1s2_mhtdc.at(i) > 0) h1_AoQs1s2_corr_mhtdc->Fill(AoQ_corr_s1s2_mhtdc.at(i));
        if (z21_mhtdc.at(i) > 10) h1_Z21_mhtdc->Fill(z21_mhtdc.at(i));
        if (z22_mhtdc.at(i) > 0) h1_Z22_mhtdc->Fill(z22_mhtdc.at(i));


        if (num_frs_gates > 0)
        {
            for (int gate = 0; gate < num_frs_gates; gate++)
            {    
                if (FrsGates[gate]->PassedS1S2(z21_mhtdc.at(i), hitItem.Get_ID_x2(), AoQ_s1s2_mhtdc.at(i)))
                {
                    if (!passed_s1s2[gate])
                    {
                        passed_s1s2[gate] = true;
                        count_passed_s1s2[gate]++;
                    }

                    // S1S2 Histograms where S1S2 Gates are passed
                    // ---- 2D -----
                    if (z21_mhtdc.at(i) > 0 && AoQ_corr_s1s2_mhtdc.at(i) > 0) h2_Z21_vs_AoQs1s2_S1S2Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(i), z21_mhtdc.at(i));
                    if (AoQ_corr_s1s2_mhtdc.at(i) > 0) h2_x1_vs_AoQs1s2_S1S2Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(i), hitItem.Get_ID_x1());
                    if (AoQ_corr_s1s2_mhtdc.at(i) > 0) h2_x2_vs_AoQs1s2_S1S2Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(i), hitItem.Get_ID_x2());

                    // ---- 1D -----
                    if (beta_s1s2_mhtdc.at(i) > 0) h1_beta_s1s2_S1S2Gated_mhtdc[gate]->Fill(beta_s1s2_mhtdc.at(i));
                    if (AoQ_corr_s1s2_mhtdc.at(i) > 0) h1_AoQs1s2_S1S2Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(i));
                    if (z21_mhtdc.at(i) > 0) h1_Z21_S1S2Gated_mhtdc[gate]->Fill(z21_mhtdc.at(i));
                }
            }
        }

    }    

    // ::::: S2S4 Loop ::::: 
    for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
    {
        if (a == 0) multihit_counter++;
        
        // ---- 2D ------
        if(AoQ_s2s4_mhtdc.at(i) > 0 && z41_mhtdc.at(i) > 0) h2_Z41_vs_AoQs2s4_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
        if(AoQ_corr_s2s4_mhtdc.at(i) > 0 && z41_mhtdc.at(i) > 0) h2_Z41_vs_AoQs2s4_corr_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
        if(z41_mhtdc.at(i) > 0 && z42_mhtdc.at(i) > 0) h2_Z41_vs_Z42_mhtdc->Fill(z41_mhtdc.at(i), z42_mhtdc.at(i));
        if(TMath::Abs(z41_mhtdc.at(i) - z42_mhtdc.at(i)) < 0.4)
        {
            h2_Z41_vs_AoQs2s4_Zsame_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
            h2_x4_vs_AoQs2s4_Zsame_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
            h2_x2_vs_AoQs2s4_Zsame_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
        }
        if(AoQ_corr_s2s4_mhtdc.at(i) > 0 && hitItem.Get_ID_x2() > -100 && hitItem.Get_ID_x2() < 100)  h2_x2_vs_AoQs2s4_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
        if(AoQ_corr_s2s4_mhtdc.at(i) > 0 && hitItem.Get_ID_x4() > -100 && hitItem.Get_ID_x4() < 100)  h2_x4_vs_AoQs2s4_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
        if(z41_mhtdc.at(i) > 0 && dEdegoQ_mhtdc.at(i) != 0) h2_dEdegoQ_vs_Z41_mhtdc->Fill(z41_mhtdc.at(i), dEdegoQ_mhtdc.at(i));
        if(z41_mhtdc.at(i) > 0 && dEdeg_z41_mhtdc.at(i) != 0) h2_dEdegZ41_vs_Z41_mhtdc->Fill(z41_mhtdc.at(i), dEdeg_z41_mhtdc.at(i));
        if(AoQ_corr_s2s4_mhtdc.at(i) != 0 && hitItem.Get_ID_a2() != 0) h2_a2_vs_AoQs2s4_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_a2());
        if(AoQ_corr_s2s4_mhtdc.at(i) != 0 && hitItem.Get_ID_a4() != 0) h2_a4_vs_AoQs2s4_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_a4());
        if(z41_mhtdc.at(i) != 0 && hitItem.Get_music42_dE()  != 0) h2_Z41_vs_dE42_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_music42_dE());
        if(z41_mhtdc.at(i) != 0 && hitItem.Get_sci_e_21() != 0) h2_Z41_vs_Sc21E_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_sci_e_21());
        h2_x2_vs_Z41_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_ID_x2());
        h2_x4_vs_Z41_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_ID_x4());
        if (AoQ_corr_s2s4_mhtdc.at(i) != 0 && hitItem.Get_sci_e_41() != 0) h2_SC41dE_vs_AoQs2s4_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_sci_e_41());
        if (AoQ_corr_s2s4_mhtdc.at(i) != 0 && hitItem.Get_sci_e_42() != 0) h2_SC42dE_vs_AoQs2s4_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_sci_e_42());
        if (z41_mhtdc.at(i) != 0 && hitItem.Get_sci_e_41() != 0) h2_SC41dE_vs_Z41_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_sci_e_41());
        if (z41_mhtdc.at(i) != 0 && hitItem.Get_sci_e_42() != 0) h2_SC42dE_vs_Z41_mhtdc->Fill(z41_mhtdc.at(i), hitItem.Get_sci_e_42()); 
        for (int j = 0; j < z21_mhtdc.size(); j++)
        {
            if (z21_mhtdc.at(j) > 0 && z41_mhtdc.at(i) > 0) h2_Z21_vs_Z41_mhtdc->Fill(z21_mhtdc.at(j), z41_mhtdc.at(i)); 
        }


        // ------ 1D ------ 
        if (beta_s2s4_mhtdc.at(i) > 0) h1_beta_s2s4_mhtdc->Fill(beta_s2s4_mhtdc.at(i));
        if (AoQ_s2s4_mhtdc.at(i) > 0) h1_AoQs2s4_mhtdc->Fill(AoQ_s2s4_mhtdc.at(i));
        if (AoQ_corr_s2s4_mhtdc.at(i) > 0) h1_AoQs2s4_corr_mhtdc->Fill(AoQ_corr_s2s4_mhtdc.at(i));
        if (z41_mhtdc.at(i) > 0) h1_Z41_mhtdc->Fill(z41_mhtdc.at(i));
        if (z42_mhtdc.at(i) > 0) h1_Z42_mhtdc->Fill(z42_mhtdc.at(i));
        if (z43_mhtdc.at(i) > 0) h1_Z43_mhtdc->Fill(z43_mhtdc.at(i));
        if (dEdeg_z41_mhtdc.at(i) > 0) h1_dEdegZ41_mhtdc->Fill(dEdeg_z41_mhtdc.at(i));

        
        // Gated
        if (num_frs_gates > 0)
        {
            for (int gate = 0; gate < num_frs_gates; gate++)
            {
                if (passed_s1s2[gate])
                {
                    // S2S4 Histograms where S1S2 Gates are passed
                    // ---- 2D ----
                    h2_Z41_vs_AoQs2s4_S1S2Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
                    h2_Z41_vs_Z42_S1S2Gated_mhtdc[gate]->Fill(z41_mhtdc.at(i), z42_mhtdc.at(i));
                    h2_x2_vs_AoQs2s4_S1S2Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
                    h2_x4_vs_AoQs2s4_S1S2Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
                    h2_dEdegZ41_vs_Z41_S1S2Gated_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdeg_z41_mhtdc.at(i));
                    
                    // ---- 1D -----
                    if (beta_s2s4_mhtdc.at(i) > 0.2) h1_beta_s2s4_S1S2Gated_mhtdc[gate]->Fill(beta_s2s4_mhtdc.at(i));
                    if (AoQ_corr_s2s4_mhtdc.at(i) > 0) h1_AoQs2s4_S1S2Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i));
                    if (z41_mhtdc.at(i) > 0) h1_Z41_S1S2Gated_mhtdc[gate]->Fill(z41_mhtdc.at(i));
                    if (z42_mhtdc.at(i) > 0) h1_Z42_S1S2Gated_mhtdc[gate]->Fill(z42_mhtdc.at(i));
                }
        
                if (FrsGates[gate]->PassedS2S4(z41_mhtdc.at(i), z42_mhtdc.at(i), hitItem.Get_ID_x2(), hitItem.Get_ID_x4(), AoQ_corr_s2s4_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), hitItem.Get_sci_e_42()))
                {
                    // S2S4 Histograms where S2S4 Gates are passed
                    // ---- 2D -----
                    if (AoQ_corr_s2s4_mhtdc.at(i) > 0 && z41_mhtdc.at(i) > 0) h2_Z41_vs_AoQs2s4_S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
                    if (z41_mhtdc.at(i) > 0 && z42_mhtdc.at(i) > 0) h2_Z41_vs_Z42_S2S4Gated_mhtdc[gate]->Fill(z41_mhtdc.at(i), z42_mhtdc.at(i));
                    if (AoQ_corr_s2s4_mhtdc.at(i) > 0) h2_x2_vs_AoQs2s4_S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
                    if (AoQ_corr_s2s4_mhtdc.at(i) > 0) h2_x4_vs_AoQs2s4_S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
                    if (z41_mhtdc.at(i) > 0 && dEdeg_z41_mhtdc.at(i) > 0) h2_dEdegZ41_vs_Z41_S2S4Gated_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdeg_z41_mhtdc.at(i));

                    // ---- 1D -----
                    if (beta_s2s4_mhtdc.at(i) > 0.2) h1_beta_s2s4_S2S4Gated_mhtdc[gate]->Fill(beta_s2s4_mhtdc.at(i));
                    if (AoQ_corr_s2s4_mhtdc.at(i) > 0) h1_AoQs2s4_S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i));
                    if (z41_mhtdc.at(i) > 0) h1_Z41_S2S4Gated_mhtdc[gate]->Fill(z41_mhtdc.at(i));
                    if (z42_mhtdc.at(i) > 0) h1_Z42_S2S4Gated_mhtdc[gate]->Fill(z42_mhtdc.at(i));

                    
                    if (!passed_s2s4[gate])
                   {
                        
                       if (passed_s1s2[gate])
                       {
                            // S1S2 Histograms where S2S4 Gates are passed
                            for (int j = 0; j < AoQ_corr_s1s2_mhtdc.size(); j++)
                            {
                                // ---- 2D -----
                                if (z21_mhtdc.at(j) > 0 && AoQ_corr_s1s2_mhtdc.at(j) > 0) h2_Z21_vs_AoQs1s2_S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(j), z21_mhtdc.at(j));
                                if (AoQ_corr_s1s2_mhtdc.at(j) > 0) h2_x1_vs_AoQs1s2_S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(j), hitItem.Get_ID_x1());
                                if (AoQ_corr_s1s2_mhtdc.at(j) > 0) h2_x2_vs_AoQs1s2_S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(j), hitItem.Get_ID_x2());

                                // ---- 1D -----
                                if (beta_s1s2_mhtdc.at(j) > 0) h1_beta_s1s2_S2S4Gated_mhtdc[gate]->Fill(beta_s1s2_mhtdc.at(j));
                                if (AoQ_corr_s1s2_mhtdc.at(j) > 0) h1_AoQs1s2_S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(j));
                                if (z21_mhtdc.at(j) > 0) h1_Z21_S2S4Gated_mhtdc[gate]->Fill(z21_mhtdc.at(j));
                            }
                            
                            passed_s1s2s4[gate] = true;
                            count_passed_s1s2s4[gate]++;
                        }
                        

                        passed_s2s4[gate] = true;
                        count_passed_s2s4[gate]++;
                    }
                }   
            }
        } // FRS Gates > 0
        
    } // S2S4 Loop


    // Anything require full sequence
    if (num_frs_gates > 0)
    {
        for (int gate = 0; gate < num_frs_gates; gate++)
        {
            if (passed_s1s2[gate] && passed_s2s4[gate]) // if anything passes, plot all? fill a new "pass vector" and fill? dunno
            {
                for (int i = 0; i < AoQ_corr_s1s2_mhtdc.size(); i++)
                {
                    // ---- 2D -----
                    if (z21_mhtdc.at(i) > 0 && AoQ_corr_s1s2_mhtdc.at(i) > 0) h2_Z21_vs_AoQs1s2_S1S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(i), z21_mhtdc.at(i));
                    if (AoQ_corr_s1s2_mhtdc.at(i) > 0) h2_x1_vs_AoQs1s2_S1S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(i), hitItem.Get_ID_x1());
                    if (AoQ_corr_s1s2_mhtdc.at(i) > 0) h2_x2_vs_AoQs1s2_S1S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(i), hitItem.Get_ID_x2());

                    // ---- 1D -----
                    if (beta_s1s2_mhtdc.at(i) > 0) h1_beta_s1s2_S1S2S4Gated_mhtdc[gate]->Fill(beta_s1s2_mhtdc.at(i));
                    if (AoQ_corr_s1s2_mhtdc.at(i) > 0) h1_AoQs1s2_S1S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s1s2_mhtdc.at(i));
                    if (z21_mhtdc.at(i) > 0) h1_Z21_S1S2S4Gated_mhtdc[gate]->Fill(z21_mhtdc.at(i));
                }

                for (int i = 0; i < AoQ_corr_s2s4_mhtdc.size(); i++)
                {
                    // ----- 2D -----
                    if (AoQ_corr_s2s4_mhtdc.at(i) > 0 && z41_mhtdc.at(i) > 0) h2_Z41_vs_AoQs2s4_S1S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i), z41_mhtdc.at(i));
                    if (z41_mhtdc.at(i) > 0 && z41_mhtdc.at(i) > 0) h2_Z41_vs_Z42_S1S2S4Gated_mhtdc[gate]->Fill(z41_mhtdc.at(i), z42_mhtdc.at(i));
                    if (AoQ_corr_s2s4_mhtdc.at(i) > 0) h2_x2_vs_AoQs2s4_S1S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_x2());
                    if (AoQ_corr_s2s4_mhtdc.at(i) > 0) h2_x4_vs_AoQs2s4_S1S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i), hitItem.Get_ID_x4());
                    if (z41_mhtdc.at(i) > 0 && dEdeg_z41_mhtdc.at(i) > 0) h2_dEdegZ41_vs_Z41_S1S2S4Gated_mhtdc[gate]->Fill(z41_mhtdc.at(i), dEdeg_z41_mhtdc.at(i));

                    // ---- 1D -----
                    if (beta_s2s4_mhtdc.at(i) > 0.2) h1_beta_s2s4_S2S4Gated_mhtdc[gate]->Fill(beta_s2s4_mhtdc.at(i));
                    if (AoQ_corr_s2s4_mhtdc.at(i) > 0) h1_AoQs2s4_S2S4Gated_mhtdc[gate]->Fill(AoQ_corr_s2s4_mhtdc.at(i));
                    if (z41_mhtdc.at(i) > 0) h1_Z41_S2S4Gated_mhtdc[gate]->Fill(z41_mhtdc.at(i));
                    if (z42_mhtdc.at(i) > 0) h1_Z42_S2S4Gated_mhtdc[gate]->Fill(z42_mhtdc.at(i));

                    // for (int j = 0; j < AoQ_corr_s1s2_mhtdc.size(); j++)
                    // {
                    //     if (z21_mhtdc.at(i) > 0 && z41_mhtdc.at(i) > 0) h2_Z21_vs_Z41_S1S2S4Gated_mhtdc[gate]->Fill();
                    // }
                }
            }
        }
    }
}


void FrsNearlineSpectra::Process_Monitors()
{
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
    if (hitItem.Get_ID_z41() > 0 && FRS_time_mins > 0) h2_Z41_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_z41());
    if (hitItem.Get_ID_z41_driftcorr() > 0 && FRS_time_mins > 0) h2_Z41_driftcorr_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_z41_driftcorr());
    if (hitItem.Get_ID_AoQ_s2s4() > 0 && FRS_time_mins > 0) h2_AoQs2s4_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_AoQ_s2s4());
    if (hitItem.Get_ID_AoQs2s4_driftcorr() > 0 && FRS_time_mins > 0) h2_AoQs2s4_driftcorr_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_AoQs2s4_driftcorr());
    //if (z41_mhtdc.at(i) > 0 && FRS_time_mins > 0) h2_Z1_vs_T_mhtdc->Fill(FRS_time_mins, z41_mhtdc.at(i));
    //if (AoQ_s2s4_mhtdc.at(i) > 0 && FRS_time_mins > 0) h2_AoQ_vs_T_mhtdc->Fill(FRS_time_mins, AoQ_s2s4_mhtdc.at(i));
    h2_sci_tof_11_21_vs_T->Fill(FRS_time_mins, hitItem.Get_sci_tof_11_21()); // calib??
    h2_sci_tof_21_41_vs_T->Fill(FRS_time_mins, hitItem.Get_sci_tof_21_41()); // calib??
    h2_sci_tof_21_42_vs_T->Fill(FRS_time_mins, hitItem.Get_sci_tof_21_42()); // calib??
    h2_sci_tof_21_81_vs_T->Fill(FRS_time_mins, hitItem.Get_sci_tof_21_81()); // calib??
    h2_sci_tof_22_41_vs_T->Fill(FRS_time_mins, hitItem.Get_sci_tof_22_41()); // calib??
    h2_sci_tof_22_81_vs_T->Fill(FRS_time_mins, hitItem.Get_sci_tof_22_81()); // calib??

    
    // CEJ:: Gate integrals/ratios... 


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

    double wr_diff_s = (wr_frs - saved_wr_frs) / 1e9;

    if (wr_diff_s > 1) 
    {
        if (saved_wr_frs != 0 && wr_diff_s < 2)
        {
            for (int gate = 0; gate < num_frs_gates; gate++)
            {
                h1_integral_S2_Gates_mhtdc[gate]->SetBinContent(ratio_running_count, count_passed_s1s2[gate]);
                h1_integral_S4_Gates_mhtdc[gate]->SetBinContent(ratio_running_count, count_passed_s1s2s4[gate]);
                // h1_integral_S4_Gates_mhtdc[gate]->SetBinContent(ratio_running_count, count_passed_s2s4[gate]);
                if (count_passed_s1s2s4[gate] == 0) continue;
                // if (count_passed_s2s4[gate] == 0) continue;
                double pid_ratio = 1000 * count_passed_s1s2[gate] / count_passed_s1s2s4[gate];
                // double pid_ratio = 1000 * count_passed_s1s2[gate] / count_passed_s2s4[gate];
                h1_ratio_S2_S4_Gates_mhtdc[gate]->SetBinContent(ratio_running_count, pid_ratio);
            }
        }

    
        saved_wr_frs = wr_frs;
        ratio_running_count++;

        for (int gate = 0; gate < num_frs_gates; gate++)
        {
            count_passed_s1s2[gate] = 0;
            count_passed_s1s2s4[gate] = 0;
            // count_passed_s2s4[gate] = 0;
        }
           
    }
}


void FrsNearlineSpectra::FinishEvent()
{
    std::fill(passed_s1s2.begin(), passed_s1s2.end(), 0);
    std::fill(passed_s1s2s4.begin(), passed_s1s2s4.end(), 0);
    std::fill(passed_s2s4.begin(), passed_s2s4.end(), 0);    
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
