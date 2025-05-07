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

#include "LisaFrsCorrelationsOnline.h"
#include "FrsHitData.h"
#include "LisaCalData.h"
#include "TLisaConfiguration.h" // not here
#include "c4Logger.h"
#include "TFile.h"
#include "THttpServer.h"
#include "TCanvas.h"

LisaFrsCorrelationsOnline::LisaFrsCorrelationsOnline() 
    : LisaFrsCorrelationsOnline("LisaFrsCorrelationsOnline")
{

}

LisaFrsCorrelationsOnline::LisaFrsCorrelationsOnline(std::vector<FrsGate*> fg)
    : LisaFrsCorrelationsOnline("LisaFrsCorrelationsOnline")
{

}

LisaFrsCorrelationsOnline::LisaFrsCorrelationsOnline(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   header(nullptr)
    ,   lisaCalArray(nullptr)
    ,   frsHitArray(nullptr)
    ,   fNEvents(0)
{
    lisa_config = TLisaConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
}

LisaFrsCorrelationsOnline::~LisaFrsCorrelationsOnline()
{
    c4LOG(info, "Destroyed LisaFrsCorrelationsOnlineProperly.");
}

InitStatus LisaFrsCorrelationsOnline::Init()
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

    layer_number = lisa_config->NLayers();
    xmax = lisa_config->XMax();
    ymax = lisa_config->YMax();
    auto const & detector_mapping = lisa_config->Mapping();

    // Ranges from MUSICs
    int min_21 = frs_config->fMin_dE_music21;
    int max_21 = frs_config->fMax_dE_music21;
    int bin_21 = (max_21 - min_21)/10;
    int min_41 = frs_config->fMin_dE_music41;
    int max_41 = frs_config->fMax_dE_music41;
    int bin_41 = (max_41 - min_41)/10;
    //.............   
    
    excluded = lisa_config->GetExcludedChannels();

    dir_time = dir_corr->mkdir("Time");

    dir_position = dir_corr->mkdir("Position");

    dir_energy = dir_corr->mkdir("Energy");
    dir_febex = dir_energy->mkdir("Febex");
    dir_mwd = dir_energy->mkdir("MWD");

    //:::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::::::: WR Time differences ::::::::::::::::::::::
    c_wr_diff = new TCanvas("c_wr_diff", "WR Time Differences", 650, 350);
    c_wr_diff->Divide(3);
    h1_wr_diff.resize(3);

    c_wr_diff->cd(1);
    h1_wr_diff[0] = new TH1I("h1_WR_Difference_LISA-FRS", " WR Difference LISA - FRS ", 6000, -3000, 3000);
    h1_wr_diff[0]->GetXaxis()->SetTitle("WR(LISA) - WR (FRS)");
    h1_wr_diff[0]->SetFillColor(kRed-3);

    c_wr_diff->cd(2);
    h1_wr_diff[1] = new TH1I("h1_WR_Difference_LISA-TravMUSIC", " WR Difference LISA - TravMUSIC ", 6000, -3000, 3000);
    h1_wr_diff[1]->GetXaxis()->SetTitle("WR(LISA) - WR (travMUSIC)");
    h1_wr_diff[1]->SetFillColor(kRed-3);

    c_wr_diff->cd(3);
    h1_wr_diff[2] = new TH1I("h1_WR_Difference_TravMUSIC-FRS", " WR Difference TravMUSIC - FRS ", 6000, -3000, 3000);
    h1_wr_diff[2]->GetXaxis()->SetTitle("WR (travMUSIC) - WR (FRS)");
    h1_wr_diff[2]->SetFillColor(kRed-3);

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
    // //::::::::::::: Layer 2 ::::::::::::::::::
    // c_xy_pos_layer2 = new TCanvas("c_xy_position_layer_2", "FRS vs LISA Position Layer 2", 650, 350);
    // c_xy_pos_layer2->Divide(2);
    // h2_xy_pos_layer2.resize(2);
    // for (int i = 0; i < 2; i++)
    // {
    //     c_xy_pos_layer2->cd(i+1);
    //     h2_xy_pos_layer2[i] = new TH2F(Form("FRS_vs_LISA_Position_%i_Layer_2",i), Form("FRS vs LISA Position %i Layer 2",i), 2, 0, 2, 300,-100,100);//change lisa range from macro - sim to sum energy for our online
    //     h2_xy_pos_layer2[i]->GetXaxis()->SetTitle(Form("LISA - Position %i Layer 2",i));
    //     h2_xy_pos_layer2[i]->GetYaxis()->SetTitle(Form("FRS Position %i",i));
    //     //h2_xy_position[i]->SetStats(0);
    //     h2_xy_pos_layer2[i]->Draw("colz");
    // }
    // c_xy_pos_layer2->cd(0);

    // dir_lisa_frs->Append(c_xy_pos_layer2);   

    //::: MUSIC21 - LISA
    //Febex
    c_MUSIC_21_layer = new TCanvas("c_MUSIC_21_layer", "MUSIC(21) vs E(LISA) per Layer", 650, 350);
    c_MUSIC_21_layer->Divide(3);
    h2_MUSIC21_vs_LISA_febex.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_MUSIC_21_layer->cd(i+1);
        h2_MUSIC21_vs_LISA_febex[i] = new TH2F(Form("h2_MUSIC(21)_vs_LISA_%i_febex",i), Form("dE MUSIC(21) vs dE(LISA) %i Febex",i), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, bin_21, min_21, max_21);
        h2_MUSIC21_vs_LISA_febex[i]->GetXaxis()->SetTitle(Form("dE(LISA) Febex - Layer %i",i));
        h2_MUSIC21_vs_LISA_febex[i]->GetYaxis()->SetTitle("dE MUSIC(21)");
        h2_MUSIC21_vs_LISA_febex[i]->Draw("COLZ");
    }
    c_MUSIC_21_layer->cd(0);
    dir_lisa_frs->Append(c_MUSIC_21_layer);

    //MWD
    c_MUSIC_21_layer_MWD = new TCanvas("c_MUSIC_21_layer_MWD", "MUSIC(21) vs E(LISA) MWD per Layer", 650, 350);
    c_MUSIC_21_layer_MWD->Divide(3);
    h2_MUSIC21_vs_LISA_MWD.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_MUSIC_21_layer->cd(i+1);
        h2_MUSIC21_vs_LISA_MWD[i] = new TH2F(Form("h2_MUSIC(21)_vs_LISA_%i_MWD",i), Form("dE MUSIC(21) vs dE(LISA) %i MWD",i), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, bin_21, min_21, max_21);
        h2_MUSIC21_vs_LISA_MWD[i]->GetXaxis()->SetTitle(Form("dE(LISA) MWD - Layer %i",i));
        h2_MUSIC21_vs_LISA_MWD[i]->GetYaxis()->SetTitle("dE MUSIC(21)");
        h2_MUSIC21_vs_LISA_MWD[i]->Draw("COLZ");
    }
    c_MUSIC_21_layer_MWD->cd(0);
    dir_lisa_frs->Append(c_MUSIC_21_layer_MWD);
    //............................

    //MUSIC 41 VS LISA
    // Febex
    c_MUSIC_41_layer = new TCanvas("c_MUSIC_41_layer", "MUSIC(41) vs E(LISA) per Layer", 650, 350);
    c_MUSIC_41_layer->Divide(3);
    h2_MUSIC41_vs_LISA_febex.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_MUSIC_41_layer->cd(i+1);
        h2_MUSIC41_vs_LISA_febex[i] = new TH2F(Form("h2_MUSIC(41)_vs_LISA_%i",i), Form("dE MUSIC(41) vs dE(LISA) %i ",i), lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy, bin_41, min_41, max_41);
        h2_MUSIC41_vs_LISA_febex[i]->GetXaxis()->SetTitle(Form("dE(LISA) - Layer %i",i));
        h2_MUSIC41_vs_LISA_febex[i]->GetYaxis()->SetTitle("dE MUSIC(41)");
        h2_MUSIC41_vs_LISA_febex[i]->Draw("COLZ");
    }
    c_MUSIC_41_layer_MWD->cd(0);
    dir_lisa_frs->Append(c_MUSIC_41_layer_MWD);

    // MWD
    c_MUSIC_41_layer_MWD = new TCanvas("c_MUSIC_41_layer_MWD", "MUSIC(41) vs E(LISA) MWD per Layer", 650, 350);
    c_MUSIC_41_layer_MWD->Divide(3);
    h2_MUSIC41_vs_LISA_MWD.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_MUSIC_41_layer->cd(i+1);
        h2_MUSIC41_vs_LISA_MWD[i] = new TH2F(Form("h2_MUSIC(41)_vs_LISA_%i_MWD",i), Form("dE MUSIC(41) vs dE(LISA) %i MWD",i), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, bin_41, min_41, max_41);
        h2_MUSIC41_vs_LISA_MWD[i]->GetXaxis()->SetTitle(Form("dE(LISA) MWD - Layer %i",i));
        h2_MUSIC41_vs_LISA_MWD[i]->GetYaxis()->SetTitle("dE MUSIC(41)");
        h2_MUSIC41_vs_LISA_MWD[i]->Draw("COLZ");
    }
    c_MUSIC_41_layer_MWD->cd(0);
    dir_lisa_frs->Append(c_MUSIC_41_layer_MWD);
 
    run->GetHttpServer()->RegisterCommand("Reset_LisaFRS_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));
    return kSUCCESS;

}


void LisaFrsCorrelationsOnline::Reset_Histo()
{
    c4LOG(info, "");
}


void LisaFrsCorrelationsOnline::Exec(Option_t* option)
{   
    // reject events without both subsystems
    if (frsHitArray->size() <= 0) return; //frs is there
    //if (lisaCalArray->size() <= 0 ) return; //for when travmusic is there but not frs

    const auto & frsHitItem = frsHitArray->at(0); // *should* only be 1 FRS subevent per event

    // ::: FRS WR
    Int_t count_wr = 0;

    wr_FRS = frsHitItem.Get_wr_t();
    wr_travMUSIC = frsHitItem.Get_travmus_wr_t();

    // ::: LISA energy
    std::vector<std::vector<float>> energy_layer(layer_number);
    energy_layer.resize(layer_number);

    std::vector<std::vector<float>> energy_MWD_layer(layer_number);
    energy_MWD_layer.resize(layer_number);

    //S2 Position x-y
    s2_x = frsHitItem.Get_ID_x2();
    s2_y = frsHitItem.Get_ID_y2();
    //c4LOG(info, "s2 x : " << s2_x << "s2 y : " << s2_y);

    // Energy MUSICS
    energy_MUSIC_21 = frsHitItem.Get_music21_dE();
    energy_MUSIC_41 = frsHitItem.Get_music41_dE(); 
    energy_MUSIC_42 = frsHitItem.Get_music42_dE();
    Float_t x2_position = frsHitItem.Get_ID_x2();
    Float_t x4_position = frsHitItem.Get_ID_x4();
    //c4LOG(info, "travMUS en : " << energy_travMUSIC << " music 1 : " << energy_MUSIC_1 << " sum energy 1 : " << sum_energy_layer[1]);


    // correlation with main FRS (10, 20, 30, 15)
    for (const auto & lisaCalItem : *lisaCalArray)
    {        
        //::::::: Retrieve Data ::::::::::::::

        //:::: White Rabbit
        if (count_wr == 0)
        {
            wr_LISA = lisaCalItem.Get_wr_t();
        }
        count_wr++;
        if (wr_LISA == 0)return;

        //::::Position
        layer = lisaCalItem.Get_layer_id();
        city = lisaCalItem.Get_city();
        int xpos = lisaCalItem.Get_xposition();
        int ypos = lisaCalItem.Get_yposition();
        float energy_LISA_febex = lisaCalItem.Get_energy_GM();
        float energy_LISA_MWD = lisaCalItem.Get_energy_MWD_GM();

        if (excluded.count(std::make_tuple(layer, xpos, ypos)) != 0) continue;

        energy_layer[layer-1].emplace_back(energy_LISA_febex);
        energy_MWD_layer[layer-1].emplace_back(energy_LISA_MWD);

        // //:::::::::::::: FRS - LISA position ::::::::::::::::::::::::::
        // //:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::   
        
        // if (layer == 1)
        // {
        // h2_xy_pos_layer1[0]->Fill(xpos,s2_x);
        // h2_xy_pos_layer1[1]->Fill(ypos,s2_y);
        // }

        // if (layer == 2)
        // {
        // h2_xy_pos_layer2[0]->Fill(xpos,s2_x);
        // h2_xy_pos_layer2[1]->Fill(ypos,s2_y);
        // }
        

        //:::: Energies
        uint32_t energy_LISA = lisaCalItem.Get_energy();
        layer = lisaCalItem.Get_layer_id();

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


    fNEvents++;

}

void LisaFrsCorrelationsOnline::FinishEvent()
{

}

void LisaFrsCorrelationsOnline::FinishTask()
{

}


ClassImp(LisaFrsCorrelationsOnline)