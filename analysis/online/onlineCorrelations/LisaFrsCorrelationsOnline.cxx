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
#include "AnalysisTools.h"

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
    frs = frs_config->FRS();
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

    dir_energy_correlated = dir_energy->mkdir("LISA_correlated_sci41");
    dir_energy_MWD_correlated = dir_energy->mkdir("LISA_correlated_sci41_mwd");

    dir_time->cd();
    //:::::::::::::::::::::::::::::::::::::::::::::::::::::
    //:::::::::: WR Time differences ::::::::::::::::::::::
    c_wr_diff = new TCanvas("c_wr_diff", "WR Time Difference", 650, 350);
    //h1_wr_diff.resize(3);
    c_wr_diff->Divide(1, 3);

    c_wr_diff->cd(1);
    h1_wr_diff = new TH1I("h1_WR_Difference_LISA-FRS", " WR Difference LISA - FRS ", 6000, -3000, 3000);
    h1_wr_diff->GetXaxis()->SetTitle("WR(LISA) - WR (FRS)");
    h1_wr_diff->SetFillColor(kRed-3);
    h1_wr_diff->Draw();
    c_wr_diff->cd(2);
    h1_wr_diff_tpat2 = new TH1I("h1_wr_diff_tpat2", " WR Difference LISA - FRS tpat 2", 6000, -3000, 3000);
    h1_wr_diff_tpat2->GetXaxis()->SetTitle("WR(LISA) - WR (FRS)");
    h1_wr_diff_tpat2->SetFillColor(kRed-3);
    h1_wr_diff_tpat2->Draw();
    c_wr_diff->cd(3);
    h1_wr_diff_tpat6 = new TH1I("h1_wr_diff_tpat6", " WR Difference LISA - FRS tpat 6 ", 6000, -3000, 3000);
    h1_wr_diff_tpat6->GetXaxis()->SetTitle("WR(LISA) - WR (FRS)");
    h1_wr_diff_tpat6->SetFillColor(kRed-3);
    h1_wr_diff_tpat6->Draw();

    // c_wr_diff->cd(2);
    // h1_wr_diff[1] = new TH1I("h1_WR_Difference_LISA-TravMUSIC", " WR Difference LISA - TravMUSIC ", 6000, -3000, 3000);
    // h1_wr_diff[1]->GetXaxis()->SetTitle("WR(LISA) - WR (travMUSIC)");
    // h1_wr_diff[1]->SetFillColor(kRed-3);

    // c_wr_diff->cd(3);
    // h1_wr_diff[2] = new TH1I("h1_WR_Difference_TravMUSIC-FRS", " WR Difference TravMUSIC - FRS ", 6000, -3000, 3000);
    // h1_wr_diff[2]->GetXaxis()->SetTitle("WR (travMUSIC) - WR (FRS)");
    // h1_wr_diff[2]->SetFillColor(kRed-3);
    c_wr_diff->cd();
    dir_time->Append(c_wr_diff);

    // Energy
    dir_energy_correlated->cd();
    // Condiiton on scintillator 41 
    // Febex
    c_energy_correlated_sci41 = new TCanvas("c_energy_corr_sci41", "LISA energy correlated with SCI41", 650, 350);
    c_energy_correlated_sci41->Divide(2, (layer_number+1)/2);
    h1_energy_layer_corr_sci41.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        c_energy_correlated_sci41->cd(i+1);
        h1_energy_layer_corr_sci41[i] = MakeTH1(dir_energy_correlated, "F",
            Form("h1_energy_layer_%i_corr_sci41", i+1), Form("Energy corr sci41- Layer %i", i+1), 
            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
            Form("E(LISA %i) Corr sci41 [a.u.]", i+1), kRed-3, kBlue+1);
        h1_energy_layer_corr_sci41[i]->Draw();
    }
    c_energy_correlated_sci41->cd();
    dir_energy_correlated->Append(c_energy_correlated_sci41);

    // MWD
    c_energy_MWD_correlated_sci41 = new TCanvas("c_energy_MWD_corr_sci41", "LISA energy MWD correlated with SCI41", 650, 350);
    c_energy_MWD_correlated_sci41->Divide(2, (layer_number+1)/2);
    h1_energy_MWD_layer_corr_sci41.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {   
        c_energy_MWD_correlated_sci41->cd(i+1);
        h1_energy_MWD_layer_corr_sci41[i] = MakeTH1(dir_energy_MWD_correlated, "F",
            Form("h1_energy_MWD_layer_%i_corr_sci41", i+1), Form("Energy MWD corr sci41- Layer %i", i+1), 
            lisa_config->bin_energy, lisa_config->min_energy, lisa_config->max_energy,
            Form("E MWD(LISA %i) Corr sci41 [a.u.]", i+1), kViolet+10, kBlue+1);
        h1_energy_MWD_layer_corr_sci41[i]->Draw();
    }
    c_energy_MWD_correlated_sci41->cd();
    dir_energy_MWD_correlated->Append(c_energy_MWD_correlated_sci41);

    dir_febex->cd();
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
    dir_febex->Append(c_MUSIC_21_layer);

    dir_mwd->cd();
    //MWD
    c_MUSIC_21_layer_MWD = new TCanvas("c_MUSIC_21_layer_MWD", "MUSIC(21) vs E(LISA) MWD per Layer", 650, 350);
    c_MUSIC_21_layer_MWD->Divide(3);
    h2_MUSIC21_vs_LISA_MWD.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_MUSIC_21_layer_MWD->cd(i+1);
        h2_MUSIC21_vs_LISA_MWD[i] = new TH2F(Form("h2_MUSIC(21)_vs_LISA_%i_MWD",i), Form("dE MUSIC(21) vs dE(LISA) %i MWD",i), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, bin_21, min_21, max_21);
        h2_MUSIC21_vs_LISA_MWD[i]->GetXaxis()->SetTitle(Form("dE(LISA) MWD - Layer %i",i));
        h2_MUSIC21_vs_LISA_MWD[i]->GetYaxis()->SetTitle("dE MUSIC(21)");
        h2_MUSIC21_vs_LISA_MWD[i]->Draw("COLZ");
    }
    c_MUSIC_21_layer_MWD->cd(0);
    dir_mwd->Append(c_MUSIC_21_layer_MWD);
    //............................

    dir_febex->cd();
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
    c_MUSIC_41_layer->cd(0);
    dir_febex->Append(c_MUSIC_41_layer);

    dir_mwd->cd();
    // MWD
    c_MUSIC_41_layer_MWD = new TCanvas("c_MUSIC_41_layer_MWD", "MUSIC(41) vs E(LISA) MWD per Layer", 650, 350);
    c_MUSIC_41_layer_MWD->Divide(3);
    h2_MUSIC41_vs_LISA_MWD.resize(layer_number);
    for (int i = 0; i < layer_number; i++)
    {
        c_MUSIC_41_layer_MWD->cd(i+1);
        h2_MUSIC41_vs_LISA_MWD[i] = new TH2F(Form("h2_MUSIC(41)_vs_LISA_%i_MWD",i), Form("dE MUSIC(41) vs dE(LISA) %i MWD",i), lisa_config->bin_energy_MWD, lisa_config->min_energy_MWD, lisa_config->max_energy_MWD, bin_41, min_41, max_41);
        h2_MUSIC41_vs_LISA_MWD[i]->GetXaxis()->SetTitle(Form("dE(LISA) MWD - Layer %i",i));
        h2_MUSIC41_vs_LISA_MWD[i]->GetYaxis()->SetTitle("dE MUSIC(41)");
        h2_MUSIC41_vs_LISA_MWD[i]->Draw("COLZ");
    }
    c_MUSIC_41_layer_MWD->cd(0);
    dir_mwd->Append(c_MUSIC_41_layer_MWD);

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
        h2_tpc_xy_LISA[i] = MakeTH2(dir_position, "F", Form("h2_tpc_xy_LISA_%i", i+1), Form("TPC XY at LISA - Layer %i", i+1),1000, -100., 100., 1000, -100., 100.);
    }

    c_tpc_x_lisa_x = new TCanvas("c_tpc_x_lisa_x", "TPC X vs LISA X", 1200, 900);
    c_tpc_x_lisa_x->Divide(2, 3);
    for (int i = 0; i < layer_number; i++) 
    {
        c_tpc_x_lisa_x->cd(i + 1);
        h2_tpc_x_lisa_x[i]->Draw("COLZ");
    }
    dir_position->Append(c_tpc_x_lisa_x);

    c_tpc_y_lisa_y = new TCanvas("c_tpc_y_lisa_y", "TPC Y vs LISA Y", 1200, 900);
    c_tpc_y_lisa_y->Divide(2, 3);
    for (int i = 0; i < layer_number; i++) 
    {
        c_tpc_y_lisa_y->cd(i + 1);
        h2_tpc_y_lisa_y[i]->Draw("COLZ");
    }
    dir_position->Append(c_tpc_y_lisa_y);

    c_tpc_xy_at_LISA = new TCanvas("c_tpc_xy_at_LISA", "TPC XY at LISA", 1200, 900);
    c_tpc_xy_at_LISA->Divide(2, 3);
    for (int i = 0; i < layer_number; i++) {
        c_tpc_xy_at_LISA->cd(i + 1);
        h2_tpc_xy_LISA[i]->Draw("COLZ");
    }
    dir_position->Append(c_tpc_xy_at_LISA);

    // TCanvas* c_tpc_xy = new TCanvas("c_tpc_xy", "TPC POS XY AT LISA", 650, 350);
    // c_tpc_xy->Divide(2,2);
    // c_tpc_xy->cd(1);
    // h2_tpc_xy_LISA_001 = MakeTH2(dir_position, "F", "h2_tpc_xy_LISA_001", "TPC XY at LISA 001", 100, -8., 10., 100, -25., -4.);
    // h2_tpc_xy_LISA_001->Draw();
    // c_tpc_xy->cd(2);
    // h2_tpc_xy_LISA_011 = MakeTH2(dir_position, "F", "h2_tpc_xy_LISA_011", "TPC XY at LISA 011", 100, -8., 10., 100, -25., -4.);
    // h2_tpc_xy_LISA_011->Draw();
    // c_tpc_xy->cd(3);
    // h2_tpc_xy_LISA_000 = MakeTH2(dir_position, "F", "h2_tpc_xy_LISA_000", "TPC XY at LISA 000", 100, -8., 10., 100, -25., -4.);
    // h2_tpc_xy_LISA_000->Draw();
    // c_tpc_xy->cd(4);
    // h2_tpc_xy_LISA_010 = MakeTH2(dir_position, "F", "h2_tpc_xy_LISA_010", "TPC XY at LISA 010", 100, -8., 10., 100, -25., -4.);
    // h2_tpc_xy_LISA_010->Draw();
    // dir_position->Append(c_tpc_xy);

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
    if (frsHitArray->size() <= 0 || lisaCalArray->size() <= 0) return; //frs is there
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

    
    // if (frsHitItem.Get_tpat() & 0b100000) c4LOG(info, "TPAT 6:: WR LISA-FRS DIFF : " << wr_LISA_FRS);
    // if (frsHitItem.Get_tpat() & 0b10) c4LOG(info, "TPAT 2:: WR LISA-FRS DIFF : " << wr_LISA_FRS);


    //if(wr_travMUSIC == 0) return;
    //h1_wr_diff[2]->Fill(wr_travMUSIC_FRS);

    //if(wr_travMUSIC == 0) return;
    //h1_wr_diff[1]->Fill(wr_LISA_travMUSIC);


    h1_wr_diff->Fill(wr_LISA_FRS);
    if (frsHitItem.Get_tpat() & 0b100000) h1_wr_diff_tpat6->Fill(wr_LISA_FRS);
    if (frsHitItem.Get_tpat() & 0b10) h1_wr_diff_tpat2->Fill(wr_LISA_FRS);

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