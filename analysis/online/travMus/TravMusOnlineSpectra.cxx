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
#include "TravMusOnlineSpectra.h"
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
#include "TFrsConfiguration.h"


TravMusOnlineSpectra::TravMusOnlineSpectra()
    :   FairTask()
    ,   travMusCalArray(nullptr)
    ,   travMusAnaArray(nullptr)
    ,   fNEvents(0)
    ,   header(nullptr)
{
    frs_config = TFrsConfiguration::GetInstance();
}

TravMusOnlineSpectra::TravMusOnlineSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   travMusCalArray(nullptr)
    ,   travMusAnaArray(nullptr)
    ,   fNEvents(0)
    ,   header(nullptr)
{
    frs_config = TFrsConfiguration::GetInstance();
}

TravMusOnlineSpectra::~TravMusOnlineSpectra()
{
    c4LOG(info, "");
}

InitStatus TravMusOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    travMusCalArray = mgr->InitObjectAs<decltype(travMusCalArray)>("TravMusCalData");
    c4LOG_IF(fatal, !travMusCalArray, "Branch TravMusCalData not found!");

    travMusAnaArray = mgr->InitObjectAs<decltype(travMusAnaArray)>("TravMusAnaData");
    c4LOG_IF(fatal, !travMusAnaArray, "Branch TravMusAnaData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");
    
    TDirectory::TContext ctx(nullptr);

    dir_travmus = (TDirectory*)mgr->GetObject("Travel MUSIC");
    if (dir_travmus == nullptr) 
    {
        LOG(info) << "Creating Travel MUSIC Directory";
        dir_travmus = new TDirectory("Travel MUSIC", "Travel MUSIC", "", 0);
        mgr->Register("Travel MUSIC", "Travel MUSIC Directory", dir_travmus, false); // allow other tasks to find this
        histograms->Add(dir_travmus);
    }
    
    dir_raw_adc = dir_travmus->mkdir("Raw ADC");
    
    dir_raw_adc->cd();

    c_raw_adc = new TCanvas("c_raw_adc", "Travel MUSIC Raw ADC", 650, 350);
    c_raw_adc->Divide(4, 2);
    for (int i = 0; i < 8; i++)
    {
        c_raw_adc->cd(i+1);
        h1_travmus_raw_adc[i] = new TH1I(Form("h1_travmus_raw_adc_anode_%i", i), Form("Raw ADC - Travel MUSIC Anode %i", i), 10500, 100, 60500);
        h1_travmus_raw_adc[i]->SetFillColor(kPink-3);
        h1_travmus_raw_adc[i]->Draw();
    }
    c_raw_adc->cd(0);
    dir_raw_adc->Append(c_raw_adc);

    
    h1_travmus_dE = MakeTH1(dir_travmus, "D", "h1_travmus_dE", "dE (Travel MUSIC)", 1000, 0, 4000., "dE (Travel MUSIC)", kPink-3, kBlue+2);


    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_TravMus_Histo", Form("/Objects/%s/->Reset_Histo()", GetName()));


    dir_travmus->cd();

    return kSUCCESS;

}

void TravMusOnlineSpectra::Reset_Histo()
{
    c4LOG(warn,"TravMus Spectra Reset (not yet)");
}


void TravMusOnlineSpectra::Exec(Option_t* option)
{
    uint64_t wr_travMUSIC = 0;
    for (auto const & travMusicItem : *travMusCalArray)
    {
        wr_travMUSIC = travMusicItem.Get_wr_t();
        if( wr_travMUSIC == 0) return;
        for (int i = 0; i < 8; i++)
        {
            h1_travmus_raw_adc[i]->Fill(travMusicItem.Get_music_energy(i));

            //c4LOG(info,"adc number : " << i << "raw adc : " << travMusicItem.Get_music_energy(i));
        }

        // dE spectra for online? 
    }

    const auto & travMusicHitItem = travMusAnaArray->at(0); 

    if (travMusicHitItem.Get_wr_t() > 0 && travMusicHitItem.Get_travmusic_dE() > 0) h1_travmus_dE->Fill(travMusicHitItem.Get_travmusic_dE());


    // need Sci S1
    // if (trav_mus_wr > 0 && hitItem.Get_ID_z_travmus() > 0) h1_Z_travmus->Fill(hitItem.Get_ID_z_travmus());
    
    // need Sci S1
    // if (trav_mus_wr > 0 && multihitItem.Get_ID_z_mhtdc() > 0 && multihitItem.Get_ID_z_travmus_mhtdc() > 0) h2_travmus_vs_Z_mhtdc->Fill(multihitItem.Get_ID_z_travmus_mhtdc(), multihitItem.Get_ID_z_mhtdc());
    
    // need Sci S1
    // if (trav_mus_wr > 0 && multihitItem.Get_ID_z_travmus_mhtdc() > 0) h1_z_travmus_mhtdc->Fill(multihitItem.Get_ID_z_travmus_mhtdc());

    // need Sci S1
    // if (multihitItem.Get_ID_z_travmus_mhtdc() > 0) h1_z_travmus_mhtdc->Fill(multihitItem.Get_ID_z_travmus_mhtdc());
  

    fNEvents += 1;
}

void TravMusOnlineSpectra::FinishEvent()
{

}

void TravMusOnlineSpectra::FinishTask()
{   

}

ClassImp(TravMusOnlineSpectra)
