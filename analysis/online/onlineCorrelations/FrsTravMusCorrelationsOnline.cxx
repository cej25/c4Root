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
 *                               25..11.24                                    *
 ******************************************************************************/

#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairTask.h"

#include "FrsTravMusCorrelationsOnline.h"
#include "FrsHitData.h"
#include "TravMusCalData.h"
#include "LisaCalData.h"
#include "TLisaConfiguration.h" // not here
#include "c4Logger.h"
#include "TFile.h"
#include "THttpServer.h"
#include "TCanvas.h"

FrsTravMusCorrelationsOnline::FrsTravMusCorrelationsOnline() 
    : FrsTravMusCorrelationsOnline("FrsTravMusCorrelationsOnline")
{

}

FrsTravMusCorrelationsOnline::FrsTravMusCorrelationsOnline(std::vector<FrsGate*> fg)
    : FrsTravMusCorrelationsOnline("FrsTravMusCorrelationsOnline")
{

}

FrsTravMusCorrelationsOnline::FrsTravMusCorrelationsOnline(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   header(nullptr)
    ,   lisaCalArray(nullptr)
    ,   travMusCalArray(nullptr)
    ,   travMusAnaArray(nullptr)
    ,   frsHitArray(nullptr)
    ,   fNEvents(0)
{
    lisa_config = TLisaConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
}

FrsTravMusCorrelationsOnline::~FrsTravMusCorrelationsOnline()
{
    c4LOG(info, "Destroyed FrsTravMusCorrelationsOnlineProperly.");
}

InitStatus FrsTravMusCorrelationsOnline::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");
    
    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaCalArray = mgr->InitObjectAs<decltype(lisaCalArray)>("LisaCalData");
    c4LOG_IF(fatal, !lisaCalArray, "Branch LisaCalData not found!");

    frsHitArray = mgr->InitObjectAs<decltype(frsHitArray)>("FrsHitData");
    c4LOG_IF(fatal, !frsHitArray, "Branch FrsHitData not found!");

    travMusCalArray = mgr->InitObjectAs<decltype(travMusCalArray)>("TravMusCalData");
    c4LOG_IF(fatal, !travMusCalArray, "Branch TravMusCalData not found!");

    travMusAnaArray = mgr->InitObjectAs<decltype(travMusAnaArray)>("TravMusAnaData");
    c4LOG_IF(fatal, !travMusAnaArray, "Branch TravMusAnaData not found!");

    layer_number = lisa_config->NLayers();

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_corr = (TDirectory*)mgr->GetObject("Correlations");
    if (dir_corr == nullptr) 
    {   
        c4LOG(info, "Creating Correlations Directory");
        dir_corr = new TDirectory("Correlations", "Correlations", "", 0);
        mgr->Register("Correlations", "Correlations Directory", dir_corr, false); // allow other tasks to find this
        histograms->Add(dir_corr);
    }

    dir_frs_travmus = dir_corr->mkdir("FRS-TravMus Correlations");
    
    dir_frs_travmus->cd();
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::::::: WR Time differences ::::::::::::::::::::::
    c_wr_diff = new TCanvas("c_wr_diff", "WR Time Differences", 650, 350);
    c_wr_diff->Divide(3);
    h1_wr_diff.resize(3);

    c_wr_diff->cd(1);
    h1_wr_diff[0] = new TH1I(" WR Difference LISA - FRS ", " WR Difference LISA - FRS ", 6000, -3000, 3000);
    //h1_wr_diff[0]->SetStats(0);
    h1_wr_diff[0]->Draw();
    h1_wr_diff[0]->GetXaxis()->SetTitle("WR(LISA) - WR (FRS)");

    c_wr_diff->cd(2);
    h1_wr_diff[1] = new TH1I(" WR Difference LISA - TravMUSIC ", " WR Difference LISA - TravMUSIC ", 6000, -3000, 3000);
    //h1_wr_diff[1]->SetStats(0);
    h1_wr_diff[1]->Draw();
    h1_wr_diff[1]->GetXaxis()->SetTitle("WR(LISA) - WR (travMUSIC)");

    c_wr_diff->cd(3);
    h1_wr_diff[2] = new TH1I(" WR Difference TravMUSIC - FRS ", " WR Difference TravMUSIC - FRS ", 6000, -3000, 3000);
    //h1_wr_diff[2]->SetStats(0);
    h1_wr_diff[2]->Draw();
    h1_wr_diff[2]->GetXaxis()->SetTitle("WR (travMUSIC) - WR (FRS)");

    c_wr_diff->cd();
    dir_lisa_frs->Append(c_wr_diff);

    //FRS position vs LISA position
    //::::::::::::: Layer 1 ::::::::::::::::::
    c_xy_pos_layer1 = new TCanvas("c_xy_position_layer_1", "FRS vs LISA Position Layer 1", 650, 350);
    c_xy_pos_layer1->Divide(2);
    h2_xy_pos_layer1.resize(2);
    for (int i = 0; i < 2; i++)
    {
        c_xy_pos_layer1->cd(i+1);
        h2_xy_pos_layer1[i] = new TH2F(Form("FRS_vs_LISA_Position_%i_Layer_1",i), Form("FRS vs LISA Position %i Layer 1",i), 2, 0, 2, 400,-50,50);//change lisa range from macro - sim to sum energy for our online
        h2_xy_pos_layer1[i]->GetXaxis()->SetTitle(Form("LISA - Position %i Layer 1",i));
        h2_xy_pos_layer1[i]->GetYaxis()->SetTitle(Form("FRS Position %i",i));
        //h2_xy_position[i]->SetStats(0);
        h2_xy_pos_layer1[i]->Draw("colz");
    }
    c_xy_pos_layer1->cd(0);
    dir_lisa_frs->Append(c_xy_pos_layer1);   

    //FRS position vs LISA position
    //::::::::::::: Layer 2 ::::::::::::::::::
    c_xy_pos_layer2 = new TCanvas("c_xy_position_layer_2", "FRS vs LISA Position Layer 2", 650, 350);
    c_xy_pos_layer2->Divide(2);
    h2_xy_pos_layer2.resize(2);
    for (int i = 0; i < 2; i++)
    {
        c_xy_pos_layer2->cd(i+1);
        h2_xy_pos_layer2[i] = new TH2F(Form("FRS_vs_LISA_Position_%i_Layer_2",i), Form("FRS vs LISA Position %i Layer 2",i), 2, 0, 2, 300,-100,100);//change lisa range from macro - sim to sum energy for our online
        h2_xy_pos_layer2[i]->GetXaxis()->SetTitle(Form("LISA - Position %i Layer 2",i));
        h2_xy_pos_layer2[i]->GetYaxis()->SetTitle(Form("FRS Position %i",i));
        //h2_xy_position[i]->SetStats(0);
        h2_xy_pos_layer2[i]->Draw("colz");
    }
    c_xy_pos_layer2->cd(0);

    dir_lisa_frs->Append(c_xy_pos_layer2);   

    //MUSIC1 - LISA
    //:::::::::::::::::::::::::::::::
    c_MUSIC_1_layer = new TCanvas("c_MUSIC_1_layer", "MUSIC(1) vs E(LISA) per Layer", 650, 350);
    c_MUSIC_1_layer->Divide(3);
    h2_MUSIC_1_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_MUSIC_1_layer->cd(i+1);
        h2_MUSIC_1_layer[i] = new TH2F(Form("MUSIC(1) vs E(LISA) Layer %i",i), Form("MUSIC(1) vs E(LISA) Layer %i",i), 2000, 1000, 3510000, 400,0,4096);//change lisa range from macro - sim to sum energy for our online
        h2_MUSIC_1_layer[i]->GetXaxis()->SetTitle(Form("E(LISA) - Layer %i",i));
        h2_MUSIC_1_layer[i]->GetYaxis()->SetTitle("dE MUSIC(1)");
        //h2_MUSIC_1_layer[i]->SetStats(0);
        h2_MUSIC_1_layer[i]->Draw("colz");
    }
    c_MUSIC_1_layer->cd(0);
    dir_lisa_frs->Append(c_MUSIC_1_layer);

    //MUSIC 2 VS LISA
    //:::::::::::::::::::::::::::::::
    c_MUSIC_2_layer = new TCanvas("c_MUSIC_2_layer", "MUSIC(1) vs E(LISA) per Layer", 650, 350);
    c_MUSIC_2_layer->Divide(3);
    h2_MUSIC_2_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_MUSIC_2_layer->cd(i+1);
        h2_MUSIC_2_layer[i] = new TH2F(Form("MUSIC(2) vs E(LISA) Layer %i",i), Form("MUSIC(2) vs E(LISA) Layer %i",i), 2000, 1000, 3510000, 400,0,4096);//change lisa range from macro - sim to sum energy for our online
        h2_MUSIC_2_layer[i]->GetXaxis()->SetTitle(Form("E(LISA) - Layer %i",i));
        h2_MUSIC_2_layer[i]->GetYaxis()->SetTitle("dE MUSIC(2)");
        //h2_MUSIC_2_layer[i]->SetStats(0);
        h2_MUSIC_2_layer[i]->Draw("colz");
    }
    c_MUSIC_2_layer->cd(0);
    dir_lisa_frs->Append(c_MUSIC_2_layer);

    //travMUSIC VS LISA
    c_travMUSIC_layer = new TCanvas("c_travMUSIC_layer", "travMUSIC vs E(LISA) per Layer", 650, 350);
    c_travMUSIC_layer->Divide(3);
    h2_travMUSIC_layer.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_travMUSIC_layer->cd(i+1);
        h2_travMUSIC_layer[i] = new TH2F(Form("travMUSIC vs E(LISA) Layer %i",i), Form("travMUSIC vs E(LISA) Layer %i",i), 2000, 1000, 3510000, 400,0,4096);//change lisa range from macro - sim to sum energy for our online
        h2_travMUSIC_layer[i]->GetXaxis()->SetTitle(Form("E(LISA) - Layer %i",i));
        h2_travMUSIC_layer[i]->GetYaxis()->SetTitle("dE travMUSIC");
        //h2_travMUSIC_layer[i]->SetStats(0);
        h2_travMUSIC_layer[i]->Draw("colz");
    }
    c_travMUSIC_layer->cd(0);
 

    run->GetHttpServer()->RegisterCommand("Reset_LisaFRS_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));
    return kSUCCESS;

}


void FrsTravMusCorrelationsOnline::Reset_Histo()
{
    c4LOG(info, "");
}


void FrsTravMusCorrelationsOnline::Exec(Option_t* option)
{   
    if (travMusAnaArray->size() <= 0 || frsHitArray->size() <= 0) return; //frs and trav music are there

    const auto & frsHitItem = frsHitArray->at(0); // *should* only be 1 FRS subevent per event
    const auto & travMusicHitItem = travMusAnaArray->at(0); 


    wr_FRS = frsHitItem.Get_wr_t();
    wr_travMUSIC = travMusicHitItem.Get_wr_t();

    //S2 Position x-y
    s2_x = frsHitItem.Get_ID_x2();
    s2_y = frsHitItem.Get_ID_y2();

    energy_MUSIC_1 = frsHitItem.Get_music_dE(0); 
    energy_MUSIC_2 = frsHitItem.Get_music_dE(1);
    energy_travMUSIC = travMusicHitItem.Get_travmusic_dE();


    wr_travMUSIC_FRS = wr_travMUSIC - wr_FRS;

    h1_wr_diff->Fill(wr_travMUSIC_FRS);


    // this is a correlation, also need Sci S1 
    // if (trav_mus_wr > 0 && hitItem.Get_ID_z() > 0 && hitItem.Get_ID_z_travmus() > 0) h2_travmus_vs_Z->Fill(hitItem.Get_ID_z_travmus(), hitItem.Get_ID_z());
    


    fNEvents++;

}

void FrsTravMusCorrelationsOnline::FinishEvent()
{

}

void FrsTravMusCorrelationsOnline::FinishTask()
{

}


ClassImp(FrsTravMusCorrelationsOnline)