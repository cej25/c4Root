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
#include "FrsHitData.h"
#include "FrsHitData.h"

#include "AnalysisTools.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TH1I.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"
#include <chrono>

WhiterabbitCorrelationOnline::WhiterabbitCorrelationOnline() : WhiterabbitCorrelationOnline("WhiterabbitCorrelationOnline")
{
}

WhiterabbitCorrelationOnline::WhiterabbitCorrelationOnline(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatimaTwinpeaks(NULL)
    , fHitbPlastTwinpeaks(NULL)
    , fHitGe(NULL)
    , fAidaDecays(nullptr)
    , fAidaScalers(nullptr)
    , fAidaImplants(nullptr)
    , fatVmeArray(nullptr)
    , hitArrayFrs(nullptr)
    , fNEvents(0)
    , fEventHeader(nullptr)
{
    conf = TAidaConfiguration::GetInstance();
}


WhiterabbitCorrelationOnline::~WhiterabbitCorrelationOnline()
{
    if (fHitFatimaTwinpeaks)
    {
        delete fHitFatimaTwinpeaks;
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

void WhiterabbitCorrelationOnline::SetDetectorSystems(std::vector<TString> detectorsystems)
{
    fNumDetectorSystems = detectorsystems.size();

    fDetectorSystems = std::vector<TString>(0);

    for (int i = 0; i < fNumDetectorSystems; i++) fDetectorSystems.push_back(detectorsystems.at(i));
}

InitStatus WhiterabbitCorrelationOnline::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    fEventHeader = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !fEventHeader, "Branch EventHeader. not found");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    for (int i = 0; i < fNumDetectorSystems; i++)
    {
        // check each subsystem and get the corresponding TClonesArray
        if (fDetectorSystems.at(i) == "Frs")
        {
            hitArrayFrs = mgr->InitObjectAs<decltype(hitArrayFrs)>("FrsHitData");
            c4LOG_IF(fatal, !hitArrayFrs, "Branch FrsHitData not found!"); 
        }
        else if (fDetectorSystems.at(i) == "bPlast")
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
            fatVmeArray = mgr->InitObjectAs<decltype(fatVmeArray)>("FatimaVmeTDCCalData");
            c4LOG_IF(fatal, !fatVmeArray, "Branch FatimaVmeTDCCalData not found!");
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
            fAidaImplants = mgr->InitObjectAs<decltype(fAidaImplants)>("AidaImplantHits");
            c4LOG_IF(fatal, !fAidaImplants, "Branch AidaImplantHits not found!");
        }
        else if (fDetectorSystems.at(i) == "BB7")
        {
            fBB7Decays = mgr->InitObjectAs<decltype(fBB7Decays)>("BB7DecayData");
            c4LOG_IF(fatal, !fBB7Decays, "Branch BB7DecayData not found!");
            fBB7Implants = mgr->InitObjectAs<decltype(fBB7Implants)>("BB7ImplantData");
            c4LOG_IF(fatal, !fBB7Implants, "Branch BB7ImplantData not found!");  
        }
        else
        {
            c4LOG(fatal, "Unknown detector system: " << fDetectorSystems.at(i));
        }
    }



    TDirectory::TContext ctx(nullptr);

    dir_whiterabbit = new TDirectory("White Rabbit", "White Rabbit", "", 0);
    mgr->Register("White Rabbit", "White Rabbit Directory", dir_whiterabbit, false); // allow other tasks to access directory.
    histograms->Add(dir_whiterabbit);

    dir_whiterabbit_correlation = dir_whiterabbit->mkdir("Trigger 1 & 3");
    dir_whiterabbit_trigger1 = dir_whiterabbit->mkdir("Trigger 1");
    dir_whiterabbit_trigger3 = dir_whiterabbit->mkdir("Trigger 3");
    dir_whiterabbit_time_differences = dir_whiterabbit->mkdir("Time Differences");

    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_aida_frs = new TH1I("h1_whiterabbit_correlation_aida_frs", "AIDA - FRS WR dT", 1000, -5e4, 5e4);
    h1_whiterabbit_correlation_aida_frs->GetXaxis()->SetTitle("Time difference (AIDA - FRS) [ns]");
    h1_whiterabbit_correlation_aida_frs->GetYaxis()->SetTitle("Counts");

    h1_whiterabbit_correlation_fatima_frs = new TH1I("h1_whiterabbit_correlation_fatima_frs", "FATIMA (TAMEX) - FRS WR dT", 1000, -1000, 1000);
    h1_whiterabbit_correlation_fatima_frs->GetXaxis()->SetTitle("Time difference (FATIMA (TAMEX) - FRS) [ns]");
    h1_whiterabbit_correlation_fatima_frs->GetYaxis()->SetTitle("Counts");

    h1_whiterabbit_correlation_bplast_frs = new TH1I("h1_whiterabbit_correlation_bplast_frs", "bPlast - FRS WR dT", 1000, -1000, 1000);
    h1_whiterabbit_correlation_bplast_frs->GetXaxis()->SetTitle("Time difference (bPlast - FRS) [ns]");
    h1_whiterabbit_correlation_bplast_frs->GetYaxis()->SetTitle("Counts");

    h1_whiterabbit_correlation_germanium_frs = new TH1I("h1_whiterabbit_correlation_germanium_frs", "DEGAS - FRS WR dT", 1000, -1000, 1000);
    h1_whiterabbit_correlation_germanium_frs->GetXaxis()->SetTitle("Time difference (DEGAS - FRS) [ns]");
    h1_whiterabbit_correlation_germanium_frs->GetYaxis()->SetTitle("Counts");

    h1_whiterabbit_correlation_bb7_frs = MakeTH1(dir_whiterabbit_correlation, "I", "h1_whiterabbit_correlation_bb7_frs", "BB7 - FRS WR dT", 1e3, -1e3, 1e3);


    // AIDA 
    // AIDA - Fatima
    
    
    h1_whiterabbit_correlation_aida_fatima = new TH1I("h1_whiterabbit_correlation_aida_fatima", "AIDA - FATIMA (TAMEX) WR dT", 1000, -5e4, 5e4);
    h1_whiterabbit_correlation_aida_fatima->GetXaxis()->SetTitle("Time difference (AIDA - FATIMA) [ns]");
    h1_whiterabbit_correlation_aida_fatima->GetYaxis()->SetTitle("Counts");

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_aida_fatima = new TH1I("h1_whiterabbit_trigger1_aida_fatima", "White Rabbit Trigger 1 AIDA - FATIMA (TAMEX)",1000,-5e4,5e4);
    h1_whiterabbit_trigger1_aida_fatima->GetXaxis()->SetTitle("AIDA - FATIMA (TAMEX) WR dT (ns)");
    h1_whiterabbit_trigger1_aida_fatima->GetYaxis()->SetTitle("Counts (Trigger 1)");



    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_aida_fatima = new TH1I("h1_whiterabbit_trigger3_aida_fatima", "White Rabbit Trigger 3 AIDA - FATIMA (TAMEX)",1000,-5e4,5e4);
    h1_whiterabbit_trigger3_aida_fatima->GetXaxis()->SetTitle("AIDA - FATIMA (TAMEX) WR dT (ns)");
    h1_whiterabbit_trigger3_aida_fatima->GetYaxis()->SetTitle("Counts (Trigger 3)");

    // AIDA - FatimaVme
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_aida_fatimavme = new TH1I("h1_whiterabbit_correlation_aida_fatimavme", "AIDA - FATIMA (VME) WR dT", 1000, -5e4, 5e4);
    h1_whiterabbit_correlation_aida_fatimavme->GetXaxis()->SetTitle("Time difference (AIDA - FATIMA (VME)) [ns]");
    h1_whiterabbit_correlation_aida_fatimavme->GetYaxis()->SetTitle("Counts");

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_aida_fatimavme = new TH1I("h1_whiterabbit_trigger1_aida_fatimavme", "White Rabbit Trigger 1 AIDA - FATIMA (VME)",1000,-5e4,5e4);
    h1_whiterabbit_trigger1_aida_fatimavme->GetXaxis()->SetTitle("AIDA - FATIMA (VME) WR dT (ns)");
    h1_whiterabbit_trigger1_aida_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 1)");


    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_aida_fatimavme = new TH1I("h1_whiterabbit_trigger3_aida_fatimavme", "White Rabbit Trigger 3 AIDA - FATIMA (VME)",1000,-5e4,5e4);
    h1_whiterabbit_trigger3_aida_fatimavme->GetXaxis()->SetTitle("AIDA - FATIMA (VME) WR dT (ns)");
    h1_whiterabbit_trigger3_aida_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 3)");

    // AIDA - bPlast
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_aida_bplast = new TH1I("h1_whiterabbit_correlation_aida_bplast", "AIDA - bPlast WR dT", 1000, -5e4, 5e4);
    h1_whiterabbit_correlation_aida_bplast->GetXaxis()->SetTitle("Time difference (AIDA - bPlast) [ns]");
    h1_whiterabbit_correlation_aida_bplast->GetYaxis()->SetTitle("Counts");

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_aida_bplast = new TH1I("h1_whiterabbit_trigger1_aida_bplast", "White Rabbit Trigger 1 AIDA-bPlast",1000,-5e4,5e4);
    h1_whiterabbit_trigger1_aida_bplast->GetXaxis()->SetTitle("AIDA - bPlast WR dT (ns)");
    h1_whiterabbit_trigger1_aida_bplast->GetYaxis()->SetTitle("Counts (Trigger 1)");


    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_aida_bplast = new TH1I("h1_whiterabbit_trigger3_aida_bplast", "White Rabbit Trigger 3 AIDA-bPlast",1000,-5e4,5e4);
    h1_whiterabbit_trigger3_aida_bplast->GetXaxis()->SetTitle("AIDA - bPlast WR dT (ns)");
    h1_whiterabbit_trigger3_aida_bplast->GetYaxis()->SetTitle("Counts (Trigger 3)");


    // AIDA - Germanium
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_aida_germanium = new TH1I("h1_whiterabbit_correlation_aida_germanium", "AIDA - DEGAS WR dT", 1000, -5e4, 5e4);
    h1_whiterabbit_correlation_aida_germanium->GetXaxis()->SetTitle("Time difference (AIDA - DEGAS) [ns]");
    h1_whiterabbit_correlation_aida_germanium->GetYaxis()->SetTitle("Counts");

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_aida_germanium = new TH1I("h1_whiterabbit_trigger1_aida_germanium", "White Rabbit Trigger 1 AIDA-DEGAS",1000,-5e4,5e4);
    h1_whiterabbit_trigger1_aida_germanium->GetXaxis()->SetTitle("AIDA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_aida_germanium->GetYaxis()->SetTitle("Counts (Trigger 1)");


    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_aida_germanium = new TH1I("h1_whiterabbit_trigger3_aida_germanium", "White Rabbit Trigger 3 AIDA-DEGAS",1000,-5e4,5e4);
    h1_whiterabbit_trigger3_aida_germanium->GetXaxis()->SetTitle("AIDA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_aida_germanium->GetYaxis()->SetTitle("Counts (Trigger 3)");

    
    // FATIMA
    // Fatima - FatimaVme
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_fatima_fatimavme = new TH1I("h1_whiterabbit_correlation_fatima_fatimavme", "FATIMA - FATIMA VME WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatima_fatimavme->GetXaxis()->SetTitle("Time difference (FATIMA - FATIMA VME) [ns]");
    h1_whiterabbit_correlation_fatima_fatimavme->GetYaxis()->SetTitle("Counts");

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_fatima_fatimavme = new TH1I("h1_whiterabbit_trigger1_fatima_fatimavme", "White Rabbit Trigger 1 FATIMA-FATIMA VME", 1e3, -1e3, 1e3);
    h1_whiterabbit_trigger1_fatima_fatimavme->GetXaxis()->SetTitle("FATIMA - FATIMA VME WR dT (ns)");
    h1_whiterabbit_trigger1_fatima_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 1)");

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_fatima_fatimavme = new TH1I("h1_whiterabbit_trigger3_fatima_fatimavme", "White Rabbit Trigger 3 FATIMA-FATIMA VME",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatima_fatimavme->GetXaxis()->SetTitle("FATIMA - FATIMA VME WR dT (ns)");
    h1_whiterabbit_trigger3_fatima_fatimavme->GetYaxis()->SetTitle("Counts (Trigger 3)");

    // Fatima - bPlast
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_fatima_bplast = new TH1I("h1_whiterabbit_correlation_fatima_bplast", "FATIMA (TAMEX) - bPlast WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatima_bplast->GetXaxis()->SetTitle("Time difference (FATIMA (TAMEX) - bPlast) [ns]");
    h1_whiterabbit_correlation_fatima_bplast->GetYaxis()->SetTitle("Counts");

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_fatima_bplast = new TH1I("h1_whiterabbit_trigger1_fatima_bplast", "White Rabbit Trigger 1 FATIMA (TAMEX) - bPlast", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_fatima_bplast->GetXaxis()->SetTitle("FATIMA (TAMEX) - bPlast WR dT (ns)");
    h1_whiterabbit_trigger1_fatima_bplast->GetYaxis()->SetTitle("Counts (Trigger 1)");

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_fatima_bplast = new TH1I("h1_whiterabbit_trigger3_fatima_bplast", "White Rabbit Trigger 3 FATIMA (TAMEX) - bPlast",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatima_bplast->GetXaxis()->SetTitle("FATIMA (TAMEX) - bPlast WR dT (ns)");
    h1_whiterabbit_trigger3_fatima_bplast->GetYaxis()->SetTitle("Counts (Trigger 3)");

    // Fatima - Germanium
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_fatima_ge = new TH1I("h1_whiterabbit_correlation_fatima_ge", "FATIMA - DEGAS WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatima_ge->GetXaxis()->SetTitle("Time difference (FATIMA - DEGAS) [ns]");
    h1_whiterabbit_correlation_fatima_ge->GetYaxis()->SetTitle("Counts");

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_fatima_ge = new TH1I("h1_whiterabbit_trigger1_fatima_ge", "White Rabbit Trigger 1 FATIMA-DEGAS", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_fatima_ge->GetXaxis()->SetTitle("FATIMA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_fatima_ge->GetYaxis()->SetTitle("Counts (Trigger 1)");

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_fatima_ge = new TH1I("h1_whiterabbit_trigger3_fatima_ge", "White Rabbit Trigger 3 FATIMA-DEGAS",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatima_ge->GetXaxis()->SetTitle("FATIMA - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_fatima_ge->GetYaxis()->SetTitle("Counts (Trigger 3)");

    // FatimaVme - bPlast
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_fatimavme_bplast = new TH1I("h1_whiterabbit_correlation_fatimavme_bplast", "FATIMA (VME) - bPlast WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatimavme_bplast->GetXaxis()->SetTitle("Time difference (FATIMA (VME) - bPlast) [ns]");
    h1_whiterabbit_correlation_fatimavme_bplast->GetYaxis()->SetTitle("Counts");

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_fatimavme_bplast = new TH1I("h1_whiterabbit_trigger1_fatimavme_bplast", "White Rabbit Trigger 1 FATIMA (VME) - bPlast", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_fatimavme_bplast->GetXaxis()->SetTitle("FATIMA (VME) - bPlast WR dT (ns)");
    h1_whiterabbit_trigger1_fatimavme_bplast->GetYaxis()->SetTitle("Counts (Trigger 1)");
    h1_whiterabbit_trigger1_fatimavme_bplast->Draw();


    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_fatimavme_bplast = new TH1I("h1_whiterabbit_trigger3_fatimavme_bplast", "White Rabbit Trigger 3 FATIMA (VME) - bPlast",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatimavme_bplast->GetXaxis()->SetTitle("FATIMA (VME) - bPlast WR dT (ns)");
    h1_whiterabbit_trigger3_fatimavme_bplast->GetYaxis()->SetTitle("Counts (Trigger 3)");


    // FatimaVme - Germanium
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_fatimavme_ge = new TH1I("h1_whiterabbit_correlation_fatimavme_ge", "FATIMA VME - DEGAS WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatimavme_ge->GetXaxis()->SetTitle("Time difference (FATIMA VME - DEGAS) [ns]");
    h1_whiterabbit_correlation_fatimavme_ge->GetYaxis()->SetTitle("Counts");

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_fatimavme_ge = new TH1I("h1_whiterabbit_trigger1_fatimavme_ge", "White Rabbit Trigger 1 FATIMA VME-DEGAS", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_fatimavme_ge->GetXaxis()->SetTitle("FATIMA VME - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_fatimavme_ge->GetYaxis()->SetTitle("Counts (Trigger 1)");

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_fatimavme_ge = new TH1I("h1_whiterabbit_trigger3_fatimavme_ge", "White Rabbit Trigger 3 FATIMA VME-DEGAS",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_fatimavme_ge->GetXaxis()->SetTitle("FATIMA VME - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_fatimavme_ge->GetYaxis()->SetTitle("Counts (Trigger 3)");

    // bPlast - Germanium
    dir_whiterabbit_correlation->cd();
    h1_whiterabbit_correlation_bplast_ge = new TH1I("h1_whiterabbit_correlation_bplast_ge", "bPlast - DEGAS WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_bplast_ge->GetXaxis()->SetTitle("Time difference (bPlast - DEGAS) [ns]");
    h1_whiterabbit_correlation_bplast_ge->GetYaxis()->SetTitle("Counts");

    dir_whiterabbit_trigger1->cd();
    h1_whiterabbit_trigger1_bplast_ge = new TH1I("h1_whiterabbit_trigger1_bplast_ge", "White Rabbit Trigger 1 bPlast-DEGAS", 1e3,-1e3,1e3);
    h1_whiterabbit_trigger1_bplast_ge->GetXaxis()->SetTitle("bPlast - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger1_bplast_ge->GetYaxis()->SetTitle("Counts (Trigger 1)");

    dir_whiterabbit_trigger3->cd();
    h1_whiterabbit_trigger3_bplast_ge = new TH1I("h1_whiterabbit_trigger3_bplast_ge", "White Rabbit Trigger 3 bPlast-DEGAS",1e3,-1e3,1e3);
    h1_whiterabbit_trigger3_bplast_ge->GetXaxis()->SetTitle("bPlast - DEGAS WR dT (ns)");
    h1_whiterabbit_trigger3_bplast_ge->GetYaxis()->SetTitle("Counts (Trigger 3)");

    h1_whiterabbit_correlation_bb7_fatima = MakeTH1(dir_whiterabbit_correlation, "I", "h1_whiterabbit_correlation_bb7_fatima", "White Rabbit BB7 - FATIMA (TAMEX)", 1e3, -1e3, 1e3);
    h1_whiterabbit_correlation_bb7_fatimavme = MakeTH1(dir_whiterabbit_correlation, "I", "h1_whiterabbit_correlation_bb7_fatimavme", "White Rabbit BB7 - FATIMA (VME)", 1e3, -1e3, 1e3);
    h1_whiterabbit_correlation_bb7_germanium = MakeTH1(dir_whiterabbit_correlation, "I", "h1_whiterabbit_correlation_bb7_germanium", "White Rabbit BB7 - DEGAS", 1e3, -1e3, 1e3);
    h1_whiterabbit_correlation_bb7_bplast = MakeTH1(dir_whiterabbit_correlation, "I", "h1_whiterabbit_correlation_bb7_bplast", "White Rabbit BB7 - bPlast", 1e3, -1e3, 1e3);


    // Trigger ID
    dir_whiterabbit->cd();
    c_whiterabbit_trigger = new TCanvas("c_whiterabbit_trigger", "White Rabbit Trigger ID", 10, 10, 800, 700);
    c_whiterabbit_trigger->cd();
    h1_whiterabbit_trigger = new TH1I("h1_whiterabbit_trigger", "White Rabbit Trigger ID", 5, 0, 5);
    h1_whiterabbit_trigger->GetXaxis()->SetTitle("Trigger ID");
    h1_whiterabbit_trigger->GetYaxis()->SetTitle("Counts");

    // Canvas addition for 10 detector systems
    dir_whiterabbit_correlation->cd();
    c_whiterabbit_correlation = new TCanvas("c_whiterabbit_correlation", "White Rabbit Correlation", 10, 10, 800, 700);
    c_whiterabbit_correlation->Divide(5, 2);
    c_whiterabbit_correlation->cd(1);
    h1_whiterabbit_correlation_fatima_bplast->Draw();
    c_whiterabbit_correlation->cd(2);
    h1_whiterabbit_correlation_fatima_ge->Draw();
    c_whiterabbit_correlation->cd(3);
    h1_whiterabbit_correlation_bplast_ge->Draw();
    c_whiterabbit_correlation->cd(4);
    h1_whiterabbit_correlation_aida_fatima->Draw();
    c_whiterabbit_correlation->cd(5);
    h1_whiterabbit_correlation_fatimavme_ge->Draw();
    c_whiterabbit_correlation->cd(6);
    h1_whiterabbit_correlation_aida_bplast->Draw();
    c_whiterabbit_correlation->cd(7);
    h1_whiterabbit_correlation_aida_germanium->Draw();
    c_whiterabbit_correlation->cd(8);
    h1_whiterabbit_correlation_fatima_fatimavme->Draw();
    c_whiterabbit_correlation->cd(9);
    h1_whiterabbit_correlation_aida_fatimavme->Draw();
    c_whiterabbit_correlation->cd(10);
    h1_whiterabbit_correlation_fatimavme_bplast->Draw();
    c_whiterabbit_correlation->cd(0);
    dir_whiterabbit_correlation->Append(c_whiterabbit_correlation);

    dir_whiterabbit_trigger1->cd();
    c_whiterabbit_trigger1 = new TCanvas("c_whiterabbit_trigger1", "White Rabbit Trigger 1", 10, 10, 800, 700);
    c_whiterabbit_trigger1->Divide(5, 2);
    c_whiterabbit_trigger1->cd(1);
    h1_whiterabbit_trigger1_fatima_bplast->Draw();
    c_whiterabbit_trigger1->cd(2);
    h1_whiterabbit_trigger1_fatima_ge->Draw();
    c_whiterabbit_trigger1->cd(3);
    h1_whiterabbit_trigger1_bplast_ge->Draw();
    c_whiterabbit_trigger1->cd(4);
    h1_whiterabbit_trigger1_aida_fatima->Draw();
    c_whiterabbit_trigger1->cd(5);
    h1_whiterabbit_trigger1_fatimavme_ge->Draw();
    c_whiterabbit_trigger1->cd(6);
    h1_whiterabbit_trigger1_aida_bplast->Draw();
    c_whiterabbit_trigger1->cd(7);
    h1_whiterabbit_trigger1_aida_germanium->Draw();
    c_whiterabbit_trigger1->cd(8);
    h1_whiterabbit_trigger1_fatima_fatimavme->Draw();
    c_whiterabbit_trigger1->cd(9);
    h1_whiterabbit_trigger1_aida_fatimavme->Draw();
    c_whiterabbit_trigger1->cd(10);
    h1_whiterabbit_trigger1_fatimavme_bplast->Draw();
    c_whiterabbit_trigger1->cd(0);
    dir_whiterabbit_trigger1->Append(c_whiterabbit_trigger1);

    dir_whiterabbit_trigger3->cd();
    c_whiterabbit_trigger3 = new TCanvas("c_whiterabbit_trigger3", "White Rabbit Trigger 3", 10, 10, 800, 700);
    c_whiterabbit_trigger3->Divide(5, 2);
    c_whiterabbit_trigger3->cd(1);
    h1_whiterabbit_trigger3_fatima_bplast->Draw();
    c_whiterabbit_trigger3->cd(2);
    h1_whiterabbit_trigger3_fatima_ge->Draw();
    c_whiterabbit_trigger3->cd(3);
    h1_whiterabbit_trigger3_bplast_ge->Draw();
    c_whiterabbit_trigger3->cd(4);
    h1_whiterabbit_trigger3_aida_fatima->Draw();
    c_whiterabbit_trigger3->cd(5);
    h1_whiterabbit_trigger3_fatimavme_ge->Draw();
    c_whiterabbit_trigger3->cd(6);
    h1_whiterabbit_trigger3_aida_bplast->Draw();
    c_whiterabbit_trigger3->cd(7);
    h1_whiterabbit_trigger3_aida_germanium->Draw();
    c_whiterabbit_trigger3->cd(8);
    h1_whiterabbit_trigger3_fatima_fatimavme->Draw();
    c_whiterabbit_trigger3->cd(9);
    h1_whiterabbit_trigger3_aida_fatimavme->Draw();
    c_whiterabbit_trigger3->cd(10);
    h1_whiterabbit_trigger3_fatimavme_bplast->Draw();
    c_whiterabbit_trigger3->cd(0);
    dir_whiterabbit_trigger3->Append(c_whiterabbit_trigger3);


    dir_whiterabbit_time_differences->cd();
    h1_whiterabbit_dt_germanium = new TH1I("h1_whiterabbit_dt_germanium", "Time between success WR hits in Germanium", 1000, 0, 500000);
    h1_whiterabbit_dt_bplast = new TH1I("h1_whiterabbit_dt_bplast", "Time between success WR hits in bPlast", 1000, 0, 500000);
    h1_whiterabbit_dt_fatima = new TH1I("h1_whiterabbit_dt_fatima", "Time between success WR hits in FATIMA", 1000, 0, 500000);
    h1_whiterabbit_dt_fatimavme = new TH1I("h1_whiterabbit_dt_fatimavme", "Time between success WR hits in FATIMA VME", 1000, 0, 500000);


    dir_whiterabbit->cd();

    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_Whiterabbit_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Whiterabbit_Hist", Form("/Objects/%s/->Snapshot_Histo()", GetName()));
    
    return kSUCCESS;
}

// work in progress
void WhiterabbitCorrelationOnline::Reset_Histo()
{
    c4LOG(info, "I'm late, I'm late, for a very important date! No time to say 'Hello, Good Bye' I'm late, I'm late, I'm late!");
    h1_whiterabbit_correlation_fatima_bplast->Reset();
    h1_whiterabbit_trigger1_fatima_bplast->Reset();
    h1_whiterabbit_trigger3_fatima_bplast->Reset();

    h1_whiterabbit_correlation_fatima_ge->Reset();
    h1_whiterabbit_trigger1_fatima_ge->Reset();
    h1_whiterabbit_trigger3_fatima_ge->Reset();

    h1_whiterabbit_correlation_bplast_ge->Reset();
    h1_whiterabbit_trigger1_bplast_ge->Reset();
    h1_whiterabbit_trigger3_bplast_ge->Reset();

    h1_whiterabbit_correlation_aida_fatima->Reset();
    h1_whiterabbit_trigger1_aida_fatima->Reset();
    h1_whiterabbit_trigger3_aida_fatima->Reset();

    h1_whiterabbit_correlation_aida_fatimavme->Reset();
    h1_whiterabbit_trigger1_aida_fatimavme->Reset();
    h1_whiterabbit_trigger3_aida_fatimavme->Reset();

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

    h1_whiterabbit_correlation_fatimavme_bplast->Reset();
    h1_whiterabbit_trigger1_fatimavme_bplast->Reset();
    h1_whiterabbit_trigger3_fatimavme_bplast->Reset();

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

    c_whiterabbit_correlation_fatima_bplast->SaveAs("c_whiterabbit_correlation_fatima_bplast.png");
    c_whiterabbit_trigger1_fatima_bplast->SaveAs("c_whiterabbit_trigger1_fatima_bplast.png");
    c_whiterabbit_trigger3_fatima_bplast->SaveAs("c_whiterabbit_trigger3_fatima_bplast.png");

    c_whiterabbit_correlation_fatima_ge->SaveAs("c_whiterabbit_correlation_fatima_ge.png");
    c_whiterabbit_trigger1_fatima_ge->SaveAs("c_whiterabbit_trigger1_fatima_ge.png");
    c_whiterabbit_trigger3_fatima_ge->SaveAs("c_whiterabbit_trigger3_fatima_ge.png");

    c_whiterabbit_correlation_aida_fatima->SaveAs("c_whiterabbit_correlation_aida_fatima.png");
    c_whiterabbit_trigger1_aida_fatima->SaveAs("c_whiterabbit_trigger1_aida_fatima.png");
    c_whiterabbit_trigger3_aida_fatima->SaveAs("c_whiterabbit_trigger3_aida_fatima.png");

    c_whiterabbit_correlation_bplast_ge->SaveAs("c_whiterabbit_correlation_bplast_ge.png");
    c_whiterabbit_trigger1_bplast_ge->SaveAs("c_whiterabbit_trigger1_bplast_ge.png");
    c_whiterabbit_trigger3_bplast_ge->SaveAs("c_whiterabbit_trigger3_bplast_ge.png");

    c_whiterabbit_correlation_aida_fatimavme->SaveAs("c_whiterabbit_correlation_aida_fatimavme.png");
    c_whiterabbit_trigger1_aida_fatimavme->SaveAs("c_whiterabbit_trigger1_aida_fatimavme.png");
    c_whiterabbit_trigger3_aida_fatimavme->SaveAs("c_whiterabbit_trigger3_aida_fatimavme.png");

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

    c_whiterabbit_correlation_fatima_bplast->SaveAs("c_whiterabbit_correlation_fatimavme_bplast.png");
    c_whiterabbit_trigger1_fatimavme_bplast->SaveAs("c_whiterabbit_trigger1_fatimavme_bplast.png");
    c_whiterabbit_trigger3_fatima_bplast->SaveAs("c_whiterabbit_trigger3_fatima_bplast.png");

    c_whiterabbit_correlation->SaveAs("c_whiterabbit_correlation.png");
    c_whiterabbit_trigger1->SaveAs("c_whiterabbit_trigger1.png");
    c_whiterabbit_trigger3->SaveAs("c_whiterabbit_trigger3.png");

    c_whiterabbit_trigger->SaveAs("c_whiterabbit_trigger.png");

    // snapshot .root file with data and time

    file_whiterabbit_snapshot = new TFile(Form("whiterabbit_snapshot_%d_%d_%d_%d_%d_%d.root", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec), "RECREATE");
    file_whiterabbit_snapshot->cd();
    dir_whiterabbit->Write();
    file_whiterabbit_snapshot->Close();
    delete file_whiterabbit_snapshot;

    gSystem->cd("..");
    c4LOG(info, "Snapshot saved in:" << snapshot_dir);    
}


void WhiterabbitCorrelationOnline::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();

    Int_t nHitsFatimaVme = 0;
    Int_t nHitsFatima = 0;
    Int_t nHitsbPlast = 0;
    Int_t nHitsGe = 0;
    Int_t nHitsAida = 0;
    Int_t nHitsAidaImplants = 0;
    Int_t nHitsFrs = 0;
    Int_t nHitsBB7 = 0;
    Int_t nHitsBB7Implants = 0;
    Int_t systems = 0;
    
    if (fHitFatimaTwinpeaks)
    {
        nHitsFatima = fHitFatimaTwinpeaks->GetEntriesFast();
        if (nHitsFatima > 0) 
        {
            systems += 1;
        
            FatimaTwinpeaksCalData* FatimaHit = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(0);
            int64_t wr_fatima = FatimaHit->Get_wr_t();
            if (last_wr_fatima != wr_fatima) 
            {
                h1_whiterabbit_dt_fatima->Fill(wr_fatima - last_wr_fatima);
                last_wr_fatima = wr_fatima;
            }
        }
    }

    if (fHitbPlastTwinpeaks) 
    {
        nHitsbPlast = fHitbPlastTwinpeaks->GetEntriesFast();
        if (nHitsbPlast > 0) 
        {
            systems += 1;

            bPlastTwinpeaksCalData* bPlastHit = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
            int64_t wr_bplast = bPlastHit->Get_wr_t();
            if (last_wr_bplast != wr_bplast) 
            {
                h1_whiterabbit_dt_bplast->Fill(wr_bplast - last_wr_bplast);
                last_wr_bplast = wr_bplast;
            }
        }
    }

    if (fHitGe) 
    {
        nHitsGe = fHitGe->GetEntriesFast();
        if (nHitsGe > 0) 
        {
            systems += 1;
            
            GermaniumCalData* GermaniumHit = (GermaniumCalData*)fHitGe->At(0);
            int64_t wr_germanium = GermaniumHit->Get_wr_t();
            if (last_wr_germanium != wr_germanium) 
            {
                h1_whiterabbit_dt_germanium->Fill(wr_germanium - last_wr_germanium);
                last_wr_germanium = wr_germanium;
            }
            
        }
    }

    if (fatVmeArray->size() > 0) 
    {
        auto const & hitFatVme = fatVmeArray->at(0);
        systems += 1;

        int64_t wr_fatimavme = hitFatVme.Get_wr_t();
        if (last_wr_fatimavme != wr_fatimavme) 
        {
            h1_whiterabbit_dt_fatimavme->Fill(wr_fatimavme - last_wr_fatimavme);
            last_wr_fatimavme = wr_fatimavme;
        }
    }
    
    if (fAidaDecays || fAidaImplants)
    {
        nHitsAida = fAidaDecays->size();
        nHitsAidaImplants = fAidaImplants->size();
        if (nHitsAida > 0 || nHitsAidaImplants > 0) systems++;
    }

    if (fBB7Decays || fBB7Implants)
    {
        nHitsBB7 = fBB7Decays->size();
        nHitsBB7Implants = fBB7Implants->size();
        if (nHitsBB7 > 0 || nHitsBB7Implants > 0) systems++;
    }

    if (hitArrayFrs)
    {
        nHitsFrs = hitArrayFrs->size();
        if (nHitsFrs > 0) systems++;
    }
    
    if (nHitsFrs > 0 && nHitsAidaImplants > 0) frs_and_aida++;

    int aidaImplantCounter = 0;
    for (auto & fa : *fAidaImplants)
    {
        if (aidaImplantCounter > 0) break;

        AidaHit aidaHit = fa;
        if (hitArrayFrs && hitArrayFrs->size() > 0)
        {
            auto const & hitFrs = hitArrayFrs->at(0);
            int64_t wr_frs = hitFrs.Get_wr_t();
            int64_t wr_aida = aidaHit.Time;
            int64_t dt = wr_aida - wr_frs;
            h1_whiterabbit_correlation_aida_frs->Fill(dt);
        }

        //aidaImplantCounter++;
    }

    // start with aida...
    int aidaCounter = 0;
    int64_t wr_aida = 0;
    for (auto & i : *fAidaDecays)
    {
        if (aidaCounter > 0) break;

        AidaHit decayAida = i;
        wr_aida = decayAida.Time;
        
        
        if (fHitFatimaTwinpeaks)
        {
            FatimaTwinpeaksCalData* hitFatima = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(0);
            if (hitFatima)
            {
                int64_t wr_fatima = hitFatima->Get_wr_t();
                int64_t dt = wr_aida - wr_fatima;
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
        }
        
        if (fatVmeArray->size() > 0)
        {
            auto const & hitFatimaVme = fatVmeArray->at(0);

            int64_t wr_fatimavme = hitFatimaVme.Get_wr_t();
            int64_t dt = wr_aida - wr_fatimavme;
            h1_whiterabbit_correlation_aida_fatimavme->Fill(dt);
            if (fEventHeader->GetTrigger() == 1)
            {
                h1_whiterabbit_trigger1_aida_fatimavme->Fill(dt);
            }
            if (fEventHeader->GetTrigger() == 3)
            {
                h1_whiterabbit_trigger3_aida_fatimavme->Fill(dt);
            }
            
        }
        
        if (fHitbPlastTwinpeaks)
        {
            bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
            if (hitbPlast)
            {
                int64_t wr_bplast = hitbPlast->Get_wr_t();
                int64_t dt = wr_aida - wr_bplast;
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
        }
        
        if (fHitGe)
        {
            GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(0);
            if (hitGe)
            {
                int64_t wr_ge = hitGe->Get_wr_t();
                int64_t dt = wr_aida - wr_ge;
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
        }
        
        aidaCounter++;
    }
    
    
    if (fHitFatimaTwinpeaks)
    {
        FatimaTwinpeaksCalData* hitFatima = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(0);

        if (hitFatima)
        {
            int64_t wr_fatima = hitFatima->Get_wr_t();
            
            if (hitArrayFrs && hitArrayFrs->size() > 0)
            {
                auto const & hitFrs = hitArrayFrs->at(0);
                int64_t wr_frs = hitFrs.Get_wr_t();
                int64_t dt = wr_fatima - wr_frs;
                h1_whiterabbit_correlation_fatima_frs->Fill(dt);
            }

            if (fatVmeArray->size() > 0) 
            {
                auto const & hitFatVme = fatVmeArray->at(0);
                
                int64_t wr_fatima_vme = hitFatVme.Get_wr_t();
                int64_t dt = wr_fatima - wr_fatima_vme;
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
            
            if (fHitbPlastTwinpeaks) 
            {
                bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
                
                if (hitbPlast)
                {
                    int64_t wr_bplast = hitbPlast->Get_wr_t();
                    int64_t dt = wr_fatima - wr_bplast;
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
                    int64_t wr_ge = hitGe->Get_wr_t();
                    int64_t dt = wr_fatima - wr_ge;
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
    
    if (fatVmeArray && fatVmeArray->size() > 0)
    {
        auto const & hitFatVme = fatVmeArray->at(0);
        
        int64_t wr_fatimavme = hitFatVme.Get_wr_t();

        if (fHitbPlastTwinpeaks) 
        {
            bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
            if (hitbPlast)
            {
                int64_t wr_bplast = hitbPlast->Get_wr_t();
                int64_t dt = wr_fatimavme - wr_bplast;
                h1_whiterabbit_correlation_fatimavme_bplast->Fill(dt);
                if (fEventHeader->GetTrigger() == 1)
                {
                    h1_whiterabbit_trigger1_fatimavme_bplast->Fill(dt);
                }
                if (fEventHeader->GetTrigger() == 3)
                {
                    h1_whiterabbit_trigger3_fatimavme_bplast->Fill(dt);
                }
            }
        }

        if (fHitGe) 
        {
            GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(0);
            if (hitGe)
            {
                int64_t wr_ge = hitGe->Get_wr_t();
                int64_t dt = wr_fatimavme - wr_ge;
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
            int64_t wr_bplast = hitbPlast->Get_wr_t();

            if (hitArrayFrs && hitArrayFrs->size() > 0)
            {
                auto const & hitFrs = hitArrayFrs->at(0);
                int64_t wr_frs = hitFrs.Get_wr_t();
                int64_t dt = wr_bplast - wr_frs;
                h1_whiterabbit_correlation_bplast_frs->Fill(dt);
            }

            if (fHitGe)
            {
                GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(0);
                if (hitGe)
                {
                    int64_t wr_ge = hitGe->Get_wr_t();
                    int64_t dt = wr_bplast - wr_ge;
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

    if (fHitGe)
    {
        GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(0);
        if (hitGe)
        {
            int64_t wr_ge = hitGe->Get_wr_t();
            if (hitArrayFrs && hitArrayFrs->size() > 0)
            {
                auto const & hitFrs = hitArrayFrs->at(0);
                int64_t wr_frs = hitFrs.Get_wr_t();
                int64_t dt = wr_ge - wr_frs;
                h1_whiterabbit_correlation_germanium_frs->Fill(dt);
            }
        }
    }

    int bb7_decay_count = 0;
    if (fBB7Decays && fBB7Decays->size())
    {   
        auto const & decayBB7 = fBB7Decays->at(0);
        int64_t wr_bb7 = decayBB7.Get_wr_t();

        // bb7-frs
        if (hitArrayFrs && hitArrayFrs->size() > 0)
        {
            auto const & hitFrs = hitArrayFrs->at(0);
            int64_t wr_frs = hitFrs.Get_wr_t();
            int64_t dt = wr_bb7 - wr_frs;
            h1_whiterabbit_correlation_bb7_frs->Fill(dt);
        }

        // bb7-fatima tamex
        if (fHitFatimaTwinpeaks)
        {
            FatimaTwinpeaksCalData* hitFatima = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(0);
            if (hitFatima)
            {
                int64_t wr_fatima = hitFatima->Get_wr_t();
                int64_t dt = wr_bb7 - wr_fatima;
                h1_whiterabbit_correlation_bb7_fatima->Fill(dt);
                
            }
        }

        // bb7-fatimavme
        if (fatVmeArray->size() > 0) 
        {
            auto const & hitFatVme = fatVmeArray->at(0);
            
            int64_t wr_fatima_vme = hitFatVme.Get_wr_t();
            int64_t dt = wr_bb7 - wr_fatima_vme;
            h1_whiterabbit_correlation_bb7_fatimavme->Fill(dt); 
        }

        // bb7-bplast
        if (fHitbPlastTwinpeaks) 
        {
            bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(0);
            if (hitbPlast)
            {
                int64_t wr_bplast = hitbPlast->Get_wr_t();
                int64_t dt = wr_bb7 - wr_bplast;
                h1_whiterabbit_correlation_bb7_bplast->Fill(dt);
            }
        }

        // bb7-germanium
        if (fHitGe) 
        {
            GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(0);
            if (hitGe)
            {
                int64_t wr_ge = hitGe->Get_wr_t();
                int64_t dt = wr_bb7 - wr_ge;
                h1_whiterabbit_correlation_bb7_germanium->Fill(dt);
            }
        }
    }

    h1_whiterabbit_trigger->Fill(fEventHeader->GetTrigger());

    fNEvents += 1;

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
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
}

void WhiterabbitCorrelationOnline::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events found, no histograms written.");
        return;
    }
   
    c4LOG(info, "Processed " << fNEvents << " events.");
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents);

   
    c4LOG(info, "Processed " << fNEvents << " events.");
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fNEvents);

}

ClassImp(WhiterabbitCorrelationOnline)
