// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

#include <vector>

// c4
#include "TimeMachineOnline.h"
#include "EventHeader.h"
#include "TimeMachineData.h"


#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

TimeMachineOnline::TimeMachineOnline()
{
}

TimeMachineOnline::TimeMachineOnline(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , f_time_machines(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

TimeMachineOnline::~TimeMachineOnline()
{
    c4LOG(info, "");
    if (f_time_machines) {
        for (int i = 0; i<num_detector_systems; i++) delete f_time_machines[i];
        delete[] f_time_machines;
    }
}

void TimeMachineOnline::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}


void TimeMachineOnline::SetDetectorSystems(std::vector<TString> detectorsystems){
    
    c4LOG(info, "Set detector systems.");
    
    num_detector_systems = detectorsystems.size();
    
    fdetector_systems = std::vector<TString>(0);
    
    for (int i = 0; i < num_detector_systems; i++) fdetector_systems.push_back(detectorsystems.at(i));

}

InitStatus TimeMachineOnline::Init()
{

    c4LOG_IF(fatal, (num_detector_systems==0) || ((num_detector_systems>20) && (num_detector_systems<0)), "Detector systems not specified for TimeMachineOnline. Please add SetDetectorSystems before Init().");

    // number of crystals, number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    c4LOG(info,"Allocating f_time_machines");
    f_time_machines = new TClonesArray*[num_detector_systems];

    for (int det = 0; det<num_detector_systems; det++){
        c4LOG(info, "Looking for " + fdetector_systems.at(det));
        f_time_machines[det] = (TClonesArray*) mgr->GetObject(fdetector_systems.at(det)+"TimeMachineData");
        c4LOG_IF(fatal, !f_time_machines[det], "Branch TimeMachineData not found!");
    }

    c4LOG(info,"allocating histograms.");
    TFolder * time_machine_folder = new TFolder("TimeMachines", "TimeMachines");
    run->AddObject(time_machine_folder);
    // Time:
    
    TCanvas * time_undelayed  = new TCanvas("time_undelayed","Time machine stuff",650,350);
    time_undelayed->Divide(1,num_detector_systems);

    for (int ihist = 0; ihist < num_detector_systems; ihist++){
        time_undelayed->cd(ihist+1);
        h1_time_undelayed[ihist] = new TH1F("time_undelayed_"+fdetector_systems.at(ihist),"time_undelayed_"+fdetector_systems.at(ihist),500,165e12,166e12);
        h1_time_undelayed[ihist]->GetXaxis()->SetTitle("time (ns)");
        h1_time_undelayed[ihist]->Draw();
        time_machine_folder->Add(h1_time_undelayed[ihist]);

    }
    //time_undelayed->cd(0);

    time_machine_folder->Add(time_undelayed);

    TCanvas * time_delayed  = new TCanvas("time_delayed","Time machine stuff",650,350);
    time_delayed->Divide(1,num_detector_systems);

    for (int ihist = 0; ihist < num_detector_systems; ihist++){
        time_delayed->cd(ihist+1);
        h1_time_delayed[ihist] = new TH1F("time_delayed_"+fdetector_systems.at(ihist),"time_delayed_"+fdetector_systems.at(ihist),500,165e12,166e12);
        h1_time_delayed[ihist]->GetXaxis()->SetTitle("time (ns)");
        h1_time_delayed[ihist]->Draw();
        time_machine_folder->Add(h1_time_delayed[ihist]);

    }
    //time_delayed->cd(0);

    time_machine_folder->Add(time_delayed);


    TCanvas * time_diff  = new TCanvas("time_diff","Time machine stuff",650,350);
    time_diff->Divide(1,num_detector_systems);

    for (int ihist = 0; ihist < num_detector_systems; ihist++){
        time_diff->cd(ihist+1);
        h1_time_diff[ihist] = new TH1F("time_diff_"+fdetector_systems.at(ihist),"time_diff_"+fdetector_systems.at(ihist),1000,-100,2000);
        h1_time_diff[ihist]->GetXaxis()->SetTitle("time (ns)");
        h1_time_diff[ihist]->Draw();
        time_machine_folder->Add(h1_time_diff[ihist]);

    }
    //time_diff->cd(0);

    time_machine_folder->Add(time_diff);


    TCanvas * time_corrs = new TCanvas("time_corrs","Time machine correlations", 650,350);
    time_corrs->Divide(1,num_detector_systems*(num_detector_systems-1));

    for (int ihist = 0; ihist < num_detector_systems; ihist++){
        for (int ihist2 = ihist + 1; ihist2 < num_detector_systems; ihist2++){
            time_corrs->cd(ihist*num_detector_systems + ihist2);
            h2_time_diff_corrs[ihist*num_detector_systems + ihist2] = new TH2F("time_corr_" + fdetector_systems.at(ihist) + "_" + fdetector_systems.at(ihist2),"time_corr_" + fdetector_systems.at(ihist) + "_" + fdetector_systems.at(ihist2),250,-100,1600,250,-100,1600);
            h2_time_diff_corrs[ihist*num_detector_systems + ihist2]->GetYaxis()->SetTitle("time (ns)");
            h2_time_diff_corrs[ihist*num_detector_systems + ihist2]->GetXaxis()->SetTitle("time (ns)");
            h2_time_diff_corrs[ihist*num_detector_systems + ihist2]->Draw("COLZ");
            time_machine_folder->Add(h2_time_diff_corrs[ihist*num_detector_systems + ihist2]);
        }
    }

    time_machine_folder->Add(time_corrs);

    run->RegisterHttpCommand("Reset TimeMachine", "/TimeMachineOnline->Reset_Histo()");
    c4LOG(info, "Setup of TimeMachineOnline complete.");
    return kSUCCESS;
    
}

void TimeMachineOnline::Reset_Histo()
{
    c4LOG(info, "Reset command received. Clearing histograms. TODO");

}

void TimeMachineOnline::Exec(Option_t* option) // if two machines (undelayed + delayed are in one event, the last corr is taken.)
{      
    for (int system = 0; system<num_detector_systems; system++){
    if (f_time_machines[system] && f_time_machines[system]->GetEntriesFast() > 0)
    {
        
        delayed_time = 0;
        undelayed_time = 0;

        Int_t nHits = f_time_machines[system]->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            hit = (TimeMachineData*)f_time_machines[system]->At(ihit);
            if (!hit) continue;

            if (hit->Get_undelayed_time() !=0 && undelayed_time == 0){
                undelayed_time = hit->Get_undelayed_time();
            }else if (hit->Get_delayed_time() != 0 && delayed_time == 0){
                delayed_time = hit->Get_delayed_time();
            }


            if (delayed_time!=0 && undelayed_time!=0) break; //once you have one undelayed and one delayed break - this assumes only one timemachine delayed-undelayed pair per event.
        }

        if ((delayed_time != 0) && (undelayed_time !=0)){
        diffs[system] = delayed_time - undelayed_time;
        h1_time_undelayed[system]->Fill(undelayed_time);
        h1_time_delayed[system]->Fill(delayed_time);
        h1_time_diff[system]->Fill(diffs[system]);
        undelayed_time = 0;
        delayed_time = 0;
        }
        }
        }
    

    
    for (int ihist = 0; ihist < num_detector_systems; ihist++){
        for (int ihist2 = ihist + 1; ihist2 < num_detector_systems; ihist2++){
        if((diffs[ihist]!=0) && (diffs[ihist2]!=0))h2_time_diff_corrs[ihist*num_detector_systems + ihist2]->Fill(diffs[ihist],diffs[ihist2]);
        }
    }



    fNEvents += 1;
}

void TimeMachineOnline::FinishEvent()
{
    if (f_time_machines)
    {
        for (int i = 0; i<num_detector_systems; i++){ 
            f_time_machines[i]->Clear();
            diffs[i] = 0;
            };
    }
}

void TimeMachineOnline::FinishTask()
{
    if (f_time_machines)//writes to file, test?
    {
        for (int ihist = 0; ihist<num_detector_systems; ihist++) h1_time_delayed[ihist]->Write();
        for (int ihist = 0; ihist<num_detector_systems; ihist++) h1_time_undelayed[ihist]->Write();
        for (int ihist = 0; ihist<num_detector_systems; ihist++) h1_time_diff[ihist]->Write();

        for (int ihist = 0; ihist < num_detector_systems; ihist++){
            for (int ihist2 = ihist + 1; ihist2 < num_detector_systems; ihist2++){
            h2_time_diff_corrs[ihist*num_detector_systems + ihist2]->Write();
            }
        }
    }
}

ClassImp(TimeMachineOnline) 