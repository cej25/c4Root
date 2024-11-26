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


// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"

// c4
//#include "TravMusSpectra.h"
#include "TravMusNearlineSpectra.h"
#include "EventHeader.h"
#include "c4Logger.h"
#include "AnalysisTools.h"

// ROOT
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"


TravMusNearlineSpectra::TravMusNearlineSpectra() : TravMusNearlineSpectra("TravMusNearlineSpectra")
{
    frs_config = TFrsConfiguration::GetInstance();
}

TravMusNearlineSpectra::TravMusNearlineSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   travMusCalArray(nullptr)
    ,   travMusAnaArray(nullptr)
    ,   fNEvents(0)
    ,   header(nullptr)
{
    frs_config = TFrsConfiguration::GetInstance();
}

TravMusNearlineSpectra::~TravMusNearlineSpectra()
{
    c4LOG(info, "");
}

InitStatus TravMusNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    travMusCalArray = mgr->InitObjectAs<decltype(travMusCalArray)>("TravMusCalData");
    c4LOG_IF(fatal, !travMusCalArray, "Branch TravMusCalData not found!");
    travMusAnaArray = mgr->InitObjectAs<decltype(travMusAnaArray)>("TravMusAnaData");
    c4LOG_IF(fatal, !travMusAnaArray, "Branch TravMusAnaData not found!");
    
    mgr->GetOutFile()->cd();
    // try to find FRS first, then MUSIC, if not..
    dir_travmus = gDirectory->mkdir("Travel MUSIC");
    //mgr->Register("Travel MUSIC", "Travel MUSIC", dir_travmus, false); // allow other tasks to find this
    
    dir_raw_adc = dir_travmus->mkdir("Raw ADC");
    dir_drifts = dir_travmus->mkdir("Drifts");
    dir_raw_adc->cd();

    //:::::::::: Raw ADC ::::::::::::::::
    c_raw_adc = new TCanvas("c_raw_adc", "Travel MUSIC Raw ADC", 650, 350);
    c_raw_adc->Divide(4, 2);
    for (int i = 0; i < 8; i++)
    {
        c_raw_adc->cd(i+1);
        h1_travmus_raw_adc[i] = MakeTH1(dir_raw_adc, "I", Form("h1_travmus_raw_adc_anode_%i", i), Form("Raw ADC - Travel MUSIC Anode %i", i), 10500, 100, 12500, "ADC Channel", kPink-3, kBlue+2);
        h1_travmus_raw_adc[i]->Draw();
    }
    c_raw_adc->cd(0);
    dir_raw_adc->Append(c_raw_adc);


    dir_travmus->cd();

    // correlations + Z from SC1
    // h2_travmus_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_travmus_vs_Z", "Z (Travel MUSIC) vs Z (MUSIC 1)", 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_Z, frs_config->fMax_Z, "Z (Travel MUSIC)", "Z (MUSIC 1)");
    
    // need Z from SC1
    // h1_Z_travmus = MakeTH1(dir_tac_1d, "D", "h1_Z_travmus", "Z (Travel MUSIC)", 750, 10, 100, "Z (Travel MUSIC)", kPink-3, kBlue+2);

    // correlations + Z from SC1
    // h2_travmus_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_travmus_vs_Z_mhtdc", "Z (Trav) vs. Z1 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z (Travel MUSIC)", "Z (MUSIC 1)");
    
    // need Z from SC1
    // h1_z_travmus_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_z_travmus_mhtdc", "Z (Travel MUSIC) (MHTDC)", 1000, 0, 100, "Z (Travel MUSIC)", kPink-3, kBlue+2);

    // correlations ... 
    // h2_Z_vs_AoQ_mhtdc_trav_gate = MakeTH2(dir_travmus, "D", "h2_Z_vs_AoQ_mhtdc_trav_gate", "Z1 vs. A/Q (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);

    // h2_Ztrav_vs_T = MakeTH2(dir_drifts, "D", "h2_Ztrav_vs_T", "Z (Trav Mus) vs Time [mins]", 500, 0, 10000, 1500, frs_config->fMin_Z, frs_config->fMax_Z);

    // from LISA branch, histos in FrsNearline
    h1_travmus_dE = MakeTH1(dir_travmus, "D", "h1_travmus_dE", "dE (Travel MUSIC)", 1000, 0, 4000., "dE (Travel MUSIC)", kPink-3, kBlue+2);
    h1_travmus_dE_driftcorr = MakeTH1(dir_travmus, "D", "h1_travmus_dE_driftcorr", "dE DriftCorr(Travel MUSIC)", 1000, 0, 4000., "dE DriftCorr (Travel MUSIC)", kPink-3, kBlue+2);

    // from LISA branch, possible a correlations histos jobby...
    // h2_Z_vs_AoQ_mhtdc_trav_gate = MakeTH2(dir_travmus, "D", "h2_Z_vs_AoQ_mhtdc_trav_gate", "Z1 vs. A/Q (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    // h2_Z_vs_AoQ_tac_trav_gate_driftcorr = MakeTH2(dir_travmus, "D", "h2_Z_vs_AoQ_tac_trav_gate_driftcorr", "Z1 vs. A/Q (TAC) DriftCorr", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    // h2_Z_vs_AoQ_driftcorr_trav_gate = MakeTH2(dir_travmus, "D", "h2_Z_vs_AoQ_tac_driftcorr_trav_gate", "Z1 vs. A/Q (DriftCorr)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);


    //::: TravMus Drift with ref to the run number
    //c_TravMus_drift = new TCanvas("c_TravMus_drift", "c_TravMus_drift", 650, 350);
    //c_TravMus_drift->SetLogz();
    //c_TravMus_drift->cd();
    h2_TravMus_vs_T = MakeTH2(dir_drifts, "D", "h2_TravMus_vs_T", "dE (TravM) vs Time [min]", 1000, 0, 10000, 1000, 0, 4200, "WR [min]", "dE (Travel MUSIC)");
    // info on run number-not working now damn (EG)
    frs_time_min = std::numeric_limits<double>::max();
    frs_time_max = std::numeric_limits<double>::lowest(); 
    double initial_x_min = 0;      
    double initial_x_max = 10000; 
    double y_position = 4100;     
    double text_offset = 50; 
 
    hline = new TLine(initial_x_min, y_position, initial_x_max, y_position);
    hline->SetLineColor(kRed);
    hline->SetLineWidth(2);

    left_bar = new TLine(initial_x_min, y_position - 50, initial_x_min, y_position + 50);
    left_bar->SetLineColor(kRed);
    left_bar->SetLineWidth(2);

    right_bar = new TLine(initial_x_max, y_position - 50, initial_x_max, y_position + 50);
    right_bar->SetLineColor(kRed);
    right_bar->SetLineWidth(2);

    run_number_text = new TText((initial_x_min + initial_x_max) / 2, y_position + text_offset,
                                Form("run: %d", frs_config->frun_num));
    run_number_text->SetTextSize(0.03);
    run_number_text->SetTextAlign(22); // Center alignment

    // hline->Write();
    // left_bar->Write();
    // right_bar->Write();
    // run_number_text->Write();
    // h2_TravMus_vs_T->Draw();
    h2_TravMus_vs_T->SetOption("colz");

    //c_TravMus_drift->cd();
    //dir_drifts->Append(c_TravMus_drift);

    // Drift corrected
    h2_TravMus_driftcorr_vs_T = MakeTH2(dir_drifts, "D", "h2_TravMus_driftcorr_vs_T", "dE (TravM) DriftCorr vs Time [min]", 1000, 0, 10000, 1000, 0, 4200, "WR [min]", "dE DriftCorr (Travel MUSIC)");



    return kSUCCESS;

}


void TravMusNearlineSpectra::Exec(Option_t* option)
{

    uint64_t wr_t = 0;
    for (auto const & travMusCalItem : *travMusCalArray)
    {
        wr_t = travMusCalItem.Get_wr_t();
        if(wr_t == 0) return;
        for (int i = 0; i < 8; i++)
        {
            h1_travmus_raw_adc[i]->Fill(travMusCalItem.Get_music_energy(i));
        }
    }

    // h1_travmus_dE->Fill(hitItem.Get_travmusic_dE());

    // if (trav_mus_wr > 0 && hitItem.Get_ID_z_travmus() > 0) h1_Z_travmus->Fill(hitItem.Get_ID_z_travmus());
    // if (trav_mus_wr > 0 && hitItem.Get_travmusic_dE() > 0) h1_travmus_dE->Fill(hitItem.Get_travmusic_dE());

    // if(hitItem.Get_travmusic_dE() >= frs_config->fMin_dE_travMus_gate && hitItem.Get_travmusic_dE() <= frs_config->fMax_dE_travMus_gate)
    // {
    //     h2_Z_vs_AoQ_mhtdc_trav_gate->Fill(multihitItem.Get_ID_AoQ_mhtdc(), multihitItem.Get_ID_z_mhtdc());
    // }

    // // multihit travmus?
    // if (trav_mus_wr > 0 && multihitItem.Get_ID_z_travmus_mhtdc() > 0) h1_z_travmus_mhtdc->Fill(multihitItem.Get_ID_z_travmus_mhtdc());
    // if (multihitItem.Get_ID_z_travmus_mhtdc() > 0) h1_z_travmus_mhtdc->Fill(multihitItem.Get_ID_z_travmus_mhtdc());
    // // dE stuff
    
    // if (hitItem.Get_ID_z_travmus() > 0 && FRS_time_mins > 0) h2_Ztrav_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_z_travmus());


    // from LISA branch
    // ::: Drift TM        
    // if (hitItem.Get_travmusic_dE() > 0 && FRS_time_mins > 0) 
    // {
    //     double y_position = 4010;  
    //     hline->SetX1(frs_time_min);
    //     hline->SetX2(frs_time_max);
    //     hline->SetY1(y_position);
    //     hline->SetY2(y_position);

    //     left_bar->SetX1(frs_time_min);
    //     left_bar->SetX2(frs_time_min);
    //     left_bar->SetY1(y_position - 50);
    //     left_bar->SetY2(y_position + 50);

    //     right_bar->SetX1(frs_time_max);
    //     right_bar->SetX2(frs_time_max);
    //     right_bar->SetY1(y_position - 50);
    //     right_bar->SetY2(y_position + 50);

    //     run_number_text->SetText((frs_time_min + frs_time_max) / 2, y_position + 50,
    //                             Form("run: %d", frs_config->frun_num));
        
    //     h2_TravMus_vs_T->Fill(FRS_time_mins, hitItem.Get_travmusic_dE());

    // }
    // if (hitItem.Get_travmusic_dE_driftcorr() > 0 && FRS_time_mins > 0)h2_TravMus_driftcorr_vs_T->Fill(FRS_time_mins, hitItem.Get_travmusic_dE_driftcorr());

    // from LISA branch
    //::: TM
    // //if (trav_mus_wr > 0 && hitItem.Get_travmusic_dE() > 0) h1_travmus_dE->Fill(hitItem.Get_travmusic_dE());
    // //if (trav_mus_wr > 0 && hitItem.Get_travmusic_dE_driftcorr() > 0) h1_travmus_dE_driftcorr->Fill(hitItem.Get_travmusic_dE_driftcorr());
    // if (hitItem.Get_travmusic_dE() > 0) h1_travmus_dE->Fill(hitItem.Get_travmusic_dE());
    // if (hitItem.Get_travmusic_dE_driftcorr() > 0) h1_travmus_dE_driftcorr->Fill(hitItem.Get_travmusic_dE_driftcorr());
    // //:: TM


    // if(hitItem.Get_travmusic_dE_driftcorr() >= frs_config->fMin_dE_travMus_gate && hitItem.Get_travmusic_dE_driftcorr() <= frs_config->fMax_dE_travMus_gate)
    // {
    //     h2_Z_vs_AoQ_tac_trav_gate_driftcorr->Fill(hitItem.Get_ID_AoQ_driftcorr(), hitItem.Get_ID_z_driftcorr());
    // }

    // if(hitItem.Get_travmusic_dE() >= frs_config->fMin_dE_travMus_gate && hitItem.Get_travmusic_dE() <= frs_config->fMax_dE_travMus_gate)
    // {
    //     h2_Z_vs_AoQ_driftcorr_trav_gate->Fill(hitItem.Get_ID_AoQ_driftcorr(), hitItem.Get_ID_z_driftcorr());
    // }

    fNEvents += 1;
}

void TravMusNearlineSpectra::FinishEvent()
{

}

void TravMusNearlineSpectra::FinishTask()
{   

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_travmus->Write();
    c4LOG(info, "Written travMUSIC analysis histograms to file.");

}

ClassImp(TravMusNearlineSpectra)
