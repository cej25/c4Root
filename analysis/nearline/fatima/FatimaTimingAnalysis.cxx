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
 *                             J.E.L. Larsson                                 *
 *                                06.05.25                                    *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaTimingAnalysis.h"
#include "EventHeader.h"
#include "FatimaTwinpeaksCalData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TRandom.h"


FatimaTimingAnalysis::FatimaTimingAnalysis() : FatimaTimingAnalysis("FatimaTimingAnalysis")
{
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
}

FatimaTimingAnalysis::FatimaTimingAnalysis(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatima(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
}

FatimaTimingAnalysis::~FatimaTimingAnalysis()
{
    c4LOG(info, "");
    if (fHitFatima)
        delete fHitFatima;
}

void FatimaTimingAnalysis::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}




InitStatus FatimaTimingAnalysis::Init()
{

    // number of crystals, number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatima = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatima, "Branch FatimaTwinpeaksCalData not found!");


    TDirectory* tmp = gDirectory;

    // Access the output file via FairRootManager
    TFile* outFile = FairRootManager::Instance()->GetOutFile();
    outFile->cd();

    // Check if the directory exists
    dir_fatima = outFile->GetDirectory("FatimaTimingAnalysis");
    if (!dir_fatima) {
        // Create the directory if it doesn't exist
        dir_fatima = outFile->mkdir("FatimaTimingAnalysis");
        c4LOG(info, "Created directory FatimaTimingAnalysis");
    } else {
        c4LOG(info, "Directory FatimaTimingAnalysis already exists");
    }

    // Change to the new directory
    dir_fatima->cd();

    if (detector_id_analyze == nullptr) {c4LOG(fatal, "Please set which detector ids to analyze");}
    

    //h_energy_E1_E2_dt
    h_energy_E1_E2_dt = new TH1F**[detector_id_analyze->size()];
    for (int i = 0; i<detector_id_analyze->size(); i++){
        h_energy_E1_E2_dt[i] = new TH1F*[detector_id_analyze->size()]; //(-j)
        for (int j=i+1; j<detector_id_analyze->size(); j++){
            h_energy_E1_E2_dt[i][j] = new TH1F(Form("h_E1_%i_E2_%i_det_%i_det_%i_dt_times",(int)E1, (int)E2,detector_id_analyze->at(i),detector_id_analyze->at(j)),Form("E1 = %f, E2 = %f, t%i - t%i;dt (ns)",E1,E2,detector_id_analyze->at(j),detector_id_analyze->at(i)),Nbins,lowBin,highBin);
            dir_fatima->Add(h_energy_E1_E2_dt[i][j]);
        }
    }

    h_energy_E1_dt_vs_E = new TH2F**[detector_id_analyze->size()];
    for (int i = 0; i<detector_id_analyze->size(); i++){
        h_energy_E1_dt_vs_E[i] = new TH2F*[detector_id_analyze->size()]; //(-j)
        for (int j=i+1; j<detector_id_analyze->size(); j++){
            h_energy_E1_dt_vs_E[i][j] = new TH2F(Form("h_E1_%i_E2_%i_dt_det_%i_det_%i_E_vs_dt",(int)E1,(int)E2,detector_id_analyze->at(i),detector_id_analyze->at(j)),Form("E1 = %f, E2 = x vs t%i - t%i = y;energy in det %i (keV);dt = t%i-t%i (ns)",E1,detector_id_analyze->at(j),detector_id_analyze->at(i),detector_id_analyze->at(j),detector_id_analyze->at(j),detector_id_analyze->at(i)),fenergy_nbins,fenergy_bin_low, fenergy_bin_high,Nbins,lowBin,highBin);
            dir_fatima->Add(h_energy_E1_dt_vs_E[i][j]);
        }
    }

    return kSUCCESS;
    
}


void FatimaTimingAnalysis::Exec(Option_t* option)
{   
    if (fHitFatima && fHitFatima->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFatima->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            FatimaTwinpeaksCalData* hit1 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit);

            if (!hit1) continue;

            double slow_ToT1 = hit1->Get_slow_ToT();
            uint16_t detector_id1 = hit1->Get_detector_id();
            double energy1 = hit1->Get_energy();
            double fast_lead_time1 = hit1->Get_fast_lead_time();
            double fast_lead_epoch1 = hit1->Get_fast_lead_epoch();

            if (std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id1) == detector_id_analyze->end()) continue; //not in vector of dets to analyze
            
            if (energy1 == 0) energy1 = slow_ToT1;
            
                            
            if (nHits>=2){ 
                for (size_t ihit2 = ihit+1; ihit2 < nHits; ihit2++) {
                    FatimaTwinpeaksCalData* hit2 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit2);
                    double slow_ToT2 = hit2->Get_slow_ToT();
                    uint16_t detector_id2 = hit2->Get_detector_id();
                    double energy2 = hit2->Get_energy();
                    double fast_lead_time2 = hit2->Get_fast_lead_time();
                    double fast_lead_epoch2 = hit2->Get_fast_lead_epoch();

                    if (std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id2) == detector_id_analyze->end()) continue; //not in vector of dets to analyze
                    

                    if (energy2 == 0) energy2 = slow_ToT2;

                    double dt = fast_lead_time1 - fast_lead_time2 + (fast_lead_epoch1 - fast_lead_epoch2);
                    
                    if (!(TMath::Abs(dt) < 1000)) continue; //require coincidence!

                    double timeshift_to_apply = 0;
                    if (detector_id2>detector_id1 && TMath::Abs(energy1 - E1)<Egatewidth){
                        
                        int index1 = std::distance(detector_id_analyze->begin(), std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id1));
                        int index2 = std::distance(detector_id_analyze->begin(), std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id2));
                        
                        timeshift_to_apply =  fatima_configuration->GetTimeshiftCoefficient(detector_id1,detector_id2); //check ordering
                        h_energy_E1_dt_vs_E[index1][index2]->Fill(energy2, - dt - timeshift_to_apply);
                        
                        
                        if (TMath::Abs(energy2 - E2)<Egatewidth){
                        // det1 is start
                        // det2 is stop
                        // det2 > det1
                        // here det1 is i and det2 is j
                        

                        h_energy_E1_E2_dt[index1][index2]->Fill(- dt - timeshift_to_apply);
                        }
                    }else if (detector_id1>detector_id2 && TMath::Abs(energy2 - E1)<Egatewidth){
                        int index1 = std::distance(detector_id_analyze->begin(), std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id2));
                        int index2 = std::distance(detector_id_analyze->begin(), std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id1));
                        h_energy_E1_dt_vs_E[index1][index2]->Fill(energy1, dt - timeshift_to_apply);
                        

                        if (TMath::Abs(energy1 - E2)<Egatewidth){
                        // det2 is start
                        // det1 is stop
                        // det1 > det2
                        // here det2 is i and det1 is j
                        
                        timeshift_to_apply =  fatima_configuration->GetTimeshiftCoefficient(detector_id2,detector_id1);
                        
                        h_energy_E1_E2_dt[index1][index2]->Fill(dt - timeshift_to_apply);

                        } 
                    }
                }
            }
        }
    }
    fNEvents += 1;
}



void FatimaTimingAnalysis::FinishEvent()
{
    if (fHitFatima)
    {
        fHitFatima->Clear();
    }
}

void FatimaTimingAnalysis::FinishTask()
{

    //h_energy_E1_E2_dt
    for (int i = 0; i<detector_id_analyze->size(); i++){
        for (int j=i+1; j<detector_id_analyze->size(); j++){
            h_energy_E1_E2_dt[i][j]->Write(Form("h_E1_%i_E2_%i_det_%i_det_%i_dt_times",(int)E1, (int)E2,detector_id_analyze->at(i),detector_id_analyze->at(j)),TObject::kOverwrite);
            h_energy_E1_dt_vs_E[i][j]->Write(Form("h_E1_%i_E2_%i_dt_det_%i_det_%i_E_vs_dt",(int)E1,(int)E2,detector_id_analyze->at(i),detector_id_analyze->at(j)),TObject::kOverwrite);
        }
    } 
}

ClassImp(FatimaTimingAnalysis)
