// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairSink.h"

// c4
#include "bPlastNearlineSpectra.h"
#include "EventHeader.h"
#include "bPlastTwinpeaksCalData.h"
#include "TbPlastConfiguration.h"

#include "c4Logger.h"

#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TROOT.h"
#include <chrono>

bPlastNearlineSpectra::bPlastNearlineSpectra() : bPlastNearlineSpectra("bPlastNearlineSpectra")
{
}

bPlastNearlineSpectra::bPlastNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitbPlastTwinpeaks(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

bPlastNearlineSpectra::~bPlastNearlineSpectra()
{
    c4LOG(info, "");
    if (fHitbPlastTwinpeaks)
        delete fHitbPlastTwinpeaks;
}

void bPlastNearlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus bPlastNearlineSpectra::Init()
{

    // set batch mode // ok but why here specifically?
    gROOT->SetBatch(kTRUE);

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitbPlastTwinpeaks = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitbPlastTwinpeaks, "Branch bPlastTwinpeaksCalData not found!");

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_bplast = gDirectory->mkdir("bPlast");
    gDirectory->cd("bPlast");

    dir_bplast_slowToT = gDirectory->mkdir("Slow ToT");
    dir_bplast_fastToT = gDirectory->mkdir("Fast ToT");
    dir_bplast_hitpattern = gDirectory->mkdir("Hit Pattern");
    dir_bplast_fast_vs_slow = gDirectory->mkdir("Fast Vs. Slow");
    dir_bplast_time_spectra = gDirectory->mkdir("Time Spectra");

    gDirectory = tmp;

    //dir_bplast = new TDirectory("bPlast", "bPlast", "", 0);
    //mgr->Register("bPlast", "bPlast Directory", dir_bplast, true); 

    /*
    dir_bplast_slowToT = dir_bplast->mkdir("Slow ToT");
    dir_bplast_fastToT = dir_bplast->mkdir("Fast ToT");
    dir_bplast_hitpattern = dir_bplast->mkdir("Hit Pattern");
    dir_bplast_fast_vs_slow = dir_bplast->mkdir("Fast Vs. Slow");
    dir_bplast_time_spectra = dir_bplast->mkdir("Time Spectra");
    */

    // bPlast Configuration
    bplast_conf = TbPlastConfiguration::GetInstance();
    nDetectors = bplast_conf->NDetectors();
    nTamexBoards = bplast_conf->NTamexBoards();

    
    // Setting histogram sizes
    h1_bplast_slowToT.resize(nDetectors+1); // index from 1 
    h1_bplast_fastToT.resize(nDetectors+1);
    h1_bplast_hitpatterns.resize(2); // this is hard coded yeah i know, but we aren't going to more bplasts?
    h1_bplast_tamex_card_hitpattern.resize(nTamexBoards);
    h2_bplast_fastToT_vs_slowToT.resize(nDetectors+1);
    h1_bplast_time_spectra.resize(nDetectors+1);

    // Slow ToT
    dir_bplast_slowToT->cd();
    for (int ihist = 1; ihist <= nDetectors; ihist++)
    {
        h1_bplast_slowToT[ihist] = new TH1F(Form("h1_bplast_slowToT_%d",ihist),Form("bPlastic Slow ToT %d",ihist),10000,0,3.5e3);
        h1_bplast_slowToT[ihist]->GetXaxis()->SetTitle("ToT (ns)");
    }


    // Fast ToT
    dir_bplast_fastToT->cd();
    for (int ihist = 1; ihist <= nDetectors; ihist++)
    {
        h1_bplast_fastToT[ihist] = new TH1F(Form("h1_bplast_fastToT_%d",ihist),Form("bPlastic Fast ToT %d",ihist),10000,0,3.5e3);
        h1_bplast_fastToT[ihist]->GetXaxis()->SetTitle("ToT (ns)"); 
    }

    // Hit Pattern
    dir_bplast_hitpattern->cd();

    h1_bplast_hitpatterns[0] = new TH1F("h1_bplast_hitpattern_upstream","Upstream detector hit patterns",64,1,65);
    h1_bplast_hitpatterns[0]->GetXaxis()->SetTitle("Detector ID");
    h1_bplast_hitpatterns[0]->GetYaxis()->SetTitle("Counts");
    
    h1_bplast_hitpatterns[1] = new TH1F("h1_bplast_hitpattern_downstream","Downstream detector hit patterns",64,65,129);
    h1_bplast_hitpatterns[1]->GetXaxis()->SetTitle("Detector ID");
    h1_bplast_hitpatterns[1]->GetYaxis()->SetTitle("Counts");

    // tamex card hit pattern
    for (int ihist = 0; ihist < nTamexBoards; ihist++)
    {
        h1_bplast_tamex_card_hitpattern[ihist] = new TH1F(Form("h1_bplast_tamex_card_hitpattern_%d",ihist),Form("bPlastic Tamex Card Hit Pattern %d",ihist),16,1,17);
        h1_bplast_tamex_card_hitpattern[ihist]->GetXaxis()->SetTitle("Channel");
        h1_bplast_tamex_card_hitpattern[ihist]->GetYaxis()->SetTitle("Counts");
    }

    // Time spectra
    dir_bplast_time_spectra->cd();
    for (int ihist = 1; ihist <= nDetectors; ihist++)
    {
        h1_bplast_time_spectra[ihist] = new TH1F(Form("h1_bplast_time_spectra_%d",ihist),Form("bPlast Time spectrum detector %d",ihist),10000,0,6e10);
        h1_bplast_time_spectra[ihist]->GetXaxis()->SetTitle("Time (ns)");
    }

    dir_bplast_fast_vs_slow->cd();
    for (int ihist = 1; ihist <= nDetectors; ihist++)
    {
        h2_bplast_fastToT_vs_slowToT[ihist] = new TH2F(Form("h1_bplast_fast_v_slow_%d",ihist),Form("bplast fast vs. slow detector %d",ihist),1000,0,3.5e3,1000,0,3.5e3);
        h2_bplast_fastToT_vs_slowToT[ihist]->GetXaxis()->SetTitle("Slow ToT (ns)");
        h2_bplast_fastToT_vs_slowToT[ihist]->GetYaxis()->SetTitle("Fast ToT (ns)");
        h2_bplast_fastToT_vs_slowToT[ihist]->SetOption("COLZ");
    }

    dir_bplast_hitpattern->cd();

    h1_bplast_multiplicity = new TH1F("Multiplicity","bPlast multiplicity",128,1,129);
    h1_bplast_multiplicity->GetXaxis()->SetTitle("Event Multilplicity");
    h1_bplast_multiplicity->GetYaxis()->SetTitle("Counts");
    // log y?

    dir_bplast->cd();

    return kSUCCESS;
}

void bPlastNearlineSpectra::Exec(Option_t* option)
{   
    auto start = std::chrono::high_resolution_clock::now();
        
    bplast_map = bplast_conf->Mapping();

    if (fHitbPlastTwinpeaks && fHitbPlastTwinpeaks->GetEntriesFast() > 0)
    {
        event_multiplicity = 0;
        Int_t nHits = fHitbPlastTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            bPlastTwinpeaksCalData* hit = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(ihit);
            if (!hit) continue;
            event_multiplicity ++;
            
            double slowToT = hit->Get_slow_ToT();
            double fastToT = hit->Get_fast_ToT();
            double fast_lead_time = hit->Get_fast_lead_time();
            
            int detector_id = hit->Get_detector_id();

            if (detector_id > nDetectors || detector_id < 0) continue;

            // Lead and Trail spectra -- empty for now
            h1_bplast_time_spectra[detector_id]->Fill(fast_lead_time);

            // Fast and Slow Tot spectra
            h1_bplast_slowToT[detector_id]->Fill(slowToT);
            h1_bplast_fastToT[detector_id]->Fill(fastToT);

            h2_bplast_fastToT_vs_slowToT[detector_id]->Fill(slowToT,fastToT);

            // Hit pattern spectra
            // the hit pattern spectrum is generated by filling the histogram with the detector ID of the hit
            for (const auto& entry : bplast_map)
            {
                if (entry.second.first == detector_id)
                {
                    if (entry.second.second.first == 'U') h1_bplast_hitpatterns[0]->Fill(detector_id);
                    if (entry.second.second.first == 'D') h1_bplast_hitpatterns[1]->Fill(detector_id);

                    for (int i = 0; i < nTamexBoards; i++)
                    {
                        if (entry.first.first == i)
                        {
                            h1_bplast_tamex_card_hitpattern[i]->Fill(entry.first.second);
                        }
                    }
                }

            }


        }
        h1_bplast_multiplicity->Fill(event_multiplicity);
    }
    fNEvents += 1;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void bPlastNearlineSpectra::FinishEvent()
{
    if (fHitbPlastTwinpeaks)
    {
        fHitbPlastTwinpeaks->Clear();
    }
}

void bPlastNearlineSpectra::FinishTask()
{
    if(fNEvents == 0)
    { 
        c4LOG(warn, "No events found, not saving histograms!");
        return;
    }

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_bplast->Write();
    gDirectory = tmp;

    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");

}


    ClassImp(bPlastNearlineSpectra)
