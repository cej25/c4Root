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
 *                              24.11.24                                      *
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
    dir_raw_adc->cd();

    //:::::::::: Raw ADC ::::::::::::::::
    c_raw_adc = new TCanvas("c_raw_adc", "Travel MUSIC Raw ADC", 650, 350);
    c_raw_adc->Divide(4, 2);
    for (int i = 0; i < 8; i++)
    {
        c_raw_adc->cd(i+1);
        h1_travmus_raw_adc[i] = new TH1I(Form("h1_travmus_raw_adc_anode_%i", i), Form("Raw ADC - Travel MUSIC Anode %i", i), 10500, 100, 12500);
        h1_travmus_raw_adc[i]->SetFillColor(kPink-3);
        h1_travmus_raw_adc[i]->Draw();
    }
    c_raw_adc->cd(0);
    dir_raw_adc->Append(c_raw_adc);


    dir_travmus->cd();

    // histos to add, or not
    // h2_travmus_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_travmus_vs_Z", "Z (Travel MUSIC) vs Z (MUSIC 1)", 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_Z, frs_config->fMax_Z, "Z (Travel MUSIC)", "Z (MUSIC 1)");
    // h1_Z_travmus = MakeTH1(dir_tac_1d, "D", "h1_Z_travmus", "Z (Travel MUSIC)", 750, 10, 100, "Z (Travel MUSIC)", kPink-3, kBlue+2);

    // h1_travmus_dE = MakeTH1(dir_tac_1d, "D", "h1_travmus_dE", "dE (Travel MUSIC)", 1000, 0, 4000., "dE (Travel MUSIC)", kPink-3, kBlue+2);

    // h2_travmus_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_travmus_vs_Z_mhtdc", "Z (Trav) vs. Z1 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z (Travel MUSIC)", "Z (MUSIC 1)");
    
    // h1_z_travmus_mhtdc = MakeTH1(dir_mhtdc_1d, "D", "h1_z_travmus_mhtdc", "Z (Travel MUSIC) (MHTDC)", 1000, 0, 100, "Z (Travel MUSIC)", kPink-3, kBlue+2);

    // h2_Z_vs_AoQ_mhtdc_trav_gate = MakeTH2(dir_travmus, "D", "h2_Z_vs_AoQ_mhtdc_trav_gate", "Z1 vs. A/Q (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);

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
