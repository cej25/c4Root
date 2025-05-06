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

    // Ranges from MUSICs
    int min_21 = frs_config->fMin_dE_music21;
    int max_21 = frs_config->fMax_dE_music21;
    int bin_21 = (max_21 - min_21)/10;
    int min_41 = frs_config->fMin_dE_music41;
    int max_41 = frs_config->fMax_dE_music41;
    int bin_41 = (max_41 - min_41)/10;
    //.............

    FairRootManager::Instance()->GetOutFile()->cd();

    excluded = lisa_config->GetExcludedChannels();

    dir_corr = gDirectory->mkdir("Correlations");
    dir_time = dir_corr->mkdir("Time");

    dir_position = dir_corr->mkdir("Position");

    dir_energy = dir_corr->mkdir("Energy");
    dir_febex = dir_energy->mkdir("Febex");
    dir_mwd = dir_energy->mkdir("MWD");

    dir_gates = dir_corr->mkdir("Gates");

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
    dir_time->cd();
    h1_wr_diff.resize(3);

    h1_wr_diff[0] = new TH1I("h1_WR_Difference_LISA-FRS", " WR Difference LISA - FRS ", 6000, -3000, 3000);
    h1_wr_diff[0]->GetXaxis()->SetTitle("WR(LISA) - WR (FRS)");
    h1_wr_diff[0]->SetFillColor(kRed-3);

    h1_wr_diff[1] = new TH1I("h1_WR_Difference_LISA-TravMUSIC", " WR Difference LISA - TravMUSIC ", 6000, -3000, 3000);
    h1_wr_diff[1]->GetXaxis()->SetTitle("WR(LISA) - WR (travMUSIC)");
    h1_wr_diff[1]->SetFillColor(kRed-3);

    h1_wr_diff[2] = new TH1I("h1_WR_Difference_TravMUSIC-FRS", " WR Difference TravMUSIC - FRS ", 6000, -3000, 3000);
    h1_wr_diff[2]->GetXaxis()->SetTitle("WR (travMUSIC) - WR (FRS)");
    h1_wr_diff[2]->SetFillColor(kRed-3);
    //...........................................

    // ::: POSITION CORRELATIONS :::
    // FRS Position on TPC interpolated on LISA vs LISA
    dir_position->cd();

    h2_TPC_vs_LISA_x.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_TPC_vs_LISA_x[i] = new TH2F(Form("h2_TPC_vs_LISA_x_Layer_%i",i+1), Form("TPC vs LISA X - Layer %i",i+1), xmax, 0, xmax, 400,-100,100);
        h2_TPC_vs_LISA_x[i]->GetXaxis()->SetTitle(Form("LISA - X position Layer %i",i+1));
        h2_TPC_vs_LISA_x[i]->GetYaxis()->SetTitle("TPC Position");
        h2_TPC_vs_LISA_x[i]->SetStats(0);
        h2_TPC_vs_LISA_x[i]->SetOption("colz");        
    }

    h2_TPC_vs_LISA_y.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_TPC_vs_LISA_y[i] = new TH2F(Form("h2_TPC_vs_LISA_y_Layer_%i",i+1), Form("TPC vs LISA Y - Layer %i",i+1), ymax, 0, ymax, 400,-100,100);
        h2_TPC_vs_LISA_y[i]->GetXaxis()->SetTitle(Form("LISA - Y position Layer %i",i+1));
        h2_TPC_vs_LISA_y[i]->GetYaxis()->SetTitle("TPC Position");
        h2_TPC_vs_LISA_y[i]->SetStats(0);
        h2_TPC_vs_LISA_y[i]->SetOption("colz");        
    }
    //.......................

    // :::   E N E R G Y    C O R R E L A T I O N S   :::
    // ::: Febex
    dir_febex->cd();
    //      MUSIC 21 - LISA Febex
    h2_MUSIC21_vs_LISA_febex.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_MUSIC21_vs_LISA_febex[i] = new TH2F(Form("h2_MUSIC(21)_vs_LISA_%i_febex",i), Form("dE MUSIC(21) vs dE(LISA) %i Febex",i), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, bin_21, min_21, max_21);
        h2_MUSIC21_vs_LISA_febex[i]->GetXaxis()->SetTitle(Form("dE(LISA) Febex - Layer %i",i));
        h2_MUSIC21_vs_LISA_febex[i]->GetYaxis()->SetTitle("dE MUSIC(21)");
        h2_MUSIC21_vs_LISA_febex[i]->SetOption("COLZ");
    }
    //.......................
    //      MUSIC 41 - LISA Febex
    h2_MUSIC41_vs_LISA_febex.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_MUSIC41_vs_LISA_febex[i] = new TH2F(Form("h2_MUSIC(41)_vs_LISA_%i_febex",i), Form("dE MUSIC(41) vs dE(LISA) %i Febex",i), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, bin_41, min_41, max_41);
        h2_MUSIC41_vs_LISA_febex[i]->GetXaxis()->SetTitle(Form("dE(LISA) Febex - Layer %i",i));
        h2_MUSIC41_vs_LISA_febex[i]->GetYaxis()->SetTitle("dE MUSIC(41)");
        h2_MUSIC41_vs_LISA_febex[i]->SetOption("COLZ");
    }
    //.......................
    // ::: MWD
    dir_mwd->cd();
    //      MUSIC 21 - LISA MWD
    h2_MUSIC21_vs_LISA_MWD.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_MUSIC21_vs_LISA_MWD[i] = new TH2F(Form("h2_MUSIC(21)_vs_LISA_%i_MWD",i), Form("dE MUSIC(21) vs dE(LISA) %i MWD",i), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, bin_21, min_21, max_21);
        h2_MUSIC21_vs_LISA_MWD[i]->GetXaxis()->SetTitle(Form("dE(LISA) MWD - Layer %i",i));
        h2_MUSIC21_vs_LISA_MWD[i]->GetYaxis()->SetTitle("dE MUSIC(21)");
        h2_MUSIC21_vs_LISA_MWD[i]->SetOption("COLZ");
    }
    //.......................
    //      MUSIC 41 - LISA MWD
    h2_MUSIC41_vs_LISA_MWD.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        h2_MUSIC41_vs_LISA_MWD[i] = new TH2F(Form("h2_MUSIC(41)_vs_LISA_%i_MWD",i), Form("dE MUSIC(41) vs dE(LISA) %i MWD",i), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, bin_41, min_41, max_41);
        h2_MUSIC41_vs_LISA_MWD[i]->GetXaxis()->SetTitle(Form("dE(LISA) MWD - Layer %i",i));
        h2_MUSIC41_vs_LISA_MWD[i]->GetYaxis()->SetTitle("dE MUSIC(41)");
        h2_MUSIC41_vs_LISA_MWD[i]->SetOption("COLZ");
    }
    //.......................

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

    if (!FrsGates.empty())
    {
        //Full sequential gate of FRS
        h2_LISA_energy_vs_layer_s1s2s4_gated.resize(FrsGates.size());
        h2_LISA_energy_MWD_vs_layer_s1s2s4_gated.resize(FrsGates.size());
        h2_LISA_energy_xy_vs_layer_s1s2s4_gated.resize(FrsGates.size());
        h2_LISA_energy_MWD_xy_vs_layer_s1s2s4_gated.resize(FrsGates.size());
        
        h1_LISA_energy_s1s2s4_gated.resize(FrsGates.size());
        h1_LISA_energy_MWD_s1s2s4_gated.resize(FrsGates.size());

        h1_LISA_energy_xy_s1s2s4_gated.resize(FrsGates.size());
        h1_LISA_energy_MWD_xy_s1s2s4_gated.resize(FrsGates.size());

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

            h2_LISA_energy_vs_layer_s1s2_gated[gate_frs] = new TH2F(Form("h2_energy_vs_layer_s1s2_gate_%i",gate_frs),
                                                            Form("Energy vs Layer ID - s1s2 Gate %i",gate_frs), 
                                                            layer_number, 0.5, layer_number + 0.5, 
                                                            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy);
            h2_LISA_energy_vs_layer_s1s2_gated[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_vs_layer_s1s2_gated[gate_frs]->GetYaxis()->SetTitle("LISA Energy [a.u.]");
            h2_LISA_energy_vs_layer_s1s2_gated[gate_frs]->SetOption("COLZ");
            
            h1_LISA_energy_s1s2s4_gated[gate_frs].resize(layer_number);
            h1_LISA_energy_s1s2_gated[gate_frs].resize(layer_number);
            for (int i = 0; i < layer_number; i++) 
            {
                h1_LISA_energy_s1s2s4_gated[gate_frs][i] = MakeTH1(dir_FRS_febex_gates[gate_frs], "F",
                    Form("h1_LISA_%i_energy_s1s2s4_gated_%i", i+1, gate_frs),
                    Form("LISA %i Energy - s1s2s4 Gate %i", i+1, gate_frs),
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
            h1_LISA_energy_xy_s1s2_gated[gate_frs].resize(layer_number);

            for (int i = 0; i < layer_number; i++) 
            {
                h1_LISA_energy_xy_s1s2s4_gated[gate_frs][i] = MakeTH1(dir_FRS_febex_gates_channel[gate_frs], "F",
                    Form("h1_LISA_%i%i%i_energy_s1s2s4_gated_%i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                    Form("LISA %i%i%i Energy - s1s2s4 Gate %i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
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

            h2_LISA_energy_MWD_vs_layer_s1s2_gated[gate_frs] = new TH2F(Form("h2_energy_MWD_vs_layer_s1s2gate_%i",gate_frs), 
                                                        Form("Energy MWD vs Layer ID - s1s2 Gate %i",gate_frs), 
                                                        layer_number, 0.5, layer_number + 0.5, 
                                                        lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_vs_layer_s1s2_gated[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_vs_layer_s1s2_gated[gate_frs]->GetYaxis()->SetTitle("LISA MWD Energy [a.u.]");
            h2_LISA_energy_MWD_vs_layer_s1s2_gated[gate_frs]->SetOption("COLZ");
            
            h1_LISA_energy_MWD_s1s2s4_gated[gate_frs].resize(layer_number);
            h1_LISA_energy_MWD_s1s2_gated[gate_frs].resize(layer_number);
            for (int i = 0; i < layer_number; i++) 
            {
                h1_LISA_energy_MWD_s1s2s4_gated[gate_frs][i] = MakeTH1(dir_FRS_mwd_gates[gate_frs], "F",
                Form("h1_LISA_%i_energy_MWD_s1s2s4_gate_%i", i+1, gate_frs),
                Form("LISA %i Energy MWD - s1s2s4 Gate %i", i+1, gate_frs),
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

            h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated[gate_frs] = new TH2F(Form("h2_LISA_energy_MWD_%i%i_vs_layer_s1s2_gate_%i",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs), 
                                                                    Form("Energy %i%i vs Layer ID - s1s2 Gate %i",lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs), 
                                                                    layer_number, 0.5, layer_number + 0.5, 
                                                                    lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD);
            h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated[gate_frs]->GetXaxis()->SetTitle("Layer ID");
            h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated[gate_frs]->GetYaxis()->SetTitle(Form("LISA %i%i Energy MWD [a.u.]",lisa_config->xpos_gate, lisa_config->ypos_gate));
            h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated[gate_frs]->SetOption("COLZ");

            h1_LISA_energy_MWD_xy_s1s2s4_gated[gate_frs].resize(layer_number);
            h1_LISA_energy_MWD_xy_s1s2_gated[gate_frs].resize(layer_number);

            for (int i = 0; i < layer_number; i++) 
            {
                h1_LISA_energy_MWD_xy_s1s2s4_gated[gate_frs][i] = MakeTH1(dir_FRS_mwd_gates_channel[gate_frs], "F",
                Form("h1_LISA_%i%i%i_energy_MWD_s1s2s4_gate_%i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
                Form("LISA %i%i%i Energy MWD - s1s2s4 Gate %i", i+1,lisa_config->xpos_gate, lisa_config->ypos_gate, gate_frs),
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

    // ::: Gates LISA applied ON FRS
    // ::: These are histos of FRS gated only with the conditions on LISA
    //      Febex gates
    dir_LISA_febex_gates = new TDirectory*[gate_number];
    dir_LISA_febex_gates_channel = new TDirectory*[gate_number];
    if (!febex_gates.empty())
    {
        h2_Z21_vs_AoQs1s2_LISA_gated.resize(gate_number);
        h2_Z41_vs_AoQs2s4_LISA_gated.resize(gate_number);
        for (int gate_lisa = 0; gate_lisa < febex_gates.size(); gate_lisa++)
        {
            dir_LISA_febex_gates[gate_lisa] = dir_gate_LISA_febex->mkdir(TString(febex_gates.at(gate_lisa)->GetName()));
            
            h2_Z21_vs_AoQs1s2_LISA_gated[gate_lisa].resize(layer_number);
            h2_Z41_vs_AoQs2s4_LISA_gated[gate_lisa].resize(layer_number);

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
        for (int gate_lisa = 0; gate_lisa < mwd_gates.size(); gate_lisa++)
        {       
            dir_LISA_mwd_gates[gate_lisa] = dir_gate_LISA_mwd->mkdir(TString(mwd_gates.at(gate_lisa)->GetName()));
            
            h2_Z21_vs_AoQs1s2_LISA_MWD_gated[gate_lisa].resize(layer_number);
            h2_Z41_vs_AoQs2s4_LISA_MWD_gated[gate_lisa].resize(layer_number);
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
            } 

        }
    }   
    //............................

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
        
        h2_LISA_energy_vs_layer_LISA_s1s2_gated.resize(pair_count);
        h2_LISA_energy_xy_vs_layer_LISA_s1s2_gated.resize(pair_count);

        h1_LISA_energy_LISA_s1s2_gated.resize(pair_count);
        h1_LISA_energy_xy_LISA_s1s2_gated.resize(pair_count);

        h2_LISA_energy_vs_layer_LISA_s1s2s4_gated.resize(pair_count);
        h2_LISA_energy_xy_vs_layer_LISA_s1s2s4_gated.resize(pair_count);

        h1_LISA_energy_LISA_s1s2s4_gated.resize(pair_count);
        h1_LISA_energy_xy_LISA_s1s2s4_gated.resize(pair_count);
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
            
            h1_LISA_energy_LISA_s1s2_gated[i].resize(layer_number);
            h1_LISA_energy_LISA_s1s2s4_gated[i].resize(layer_number);

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

            h1_LISA_energy_xy_LISA_s1s2_gated[i].resize(layer_number);
            h1_LISA_energy_xy_LISA_s1s2s4_gated[i].resize(layer_number);
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
            }
        }
    }

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
            }
        }
    }
    //..........................

 
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

    // ::: Positions
    // //S2 Position x-y
    // s2_x = frsHitItem.Get_ID_x2();
    // s2_y = frsHitItem.Get_ID_y2();
    // //c4LOG(info, "s2 x : " << s2_x << "s2 y : " << s2_y);

    // ::: LISA energy
    std::vector<std::vector<float>> energy_layer(layer_number);
    energy_layer.resize(layer_number);

    std::vector<std::vector<float>> energy_MWD_layer(layer_number);
    energy_MWD_layer.resize(layer_number);

    // ::: Energy gated - Layer

    std::vector<float> energy_layer_gated[gate_number][layer_number];
    std::vector<float> energy_MWD_layer_gated[mwd_gate_number][layer_number];

    // ::: Energy gated - Channel
    std::vector<float> energy_xy_gated[gate_number][layer_number][xmax][ymax];
    std::vector<float> energy_MWD_xy_gated[mwd_gate_number][layer_number][xmax][ymax];
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
    std::vector<Float_t> dEdeg_z41_mhtdc = multihitItem.Get_ID_dEdeg_z41_mhtdc();
    Float_t x2_position = frsHitItem.Get_ID_x2();
    Float_t x4_position = frsHitItem.Get_ID_x4();
    Float_t sci42e = frsHitItem.Get_sci_e_42();

    

    // //c4LOG(info, "s2 x : " << s2_x << "s2 y : " << s2_y);

    // std::vector<uint32_t> energy_layer_GM;
    // energy_layer_GM.resize(layer_number);

    // uint32_t energy_ch_GM[layer_number][xmax][ymax] = {0,0,0};

    // // Energy from frs
    // // energy_travMUSIC_driftcorr = travMusicHitItem.Get_travmusic_dE_driftcorr();
    // energy_travMUSIC_driftcorr = 0; //
    // // double z21_driftcorr = frsHitItem.Get_ID_z21_driftcorr();



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

        // ::: Data
        layer = lisaCalItem.Get_layer_id();
        city = lisaCalItem.Get_city();
        int xpos = lisaCalItem.Get_xposition();
        int ypos = lisaCalItem.Get_yposition();

        float energy_LISA_febex = lisaCalItem.Get_energy_GM();
        float energy_LISA_MWD = lisaCalItem.Get_energy_MWD_GM();

        if (excluded.count(std::make_tuple(layer, xpos, ypos)) != 0) continue;

        energy_layer[layer-1].emplace_back(energy_LISA_febex);
        energy_MWD_layer[layer-1].emplace_back(energy_LISA_MWD);

        // Loop over gates for LISA FEBEX
        int g = 0;
        for (auto & gate : febex_gates)
        {
            if (gate->PassedGate(layer, energy_LISA_febex))
            {
                energy_layer_gated[g][layer-1].push_back( energy_LISA_febex);
                energy_xy_gated[g][layer-1][xpos][ypos].push_back( energy_LISA_febex);
            }
            g++;
        }
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

        // ::: Position Correlation
        
        // if (layer == 1)
        // {
        //     h2_xy_pos_layer1[0]->Fill(xpos,s2_x);
        //     h2_xy_pos_layer1[1]->Fill(ypos,s2_y);
        // }

        // if (layer == 2)
        // {
        //     h2_xy_pos_layer2[0]->Fill(xpos,s2_x);
        //     h2_xy_pos_layer2[1]->Fill(ypos,s2_y);
        // }
        //..........................

        // ::: FRS Gates applied on LISA (FRS_ON_LISA Directory)
        int mh_counter_passed_s1s2[FrsGates.size()] = {0};
        int mh_counter_passed_s2s4[FrsGates.size()] = {0};
        if (!FrsGates.empty())
        {
            for (int gate = 0; gate < FrsGates.size(); gate++)
            {    
                // Loop for S1S2
                for (int i = 0; i < AoQ_s1s2_mhtdc.size(); i++)
                {
                    if (mh_counter_passed_s1s2[gate] > 0) break;
                    if (FrsGates[gate]->PassedS1S2(z21_mhtdc.at(i), x2_position, AoQ_s1s2_mhtdc.at(i)))
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
                        mh_counter_passed_s1s2[gate]++;
                    }                   
                }
                // Full sequential gate loop
                for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
                {
                    if (mh_counter_passed_s2s4[gate] > 0) break;
                    if (FrsGates[gate]->PassedS2S4(z41_mhtdc.at(i), z42_mhtdc.at(i), x2_position, x4_position, AoQ_s2s4_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), sci42e))
                    {
                        if (mh_counter_passed_s1s2[gate] > 0)
                        //if (1) //just for testing when we don't have S1S2 data
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
                        mh_counter_passed_s2s4[gate]++;
                    }                   
                }
            }            
        } 
        multi_evt++;
        //..........................
        
    }
    
    // ::: T I M E - WR differences
    wr_LISA_FRS = wr_LISA - wr_FRS;
    wr_LISA_travMUSIC = wr_LISA - wr_travMUSIC;
    wr_travMUSIC_FRS = wr_travMUSIC - wr_FRS;
    
    if(wr_travMUSIC == 0) return;
    h1_wr_diff[2]->Fill(wr_travMUSIC_FRS);

    if(wr_travMUSIC == 0) return;
    h1_wr_diff[1]->Fill(wr_LISA_travMUSIC);

    if (wr_FRS != 0 && wr_LISA != 0) h1_wr_diff[0]->Fill(wr_LISA_FRS);
    //............................

    // ::: E N E R G Y  - LISA vs MUSICs
    for (int i = 0; i < layer_number; i++)
    {
        for (int j = 0; j < energy_layer[i].size(); j++)
        {
            // MUSIC 21
            h2_MUSIC21_vs_LISA_febex[i]->Fill(energy_layer[i][j],energy_MUSIC_21);
            // MUSIC 41
            h2_MUSIC41_vs_LISA_febex[i]->Fill(energy_layer[i][j],energy_MUSIC_41);
        }

        for (int j = 0; j < energy_MWD_layer[i].size(); j++)
        {
            // MUSIC 21
            h2_MUSIC21_vs_LISA_MWD[i]->Fill(energy_MWD_layer[i][j],energy_MUSIC_21);
            // MUSIC 41
            h2_MUSIC41_vs_LISA_MWD[i]->Fill(energy_MWD_layer[i][j],energy_MUSIC_41);
        }

    }
    //............................

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
            }            
        }
    }
    //............................

    // ::: LISA-FRS gates applied on LISA (LISA_FRS Directory)
    // ::: Febex
    //pair_count = std::min(febex_gates.size(), FrsGates.size());
    int mh_counter_passed_s1s2_seq[pair_count] = {0};
    int mh_counter_passed_s2s4_seq[pair_count] = {0};

    for (int pair = 0; pair < pair_count; pair++)  
    {
        for (int l = 0; l < layer_number; l++) 
        {
            // Check condition on Febex Gate
            if (energy_layer_gated[pair][l].size() == 0) break;  
            for (int i = 0; i < AoQ_s1s2_mhtdc.size(); i++)
            {
                if (mh_counter_passed_s1s2_seq[pair] > 0) break;
                if (FrsGates[pair]->PassedS1S2(z21_mhtdc.at(i), x2_position, AoQ_s1s2_mhtdc.at(i)))
                {
                    for ( int j = 0; j < energy_layer_gated[pair][l].size(); j++)
                    {
                        // Febex
                        h2_LISA_energy_vs_layer_LISA_s1s2_gated[pair]->Fill(layer, energy_layer_gated[pair][l].at(j));
                        h1_LISA_energy_LISA_s1s2_gated[pair][l]->Fill(energy_layer_gated[pair][l].at(j));   
                    }

                    for ( int k = 0; k < energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].size(); k++ )
                    {
                        // Febex XY
                        h2_LISA_energy_xy_vs_layer_s1s2_gated[pair]->Fill(layer, energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                        h1_LISA_energy_xy_s1s2_gated[pair][l]->Fill(energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                    }

                    mh_counter_passed_s1s2_seq[pair]++;
                }                   
            }
            // Loop for sequential gate S1S2S4
            for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
            {
                if (mh_counter_passed_s2s4_seq[pair] > 0) break;
                if (FrsGates[pair]->PassedS2S4(z41_mhtdc.at(i), z42_mhtdc.at(i), x2_position, x4_position, AoQ_s2s4_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), sci42e))
                {
                    if (mh_counter_passed_s1s2_seq[pair] > 0)
                    //if (1)
                    {
                        for ( int j = 0; j < energy_layer_gated[pair][l].size(); j++)
                        {
                            // Febex
                            h2_LISA_energy_vs_layer_LISA_s1s2s4_gated[pair]->Fill(layer, energy_layer_gated[pair][l].at(j));
                            h1_LISA_energy_LISA_s1s2s4_gated[pair][l]->Fill(energy_layer_gated[pair][l].at(j));   
                        }

                        for ( int k = 0; k < energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].size(); k++ )
                        {
                            // Febex XY
                            h2_LISA_energy_xy_vs_layer_s1s2s4_gated[pair]->Fill(layer, energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                            h1_LISA_energy_xy_s1s2s4_gated[pair][l]->Fill(energy_xy_gated[pair][l][lisa_config->xpos_gate][lisa_config->ypos_gate].at(k));
                        }
                    }
                    mh_counter_passed_s2s4_seq[pair]++;
                }                   
            }
                
        }
    }
    // ::: MWD 
    int pair_count_mwd = std::min(mwd_gates.size(), FrsGates.size());
    int mh_counter_passed_s1s2_seq_mwd[pair_count_mwd] = {0};
    int mh_counter_passed_s2s4_seq_mwd[pair_count_mwd] = {0};

    for (int pair = 0; pair < pair_count; pair++)  
    {
        for (int l = 0; l < layer_number; l++) 
        {
            // Check condition on Febex Gate
            if (energy_MWD_layer_gated[pair][l].size() == 0) break;  
            // Loop for S1S2
            for (int i = 0; i < AoQ_s1s2_mhtdc.size(); i++)
            {
                if (mh_counter_passed_s1s2_seq_mwd[pair] > 0) break;
                if (FrsGates[pair]->PassedS1S2(z21_mhtdc.at(i), x2_position, AoQ_s1s2_mhtdc.at(i)))
                {
                    //h2_LISA_energy_MWD_vs_layer_LISA_s1s2_gated[pair]->Fill(layer, energy_MWD_layer_gated[pair][l-1]);
                    //h1_LISA_energy_MWD_LISA_s1s2_gated[pair][layer-1]->Fill(energy_MWD_layer_gated[pair][layer-1]);
                    
                    //h2_LISA_energy_MWD_xy_vs_layer_s1s2_gated[pair]->Fill(layer, energy_MWD_layer_gated[pair][layer-1][lisa_config->xpos_gate][lisa_config->ypos_gate]);
                    //h1_LISA_energy_MWD_xy_s1s2_gated[pair][layer-1]->Fill(energy_MWD_layer_gated[pair][layer-1][lisa_config->xpos_gate][lisa_config->ypos_gate]);
                
                    mh_counter_passed_s1s2_seq_mwd[pair]++;
                }                   
            }
            // Loop for sequential gate S1S2S4
            for (int i = 0; i < AoQ_s2s4_mhtdc.size(); i++)
            {
                if (mh_counter_passed_s2s4_seq[pair] > 0) break;
                if (FrsGates[pair]->PassedS2S4(z41_mhtdc.at(i), z42_mhtdc.at(i), x2_position, x4_position, AoQ_s2s4_mhtdc.at(i), dEdeg_z41_mhtdc.at(i), sci42e))
                {
                    if (mh_counter_passed_s1s2_seq_mwd[pair] > 0)
                    {

                    }
                    mh_counter_passed_s2s4_seq_mwd[pair]++;
                }                   
            }
                
        }
    } 
    //............................

    fNEvents++;

}

void LisaFrsCorrelations::FinishEvent()
{

}

void LisaFrsCorrelations::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_corr->Write();
    //dir_corr_driftcorr->Write();
    c4LOG(info, "Written LISA analysis histograms to file.");
    //c4LOG(info, "Multi hit events when LISA is in the event (correlated) : " <<  multi_evt++ << " LISA-FRS events : " << fNEvents);


}


ClassImp(LisaFrsCorrelations)