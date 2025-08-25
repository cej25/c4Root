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
#include "FatimaSinglesAnalysis.h"
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


FatimaSinglesAnalysis::FatimaSinglesAnalysis() : FatimaSinglesAnalysis("FatimaSinglesAnalysis")
{
}

FatimaSinglesAnalysis::FatimaSinglesAnalysis(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatimaTwinpeaks(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
}

FatimaSinglesAnalysis::~FatimaSinglesAnalysis()
{
    c4LOG(info, "");
    if (fHitFatimaTwinpeaks)
        delete fHitFatimaTwinpeaks;
}

void FatimaSinglesAnalysis::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}




InitStatus FatimaSinglesAnalysis::Init()
{
    c4LOG(info, "");
    mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    //FairRunAna * run = FairRunAna::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatimaTwinpeaks = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatimaTwinpeaks, "Branch FatimaTwinpeaksCalData not found!");


    TFolder * fatima_spectra_folder = new TFolder("FatimaSinglesAnalysis", "FatimaSinglesAnalysis");

    //run->AddObject(fatima_spectra_folder);


    if (detector_id_analyze == nullptr) {c4LOG(fatal, "Please set which detector ids to analyze");}
    
    h_slow_ToT = new TH1F*[detector_id_analyze->size()];
    h_fast_ToT = new TH1F*[detector_id_analyze->size()];
    h_energy = new TH1F*[detector_id_analyze->size()];
    
    for (int i = 0; i<detector_id_analyze->size(); i++){
        h_slow_ToT[i] = new TH1F(Form("h_slow_ToT_det_%i",detector_id_analyze->at(i)),Form("slow ToT det %i;slow ToT (ns)",detector_id_analyze->at(i)),fslow_tot_nbins,fslow_tot_bin_low,fslow_tot_bin_high);
        h_fast_ToT[i] = new TH1F(Form("h_fast_ToT_det_%i",detector_id_analyze->at(i)),Form("fast ToT det %i;fast ToT (ns)",detector_id_analyze->at(i)),ffast_tot_nbins,ffast_tot_bin_low,ffast_tot_bin_high);
        h_energy[i] = new TH1F(Form("h_energy_det_%i",detector_id_analyze->at(i)),Form("Energy det %i; energy (keV)",detector_id_analyze->at(i)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        fatima_spectra_folder->Add(h_slow_ToT[i]);
        fatima_spectra_folder->Add(h_fast_ToT[i]);
        fatima_spectra_folder->Add(h_energy[i]);
    }

    return kSUCCESS;
    
}


void FatimaSinglesAnalysis::Exec(Option_t* option)
{   
    if (fHitFatimaTwinpeaks && fHitFatimaTwinpeaks->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFatimaTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            FatimaTwinpeaksCalData* hit1 = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit);

            if (!hit1) continue;

            double slow_ToT1 = hit1->Get_slow_ToT();
            uint16_t detector_id1 = hit1->Get_detector_id();
            double energy1 = hit1->Get_energy();
            double fast_lead1 = hit1->Get_fast_lead_time();
            double fast_ToT1 = hit1->Get_fast_ToT();

            if (std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id1) == detector_id_analyze->end()) continue; //not in vector of dets to analyze
            
            if (energy1 == 0) energy1 = slow_ToT1;
            int index1 = std::distance(detector_id_analyze->begin(), std::find(detector_id_analyze->begin(), detector_id_analyze->end(), detector_id1));

            h_energy[index1]->Fill(energy1);
            h_slow_ToT[index1]->Fill(slow_ToT1);
            h_fast_ToT[index1]->Fill(fast_ToT1);
        }
    }
    fNEvents += 1;
}



void FatimaSinglesAnalysis::FinishEvent()
{
    if (fHitFatimaTwinpeaks)
    {
        fHitFatimaTwinpeaks->Clear();
    }
}

void FatimaSinglesAnalysis::FinishTask()
{
    for (int i = 0; i<detector_id_analyze->size(); i++){
        h_slow_ToT[i]->Write(Form("h_slow_ToT_det_%i",detector_id_analyze->at(i)),TObject::kOverwrite);
        h_fast_ToT[i]->Write(Form("h_fast_ToT_det_%i",detector_id_analyze->at(i)),TObject::kOverwrite);
        h_energy[i]->Write(Form("h_energy_det_%i",detector_id_analyze->at(i)),TObject::kOverwrite);

    } 
}

ClassImp(FatimaSinglesAnalysis)
