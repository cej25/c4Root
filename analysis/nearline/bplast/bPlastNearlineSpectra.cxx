// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairSink.h"

// c4
#include "bPlastNearlineSpectra.h"
#include "EventHeader.h"
#include "bPlastTwinpeaksCalData.h"
#include "TbPlastConfiguration.h"

#include "AnalysisTools.h"
#include "c4Logger.h"

#include "TClonesArray.h"
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
    dir_bplast_rates = dir_bplast->mkdir("Rates");

    // bPlast Configuration
    bplast_conf = TbPlastConfiguration::GetInstance();
    nDetectors = bplast_conf->NDetectors();
    nTamexBoards = bplast_conf->NTamexBoards();

    // Experiment Configuration
    exp_conf = TExperimentConfiguration::GetInstance();
    int64_t exp_start = exp_conf->exp_start_time;
    int64_t exp_end = exp_conf->exp_end_time;
    int64_t exp_duration = exp_end - exp_start;
    
    // Setting histogram sizes
    h1_bplast_slowToT.resize(nDetectors+1); // index from 1 
    h1_bplast_fastToT.resize(nDetectors+1);
    h1_bplast_hitpatterns.resize(2); // this is hard coded yeah i know, but we aren't going to more bplasts?
    h1_bplast_tamex_card_hitpattern.resize(nTamexBoards);
    h2_bplast_fastToT_vs_slowToT.resize(nDetectors+1);
    h1_bplast_time_spectra.resize(nDetectors+1);

    // Slow ToT
    for (int ihist = 1; ihist <= nDetectors; ihist++)
    {
        h1_bplast_slowToT[ihist] = MakeTH1(dir_bplast_slowToT, "F", Form("h1_bplast_slowToT_%d",ihist),Form("bPlastic Slow ToT %d",ihist), 1e4, 0, 3.5e3, "ToT [ns]", kSpring, kBlue+2);
    }

    // Fast ToT
    for (int ihist = 1; ihist <= nDetectors; ihist++)
    {
        h1_bplast_fastToT[ihist] = MakeTH1(dir_bplast_fastToT, "F", Form("h1_bplast_fastToT_%d",ihist),Form("bPlastic Fast ToT %d",ihist), 1e4, 0, 3.5e3, "ToT [ns]", kSpring, kBlue+2);
    }

    // Hit Pattern
    h1_bplast_hitpatterns[0] = MakeTH1(dir_bplast_hitpattern, "F", "h1_bplast_hitpattern_upstream","Upstream detector hit patterns",64,1,65, "Detector ID", kRed-3, kBlack);
    h1_bplast_hitpatterns[1] = MakeTH1(dir_bplast_hitpattern, "F", "h1_bplast_hitpattern_downstream","Downstream detector hit patterns",64,65,129, "Detector ID", kRed-3, kBlack);
    
    // tamex card hit pattern
    for (int ihist = 0; ihist < nTamexBoards; ihist++)
    {
        h1_bplast_tamex_card_hitpattern[ihist] = MakeTH1(dir_bplast_hitpattern, "I", Form("h1_bplast_tamex_card_hitpattern_%d",ihist),Form("bPlastic Tamex Card Hit Pattern %d",ihist),16,1,17, "Channel", kRed-3, kBlack);
    }

    // Time spectra - CEJ: not in online currently.
    for (int ihist = 1; ihist <= nDetectors; ihist++)
    {
        h1_bplast_time_spectra[ihist] = MakeTH1(dir_bplast_time_spectra, "F", Form("h1_bplast_time_spectra_%d",ihist),Form("bPlast Time spectrum detector %d",ihist), 1e4, 0, 6e10, "Time [ns]");
    }

    // fast vs slow
    for (int ihist = 1; ihist <= nDetectors; ihist++)
    {
        h2_bplast_fastToT_vs_slowToT[ihist] = MakeTH2(dir_bplast_fast_vs_slow, "F", Form("h1_bplast_fast_v_slow_%d",ihist),Form("bplast fast vs. slow detector %d",ihist), 1e3, 0, 3.5e3, 1e3, 0, 3.5e3, "Slow ToT [ns]", "Fast ToT [ns]");
    }

    h1_bplast_multiplicity = MakeTH1(dir_bplast_hitpattern, "I", "Multiplicity","bPlast multiplicity",128,1,129, "Event Multiplicity", kRed-3, kBlack);
    // log y?

    detector_counters = new int[nDetectors+1];
    detector_rates = new int[nDetectors+1];
    h1_bplast_rates.resize(nDetectors+1);
    for(int ihist = 1; ihist <= nDetectors; ihist++)
    {
        h1_bplast_rates[ihist] = MakeTH1(dir_bplast_rates,"I",Form("h1_bplast_rates_%d",ihist),Form("bPlast Rates for Channel %d",ihist),exp_duration/6e11,0,exp_duration/6e10,"Time [10 minute binning]",kCyan,kBlack);
    }

    dir_bplast->cd();
    gDirectory = tmp;

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
            detector_counters[detector_id]++;

            if (detector_id > nDetectors || detector_id < 0) continue;

            // Lead and Trail spectra -- empty for now
            h1_bplast_time_spectra[detector_id]->Fill(fast_lead_time);

            // Fast and Slow Tot spectra
            h1_bplast_slowToT[detector_id]->Fill(slowToT);
            h1_bplast_fastToT[detector_id]->Fill(fastToT);

            h2_bplast_fastToT_vs_slowToT[detector_id]->Fill(slowToT,fastToT);

            // Rates over whole experiment in 10 minute chunks
            bPlastTwinpeaksCalData* wr_hit = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
            wr_t = wr_hit->Get_wr_t();
            int64_t wr_dt = (wr_t - wr_prev1s)/6e10; // minutes
            if (wr_dt > 10) 
            {
                if (wr_prev1s != 0)
                {
                    for (int i = 1; i <= nDetectors; i++)
                    {
                        detector_rates[i] = detector_counters[i] / wr_dt;
                        h1_bplast_rates[i]->SetBinContent(rate_running_count, detector_rates[i]);
                    }
                }
                
                wr_prev1s = wr_t;
                rate_running_count++;
                // for (int i = 1; i <= nDetectors; i++) 
                // {
                //     if (rate_running_count == 1800) h1_bplast_rates[i]->Reset();
                //     detector_counters[i] = 0;
                // }
                // if (rate_running_count == 1800) rate_running_count = 0;
            }
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
