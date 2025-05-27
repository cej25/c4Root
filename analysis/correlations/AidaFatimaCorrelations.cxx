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
 *                                C.E. Jones                                  *
 *                                 06.05.25                                   *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AidaFatimaCorrelations.h"
#include "EventHeader.h"
#include "FatimaTwinpeaksCalData.h"
#include "AidaData.h"


#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"


double time_differences_to_SCI42[10] = 
{
    -300.7,
    -295.5,
    -301.5,
    -302.0,
    -303.9,
    -301.9,
    -305.9,
    0,
    -301.2,
    -301.6
};

AidaFatimaCorrelations::AidaFatimaCorrelations() : AidaFatimaCorrelations("AidaFatimaCorrelations")
{
}

AidaFatimaCorrelations::AidaFatimaCorrelations(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatimaTwinpeaks(nullptr)
    , implantHitArray(nullptr)
    , decayHitArray(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
}

AidaFatimaCorrelations::~AidaFatimaCorrelations()
{
    c4LOG(info, "");
    if (fHitFatimaTwinpeaks)
        delete fHitFatimaTwinpeaks;
}

void AidaFatimaCorrelations::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus AidaFatimaCorrelations::Init()
{

    // number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatimaTwinpeaks = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatimaTwinpeaks, "Branch FatimaTwinpeaksCalData not found!");

    implantHitArray = mgr->InitObjectAs<decltype(implantHitArray)>("AidaImplantHits");
    c4LOG_IF(fatal, !implantHitArray, "Branch AidaImplantHits not found!");
    
    decayHitArray = mgr->InitObjectAs<decltype(decayHitArray)>("AidaDecayHits");
    c4LOG_IF(fatal, !decayHitArray, "Branch AidaDecayHits not found!");

    h1_fatima_time_differences_energy_SCI41_gated = new TH1F("h1_fatima_time_differences_energy_SCI41_gated","FATIMA energy gated just after prompt flash",500,0,2e3);
    h1_fatima_time_differences_energy_SCI41_gated->GetXaxis()->SetTitle("Time (ns)");
    h1_fatima_time_differences_energy_SCI41_gated->GetYaxis()->SetTitle("Energy (keV)");
    
    h1_fatima_time_differences_energy_SCI41_dt = new TH2F("h1_fatima_time_differences_energy_SCI41_dt","FATIMA energy dt just after prompt flash",1000,-500,500,500,0,2e3);
    h1_fatima_time_differences_energy_SCI41_dt->GetXaxis()->SetTitle("Time (ns)");
    h1_fatima_time_differences_energy_SCI41_dt->GetYaxis()->SetTitle("Energy (keV)");
    
    h1_fatima_energy_anticoincidence_SCI41 = new TH1F("h1_fatima_energy_anticoincidence_SCI41","FATIMA energy NO SCI41",500,0,2e3);
    h1_fatima_energy_anticoincidence_SCI41->GetXaxis()->SetTitle("Time (ns)");
    h1_fatima_energy_anticoincidence_SCI41->GetYaxis()->SetTitle("Energy (keV)");
    
    h1_fatima_energy_decay_gated = new TH2F("h1_fatima_energy_decay_gated","FATIMA energy gated decay E=6.3 - 6.6 MeV",500,0,2e3,10,0,10);
    h1_fatima_energy_decay_gated->GetXaxis()->SetTitle("Time (ns)");
    h1_fatima_energy_decay_gated->GetYaxis()->SetTitle("Energy (keV)");
    
    h1_fatima_energy_decay_a_vary = new TH2F("h1_fatima_energy_decay_a_vary","FATIMA energy vs AIDA decay energy",500,0,2e3,100,0,20e3);
    h1_fatima_energy_decay_a_vary->GetXaxis()->SetTitle("Energy gamma (keV)");
    h1_fatima_energy_decay_a_vary->GetYaxis()->SetTitle("Energy alpha (keV)");
    
    h1_fatima_energy_decay_gated_mult2 = new TH2F("h1_fatima_energy_decay_gated_mult2","FATIMA energy gated decay E=6.3 - 6.6 MeV",500,0,2e3,500,0,2e3);
    h1_fatima_energy_decay_gated_mult2->GetXaxis()->SetTitle("Energy (keV)");
    h1_fatima_energy_decay_gated_mult2->GetYaxis()->SetTitle("Energy (keV)");

    h1_fatima_time_differences_SCI41_dt_detector = new TH2F("h1_fatima_time_differences_SCI41_dt_detector","Time to SCI41",1000,-500,500,24,0,24);
    h1_fatima_time_differences_SCI41_dt_detector->GetXaxis()->SetTitle("Time dt (ns)");
    h1_fatima_time_differences_SCI41_dt_detector->GetYaxis()->SetTitle("detector id");

    h1_decay_e = new TH1F("h1_decay_e","AIDA decay energy",500,0,20e3);
    h1_decay_e->GetXaxis()->SetTitle("Time (ns)");
    h1_decay_e->GetYaxis()->SetTitle("Energy (keV)");

    h1_implant_e = new TH1F("h1_implant_e","AIDA implant energy",500,0,20e3);
    h1_implant_e->GetXaxis()->SetTitle("Time (ns)");
    h1_implant_e->GetYaxis()->SetTitle("Energy (MeV)");


    return kSUCCESS;
    
}


void AidaFatimaCorrelations::Exec(Option_t* option)
{   
    if (fHitFatimaTwinpeaks && fHitFatimaTwinpeaks->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFatimaTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            veto_sci41 = false;
            FatimaTwinpeaksCalData* hit = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit);

            if (!hit) continue;
            
            if (hit->Get_detector_id() > NDetectors || hit->Get_detector_id() < 0) continue;

            if (hit->Get_detector_id() == 18 || hit->Get_detector_id() == 19) veto_sci41 = true;
            
            //COINCIDENCES:
            if (nHits > 1){
                for (Int_t ihit2 = ihit+1; ihit2 < nHits; ihit2++){
                    FatimaTwinpeaksCalData * hit2 = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit2);
                    if (!(TMath::Abs(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time())<20e3)) continue;
            
                    if (hit->Get_detector_id() == 18){
                        if (hit2->Get_detector_id() < 10 ) {
                            if (hit2->Get_fast_lead_time() - hit->Get_fast_lead_time() > - 305) h1_fatima_time_differences_energy_SCI41_gated->Fill(hit2->Get_energy());
                            h1_fatima_time_differences_energy_SCI41_dt->Fill(hit2->Get_fast_lead_time() - hit->Get_fast_lead_time() - time_differences_to_SCI42[hit2->Get_detector_id()], hit2->Get_energy());
                            if (TMath::Abs((hit2->Get_energy() - 1000)<20)) h1_fatima_time_differences_SCI41_dt_detector->Fill(hit2->Get_fast_lead_time() - hit->Get_fast_lead_time(), hit2->Get_detector_id());
                        }
                    }else if (hit2->Get_detector_id() == 18){
                        if (hit->Get_detector_id() < 10 ) {
                            if (hit->Get_fast_lead_time() - hit2->Get_fast_lead_time() > - 305) h1_fatima_time_differences_energy_SCI41_gated->Fill(hit->Get_energy());
                            h1_fatima_time_differences_energy_SCI41_dt->Fill(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time() - time_differences_to_SCI42[hit->Get_detector_id()], hit->Get_energy());
                            if (TMath::Abs((hit->Get_energy() - 1000)<20)) h1_fatima_time_differences_SCI41_dt_detector->Fill(hit->Get_fast_lead_time() - hit2->Get_fast_lead_time(), hit->Get_detector_id());

                        }
                    }    
                }
            }
        }
        if (!veto_sci41){
            for (Int_t ihit = 0; ihit < nHits; ihit++)
            {   
                FatimaTwinpeaksCalData* hit = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit);
                if (!hit) continue;        
                if (hit->Get_detector_id() >= 10 || hit->Get_detector_id() < 0) continue;
                h1_fatima_energy_anticoincidence_SCI41->Fill(hit->Get_energy());
            }
        }
    }

    for (auto const& hit : *implantHitArray)
    {
        h1_implant_e->Fill(hit.Energy);
    }
    for (auto const& hit : *decayHitArray)
    {
        h1_decay_e->Fill(hit.Energy);

        if (fHitFatimaTwinpeaks && fHitFatimaTwinpeaks->GetEntriesFast() > 0 && implantHitArray->size() == 0)
        {
            Int_t nHits = fHitFatimaTwinpeaks->GetEntriesFast();
            for (Int_t ihit = 0; ihit < nHits; ihit++)
            {   
                FatimaTwinpeaksCalData* hit_fati = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit);

                if (!hit_fati) continue;
                
                if (hit_fati->Get_detector_id() >= 10 || hit_fati->Get_detector_id() < 0) continue;

                h1_fatima_energy_decay_a_vary->Fill(hit_fati->Get_energy(),hit.Energy);

                if (hit.Energy > 6.3e3 && hit.Energy < 6.6e3) 
                {
                    h1_fatima_energy_decay_gated->Fill(hit_fati->Get_energy(),hit_fati->Get_detector_id());

                    if (nHits > 1){
                        for (Int_t ihit2 = ihit+1; ihit2 < nHits; ihit2++){
                            FatimaTwinpeaksCalData * hit_fati2 = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit2);
                            
                            if (hit_fati2->Get_detector_id() >= 10 || hit_fati2->Get_detector_id() < 0) continue;
                            
                            if (!(TMath::Abs(hit_fati->Get_fast_lead_time() - hit_fati2->Get_fast_lead_time())<20e3)) continue;
                            
                            h1_fatima_energy_decay_gated_mult2->Fill(hit_fati->Get_energy(),hit_fati2->Get_energy());  
                        }
                    }
                }
            }
        }
    }
    fNEvents += 1;
}



void AidaFatimaCorrelations::FinishEvent()
{
    if (fHitFatimaTwinpeaks)
    {
        fHitFatimaTwinpeaks->Clear();
    }
}

void AidaFatimaCorrelations::FinishTask()
{
    if (fHitFatimaTwinpeaks)
    {
        h1_fatima_time_differences_energy_SCI41_gated->Write();
        h1_fatima_energy_anticoincidence_SCI41->Write();
        h1_fatima_energy_decay_gated->Write();
        h1_implant_e->Write();    
        h1_decay_e->Write();    
        h1_fatima_energy_decay_gated_mult2->Write();
        h1_fatima_time_differences_energy_SCI41_dt->Write();
        h1_fatima_time_differences_SCI41_dt_detector->Write();
        h1_fatima_energy_decay_a_vary->Write();
    }
}

ClassImp(AidaFatimaCorrelations)
