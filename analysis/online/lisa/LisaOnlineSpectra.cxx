// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "EventHeader.h"
#include "LisaOnlineSpectra.h"
#include "LisaData.h"
#include "LisaTraceData.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

LisaOnlineSpectra::LisaOnlineSpectra()
{
}

LisaOnlineSpectra::LisaOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitLisa(NULL)
    , fNEvents(0)
    , header(nullptr)
    // ranges
{
}

LisaOnlineSpectra::~LisaOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitLisa)
        delete fHitLisa;
}

void LisaOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus LisaOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitLisa = (TClonesArray*)mgr->GetObject("LisaData");
    c4LOG_IF(fatal, !fHitLisa, "Branch LisaData not found!");

    //sum time spectrum
    // spectra definition

    //Define histograms
    //:::::::::::Hit Pattern
    
    TFolder *lisaFold = new TFolder("Lisa", "Lisa");
    
    run->AddObject(lisaFold);

    h1_hitpattern = new TH1I("h1_hitpattern","LISA Hit Pattern",16,0,16);
    //set visual stuff for histo

    lisaFold->Add(h1_hitpattern);

    h1_energy = new TH1F("h1_energy", "LISA Energy", 400,0,1000000); //in case of data from 241Am
    lisaFold->Add(h1_energy);

    //h1_energy = new TH1I("h1_energy", "LISA Energy", 400,0,1000000); //in case of data from 241Am
    //lisaFold->Add(h1_energy);



    run->GetHttpServer()->RegisterCommand("Reset_Lisa_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void LisaOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    //fh1_SumTime->Reset();
}

void LisaOnlineSpectra::Exec(Option_t* option)
{   

    if (fHitLisa && fHitLisa->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitLisa->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            LisaData* hit = (LisaData*)fHitLisa->At(ihit);
            if (!hit)
                continue;
            
            std::vector<int> hit_pattern = hit->GetHitPattern(); 
            for (int n = 0; n< hit_pattern.size(); n++ )
            {
                h1_hitpattern->Fill(hit_pattern[n]);
            }

            //get stuff looping over M
            std::vector<uint32_t> ch_energy = hit->GetEnergy(); 
            for (int index = 0; index < M; index++)
            {
                h1_energy->Fill(ch_energy[index]);
            }
            
        }
    }

    fNEvents += 1;
}

void LisaOnlineSpectra::FinishEvent()
{
    if (fHitLisa)
    {
        fHitLisa->Clear();
    }
}

void LisaOnlineSpectra::FinishTask()
{
    if (fHitLisa)
    {
        //fh1_SumTime->Write();
    }
}

ClassImp(LisaOnlineSpectra)
