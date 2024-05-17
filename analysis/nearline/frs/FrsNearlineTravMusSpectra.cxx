// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"

// c4
#include "FrsTravMusSpectra.h"
#include "FrsNearlineTravMusSpectra.h"
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


FrsNearlineTravMusSpectra::FrsNearlineTravMusSpectra() : FrsNearlineTravMusSpectra("FrsNearlineTravMusSpectra")
{
    frs_config = TFrsConfiguration::GetInstance();
}

FrsNearlineTravMusSpectra::FrsNearlineTravMusSpectra(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , travMusicArray(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
    frs_config = TFrsConfiguration::GetInstance();
}

FrsNearlineTravMusSpectra::~FrsNearlineTravMusSpectra()
{
    c4LOG(info, "");
}

InitStatus FrsNearlineTravMusSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    travMusicArray = mgr->InitObjectAs<decltype(travMusicArray)>("FrsTravMusCalData");
    c4LOG_IF(fatal, !travMusicArray, "Branch FrsTravMusCalData not found!");
    
    //TDirectory::TContext ctx(nullptr);

    FairRootManager::Instance()->GetOutFile()->cd();
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

    return kSUCCESS;

}


void FrsNearlineTravMusSpectra::Exec(Option_t* option)
{

    uint64_t wr_travMUSIC = 0;
    for (auto const & travMusicItem : *travMusicArray)
    {
        wr_travMUSIC = travMusicItem.Get_wr_t();
        if( wr_travMUSIC == 0) return;
        for (int i = 0; i < 8; i++)
        {
            h1_travmus_raw_adc[i]->Fill(travMusicItem.Get_music_energy(i));

            //c4LOG(info,"adc number : " << i << "raw adc : " << travMusicItem.Get_music_energy(i));
        }
    }
    

    fNEvents += 1;
}

void FrsNearlineTravMusSpectra::FinishEvent()
{

}

void FrsNearlineTravMusSpectra::FinishTask()
{   

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_travmus->Write();
    c4LOG(info, "Written travMUSIC analysis histograms to file.");

}

ClassImp(FrsNearlineTravMusSpectra)
