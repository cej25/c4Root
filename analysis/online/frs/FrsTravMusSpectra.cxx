// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"

// c4
#include "FrsTravMusSpectra.h"
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


FrsTravMusSpectra::FrsTravMusSpectra()
    : FairTask()
    , travMusicArray(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
    frs_config = TFrsConfiguration::GetInstance();
}

FrsTravMusSpectra::FrsTravMusSpectra(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , travMusicArray(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
    frs_config = TFrsConfiguration::GetInstance();
}

FrsTravMusSpectra::~FrsTravMusSpectra()
{
    c4LOG(info, "");
}

InitStatus FrsTravMusSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    travMusicArray = mgr->InitObjectAs<decltype(travMusicArray)>("FrsTravMusCalData");
    c4LOG_IF(fatal, !travMusicArray, "Branch FrsTravMusCalData not found!");

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
        h1_travmus_raw_adc[i] = new TH1I(Form("h1_travmus_raw_adc_anode_%i", i), Form("Raw ADC - Travel MUSIC Anode %i", i), 10500, 100, 12500);
        h1_travmus_raw_adc[i]->SetFillColor(kPink-3);
        h1_travmus_raw_adc[i]->Draw();
    }
    c_raw_adc->cd(0);
    dir_raw_adc->Append(c_raw_adc);

    


    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_TravMus_Histo", Form("/Objects/%s/->Reset_Histo()", GetName()));


    dir_travmus->cd();

    return kSUCCESS;

}

void FrsTravMusSpectra::Reset_Histo()
{
    c4LOG(warn,"TravMus Spectra Reset (not yet)");
}


void FrsTravMusSpectra::Exec(Option_t* option)
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

void FrsTravMusSpectra::FinishEvent()
{

}

void FrsTravMusSpectra::FinishTask()
{   

}

ClassImp(FrsTravMusSpectra)
