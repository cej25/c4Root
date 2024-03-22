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
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"

WhiterabbitCorrelationOnline::WhiterabbitCorrelationOnline() : WhiterabbitCorrelationOnline("WhiterabbitCorrelationOnline")
{
}

WhiterabbitCorrelationOnline::WhiterabbitCorrelationOnline(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatimaTwinpeaks(NULL)
    , fHitbPlastTwinpeaks(NULL)
    , fHitGe(NULL)
    , fAidaDecays(new std::vector<AidaHit>)
    , fNEvents(0)
    , header(nullptr)
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

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

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

    folder_whiterabbit = new TFolder("Whiterabbit Subsystem Correlation", "Whiterabbit Subsystem Correlation");

    run->AddObject(folder_whiterabbit);
    
    // AIDA 
    // AIDA - Fatima
    c_whiterabbit_correlation_fatima_aida = new TCanvas("c_whiterabbit_correlation_fatima_aida", "AIDA - FATIMA WR dT", 10, 10, 800, 700);
    c_whiterabbit_correlation_fatima_aida->cd();
    h1_whiterabbit_correlation_fatima_aida = new TH1I("h1_whiterabbit_correlation_fatima_aida", "AIDA - FATIMA WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_fatima_aida->GetXaxis()->SetTitle("Time difference(AIDA - FATIMA) [ns]");
    h1_whiterabbit_correlation_fatima_aida->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatima_aida->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_fatima_aida);
    c_whiterabbit_correlation_fatima_aida->cd(0);
    // AIDA - FatimaVme
    c_whiterabbit_correlation_fatimavme_aida = new TCanvas("c_whiterabbit_correlation_fatimavme_aida", "AIDA - FATIMA VME WR dT", 10, 10, 800, 700);
    c_whiterabbit_correlation_fatimavme_aida->cd();
    h1_whiterabbit_correlation_fatimavme_aida = new TH1I("h1_whiterabbit_correlation_fatimavme_aida", "AIDA - FATIMAVME WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_fatimavme_aida->GetXaxis()->SetTitle("Time difference (AIDA - FATIMA VME) [ns]");
    h1_whiterabbit_correlation_fatimavme_aida->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatimavme_aida->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_fatimavme_aida);
    c_whiterabbit_correlation_fatimavme_aida->cd(0);
    // AIDA - bPlast
    c_whiterabbit_correlation_aida_bplast = new TCanvas("c_whiterabbit_correlation_aida_bplast", "AIDA - bPlast WR dT", 10, 10, 800, 700);
    c_whiterabbit_correlation_aida_bplast->cd();
    h1_whiterabbit_correlation_aida_bplast = new TH1I("h1_whiterabbit_correlation_aida_bplast", "AIDA - bPlast WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_aida_bplast->GetXaxis()->SetTitle("Time difference (AIDA - bPlast) [ns]");
    h1_whiterabbit_correlation_aida_bplast->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_aida_bplast->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_aida_bplast);
    c_whiterabbit_correlation_aida_bplast->cd(0);
    // AIDA - Germanium
    c_whiterabbit_correlation_aida_germanium = new TCanvas("c_whiterabbit_correlation_aida_germanium", "AIDA - DEGAS WR dT", 10, 10, 800, 700);
    c_whiterabbit_correlation_aida_germanium->cd();
    h1_whiterabbit_correlation_aida_germanium = new TH1I("h1_whiterabbit_correlation_aida_germanium", "AIDA - DEGAS WR dT", 1000, -1e3, 5e4);
    h1_whiterabbit_correlation_aida_germanium->GetXaxis()->SetTitle("Time difference (AIDA - DEGAS) [ns]");
    h1_whiterabbit_correlation_aida_germanium->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_aida_germanium->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_aida_germanium);
    c_whiterabbit_correlation_aida_germanium->cd(0);
    
    // FATIMA
    // Fatima - FatimaVme
    c_whiterabbit_correlation_fatima_fatimavme = new TCanvas("c_whiterabbit_correlation_fatima_fatimavme", "FATIMA - FATIMA VME WR dT", 10, 10, 800, 700);
    c_whiterabbit_correlation_fatima_fatimavme->cd();
    h1_whiterabbit_correlation_fatima_fatimavme = new TH1I("h1_whiterabbit_correlation_fatima_fatimavme", "FATIMA - FATIMA VME WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_fatima_fatimavme->GetXaxis()->SetTitle("Time difference (FATIMA - FATIMA VME) [ns]");
    h1_whiterabbit_correlation_fatima_fatimavme->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatima_fatimavme->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_fatima_fatimavme);
    c_whiterabbit_correlation_fatima_fatimavme->cd(0);
    // Fatima - bPlast
    c_whiterabbit_correlation_bplast_fatima = new TCanvas("c_whiterabbit_correlation_bplast_fatima", "bPlast - FATIMA WR dT", 10, 10, 800, 700);
    c_whiterabbit_correlation_bplast_fatima->cd();
    h1_whiterabbit_correlation_bplast_fatima = new TH1I("h1_whiterabbit_correlation_bplast_fatima", "bPlast - FATIMA WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_bplast_fatima->GetXaxis()->SetTitle("Time difference (bPlast - FATIMA) [ns]");
    h1_whiterabbit_correlation_bplast_fatima->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_bplast_fatima->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_bplast_fatima);
    c_whiterabbit_correlation_bplast_fatima->cd(0);
    // Fatima - Germanium
    c_whiterabbit_correlation_fatima_ge = new TCanvas("c_whiterabbit_correlation_fatima_ge", "FATIMA - DEGAS WR dT", 10, 10, 800, 700);
    c_whiterabbit_correlation_fatima_ge->cd();
    h1_whiterabbit_correlation_fatima_ge = new TH1I("h1_whiterabbit_correlation_fatima_ge", "FATIMA - DEGAS WR dT", 1000, -1e3, 1e5);
    h1_whiterabbit_correlation_fatima_ge->GetXaxis()->SetTitle("Time difference (FATIMA - DEGAS) [ns]");
    h1_whiterabbit_correlation_fatima_ge->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatima_ge->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_fatima_ge);
    c_whiterabbit_correlation_fatima_ge->cd(0);
    
    // FatimaVme
    // FatimaVme - bPlast
    c_whiterabbit_correlation_bplast_fatimavme = new TCanvas("c_whiterabbit_correlation_bplast_fatimavme", "bPlast - FATIMA VME WR dT", 10, 10, 800, 700);
    c_whiterabbit_correlation_bplast_fatimavme->cd();
    h1_whiterabbit_correlation_bplast_fatimavme = new TH1I("h1_whiterabbit_correlation_bplast_fatimavme", "bPlast - FATIMA VME WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_bplast_fatimavme->GetXaxis()->SetTitle("Time difference (bPlast - FATIMA VME) [ns]");
    h1_whiterabbit_correlation_bplast_fatimavme->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_bplast_fatimavme->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_bplast_fatimavme);
    c_whiterabbit_correlation_bplast_fatimavme->cd(0);
    // FatimaVme - Germanium
    c_whiterabbit_correlation_fatimavme_ge = new TCanvas("c_whiterabbit_correlation_fatimavme_ge", "FATIMA VME - DEGAS WR dT", 10, 10, 800, 700);
    c_whiterabbit_correlation_fatimavme_ge->cd();
    h1_whiterabbit_correlation_fatimavme_ge = new TH1I("h1_whiterabbit_correlation_fatimavme_ge", "FATIMA VME - DEGAS WR dT", 1000, -1e3, 1e5);
    h1_whiterabbit_correlation_fatimavme_ge->GetXaxis()->SetTitle("Time difference (FATIMA VME - DEGAS) [ns]");
    h1_whiterabbit_correlation_fatimavme_ge->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatimavme_ge->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_fatimavme_ge);
    c_whiterabbit_correlation_fatimavme_ge->cd(0);

    // bPlast
    // bPlast - Germanium
    c_whiterabbit_correlation_bplast_ge = new TCanvas("c_whiterabbit_correlation_bplast_ge", "bPlast - DEGAS WR dT", 10, 10, 800, 700);
    c_whiterabbit_correlation_bplast_ge->cd();
    h1_whiterabbit_correlation_bplast_ge = new TH1I("h1_whiterabbit_correlation_bplast_ge", "bPlast - DEGAS WR dT", 1000, -1e3, 1e3);
    h1_whiterabbit_correlation_bplast_ge->GetXaxis()->SetTitle("Time difference (bPlast - DEGAS) [ns]");
    h1_whiterabbit_correlation_bplast_ge->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_bplast_ge->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_bplast_ge);
    c_whiterabbit_correlation_bplast_ge->cd(0);



    run->GetHttpServer()->RegisterCommand("Reset_Whiterabbit_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Whiterabbit_Hist", Form("/Objects/%s/->Snapshot_Histo()", GetName()));

    return kSUCCESS;
    
}

// work in progress
void WhiterabbitCorrelationOnline::Reset_Histo()
{
    c4LOG(info, "I'm late, I'm late, for a very important date! No time to say 'Hello, Good Bye' I'm late, I'm late, I'm late!");
    h1_whiterabbit_correlation_bplast_fatima->Reset();
    h1_whiterabbit_correlation_fatima_ge->Reset();
    h1_whiterabbit_correlation_bplast_ge->Reset();
    h1_whiterabbit_correlation_fatima_aida->Reset();
}

void WhiterabbitCorrelationOnline::Snapshot_Histo()
{
    c4LOG(info, "Good heavens, would you look at the time!");

    //date and time stamp
    time_t now = time(0);
    tm *ltm = localtime(&now);

    const char* snapshot_dir = Form("Whiterabbit_correlation_%d_%d_%d_%d_%d_%d.png", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    c_whiterabbit_correlation_bplast_fatima->SaveAs("c_whiterabbit_correlation_bplast_fatima.png");
    c_whiterabbit_correlation_fatima_ge->SaveAs("c_whiterabbit_correlation_fatima_ge.png");
    c_whiterabbit_correlation_bplast_ge->SaveAs("c_whiterabbit_correlation_bplast_ge.png");
    c_whiterabbit_correlation_fatima_aida->SaveAs("c_whiterabbit_correlation_fatima_aida.png");

    gSystem->cd("..");

    // snapshot .root file with data and time

    file_whiterabbit_snapshot = new TFile(Form("Whiterabbit_correlation_%d_%d_%d_%d_%d_%d.root", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec), "RECREATE");
    file_whiterabbit_snapshot->cd();
    h1_whiterabbit_correlation_bplast_fatima->Write();
    h1_whiterabbit_correlation_fatima_ge->Write();
    h1_whiterabbit_correlation_bplast_ge->Write();
    h1_whiterabbit_correlation_fatima_aida->Write();
    file_whiterabbit_snapshot->Close();
    delete file_whiterabbit_snapshot;

    gSystem->cd("..");
    c4LOG(info, "Snapshot saved in:" << snapshot_dir);    
}



void WhiterabbitCorrelationOnline::Exec(Option_t* option)
{   
    //JB: there is probably a better way to code this. JEL or Nic hilfe bitte!

    // loop over each detector system
    Int_t nHitsFatima = 0;
    Int_t nHitsFatimaVme = 0;
    Int_t nHitsbPlast = 0;
    Int_t nHitsGe = 0;
    Int_t nHitsAida = 0;

    if (fHitFatimaTwinpeaks) nHitsFatima = fHitFatimaTwinpeaks->GetEntriesFast();

    if (fHitbPlastTwinpeaks) nHitsbPlast = fHitbPlastTwinpeaks->GetEntriesFast();

    if (fHitGe) nHitsGe = fHitGe->GetEntriesFast();

    if (fHitFatimaVme) nHitsFatimaVme = fHitFatimaVme->GetEntriesFast();
    
    //if (fAidaDecays) nHitsAida = fAidaDecays->GetEntries();


    // start with aida...
    for (auto & i : *fAidaDecays)
    {
        AidaHit hitAida = i;

        // aida-fatima
        for (Int_t ihit = 0; ihit < nHitsFatima; ihit++)
        {
            FatimaTwinpeaksCalData* hitFatima = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit);

            int dt = hitAida.Time - hitFatima->Get_wr_t();
            h1_whiterabbit_correlation_fatima_aida->Fill(dt);

        }
        
        // aida-fatima vme
        for (Int_t ihit = 0; ihit < nHitsFatimaVme; ihit++)
        {
            FatimaVmeCalData* hitFatimaVme = (FatimaVmeCalData*)fHitFatimaVme->At(ihit);
            
            int dt = hitAida.Time - hitFatimaVme->Get_wr_t();
            h1_whiterabbit_correlation_fatimavme_aida->Fill(dt);
        }

        // aida-bplast
        for (Int_t jhit = 0; jhit < nHitsbPlast; jhit++)
        {
            bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(jhit);
            if (!hitbPlast) continue;

            int dt = hitAida.Time - hitbPlast->Get_wr_t();
            h1_whiterabbit_correlation_aida_bplast->Fill(dt);
        }
        
        // aida-ge
        for (Int_t jhit = 0; jhit < nHitsGe; jhit++)
        {
            GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(jhit);
            if (!hitGe) continue;

            int dt = hitAida.Time - hitGe->Get_wr_t();
            h1_whiterabbit_correlation_aida_germanium->Fill(dt);
        }
        
    }

    for (Int_t ihit = 0; ihit < nHitsFatima; ihit++)
    {
        FatimaTwinpeaksCalData* hitFatima = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(ihit);
        if (!hitFatima) continue;

        // fatima-fatima vme
        for (Int_t jhit = 0; jhit < nHitsFatimaVme; jhit++)
        {
            FatimaVmeCalData* hitFatimaVme = (FatimaVmeCalData*)fHitFatimaVme->At(jhit);
            if (!hitFatimaVme) continue;

            int dt = hitFatima->Get_wr_t() - hitFatimaVme->Get_wr_t();
            h1_whiterabbit_correlation_fatima_fatimavme->Fill(dt);
        }
        
        // fatima-bplast
        for (Int_t jhit = 0; jhit < nHitsbPlast; jhit++)
        {
            bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(jhit);
            if (!hitbPlast) continue;

            int dt = hitFatima->Get_wr_t() - hitbPlast->Get_wr_t();
            h1_whiterabbit_correlation_bplast_fatima->Fill(dt);
        }
        
        // fatima-ge
        for (Int_t jhit = 0; jhit < nHitsGe; jhit++)
        {
            GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(jhit);
            if (!hitGe) continue;

            int dt = hitFatima->Get_wr_t() - hitGe->Get_wr_t();
            h1_whiterabbit_correlation_fatima_ge->Fill(dt);
        }
    }
    

    // fatima vme-bplast,ge 
    for (Int_t ihit = 0; ihit < nHitsFatimaVme; ihit++)
    {
        FatimaVmeCalData* hitFatimaVme = (FatimaVmeCalData*)fHitFatimaVme->At(ihit);
        if (!hitFatimaVme) continue;

        for (Int_t jhit = 0; jhit < nHitsbPlast; jhit++)
        {
            bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(jhit);
            if (!hitbPlast) continue;

            int dt = hitFatimaVme->Get_wr_t() - hitbPlast->Get_wr_t();
            h1_whiterabbit_correlation_bplast_fatimavme->Fill(dt);
        }
        
        for (Int_t jhit = 0; jhit < nHitsGe; jhit++)
        {
            GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(jhit);
            if (!hitGe) continue;

            int dt = hitFatimaVme->Get_wr_t() - hitGe->Get_wr_t();
            h1_whiterabbit_correlation_fatimavme_ge->Fill(dt);
        }
        
    }

    for (Int_t ihit = 0; ihit < nHitsbPlast; ihit++)
    {
        bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(ihit);
        if (!hitbPlast) continue;

        for (Int_t jhit = 0; jhit < nHitsGe; jhit++)
        {
            GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(jhit);
            if (!hitGe) continue;
            
            int dt = hitbPlast->Get_wr_t() - hitGe->Get_wr_t();
            h1_whiterabbit_correlation_bplast_ge->Fill(dt);
        }
    }
    

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
}

void WhiterabbitCorrelationOnline::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events found, no histograms written.");
        return;
    }
    if (fHitFatimaTwinpeaks || fHitbPlastTwinpeaks || fHitGe)
    {   
        folder_whiterabbit->Write();
        c4LOG(info, "Processed " << fNEvents << " events.");
        c4LOG(info, "WhiteRabbit histograms written to file.");
    }
}

ClassImp(WhiterabbitCorrelationOnline)
