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
 *                       J.P. Bormans, C.E. Jones                             *
 *                              17.12.24                                      *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "bPlastOnlineSpectra.h"
#include "EventHeader.h"
#include "bPlastTwinpeaksCalData.h"
#include "TbPlastConfiguration.h"

#include "AnalysisTools.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TROOT.h"
#include <chrono>
#include <TKey.h>

bPlastOnlineSpectra::bPlastOnlineSpectra() : bPlastOnlineSpectra("bPlastOnlineSpectra")
{
}

bPlastOnlineSpectra::bPlastOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitbPlastTwinpeaks(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

bPlastOnlineSpectra::~bPlastOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitbPlastTwinpeaks) delete fHitbPlastTwinpeaks;
}

void bPlastOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus bPlastOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitbPlastTwinpeaks = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitbPlastTwinpeaks, "Branch bPlastTwinpeaksCalData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_bplast = new TDirectory("bPlast","bPlast", "", 0);
    // mgr->Register("bPlast", "bPlast Directory", dir_bplast, false); // allow other tasks to access directory.
    histograms->Add(dir_bplast);

    dir_bplast_slowToT = dir_bplast->mkdir("Slow ToT");
    dir_bplast_fastToT = dir_bplast->mkdir("Fast ToT");
    dir_bplast_hitpattern = dir_bplast->mkdir("Hit Pattern");
    dir_bplast_fast_vs_slow = dir_bplast->mkdir("Fast Vs. Slow");
    dir_bplast_rates = dir_bplast->mkdir("Rates");

    // bPlast Configuration
    bplast_conf = TbPlastConfiguration::GetInstance();
    bplast_map = bplast_conf->Mapping();
    nDetectors = bplast_conf->NDetectors();
    nTamexBoards = bplast_conf->NTamexBoards();

    // Setting histogram sizes
    h1_bplast_slowToT.resize(nDetectors+1); // index from 1 
    h1_bplast_fastToT.resize(nDetectors+1);
    h1_bplast_hitpatterns.resize(2); // this is hard coded yeah i know, but we aren't going to more bplasts? - JB no probably not but this is a limited case
    h1_bplast_multiplicity.resize(6);
    h1_bplast_tamex_card_hitpattern.resize(nTamexBoards+1);
    h2_bplast_fastToT_vs_slowToT.resize(nDetectors+1);

    // Slow ToT
    c_bplast_slowToT  = new TCanvas("c_bplast_slowToT","slow ToT bPlast spectra",1200,800);
    c_bplast_slowToT->Divide(5,(nDetectors%5==0) ? (nDetectors/5) : (nDetectors/5 + 1));
    h1_bplast_slowToT.resize(nDetectors+1); // index from 1
    for (int ihist = 1; ihist <= nDetectors; ihist++)
    {
        c_bplast_slowToT->cd(ihist);
        h1_bplast_slowToT[ihist] = MakeTH1(dir_bplast_slowToT, "F", Form("h1_bplast_slowToT_%d",ihist),Form("bPlastic Slow ToT %d",ihist), 1e4, 0, 3.5e3, "ToT [ns]", kSpring, kBlue+2);
        h1_bplast_slowToT[ihist]->Draw();
    }
    c_bplast_slowToT->cd(0);
    dir_bplast_slowToT->Append(c_bplast_slowToT);

    // Fast ToT
    c_bplast_fastToT  = new TCanvas("c_bplast_fastToT","Fast ToT bPlast spectra",1200,800);
    c_bplast_fastToT->Divide(5,(nDetectors%5==0) ? (nDetectors/5) : (nDetectors/5 + 1));
    h1_bplast_fastToT.resize(nDetectors+1);
    for (int ihist = 1; ihist <= nDetectors; ihist++)
    {
        c_bplast_fastToT->cd(ihist);
        h1_bplast_fastToT[ihist] = MakeTH1(dir_bplast_fastToT, "F", Form("h1_bplast_fastToT_%d",ihist),Form("bPlastic Fast ToT %d",ihist),10000,0,3.5e3, "ToT [ns]", kSpring, kBlue+2);
        h1_bplast_fastToT[ihist]->Draw();   
    }
    c_bplast_fastToT->cd(0);
    dir_bplast_fastToT->Append(c_bplast_fastToT);

    // Hit Pattern
    dir_bplast_hitpattern->cd();
    c_bplast_hitpatterns = new TCanvas("c_bplast_hitpatterns","bPlast Hit Pattern",1200,800);
    c_bplast_hitpatterns->Divide(2,1);
    c_bplast_hitpatterns->cd(1);
    h1_bplast_hitpatterns.resize(2); // this is hard coded yeah i know, but we aren't going to more bplasts?
    h1_bplast_hitpatterns[0] = MakeTH1(dir_bplast_hitpattern, "F", "h1_bplast_hitpattern_upstream","Upstream detector hit patterns",64,1,65, "Detector ID", kRed-3, kBlack);
    h1_bplast_hitpatterns[0]->Draw();
    c_bplast_hitpatterns->cd(2);
    h1_bplast_hitpatterns[1] = MakeTH1(dir_bplast_hitpattern, "F", "h1_bplast_hitpattern_downstream","Downstream detector hit patterns",64,65,129, "Detector ID", kRed-3, kBlack);
    h1_bplast_hitpatterns[1]->Draw();
    c_bplast_hitpatterns->cd(0);
    dir_bplast_hitpattern->Append(c_bplast_hitpatterns);

    // tamex card hit pattern
    c_bplast_tamex_card_hitpattern  = new TCanvas("c_bplast_tamex_card_hitpattern","bPlast Tamex Card Hit Pattern",1200,800);
    c_bplast_tamex_card_hitpattern->Divide(5,(nTamexBoards%5==0) ? (nTamexBoards/5) : (nTamexBoards/5 + 1));
    h1_bplast_tamex_card_hitpattern.resize(nTamexBoards);
    for (int ihist = 0; ihist < nTamexBoards; ihist++)
    {
        c_bplast_tamex_card_hitpattern->cd(ihist+1);
        h1_bplast_tamex_card_hitpattern[ihist] = MakeTH1(dir_bplast_hitpattern, "I", Form("h1_bplast_tamex_card_hitpattern_%d",ihist),Form("bPlastic Tamex Card Hit Pattern %d",ihist),16,1,17, "Channel", kRed-3, kBlack);
        h1_bplast_tamex_card_hitpattern[ihist]->Draw();
    }
    c_bplast_tamex_card_hitpattern->cd(0);
    dir_bplast_hitpattern->Append(c_bplast_tamex_card_hitpattern);

    c_bplast_fast_v_slow  = new TCanvas("c_bplast_fast_v_slow","fast vs slow ToT bplast spectra",1200,800);
    c_bplast_fast_v_slow->Divide(5,(nDetectors%5==0) ? (nDetectors/5) : (nDetectors/5 + 1));
    h2_bplast_fastToT_vs_slowToT.resize(nDetectors+1);
    for (int ihist = 1; ihist <= nDetectors; ihist++)
    {
        c_bplast_fast_v_slow->cd(ihist);
        h2_bplast_fastToT_vs_slowToT[ihist] = MakeTH2(dir_bplast_fast_vs_slow, "F", Form("h1_bplast_fast_v_slow_%d",ihist),Form("bplast fast vs. slow detector %d",ihist),1000,0,3.5e3,1000,0,3.5e3, "Slow ToT [ns]", "Fast ToT [ns]");
        h2_bplast_fastToT_vs_slowToT[ihist]->Draw();
    }
    c_bplast_fast_v_slow->cd(0);
    dir_bplast_fast_vs_slow->Append(c_bplast_fast_v_slow);

    c_bplast_multiplicity  = new TCanvas("c_bplast_multiplicity","bPlast multiplicity spectra",1200,800);
    c_bplast_multiplicity->Divide(2,3);
    c_bplast_multiplicity->cd(1);
    h1_bplast_multiplicity[0] = MakeTH1(dir_bplast_hitpattern, "F", "h1_bplast_multiplicity_upstream","Upstream bPlast multiplicity => 2",64,0,64, "Channel Multiplicity", kRed-3, kBlack);
    h1_bplast_multiplicity[0]->Draw();
    c_bplast_multiplicity->cd(2);
    h1_bplast_multiplicity[1] = MakeTH1(dir_bplast_hitpattern, "F", "h1_bplast_multiplicity_downstream","Downstream bPlast multiplicity => 2",64,0,64, "Channel Multiplicity", kRed-3, kBlack);
    h1_bplast_multiplicity[1]->Draw();
    c_bplast_multiplicity->cd(3);
    h1_bplast_multiplicity[2] = MakeTH1(dir_bplast_hitpattern, "F", "h1_bplast_multiplicity_upstream_frs","Upstream bPlast multiplicity with FRS accepted",64,0,64, "Channel Multiplicity", kRed-3, kBlack);
    h1_bplast_multiplicity[2]->Draw();
    c_bplast_multiplicity->cd(4);
    h1_bplast_multiplicity[3] = MakeTH1(dir_bplast_hitpattern, "F", "h1_bplast_multiplicity_downstream_frs","Downstream bPlast multiplicity with FRS accepted",64,0,64, "Channel Multiplicity", kRed-3, kBlack);
    h1_bplast_multiplicity[3]->Draw();
    c_bplast_multiplicity->cd(5);
    h1_bplast_multiplicity[4] = MakeTH1(dir_bplast_hitpattern, "F", "h1_bplast_multiplicity_anticoincidence_frs_upstream","Upstream bPlast multiplicity with FRS anticoincidence",64,0,64, "Channel Multiplicity", kRed-3, kBlack);
    h1_bplast_multiplicity[4]->Draw();
    c_bplast_multiplicity->cd(6);
    h1_bplast_multiplicity[5] = MakeTH1(dir_bplast_hitpattern, "F", "h1_bplast_multiplicity_anticoincidence_frs_downstream","Downstream bPlast multiplicity with FRS anticoincidence",64,0,64, "Channel Multiplicity", kRed-3, kBlack);
    h1_bplast_multiplicity[5]->Draw();
    



    c_bplast_multiplicity->SetLogy();
    c_bplast_multiplicity->cd(0);
    dir_bplast_hitpattern->Append(c_bplast_multiplicity);

    c_bplast_wr_time_diff  = new TCanvas("c_bplast_wr_time_diff","bPlast WR time difference",1200,800);
    h1_bplast_wr_time_diff = MakeTH1(dir_bplast_hitpattern, "F", "h1_bplast_wr_time_diff","bPlast WR time difference",1e3,-1e2,5e5, "White Rabbit Event Time Difference [ns]", kViolet, kBlue+2);
    h1_bplast_wr_time_diff->Draw();
    c_bplast_wr_time_diff->cd(0);
    dir_bplast_hitpattern->Append(c_bplast_wr_time_diff);

    detector_counters = new int[nDetectors+1];
    detector_rates = new int[nDetectors+1];
    h1_bplast_rates.resize(nDetectors+1);
    for(int ihist = 1; ihist <= nDetectors; ihist++)
    {
        h1_bplast_rates[ihist] = MakeTH1(dir_bplast_rates,"I",Form("h1_bplast_rates_%d",ihist),Form("bPlast Rates for Channel %d",ihist),1800,0,1800,"Time [10 minute binning]",kCyan,kBlack);
    }

    run->GetHttpServer()->RegisterCommand("Reset_bPlast_Histos", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;

}

void bPlastOnlineSpectra::Reset_Histo() {
    c4LOG(info, "Resetting bPlast histograms.");

    // Assuming dir_bplast is a TDirectory pointer containing histograms
    if (dir_bplast) {
        AnalysisTools_H::ResetHistogramsInDirectory(dir_bplast);
        c4LOG(info, "bPlast histograms reset.");
    } else {
        c4LOG(error, "Failed to get list of histograms from directory.");
    }
}

void bPlastOnlineSpectra::Exec(Option_t* option)
{   
    auto start = std::chrono::high_resolution_clock::now();

    if (fHitbPlastTwinpeaks && fHitbPlastTwinpeaks->GetEntriesFast() > 0)
    {
        event_multiplicity_upstream = 0;
        event_multiplicity_downstream = 0;
        event_multiplicity_frs_upstream = 0;
        event_multiplicity_frs_downstream = 0;
        event_multiplicity_anticoincidence_frs_upstream = 0;
        event_multiplicity_anticoincidence_frs_downstream = 0;
        bool frs_accept = false;

        Int_t nHits = fHitbPlastTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            bPlastTwinpeaksCalData* hit = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(ihit);
            if (!hit) continue;
            
            // event_multiplicity_downstream ++;
            double slowToT = hit->Get_slow_ToT();
            double fastToT = hit->Get_fast_ToT();
            double fast_lead_time = hit->Get_fast_lead_time();
            
            int detector_id = hit->Get_detector_id();
            if(bplast_conf->FRS_ACCEPT() == detector_id) frs_accept = true; // we need to check it once through the event loop to see if it is ever true, it might come at the end and then we count wrong
            detector_counters[detector_id]++;

            if (detector_id > nDetectors || detector_id < 0) continue;

            // Fast and Slow Tot spectra
            h1_bplast_slowToT[detector_id]->Fill(slowToT);
            h1_bplast_fastToT[detector_id]->Fill(fastToT);

            h2_bplast_fastToT_vs_slowToT[detector_id]->Fill(slowToT,fastToT);

            // White Rabbit time difference
            bPlastTwinpeaksCalData* wr_hit = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
            wr_t = wr_hit->Get_wr_t();
            if (wr_t != wr_prev)
            {
                int64_t dt = wr_t - wr_prev;
                h1_bplast_wr_time_diff->Fill(dt);
            } 
            wr_prev = wr_t;

            int64_t wr_dt = (wr_t - wr_prev1s)/1e9;
            if (wr_dt > 1) 
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
                for (int i = 1; i <= nDetectors; i++) 
                {
                    if (rate_running_count == 1800) h1_bplast_rates[i]->Reset();
                    detector_counters[i] = 0;
                }
                if (rate_running_count == 1800) rate_running_count = 0;
            }
            


            // Hit pattern spectra
            // the hit pattern spectrum is generated by filling the histogram with the detector ID of the hit
            for (const auto& entry : bplast_map)
            {
                if (entry.second.first == detector_id && detector_id < 129)
                {
                    if (entry.second.second.first == 'U')
                    {
                        h1_bplast_hitpatterns[0]->Fill(detector_id);
                        event_multiplicity_upstream ++;
                    }
                    if (entry.second.second.first == 'D')
                    {
                        h1_bplast_hitpatterns[1]->Fill(detector_id);
                        event_multiplicity_downstream ++;
                    }
                }
                if (entry.second.first == detector_id)
                {
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

        // Now we handle if there is an FRS event
        if(frs_accept){ // we see FRS in the event
            for (Int_t ihit = 0; ihit < nHits; ihit++)
            {   
                bPlastTwinpeaksCalData* hit = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(ihit);
                if (!hit) continue;
                int detector_id = hit->Get_detector_id();

                for (const auto& entry : bplast_map)
                {
                    if (entry.second.first == detector_id && detector_id < 129)
                    {
                        if (entry.second.second.first == 'U')
                        {
                            event_multiplicity_frs_upstream ++;
                        }
                        if (entry.second.second.first == 'D')
                        {
                            event_multiplicity_frs_downstream ++;
                        }
                    }
                }

            }
        }
        else{ // we dont see FRS in the event
            for (Int_t ihit = 0; ihit < nHits; ihit++)
            {   
                bPlastTwinpeaksCalData* hit = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(ihit);
                if (!hit) continue;
                int detector_id = hit->Get_detector_id();

                for (const auto& entry : bplast_map)
                {
                    if (entry.second.first == detector_id && detector_id < 129)
                    {
                        if (entry.second.second.first == 'U')
                        {
                            event_multiplicity_anticoincidence_frs_upstream ++;
                        }
                        if (entry.second.second.first == 'D')
                        {
                            event_multiplicity_anticoincidence_frs_downstream ++;
                        }
                    }
                }
            }
        }
        // Fill the multiplicity histograms
        if(event_multiplicity_upstream >= 2) h1_bplast_multiplicity[0]->Fill(event_multiplicity_upstream);
        if(event_multiplicity_downstream >= 2) h1_bplast_multiplicity[1]->Fill(event_multiplicity_downstream);
        if(event_multiplicity_frs_upstream >= 2) h1_bplast_multiplicity[2]->Fill(event_multiplicity_frs_upstream);
        if(event_multiplicity_frs_downstream >= 2) h1_bplast_multiplicity[3]->Fill(event_multiplicity_frs_downstream);
        if(event_multiplicity_anticoincidence_frs_upstream >= 2) h1_bplast_multiplicity[4]->Fill(event_multiplicity_anticoincidence_frs_upstream);
        if(event_multiplicity_anticoincidence_frs_downstream >= 2) h1_bplast_multiplicity[5]->Fill(event_multiplicity_anticoincidence_frs_downstream);

    }
    fNEvents += 1;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void bPlastOnlineSpectra::FinishEvent()
{
    if (fHitbPlastTwinpeaks)
    {
        fHitbPlastTwinpeaks->Clear();
    }
}

void bPlastOnlineSpectra::FinishTask()
{
    if(fNEvents == 0)
    { 
        c4LOG(warn, "No events found, not saving histograms!");
        return;
    }
   
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents << " microseconds.");
    
}

ClassImp(bPlastOnlineSpectra)
