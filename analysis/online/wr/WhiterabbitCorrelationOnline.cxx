// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "WhiterabbitCorrelationOnline.h"
#include "EventHeader.h"
#include "TimeMachineData.h"
#include "FatimaTwinpeaksCalData.h"
#include "FatimaVmeCalData.h"
#include "bPlastTwinpeaksCalData.h"
#include "GermaniumCalData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1I.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"
#include "TDirectory.h"

WhiterabbitCorrelationOnline::WhiterabbitCorrelationOnline() : WhiterabbitCorrelationOnline("WhiterabbitCorrelationOnline")
{
}

WhiterabbitCorrelationOnline::WhiterabbitCorrelationOnline(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatimaTwinpeaks(NULL)
    , fHitbPlastTwinpeaks(NULL)
    , fHitGe(NULL)
    , fHitFatimaVme(NULL)
    , fAidaDecays(new std::vector<AidaHit>)
    , fNEvents(0)
    , fEventHeader(nullptr)
{
}


WhiterabbitCorrelationOnline::~WhiterabbitCorrelationOnline()
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

void WhiterabbitCorrelationOnline::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

void WhiterabbitCorrelationOnline::SetDetectorSystems(std::vector<TString> detectorsystems)
{
    fNumDetectorSystems = detectorsystems.size();

    fDetectorSystems = std::vector<TString>(0);

    for (int i = 0; i < fNumDetectorSystems; i++) fDetectorSystems.push_back(detectorsystems.at(i));
}

InitStatus WhiterabbitCorrelationOnline::Init()
{

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

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
            c4LOG_IF(fatal, !fAidaDecays, "Branch fAidaDecayHits not found!");
        }
        else
        {
            c4LOG(fatal, "Unknown detector system: " << fDetectorSystems.at(i));
        }
    }

    TDirectory::TContext ctx(nullptr);

    folder_whiterabbit = new TFolder("White Rabbit", "White Rabbit");

    run->AddObject(folder_whiterabbit);

    folder_whiterabbit_correlation = new TFolder("Trigger 1 & 3", "Trigger 1 & 3");
    folder_whiterabbit_trigger1 = new TFolder("Trigger 1", "Trigger 1");
    folder_whiterabbit_trigger3 = new TFolder("Trigger 3", "Trigger 3");

    folder_whiterabbit->Add(folder_whiterabbit_correlation);
    folder_whiterabbit->Add(folder_whiterabbit_trigger1);
    folder_whiterabbit->Add(folder_whiterabbit_trigger3);

    // AIDA 
    // AIDA - Fatima
    c_whiterabbit_correlation_fatima_aida = new TCanvas("c_whiterabbit_correlation_fatima_aida", "AIDA - FATIMA WR dT (ns)", 10, 10, 800, 700);
    c_whiterabbit_correlation_fatima_aida->cd();
    h1_whiterabbit_correlation_fatima_aida = new TH1I("h1_whiterabbit_correlation_fatima_aida", "AIDA - FATIMA WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_fatima_aida->GetXaxis()->SetTitle("Time difference(AIDA - FATIMA) [ns]");
    h1_whiterabbit_correlation_fatima_aida->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatima_aida->Draw();
    folder_whiterabbit_correlation->Add(h1_whiterabbit_correlation_fatima_aida);
    c_whiterabbit_correlation_fatima_aida->cd(0);

    c_whiterabbit_trigger1_fatima_aida = new TCanvas("c_whiterabbit_correlation_trigger1_fatima_aida", "White Rabbit Trigger 1 FATIMA-AIDA", 10, 10, 800, 700);
    c_whiterabbit_trigger1_fatima_aida->cd();
    h1_whiterabbit_trigger1_fatima_aida = new TH1I("h1_whiterabbit_trigger1_fatima_aida", "White Rabbit Trigger 1 FATIMA-AIDA",1000,-1e3,5e4);
    h1_whiterabbit_trigger1_fatima_aida->GetXaxis()->SetTitle("AIDA - FATIMA WR dT (ns)");
    h1_whiterabbit_trigger1_fatima_aida->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_fatima_aida->Draw();
    folder_whiterabbit_trigger1->Add(h1_whiterabbit_trigger1_fatima_aida);
    c_whiterabbit_trigger1_fatima_aida->cd(0);

    c_whiterabbit_trigger3_fatima_aida = new TCanvas("c_whiterabbit_correlation_trigger3_fatima_aida", "White Rabbit Trigger 3 FATIMA-AIDA", 10, 10, 800, 700);
    c_whiterabbit_trigger3_fatima_aida->cd();
    h1_whiterabbit_trigger3_fatima_aida = new TH1I("h1_whiterabbit_trigger3_fatima_aida", "White Rabbit Trigger 3 FATIMA-AIDA",1000,-1e3,5e4);
    h1_whiterabbit_trigger3_fatima_aida->GetXaxis()->SetTitle("AIDA - FATIMA WR dT (ns)");
    h1_whiterabbit_trigger3_fatima_aida->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_fatima_aida->Draw();
    folder_whiterabbit_trigger3->Add(h1_whiterabbit_trigger3_fatima_aida);
    c_whiterabbit_trigger3_fatima_aida->cd(0);


    // AIDA - FatimaVme
    c_whiterabbit_correlation_fatimavme_aida = new TCanvas("c_whiterabbit_correlation_fatimavme_aida", "AIDA - FATIMA VME WR dT (ns)", 10, 10, 800, 700);
    c_whiterabbit_correlation_fatimavme_aida->cd();
    h1_whiterabbit_correlation_fatimavme_aida = new TH1I("h1_whiterabbit_correlation_fatimavme_aida", "AIDA - FATIMAVME WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_fatimavme_aida->GetXaxis()->SetTitle("Time difference (AIDA - FATIMA VME) [ns]");
    h1_whiterabbit_correlation_fatimavme_aida->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatimavme_aida->Draw();
    folder_whiterabbit_correlation->Add(h1_whiterabbit_correlation_fatimavme_aida);
    c_whiterabbit_correlation_fatimavme_aida->cd(0);

    c_whiterabbit_trigger1_fatimavme_aida = new TCanvas("c_whiterabbit_correlation_trigger1_fatimavme_aida", "White Rabbit Trigger 1 FATIMA VME-AIDA", 10, 10, 800, 700);
    c_whiterabbit_trigger1_fatimavme_aida->cd();
    h1_whiterabbit_trigger1_fatimavme_aida = new TH1I("h1_whiterabbit_trigger1_fatimavme_aida", "White Rabbit Trigger 1 FATIMA VME-AIDA",1000,-1e3,5e4);
    h1_whiterabbit_trigger1_fatimavme_aida->GetXaxis()->SetTitle("AIDA - FATIMA VME WR dT (ns)");
    h1_whiterabbit_trigger1_fatimavme_aida->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_fatimavme_aida->Draw();
    folder_whiterabbit_trigger1->Add(h1_whiterabbit_trigger1_fatimavme_aida);
    c_whiterabbit_trigger1_fatimavme_aida->cd(0);

    c_whiterabbit_trigger3_fatimavme_aida = new TCanvas("c_whiterabbit_correlation_trigger3_fatimavme_aida", "White Rabbit Trigger 3 FATIMA VME-AIDA", 10, 10, 800, 700);
    c_whiterabbit_trigger3_fatimavme_aida->cd();
    h1_whiterabbit_trigger3_fatimavme_aida = new TH1I("h1_whiterabbit_trigger3_fatimavme_aida", "White Rabbit Trigger 3 FATIMA VME-AIDA",1000,-1e3,5e4);
    h1_whiterabbit_trigger3_fatimavme_aida->GetXaxis()->SetTitle("AIDA - FATIMA VME WR dT (ns)");
    h1_whiterabbit_trigger3_fatimavme_aida->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_fatimavme_aida->Draw();
    folder_whiterabbit_trigger3->Add(h1_whiterabbit_trigger3_fatimavme_aida);
    c_whiterabbit_trigger3_fatimavme_aida->cd(0);

    // AIDA - bPlast
    c_whiterabbit_correlation_aida_bplast = new TCanvas("c_whiterabbit_correlation_aida_bplast", "AIDA - bPlast WR dT (ns)", 10, 10, 800, 700);
    c_whiterabbit_correlation_aida_bplast->cd();
    h1_whiterabbit_correlation_aida_bplast = new TH1I("h1_whiterabbit_correlation_aida_bplast", "AIDA - bPlast WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_aida_bplast->GetXaxis()->SetTitle("Time difference (AIDA - bPlast) [ns]");
    h1_whiterabbit_correlation_aida_bplast->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_aida_bplast->Draw();
    folder_whiterabbit_correlation->Add(h1_whiterabbit_correlation_aida_bplast);
    c_whiterabbit_correlation_aida_bplast->cd(0);

    c_whiterabbit_trigger1_aida_bplast = new TCanvas("c_whiterabbit_correlation_trigger1_aida_bplast", "White Rabbit Trigger 1 AIDA-bPlast", 10, 10, 800, 700);
    c_whiterabbit_trigger1_aida_bplast->cd();
    h1_whiterabbit_trigger1_aida_bplast = new TH1I("h1_whiterabbit_trigger1_aida_bplast", "White Rabbit Trigger 1 AIDA-bPlast",1000,-1e3,5e4);
    h1_whiterabbit_trigger1_aida_bplast->GetXaxis()->SetTitle("AIDA - bPlast WR dT (ns)");
    h1_whiterabbit_trigger1_aida_bplast->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_aida_bplast->Draw();
    folder_whiterabbit_trigger1->Add(h1_whiterabbit_trigger1_aida_bplast);
    c_whiterabbit_trigger1_aida_bplast->cd(0);

    c_whiterabbit_trigger3_aida_bplast = new TCanvas("c_whiterabbit_correlation_trigger3_aida_bplast", "White Rabbit Trigger 3 AIDA-bPlast", 10, 10, 800, 700);
    c_whiterabbit_trigger3_aida_bplast->cd();
    h1_whiterabbit_trigger3_aida_bplast = new TH1I("h1_whiterabbit_trigger3_aida_bplast", "White Rabbit Trigger 3 AIDA-bPlast",1000,-1e3,5e4);
    h1_whiterabbit_trigger3_aida_bplast->GetXaxis()->SetTitle("AIDA - bPlast WR dT (ns)");
    h1_whiterabbit_trigger3_aida_bplast->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_aida_bplast->Draw();
    folder_whiterabbit_trigger3->Add(h1_whiterabbit_trigger3_aida_bplast);
    c_whiterabbit_trigger3_aida_bplast->cd(0);

    // AIDA - Germanium
    c_whiterabbit_correlation_aida_germanium = new TCanvas("c_whiterabbit_correlation_aida_germanium", "AIDA - DEGAS WR dT (ns)", 10, 10, 800, 700);
    c_whiterabbit_correlation_aida_germanium->cd();
    h1_whiterabbit_correlation_aida_germanium = new TH1I("h1_whiterabbit_correlation_aida_germanium", "AIDA - DEGAS WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_aida_germanium->GetXaxis()->SetTitle("Time difference (AIDA - DEGAS) [ns]");
    h1_whiterabbit_correlation_aida_germanium->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_aida_germanium->Draw();
    folder_whiterabbit_correlation->Add(h1_whiterabbit_correlation_aida_germanium);
    c_whiterabbit_correlation_aida_germanium->cd(0);

    c_whiterabbit_trigger1_aida_germanium = new TCanvas("c_whiterabbit_correlation_trigger1_aida_germanium", "White Rabbit Trigger 1 AIDA-DEGAS", 10, 10, 800, 700);
    c_whiterabbit_trigger1_aida_germanium->cd();
    h1_whiterabbit_trigger1_aida_germanium = new TH1I("h1_whiterabbit_trigger1_aida_germanium", "White Rabbit Trigger 1 AIDA-DEGAS",1000,-1e3,5e4);
    h1_whiterabbit_trigger1_aida_germanium->GetXaxis()->SetTitle("AIDA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_aida_germanium->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_aida_germanium->Draw();
    folder_whiterabbit_trigger1->Add(h1_whiterabbit_trigger1_aida_germanium);
    c_whiterabbit_trigger1_aida_germanium->cd(0);

    c_whiterabbit_trigger3_aida_germanium = new TCanvas("c_whiterabbit_correlation_trigger3_aida_germanium", "White Rabbit Trigger 3 AIDA-DEGAS", 10, 10, 800, 700);
    c_whiterabbit_trigger3_aida_germanium->cd();
    h1_whiterabbit_trigger3_aida_germanium = new TH1I("h1_whiterabbit_trigger3_aida_germanium", "White Rabbit Trigger 3 AIDA-DEGAS",1000,-1e3,5e4);
    h1_whiterabbit_trigger3_aida_germanium->GetXaxis()->SetTitle("AIDA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_aida_germanium->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_aida_germanium->Draw();
    folder_whiterabbit_trigger3->Add(h1_whiterabbit_trigger3_aida_germanium);
    c_whiterabbit_trigger3_aida_germanium->cd(0);
    

    c4LOG(info, "im the error 1");
    // FATIMA
    // Fatima - FatimaVme
    c_whiterabbit_correlation_fatima_fatimavme = new TCanvas("c_whiterabbit_correlation_fatima_fatimavme", "FATIMA - FATIMA VME WR dT (ns)", 10, 10, 800, 700);
    c_whiterabbit_correlation_fatima_fatimavme->cd();
    h1_whiterabbit_correlation_fatima_fatimavme = new TH1I("h1_whiterabbit_correlation_fatima_fatimavme", "FATIMA - FATIMA VME WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatima_fatimavme->GetXaxis()->SetTitle("Time difference (FATIMA - FATIMA VME) [ns]");
    h1_whiterabbit_correlation_fatima_fatimavme->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatima_fatimavme->Draw();
    folder_whiterabbit_correlation->Add(h1_whiterabbit_correlation_fatima_fatimavme);
    c_whiterabbit_correlation_fatima_fatimavme->cd(0);

    c_whiterabbit_trigger1_fatima_fatimavme = new TCanvas("c_whiterabbit_correlation_trigger1_fatima_fatimavme", "White Rabbit Trigger 1 FATIMA-FATIMA VME", 10, 10, 800, 700);
    c_whiterabbit_trigger1_fatima_fatimavme->cd();
    h1_whiterabbit_trigger1_fatima_fatimavme = new TH1I("h1_whiterabbit_trigger1_fatima_fatimavme", "White Rabbit Trigger 1 FATIMA-FATIMA VME", 1e3, -1e3, 1e3);
    h1_whiterabbit_trigger1_fatima_fatimavme->GetXaxis()->SetTitle("FATIMA - FATIMA VME WR dT (ns)");
    h1_whiterabbit_trigger1_fatima_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_fatima_fatimavme->Draw();
    folder_whiterabbit_trigger1->Add(h1_whiterabbit_trigger1_fatima_fatimavme);
    c_whiterabbit_trigger1_fatima_fatimavme->cd(0);

    c_whiterabbit_trigger3_fatima_fatimavme = new TCanvas("c_whiterabbit_correlation_trigger3_fatima_fatimavme", "White Rabbit Trigger 3 FATIMA-FATIMA VME", 10, 10, 800, 700);
    c_whiterabbit_trigger3_fatima_fatimavme->cd();
    h1_whiterabbit_trigger3_fatima_fatimavme = new TH1I("h1_whiterabbit_trigger3_fatima_fatimavme", "White Rabbit Trigger 3 FATIMA-FATIMA VME",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatima_fatimavme->GetXaxis()->SetTitle("FATIMA - FATIMA VME WR dT (ns)");
    h1_whiterabbit_trigger3_fatima_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_fatima_fatimavme->Draw();
    folder_whiterabbit_trigger3->Add(h1_whiterabbit_trigger3_fatima_fatimavme);
    c_whiterabbit_trigger3_fatima_fatimavme->cd(0);


    // Fatima - bPlast
    c_whiterabbit_correlation_bplast_fatima = new TCanvas("c_whiterabbit_correlation_bplast_fatima", "bPlast - FATIMA WR dT (ns)", 10, 10, 800, 700);
    c_whiterabbit_correlation_bplast_fatima->cd();
    h1_whiterabbit_correlation_bplast_fatima = new TH1I("h1_whiterabbit_correlation_bplast_fatima", "bPlast - FATIMA WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_bplast_fatima->GetXaxis()->SetTitle("Time difference (bPlast - FATIMA) [ns]");
    h1_whiterabbit_correlation_bplast_fatima->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_bplast_fatima->Draw();
    folder_whiterabbit_correlation->Add(h1_whiterabbit_correlation_bplast_fatima);
    c_whiterabbit_correlation_bplast_fatima->cd(0);

    c_whiterabbit_trigger1_bplast_fatima = new TCanvas("c_whiterabbit_trigger1_bplast_fatima", "White Rabbit Trigger 1 bPlast-FATIMA", 10, 10, 800, 700);
    c_whiterabbit_trigger1_bplast_fatima->cd();
    h1_whiterabbit_trigger1_bplast_fatima = new TH1I("h1_whiterabbit_trigger1_bplast_fatima", "White Rabbit Trigger 1 bPlast-FATIMA", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_bplast_fatima->GetXaxis()->SetTitle("bPlast - FATIMA WR dT (ns)");
    h1_whiterabbit_trigger1_bplast_fatima->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_bplast_fatima->Draw();
    folder_whiterabbit_trigger1->Add(h1_whiterabbit_trigger1_bplast_fatima);
    c_whiterabbit_trigger1_bplast_fatima->cd(0);

    c_whiterabbit_trigger3_bplast_fatima = new TCanvas("c_whiterabbit_trigger3_bplast_fatima", "White Rabbit Trigger 3 bPlast-FATIMA", 10, 10, 800, 700);
    c_whiterabbit_trigger3_bplast_fatima->cd();
    h1_whiterabbit_trigger3_bplast_fatima = new TH1I("h1_whiterabbit_trigger3_bplast_fatima", "White Rabbit Trigger 3 bPlast-FATIMA",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_bplast_fatima->GetXaxis()->SetTitle("bPlast - FATIMA WR dT (ns)");
    h1_whiterabbit_trigger3_bplast_fatima->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_bplast_fatima->Draw();
    folder_whiterabbit_trigger3->Add(h1_whiterabbit_trigger3_bplast_fatima);
    c_whiterabbit_trigger3_bplast_fatima->cd(0);

    // Fatima - Germanium
    c_whiterabbit_correlation_fatima_ge = new TCanvas("c_whiterabbit_correlation_fatima_ge", "White Rabbit FATIMA-DEGAS", 10, 10, 800, 700);
    c_whiterabbit_correlation_fatima_ge->cd();
    h1_whiterabbit_correlation_fatima_ge = new TH1I("h1_whiterabbit_correlation_fatima_ge", "FATIMA - DEGAS WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatima_ge->GetXaxis()->SetTitle("Time difference (FATIMA - DEGAS) [ns]");
    h1_whiterabbit_correlation_fatima_ge->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatima_ge->Draw();
    folder_whiterabbit_correlation->Add(h1_whiterabbit_correlation_fatima_ge);
    c_whiterabbit_correlation_fatima_ge->cd(0);

    c_whiterabbit_trigger1_fatima_ge = new TCanvas("c_whiterabbit_correlation_trigger1_fatima_ge", "White Rabbit Trigger 1 FATIMA-DEGAS", 10, 10, 800, 700);
    c_whiterabbit_trigger1_fatima_ge->cd();
    h1_whiterabbit_trigger1_fatima_ge = new TH1I("h1_whiterabbit_trigger1_fatima_ge", "White Rabbit Trigger 1 FATIMA-DEGAS", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_fatima_ge->GetXaxis()->SetTitle("FATIMA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_fatima_ge->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_fatima_ge->Draw();
    folder_whiterabbit_trigger1->Add(h1_whiterabbit_trigger1_fatima_ge);
    c_whiterabbit_trigger1_fatima_ge->cd(0);

    c_whiterabbit_trigger3_fatima_ge = new TCanvas("c_whiterabbit_correlation_trigger3_fatima_ge", "White Rabbit Trigger 3 FATIMA-DEGAS", 10, 10, 800, 700);
    c_whiterabbit_trigger3_fatima_ge->cd();
    h1_whiterabbit_trigger3_fatima_ge = new TH1I("h1_whiterabbit_trigger3_fatima_ge", "White Rabbit Trigger 3 FATIMA-DEGAS",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatima_ge->GetXaxis()->SetTitle("FATIMA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_fatima_ge->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_fatima_ge->Draw();
    folder_whiterabbit_trigger3->Add(h1_whiterabbit_trigger3_fatima_ge);
    c_whiterabbit_trigger3_fatima_ge->cd(0);

    
    // FatimaVme - bPlast
    c_whiterabbit_correlation_bplast_fatimavme = new TCanvas("c_whiterabbit_correlation_bplast_fatimavme", "bPlast - FATIMA VME WR dT (ns)", 10, 10, 800, 700);
    c_whiterabbit_correlation_bplast_fatimavme->cd();
    h1_whiterabbit_correlation_bplast_fatimavme = new TH1I("h1_whiterabbit_correlation_bplast_fatimavme", "bPlast - FATIMA VME WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_bplast_fatimavme->GetXaxis()->SetTitle("Time difference (bPlast - FATIMA VME) [ns]");
    h1_whiterabbit_correlation_bplast_fatimavme->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_bplast_fatimavme->Draw();
    folder_whiterabbit_correlation->Add(h1_whiterabbit_correlation_bplast_fatimavme);
    c_whiterabbit_correlation_bplast_fatimavme->cd(0);

    c_whiterabbit_trigger1_bplast_fatimavme = new TCanvas("c_whiterabbit_correlation_trigger1_bplast_fatimavme", "White Rabbit Trigger 1 bPlast-FATIMA VME", 10, 10, 800, 700);
    c_whiterabbit_trigger1_bplast_fatimavme->cd();
    h1_whiterabbit_trigger1_bplast_fatimavme = new TH1I("h1_whiterabbit_trigger1_bplast_fatimavme", "White Rabbit Trigger 1 bPlast-FATIMA VME", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_bplast_fatimavme->GetXaxis()->SetTitle("bPlast - FATIMA VME WR dT (ns)");
    h1_whiterabbit_trigger1_bplast_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_bplast_fatimavme->Draw();
    folder_whiterabbit_trigger1->Add(h1_whiterabbit_trigger1_bplast_fatimavme);
    c_whiterabbit_trigger1_bplast_fatimavme->cd(0);

    c_whiterabbit_trigger3_bplast_fatimavme = new TCanvas("c_whiterabbit_correlation_trigger3_bplast_fatimavme", "White Rabbit Trigger 3 bPlast-FATIMA VME", 10, 10, 800, 700);
    c_whiterabbit_trigger3_bplast_fatimavme->cd();
    h1_whiterabbit_trigger3_bplast_fatimavme = new TH1I("h1_whiterabbit_trigger3_bplast_fatimavme", "White Rabbit Trigger 3 bPlast-FATIMA VME",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_bplast_fatimavme->GetXaxis()->SetTitle("bPlast - FATIMA VME WR dT (ns)");
    h1_whiterabbit_trigger3_bplast_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_bplast_fatimavme->Draw();
    folder_whiterabbit_trigger3->Add(h1_whiterabbit_trigger3_bplast_fatimavme);
    c_whiterabbit_trigger3_bplast_fatimavme->cd(0);

    // FatimaVme - Germanium
    c_whiterabbit_correlation_fatimavme_ge = new TCanvas("c_whiterabbit_correlation_fatimavme_ge", "FATIMA VME - DEGAS WR dT (ns)", 10, 10, 800, 700);
    c_whiterabbit_correlation_fatimavme_ge->cd();
    h1_whiterabbit_correlation_fatimavme_ge = new TH1I("h1_whiterabbit_correlation_fatimavme_ge", "FATIMA VME - DEGAS WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatimavme_ge->GetXaxis()->SetTitle("Time difference (FATIMA VME - DEGAS) [ns]");
    h1_whiterabbit_correlation_fatimavme_ge->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatimavme_ge->Draw();
    folder_whiterabbit_correlation->Add(h1_whiterabbit_correlation_fatimavme_ge);
    c_whiterabbit_correlation_fatimavme_ge->cd(0);

    c_whiterabbit_trigger1_fatimavme_ge = new TCanvas("c_whiterabbit_correlation_trigger1_fatimavme_ge", "White Rabbit Trigger 1 FATIMA VME-DEGAS", 10, 10, 800, 700);
    c_whiterabbit_trigger1_fatimavme_ge->cd();
    h1_whiterabbit_trigger1_fatimavme_ge = new TH1I("h1_whiterabbit_trigger1_fatimavme_ge", "White Rabbit Trigger 1 FATIMA VME-DEGAS", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_fatimavme_ge->GetXaxis()->SetTitle("FATIMA VME - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_fatimavme_ge->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_fatimavme_ge->Draw();
    folder_whiterabbit_trigger1->Add(h1_whiterabbit_trigger1_fatimavme_ge);
    c_whiterabbit_trigger1_fatimavme_ge->cd(0);

    c_whiterabbit_trigger3_fatimavme_ge = new TCanvas("c_whiterabbit_correlation_trigger3_fatimavme_ge", "White Rabbit Trigger 3 FATIMA VME-DEGAS", 10, 10, 800, 700);
    c_whiterabbit_trigger3_fatimavme_ge->cd();
    h1_whiterabbit_trigger3_fatimavme_ge = new TH1I("h1_whiterabbit_trigger3_fatimavme_ge", "White Rabbit Trigger 3 FATIMA VME-DEGAS",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatimavme_ge->GetXaxis()->SetTitle("FATIMA VME - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_fatimavme_ge->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_fatimavme_ge->Draw();
    folder_whiterabbit_trigger3->Add(h1_whiterabbit_trigger3_fatimavme_ge);
    c_whiterabbit_trigger3_fatimavme_ge->cd(0);

    // bPlast
    // bPlast - Germanium
    c_whiterabbit_correlation_bplast_ge = new TCanvas("c_whiterabbit_correlation_bplast_ge", "bPlast - DEGAS WR dT (ns)", 10, 10, 800, 700);
    c_whiterabbit_correlation_bplast_ge->cd();
    h1_whiterabbit_correlation_bplast_ge = new TH1I("h1_whiterabbit_correlation_bplast_ge", "bPlast - DEGAS WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_bplast_ge->GetXaxis()->SetTitle("Time difference (bPlast - DEGAS) [ns]");
    h1_whiterabbit_correlation_bplast_ge->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_bplast_ge->Draw();
    folder_whiterabbit_correlation->Add(h1_whiterabbit_correlation_bplast_ge);
    c_whiterabbit_correlation_bplast_ge->cd(0);

    c_whiterabbit_trigger1_bplast_ge = new TCanvas("c_whiterabbit_correlation_trigger1_bplast_ge", "White Rabbit Trigger 1 bPlast-DEGAS", 10, 10, 800, 700);
    c_whiterabbit_trigger1_bplast_ge->cd();
    h1_whiterabbit_trigger1_bplast_ge = new TH1I("h1_whiterabbit_trigger1_bplast_ge", "White Rabbit Trigger 1 bPlast-DEGAS", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_bplast_ge->GetXaxis()->SetTitle("bPlast - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_bplast_ge->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_bplast_ge->Draw();
    folder_whiterabbit_trigger1->Add(h1_whiterabbit_trigger1_bplast_ge);
    c_whiterabbit_trigger1_bplast_ge->cd(0);

    c_whiterabbit_trigger3_bplast_ge = new TCanvas("c_whiterabbit_correlation_trigger3_bplast_ge", "White Rabbit Trigger 3 bPlast-DEGAS", 10, 10, 800, 700);
    c_whiterabbit_trigger3_bplast_ge->cd();
    h1_whiterabbit_trigger3_bplast_ge = new TH1I("h1_whiterabbit_trigger3_bplast_ge", "White Rabbit Trigger 3 bPlast-DEGAS",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_bplast_ge->GetXaxis()->SetTitle("bPlast - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_bplast_ge->GetYaxis()->SetTitle("Counts (Trigger 3)");
    h1_whiterabbit_trigger3_bplast_ge->Draw();
    folder_whiterabbit_trigger3->Add(h1_whiterabbit_trigger3_bplast_ge);
    c_whiterabbit_trigger3_bplast_ge->cd(0);

    // Trigger ID

    c_whiterabbit_trigger = new TCanvas("c_whiterabbit_trigger", "White Rabbit Trigger ID", 10, 10, 800, 700);
    c_whiterabbit_trigger->cd();
    h1_whiterabbit_trigger = new TH1I("h1_whiterabbit_trigger", "White Rabbit Trigger ID", 5, 0, 5);
    h1_whiterabbit_trigger->GetXaxis()->SetTitle("Trigger ID");
    h1_whiterabbit_trigger->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_trigger->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_trigger);
    c_whiterabbit_trigger->cd(0);


    c4LOG(info, "im the error 2");
    // Canvas addition for 10 detector systems

    c_whiterabbit_correlation = new TCanvas("c_whiterabbit_correlation", "White Rabbit Correlation", 10, 10, 800, 700);
    c_whiterabbit_correlation->Divide(5, 2);
    c_whiterabbit_correlation->cd(1);
    h1_whiterabbit_correlation_bplast_fatima->Draw();
    c_whiterabbit_correlation->cd(2);
    h1_whiterabbit_correlation_fatima_ge->Draw();
    c_whiterabbit_correlation->cd(3);
    h1_whiterabbit_correlation_bplast_ge->Draw();
    c_whiterabbit_correlation->cd(4);
    h1_whiterabbit_correlation_fatima_aida->Draw();
    c_whiterabbit_correlation->cd(5);
    h1_whiterabbit_correlation_fatimavme_ge->Draw();
    c_whiterabbit_correlation->cd(6);
    h1_whiterabbit_correlation_aida_bplast->Draw();
    c_whiterabbit_correlation->cd(7);
    h1_whiterabbit_correlation_aida_germanium->Draw();
    c_whiterabbit_correlation->cd(8);
    h1_whiterabbit_correlation_fatima_fatimavme->Draw();
    c_whiterabbit_correlation->cd(9);
    h1_whiterabbit_correlation_fatimavme_aida->Draw();
    c_whiterabbit_correlation->cd(10);
    h1_whiterabbit_correlation_bplast_fatimavme->Draw();
    c_whiterabbit_correlation->cd(0);

    folder_whiterabbit_correlation->Add(c_whiterabbit_correlation);

    c_whiterabbit_trigger1 = new TCanvas("c_whiterabbit_trigger1", "White Rabbit Trigger 1", 10, 10, 800, 700);
    c_whiterabbit_trigger1->Divide(5, 2);
    c_whiterabbit_trigger1->cd(1);
    h1_whiterabbit_trigger1_bplast_fatima->Draw();
    c_whiterabbit_trigger1->cd(2);
    h1_whiterabbit_trigger1_fatima_ge->Draw();
    c_whiterabbit_trigger1->cd(3);
    h1_whiterabbit_trigger1_bplast_ge->Draw();
    c_whiterabbit_trigger1->cd(4);
    h1_whiterabbit_trigger1_fatima_aida->Draw();
    c_whiterabbit_trigger1->cd(5);
    h1_whiterabbit_trigger1_fatimavme_ge->Draw();
    c_whiterabbit_trigger1->cd(6);
    h1_whiterabbit_trigger1_aida_bplast->Draw();
    c_whiterabbit_trigger1->cd(7);
    h1_whiterabbit_trigger1_aida_germanium->Draw();
    c_whiterabbit_trigger1->cd(8);
    h1_whiterabbit_trigger1_fatima_fatimavme->Draw();
    c_whiterabbit_trigger1->cd(9);
    h1_whiterabbit_trigger1_fatimavme_aida->Draw();
    c_whiterabbit_trigger1->cd(10);
    h1_whiterabbit_trigger1_bplast_fatimavme->Draw();
    c_whiterabbit_trigger1->cd(0);

    folder_whiterabbit_trigger1->Add(c_whiterabbit_trigger1);

    c_whiterabbit_trigger3 = new TCanvas("c_whiterabbit_trigger3", "White Rabbit Trigger 3", 10, 10, 800, 700);
    c_whiterabbit_trigger3->Divide(5, 2);
    c_whiterabbit_trigger3->cd(1);
    h1_whiterabbit_trigger3_bplast_fatima->Draw();
    c_whiterabbit_trigger3->cd(2);
    h1_whiterabbit_trigger3_fatima_ge->Draw();
    c_whiterabbit_trigger3->cd(3);
    h1_whiterabbit_trigger3_bplast_ge->Draw();
    c_whiterabbit_trigger3->cd(4);
    h1_whiterabbit_trigger3_fatima_aida->Draw();
    c_whiterabbit_trigger3->cd(5);
    h1_whiterabbit_trigger3_fatimavme_ge->Draw();
    c_whiterabbit_trigger3->cd(6);
    h1_whiterabbit_trigger3_aida_bplast->Draw();
    c_whiterabbit_trigger3->cd(7);
    h1_whiterabbit_trigger3_aida_germanium->Draw();
    c_whiterabbit_trigger3->cd(8);
    h1_whiterabbit_trigger3_fatima_fatimavme->Draw();
    c_whiterabbit_trigger3->cd(9);
    h1_whiterabbit_trigger3_fatimavme_aida->Draw();
    c_whiterabbit_trigger3->cd(10);
    h1_whiterabbit_trigger3_bplast_fatimavme->Draw();
    c_whiterabbit_trigger3->cd(0);

    folder_whiterabbit_trigger3->Add(c_whiterabbit_trigger3);

    // Register command to reset histograms

    c4LOG(info, "im the error 3");

    run->GetHttpServer()->RegisterCommand("Reset_Whiterabbit_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Whiterabbit_Hist", Form("/Objects/%s/->Snapshot_Histo()", GetName()));
    
    return kSUCCESS;
}

// work in progress
void WhiterabbitCorrelationOnline::Reset_Histo()
{
    c4LOG(info, "I'm late, I'm late, for a very important date! No time to say 'Hello, Good Bye' I'm late, I'm late, I'm late!");
    h1_whiterabbit_correlation_bplast_fatima->Reset();
    h1_whiterabbit_trigger1_bplast_fatima->Reset();
    h1_whiterabbit_trigger3_bplast_fatima->Reset();

    h1_whiterabbit_correlation_fatima_ge->Reset();
    h1_whiterabbit_trigger1_fatima_ge->Reset();
    h1_whiterabbit_trigger3_fatima_ge->Reset();

    h1_whiterabbit_correlation_bplast_ge->Reset();
    h1_whiterabbit_trigger1_bplast_ge->Reset();
    h1_whiterabbit_trigger3_bplast_ge->Reset();

    h1_whiterabbit_correlation_fatima_aida->Reset();
    h1_whiterabbit_trigger1_fatima_aida->Reset();
    h1_whiterabbit_trigger3_fatima_aida->Reset();

    h1_whiterabbit_correlation_fatimavme_aida->Reset();
    h1_whiterabbit_trigger1_fatimavme_aida->Reset();
    h1_whiterabbit_trigger3_fatimavme_aida->Reset();

    h1_whiterabbit_correlation_aida_bplast->Reset();
    h1_whiterabbit_trigger1_aida_bplast->Reset();
    h1_whiterabbit_trigger3_aida_bplast->Reset();

    h1_whiterabbit_correlation_aida_germanium->Reset();
    h1_whiterabbit_trigger1_aida_germanium->Reset();
    h1_whiterabbit_trigger3_aida_germanium->Reset();

    h1_whiterabbit_correlation_fatima_fatimavme->Reset();
    h1_whiterabbit_trigger1_fatima_fatimavme->Reset();
    h1_whiterabbit_trigger3_fatima_fatimavme->Reset();

    h1_whiterabbit_correlation_fatimavme_ge->Reset();
    h1_whiterabbit_trigger1_fatimavme_ge->Reset();
    h1_whiterabbit_trigger3_fatimavme_ge->Reset();

    h1_whiterabbit_correlation_bplast_fatimavme->Reset();
    h1_whiterabbit_trigger1_bplast_fatimavme->Reset();
    h1_whiterabbit_trigger3_bplast_fatimavme->Reset();

    h1_whiterabbit_trigger->Reset();
}
void WhiterabbitCorrelationOnline::Snapshot_Histo()
{
    c4LOG(info, "Good heavens, would you look at the time!");

    time_t now = time(0);
    tm *ltm = localtime(&now);

    const char* snapshot_dir = Form("Whiterabbit_correlation_%d_%d_%d_%d_%d_%d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    c_whiterabbit_correlation_bplast_fatima->SaveAs("c_whiterabbit_correlation_bplast_fatima.png");
    c_whiterabbit_trigger1_bplast_fatima->SaveAs("c_whiterabbit_trigger1_bplast_fatima.png");
    c_whiterabbit_trigger3_bplast_fatima->SaveAs("c_whiterabbit_trigger3_bplast_fatima.png");

    c_whiterabbit_correlation_fatima_ge->SaveAs("c_whiterabbit_correlation_fatima_ge.png");
    c_whiterabbit_trigger1_fatima_ge->SaveAs("c_whiterabbit_trigger1_fatima_ge.png");
    c_whiterabbit_trigger3_fatima_ge->SaveAs("c_whiterabbit_trigger3_fatima_ge.png");

    c_whiterabbit_correlation_fatima_aida->SaveAs("c_whiterabbit_correlation_fatima_aida.png");
    c_whiterabbit_trigger1_fatima_aida->SaveAs("c_whiterabbit_trigger1_fatima_aida.png");
    c_whiterabbit_trigger3_fatima_aida->SaveAs("c_whiterabbit_trigger3_fatima_aida.png");

    c_whiterabbit_correlation_bplast_ge->SaveAs("c_whiterabbit_correlation_bplast_ge.png");
    c_whiterabbit_trigger1_bplast_ge->SaveAs("c_whiterabbit_trigger1_bplast_ge.png");
    c_whiterabbit_trigger3_bplast_ge->SaveAs("c_whiterabbit_trigger3_bplast_ge.png");

    c_whiterabbit_correlation_fatimavme_aida->SaveAs("c_whiterabbit_correlation_fatimavme_aida.png");
    c_whiterabbit_trigger1_fatimavme_aida->SaveAs("c_whiterabbit_trigger1_fatimavme_aida.png");
    c_whiterabbit_trigger3_fatimavme_aida->SaveAs("c_whiterabbit_trigger3_fatimavme_aida.png");

    c_whiterabbit_correlation_aida_bplast->SaveAs("c_whiterabbit_correlation_aida_bplast.png");
    c_whiterabbit_trigger1_aida_bplast->SaveAs("c_whiterabbit_trigger1_aida_bplast.png");
    c_whiterabbit_trigger3_aida_bplast->SaveAs("c_whiterabbit_trigger3_aida_bplast.png");

    c_whiterabbit_correlation_aida_germanium->SaveAs("c_whiterabbit_correlation_aida_germanium.png");
    c_whiterabbit_trigger1_aida_germanium->SaveAs("c_whiterabbit_trigger1_aida_germanium.png");
    c_whiterabbit_trigger3_aida_germanium->SaveAs("c_whiterabbit_trigger3_aida_germanium.png");

    c_whiterabbit_correlation_fatima_fatimavme->SaveAs("c_whiterabbit_correlation_fatima_fatimavme.png");
    c_whiterabbit_trigger1_fatima_fatimavme->SaveAs("c_whiterabbit_trigger1_fatima_fatimavme.png");
    c_whiterabbit_trigger3_fatima_fatimavme->SaveAs("c_whiterabbit_trigger3_fatima_fatimavme.png");

    c_whiterabbit_correlation_fatimavme_ge->SaveAs("c_whiterabbit_correlation_fatimavme_ge.png");
    c_whiterabbit_trigger1_fatimavme_ge->SaveAs("c_whiterabbit_trigger1_fatimavme_ge.png");
    c_whiterabbit_trigger3_fatimavme_ge->SaveAs("c_whiterabbit_trigger3_fatimavme_ge.png");

    c_whiterabbit_correlation_bplast_fatimavme->SaveAs("c_whiterabbit_correlation_bplast_fatimavme.png");
    c_whiterabbit_trigger1_bplast_fatimavme->SaveAs("c_whiterabbit_trigger1_bplast_fatimavme.png");
    c_whiterabbit_trigger3_bplast_fatimavme->SaveAs("c_whiterabbit_trigger3_bplast_fatimavme.png");

    c_whiterabbit_trigger->SaveAs("c_whiterabbit_trigger.png");

    // snapshot .root file with data and time

    file_whiterabbit_snapshot = new TFile(Form("whiterabbit_snapshot_%d_%d_%d_%d_%d_%d.root", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec), "RECREATE");
    file_whiterabbit_snapshot->cd();
    folder_whiterabbit->Write();
    file_whiterabbit_snapshot->Close();
    delete file_whiterabbit_snapshot;

    gSystem->cd("..");
    c4LOG(info, "Snapshot saved in:" << snapshot_dir);    
}


void WhiterabbitCorrelationOnline::Exec(Option_t* option)
{

    Int_t nHitsFatimaVme = 0;
    Int_t nHitsFatima = 0;
    Int_t nHitsbPlast = 0;
    Int_t nHitsGe = 0;
    Int_t nHitsAida = 0;
    
    if (fHitFatimaTwinpeaks) nHitsFatima = fHitFatimaTwinpeaks->GetEntriesFast();
    if (fHitbPlastTwinpeaks) nHitsbPlast = fHitbPlastTwinpeaks->GetEntriesFast();
    if (fHitGe) nHitsGe = fHitGe->GetEntriesFast();

    if (fHitFatimaVme) nHitsFatimaVme = fHitFatimaVme->GetEntriesFast();
    
    //if (fAidaDecays) nHitsAida = fAidaDecays->GetEntries();


    // start with aida...
    int aidaCounter = 0;
    for (auto & i : *fAidaDecays)
    {
        if (aidaCounter > 0) break;
        AidaHit hitAida = i;
        int wr_aida = hitAida.Time;
        
        if (fHitFatimaTwinpeaks)
        {
            FatimaTwinpeaksCalData* hitFatima = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(0);
            if (!hitFatima) continue;
            int wr_fatima = hitFatima->Get_wr_t();
            int dt = wr_aida - wr_fatima;
            h1_whiterabbit_correlation_fatima_aida->Fill(dt);
            if (fEventHeader->GetTrigger() == 1)
            {
                h1_whiterabbit_trigger1_fatima_aida->Fill(dt);
            }
            if (fEventHeader->GetTrigger() == 3)
            {
                h1_whiterabbit_trigger3_fatima_aida->Fill(dt);
            }
        }
        
        if (fHitFatimaVme)
        {
            FatimaVmeCalData* hitFatimaVme = (FatimaVmeCalData*)fHitFatimaVme->At(0);
            if (!hitFatimaVme) continue;
            int wr_fatimavme = hitFatimaVme->Get_wr_t();
            int dt = wr_aida - wr_fatimavme;
            h1_whiterabbit_correlation_fatimavme_aida->Fill(dt);
            if (fEventHeader->GetTrigger() == 1)
            {
                h1_whiterabbit_trigger1_fatimavme_aida->Fill(dt);
            }
            if (fEventHeader->GetTrigger() == 3)
            {
                h1_whiterabbit_trigger3_fatimavme_aida->Fill(dt);
            }
        }
        
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
            FatimaVmeCalData* hitFatimaVme = (FatimaVmeCalData*)fHitFatimaVme->At(0);
            if (hitFatimaVme)
            {
                int wr_fatima_vme = hitFatimaVme->Get_wr_t();
                int dt = wr_fatima - wr_fatima_vme;
                h1_whiterabbit_correlation_fatima_fatimavme->Fill(dt);
                if (fEventHeader->GetTrigger() == 1)
                {
                    h1_whiterabbit_trigger1_fatima_fatimavme->Fill(dt);
                }
                if (fEventHeader->GetTrigger() == 3)
                {
                    h1_whiterabbit_trigger3_fatima_fatimavme->Fill(dt);
                }
            }
            
            bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
            if (hitbPlast)
            {
                int wr_bplast = hitbPlast->Get_wr_t();
                int dt = wr_bplast - wr_fatima;
                h1_whiterabbit_correlation_bplast_fatima->Fill(dt);
                if (fEventHeader->GetTrigger() == 1)
                {
                    h1_whiterabbit_trigger1_bplast_fatima->Fill(dt);
                }
                if (fEventHeader->GetTrigger() == 3)
                {
                    h1_whiterabbit_trigger3_bplast_fatima->Fill(dt);
                }
            }
            
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
    
    if (fHitFatimaVme)
    {
        FatimaVmeCalData* hitFatimaVme = (FatimaVmeCalData*)fHitFatimaVme->At(0);
        if (hitFatimaVme)
        {
            int wr_fatimavme= hitFatimaVme->Get_wr_t();
            bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
            if (hitbPlast)
            {
                int wr_bplast = hitbPlast->Get_wr_t();
                int dt = wr_bplast - wr_fatimavme;
                h1_whiterabbit_correlation_bplast_fatimavme->Fill(dt);
                if (fEventHeader->GetTrigger() == 1)
                {
                    h1_whiterabbit_trigger1_bplast_fatimavme->Fill(dt);
                }
                if (fEventHeader->GetTrigger() == 3)
                {
                    h1_whiterabbit_trigger3_bplast_fatimavme->Fill(dt);
                }
            }
            
            GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(0);
            if (hitGe)
            {
                int wr_ge = hitGe->Get_wr_t();
                int dt = wr_fatimavme - wr_ge;
                h1_whiterabbit_correlation_fatimavme_ge->Fill(dt);
                if (fEventHeader->GetTrigger() == 1)
                {
                    h1_whiterabbit_trigger1_fatimavme_ge->Fill(dt);
                }
                if (fEventHeader->GetTrigger() == 3)
                {
                    h1_whiterabbit_trigger3_fatimavme_ge->Fill(dt);
                }
            }
        }
    }
        
    if (fHitbPlastTwinpeaks)
    {
        bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
        if (hitbPlast)
        {
            int bplast_wr = hitbPlast->Get_wr_t();
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
    h1_whiterabbit_trigger->Fill(fEventHeader->GetTrigger());

    fNEvents += 1;
}





void WhiterabbitCorrelationOnline::FinishEvent()
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

void WhiterabbitCorrelationOnline::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events found, no histograms written.");
        return;
    }
    if (fHitFatimaTwinpeaks || fHitbPlastTwinpeaks || fHitGe || fHitFatimaVme || fAidaDecays)
    {   
        //folder_whiterabbit->Write();
        c4LOG(info, "Processed " << fNEvents << " events.");
        c4LOG(info, "WhiteRabbit histograms written to file.");
    }
}

ClassImp(WhiterabbitCorrelationOnline)
