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
 *                       C.E. Jones, J.P. Bormans                             *
 *                              17.12.24                                      *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "WhiterabbitCorrelationNearline.h"
#include "EventHeader.h"
#include "TimeMachineData.h"
#include "FatimaTwinpeaksCalData.h"
#include "FatimaVmeCalData.h"
#include "bPlastTwinpeaksCalData.h"
#include "GermaniumCalData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TH1I.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"
#include <chrono>

WhiterabbitCorrelationNearline::WhiterabbitCorrelationNearline() : WhiterabbitCorrelationNearline("WhiterabbitCorrelationNearline")
{
}

WhiterabbitCorrelationNearline::WhiterabbitCorrelationNearline(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatimaTwinpeaks(NULL)
    , fHitbPlastTwinpeaks(NULL)
    , fHitGe(NULL)
    , fHitFatimaVme(NULL)
    , fAidaDecays(new std::vector<AidaHit>)
    , fAidaScalers(new std::vector<AidaUnpackScalerItem>)
    , fNEvents(0)
    , fEventHeader(nullptr)
{
    conf = TAidaConfiguration::GetInstance();
}


WhiterabbitCorrelationNearline::~WhiterabbitCorrelationNearline()
{
    c4LOG(info, "");
    if (fHitFatimaTwinpeaks)
    {
        delete fHitFatimaTwinpeaks;
    }
    if (fHitFatimaVme)
    {
        delete fHitFatimaVme;
    }
    if (fHitbPlastTwinpeaks)
    {
        delete fHitbPlastTwinpeaks;
    }
    if (fHitGe)
    {
        delete fHitGe;
    }
    if (fAidaDecays)
    {
        delete fAidaDecays;
    }
    if (fEventHeader)
    {
        delete fEventHeader;
    }
}

void WhiterabbitCorrelationNearline::SetDetectorSystems(std::vector<TString> detectorsystems)
{
    fNumDetectorSystems = detectorsystems.size();

    fDetectorSystems = std::vector<TString>(0);

    for (int i = 0; i < fNumDetectorSystems; i++) fDetectorSystems.push_back(detectorsystems.at(i));
}

InitStatus WhiterabbitCorrelationNearline::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    fEventHeader = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !fEventHeader, "Branch EventHeader. not found");

    for (int i = 0; i < fNumDetectorSystems; i++)
    {
        // check each subsystem and get the corresponding TClonesArray
        if (fDetectorSystems.at(i) == "bPlast")
        {
            fHitbPlastTwinpeaks = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksCalData");
            c4LOG_IF(error, !fHitbPlastTwinpeaks, "Branch bPlastTwinpeaksCalData not found");
        }
        else if (fDetectorSystems.at(i) == "Fatima")
        {
            fHitFatimaTwinpeaks = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
            c4LOG_IF(error, !fHitFatimaTwinpeaks, "Branch FatimaTwinpeaksCalData. not found");
        }
        else if (fDetectorSystems.at(i) == "FatimaVme")
        {
            fHitFatimaVme = (TClonesArray*)mgr->GetObject("FatimaVmeCalData");
            c4LOG_IF(error, !fHitFatimaVme, "Branch FatimaVmeCalData. not found");
        }
        else if (fDetectorSystems.at(i) == "Germanium")
        {
            fHitGe = (TClonesArray*)mgr->GetObject("GermaniumCalData");
            c4LOG_IF(error, !fHitGe, "Branch GermaniumCalData. not found");
        }
        else if (fDetectorSystems.at(i) == "Aida")
        {
            fAidaDecays = mgr->InitObjectAs<decltype(fAidaDecays)>("AidaDecayHits");
            c4LOG_IF(fatal, !fAidaDecays, "Branch AidaDecayHits not found!");
            fAidaScalers = mgr->InitObjectAs<decltype(fAidaScalers)>("AidaScalerData");
            c4LOG_IF(fatal, !fAidaScalers, "Branch AidaScalerData not found!");
        }
        else
        {
            c4LOG(fatal, "Unknown detector system: " << fDetectorSystems.at(i));
        }
    }

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_whiterabbit = gDirectory->mkdir("White Rabbit");
    gDirectory->cd("White Rabbit");

    dir_whiterabbit_correlation = dir_whiterabbit->mkdir("Trigger 1 & 3");
    dir_whiterabbit_trigger1 = dir_whiterabbit->mkdir("Trigger 1");
    dir_whiterabbit_trigger3 = dir_whiterabbit->mkdir("Trigger 3");

    // AIDA 
    // AIDA - Fatima
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_aida_fatima = new TH1I("h1_whiterabbit_correlation_aida_fatima", "AIDA - FATIMA (TAMEX) WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_aida_fatima->GetXaxis()->SetTitle("Time difference (AIDA - FATIMA) [ns]");
    h1_whiterabbit_correlation_aida_fatima->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_aida_fatima->Draw();

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_aida_fatima = new TH1I("h1_whiterabbit_trigger1_aida_fatima", "White Rabbit Trigger 1 FATIMA-AIDA",1000,-1e3,5e4);
    h1_whiterabbit_trigger1_aida_fatima->GetXaxis()->SetTitle("AIDA - FATIMA WR dT (ns)");
    h1_whiterabbit_trigger1_aida_fatima->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_aida_fatima->Draw();

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_aida_fatima = new TH1I("h1_whiterabbit_trigger3_aida_fatima", "White Rabbit Trigger 3 AIDA - FATIMA (TAMEX)",1000,-1e3,5e4);
    h1_whiterabbit_trigger3_aida_fatima->GetXaxis()->SetTitle("AIDA - FATIMA WR dT (ns)");
    h1_whiterabbit_trigger3_aida_fatima->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_aida_fatima->Draw();

    // AIDA - FatimaVme
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_aida_fatimavme = new TH1I("h1_whiterabbit_correlation_aida_fatimavme", "AIDA - FATIMA (VME) WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_aida_fatimavme->GetXaxis()->SetTitle("Time difference (AIDA - FATIMA (VME)) [ns]");
    h1_whiterabbit_correlation_aida_fatimavme->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_aida_fatimavme->Draw();

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_aida_fatimavme = new TH1I("h1_whiterabbit_trigger1_aida_fatimavme", "White Rabbit Trigger 1 AIDA - FATIMA (VME)",1000,-1e3,5e4);
    h1_whiterabbit_trigger1_aida_fatimavme->GetXaxis()->SetTitle("AIDA - FATIMA (VME) WR dT (ns)");
    h1_whiterabbit_trigger1_aida_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_aida_fatimavme->Draw();

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_aida_fatimavme = new TH1I("h1_whiterabbit_trigger3_aida_fatimavme", "White Rabbit Trigger 3 AIDA - FATIMA (VME)",1000,-1e3,5e4);
    h1_whiterabbit_trigger3_aida_fatimavme->GetXaxis()->SetTitle("AIDA - FATIMA (VME) WR dT (ns)");
    h1_whiterabbit_trigger3_aida_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_aida_fatimavme->Draw();

    // AIDA - bPlast
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_aida_bplast = new TH1I("h1_whiterabbit_correlation_aida_bplast", "AIDA - bPlast WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_aida_bplast->GetXaxis()->SetTitle("Time difference (AIDA - bPlast) [ns]");
    h1_whiterabbit_correlation_aida_bplast->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_aida_bplast->Draw();

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_aida_bplast = new TH1I("h1_whiterabbit_trigger1_aida_bplast", "White Rabbit Trigger 1 AIDA-bPlast",1000,-1e3,5e4);
    h1_whiterabbit_trigger1_aida_bplast->GetXaxis()->SetTitle("AIDA - bPlast WR dT (ns)");
    h1_whiterabbit_trigger1_aida_bplast->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_aida_bplast->Draw();

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_aida_bplast = new TH1I("h1_whiterabbit_trigger3_aida_bplast", "White Rabbit Trigger 3 AIDA-bPlast",1000,-1e3,5e4);
    h1_whiterabbit_trigger3_aida_bplast->GetXaxis()->SetTitle("AIDA - bPlast WR dT (ns)");
    h1_whiterabbit_trigger3_aida_bplast->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_aida_bplast->Draw();

    // AIDA - Germanium
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_aida_germanium = new TH1I("h1_whiterabbit_correlation_aida_germanium", "AIDA - DEGAS WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_aida_germanium->GetXaxis()->SetTitle("Time difference (AIDA - DEGAS) [ns]");
    h1_whiterabbit_correlation_aida_germanium->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_aida_germanium->Draw();

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_aida_germanium = new TH1I("h1_whiterabbit_trigger1_aida_germanium", "White Rabbit Trigger 1 AIDA-DEGAS",1000,-1e3,5e4);
    h1_whiterabbit_trigger1_aida_germanium->GetXaxis()->SetTitle("AIDA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_aida_germanium->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_aida_germanium->Draw();

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_aida_germanium = new TH1I("h1_whiterabbit_trigger3_aida_germanium", "White Rabbit Trigger 3 AIDA-DEGAS",1000,-1e3,5e4);
    h1_whiterabbit_trigger3_aida_germanium->GetXaxis()->SetTitle("AIDA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_aida_germanium->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_aida_germanium->Draw();
    
    // FATIMA
    // Fatima - FatimaVme
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_fatima_fatimavme = new TH1I("h1_whiterabbit_correlation_fatima_fatimavme", "FATIMA - FATIMA VME WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatima_fatimavme->GetXaxis()->SetTitle("Time difference (FATIMA - FATIMA VME) [ns]");
    h1_whiterabbit_correlation_fatima_fatimavme->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatima_fatimavme->Draw();

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_fatima_fatimavme = new TH1I("h1_whiterabbit_trigger1_fatima_fatimavme", "White Rabbit Trigger 1 FATIMA-FATIMA VME", 1e3, -1e3, 1e3);
    h1_whiterabbit_trigger1_fatima_fatimavme->GetXaxis()->SetTitle("FATIMA - FATIMA VME WR dT (ns)");
    h1_whiterabbit_trigger1_fatima_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_fatima_fatimavme->Draw();

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_fatima_fatimavme = new TH1I("h1_whiterabbit_trigger3_fatima_fatimavme", "White Rabbit Trigger 3 FATIMA-FATIMA VME",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatima_fatimavme->GetXaxis()->SetTitle("FATIMA - FATIMA VME WR dT (ns)");
    h1_whiterabbit_trigger3_fatima_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_fatima_fatimavme->Draw();

    // Fatima - bPlast
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_fatima_bplast = new TH1I("h1_whiterabbit_correlation_fatima_bplast", "FATIMA (TAMEX) - bPlast WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatima_bplast->GetXaxis()->SetTitle("Time difference (FATIMA (TAMEX) - bPlast) [ns]");
    h1_whiterabbit_correlation_fatima_bplast->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatima_bplast->Draw();

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_fatima_bplast = new TH1I("h1_whiterabbit_trigger1_fatima_bplast", "White Rabbit Trigger 1 FATIMA (TAMEX) - bPlast", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_fatima_bplast->GetXaxis()->SetTitle("FATIMA (TAMEX) - bPlast WR dT (ns)");
    h1_whiterabbit_trigger1_fatima_bplast->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_fatima_bplast->Draw();

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_fatima_bplast = new TH1I("h1_whiterabbit_trigger3_fatima_bplast", "White Rabbit Trigger 3 FATIMA (TAMEX) - bPlast",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatima_bplast->GetXaxis()->SetTitle("FATIMA (TAMEX) - bPlast WR dT (ns)");
    h1_whiterabbit_trigger3_fatima_bplast->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_fatima_bplast->Draw();

    // Fatima - Germanium
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_fatima_ge = new TH1I("h1_whiterabbit_correlation_fatima_ge", "FATIMA - DEGAS WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatima_ge->GetXaxis()->SetTitle("Time difference (FATIMA - DEGAS) [ns]");
    h1_whiterabbit_correlation_fatima_ge->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatima_ge->Draw();

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_fatima_ge = new TH1I("h1_whiterabbit_trigger1_fatima_ge", "White Rabbit Trigger 1 FATIMA-DEGAS", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_fatima_ge->GetXaxis()->SetTitle("FATIMA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_fatima_ge->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_fatima_ge->Draw();

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_fatima_ge = new TH1I("h1_whiterabbit_trigger3_fatima_ge", "White Rabbit Trigger 3 FATIMA-DEGAS",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatima_ge->GetXaxis()->SetTitle("FATIMA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_fatima_ge->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_fatima_ge->Draw();

    // FatimaVme - bPlast
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_fatimavme_bplast = new TH1I("h1_whiterabbit_correlation_fatimavme_bplast", "FATIMA (VME) - bPlast WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatimavme_bplast->GetXaxis()->SetTitle("Time difference (FATIMA (VME) - bPlast) [ns]");
    h1_whiterabbit_correlation_fatimavme_bplast->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatimavme_bplast->Draw();

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_fatimavme_bplast = new TH1I("h1_whiterabbit_trigger1_fatimavme_bplast", "White Rabbit Trigger 1 FATIMA (VME) - bPlast", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_fatimavme_bplast->GetXaxis()->SetTitle("FATIMA (VME) - bPlast WR dT (ns)");
    h1_whiterabbit_trigger1_fatimavme_bplast->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_fatimavme_bplast->Draw();

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_fatimavme_bplast = new TH1I("h1_whiterabbit_trigger3_fatimavme_bplast", "White Rabbit Trigger 3 FATIMA (VME) - bPlast",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatimavme_bplast->GetXaxis()->SetTitle("FATIMA (VME) - bPlast WR dT (ns)");
    h1_whiterabbit_trigger3_fatimavme_bplast->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_fatimavme_bplast->Draw();

    // FatimaVme - Germanium
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_fatimavme_ge = new TH1I("h1_whiterabbit_correlation_fatimavme_ge", "FATIMA VME - DEGAS WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatimavme_ge->GetXaxis()->SetTitle("Time difference (FATIMA VME - DEGAS) [ns]");
    h1_whiterabbit_correlation_fatimavme_ge->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatimavme_ge->Draw();

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_fatimavme_ge = new TH1I("h1_whiterabbit_trigger1_fatimavme_ge", "White Rabbit Trigger 1 FATIMA VME-DEGAS", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_fatimavme_ge->GetXaxis()->SetTitle("FATIMA VME - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_fatimavme_ge->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_fatimavme_ge->Draw();

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_fatimavme_ge = new TH1I("h1_whiterabbit_trigger3_fatimavme_ge", "White Rabbit Trigger 3 FATIMA VME-DEGAS",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatimavme_ge->GetXaxis()->SetTitle("FATIMA VME - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_fatimavme_ge->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_fatimavme_ge->Draw();

    // bPlast - Germanium
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_bplast_ge = new TH1I("h1_whiterabbit_correlation_bplast_ge", "bPlast - DEGAS WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_bplast_ge->GetXaxis()->SetTitle("Time difference (bPlast - DEGAS) [ns]");
    h1_whiterabbit_correlation_bplast_ge->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_bplast_ge->Draw();

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_bplast_ge = new TH1I("h1_whiterabbit_trigger1_bplast_ge", "White Rabbit Trigger 1 bPlast-DEGAS", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_bplast_ge->GetXaxis()->SetTitle("bPlast - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_bplast_ge->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_bplast_ge->Draw();

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_bplast_ge = new TH1I("h1_whiterabbit_trigger3_bplast_ge", "White Rabbit Trigger 3 bPlast-DEGAS",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_bplast_ge->GetXaxis()->SetTitle("bPlast - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_bplast_ge->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_bplast_ge->Draw();

    // Trigger ID
    dir_whiterabbit->cd();
    h1_whiterabbit_trigger = new TH1I("h1_whiterabbit_trigger", "White Rabbit Trigger ID", 5, 0, 5);
    h1_whiterabbit_trigger->GetXaxis()->SetTitle("Trigger ID");
    h1_whiterabbit_trigger->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_trigger->Draw();


  

  

    dir_whiterabbit->cd();
    gDirectory = tmp;

    return kSUCCESS;
}


void WhiterabbitCorrelationNearline::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();

    Int_t nHitsFatimaVme = 0;
    Int_t nHitsFatima = 0;
    Int_t nHitsbPlast = 0;
    Int_t nHitsGe = 0;
    Int_t nHitsAida = 0;
    Int_t systems = 0;
    
    if (fHitFatimaTwinpeaks)
    {
        nHitsFatima = fHitFatimaTwinpeaks->GetEntriesFast();
        if (nHitsFatima > 0) systems += 1;
    }
    if (fHitbPlastTwinpeaks) 
    {
         nHitsbPlast = fHitbPlastTwinpeaks->GetEntriesFast();
         if (nHitsbPlast > 0) systems += 1;
    }
    if (fHitGe) 
    {
        nHitsGe = fHitGe->GetEntriesFast();
        if (nHitsGe > 0) systems += 1;
    }

    if (fHitFatimaVme) 
    {
        nHitsFatimaVme = fHitFatimaVme->GetEntriesFast();
        if (nHitsFatimaVme > 0) systems += 1;
    }
    
    if (fAidaDecays)
    {
        nHitsAida = fAidaDecays->size();
        if (nHitsAida > 0) systems += 1;
    }

    if (systems < 2) return;


    // start with aida...
    int aidaCounter = 0;
    int wr_aida = 0;
    for (auto & i : *fAidaScalers)
    {
        if (aidaCounter > 0) break;

        AidaUnpackScalerItem scalerAida = i;
        if (scalerAida.Fee() == conf->TM_Undelayed())
        {
            wr_aida = scalerAida.Time();
        }
        else
        {
            continue;
        }
        
        if (fHitFatimaTwinpeaks)
        {
            FatimaTwinpeaksCalData* hitFatima = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(0);
            if (!hitFatima) continue;
            int wr_fatima = hitFatima->Get_wr_t();
            int dt = wr_aida - wr_fatima;
            h1_whiterabbit_correlation_aida_fatima->Fill(dt);
            if (fEventHeader->GetTrigger() == 1)
            {
                h1_whiterabbit_trigger1_aida_fatima->Fill(dt);
            }
            if (fEventHeader->GetTrigger() == 3)
            {
                h1_whiterabbit_trigger3_aida_fatima->Fill(dt);
            }
        }
        
        // if (fHitFatimaVme)
        // {
        //     FatimaVmeCalData* hitFatimaVme = (FatimaVmeCalData*)fHitFatimaVme->At(0);
        //     if (!hitFatimaVme) continue;
        //     int wr_fatimavme = hitFatimaVme->Get_wr_t();
        //     int dt = wr_aida - wr_fatimavme;
        //     h1_whiterabbit_correlation_aida_fatimavme->Fill(dt);
        //     if (fEventHeader->GetTrigger() == 1)
        //     {
        //         h1_whiterabbit_trigger1_aida_fatimavme->Fill(dt);
        //     }
        //     if (fEventHeader->GetTrigger() == 3)
        //     {
        //         h1_whiterabbit_trigger3_aida_fatimavme->Fill(dt);
        //     }
        // }
        
        if (fHitbPlastTwinpeaks)
        {
            bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
            if (!hitbPlast) continue;
            int wr_bplast = hitbPlast->Get_wr_t();
            int dt = wr_aida - wr_bplast;
            h1_whiterabbit_correlation_aida_bplast->Fill(dt);
            if (fEventHeader->GetTrigger() == 1)
            {
                h1_whiterabbit_trigger1_aida_bplast->Fill(dt);
            }
            if (fEventHeader->GetTrigger() == 3)
            {
                h1_whiterabbit_trigger3_aida_bplast->Fill(dt);
            }
        }
        
        if (fHitGe)
        {
            GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(0);
            if (!hitGe) continue;
            int wr_ge = hitGe->Get_wr_t();
            int dt = wr_aida - wr_ge;
            h1_whiterabbit_correlation_aida_germanium->Fill(dt);
            if (fEventHeader->GetTrigger() == 1)
            {
                h1_whiterabbit_trigger1_aida_germanium->Fill(dt);
            }
            if (fEventHeader->GetTrigger() == 3)
            {
                h1_whiterabbit_trigger3_aida_germanium->Fill(dt);
            }
        }
        
        aidaCounter++;
        
    }
    
    
    if (fHitFatimaTwinpeaks)
    {
        FatimaTwinpeaksCalData* hitFatima = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(0);
        if (hitFatima)
        {
            int wr_fatima = hitFatima->Get_wr_t();
            // if (fHitFatimaVme) 
            // {
            //     FatimaVmeCalData* hitFatimaVme = (FatimaVmeCalData*)fHitFatimaVme->At(0);
            //     if (hitFatimaVme)
            //     {
            //         int wr_fatima_vme = hitFatimaVme->Get_wr_t();
            //         int dt = wr_fatima - wr_fatima_vme;
            //         h1_whiterabbit_correlation_fatima_fatimavme->Fill(dt);
            //         if (fEventHeader->GetTrigger() == 1)
            //         {
            //             h1_whiterabbit_trigger1_fatima_fatimavme->Fill(dt);
            //         }
            //         if (fEventHeader->GetTrigger() == 3)
            //         {
            //             h1_whiterabbit_trigger3_fatima_fatimavme->Fill(dt);
            //         }
            //     }
            // }
            
            if (fHitbPlastTwinpeaks) 
            {
                bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
                if (hitbPlast)
                {
                    int wr_bplast = hitbPlast->Get_wr_t();
                    int dt = wr_fatima - wr_bplast;
                    h1_whiterabbit_correlation_fatima_bplast->Fill(dt);
                    if (fEventHeader->GetTrigger() == 1)
                    {
                        h1_whiterabbit_trigger1_fatima_bplast->Fill(dt);
                    }
                    if (fEventHeader->GetTrigger() == 3)
                    {
                        h1_whiterabbit_trigger3_fatima_bplast->Fill(dt);
                    }
                }
            }
            
            if (fHitGe) 
            {
                GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(0);
                if (hitGe)
                {
                    int wr_ge = hitGe->Get_wr_t();
                    int dt = wr_fatima - wr_ge;
                    h1_whiterabbit_correlation_fatima_ge->Fill(dt);
                    if (fEventHeader->GetTrigger() == 1)
                    {
                        h1_whiterabbit_trigger1_fatima_ge->Fill(dt);
                    }
                    if (fEventHeader->GetTrigger() == 3)
                    {
                        h1_whiterabbit_trigger3_fatima_ge->Fill(dt);
                    }
                }
            }
        }
    }
    
    // if (fHitFatimaVme)
    // {
    //     FatimaVmeCalData* hitFatimaVme = (FatimaVmeCalData*)fHitFatimaVme->At(0);
    //     if (hitFatimaVme)
    //     {
    //         int wr_fatimavme= hitFatimaVme->Get_wr_t();

    //         if (fHitbPlastTwinpeaks) 
    //         {
    //             bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
    //             if (hitbPlast)
    //             {
    //                 int wr_bplast = hitbPlast->Get_wr_t();
    //                 int dt = wr_fatimavme - wr_bplast;
    //                 h1_whiterabbit_correlation_fatimavme_bplast->Fill(dt);
    //                 if (fEventHeader->GetTrigger() == 1)
    //                 {
    //                     h1_whiterabbit_trigger1_fatimavme_bplast->Fill(dt);
    //                 }
    //                 if (fEventHeader->GetTrigger() == 3)
    //                 {
    //                     h1_whiterabbit_trigger3_fatimavme_bplast->Fill(dt);
    //                 }
    //             }
    //         }
            
    //         if (fHitGe) 
    //         {
    //             GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(0);
    //             if (hitGe)
    //             {
    //                 int wr_ge = hitGe->Get_wr_t();
    //                 int dt = wr_fatimavme - wr_ge;
    //                 h1_whiterabbit_correlation_fatimavme_ge->Fill(dt);
    //                 if (fEventHeader->GetTrigger() == 1)
    //                 {
    //                     h1_whiterabbit_trigger1_fatimavme_ge->Fill(dt);
    //                 }
    //                 if (fEventHeader->GetTrigger() == 3)
    //                 {
    //                     h1_whiterabbit_trigger3_fatimavme_ge->Fill(dt);
    //                 }
    //             }
    //         }
    //     }
    // }
        
    if (fHitbPlastTwinpeaks)
    {
        if (fHitbPlastTwinpeaks) 
        {
            bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
            if (hitbPlast)
            {
                int bplast_wr = hitbPlast->Get_wr_t();
                if (fHitGe)
                {
                    GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(0);
                    if (hitGe)
                    {
                        int wr_ge = hitGe->Get_wr_t();
                        int dt = bplast_wr - wr_ge;
                        h1_whiterabbit_correlation_bplast_ge->Fill(dt);
                        if (fEventHeader->GetTrigger() == 1)
                        {
                            h1_whiterabbit_trigger1_bplast_ge->Fill(dt);
                        }
                        if (fEventHeader->GetTrigger() == 3)
                        {
                            h1_whiterabbit_trigger3_bplast_ge->Fill(dt);
                        }
                    }
                }
            }
        }
    }
    h1_whiterabbit_trigger->Fill(fEventHeader->GetTrigger());

    fNEvents += 1;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}





void WhiterabbitCorrelationNearline::FinishEvent()
{
    if (fHitFatimaTwinpeaks)
    {
        fHitFatimaTwinpeaks->Clear();
    }
    if (fHitbPlastTwinpeaks)
    {
        fHitbPlastTwinpeaks->Clear();
    }
    if (fHitGe)
    {
        fHitGe->Clear();
    }
    if (fHitFatimaVme)
    {
        fHitFatimaVme->Clear();
    }
}

void WhiterabbitCorrelationNearline::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events found, no histograms written.");
        return;
    }
    
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_whiterabbit->Write();
    gDirectory = tmp;
    c4LOG(info, "Processed " << fNEvents << " events.");
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents);
    
}

ClassImp(WhiterabbitCorrelationNearline)
