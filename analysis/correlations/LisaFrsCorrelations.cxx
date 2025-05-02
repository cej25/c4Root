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

    FairRootManager::Instance()->GetOutFile()->cd();
    dir_corr = gDirectory->mkdir("LISA-FRS_Correlations");
    dir_time = dir_corr->mkdir("Time");
    // dir_position = dir_corr->mkdir("Position");
    // dir_energy = dir_corr->mkdir("Energy");
    // dir_energy_ch = dir_energy->mkdir("Channels");
    // dir_energy_MWD = dir_corr->mkdir("Energy_MWD");
    // dir_energy_MWD_ch = dir_energy_MWD->mkdir("Channels");
    //dir_corr_driftcorr = dir_corr->mkdir("DriftCorrected");
    //dir_energy_ch_driftcorr = dir_corr_driftcorr->mkdir("Energy_Channel_DriftCorr");
 
    dir_time->cd();
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::::::: WR Time differences ::::::::::::::::::::::
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


    //dir_position->cd();
    //FRS position vs LISA position
    //::::::::::::: Layer 1 ::::::::::::::::::
    // h2_xy_pos_layer1.resize(2);
    // for (int i = 0; i < 2; i++)
    // {
    //     //c_xy_pos_layer1->cd(i+1);
    //     h2_xy_pos_layer1[i] = new TH2F(Form("h2_FRS_vs_LISA_Position_%i_Layer_1",i), Form("FRS vs LISA Position %i Layer 1",i), 2, 0, 2, 400,-50,50);//change lisa range from macro - sim to sum energy for our online
    //     h2_xy_pos_layer1[i]->GetXaxis()->SetTitle(Form("LISA - Position %i Layer 1",i));
    //     h2_xy_pos_layer1[i]->GetYaxis()->SetTitle(Form("FRS Position %i",i));
    //     //h2_xy_position[i]->SetStats(0);
    //     h2_xy_pos_layer1[i]->SetOption("colz");
    // }
   
    // //FRS position vs LISA position
    // //::::::::::::: Layer 2 ::::::::::::::::::
    // h2_xy_pos_layer2.resize(2);
    // for (int i = 0; i < 2; i++)
    // {
    //     h2_xy_pos_layer2[i] = new TH2F(Form("h2_FRS_vs_LISA_Position_%i_Layer_2",i), Form("FRS vs LISA Position %i Layer 2",i), 2, 0, 2, 300,-100,100);//change lisa range from macro - sim to sum energy for our online
    //     h2_xy_pos_layer2[i]->GetXaxis()->SetTitle(Form("LISA - Position %i Layer 2",i));
    //     h2_xy_pos_layer2[i]->GetYaxis()->SetTitle(Form("FRS Position %i",i));
    //     //h2_xy_position[i]->SetStats(0);
    //     h2_xy_pos_layer2[i]->SetOption("colz");
    // }
   
    //dir_energy->cd();
    //MUSIC 1 - LISA GM
    //:::::::::::::::::::::::::::::::
    // h2_MUSIC_1_layer_GM.resize(layer_number);
    // for (int i = 0; i < layer_number; i++)
    // {
    //     h2_MUSIC_1_layer_GM[i] = new TH2F(Form("h2_MUSIC(1)_vs_E(LISA)_GM_Layer_%i",i), Form("MUSIC(1) vs E(LISA) GM Layer %i",i), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM, 400,0,4096);
    //     h2_MUSIC_1_layer_GM[i]->GetXaxis()->SetTitle(Form("E(LISA) [MeV] - Layer %i",i));
    //     h2_MUSIC_1_layer_GM[i]->GetYaxis()->SetTitle("dE MUSIC(1)");
    //     h2_MUSIC_1_layer_GM[i]->SetOption("colz");
    // }

    // //MUSIC 2 VS LISA GM
    // //:::::::::::::::::::::::::::::::
    // h2_MUSIC_2_layer_GM.resize(layer_number);
    // for (int i = 0; i < layer_number; i++)
    // {
    //     h2_MUSIC_2_layer_GM[i] = new TH2F(Form("h2_MUSIC(2)_vs_E(LISA)_GM_Layer_%i",i), Form("MUSIC(2) vs E(LISA) GM Layer %i",i), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM, 400,0,4096);
    //     h2_MUSIC_2_layer_GM[i]->GetXaxis()->SetTitle(Form("E(LISA) [MeV] - Layer %i",i));
    //     h2_MUSIC_2_layer_GM[i]->GetYaxis()->SetTitle("dE MUSIC(2)");
    //     h2_MUSIC_2_layer_GM[i]->SetOption("colz");
    // }

    // //travMUSIC VS LISA
    // h2_travMUSIC_layer_GM.resize(layer_number);
    // for (int i = 0; i < layer_number; i++)
    // {
    //     h2_travMUSIC_layer_GM[i] = new TH2F(Form("h2_travMUSIC_vs_E(LISA)_GM_Layer_%i",i), Form("travMUSIC vs E(LISA) GM Layer %i",i), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM, 1000,0,4096);
    //     h2_travMUSIC_layer_GM[i]->GetXaxis()->SetTitle(Form("E(LISA) [MeV] - Layer %i",i));
    //     h2_travMUSIC_layer_GM[i]->GetYaxis()->SetTitle("dE travMUSIC");
    //     h2_travMUSIC_layer_GM[i]->SetOption("colz");
    // }

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
    // dir_energy->cd();
    //::: L I S A   E N E R G Y   G A T E D   O N   F R S :::
    // if (!FrsGates.empty())
    // {
    //     //Energy GainMatched and calibrated gated on ROI on ZvsAoQ, for each detector
    //     h1_energy_ch_GM_PIDgated.resize(FrsGates.size());

    //     //Energy GM and calibrated gated on ROI on ZvsAoQ & Trav Music, for each detector
    //     h1_energy_ch_GM_PIDgated_Trav.resize(FrsGates.size());

    //     //Energy GM and calibrated gated on ROI on ZvsAoQ & Trav Music, 
    //     //for each layer and the total stats of the detector on layer
    //     h1_energy_layer_GM_PID_TM.resize(FrsGates.size());

    //     //Energy of Layer2 gated on PID,trav, and 98Nb in LISA1
    //     h1_energy_layer2_GM_PID_TM_LISA1.resize(FrsGates.size());
    
    //     dir_tokyo->cd();
    //     for (int gate = 0; gate < FrsGates.size(); gate++)
    //     {
            
    //         // //::: Energy spectra Gated with FRS for Layer 0 (Tokyo)
    //         h1_energy_ch_GM_PIDgated[gate].resize(layer_number);
    //         // h1_energy_ch_GM_PIDgated[gate][0].resize(1);
    //         // h1_energy_ch_GM_PIDgated[gate][0][0].resize(1);
    //         // h1_energy_ch_GM_PIDgated[gate][0][0][0] = new TH1F(Form("h1_energy_000_GM_PIDgated_%i",gate), "Tokyo", lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);

    //         h1_energy_ch_GM_PIDgated_Trav[gate].resize(layer_number);
    //         // h1_energy_ch_GM_PIDgated_Trav[gate][0].resize(1);
    //         // h1_energy_ch_GM_PIDgated_Trav[gate][0][0].resize(1);
    //         // h1_energy_ch_GM_PIDgated_Trav[gate][0][0][0] = new TH1F(Form("h1_energy_000_GM_PIDgated%i_T",gate), "Tokyo T", lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);

    //         h1_energy_layer_GM_PID_TM[gate].resize(layer_number);
    //         // h1_energy_layer_GM_PID_TM[gate][0] = new TH1F(Form("h1_energy_Layer0_GM_PIDgated%i_Trav",gate), "Tokyo T", lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);

    //         h1_energy_layer2_GM_PID_TM_LISA1[gate].resize(layer_number);
    //         // h1_energy_layer2_GM_PID_TM_LISA1[gate][0] = new TH1F(Form("h1_energy_Layer0_GM_PIDgated%i_TM_LISA1",gate), "Tokyo T+PID+LISA", lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);
    //         // //c4LOG(info," after 000 ");

    //         //::: Energy spectra Gated with FRS for Layer 1 and 2
    //         for (int i = 0; i < layer_number; i++) 
    //         {
    //             //:::For each layer
    //             //Energy GM gated on PID, for all detectors
    //             h1_energy_ch_GM_PIDgated[gate][i].resize(xmax);
    //             //Energy GM gated on PID&TravMus, for all detectors
    //             h1_energy_ch_GM_PIDgated_Trav[gate][i].resize(xmax);

    //             dir_energy->cd();
    //             //Energy GM gated on PID&TravMus, for each layer 
    //             //summed stats between detectors
    //             h1_energy_layer_GM_PID_TM[gate][i] = new TH1F(Form("h1_energy_layer_%i_GM_PIDgate_%i_Trav", i, gate), Form("Energy Layer %i gated on PID and TM",i), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);             
    //             h1_energy_layer_GM_PID_TM[gate][i]->GetXaxis()->SetTitle(Form("E(LISA) Layer %i [MeV]",i));
    //             h1_energy_layer_GM_PID_TM[gate][i]->SetLineColor(i);
    //             h1_energy_layer_GM_PID_TM[gate][i]->SetFillColor(i);

    //             //Energy of LISA layer gated on PID, TM and LISA
    //             h1_energy_layer2_GM_PID_TM_LISA1[gate][i] = new TH1F(Form("h1_energy_layer_%i_GM_PID_%i_TM_LISA1", i, gate), Form("Energy Layer %i gated on PID-TM-LISA1",i), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);             
    //             h1_energy_layer2_GM_PID_TM_LISA1[gate][i]->GetXaxis()->SetTitle(Form("E(LISA) Layer %i [MeV]",i));
    //             h1_energy_layer2_GM_PID_TM_LISA1[gate][i]->SetLineColor(i+2);
    //             h1_energy_layer2_GM_PID_TM_LISA1[gate][i]->SetFillColor(i+2);

    //             dir_energy_ch->cd();
    //             //:::For each detector
    //             for (int j = 0; j < xmax; j++)
    //             {
    //                 h1_energy_ch_GM_PIDgated[gate][i][j].resize(ymax);
    //                 h1_energy_ch_GM_PIDgated_Trav[gate][i][j].resize(ymax);

    //                 for (int k = 0; k < ymax; k++)
    //                 {                           
    //                     city = "";
    //                     for (auto & detector : detector_mapping)
    //                     {
    //                         if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
    //                         {
    //                             city = detector.second.first.second;
    //                             break;
    //                         }
    //                     }
                        
    //                     h1_energy_ch_GM_PIDgated[gate][i][j][k] = new TH1F(Form("h1_energy_%i_%i_%i_GM_PIDgate_%i", i, j, k, gate), Form("%i%i%i PID%i",i,j,k,gate), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);
    //                     h1_energy_ch_GM_PIDgated[gate][i][j][k]->GetXaxis()->SetTitle("E(LISA) [MeV]");
    //                     h1_energy_ch_GM_PIDgated[gate][i][j][k]->SetLineColor(kBlack);
    //                     h1_energy_ch_GM_PIDgated[gate][i][j][k]->SetFillColor(kBlue);

    //                     h1_energy_ch_GM_PIDgated_Trav[gate][i][j][k] = new TH1F(Form("h1_energy_%i_%i_%i_GM_PIDgate_%i_Trav", i, j, k, gate), Form("%i%i%i PID%i",i,j,k,gate) , lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);
    //                     h1_energy_ch_GM_PIDgated_Trav[gate][i][j][k]->GetXaxis()->SetTitle("E(LISA) [MeV]");
    //                     h1_energy_ch_GM_PIDgated_Trav[gate][i][j][k]->SetLineColor(kBlack);
    //                     h1_energy_ch_GM_PIDgated_Trav[gate][i][j][k]->SetFillColor(kRed-3);                        

    //                 }
    //             }
                
    //         }
            
            
    //     }

    //}

    // dir_corr_driftcorr->cd();
    // //::: FRS gate on Drift Corrected data
    // if (!FrsGates.empty())
    // {
    //     //Energy gated and calibrated gated on ROI on ZvsAoQ & Trav Music, for each detector
    //     h1_energy_ch_GM_PID_TM_driftcorr.resize(FrsGates.size());               //drift corrected

    //     //Energy gated and calibrated gated on ROI on ZvsAoQ & Trav Music, 
    //     //for each layer and the total stats of the detector on layer
    //     h1_energy_layer_GM_PID_driftcorr.resize(FrsGates.size());               //drift corrected
    //     h1_energy_layer_GM_PID_TM_driftcorr.resize(FrsGates.size());            //drift corrected

    //     //Energy of Layer2 gated on PID,trav, and 98Nb in LISA1
    //     h1_energy_layer2_GM_PID_TM_driftcorr_LISA1.resize(FrsGates.size());     //drift corrected
        
    //     h1_energy_ch201_GM_PID_TM_driftcorr_ch101.resize(FrsGates.size());      //drift corrected

    
    //     for (int gate = 0; gate < FrsGates.size(); gate++)
    //     {
    //         dir_tokyo->cd();
    //         //::: Drift Corrected :::
    //         //::: Energy spectra Gated with FRS for Layer 0 (Tokyo) 
    //         h1_energy_ch_GM_PID_TM_driftcorr[gate].resize(layer_number);
    //         h1_energy_ch_GM_PID_TM_driftcorr[gate][0].resize(1);
    //         h1_energy_ch_GM_PID_TM_driftcorr[gate][0][0].resize(1);
    //         h1_energy_ch_GM_PID_TM_driftcorr[gate][0][0][0] = new TH1F(Form("h1_energy_000_GM_PID%i_TM_driftcorr",gate), "Tokyo T", lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);

    //         h1_energy_layer_GM_PID_TM_driftcorr[gate].resize(layer_number);
    //         h1_energy_layer_GM_PID_TM_driftcorr[gate][0] = new TH1F(Form("h1_energy_0_GM_PID%i_TM_driftcorr",gate), "Tokyo T", lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);

    //         h1_energy_layer_GM_PID_driftcorr[gate].resize(layer_number);
    //         h1_energy_layer_GM_PID_driftcorr[gate][0] = new TH1F(Form("h1_energy_0_GM_PID%i_driftcorr",gate), "Tokyo T", lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);

    //         h1_energy_layer2_GM_PID_TM_driftcorr_LISA1[gate].resize(layer_number);
    //         h1_energy_layer2_GM_PID_TM_driftcorr_LISA1[gate][0] = new TH1F(Form("h1_energy_0_GM_PID%i_TM_driftcorrLISA1",gate), "Tokyo T+PID+LISA", lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);
            
    //         h1_energy_ch201_GM_PID_TM_driftcorr_ch101[gate].resize(layer_number);
    //         h1_energy_ch201_GM_PID_TM_driftcorr_ch101[gate][0].resize(1);
    //         h1_energy_ch201_GM_PID_TM_driftcorr_ch101[gate][0][0].resize(1);
    //         h1_energy_ch201_GM_PID_TM_driftcorr_ch101[gate][0][0][0] = new TH1F(Form("h1_energy_201_GM_PID%i_TM_driftcorrch101",gate), "Tokyo T+PID+c101", lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);
    //         //c4LOG(info," after 000 ");
    //         //::: Energy spectra Gated with FRS for Layer 1 and 2
    //         for (int i = 1; i < layer_number; i++) 
    //         {
                
    //             //:::For each layer
    //             //Energy GM gated on PID&TravMus, for all detectors
    //             dir_corr_driftcorr->cd();
    //             h1_energy_layer_GM_PID_driftcorr[gate][i] = new TH1F(Form("h1_energy_layer_%i_GM_PID%i_driftcorr", i, gate), Form("Energy Layer %i gated on PID DriftCorr",i), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);             
    //             h1_energy_layer_GM_PID_driftcorr[gate][i]->GetXaxis()->SetTitle(Form("E(LISA) Layer %i [MeV]",i));
    //             h1_energy_layer_GM_PID_driftcorr[gate][i]->SetLineColor(i);
    //             h1_energy_layer_GM_PID_driftcorr[gate][i]->SetFillColor(i);

    //             //Energy GM gated on PID&TravMus, for each layer 
    //             //summed stats between detectors
    //             h1_energy_layer_GM_PID_TM_driftcorr[gate][i] = new TH1F(Form("h1_energy_layer_%i_GM_PID%i_TM_driftcorr", i, gate), Form("Energy Layer %i gated on PID+TM DriftCorr",i), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);             
    //             h1_energy_layer_GM_PID_TM_driftcorr[gate][i]->GetXaxis()->SetTitle(Form("E(LISA) Layer %i [MeV]",i));
    //             h1_energy_layer_GM_PID_TM_driftcorr[gate][i]->SetLineColor(i);
    //             h1_energy_layer_GM_PID_TM_driftcorr[gate][i]->SetFillColor(i);

    //             //Energy of LISA layer gated on PID, TM and LISA
    //             h1_energy_layer2_GM_PID_TM_driftcorr_LISA1[gate][i] = new TH1F(Form("h1_energy_layer_%i_GM_PID%i_TM_LISA1", i, gate), Form("Energy Layer %i gated on PID+TM+LISA1 DriftCorr",i), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);             
    //             h1_energy_layer2_GM_PID_TM_driftcorr_LISA1[gate][i]->GetXaxis()->SetTitle(Form("E(LISA) Layer %i [MeV]",i));
    //             h1_energy_layer2_GM_PID_TM_driftcorr_LISA1[gate][i]->SetLineColor(i+2);
    //             h1_energy_layer2_GM_PID_TM_driftcorr_LISA1[gate][i]->SetFillColor(i+2);

    //             //:::
    //             h1_energy_ch_GM_PID_TM_driftcorr[gate][i].resize(xmax);
    //             h1_energy_ch201_GM_PID_TM_driftcorr_ch101[gate][i].resize(xmax);

    //             //:::For each detector
    //             dir_energy_ch_driftcorr->cd();
    //             for (int j = 0; j < xmax; j++)
    //             {
    //                 h1_energy_ch_GM_PID_TM_driftcorr[gate][i][j].resize(ymax);
    //                 h1_energy_ch201_GM_PID_TM_driftcorr_ch101[gate][i][j].resize(ymax);

    //                 for (int k = 0; k < ymax; k++)
    //                 {                           
    //                     city = "";
    //                     for (auto & detector : detector_mapping)
    //                     {
    //                         if (detector.second.first.first == i && detector.second.second.first == j && detector.second.second.second == k)
    //                         {
    //                             city = detector.second.first.second;
    //                             break;
    //                         }
    //                     }
                        
    //                     h1_energy_ch_GM_PID_TM_driftcorr[gate][i][j][k] = new TH1F(Form("h1_energy_%i_%i_%i_GM_PID%i_TM", i, j, k, gate), Form("%i%i%i",i,j,k), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);
    //                     h1_energy_ch_GM_PID_TM_driftcorr[gate][i][j][k]->GetXaxis()->SetTitle("E(LISA) [MeV]");
    //                     h1_energy_ch_GM_PID_TM_driftcorr[gate][i][j][k]->SetLineColor(kBlack);
    //                     h1_energy_ch_GM_PID_TM_driftcorr[gate][i][j][k]->SetFillColor(kRed-3);

    //                     //Energy of ch201 gated on ch101 all gm and dc
    //                     h1_energy_ch201_GM_PID_TM_driftcorr_ch101[gate][i][j][k] = new TH1F(Form("h1_energy_ch201_%i%i%i_GM_PID%i_TM_ch101", i,j,k,gate), Form("ch201 %i%i%i gated on PID+TM+ch101 DriftCorr",i,j,k), lisa_config->bin_energy_GM, lisa_config->min_energy_GM, lisa_config->max_energy_GM);             
    //                     h1_energy_ch201_GM_PID_TM_driftcorr_ch101[gate][i][j][k]->GetXaxis()->SetTitle(Form("E(LISA) Layer %i [MeV]",i));
    //                     h1_energy_ch201_GM_PID_TM_driftcorr_ch101[gate][i][j][k]->SetLineColor(i+2);
    //                     h1_energy_ch201_GM_PID_TM_driftcorr_ch101[gate][i][j][k]->SetFillColor(i+2); 



    //                 }
    //             }

                
    //         }
            
            
    //     }

    //}

 
    return kSUCCESS;

}



void LisaFrsCorrelations::Exec(Option_t* option)
{   
    // -> Reject events without both subsystems <-
    if (frsHitArray->size() <= 0 || lisaCalArray->size() <= 0) return;  // frs, lisa and travmus subevent exists

    const auto & frsHitItem = frsHitArray->at(0);                       // *should* only be 1 FRS subevent per event
    
    //const auto & multihitItem = multihitArray->at(0);                 // *should* only be 1 FRS subevent per event

    // ::: FRS WR
    Int_t count_wr = 0;
    wr_FRS = frsHitItem.Get_wr_t();
    wr_travMUSIC = frsHitItem.Get_travmus_wr_t();


    // //S2 Position x-y
    // s2_x = frsHitItem.Get_ID_x2();
    // s2_y = frsHitItem.Get_ID_y2();
    // //c4LOG(info, "s2 x : " << s2_x << "s2 y : " << s2_y);

    // std::vector<uint32_t> sum_energy_layer;
    // sum_energy_layer.resize(layer_number);

    // std::vector<uint32_t> sum_energy_layer_GM;
    // sum_energy_layer_GM.resize(layer_number);
    // //c4LOG(info, "s2 x : " << s2_x << "s2 y : " << s2_y);

    // std::vector<uint32_t> energy_layer_GM;
    // energy_layer_GM.resize(layer_number);

    // uint32_t energy_ch_GM[layer_number][xmax][ymax] = {0,0,0};

    // // Energy from frs
    // energy_MUSIC_1 = frsHitItem.Get_music41_dE(); 
    // energy_MUSIC_2 = frsHitItem.Get_music42_dE();
    // energy_travMUSIC = frsHitItem.Get_music21_dE();
    // //energy_travMUSIC = travMusicHitItem.Get_travmusic_dE();
    // // CEJ needs adding
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

        //::::Position
        //int xpos = lisaCalItem.Get_xposition();
        //int ypos = lisaCalItem.Get_yposition();

        //:::::::::::::: FRS - LISA position ::::::::::::::::::::::::::
        //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::   
        
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
        
        //:::: Energy and SumEnergy for LISA
        // uint32_t energy_LISA = lisaCalItem.Get_energy();
        // uint32_t energy_LISA_GM = lisaCalItem.Get_energy_GM();

        // layer = lisaCalItem.Get_layer_id();
        // energy_layer_GM[layer-1] = energy_LISA_GM;
        // sum_energy_layer[layer-1] += energy_LISA;
        // sum_energy_layer_GM[layer-1] += energy_LISA_GM;
        // energy_ch_GM[layer-1][xpos][ypos] = energy_LISA_GM;

        // //::::::::: E N E R G Y GATED MULTI HIT:::::::::::::::
        // int mh_counter = 0;

        // for ( auto const & multihitItem : *multihitArray )
        // {    
        //     if (mh_counter > 0) break;
        //     if (!FrsGates.empty())
        //     {
        //        for (int gate = 0; gate < FrsGates.size(); gate++)
        //         {  
        //             //::: Gate on PID
        //             if (FrsGates[gate]->Passed_ZvsAoQ(multihitItem.Get_ID_z_mhtdc(), multihitItem.Get_ID_AoQ_mhtdc()))
        //             {
        //                 h1_energy_ch_GM_PIDgated[gate][layer][xpos][ypos]->Fill(energy_LISA_GM);

        //                 //::: Gate on Trav Music
        //                 if(frsHitItem.Get_travmusic_dE() >= frs_config->fMin_dE_travMus_gate && frsHitItem.Get_travmusic_dE() <= frs_config->fMax_dE_travMus_gate)
        //                 {   
        //                     h1_energy_ch_GM_PIDgated_Trav[gate][layer][xpos][ypos]->Fill(energy_LISA_GM);
        //                     h1_energy_layer_GM_PID_TM[gate][layer]->Fill(energy_LISA_GM);
        //                 }
        //             }
        //         }
        //     } 
        
        //     mh_counter++;
        //     multi_evt++;
        // }

        //::::::::: E N E R G Y GATED TAC :::::::::::::::
        // if (!FrsGates.empty())
        // {
        //     for (int gate = 0; gate < FrsGates.size(); gate++)
        //     {  
        //         //::: Gate on PID
        //         if (FrsGates[gate]->Passed_Z41vsAoQs2s4(frsHitItem.Get_ID_z41(), frsHitItem.Get_ID_AoQ_s2s4()))
        //         {
        //             h1_energy_ch_GM_PIDgated[gate][layer-1][xpos][ypos]->Fill(energy_LISA_GM);

        //             //::: Gate on Trav Music
        //             if(energy_travMUSIC >= frs_config->fMin_dE_travMus_gate && energy_travMUSIC <= frs_config->fMax_dE_travMus_gate)
        //             {   
        //                 h1_energy_ch_GM_PIDgated_Trav[gate][layer-1][xpos][ypos]->Fill(energy_LISA_GM);
        //                 h1_energy_layer_GM_PID_TM[gate][layer-1]->Fill(energy_LISA_GM);

        //                 //gate on 98Nb in LISA1 for LISA2. On LISA1, 98Nb is at 1090 (+-20)
        //                 if(energy_layer_GM[1] >= lisa_config->fMin_dE_LISA1_gate && energy_layer_GM[1] <= lisa_config->fMax_dE_LISA1_gate)
        //                 {
        //                     h1_energy_layer2_GM_PID_TM_LISA1[gate][layer-1]->Fill(energy_LISA_GM);
        //                 }
                        
        //             }
        //         }
        //     }
        // }

        //::::::::: E N E R G Y GATED TAC DriftCorrected:::::::::::::::
    //     if (!FrsGates.empty())
    //     {
    //         for (int gate = 0; gate < FrsGates.size(); gate++)
    //         {  
    //             //::: Gate on PID
    //             if (FrsGates[gate]->Passed_Z41vsAoQs2s4_driftcorr(frsHitItem.Get_ID_z41_driftcorr(), frsHitItem.Get_ID_AoQs2s4_driftcorr()))
    //             {

    //                 h1_energy_layer_GM_PID_driftcorr[gate][layer-1]->Fill(energy_LISA_GM);
    //                 //::: Gate on Trav Music Drift Corrected
    //                 if(energy_travMUSIC_driftcorr >= frs_config->fMin_dE_travMus_gate && energy_travMUSIC_driftcorr <= frs_config->fMax_dE_travMus_gate)
    //                 {   

    //                     h1_energy_ch_GM_PID_TM_driftcorr[gate][layer-1][xpos][ypos]->Fill(energy_LISA_GM);
    //                     h1_energy_layer_GM_PID_TM_driftcorr[gate][layer-1]->Fill(energy_LISA_GM);

    //                     //gate on 98Nb in LISA1 for LISA2. On LISA1, 98Nb is at 1090 (+-20)
    //                     if(energy_layer_GM[1] >= lisa_config->fMin_dE_LISA1_gate && energy_layer_GM[1] <= lisa_config->fMax_dE_LISA1_gate)
    //                     {
    //                         h1_energy_layer2_GM_PID_TM_driftcorr_LISA1[gate][layer-1]->Fill(energy_LISA_GM);
    //                     }

    //                     if(energy_ch_GM[1][0][1] >= lisa_config->fMin_dE_LISA1_gate && energy_ch_GM[1][0][1] <= lisa_config->fMax_dE_LISA1_gate)
    //                     {
    //                         h1_energy_ch201_GM_PID_TM_driftcorr_ch101[gate][layer-1][xpos][ypos]->Fill(energy_LISA_GM);
    //                     }

                        
    //                 }
    //             }
    //         }
    //     } 
    }
    
    //:::::::::::::: WR Time differences ::::::::::::::::::::::::::
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    wr_LISA_FRS = wr_LISA - wr_FRS;
    wr_LISA_travMUSIC = wr_LISA - wr_travMUSIC;
    wr_travMUSIC_FRS = wr_travMUSIC - wr_FRS;
    
    if(wr_travMUSIC == 0) return;
    h1_wr_diff[2]->Fill(wr_travMUSIC_FRS);

    if(wr_travMUSIC == 0) return;
    h1_wr_diff[1]->Fill(wr_LISA_travMUSIC);

    if (wr_FRS != 0 && wr_LISA != 0) h1_wr_diff[0]->Fill(wr_LISA_FRS);


    //:::::::::::::: ENERGY correlation ::::::::::::::::::::::::::
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    // for (int i = 0; i < layer_number; i++)
    // {
    //     //MUSIC 1
    //     h2_MUSIC_1_layer_GM[i]->Fill(sum_energy_layer_GM[i],energy_MUSIC_1);
    //     //MUSIC 2
    //     h2_MUSIC_2_layer_GM[i]->Fill(sum_energy_layer_GM[i],energy_MUSIC_2);
    //     //travMUSIC
    //     h2_travMUSIC_layer_GM[i]->Fill(sum_energy_layer_GM[i],energy_travMUSIC);
    //     h2_travMUSIC_driftcorr_layer_GM[i]->Fill(sum_energy_layer_GM[i],energy_travMUSIC_driftcorr);

        
    // }


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