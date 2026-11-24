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
 *                         J.E.L. Larsson, C.E. Jones                         *
 *                               17.12.24                                     *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "TimeMachineNearline.h"
#include "EventHeader.h"
#include "TimeMachineData.h"
#include "TCorrelationsConfiguration.h"

#include "c4Logger.h"

#include "TClonesArray.h"
#include "TMath.h"
#include "TRandom.h"
#include "TDirectory.h"
#include <iostream>
#include <vector>
#include <string>
#include "TFile.h"

TimeMachineNearline::TimeMachineNearline() 
    : TimeMachineNearline("TimeMachineNearline")
    {
        correl_config = TCorrelationsConfiguration::GetInstance();
        Correl = correl_config->CorrelationsMap();
        TMGates = correl_config->TimeMachineMap();
    }

TimeMachineNearline::TimeMachineNearline(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fTimeMachine(NULL)
    , fNEvents(0)
    , header(nullptr)
{
    correl_config = TCorrelationsConfiguration::GetInstance();
    Correl = correl_config->CorrelationsMap();
    TMGates = correl_config->TimeMachineMap();
}

TimeMachineNearline::~TimeMachineNearline()
{
    c4LOG(info, "");
    if (fTimeMachine) 
    {
        for (int i = 0; i<fNumDetectorSystems; i++) delete fTimeMachine[i];
        delete[] fTimeMachine;
    }
}

void TimeMachineNearline::SetDetectorSystems(std::vector<TString> detectorsystems)
{
    
    
    fNumDetectorSystems = detectorsystems.size();
    
    fDetectorSystems = std::vector<TString>(0);

    std::string det_log;
    for (int i = 0; i < fNumDetectorSystems; i++) 
    {
        fDetectorSystems.push_back(detectorsystems.at(i));
        if (i < fNumDetectorSystems - 1) det_log += std::string(detectorsystems.at(i).Data()) + ", ";
        else det_log += std::string(detectorsystems.at(i).Data());
    }

    c4LOG(info, "Success: " + det_log);

}

InitStatus TimeMachineNearline::Init()
{
    c4LOG_IF(fatal, (fNumDetectorSystems == 0) || (fNumDetectorSystems < 0), "Detector systems not specified for TimeMachineNearline. Please add SetDetectorSystems before Init().");

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    fTimeMachine = new TClonesArray*[fNumDetectorSystems];

    for (int det = 0; det<fNumDetectorSystems; det++)
    {
        fTimeMachine[det] = (TClonesArray*) mgr->GetObject(fDetectorSystems.at(det)+"TimeMachineData");
        c4LOG_IF(fatal, !fTimeMachine[det], "Branch TimeMachineData not found!");
    }

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_time_machine = gDirectory->mkdir("TimeMachines");
    gDirectory->cd("TimeMachines");

    // do we even need/use these?
    dir_time_machine_undelayed = dir_time_machine->mkdir("Time Machine Undelayed");
    dir_time_machine_delayed = dir_time_machine->mkdir("Time Machine Delayed");
    dir_time_machine_diff = dir_time_machine->mkdir("Time Machine Difference");
    dir_time_machine_corrs = dir_time_machine->mkdir("Time Machine Correlations");

    h1_time_undelayed.resize(fNumDetectorSystems);
    h1_time_delayed.resize(fNumDetectorSystems);
    h1_time_diff.resize(fNumDetectorSystems*(fNumDetectorSystems - 1));
    h2_time_diff_corrs.resize((fNumDetectorSystems*fNumDetectorSystems)*(fNumDetectorSystems*fNumDetectorSystems-1)); // pairs from n items
    
    dir_time_machine_undelayed->cd();
    for (int ihist = 0; ihist < fNumDetectorSystems; ihist++)
    {
        h1_time_undelayed[ihist] = new TH1F("time_undelayed_"+fDetectorSystems.at(ihist),"time_undelayed_"+fDetectorSystems.at(ihist),500,165e12,166e12);
        h1_time_undelayed[ihist]->GetXaxis()->SetTitle("time (ns)");
    }

    dir_time_machine_delayed->cd();
    for (int ihist = 0; ihist < fNumDetectorSystems; ihist++)
    {
        h1_time_delayed[ihist] = new TH1F("time_delayed_"+fDetectorSystems.at(ihist),"time_delayed_"+fDetectorSystems.at(ihist),500,165e12,166e12);
        h1_time_delayed[ihist]->GetXaxis()->SetTitle("time (ns)");
    }

    dir_time_machine_diff->cd();
    for (int ihist = 0; ihist < fNumDetectorSystems; ihist++)
    {
        h1_time_diff[ihist] = new TH1F("time_diff_"+fDetectorSystems.at(ihist),"time_diff_"+fDetectorSystems.at(ihist),1000,-100,2000);
        h1_time_diff[ihist]->GetXaxis()->SetTitle("time (ns)");
    }

    dir_time_machine_corrs->cd();
    for (int ihist = 0; ihist < fNumDetectorSystems; ihist++)
    {
        for (int ihist2 = ihist + 1; ihist2 < fNumDetectorSystems; ihist2++)
        {
            h2_time_diff_corrs[ihist*fNumDetectorSystems + ihist2] = new TH2F("time_corr_" + fDetectorSystems.at(ihist) + "_" + fDetectorSystems.at(ihist2),"time_corr_" + fDetectorSystems.at(ihist) + "_" + fDetectorSystems.at(ihist2),250,-100,1600,250,-100,1600);
            h2_time_diff_corrs[ihist*fNumDetectorSystems + ihist2]->GetYaxis()->SetTitle("Time (ns)");
            h2_time_diff_corrs[ihist*fNumDetectorSystems + ihist2]->GetXaxis()->SetTitle("Time (ns)");
            h2_time_diff_corrs[ihist*fNumDetectorSystems + ihist2]->SetOption("COLZ");
        }
    }

    dir_time_machine->cd();
    gDirectory = tmp;


    return kSUCCESS;
    
}

void TimeMachineNearline::Exec(Option_t* option) // if two machines (undelayed + delayed are in one event, the last corr is taken.)
{   
    // Delayed and undelayed time machine   
    
    for (int system = 0; system<fNumDetectorSystems; system++)
    {
        if (fTimeMachine[system] && fTimeMachine[system]->GetEntriesFast() > 0)
        {
            delayed_time = 0;
            undelayed_time = 0;

            Int_t nHits = fTimeMachine[system]->GetEntriesFast();
            for (Int_t ihit = 0; ihit < nHits; ihit++)
            {   
                fTimeMachineHit = (TimeMachineData*)fTimeMachine[system]->At(ihit);
                if (!fTimeMachineHit) continue;

                if (fTimeMachineHit->Get_wr_t() != 0)
                {
                    wr[system] = fTimeMachineHit->Get_wr_t();
                }

                if (fTimeMachineHit->Get_undelayed_time() !=0 && undelayed_time == 0){
                    undelayed_time = fTimeMachineHit->Get_undelayed_time();
                }else if (fTimeMachineHit->Get_delayed_time() != 0 && delayed_time == 0){
                    delayed_time = fTimeMachineHit->Get_delayed_time();
                }
                
                if (delayed_time!=0 && undelayed_time!=0) break; //once you have one undelayed and one delayed break - this assumes only one timemachine delayed-undelayed pair per event.
            }

            if ((delayed_time != 0) && (undelayed_time !=0))
            {
                diffs[system] = delayed_time - undelayed_time;
                h1_time_undelayed[system]->Fill(undelayed_time);
                h1_time_delayed[system]->Fill(delayed_time);
                h1_time_diff[system]->Fill(diffs[system]);
                undelayed_time = 0;
                delayed_time = 0;
            }
        }
    }
    
    // Time differences
    for (int ihist = 0; ihist < fNumDetectorSystems; ihist++)
    {
        std::string systemName1 = fDetectorSystems[ihist].Data();
        uint64_t wr_t1 = wr[ihist];

        for (int ihist2 = ihist + 1; ihist2 < fNumDetectorSystems; ihist2++)
        {

            std::string systemName2 = fDetectorSystems[ihist2].Data();
            uint64_t wr_t2 = wr[ihist2];
            int wr_diff = wr_t1 - wr_t2;

            std::string key = systemName1 + "-" + systemName2 + " TM Gate";

            if((diffs[ihist]!=0) && (diffs[ihist2]!=0) && wr_diff > TMGates[key][0] && wr_diff < TMGates[key][1])
            {   
                h2_time_diff_corrs[ihist*fNumDetectorSystems + ihist2]->Fill(diffs[ihist],diffs[ihist2]);
            }
        }
    }

    fNEvents += 1;
}

void TimeMachineNearline::FinishEvent()
{
    if (fTimeMachine)
    {
        for (int i = 0; i<fNumDetectorSystems; i++){ 
            fTimeMachine[i]->Clear();
            diffs[i] = 0;
            };
    }
}

void TimeMachineNearline::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_time_machine->Write();
    gDirectory = tmp;
}

ClassImp(TimeMachineNearline) 
