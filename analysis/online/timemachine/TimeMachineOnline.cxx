// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "TimeMachineOnline.h"
#include "EventHeader.h"
#include "TimeMachineData.h"
#include "TCorrelationsConfiguration.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TDirectory.h"
#include <iostream>
#include <vector>
#include <string>

TimeMachineOnline::TimeMachineOnline() 
    : TimeMachineOnline("TimeMachineOnline")
    {
        correl_config = TCorrelationsConfiguration::GetInstance();
        Correl = correl_config->CorrelationsMap();
        TMGates = correl_config->TimeMachineMap();
    }

TimeMachineOnline::TimeMachineOnline(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fTimeMachine(NULL)
    , fNEvents(0)
    , header(nullptr)
{
    correl_config = TCorrelationsConfiguration::GetInstance();
    Correl = correl_config->CorrelationsMap();
    TMGates = correl_config->TimeMachineMap();
}

TimeMachineOnline::~TimeMachineOnline()
{
    c4LOG(info, "");
    if (fTimeMachine) 
    {
        for (int i = 0; i<fNumDetectorSystems; i++) delete fTimeMachine[i];
        delete[] fTimeMachine;
    }
}

void TimeMachineOnline::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}


void TimeMachineOnline::SetDetectorSystems(std::vector<TString> detectorsystems)
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

InitStatus TimeMachineOnline::Init()
{

    c4LOG_IF(fatal, (fNumDetectorSystems == 0) || (fNumDetectorSystems < 0), "Detector systems not specified for TimeMachineOnline. Please add SetDetectorSystems before Init().");

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    fTimeMachine = new TClonesArray*[fNumDetectorSystems];

    for (int det = 0; det<fNumDetectorSystems; det++)
    {
        fTimeMachine[det] = (TClonesArray*) mgr->GetObject(fDetectorSystems.at(det)+"TimeMachineData");
        c4LOG_IF(fatal, !fTimeMachine[det], "Branch TimeMachineData not found!");
    }

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_time_machine = new TDirectory("TimeMachines", "TimeMachines", "", 0);
    mgr->Register("TimeMachines", "TimeMachines Directory", dir_time_machine, false); // allow other tasks to access directory;
    histograms->Add(dir_time_machine);

    dir_time_machine_undelayed = dir_time_machine->mkdir("Time Machine Undelayed");
    dir_time_machine_delayed = dir_time_machine->mkdir("Time Machine Delayed");
    dir_time_machine_diff = dir_time_machine->mkdir("Time Machine Difference");
    dir_time_machine_corrs = dir_time_machine->mkdir("Time Machine Correlations");

    h1_time_undelayed.resize(fNumDetectorSystems);
    h1_time_delayed.resize(fNumDetectorSystems);
    h1_time_diff.resize(fNumDetectorSystems*(fNumDetectorSystems - 1));
    h2_time_diff_corrs.resize((fNumDetectorSystems*fNumDetectorSystems)*(fNumDetectorSystems*fNumDetectorSystems-1)); // pairs from n items
    

    dir_time_machine_undelayed->cd();
    c_time_undelayed  = new TCanvas("c_time_undelayed","Time Machine Undelayed",650,350);
    c_time_undelayed->Divide(1,fNumDetectorSystems);
    for (int ihist = 0; ihist < fNumDetectorSystems; ihist++)
    {
        c_time_undelayed->cd(ihist+1);
        h1_time_undelayed[ihist] = new TH1F("time_undelayed_"+fDetectorSystems.at(ihist),"time_undelayed_"+fDetectorSystems.at(ihist),500,165e12,166e12);
        h1_time_undelayed[ihist]->GetXaxis()->SetTitle("time (ns)");
        h1_time_undelayed[ihist]->Draw();
    }
    c_time_undelayed->cd(0);
    dir_time_machine_undelayed->Append(c_time_undelayed);

    dir_time_machine_delayed->cd();
    c_time_delayed  = new TCanvas("c_time_delayed","Time Machine Delayed",650,350);
    c_time_delayed->Divide(1,fNumDetectorSystems);
    for (int ihist = 0; ihist < fNumDetectorSystems; ihist++)
    {
        c_time_delayed->cd(ihist+1);
        h1_time_delayed[ihist] = new TH1F("time_delayed_"+fDetectorSystems.at(ihist),"time_delayed_"+fDetectorSystems.at(ihist),500,165e12,166e12);
        h1_time_delayed[ihist]->GetXaxis()->SetTitle("time (ns)");
        h1_time_delayed[ihist]->Draw();
    }
    c_time_delayed->cd(0);
    dir_time_machine_delayed->Append(c_time_delayed);

    dir_time_machine_diff->cd();
    c_time_diff  = new TCanvas("c_time_diff","Time Machine Difference",650,350);
    c_time_diff->Divide(1,fNumDetectorSystems);
    for (int ihist = 0; ihist < fNumDetectorSystems; ihist++){
        c_time_diff->cd(ihist+1);
        h1_time_diff[ihist] = new TH1F("time_diff_"+fDetectorSystems.at(ihist),"time_diff_"+fDetectorSystems.at(ihist),1000,-100,2000);
        h1_time_diff[ihist]->GetXaxis()->SetTitle("time (ns)");
        h1_time_diff[ihist]->Draw();
    }
    c_time_diff->cd(0);
    dir_time_machine_diff->Append(c_time_diff);

    dir_time_machine_corrs->cd();
    c_time_corrs = new TCanvas("c_time_corrs","Time Machine Correlations", 650,350);
    c_time_corrs->Divide(1,fNumDetectorSystems*(fNumDetectorSystems-1));
    for (int ihist = 0; ihist < fNumDetectorSystems; ihist++){
        for (int ihist2 = ihist + 1; ihist2 < fNumDetectorSystems; ihist2++){
  
            c_time_corrs->cd(ihist*fNumDetectorSystems + ihist2);  
            h2_time_diff_corrs[ihist*fNumDetectorSystems + ihist2] = new TH2F("time_corr_" + fDetectorSystems.at(ihist) + "_" + fDetectorSystems.at(ihist2),"time_corr_" + fDetectorSystems.at(ihist) + "_" + fDetectorSystems.at(ihist2),250,-100,1600,250,-100,1600);
            h2_time_diff_corrs[ihist*fNumDetectorSystems + ihist2]->GetYaxis()->SetTitle("Time (ns)");
            h2_time_diff_corrs[ihist*fNumDetectorSystems + ihist2]->GetXaxis()->SetTitle("Time (ns)");
            h2_time_diff_corrs[ihist*fNumDetectorSystems + ihist2]->Draw("COLZ");
        }
    }
    c_time_corrs->cd(0);
    dir_time_machine_corrs->Append(c_time_corrs);

    dir_time_machine->cd();

    run->GetHttpServer()->RegisterCommand("Reset_TimeMachine_Histo", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_TimeMachine_Histo", Form("/Objects/%s/->Snapshot_Histo()", GetName()));

    return kSUCCESS;
    
}



void TimeMachineOnline::Reset_Histo()
{
    c4LOG(info, "Reset command received. Clearing histograms.");
    for (int ihist = 0; ihist<fNumDetectorSystems; ihist++) h1_time_delayed[ihist]->Reset();
    for (int ihist = 0; ihist<fNumDetectorSystems; ihist++) h1_time_undelayed[ihist]->Reset();
    for (int ihist = 0; ihist<fNumDetectorSystems; ihist++) h1_time_diff[ihist]->Reset();
    for (int ihist = 0; ihist<fNumDetectorSystems; ihist++){
        for (int ihist2 = ihist + 1; ihist2 < fNumDetectorSystems; ihist2++){
        h2_time_diff_corrs[ihist*fNumDetectorSystems + ihist2]->Reset();
        }
    }
}

void TimeMachineOnline::Snapshot_Histo()
{
    // date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    //make folder with date and time
    const char* snapshot_dir = Form("TimeMachine_snapshot_%d_%d_%d_%d_%d_%d",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec);
    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    // save histograms to canvases
    c_time_machine_time_snapshot = new TCanvas("c_time_machine_time_snapshot","c_time_machine_time_snapshot",650,350);

    for (int ihist = 0; ihist< fNumDetectorSystems; ihist++)
    {
        if(h1_time_delayed[ihist]->GetEntries()>0)
        {
            h1_time_delayed[ihist]->Draw();
            c_time_machine_time_snapshot->SaveAs(Form("h1_time_delayed_%s.png",fDetectorSystems.at(ihist).Data()));
            c_time_machine_time_snapshot->Clear();
        }
        if(h1_time_undelayed[ihist]->GetEntries()>0)
        {
            h1_time_undelayed[ihist]->Draw();
            c_time_machine_time_snapshot->SaveAs(Form("h1_time_undelayed_%s.png",fDetectorSystems.at(ihist).Data()));
            c_time_machine_time_snapshot->Clear();
        }
        if(h1_time_diff[ihist]->GetEntries()>0)
        {
            h1_time_diff[ihist]->Draw();
            c_time_machine_time_snapshot->SaveAs(Form("h1_time_diff_%s.png",fDetectorSystems.at(ihist).Data()));
            c_time_machine_time_snapshot->Clear();
        }
    }
    delete c_time_machine_time_snapshot;

    gSystem->cd("..");
    c4LOG(info, "Snapshot saved to:" << snapshot_dir);
}

void TimeMachineOnline::Exec(Option_t* option) // if two machines (undelayed + delayed are in one event, the last corr is taken.)
{   
    // Delayed and undelayed time machine   
    
    for (int system = 0; system<fNumDetectorSystems; system++)
    {
        if (fTimeMachine[system] && fTimeMachine[system]->GetEntriesFast() > 0)
        {
            delayed_time = 0;
            undelayed_time = 0;

            Int_t nHits = fTimeMachine[system]->GetEntriesFast();
            std::string systemName1 = fDetectorSystems[system].Data();

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
        int64_t wr_t1 = wr[ihist];

        for (int ihist2 = ihist + 1; ihist2 < fNumDetectorSystems; ihist2++)
        {

            std::string systemName2 = fDetectorSystems[ihist2].Data();
            int64_t wr_t2 = wr[ihist2];
            int64_t wr_diff = wr_t1 - wr_t2;            

            /*if (systemName1 == "Aida") {wr_diff -= 14000;}
            else if (systemName2 == "Aida") {wr_diff += 14000;}*/

            std::string key = systemName1 + "-" + systemName2 + " TM Gate";
            
            /*if((diffs[ihist]!=0) && (diffs[ihist2]!=0))
            {
                std::cout << "this part works for key: " << key << std::endl;

            }*/

            if((diffs[ihist]!=0) && (diffs[ihist2]!=0) && wr_diff > TMGates[key][0] && wr_diff < TMGates[key][1])
            {   
                h2_time_diff_corrs[ihist*fNumDetectorSystems + ihist2]->Fill(diffs[ihist],diffs[ihist2]);
            }
        }
    }

    fNEvents += 1;
}

void TimeMachineOnline::FinishEvent()
{
    if (fTimeMachine)
    {
        for (int i = 0; i<fNumDetectorSystems; i++){ 
            fTimeMachine[i]->Clear();
            diffs[i] = 0;
            };
    }
}

void TimeMachineOnline::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
}

ClassImp(TimeMachineOnline) 
