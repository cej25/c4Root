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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25.11.24                                     *
 ******************************************************************************/

// ::: Note::: No canvases in Nearline Tasks please :::

#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairTask.h"

#include "LisaFrsCorrelations.h"
#include "FrsHitData.h"
#include "LisaCalData.h"
#include "TLisaConfiguration.h"     // not here
#include "c4Logger.h"
#include "TFile.h"
#include "THttpServer.h"
#include "TCanvas.h"

// c4
#include "EventHeader.h"
#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TCanvas.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <string>
#include "TColor.h"
#include "TStyle.h"

LisaFrsCorrelations::LisaFrsCorrelations() 
    : LisaFrsCorrelations("LisaFrsCorrelations")
{

}

LisaFrsCorrelations::LisaFrsCorrelations(std::vector<FrsGate*> fg)
    : LisaFrsCorrelations("LisaFrsCorrelations")
{
    FrsGates = fg;
}

LisaFrsCorrelations::LisaFrsCorrelations(std::vector<LisaGate*> lg)
    : LisaFrsCorrelations("LisaFrsCorrelations")
{
    for (auto & gate : lg) 
    {
        if (gate->GetType() == "energy") febex_gates.emplace_back(gate); 
        else if (gate->GetType() == "energy_mwd") mwd_gates.emplace_back(gate);
    }
}

LisaFrsCorrelations::LisaFrsCorrelations(std::vector<FrsGate*> fg, std::vector<LisaGate*> lg)
    : LisaFrsCorrelations("LisaFrsCorrelations")
{
    FrsGates = fg;
    std::cout << "SIZE OF FRS GATES: " << FrsGates.size() << std::endl;
    for (int i = 0; i < FrsGates.size(); i++)
    {
        std::cout << FrsGates.at(i)->GetName() << std::endl;
    }
    
    std::cout << "SIZE OF LISA FEBEX+MWD GATES: " << lg.size() << std::endl;
    for (int i = 0; i < lg.size(); i++)
    {
        std::cout << lg.at(i)->GetName() << std::endl;
    }

    for (auto & gate : lg) 
    {
        if (gate->GetType() == "energy") febex_gates.emplace_back(gate); 
        else if (gate->GetType() == "energy_mwd") mwd_gates.emplace_back(gate);
    }
}


LisaFrsCorrelations::LisaFrsCorrelations(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   header(nullptr)
    ,   lisaCalArray(nullptr)
    ,   frsHitArray(nullptr)
    ,   fNEvents(0)
    ,   multihitArray(nullptr)

{
    lisa_config = TLisaConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
}

LisaFrsCorrelations::~LisaFrsCorrelations()
{
    c4LOG(info, "Destroyed LisaFrsCorrelationsProperly.");
}

InitStatus LisaFrsCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = mgr->InitObjectAs<decltype(header)>("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found!");

    lisaCalArray = mgr->InitObjectAs<decltype(lisaCalArray)>("LisaCalData");
    c4LOG_IF(fatal, !lisaCalArray, "Branch LisaCalData not found!");
    frsHitArray = mgr->InitObjectAs<decltype(frsHitArray)>("FrsHitData");
    c4LOG_IF(fatal, !frsHitArray, "Branch FrsHitData not found!");

    multihitArray = mgr->InitObjectAs<decltype(multihitArray)>("FrsMultiHitData");
    c4LOG_IF(fatal, !multihitArray, "Branch FrsMultiHitData not found!");

    layer_number = lisa_config->NLayers();
    xmax = lisa_config->XMax();
    ymax = lisa_config->YMax();
    auto const & detector_mapping = lisa_config->Mapping();

    gate_number = febex_gates.size();
    mwd_gate_number = mwd_gates.size();

    // std::cout << "gate number:: " << gate_number << std::endl;
    // std::cout << "mwd gate number:: " << mwd_gate_number << std::endl;
    // std::cout << "frs gate number:: " << FrsGates.size() << std::endl;

    // Ranges from MUSICs
    int min_21 = frs_config->fMin_dE_music21;
    int max_21 = frs_config->fMax_dE_music21;
    int bin_21 = (max_21 - min_21)/40;
    int min_41 = frs_config->fMin_dE_music41;
    int max_41 = frs_config->fMax_dE_music41;
    int bin_41 = (max_41 - min_41)/40;
    int min_42 = frs_config->fMin_dE_music42;
    int max_42 = frs_config->fMax_dE_music42;
    int bin_42 = (max_42 - min_42)/40;
    //.............

    FairRootManager::Instance()->GetOutFile()->cd();

    excluded = lisa_config->GetExcludedChannels();

    dir_corr = gDirectory->mkdir("Correlations");
    dir_time = dir_corr->mkdir("Time");

    dir_position = dir_corr->mkdir("Position");

    dir_energy = dir_corr->mkdir("Energy_LISA_vs_MUSIC");
    dir_febex = dir_energy->mkdir("Febex");
    dir_mwd = dir_energy->mkdir("MWD");

    dir_energy_LISA = dir_corr->mkdir("Energy_LISA-FRS");
    dir_LISA_FRS_febex = dir_energy_LISA->mkdir("Febex");
    dir_LISA_FRS_mwd = dir_energy_LISA->mkdir("MWD");

    dir_gates = dir_corr->mkdir("Gates");

    dir_gate_FRS_FRS = dir_gates->mkdir("FRS_on_FRS");
    dir_gate_LISA = dir_gates->mkdir("LISA_on_FRS");
    dir_gate_FRS = dir_gates->mkdir("FRS_on_LISA");
    dir_gate_LISA_FRS = dir_gates->mkdir("LISA_FRS");

    dir_gate_LISA_febex = dir_gate_LISA->mkdir("Febex");
    dir_gate_LISA_mwd = dir_gate_LISA->mkdir("MWD");

    dir_gate_FRS_febex = dir_gate_FRS->mkdir("Febex");
    dir_gate_FRS_mwd = dir_gate_FRS->mkdir("MWD");

    dir_gate_LISA_FRS_febex = dir_gate_LISA_FRS->mkdir("Febex");
    dir_gate_LISA_FRS_mwd = dir_gate_LISA_FRS->mkdir("MWD");

    //dir_corr_driftcorr = dir_corr->mkdir("DriftCorrected");
    //dir_energy_ch_driftcorr = dir_corr_driftcorr->mkdir("Energy_Channel_DriftCorr");
 
    // ::: TIME CORRELATIONS :::
    //c4LOG(info, "::::::::::::::::::start of init");
    dir_time->cd();
    h1_wr_diff = new TH1I("h1_WR_Difference_LISA-FRS", " WR Difference LISA - FRS ", 6000, -3000, 3000);
    h1_wr_diff->GetXaxis()->SetTitle("WR(LISA) - WR (FRS)");
    h1_wr_diff->SetFillColor(kRed-3);
    
    h1_wr_diff_tpat2 = new TH1I("h1_wr_diff_tpat2", " WR Difference LISA - FRS tpat 2", 6000, -3000, 3000);
    h1_wr_diff_tpat2->GetXaxis()->SetTitle("WR(LISA) - WR (FRS)");
    h1_wr_diff_tpat2->SetFillColor(kRed-3);

    h1_wr_diff_tpat6 = new TH1I("h1_wr_diff_tpat6", " WR Difference LISA - FRS tpat 6 ", 6000, -3000, 3000);
    h1_wr_diff_tpat6->GetXaxis()->SetTitle("WR(LISA) - WR (FRS)");
    h1_wr_diff_tpat6->SetFillColor(kRed-3);

    // h1_wr_diff[0] = new TH1I("h1_WR_Difference_LISA-FRS", " WR Difference LISA - FRS ", 6000, -3000, 3000);
    // h1_wr_diff[0]->GetXaxis()->SetTitle("WR(LISA) - WR (FRS)");
    // h1_wr_diff[0]->SetFillColor(kRed-3);

    // h1_wr_diff[1] = new TH1I("h1_WR_Difference_LISA-TravMUSIC", " WR Difference LISA - TravMUSIC ", 6000, -3000, 3000);
    // h1_wr_diff[1]->GetXaxis()->SetTitle("WR(LISA) - WR (travMUSIC)");
    // h1_wr_diff[1]->SetFillColor(kRed-3);

    // h1_wr_diff[2] = new TH1I("h1_WR_Difference_TravMUSIC-FRS", " WR Difference TravMUSIC - FRS ", 6000, -3000, 3000);
    // h1_wr_diff[2]->GetXaxis()->SetTitle("WR (travMUSIC) - WR (FRS)");
    // h1_wr_diff[2]->SetFillColor(kRed-3);
    //...........................................
    //c4LOG(info, "::::::::::::::::::end of time histos");
    // ::: Energy LISA correlated with FRS :::
    // Condition on scintillator 21
    // Febex
    h1_energy_layer_corr_sci21.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        h1_energy_layer_corr_sci21[i] = MakeTH1(dir_LISA_FRS_febex, "F",
            Form("h1_energy_layer_%i_corr_sci21", i+1), Form("Energy corr sci21- Layer %i", i+1), 
            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
            Form("E(LISA %i) Corr sci21 [a.u.]", i+1), kRed-3, kBlue+1);
    }
    // MWD
    h1_energy_MWD_layer_corr_sci21.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        h1_energy_MWD_layer_corr_sci21[i] = MakeTH1(dir_LISA_FRS_mwd, "F",
            Form("h1_energy_MWD_layer_%i_corr_sci21", i+1), Form("Energy MWD corr sci21- Layer %i", i+1), 
            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
            Form("E MWD(LISA %i) Corr sci21 [a.u.]", i+1), kViolet+3, kBlue+1);
    }

    // Condiiton on scintillator 41 
    // Febex
    h1_energy_layer_corr_sci41.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        h1_energy_layer_corr_sci41[i] = MakeTH1(dir_LISA_FRS_febex, "F",
            Form("h1_energy_layer_%i_corr_sci41", i+1), Form("Energy corr sci41- Layer %i", i+1), 
            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
            Form("E(LISA %i) Corr sci41 [a.u.]", i+1), kRed-3, kBlue+1);
    }
    // MWD
    h1_energy_MWD_layer_corr_sci41.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        h1_energy_MWD_layer_corr_sci41[i] = MakeTH1(dir_LISA_FRS_mwd, "F",
            Form("h1_energy_MWD_layer_%i_corr_sci41", i+1), Form("Energy MWD corr sci41- Layer %i", i+1), 
            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
            Form("E MWD(LISA %i) Corr sci41 [a.u.]", i+1), kViolet+10, kBlue+1);
    }
    //...........................................
    //c4LOG(info, "::::::::::::::::::end of sci histo");
    // :::   E N E R G Y  LISA vs MUSIC  C O R R E L A T I O N S   :::
    // ::: Febex
    dir_febex->cd();
    //      MUSIC 21 - LISA Febex
    h2_MUSIC21_vs_LISA_febex.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_MUSIC21_vs_LISA_febex[i] = new TH2F(Form("h2_MUSIC(21)_vs_LISA_%i_febex",i+1), Form("dE MUSIC(21) vs dE(LISA) %i Febex",i+1), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, bin_21, min_21, max_21);
        h2_MUSIC21_vs_LISA_febex[i]->GetXaxis()->SetTitle(Form("dE(LISA) Febex - Layer %i",i+1));
        h2_MUSIC21_vs_LISA_febex[i]->GetYaxis()->SetTitle("dE MUSIC(21)");
        h2_MUSIC21_vs_LISA_febex[i]->SetOption("COLZ");
    }
    //.......................
    //      MUSIC 41 - LISA Febex
    h2_MUSIC41_vs_LISA_febex.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_MUSIC41_vs_LISA_febex[i] = new TH2F(Form("h2_MUSIC(41)_vs_LISA_%i_febex",i+1), Form("dE MUSIC(41) vs dE(LISA) %i Febex",i+1), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, bin_41, min_41, max_41);
        h2_MUSIC41_vs_LISA_febex[i]->GetXaxis()->SetTitle(Form("dE(LISA) Febex - Layer %i",i+1));
        h2_MUSIC41_vs_LISA_febex[i]->GetYaxis()->SetTitle("dE MUSIC(41)");
        h2_MUSIC41_vs_LISA_febex[i]->SetOption("COLZ");
    }
    //.......................
    //      MUSIC 42 - LISA Febex
    h2_MUSIC42_vs_LISA_febex.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_MUSIC42_vs_LISA_febex[i] = new TH2F(Form("h2_MUSIC(42)_vs_LISA_%i_febex",i+1), Form("dE MUSIC(42) vs dE(LISA) %i Febex",i+1), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, bin_42, min_42, max_42);
        h2_MUSIC42_vs_LISA_febex[i]->GetXaxis()->SetTitle(Form("dE(LISA) Febex - Layer %i",i+1));
        h2_MUSIC42_vs_LISA_febex[i]->GetYaxis()->SetTitle("dE MUSIC(42)");
        h2_MUSIC42_vs_LISA_febex[i]->SetOption("COLZ");
    }
    //.......................
    // ::: MWD
    dir_mwd->cd();
    //      MUSIC 21 - LISA MWD
    h2_MUSIC21_vs_LISA_MWD.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_MUSIC21_vs_LISA_MWD[i] = new TH2F(Form("h2_MUSIC(21)_vs_LISA_%i_MWD",i), Form("dE MUSIC(21) vs dE(LISA) %i MWD",i+1), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, bin_21, min_21, max_21);
        h2_MUSIC21_vs_LISA_MWD[i]->GetXaxis()->SetTitle(Form("dE(LISA) MWD - Layer %i",i));
        h2_MUSIC21_vs_LISA_MWD[i]->GetYaxis()->SetTitle("dE MUSIC(21)");
        h2_MUSIC21_vs_LISA_MWD[i]->SetOption("COLZ");
    }
    //.......................
    //      MUSIC 41 - LISA MWD
    h2_MUSIC41_vs_LISA_MWD.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_MUSIC41_vs_LISA_MWD[i] = new TH2F(Form("h2_MUSIC(41)_vs_LISA_%i_MWD",i+1), Form("dE MUSIC(41) vs dE(LISA) %i MWD",i+1), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, bin_41, min_41, max_41);
        h2_MUSIC41_vs_LISA_MWD[i]->GetXaxis()->SetTitle(Form("dE(LISA) MWD - Layer %i",i+1));
        h2_MUSIC41_vs_LISA_MWD[i]->GetYaxis()->SetTitle("dE MUSIC(41)");
        h2_MUSIC41_vs_LISA_MWD[i]->SetOption("COLZ");
    }
    //.......................
    //      MUSIC 42 - LISA MWD
    h2_MUSIC42_vs_LISA_MWD.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_MUSIC42_vs_LISA_MWD[i] = new TH2F(Form("h2_MUSIC(42)_vs_LISA_%i_MWD",i+1), Form("dE MUSIC(42) vs dE(LISA) %i MWD",i+1), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, bin_42, min_42, max_42);
        h2_MUSIC42_vs_LISA_MWD[i]->GetXaxis()->SetTitle(Form("dE(LISA) MWD - Layer %i",i+1));
        h2_MUSIC42_vs_LISA_MWD[i]->GetYaxis()->SetTitle("dE MUSIC(42)");
        h2_MUSIC42_vs_LISA_MWD[i]->SetOption("COLZ");
    }
    //.......................
    //c4LOG(info, "::::::::::::::::::end of musci histo");

    //travMUSIC drift corrected VS LISA
    // dir_corr_driftcorr->cd();
    // h2_travMUSIC_driftcorr_layer_GM.resize(layer_number);
    // for (int i = 0; i < layer_number; i++)
    // {
    //     h2_travMUSIC_driftcorr_layer_GM[i] = new TH2F(Form("h2_travMUSIC_driftcorr_vs_E(LISA)_GM_Layer_%i",i), Form("travMUSIC DriftCorr vs E(LISA) GM Layer %i",i), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM, 1000,0,4096);
    //     h2_travMUSIC_driftcorr_layer_GM[i]->GetXaxis()->SetTitle(Form("E(LISA) [MeV] - Layer %i",i));
    //     h2_travMUSIC_driftcorr_layer_GM[i]->GetYaxis()->SetTitle("dE travMUSIC driftcorr");
    //     h2_travMUSIC_driftcorr_layer_GM[i]->SetOption("colz");

    // }

    // c4LOG(info," before gate");

    // ::: G A T E S 

    // ::: Gates FRS applied ON LISA 
    // ::: These are histos of LISA gated only with the conditions on FRS
    dir_FRS_febex_gates = new TDirectory*[FrsGates.size()];
    dir_FRS_febex_gates_channel = new TDirectory*[FrsGates.size()];
    dir_FRS_mwd_gates = new TDirectory*[FrsGates.size()];
    dir_FRS_mwd_gates_channel = new TDirectory*[FrsGates.size()];
    //c4LOG(info, ":::::::::::::::::: start of gate histos in init");   
    if (!FrsGates.empty())
    {
        //Full sequential gate of FRS - Z41
        h2_LISA_energy_vs_layer_s1s2s4_gated.resize(FrsGates.size());
        h2_LISA_energy_MWD_vs_layer_s1s2s4_gated.resize(FrsGates.size());
        h2_LISA_energy_xy_vs_layer_s1s2s4_gated.resize(FrsGates.size());
        h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated.resize(FrsGates.size());
        
        h1_LISA_energy_s1s2s4_gated.resize(FrsGates.size());
        h1_LISA_energy_MWD_s1s2s4_gated.resize(FrsGates.size());

        h1_LISA_energy_xy_s1s2s4_gated.resize(FrsGates.size());
        h1_LISA_energy_MWD_xy_s1s2s4_gated.resize(FrsGates.size());

        //Full sequential gate of FRS - Z42
        h2_LISA_energy_vs_layer_s1s2s4_gated_Z42.resize(FrsGates.size());
        h2_LISA_energy_MWD_vs_layer_s1s2s4_gated_Z42.resize(FrsGates.size());
        h2_LISA_energy_xy_vs_layer_s1s2s4_gated_Z42.resize(FrsGates.size());
        h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated_Z42.resize(FrsGates.size());
        
        h1_LISA_energy_s1s2s4_gated_Z42.resize(FrsGates.size());
        h1_LISA_energy_MWD_s1s2s4_gated_Z42.resize(FrsGates.size());

        h1_LISA_energy_xy_s1s2s4_gated_Z42.resize(FrsGates.size());
        h1_LISA_energy_MWD_xy_s1s2s4_gated_Z42.resize(FrsGates.size());

        // S1S2 gate
        h2_LISA_energy_vs_layer_s1s2_gated.resize(FrsGates.size());
        h2_LISA_energy_MWD_vs_layer_s1s2_gated.resize(FrsGates.size());
        h2_LISA_energy_xy_vs_layer_s1s2_gated.resize(FrsGates.size());
        h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated.resize(FrsGates.size());
        
        h1_LISA_energy_s1s2_gated.resize(FrsGates.size());
        h1_LISA_energy_MWD_s1s2_gated.resize(FrsGates.size());

        h1_LISA_energy_xy_s1s2_gated.resize(FrsGates.size());
        h1_LISA_energy_MWD_xy_s1s2_gated.resize(FrsGates.size());

        for (int gate_frs = 0; gate_frs < FrsGates.size(); gate_frs++)
        {
            // Febex - Layer
            dir_FRS_febex_gates[gate_frs] = dir_gate_FRS_febex->mkdir(TString(FrsGates.at(gate_frs)->GetName())); 

            dir_FRS_febex_gates[gate_frs]->cd();
            h2_LISA_energy_vs_layer_s1s2s4_gated[gate_frs] = new TH2F(Form("h2_energy_vs_layer_s1s2s4_gate_%i",gate_frs),
                                                            Form("Energy vs Layer ID - s1s2s4 Gate %i",gate_frs), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_vs_layer_s1s2s4_gated[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_vs_layer_s1s2s4_gated[gate_frs]->GetYaxis()->SetTitle("LISA Energy [a.u.]");
            h2_LISA_energy_vs_layer_s1s2s4_gated[gate_frs]->SetOption("COLZ");

            h2_LISA_energy_vs_layer_s1s2s4_gated_Z42[gate_frs] = new TH2F(Form("h2_energy_vs_layer_s1s2s4_gate_%i_Z42",gate_frs),
                                                            Form("Energy vs Layer ID - s1s2s4 Gate %i Z42",gate_frs), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_vs_layer_s1s2s4_gated_Z42[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_vs_layer_s1s2s4_gated_Z42[gate_frs]->GetYaxis()->SetTitle("LISA Energy [a.u.]");
            h2_LISA_energy_vs_layer_s1s2s4_gated_Z42[gate_frs]->SetOption("COLZ");

            h2_LISA_energy_vs_layer_s1s2_gated[gate_frs] = new TH2F(Form("h2_energy_vs_layer_s1s2_gate_%i",gate_frs),
                                                            Form("Energy vs Layer ID - s1s2 Gate %i",gate_frs), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_vs_layer_s1s2_gated[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_vs_layer_s1s2_gated[gate_frs]->GetYaxis()->SetTitle("LISA Energy [a.u.]");
            h2_LISA_energy_vs_layer_s1s2_gated[gate_frs]->SetOption("COLZ");
            
            h1_LISA_energy_s1s2s4_gated[gate_frs].resize(layer_number);
            h1_LISA_energy_s1s2s4_gated_Z42[gate_frs].resize(layer_number);

            h1_LISA_energy_s1s2_gated[gate_frs].resize(layer_number);
            for (int i = 0; i < layer_number; i++) 
            {
                h1_LISA_energy_s1s2s4_gated[gate_frs][i] = MakeTH1(dir_FRS_febex_gates[gate_frs], "F",
                    Form("h1_LISA_%i_energy_s1s2s4_gated_%i", i+1, gate_frs),
                    Form("LISA %i Energy - s1s2s4 Gate %i", i+1, gate_frs),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i) [a.u.]", i+1), kYellow+3, kBlue+1);

                h1_LISA_energy_s1s2s4_gated_Z42[gate_frs][i] = MakeTH1(dir_FRS_febex_gates[gate_frs], "F",
                    Form("h1_LISA_%i_energy_s1s2s4_gated_%i_Z42", i+1, gate_frs),
                    Form("LISA %i Energy - s1s2s4 Gate %i Z42", i+1, gate_frs),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i) [a.u.]", i+1), kYellow+3, kBlue+1);

                h1_LISA_energy_s1s2_gated[gate_frs][i] = MakeTH1(dir_FRS_febex_gates[gate_frs], "F",
                    Form("h1_LISA_%i_energy_s1s2_gated_%i", i+1, gate_frs),
                    Form("LISA %i Energy - s1s2 Gate %i", i+1, gate_frs),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i) [a.u.]", i+1), kYellow+3, kBlue+1);
            }

            // Febex - Channel
            dir_FRS_febex_gates_channel[gate_frs] = dir_FRS_febex_gates[gate_frs]->mkdir("Channel");

            dir_FRS_febex_gates_channel[gate_frs]->cd();
            h2_LISA_energy_xy_vs_layer_s1s2s4_gated[gate_frs] = new TH2F(Form("h2_LISA_energy_%i%i_vs_layer_s1s2s4_gate_%i",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                                                                Form("Energy %i%i vs Layer ID - s1s2s4 Gate %i",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                                                                layer_number, 0.5, layer_number + 0.5,
                                                                lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_xy_vs_layer_s1s2s4_gated[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_xy_vs_layer_s1s2s4_gated[gate_frs]->GetYaxis()->SetTitle(Form("LISA %i%i Energy [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_xy_vs_layer_s1s2s4_gated[gate_frs]->SetOption("COLZ");

            h2_LISA_energy_xy_vs_layer_s1s2_gated[gate_frs] = new TH2F(Form("h2_LISA_energy_%i%i_vs_layer_s1s2_gate_%i",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                                                                Form("Energy %i%i vs Layer ID - s1s2 Gate %i",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                                                                layer_number, 0.5, layer_number + 0.5,
                                                                lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_xy_vs_layer_s1s2_gated[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_xy_vs_layer_s1s2_gated[gate_frs]->GetYaxis()->SetTitle(Form("LISA %i%i Energy [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_xy_vs_layer_s1s2_gated[gate_frs]->SetOption("COLZ");

            h1_LISA_energy_xy_s1s2s4_gated[gate_frs].resize(layer_number);
            h1_LISA_energy_xy_s1s2s4_gated_Z42[gate_frs].resize(layer_number);

            h1_LISA_energy_xy_s1s2_gated[gate_frs].resize(layer_number);

            for (int i = 0; i < layer_number; i++) 
            {
                h1_LISA_energy_xy_s1s2s4_gated[gate_frs][i] = MakeTH1(dir_FRS_febex_gates_channel[gate_frs], "F",
                    Form("h1_LISA_%i%i%i_energy_s1s2s4_gated_%i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                    Form("LISA %i%i%i Energy - s1s2s4 Gate %i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i%i%i) [a.u.]", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                    kYellow-3, kBlue+1);

                h1_LISA_energy_xy_s1s2s4_gated_Z42[gate_frs][i] = MakeTH1(dir_FRS_febex_gates_channel[gate_frs], "F",
                    Form("h1_LISA_%i%i%i_energy_s1s2s4_gated_%i_Z42", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                    Form("LISA %i%i%i Energy - s1s2s4 Gate %i Z42", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i%i%i) [a.u.]", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                    kYellow-3, kBlue+1);

                h1_LISA_energy_xy_s1s2_gated[gate_frs][i] = MakeTH1(dir_FRS_febex_gates_channel[gate_frs], "F",
                    Form("h1_LISA_%i%i%i_energy_s1s2_gated_%i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                    Form("LISA %i%i%i Energy - s1s2 Gate %i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i%i%i) [a.u.]", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                    kYellow-3, kBlue+1);
            }

            //..........................

            // MWD  - Layer
            dir_FRS_mwd_gates[gate_frs] = dir_gate_FRS_mwd->mkdir(TString(FrsGates.at(gate_frs)->GetName()));

            dir_FRS_mwd_gates[gate_frs]->cd();
            h2_LISA_energy_MWD_vs_layer_s1s2s4_gated[gate_frs] = new TH2F(Form("h2_energy_MWD_vs_layer_s1s2s4gate_%i",gate_frs), 
                                                        Form("Energy MWD vs Layer ID - s1s2s4 Gate %i",gate_frs), 
                                                        layer_number, 0.5, layer_number + 0.5, 
                                                        lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_vs_layer_s1s2s4_gated[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_vs_layer_s1s2s4_gated[gate_frs]->GetYaxis()->SetTitle("LISA MWD Energy [a.u.]");
            h2_LISA_energy_MWD_vs_layer_s1s2s4_gated[gate_frs]->SetOption("COLZ");

            h2_LISA_energy_MWD_vs_layer_s1s2s4_gated_Z42[gate_frs] = new TH2F(Form("h2_energy_MWD_vs_layer_s1s2s4gate_%i_Z42",gate_frs), 
                                                        Form("Energy MWD vs Layer ID - s1s2s4 Gate %i Z42",gate_frs), 
                                                        layer_number, 0.5, layer_number + 0.5, 
                                                        lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_vs_layer_s1s2s4_gated_Z42[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_vs_layer_s1s2s4_gated_Z42[gate_frs]->GetYaxis()->SetTitle("LISA MWD Energy [a.u.]");
            h2_LISA_energy_MWD_vs_layer_s1s2s4_gated_Z42[gate_frs]->SetOption("COLZ");

            h2_LISA_energy_MWD_vs_layer_s1s2_gated[gate_frs] = new TH2F(Form("h2_energy_MWD_vs_layer_s1s2gate_%i",gate_frs), 
                                                        Form("Energy MWD vs Layer ID - s1s2 Gate %i",gate_frs), 
                                                        layer_number, 0.5, layer_number + 0.5, 
                                                        lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_vs_layer_s1s2_gated[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_vs_layer_s1s2_gated[gate_frs]->GetYaxis()->SetTitle("LISA MWD Energy [a.u.]");
            h2_LISA_energy_MWD_vs_layer_s1s2_gated[gate_frs]->SetOption("COLZ");
            
            h1_LISA_energy_MWD_s1s2s4_gated[gate_frs].resize(layer_number);
            h1_LISA_energy_MWD_s1s2s4_gated_Z42[gate_frs].resize(layer_number);

            h1_LISA_energy_MWD_s1s2_gated[gate_frs].resize(layer_number);
            for (int i = 0; i < layer_number; i++) 
            {
                h1_LISA_energy_MWD_s1s2s4_gated[gate_frs][i] = MakeTH1(dir_FRS_mwd_gates[gate_frs], "F",
                Form("h1_LISA_%i_energy_MWD_s1s2s4_gate_%i", i+1, gate_frs),
                Form("LISA %i Energy MWD - s1s2s4 Gate %i", i+1, gate_frs),
                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                Form("E MWD(LISA %i) [a.u.]", i+1), kGreen+3, kBlue+1);

                h1_LISA_energy_MWD_s1s2s4_gated_Z42[gate_frs][i] = MakeTH1(dir_FRS_mwd_gates[gate_frs], "F",
                Form("h1_LISA_%i_energy_MWD_s1s2s4_gate_%i_Z42", i+1, gate_frs),
                Form("LISA %i Energy MWD - s1s2s4 Gate %i Z42", i+1, gate_frs),
                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                Form("E MWD(LISA %i) [a.u.]", i+1), kGreen+3, kBlue+1);

                h1_LISA_energy_MWD_s1s2_gated[gate_frs][i] = MakeTH1(dir_FRS_mwd_gates[gate_frs], "F",
                Form("h1_LISA_%i_energy_MWD_s1s2_gate_%i", i+1, gate_frs),
                Form("LISA %i Energy MWD - s1s2 Gate %i", i+1, gate_frs),
                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                Form("E MWD(LISA %i) [a.u.]", i+1), kGreen+3, kBlue+1);
            }
        
            // MWD - Channel
            dir_FRS_mwd_gates_channel[gate_frs] = dir_FRS_mwd_gates[gate_frs]->mkdir("Channel");

            dir_FRS_mwd_gates_channel[gate_frs]->cd();
            h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated[gate_frs] = new TH2F(Form("h2_LISA_energy_MWD_%i%i_vs_layer_s1s2s4_gate_%i",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs), 
                                                                    Form("Energy %i%i vs Layer ID - s1s2s4 Gate %i",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs), 
                                                                    layer_number, 0.5, layer_number + 0.5, 
                                                                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated[gate_frs]->GetYaxis()->SetTitle(Form("LISA %i%i Energy MWD [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated[gate_frs]->SetOption("COLZ");

            h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated_Z42[gate_frs] = new TH2F(Form("h2_LISA_energy_MWD_%i%i_vs_layer_s1s2s4_gate_%i_Z42",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs), 
                                                                    Form("Energy %i%i vs Layer ID - s1s2s4 Gate %i Z42",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs), 
                                                                    layer_number, 0.5, layer_number + 0.5, 
                                                                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated_Z42[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated_Z42[gate_frs]->GetYaxis()->SetTitle(Form("LISA %i%i Energy MWD [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated_Z42[gate_frs]->SetOption("COLZ");

            h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated[gate_frs] = new TH2F(Form("h2_LISA_energy_MWD_%i%i_vs_layer_s1s2_gate_%i",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs), 
                                                                    Form("Energy %i%i vs Layer ID - s1s2 Gate %i",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs), 
                                                                    layer_number, 0.5, layer_number + 0.5, 
                                                                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated[gate_frs]->GetYaxis()->SetTitle(Form("LISA %i%i Energy MWD [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated[gate_frs]->SetOption("COLZ");

            h1_LISA_energy_MWD_xy_s1s2s4_gated[gate_frs].resize(layer_number);
            h1_LISA_energy_MWD_xy_s1s2s4_gated_Z42[gate_frs].resize(layer_number);

            h1_LISA_energy_MWD_xy_s1s2_gated[gate_frs].resize(layer_number);

            for (int i = 0; i < layer_number; i++) 
            {
                h1_LISA_energy_MWD_xy_s1s2s4_gated[gate_frs][i] = MakeTH1(dir_FRS_mwd_gates_channel[gate_frs], "F",
                Form("h1_LISA_%i%i%i_energy_MWD_s1s2s4_gate_%i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                Form("LISA %i%i%i Energy MWD - s1s2s4 Gate %i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                Form("E MWD(LISA %i%i%i) [a.u.]", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                kGreen-3, kBlue+1);

                h1_LISA_energy_MWD_xy_s1s2s4_gated_Z42[gate_frs][i] = MakeTH1(dir_FRS_mwd_gates_channel[gate_frs], "F",
                Form("h1_LISA_%i%i%i_energy_MWD_s1s2s4_gate_%i_Z42", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                Form("LISA %i%i%i Energy MWD - s1s2s4 Gate %i Z42", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                Form("E MWD(LISA %i%i%i) [a.u.]", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                kGreen-3, kBlue+1);

                h1_LISA_energy_MWD_xy_s1s2_gated[gate_frs][i] = MakeTH1(dir_FRS_mwd_gates_channel[gate_frs], "F",
                Form("h1_LISA_%i%i%i_energy_MWD_s1s2_gate_%i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                Form("LISA %i%i%i Energy MWD - s1s2 Gate %i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                Form("E MWD(LISA %i%i%i) [a.u.]", i+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                kGreen-3, kBlue+1);
                
            }
        }
    }
    //..........................
    // continue adding Z42 from here!!!!
    //c4LOG(info, "::::::::::::::::::end of gate histos in init");
    // ::: Gates LISA applied ON FRS
    // ::: These are histos of FRS gated only with the conditions on LISA
    //      Febex gates
    dir_LISA_febex_gates = new TDirectory*[gate_number];
    dir_LISA_febex_gates_channel = new TDirectory*[gate_number];
    if (!febex_gates.empty())
    {
        h2_Z21_vs_AoQs1s2_LISA_gated.resize(gate_number);
        h2_Z41_vs_AoQs2s4_LISA_gated.resize(gate_number);
        h2_Z42_vs_AoQs2s4_LISA_gated.resize(gate_number);
        for (int gate_lisa = 0; gate_lisa < febex_gates.size(); gate_lisa++)
        {
            dir_LISA_febex_gates[gate_lisa] = dir_gate_LISA_febex->mkdir(TString(febex_gates.at(gate_lisa)->GetName()));
            
            h2_Z21_vs_AoQs1s2_LISA_gated[gate_lisa].resize(layer_number);
            h2_Z41_vs_AoQs2s4_LISA_gated[gate_lisa].resize(layer_number);
            h2_Z42_vs_AoQs2s4_LISA_gated[gate_lisa].resize(layer_number);


            dir_LISA_febex_gates[gate_lisa]->cd();
            for ( int i = 0; i < layer_number; i++)
            {
                h2_Z21_vs_AoQs1s2_LISA_gated[gate_lisa][i] = new TH2F(Form("h2_Z21_vs_AoQs1s2_LISA_%i_gate_%i", i+1, gate_lisa), 
                                                        Form(" ZvsAoQ S2 - LISA %i - Gate %i", i+1, gate_lisa),  
                                                        1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                        1000, frs_config->fMin_Z, frs_config->fMax_Z);
                h2_Z21_vs_AoQs1s2_LISA_gated[gate_lisa][i]->GetXaxis()->SetTitle("AoQ - S1S2");
                h2_Z21_vs_AoQs1s2_LISA_gated[gate_lisa][i]->GetYaxis()->SetTitle("Z(21)");
                h2_Z21_vs_AoQs1s2_LISA_gated[gate_lisa][i]->SetOption("COLZ");  

                h2_Z41_vs_AoQs2s4_LISA_gated[gate_lisa][i] = new TH2F(Form("h2_Z41_vs_AoQs2s4_LISA_%i_gate_%i", i+1, gate_lisa), 
                                                        Form(" ZvsAoQ S4 - LISA %i - Gate %i", i+1, gate_lisa),  
                                                        1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                        1000, frs_config->fMin_Z, frs_config->fMax_Z);
                h2_Z41_vs_AoQs2s4_LISA_gated[gate_lisa][i]->GetXaxis()->SetTitle("AoQ - S2S4");
                h2_Z41_vs_AoQs2s4_LISA_gated[gate_lisa][i]->GetYaxis()->SetTitle("Z(41)");
                h2_Z41_vs_AoQs2s4_LISA_gated[gate_lisa][i]->SetOption("COLZ");  

                h2_Z42_vs_AoQs2s4_LISA_gated[gate_lisa][i] = new TH2F(Form("h2_Z42_vs_AoQs2s4_LISA_%i_gate_%i", i+1, gate_lisa), 
                                                        Form(" ZvsAoQ S4 - LISA %i - Gate %i", i+1, gate_lisa),  
                                                        1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                        1000, frs_config->fMin_Z, frs_config->fMax_Z);
                h2_Z42_vs_AoQs2s4_LISA_gated[gate_lisa][i]->GetXaxis()->SetTitle("AoQ - S2S4");
                h2_Z42_vs_AoQs2s4_LISA_gated[gate_lisa][i]->GetYaxis()->SetTitle("Z(42)");
                h2_Z42_vs_AoQs2s4_LISA_gated[gate_lisa][i]->SetOption("COLZ");              
            }        
        }
    }
    
    //      MWD gates
    dir_LISA_mwd_gates = new TDirectory*[mwd_gate_number];
    dir_LISA_mwd_gates_channel = new TDirectory*[mwd_gate_number];
    if (!mwd_gates.empty())
    {
        h2_Z21_vs_AoQs1s2_LISA_MWD_gated.resize(mwd_gate_number);
        h2_Z41_vs_AoQs2s4_LISA_MWD_gated.resize(mwd_gate_number);
        h2_Z42_vs_AoQs2s4_LISA_MWD_gated.resize(mwd_gate_number);

        for (int gate_lisa = 0; gate_lisa < mwd_gates.size(); gate_lisa++)
        {       
            dir_LISA_mwd_gates[gate_lisa] = dir_gate_LISA_mwd->mkdir(TString(mwd_gates.at(gate_lisa)->GetName()));
            
            h2_Z21_vs_AoQs1s2_LISA_MWD_gated[gate_lisa].resize(layer_number);
            h2_Z41_vs_AoQs2s4_LISA_MWD_gated[gate_lisa].resize(layer_number);
            h2_Z42_vs_AoQs2s4_LISA_MWD_gated[gate_lisa].resize(layer_number);

            dir_LISA_mwd_gates[gate_lisa]->cd();
            for ( int i = 0; i < layer_number; i++)
            {
                h2_Z21_vs_AoQs1s2_LISA_MWD_gated[gate_lisa][i] = new TH2F(Form("h2_Z21_vs_AoQs1s2_LISA_MWD_%i_gate_%i", i+1, gate_lisa), 
                                                        Form(" ZvsAoQ S2 - LISA_MWD %i - Gate %i", i+1, gate_lisa),  
                                                        1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                        1000, frs_config->fMin_Z, frs_config->fMax_Z);
                h2_Z21_vs_AoQs1s2_LISA_MWD_gated[gate_lisa][i]->GetXaxis()->SetTitle("AoQ - S1S2");
                h2_Z21_vs_AoQs1s2_LISA_MWD_gated[gate_lisa][i]->GetYaxis()->SetTitle("Z(21)");
                h2_Z21_vs_AoQs1s2_LISA_MWD_gated[gate_lisa][i]->SetOption("COLZ");  

                h2_Z41_vs_AoQs2s4_LISA_MWD_gated[gate_lisa][i] = new TH2F(Form("h2_Z41_vs_AoQs2s4_LISA_MWD_%i_gate_%i", i+1, gate_lisa), 
                                                        Form(" ZvsAoQ S4 - LISA_MWD %i - Gate %i",i+1, gate_lisa),  
                                                        1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                        1000, frs_config->fMin_Z, frs_config->fMax_Z);
                h2_Z41_vs_AoQs2s4_LISA_MWD_gated[gate_lisa][i]->GetXaxis()->SetTitle("AoQ - S2S4");
                h2_Z41_vs_AoQs2s4_LISA_MWD_gated[gate_lisa][i]->GetYaxis()->SetTitle("Z(41)");
                h2_Z41_vs_AoQs2s4_LISA_MWD_gated[gate_lisa][i]->SetOption("COLZ"); 


                h2_Z42_vs_AoQs2s4_LISA_MWD_gated[gate_lisa][i] = new TH2F(Form("h2_Z42_vs_AoQs2s4_LISA_MWD_%i_gate_%i", i+1, gate_lisa), 
                                                        Form(" ZvsAoQ S4 - LISA_MWD %i - Gate %i",i+1, gate_lisa),  
                                                        1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                        1000, frs_config->fMin_Z, frs_config->fMax_Z);
                h2_Z42_vs_AoQs2s4_LISA_MWD_gated[gate_lisa][i]->GetXaxis()->SetTitle("AoQ - S2S4");
                h2_Z42_vs_AoQs2s4_LISA_MWD_gated[gate_lisa][i]->GetYaxis()->SetTitle("Z(42)");
                h2_Z42_vs_AoQs2s4_LISA_MWD_gated[gate_lisa][i]->SetOption("COLZ");   
            } 

        }
    }   
    //............................
    //c4LOG(info, "::::::::::::::::::end of LISA applied on frs");

    // ::: Gates FRS applied on FRS :::
    dir_FRS_gates_correlated = new TDirectory*[FrsGates.size()];
    if (!FrsGates.empty())
    {
        // S1-S2 gate
        h2_Z21_vs_AoQs1s2_s1s2_correlated.resize(FrsGates.size());
        // S1S2S4 gate (full sequential gate)
        h2_Z21_vs_AoQs1s2_s1s2s4_correlated.resize(FrsGates.size());
        h2_Z41_vs_AoQs2s4_s1s2s4_correlated.resize(FrsGates.size());
        h2_Z42_vs_AoQs2s4_s1s2s4_correlated.resize(FrsGates.size());

        
        for (int gate_frs = 0; gate_frs < FrsGates.size(); gate_frs++)
        {
            dir_FRS_gates_correlated[gate_frs] = dir_gate_FRS_FRS->mkdir(TString(FrsGates.at(gate_frs)->GetName())); 
            dir_FRS_gates_correlated[gate_frs]->cd();       

            // S1S2 gated on S1S2
            h2_Z21_vs_AoQs1s2_s1s2_correlated[gate_frs] = new TH2F(Form("h2_Z21_vs_AoQs1s2_s1s2_correlated_gate_%i",gate_frs),
                                                            Form("Z21 vs AoQs1s2 - s1s2 Gate %i",gate_frs), 
                                                            1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                            1000, frs_config->fMin_Z, frs_config->fMax_Z);
            h2_Z21_vs_AoQs1s2_s1s2_correlated[gate_frs]->GetXaxis()->SetTitle("AoQ S1S2");
            h2_Z21_vs_AoQs1s2_s1s2_correlated[gate_frs]->GetYaxis()->SetTitle("Z(21)");
            h2_Z21_vs_AoQs1s2_s1s2_correlated[gate_frs]->SetOption("COLZ");

            // S1S2 gated on S1S2S4
            h2_Z21_vs_AoQs1s2_s1s2s4_correlated[gate_frs] = new TH2F(Form("h2_Z21_vs_AoQs1s2_s1s2s4_correlated_gate_%i",gate_frs),
                                                            Form("Z21 vs AoQs1s2 - s1s2s4 Gate %i",gate_frs), 
                                                            1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                            1000, frs_config->fMin_Z, frs_config->fMax_Z);
            h2_Z21_vs_AoQs1s2_s1s2s4_correlated[gate_frs]->GetXaxis()->SetTitle("AoQ S1S2");
            h2_Z21_vs_AoQs1s2_s1s2s4_correlated[gate_frs]->GetYaxis()->SetTitle("Z(21)");
            h2_Z21_vs_AoQs1s2_s1s2s4_correlated[gate_frs]->SetOption("COLZ");

            // S2S4 gated on S1S2S4
            h2_Z41_vs_AoQs2s4_s1s2s4_correlated[gate_frs] = new TH2F(Form("h2_Z41_vs_AoQs2s4_s1s2s4_correlated_gate_%i",gate_frs),
                                                            Form("Z41 vs AoQs2s4 - s1s2s4 Gate %i",gate_frs), 
                                                            1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                            1000, frs_config->fMin_Z, frs_config->fMax_Z);
            h2_Z41_vs_AoQs2s4_s1s2s4_correlated[gate_frs]->GetXaxis()->SetTitle("AoQ S2S4");
            h2_Z41_vs_AoQs2s4_s1s2s4_correlated[gate_frs]->GetYaxis()->SetTitle("Z(41)");
            h2_Z41_vs_AoQs2s4_s1s2s4_correlated[gate_frs]->SetOption("COLZ"); 

            h2_Z42_vs_AoQs2s4_s1s2s4_correlated[gate_frs] = new TH2F(Form("h2_Z42_vs_AoQs2s4_s1s2s4_correlated_gate_%i",gate_frs),
                                                            Form("Z42 vs AoQs2s4 - s1s2s4 Gate %i",gate_frs), 
                                                            1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 
                                                            1000, frs_config->fMin_Z, frs_config->fMax_Z);
            h2_Z42_vs_AoQs2s4_s1s2s4_correlated[gate_frs]->GetXaxis()->SetTitle("AoQ S2S4");
            h2_Z42_vs_AoQs2s4_s1s2s4_correlated[gate_frs]->GetYaxis()->SetTitle("Z(42)");
            h2_Z42_vs_AoQs2s4_s1s2s4_correlated[gate_frs]->SetOption("COLZ");         
        }
    }
    //...................
    // ::: Gates LISA - FRS
    // ::: These are histos of LISA gated with conditions on FRS and LISA
    dir_LISA_FRS_febex_gates = new TDirectory*[FrsGates.size()];
    dir_LISA_FRS_febex_gates_channel = new TDirectory*[FrsGates.size()];
    dir_LISA_FRS_mwd_gates = new TDirectory*[FrsGates.size()];
    dir_LISA_FRS_mwd_gates_channel = new TDirectory*[FrsGates.size()];

    // Febex - FRS
    if (!febex_gates.empty() && !FrsGates.empty())
    {
        pair_count = std::min(febex_gates.size(), FrsGates.size());
        // std::cout << "pair_count" << pair_count << std::endl;
        
        h2_LISA_energy_vs_layer_LISA_s1s2_gated.resize(pair_count);
        h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated.resize(pair_count);

        h1_LISA_energy_LISA_s1s2_gated.resize(pair_count);
        h1_LISA_energy_xy_LISA_s1s2_gated.resize(pair_count);

        h2_LISA_energy_vs_layer_LISA_s1s2s4_gated.resize(pair_count);
        h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated.resize(pair_count);

        h1_LISA_energy_LISA_s1s2s4_gated.resize(pair_count);
        h1_LISA_energy_xy_LISA_s1s2s4_gated.resize(pair_count);
        //............
        // Multiplicity 5 condition
        h2_LISA_energy_vs_layer_LISA_s1s2_gated_M5.resize(pair_count);
        h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated_M5.resize(pair_count);

        h1_LISA_energy_LISA_s1s2_gated_M5.resize(pair_count);
        h1_LISA_energy_xy_LISA_s1s2_gated_M5.resize(pair_count);

        h2_LISA_energy_vs_layer_LISA_s1s2s4_gated_M5.resize(pair_count);
        h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated_M5.resize(pair_count);

        h1_LISA_energy_LISA_s1s2s4_gated_M5.resize(pair_count);
        h1_LISA_energy_xy_LISA_s1s2s4_gated_M5.resize(pair_count);
        //
        for (int i = 0; i < pair_count; ++i)
        {
            dir_LISA_FRS_febex_gates[i] = dir_gate_LISA_FRS_febex->mkdir(Form(TString(FrsGates.at(i)->GetName()) + "_" + TString(febex_gates.at(i)->GetName()) ));

            dir_LISA_FRS_febex_gates[i]->cd();

            h2_LISA_energy_vs_layer_LISA_s1s2_gated[i] = new TH2F(Form("h2_energy_vs_layer_LISA-s1s2_gate_%i",i),
                                                            Form("Energy vs Layer ID - LISA-s1s2 Gate %i",i), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_vs_layer_LISA_s1s2_gated[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_vs_layer_LISA_s1s2_gated[i]->GetYaxis()->SetTitle("LISA Energy [a.u.]");
            h2_LISA_energy_vs_layer_LISA_s1s2_gated[i]->SetOption("COLZ");

            h2_LISA_energy_vs_layer_LISA_s1s2s4_gated[i] = new TH2F(Form("h2_energy_vs_layer_LISA-s1s2s4_gate_%i",i),
                                                            Form("Energy vs Layer ID - LISA-s1s2s4 Gate %i",i), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_vs_layer_LISA_s1s2s4_gated[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_vs_layer_LISA_s1s2s4_gated[i]->GetYaxis()->SetTitle("LISA Energy [a.u.]");
            h2_LISA_energy_vs_layer_LISA_s1s2s4_gated[i]->SetOption("COLZ");

            // Mulitplicity 5
            h2_LISA_energy_vs_layer_LISA_s1s2_gated_M5[i] = new TH2F(Form("h2_energy_vs_layer_LISA-s1s2_gate_%i_M5",i),
                                                            Form("Energy vs Layer ID - LISA-s1s2 Gate %i M5",i), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_vs_layer_LISA_s1s2_gated_M5[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_vs_layer_LISA_s1s2_gated_M5[i]->GetYaxis()->SetTitle("LISA Energy [a.u.]");
            h2_LISA_energy_vs_layer_LISA_s1s2_gated_M5[i]->SetOption("COLZ");

            h2_LISA_energy_vs_layer_LISA_s1s2s4_gated_M5[i] = new TH2F(Form("h2_energy_vs_layer_LISA-s1s2s4_gate_%i_M5",i),
                                                            Form("Energy vs Layer ID - LISA-s1s2s4 Gate %i M5",i), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_vs_layer_LISA_s1s2s4_gated_M5[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_vs_layer_LISA_s1s2s4_gated_M5[i]->GetYaxis()->SetTitle("LISA Energy [a.u.]");
            h2_LISA_energy_vs_layer_LISA_s1s2s4_gated_M5[i]->SetOption("COLZ");
            //.....
            h1_LISA_energy_LISA_s1s2_gated[i].resize(layer_number);
            h1_LISA_energy_LISA_s1s2s4_gated[i].resize(layer_number);

            h1_LISA_energy_LISA_s1s2_gated_M5[i].resize(layer_number);
            h1_LISA_energy_LISA_s1s2s4_gated_M5[i].resize(layer_number);

            for (int l = 0; l < layer_number; l++) 
            {
                h1_LISA_energy_LISA_s1s2_gated[i][l] = MakeTH1(dir_LISA_FRS_febex_gates[i], "F",
                    Form("h1_LISA_%i_energy_LISA_s1s2_gated_%i", l+1, i),
                    Form("LISA %i Energy - LISA-s1s2 Gate %i", l+1, i),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i) [a.u.]", l+1), kYellow+3, kBlue+1);

                h1_LISA_energy_LISA_s1s2s4_gated[i][l] = MakeTH1(dir_LISA_FRS_febex_gates[i], "F",
                    Form("h1_LISA_%i_energy_LISA_s1s2s4_gated_%i", l+1, i),
                    Form("LISA %i Energy - LISA-s1s2s4 Gate %i", l+1, i),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i) [a.u.]", l+1), kYellow+3, kBlue+1);
                // Multiplicity 5
                h1_LISA_energy_LISA_s1s2_gated_M5[i][l] = MakeTH1(dir_LISA_FRS_febex_gates[i], "F",
                    Form("h1_LISA_%i_energy_LISA_s1s2_gated_%i_M5", l+1, i),
                    Form("LISA %i Energy - LISA-s1s2 Gate %i M5", l+1, i),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i) [a.u.]", l+1), kYellow+3, kBlue+1);

                h1_LISA_energy_LISA_s1s2s4_gated_M5[i][l] = MakeTH1(dir_LISA_FRS_febex_gates[i], "F",
                    Form("h1_LISA_%i_energy_LISA_s1s2s4_gated_%i_M5", l+1, i),
                    Form("LISA %i Energy - LISA-s1s2s4 Gate %i M5", l+1, i),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i) [a.u.]", l+1), kYellow+3, kBlue+1);
                //
            }           
            
            dir_LISA_FRS_febex_gates_channel[i] = dir_LISA_FRS_febex_gates[i]->mkdir("Channel");

            dir_LISA_FRS_febex_gates_channel[i]->cd();
            h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated[i] = new TH2F(Form("h2_LISA_energy_%i%i_vs_layer_LISA-s1s2_gate_%i",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                Form("Energy %i%i vs Layer ID - LISA-s1s2 Gate %i",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                layer_number, 0.5, layer_number + 0.5,
                                                                lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated[i]->GetYaxis()->SetTitle(Form("LISA %i%i Energy [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated[i]->SetOption("COLZ");

            h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated[i] = new TH2F(Form("h2_LISA_energy_%i%i_vs_layer_LISA-s1s2s4_gate_%i",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                Form("Energy %i%i vs Layer ID - LISA-s1s2s4 Gate %i",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                layer_number, 0.5, layer_number + 0.5,
                                                                lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated[i]->GetYaxis()->SetTitle(Form("LISA %i%i Energy [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated[i]->SetOption("COLZ");
            // Multiplicity 5
            h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated_M5[i] = new TH2F(Form("h2_LISA_energy_%i%i_vs_layer_LISA-s1s2_gate_%i_M5",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                Form("Energy %i%i vs Layer ID - LISA-s1s2 Gate %i M5",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                layer_number, 0.5, layer_number + 0.5,
                                                                lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated_M5[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated_M5[i]->GetYaxis()->SetTitle(Form("LISA %i%i Energy [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated_M5[i]->SetOption("COLZ");

            h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated_M5[i] = new TH2F(Form("h2_LISA_energy_%i%i_vs_layer_LISA-s1s2s4_gate_%i_M5",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                Form("Energy %i%i vs Layer ID - LISA-s1s2s4 Gate %i M5",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                layer_number, 0.5, layer_number + 0.5,
                                                                lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated_M5[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated_M5[i]->GetYaxis()->SetTitle(Form("LISA %i%i Energy [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated_M5[i]->SetOption("COLZ");
            //

            h1_LISA_energy_xy_LISA_s1s2_gated[i].resize(layer_number);
            h1_LISA_energy_xy_LISA_s1s2s4_gated[i].resize(layer_number);

            h1_LISA_energy_xy_LISA_s1s2_gated_M5[i].resize(layer_number);
            h1_LISA_energy_xy_LISA_s1s2s4_gated_M5[i].resize(layer_number);
            for (int l = 0; l < layer_number; l++) 
            {
                h1_LISA_energy_xy_LISA_s1s2_gated[i][l] = MakeTH1(dir_LISA_FRS_febex_gates_channel[i], "F",
                    Form("h1_LISA_%i%i%i_energy_LISA_s1s2_gated_%i", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    Form("LISA %i%i%i Energy - LISA_s1s2 Gate %i", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i%i%i) [a.u.]", l+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                    kYellow-3, kBlue+1);

                h1_LISA_energy_xy_LISA_s1s2s4_gated[i][l] = MakeTH1(dir_LISA_FRS_febex_gates_channel[i], "F",
                    Form("h1_LISA_%i%i%i_energy_LISA_s1s2s4_gated_%i", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    Form("LISA %i%i%i Energy - LISA_s1s2s4 Gate %i", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i%i%i) [a.u.]", l+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                    kYellow-3, kBlue+1);
                // Multiplicity 5
                h1_LISA_energy_xy_LISA_s1s2_gated_M5[i][l] = MakeTH1(dir_LISA_FRS_febex_gates_channel[i], "F",
                    Form("h1_LISA_%i%i%i_energy_LISA_s1s2_gated_%i_M5", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    Form("LISA %i%i%i Energy - LISA_s1s2 Gate %i M5", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i%i%i) [a.u.]", l+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                    kYellow-3, kBlue+1);

                h1_LISA_energy_xy_LISA_s1s2s4_gated_M5[i][l] = MakeTH1(dir_LISA_FRS_febex_gates_channel[i], "F",
                    Form("h1_LISA_%i%i%i_energy_LISA_s1s2s4_gated_%i_M5", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    Form("LISA %i%i%i Energy - LISA_s1s2s4 Gate %i M5", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, 
                    Form("E(LISA %i%i%i) [a.u.]", l+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                    kYellow-3, kBlue+1);
                //
                
            }
        }
    }
    //c4LOG(info, "::::::::::::::::::end of LISA-FRS febex ");
    // MWD - FRS
    if (!mwd_gates.empty() && !FrsGates.empty())
    {
        pair_count_MWD = std::min(mwd_gates.size(), FrsGates.size());

        h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated.resize(pair_count_MWD);
        h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated.resize(pair_count_MWD);

        h1_LISA_energy_MWD_LISA_s1s2_gated.resize(pair_count_MWD);
        h1_LISA_energy_MWD_xy_LISA_s1s2_gated.resize(pair_count_MWD);

        h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated.resize(pair_count_MWD);
        h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated.resize(pair_count_MWD);

        h1_LISA_energy_MWD_LISA_s1s2s4_gated.resize(pair_count_MWD);
        h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated.resize(pair_count_MWD);
        // Mulitplicity 5 condition
        h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated_M5.resize(pair_count_MWD);
        h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated_M5.resize(pair_count_MWD);

        h1_LISA_energy_MWD_LISA_s1s2_gated_M5.resize(pair_count_MWD);
        h1_LISA_energy_MWD_xy_LISA_s1s2_gated_M5.resize(pair_count_MWD);

        h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated_M5.resize(pair_count_MWD);
        h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated_M5.resize(pair_count_MWD);

        h1_LISA_energy_MWD_LISA_s1s2s4_gated_M5.resize(pair_count_MWD);
        h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated_M5.resize(pair_count_MWD);
        //........

        for (int i = 0; i < pair_count_MWD; ++i)
        {
            dir_LISA_FRS_mwd_gates[i] = dir_gate_LISA_FRS_mwd->mkdir(Form(TString(FrsGates.at(i)->GetName()) + "_" + TString(mwd_gates.at(i)->GetName()) ));

            dir_LISA_FRS_mwd_gates[i]->cd();
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated[i] = new TH2F(Form("h2_energy_MWD_vs_layer_LISA-s1s2_gate_%i",i),
                                                            Form("Energy MWD vs Layer ID - LISA-s1s2 Gate %i",i), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated[i]->GetYaxis()->SetTitle("LISA Energy MWD [a.u.]");
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated[i]->SetOption("COLZ");

            h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated[i] = new TH2F(Form("h2_energy_MWD_vs_layer_LISA-s1s2s4_gate_%i",i),
                                                            Form("Energy MWD vs Layer ID - LISA-s1s2s4 Gate %i",i), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated[i]->GetYaxis()->SetTitle("LISA Energy MWD [a.u.]");
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated[i]->SetOption("COLZ");
            
            h1_LISA_energy_MWD_LISA_s1s2_gated[i].resize(layer_number);
            h1_LISA_energy_MWD_LISA_s1s2s4_gated[i].resize(layer_number);

            // Multiplicity 5
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated_M5[i] = new TH2F(Form("h2_energy_MWD_vs_layer_LISA-s1s2_gate_%i_M5",i),
                                                            Form("Energy MWD vs Layer ID - LISA-s1s2 Gate %i M5",i), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated_M5[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated_M5[i]->GetYaxis()->SetTitle("LISA Energy MWD [a.u.]");
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated_M5[i]->SetOption("COLZ");

            h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated_M5[i] = new TH2F(Form("h2_energy_MWD_vs_layer_LISA-s1s2s4_gate_%i_M5",i),
                                                            Form("Energy MWD vs Layer ID - LISA-s1s2s4 Gate %i M5",i), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated_M5[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated_M5[i]->GetYaxis()->SetTitle("LISA Energy MWD [a.u.]");
            h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated_M5[i]->SetOption("COLZ");
            
            h1_LISA_energy_MWD_LISA_s1s2_gated_M5[i].resize(layer_number);
            h1_LISA_energy_MWD_LISA_s1s2s4_gated_M5[i].resize(layer_number);
            //

            for (int l = 0; l < layer_number; l++) 
            {
                h1_LISA_energy_MWD_LISA_s1s2_gated[i][l] = MakeTH1(dir_LISA_FRS_mwd_gates[i], "F",
                    Form("h1_LISA_%i_energy_MWD_LISA_s1s2_gated_%i", l+1, i),
                    Form("LISA %i Energy MWD - LISA-s1s2 Gate %i", l+1, i),
                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                    Form("E MWD(LISA %i) [a.u.]", l+1), kGreen+3, kBlue+1);
                h1_LISA_energy_MWD_LISA_s1s2s4_gated[i][l] = MakeTH1(dir_LISA_FRS_mwd_gates[i], "F",
                    Form("h1_LISA_%i_energy_MWD_LISA_s1s2s4_gated_%i", l+1, i),
                    Form("LISA %i Energy MWD - LISA-s1s2s4 Gate %i", l+1, i),
                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                    Form("E MWD(LISA %i) [a.u.]", l+1), kGreen+3, kBlue+1);

                //Multiplciity 5
                h1_LISA_energy_MWD_LISA_s1s2_gated_M5[i][l] = MakeTH1(dir_LISA_FRS_mwd_gates[i], "F",
                    Form("h1_LISA_%i_energy_MWD_LISA_s1s2_gated_%i_M5", l+1, i),
                    Form("LISA %i Energy MWD - LISA-s1s2 Gate %i M5", l+1, i),
                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                    Form("E MWD(LISA %i) [a.u.]", l+1), kGreen+3, kBlue+1);
                h1_LISA_energy_MWD_LISA_s1s2s4_gated_M5[i][l] = MakeTH1(dir_LISA_FRS_mwd_gates[i], "F",
                    Form("h1_LISA_%i_energy_MWD_LISA_s1s2s4_gated_%i_M5", l+1, i),
                    Form("LISA %i Energy MWD - LISA-s1s2s4 Gate %i M5", l+1, i),
                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                    Form("E MWD(LISA %i) [a.u.]", l+1), kGreen+3, kBlue+1);
                //
            
            
            }               
            
            dir_LISA_FRS_mwd_gates_channel[i] = dir_LISA_FRS_mwd_gates[i]->mkdir("Channel");

            dir_LISA_FRS_mwd_gates_channel[i]->cd();
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated[i] = new TH2F(Form("h2_LISA_energy_MWD_%i%i_vs_layer_LISA-s1s2_gate_%i",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                Form("Energy %i%i vs Layer ID - LISA-s1s2 Gate %i",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                layer_number, 0.5, layer_number + 0.5,
                                                                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated[i]->GetYaxis()->SetTitle(Form("LISA %i%i Energy MWD [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated[i]->SetOption("COLZ");

            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated[i] = new TH2F(Form("h2_LISA_energy_MWD_%i%i_vs_layer_LISA-s1s2s4_gate_%i",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                Form("Energy %i%i vs Layer ID - LISA-s1s2s4 Gate %i",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                layer_number, 0.5, layer_number + 0.5,
                                                                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated[i]->GetYaxis()->SetTitle(Form("LISA %i%i Energy MWD [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated[i]->SetOption("COLZ");

            h1_LISA_energy_MWD_xy_LISA_s1s2_gated[i].resize(layer_number);
            h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated[i].resize(layer_number);

            // Multiplciity 5
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated_M5[i] = new TH2F(Form("h2_LISA_energy_MWD_%i%i_vs_layer_LISA-s1s2_gate_%i_M5",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                Form("Energy %i%i vs Layer ID - LISA-s1s2 Gate %i M5",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                layer_number, 0.5, layer_number + 0.5,
                                                                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated_M5[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated_M5[i]->GetYaxis()->SetTitle(Form("LISA %i%i Energy MWD [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated_M5[i]->SetOption("COLZ");

            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated_M5[i] = new TH2F(Form("h2_LISA_energy_MWD_%i%i_vs_layer_LISA-s1s2s4_gate_%i_M5",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                Form("Energy %i%i vs Layer ID - LISA-s1s2s4 Gate %i M5",lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                                                                layer_number, 0.5, layer_number + 0.5,
                                                                lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated_M5[i]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated_M5[i]->GetYaxis()->SetTitle(Form("LISA %i%i Energy MWD [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated_M5[i]->SetOption("COLZ");

            h1_LISA_energy_MWD_xy_LISA_s1s2_gated_M5[i].resize(layer_number);
            h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated_M5[i].resize(layer_number);
            //
            for (int l = 0; l < layer_number; l++) 
            {
                h1_LISA_energy_MWD_xy_LISA_s1s2_gated[i][l] = MakeTH1(dir_LISA_FRS_mwd_gates_channel[i], "F",
                    Form("h1_LISA_%i%i%i_energy_MWD_LISA_s1s2_gated_%i", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    Form("LISA %i%i%i Energy MWD - LISA_s1s2 Gate %i", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                    Form("E MWD(LISA %i%i%i) [a.u.]", l+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                    kGreen-3, kBlue+1);
                h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated[i][l] = MakeTH1(dir_LISA_FRS_mwd_gates_channel[i], "F",
                    Form("h1_LISA_%i%i%i_energy_MWD_LISA_s1s2s4_gated_%i", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    Form("LISA %i%i%i Energy MWD - LISA_s1s2s4 Gate %i", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                    Form("E MWD(LISA %i%i%i) [a.u.]", l+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                    kGreen-3, kBlue+1);
                
                // Multiplicity 5
                h1_LISA_energy_MWD_xy_LISA_s1s2_gated_M5[i][l] = MakeTH1(dir_LISA_FRS_mwd_gates_channel[i], "F",
                    Form("h1_LISA_%i%i%i_energy_MWD_LISA_s1s2_gated_%i_M5", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    Form("LISA %i%i%i Energy MWD - LISA_s1s2 Gate %i M5", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                    Form("E MWD(LISA %i%i%i) [a.u.]", l+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                    kGreen-3, kBlue+1);
                h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated_M5[i][l] = MakeTH1(dir_LISA_FRS_mwd_gates_channel[i], "F",
                    Form("h1_LISA_%i%i%i_energy_MWD_LISA_s1s2s4_gated_%i_M5", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    Form("LISA %i%i%i Energy MWD - LISA_s1s2s4 Gate %i M5", l+1,lisa_config->xpos_gate, lisa_config->ypos_gate, i),
                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, 
                    Form("E MWD(LISA %i%i%i) [a.u.]", l+1, lisa_config->xpos_gate, lisa_config->ypos_gate),
                    kGreen-3, kBlue+1);
            
            }
        }
    }
    //c4LOG(info, "::::::::::::::::::end of LISA-FRS mwd ");
    // Extrapolated TPC positon at LISA
    h1_tpc_lisa_x = new TH1*[layer_number];
    h1_tpc_lisa_y = new TH1*[layer_number];
    h2_tpc_x_lisa_x = new TH2*[layer_number];
    h2_tpc_y_lisa_y = new TH2*[layer_number];
    h2_tpc_xy_LISA = new TH2*[layer_number];
    for (int i = 0; i < layer_number; i++)
    {
        h1_tpc_lisa_x[i] = MakeTH1(dir_position, "F", Form("h1_tpc_lisa_x_%i", i+1), Form("LISA X (FROM TPC) Layer %i", i+1), 1000, -100., 100., "X", kYellow, kBlack);
        h1_tpc_lisa_y[i] = MakeTH1(dir_position, "F", Form("h1_tpc_lisa_y_%i", i+1), Form("LISA Y (FROM TPC) Layer %i", i+1), 1000, -100., 100., "Y", kYellow, kBlack);
        h2_tpc_x_lisa_x[i] = MakeTH2(dir_position, "F", Form("h2_tpc_x_lisa_x_%i", i+1),Form("TPC X vs LISA X Layer %i", i+1), xmax, 0, xmax, 1000, -100., 100.);
        h2_tpc_y_lisa_y[i] = MakeTH2(dir_position, "F", Form("h2_tpc_y_lisa_y_%i", i+1),Form("TPC Y vs LISA Y Layer %i", i+1), ymax, 0, ymax, 1000, -100., 100.);
        h2_tpc_xy_LISA[i] = MakeTH2(dir_position, "F", Form("h2_tpc_xy_LISA_%i", i+1), Form("TPC XY at LISA - Layer %i", i+1), 1000, -100., 100., 1000, -100., 100.);
    }

    // TCanvas* c_test = new TCanvas("c_test", "TPC POS XY AT LISA", 650, 350);
    // c_test->Divide(2,2);
    // c_test->cd(1);
    // h2_tpc_xy_LISA_001 = MakeTH2(dir_position, "F", "h2_tpc_xy_LISA_001", "TPC XY at LISA 001", 40, -8., 10., 40, -25., -4.);
    // // h2_tpc_xy_LISA_001->Draw();
    // // c_test->cd(2);
    // h2_tpc_xy_LISA_011 = MakeTH2(dir_position, "F", "h2_tpc_xy_LISA_011", "TPC XY at LISA 011", 40, -8., 10., 40, -25., -4.);
    // // h2_tpc_xy_LISA_011->Draw();
    // // c_test->cd(3);
    // h2_tpc_xy_LISA_000 = MakeTH2(dir_position, "F", "h2_tpc_xy_LISA_000", "TPC XY at LISA 000", 40, -8., 10., 40, -25., -4.);
    // // h2_tpc_xy_LISA_000->Draw();
    // // c_test->cd(4);
    // h2_tpc_xy_LISA_010 = MakeTH2(dir_position, "F", "h2_tpc_xy_LISA_010", "TPC XY at LISA 010", 40, -8., 10., 40, -25., -4.);
    // // h2_tpc_xy_LISA_010->Draw();
    // // dir_position->Append(c_test);
    //..........................
    //c4LOG(info, "::::::::::::::::::end of position ");

    mh_counter_passed_s1s2_seq = new int*[pair_count];
    mh_counter_passed_s2s4_seq = new int*[pair_count];
    for (int pair = 0; pair < pair_count; pair++)
    {   
        mh_counter_passed_s1s2_seq[pair] = new int[layer_number];
        mh_counter_passed_s2s4_seq[pair] = new int[layer_number];
        for (int i = 0; i < layer_number; i++)
        {
            mh_counter_passed_s1s2_seq[pair][i] = 0;
            mh_counter_passed_s2s4_seq[pair][i] = 0;
        }
    }

    mh_counter_passed_s1s2_seq_mwd = new int*[pair_count_MWD];
    mh_counter_passed_s2s4_seq_mwd = new int*[pair_count_MWD];
    for (int pair = 0; pair < pair_count; pair++)
    {   
        mh_counter_passed_s1s2_seq_mwd[pair] = new int[layer_number];
        mh_counter_passed_s2s4_seq_mwd[pair] = new int[layer_number];
        for (int i = 0; i < layer_number; i++)
        {
            mh_counter_passed_s1s2_seq_mwd[pair][i] = 0;
            mh_counter_passed_s2s4_seq_mwd[pair][i] = 0;
        }
    }
    //c4LOG(info, "::::::::::::::::::end of counters ");
   
    energy_layer.resize(layer_number);
    energy_MWD_layer.resize(layer_number);

    energy_xy_gated.resize(gate_number);
    energy_layer_gated.resize(gate_number);
    for (int g = 0; g < gate_number; g++) 
    {   
        energy_layer_gated[g].resize(layer_number);
        energy_xy_gated[g].resize(layer_number);
        for (int l = 0; l < layer_number; l++) 
        {
            energy_xy_gated[g][l].resize(xmax);
            for (int x = 0; x < xmax; x++) 
            {
                energy_xy_gated[g][l][x].resize(ymax);
            }
        }
    }
    //c4LOG(info, "::::::::::::::::::end of energy gated febex ");
   
    energy_MWD_xy_gated.resize(mwd_gate_number);
    energy_MWD_layer_gated.resize(mwd_gate_number);
    for (int g = 0; g < mwd_gate_number; g++) 
    {   
        energy_MWD_layer_gated[g].resize(layer_number);
        energy_MWD_xy_gated[g].resize(layer_number);
        for (int l = 0; l < layer_number; l++) 
        {
            energy_MWD_xy_gated[g][l].resize(xmax);
            for (int x = 0; x < xmax; x++) 
            {
                energy_MWD_xy_gated[g][l][x].resize(ymax);
            }
        }
    }

    z21_passed.resize(FrsGates.size());
    AoQ_s1s2_passed.resize(FrsGates.size());
    z41_passed.resize(FrsGates.size());
    z42_passed.resize(FrsGates.size());
    AoQ_s2s4_passed.resize(FrsGates.size());
    dEdeg_z41_passed.resize(FrsGates.size());
    // now it should be a sized vector of vectors?

    //c4LOG(info, "::::::::::::::::::end of init");
    return kSUCCESS;
    

}



void LisaFrsCorrelations::Exec(Option_t* option)
{   
    // -> Reject events without both subsystems <-
    if (frsHitArray->size() <= 0 || lisaCalArray->size() <= 0) return;  // frs, lisa and travmus subevent exists
    
    

    const auto & frsHitItem = frsHitArray->at(0);                       // *should* only be 1 FRS subevent per event
    const auto & multihitItem = multihitArray->at(0);                 // *should* only be 1 FRS subevent per event

    // ::: FRS WR
    Int_t count_wr = 0;
    wr_FRS = frsHitItem.Get_wr_t();
    wr_travMUSIC = frsHitItem.Get_travmus_wr_t();

    // ::: Total multiplicity of lisa
    int lisa_total_multiplicity = 0;

    //................

    // ::: MUSIC energies
    energy_MUSIC_21 = frsHitItem.Get_music21_dE();
    energy_MUSIC_41 = frsHitItem.Get_music41_dE(); 
    energy_MUSIC_42 = frsHitItem.Get_music42_dE();
    // ::: FRS data
    std::vector<Float_t> z21_mhtdc = multihitItem.Get_ID_z21_mhtdc();
    std::vector<Float_t> z41_mhtdc = multihitItem.Get_ID_z41_mhtdc();
    std::vector<Float_t> z42_mhtdc = multihitItem.Get_ID_z42_mhtdc();
    std::vector<Float_t> AoQ_s1s2_mhtdc = multihitItem.Get_ID_AoQ_corr_s1s2_mhtdc();
    std::vector<Float_t> AoQ_s2s4_mhtdc = multihitItem.Get_ID_AoQ_corr_s2s4_mhtdc();
    if (AoQ_s2s4_mhtdc.size() > 0) aoq++;
    std::vector<Float_t> dEdeg_z41_mhtdc = multihitItem.Get_ID_dEdeg_z41_mhtdc();
    Float_t x2_position = frsHitItem.Get_ID_x2();
    Float_t x4_position = frsHitItem.Get_ID_x4();
    Float_t sci42e = frsHitItem.Get_sci_e_42();

    if (AoQ_s1s2_mhtdc.size()!=1 || AoQ_s2s4_mhtdc.size() !=1 ) return;   // this is a quick fix to avoid getting any event with multihits (just pick 1)
    ncorr++;
    
    // CEJ :: Process FRS Gate info here first.
    for (int gate = 0; gate < FrsGates.size(); gate++)
    {
        if (AoQ_s1s2_mhtdc.size()!=1 || AoQ_s2s4_mhtdc.size() !=1 )break; // this is a quick fix to reject all the events with multihits - redundant
        for (int i = 0; i < AoQ_s1s2_mhtdc.size(); i++)
        {
            
            if (FrsGates[gate]->PassedS1S2(z21_mhtdc.at(i), x2_position, AoQ_s1s2_mhtdc.at(i)))
            {
                z21_passed[gate].emplace_back(z21_mhtdc.at(i));
                AoQ_s1s2_passed[gate].emplace_back(AoQ_s1s2_mhtdc.at(i));
                
            }
        }

        for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
        {
            if (FrsGates[gate]->PassedS2S4(z41_mhtdc.at(i), z42_mhtdc.at(i), x2_position, x4_position, AoQ_s2s4_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), sci42e))
            {
                z41_passed[gate].emplace_back(z41_mhtdc.at(i));
                z42_passed[gate].emplace_back(z42_mhtdc.at(i));
                AoQ_s2s4_passed[gate].emplace_back(AoQ_s2s4_mhtdc.at(i));
                dEdeg_z41_passed[gate].emplace_back(dEdeg_z41_mhtdc.at(i));
            }
        }
    }


    layer1seen = false;
    layer2seen = false;

    // correlation with main FRS (10, 20, 30, 15)
    for (const auto & lisaCalItem : *lisaCalArray)
    {        

        // ::: LISA White Rabbit
        if (count_wr == 0)
        {
            wr_LISA = lisaCalItem.Get_wr_t();
        }
        count_wr++;
        if (wr_LISA == 0)return;

        // ::: Position data
        layer = lisaCalItem.Get_layer_id();
        if (layer == 1) layer1seen = true;
        else if (layer == 2) layer2seen = true;

        city = lisaCalItem.Get_city();
        int xpos = lisaCalItem.Get_xposition();
        int ypos = lisaCalItem.Get_yposition();

        Float_t a_focs2 = frsHitItem.Get_tpc_angle_x_s2_foc_22_23();
        Float_t b_focs2 = frsHitItem.Get_tpc_angle_y_s2_foc_22_23();
        Float_t x_focs2 = frsHitItem.Get_tpc_x_s2_foc_22_23();
        Float_t y_focs2 = frsHitItem.Get_tpc_y_s2_foc_22_23();

        Float_t dist_focS2_TPC22 = frs->dist_focS2 - frs->dist_TPC22;
        Float_t dist_LISA_focS2 = 1930 + 153 + (layer-1) * 4.8 + dist_focS2_TPC22;

        Float_t x_lisa_tpc22_23 = (a_focs2 / 1000. * dist_LISA_focS2) + x_focs2;
        Float_t y_lisa_tpc22_23 = (b_focs2 / 1000. * dist_LISA_focS2) + y_focs2;

        h1_tpc_lisa_x[layer-1]->Fill(x_lisa_tpc22_23);
        h1_tpc_lisa_y[layer-1]->Fill(y_lisa_tpc22_23);

        h2_tpc_x_lisa_x[layer-1]->Fill(xpos, x_lisa_tpc22_23);
        h2_tpc_y_lisa_y[layer-1]->Fill(ypos, y_lisa_tpc22_23);
        h2_tpc_xy_LISA[layer-1]->Fill(x_lisa_tpc22_23, y_lisa_tpc22_23);

        // if (layer == 1 && xpos == 0 && ypos == 1) h2_tpc_xy_LISA_001->Fill(x_lisa_tpc22_23, y_lisa_tpc22_23);
        // if (layer == 1 && xpos == 1 && ypos == 1) h2_tpc_xy_LISA_011->Fill(x_lisa_tpc22_23, y_lisa_tpc22_23);
        // if (layer == 1 && xpos == 0 && ypos == 0) h2_tpc_xy_LISA_000->Fill(x_lisa_tpc22_23, y_lisa_tpc22_23);
        // if (layer == 1 && xpos == 1 && ypos == 0) h2_tpc_xy_LISA_010->Fill(x_lisa_tpc22_23, y_lisa_tpc22_23);
    
        // ::: Total multiplicity of lisa detector
        lisa_total_multiplicity++;
        // ::: Energy data
        float energy_LISA_febex = lisaCalItem.Get_energy_GM();
        float energy_LISA_MWD = lisaCalItem.Get_energy_MWD_GM();

        // Exclude channel before filling layers
        if (excluded.count(std::make_tuple(layer, xpos, ypos)) != 0) continue;

        energy_layer[layer-1].emplace_back(energy_LISA_febex);
        energy_MWD_layer[layer-1].emplace_back(energy_LISA_MWD);

        // Loop over gates for LISA FEBEX
        for (int g = 0; g < febex_gates.size(); g++)
        {
            if (febex_gates.at(g)->PassedGate(layer, energy_LISA_febex))
            {
                energy_layer_gated[g][layer-1].push_back( energy_LISA_febex);
                energy_xy_gated[g][layer-1][xpos][ypos].push_back( energy_LISA_febex);
            }
        }


        int g = 0;

        // Loop over gates for LISA MWD
        g = 0;
        for (auto & gate : mwd_gates)
        {   
            if (gate->PassedGate(layer, energy_LISA_MWD))
            {
                energy_MWD_layer_gated[g][layer-1].push_back(energy_LISA_MWD);
                energy_MWD_xy_gated[g][layer-1][xpos][ypos].push_back(energy_LISA_MWD);
            }
            g++;
        }
        //...........................


        // ::: FRS applied on LISA (FRS_ON_LISA Directory)
        //int mh_counter_passed_s1s2[FrsGates.size()] = {0};
        //int mh_counter_passed_s2s4[FrsGates.size()] = {0};
        if (!FrsGates.empty())
        {
            for (int gate = 0; gate < FrsGates.size(); gate++)
            {    
                // S1S2 gated
                if ( z21_passed[gate].size() > 0 )
                {
                    // Febex
                    h2_LISA_energy_vs_layer_s1s2_gated[gate]->Fill(layer, energy_LISA_febex);
                    h1_LISA_energy_s1s2_gated[gate][layer-1]->Fill(energy_LISA_febex);
                    // MWD
                    h2_LISA_energy_MWD_vs_layer_s1s2_gated[gate]->Fill(layer, energy_LISA_MWD);
                    h1_LISA_energy_MWD_s1s2_gated[gate][layer-1]->Fill(energy_LISA_MWD);
                    
                    //Febex and MWD XY channel
                    if ( xpos == lisa_config->xpos_gate && ypos == lisa_config->ypos_gate)
                    {
                        h2_LISA_energy_xy_vs_layer_s1s2_gated[gate]->Fill(layer, energy_LISA_febex);
                        h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated[gate]->Fill(layer, energy_LISA_MWD);
                        
                        h1_LISA_energy_xy_s1s2_gated[gate][layer-1]->Fill(energy_LISA_febex);
                        h1_LISA_energy_MWD_xy_s1s2_gated[gate][layer-1]->Fill(energy_LISA_MWD);
                    } 
                }

                // Sequential
                if ( z21_passed[gate].size() > 0 && z41_passed[gate].size() > 0) //all vectors of s1s2 have the same size (same for s2s4)
                {
                    // Febex
                    h2_LISA_energy_vs_layer_s1s2s4_gated[gate]->Fill(layer, energy_LISA_febex);
                    h1_LISA_energy_s1s2s4_gated[gate][layer-1]->Fill(energy_LISA_febex);
                    // MWD
                    h2_LISA_energy_MWD_vs_layer_s1s2s4_gated[gate]->Fill(layer, energy_LISA_MWD);
                    h1_LISA_energy_MWD_s1s2s4_gated[gate][layer-1]->Fill(energy_LISA_MWD);
                    
                    //Febex and MWD XY channel
                    if ( xpos == lisa_config->xpos_gate && ypos == lisa_config->ypos_gate)
                    {
                        h2_LISA_energy_xy_vs_layer_s1s2s4_gated[gate]->Fill(layer, energy_LISA_febex);
                        h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated[gate]->Fill(layer, energy_LISA_MWD);
                        
                        h1_LISA_energy_xy_s1s2s4_gated[gate][layer-1]->Fill(energy_LISA_febex);
                        h1_LISA_energy_MWD_xy_s1s2s4_gated[gate][layer-1]->Fill(energy_LISA_MWD);
                    } 
                }
                
            }            
        } 


        multi_evt++;
        //..........................
        
    }
    
    //c4LOG(info, " Total multiplicity of lisa: " << lisa_total_multiplicity);
    // ::: T I M E - WR differences
    wr_LISA_FRS = wr_LISA - wr_FRS;
    wr_LISA_travMUSIC = wr_LISA - wr_travMUSIC;
    wr_travMUSIC_FRS = wr_travMUSIC - wr_FRS;
    
    //if(wr_travMUSIC == 0) return;
    //h1_wr_diff[2]->Fill(wr_travMUSIC_FRS);

    //if(wr_travMUSIC == 0) return;
    //h1_wr_diff[1]->Fill(wr_LISA_travMUSIC);

    //if (wr_FRS != 0 && wr_LISA != 0) h1_wr_diff[0]->Fill(wr_LISA_FRS);

    h1_wr_diff->Fill(wr_LISA_FRS);
    if (frsHitItem.Get_tpat() & 0b100000) h1_wr_diff_tpat6->Fill(wr_LISA_FRS);
    if (frsHitItem.Get_tpat() & 0b10) h1_wr_diff_tpat2->Fill(wr_LISA_FRS);
    //............................

    // ::: Energy correlations with SCI21 (TPAT 6)
    
    if (frsHitItem.Get_tpat() & 0b100000)
    {
        for (int i = 0; i < layer_number; i++)
        {
            for (int j = 0; j < energy_layer[i].size(); j++)
            {
                h1_energy_layer_corr_sci21[i]->Fill(energy_layer[i][j]);
                
            }

            for (int j = 0; j < energy_MWD_layer[i].size(); j++)
            {
                h1_energy_MWD_layer_corr_sci21[i]->Fill(energy_MWD_layer[i][j]);
            }

        }
    }
    //..........................
    // ::: Energy correlations with SCI41 (TPAT 2)
    if (frsHitItem.Get_tpat() & 0b10)
    {
        for (int i = 0; i < layer_number; i++)
        {
            for (int j = 0; j < energy_layer[i].size(); j++)
            {
                h1_energy_layer_corr_sci41[i]->Fill(energy_layer[i][j]);
            }
            for (int j = 0; j < energy_layer[i].size(); j++)
            {
                h1_energy_MWD_layer_corr_sci41[i]->Fill(energy_MWD_layer[i][j]);
            }

        }
    }
    //..........................

    // ::: E N E R G Y  - LISA vs MUSICs
    for (int i = 0; i < layer_number; i++)
    {
        for (int j = 0; j < energy_layer[i].size(); j++)
        {
            // MUSIC 21
            h2_MUSIC21_vs_LISA_febex[i]->Fill(energy_layer[i][j],energy_MUSIC_21);
            // MUSIC 41
            h2_MUSIC41_vs_LISA_febex[i]->Fill(energy_layer[i][j],energy_MUSIC_41);
            // MUSIC 42
            h2_MUSIC42_vs_LISA_febex[i]->Fill(energy_layer[i][j],energy_MUSIC_42);
        }

        for (int j = 0; j < energy_MWD_layer[i].size(); j++)
        {
            // MUSIC 21
            h2_MUSIC21_vs_LISA_MWD[i]->Fill(energy_MWD_layer[i][j],energy_MUSIC_21);
            // MUSIC 41
            h2_MUSIC41_vs_LISA_MWD[i]->Fill(energy_MWD_layer[i][j],energy_MUSIC_41);
            // MUSIC 42
            h2_MUSIC42_vs_LISA_MWD[i]->Fill(energy_MWD_layer[i][j],energy_MUSIC_42);
        }

    }
    //............................
    // Fill FRS histos applied on FRS
    // FRS on FRS
    if (!FrsGates.empty())
    {
        for (int gate = 0; gate < FrsGates.size(); gate++)
        {
            // Loop S1S2
            if ( z21_passed[gate].size() > 0 )
            {
                for ( int i = 0; i < z21_passed[gate].size(); i++)
                {
                    h2_Z21_vs_AoQs1s2_s1s2_correlated[gate]->Fill(AoQ_s1s2_passed[gate].at(i), z21_passed[gate].at(i));
                }
            }
            // Full seq gate (S1S2S4)
            if ( z21_passed[gate].size() > 0 && z41_passed[gate].size() > 0) 
            {
                for ( int i = 0; i < z21_passed[gate].size(); i++)
                {
                    h2_Z21_vs_AoQs1s2_s1s2s4_correlated[gate]->Fill( AoQ_s1s2_passed[gate].at(i), z21_passed[gate].at(i));
                }

                for ( int j = 0; j < z41_passed[gate].size(); j++)
                {
                    h2_Z41_vs_AoQs2s4_s1s2s4_correlated[gate]->Fill(AoQ_s2s4_passed[gate].at(j), z41_passed[gate].at(j));
                    h2_Z42_vs_AoQs2s4_s1s2s4_correlated[gate]->Fill(AoQ_s2s4_passed[gate].at(j), z42_passed[gate].at(j));

                }
            }
        }
    }
    //....................

    // ::: LISA gates applied on FRS (LISA_ON_FRS Directory)
    // ::: FRS histos gated on LISA layers - Febex
    for (int g = 0; g < gate_number; g++)  
    {
        for (int l = 0; l < layer_number; l++) 
        {
            // Check condition on Febex Gate
            if (energy_layer_gated[g][l].size() == 0) break;  
            // S1S2
            for (int i = 0; i < AoQ_s1s2_mhtdc.size(); i++)
            {
                h2_Z21_vs_AoQs1s2_LISA_gated[g][l]->Fill(AoQ_s1s2_mhtdc.at(i),z21_mhtdc.at(i));
            }
            // S2S4
            for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
            {
                h2_Z41_vs_AoQs2s4_LISA_gated[g][l]->Fill(AoQ_s2s4_mhtdc.at(i),z41_mhtdc.at(i));
                h2_Z42_vs_AoQs2s4_LISA_gated[g][l]->Fill(AoQ_s2s4_mhtdc.at(i),z42_mhtdc.at(i));

            }            
        
        }
    }
    // ::: FRS histos gated on LISA layers - MWD
    
    for (int g = 0; g < mwd_gate_number; g++)  
    {
        for (int l = 0; l < layer_number; l++) 
        {
            // Check condition on MWD Gate
            if (energy_MWD_layer_gated[g][l].size() == 0) break;  
            // S1S2
            for (int i = 0; i < AoQ_s1s2_mhtdc.size(); i++)
            {
                h2_Z21_vs_AoQs1s2_LISA_MWD_gated[g][l]->Fill(AoQ_s1s2_mhtdc.at(i),z21_mhtdc.at(i));
            }
            // S2S4
            for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
            {
                h2_Z41_vs_AoQs2s4_LISA_MWD_gated[g][l]->Fill(AoQ_s2s4_mhtdc.at(i),z41_mhtdc.at(i));
                h2_Z42_vs_AoQs2s4_LISA_MWD_gated[g][l]->Fill(AoQ_s2s4_mhtdc.at(i),z42_mhtdc.at(i));

            }            
        }
    }
    //............................

    // ::: LISA-FRS gates applied on LISA (LISA_FRS Directory)
    //     Histo with no condition on multiplicity and with condition of multiplicity 5
    // ::: Febex
    //pair_count = std::min(febex_gates.size(), FrsGates.size());
    for (int pair = 0; pair < pair_count; pair++)  
    {
        for (int l = 0; l < layer_number; l++) 
        {
            // Check condition on Febex Gate
            if (energy_layer_gated[pair][l].size() == 0) break; 

            // S1 S2 conditions
            if ( z21_passed[pair].size() > 0 ) 
            {
                for ( int j = 0; j < energy_layer_gated[pair][l].size(); j++)
                {
                    // Febex with condition of trigger on sci41 (TPAT 2)
                    if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_vs_layer_LISA_s1s2_gated[pair]->Fill(l+1, energy_layer_gated[pair][l].at(j));
                    if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_LISA_s1s2_gated[pair][l]->Fill(energy_layer_gated[pair][l].at(j)); 

                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_vs_layer_LISA_s1s2_gated_M5[pair]->Fill(l+1, energy_layer_gated[pair][l].at(j));
                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_LISA_s1s2_gated_M5[pair][l]->Fill(energy_layer_gated[pair][l].at(j)); 
                
                }

                for ( int k = 0; k < energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].size(); k++ )
                {
                    // Febex XY with condition of trigger on sci41 (TPAT 2)
                    if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated[pair]->Fill(l+1, energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                    if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_xy_LISA_s1s2_gated[pair][l]->Fill(energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));

                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated_M5[pair]->Fill(l+1, energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_xy_LISA_s1s2_gated_M5[pair][l]->Fill(energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));

                }
            }

            // Loop for sequential gate S1S2S4
            if ( z21_passed[pair].size() > 0 && z41_passed[pair].size() > 0 ) 
            {
                for ( int j = 0; j < energy_layer_gated[pair][l].size(); j++)
                {
                    // Febex with condition of trigger on sci41 (TPAT 2)
                    if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_vs_layer_LISA_s1s2s4_gated[pair]->Fill(l+1, energy_layer_gated[pair][l].at(j));
                    if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_LISA_s1s2s4_gated[pair][l]->Fill(energy_layer_gated[pair][l].at(j));   

                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_vs_layer_LISA_s1s2s4_gated_M5[pair]->Fill(l+1, energy_layer_gated[pair][l].at(j));
                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_LISA_s1s2s4_gated_M5[pair][l]->Fill(energy_layer_gated[pair][l].at(j));   
                }

                for ( int k = 0; k < energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].size(); k++ )
                {
                    // Febex XY with condition of trigger on sci41 (TPAT 2)
                    if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated[pair]->Fill(l+1, energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                    if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_xy_LISA_s1s2s4_gated[pair][l]->Fill(energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));

                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated_M5[pair]->Fill(l+1, energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_xy_LISA_s1s2s4_gated_M5[pair][l]->Fill(energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));                       
                
                }
            }
                
        }
    }
    // ::: MWD 
    //int pair_count_MWD = std::min(mwd_gates.size(), FrsGates.size());
    
    for (int pair = 0; pair < pair_count_MWD; pair++)  
    {
        for (int l = 0; l < layer_number; l++) 
        {
            // Check condition on Febex Gate
            if (energy_MWD_layer_gated[pair][l].size() == 0) break;

            // Loop for S1S2
            if ( z21_passed[pair].size() > 0 ) 
            {
                for ( int j = 0; j < energy_MWD_layer_gated[pair][l].size(); j++)
                {
                    // MWD  with condition of trigger on sci41 (TPAT 2)
                    if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated[pair]->Fill(l+1, energy_MWD_layer_gated[pair][l].at(j));
                    if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_MWD_LISA_s1s2_gated[pair][l]->Fill(energy_MWD_layer_gated[pair][l].at(j));   

                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated_M5[pair]->Fill(l+1, energy_MWD_layer_gated[pair][l].at(j));
                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_MWD_LISA_s1s2_gated_M5[pair][l]->Fill(energy_MWD_layer_gated[pair][l].at(j));           
                }

                for ( int k = 0; k < energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].size(); k++ )
                {
                    // MWD XY  with condition of trigger on sci41 (TPAT 2)
                    if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated[pair]->Fill(l+1, energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                    if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_MWD_xy_LISA_s1s2_gated[pair][l]->Fill(energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));

                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2_gated_M5[pair]->Fill(l+1, energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_MWD_xy_LISA_s1s2_gated_M5[pair][l]->Fill(energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                                    
                }                  
            }

            // Loop for sequential gate S1S2S4
            if ( z21_passed[pair].size() > 0 && z41_passed[pair].size() > 0 ) 
            {
                
                for ( int j = 0; j < energy_MWD_layer_gated[pair][l].size(); j++)
                {
                    // MWD with condition of trigger on sci41 (TPAT 2)
                    if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated[pair]->Fill(l+1, energy_MWD_layer_gated[pair][l].at(j));
                    if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_MWD_LISA_s1s2s4_gated[pair][l]->Fill(energy_MWD_layer_gated[pair][l].at(j));   

                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_MWD_vs_layer_LISA_s1s2s4_gated_M5[pair]->Fill(l+1, energy_MWD_layer_gated[pair][l].at(j));
                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_MWD_LISA_s1s2s4_gated_M5[pair][l]->Fill(energy_MWD_layer_gated[pair][l].at(j));                        
                
                }

                for ( int k = 0; k < energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].size(); k++ )
                {
                    // MWD XY with condition of trigger on sci41 (TPAT 2)
                    if (frsHitItem.Get_tpat() & 0b10) h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated[pair]->Fill(l+1, energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                    if (frsHitItem.Get_tpat() & 0b10) h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated[pair][l]->Fill(energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));

                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h2_LISA_energy_MWD_xy_vs_layer_LISA_s1s2s4_gated_M5[pair]->Fill(l+1, energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                    if ((frsHitItem.Get_tpat() & 0b10) && lisa_total_multiplicity == 5) h1_LISA_energy_MWD_xy_LISA_s1s2s4_gated_M5[pair][l]->Fill(energy_MWD_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));                    
                }
                                   
            }
        }
    } 
    //............................


    fNEvents++;

}

void LisaFrsCorrelations::FinishEvent()
{
    for (int pair = 0; pair < pair_count; pair++)
    {
        for (int i = 0; i < layer_number; i++)
        {
            mh_counter_passed_s1s2_seq[pair][i] = 0;
            mh_counter_passed_s2s4_seq[pair][i] = 0;
        }
    }
    for (int pair = 0; pair < pair_count_MWD; pair++)
    {
        for (int i = 0; i < layer_number; i++)
        {
            mh_counter_passed_s1s2_seq_mwd[pair][i] = 0;
            mh_counter_passed_s2s4_seq_mwd[pair][i] = 0;
        }
    }

    for (int l = 0; l < layer_number; l++)
    {
        energy_layer[l].clear();
        energy_MWD_layer[l].clear();
    }

    for (int g = 0; g < gate_number; g++)
    {
        for (int l = 0; l < layer_number; l++)
        {
            energy_layer_gated[g][l].clear();
            energy_MWD_layer_gated[g][l].clear();
            for (int x = 0; x < xmax; x++)
            {
                for (int y = 0; y < ymax; y++)
                {
                    energy_xy_gated[g][l][x][y].clear();
                    energy_MWD_xy_gated[g][l][x][y].clear();
                }
            }
        }
    }

    for (int gate = 0; gate < FrsGates.size(); gate++)
    {
        z21_passed[gate].clear();
        AoQ_s1s2_passed[gate].clear();
        z41_passed[gate].clear();
        z42_passed[gate].clear();
        AoQ_s2s4_passed[gate].clear();
        dEdeg_z41_passed[gate].clear(); 
    }
}

void LisaFrsCorrelations::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_corr->Write();
    //dir_corr_driftcorr->Write();
    c4LOG(info, "Written LISA analysis histograms to file.");
    c4LOG(info, "Multi hit events when LISA is in the event (correlated) : " <<  multi_evt++ << " LISA-FRS events : " << fNEvents);


}


ClassImp(LisaFrsCorrelations)