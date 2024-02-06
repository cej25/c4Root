// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "WhiterabbitCorrelationOnline.h"
#include "EventHeader.h"
#include "FatimaTwinpeaksCalData.h"
#include "bPlastTwinpeaksCalData.h"
#include "GermaniumCalData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

WhiterabbitCorrelationOnline::WhiterabbitCorrelationOnline() : WhiterabbitCorrelationOnline("WhiterabbitCorrelationOnline")
{
}

WhiterabbitCorrelationOnline::WhiterabbitCorrelationOnline(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatimaTwinpeaks(NULL)
    , fHitbPlastTwinpeaks(NULL)
    , fHitGe(NULL)
    , fHitAida(NULL)
    , fNEvents(0)
    , header(nullptr)
{
}

WhiterabbitCorrelationOnline::~WhiterabbitCorrelationOnline()
{
    c4LOG(info, "");
    if (fHitFatimaTwinpeaks)
        delete fHitFatimaTwinpeaks;
    if (fHitbPlastTwinpeaks)
        delete fHitbPlastTwinpeaks;
    if (fHitGe)
        delete fHitGe;
}

void WhiterabbitCorrelationOnline::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus WhiterabbitCorrelationOnline::Init()
{

    // number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatimaTwinpeaks = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatimaTwinpeaks, "Branch FatimaTwinpeaksCalData not found!");

    folder_whiterabbit = new TFolder("Whiterabbit Subsystem Correlation", "Whiterabbit Subsystem Correlation");

    run->AddObject(folder_whiterabbit);

    c_whiterabbit_correlation_bplast_fatima = new TCanvas("c_whiterabbit_correlation_bplast_fatima", "c_whiterabbit_correlation_bplast_fatima", 10, 10, 800, 700);
    c_whiterabbit_correlation_bplast_fatima->cd();
    h1_whiterabbit_correlation_bplast_fatima = new TH2F("h1_whiterabbit_correlation_bplast_fatima", "h1_whiterabbit_correlation_bplast_fatima", 1000, -1000, 1000, 1000, 0, 1e5);
    h1_whiterabbit_correlation_bplast_fatima->GetXaxis()->SetTitle("Time difference(bPlast - Fatima) [ns]");
    h1_whiterabbit_correlation_bplast_fatima->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_bplast_fatima->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_bplast_fatima);
    c_whiterabbit_correlation_bplast_fatima->cd(0);

    c_whiterabbit_correlation_fatima_ge = new TCanvas("c_whiterabbit_correlation_fatima_ge", "c_whiterabbit_correlation_fatima_ge", 10, 10, 800, 700);
    c_whiterabbit_correlation_fatima_ge->cd();
    h1_whiterabbit_correlation_fatima_ge = new TH2F("h1_whiterabbit_correlation_fatima_ge", "h1_whiterabbit_correlation_fatima_ge", 1000, -1000, 1000, 1000, 0, 1e5);
    h1_whiterabbit_correlation_fatima_ge->GetXaxis()->SetTitle("Time difference(Fatima - Germanium) [ns]");
    h1_whiterabbit_correlation_fatima_ge->GetYaxis()->SetTitle("Counts");
    h1_whiterabbit_correlation_fatima_ge->Draw();
    folder_whiterabbit->Add(h1_whiterabbit_correlation_fatima_ge);
    c_whiterabbit_correlation_fatima_ge->cd(0);

    c_whiterabbit_correlation_bplast_ge = new TCanvas("c_whiterabbit_correlation_bplast_ge", "c_whiterabbit_correlation_bplast_ge", 10, 10, 800, 700);
    c_whiterabbit_correlation_bplast_ge->cd();
    h1_whiterabbit_correlation_bplast_ge = new TH2F("h1_whiterabbit_correlation_bplast_ge", "h1_whiterabbit_correlation_bplast_ge", 1000, -1000, 1000, 1000, 0, 1e5);
    h1_whiterabbit_correlation_bplast_ge->GetXaxis()->SetTitle("Time difference(bPlast - Germanium) [ns]");
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

    gSystem->cd("..");

    // snapshot .root file with data and time

    file_whiterabbit_snapshot = new TFile(Form("Whiterabbit_correlation_%d_%d_%d_%d_%d_%d.root", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec), "RECREATE");
    file_whiterabbit_snapshot->cd();
    h1_whiterabbit_correlation_bplast_fatima->Write();
    h1_whiterabbit_correlation_fatima_ge->Write();
    h1_whiterabbit_correlation_bplast_ge->Write();
    file_whiterabbit_snapshot->Close();
    delete file_whiterabbit_snapshot;

    gSystem->cd("..");
    c4LOG(info, "Snapshot saved in:" << snapshot_dir);    
}



void WhiterabbitCorrelationOnline::Exec(Option_t* option)
{   
    //JB: there is probably a better way to code this. JEL or Nic hilfe bitte!
    if (fHitFatimaTwinpeaks && fHitFatimaTwinpeaks->GetEntriesFast() > 0 && fHitbPlastTwinpeaks && fHitbPlastTwinpeaks->GetEntriesFast() > 0 && fHitGe && fHitGe->GetEntriesFast() > 0)
    {
        Int_t nHitsFatima = fHitFatimaTwinpeaks->GetEntriesFast();
        Int_t nHitsbPlast = fHitbPlastTwinpeaks->GetEntriesFast();
        Int_t nHitsGe = fHitGe->GetEntriesFast();

        for (Int_t i = 0; i < nHitsFatima; i++)
        {
            FatimaTwinpeaksCalData* hitFatima = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(i);
            if (hitFatima)
            {
                for (Int_t j = 0; j < nHitsbPlast; j++)
                {
                    bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(j);
                    if (hitbPlast)
                    {
                        h1_whiterabbit_correlation_bplast_fatima->Fill(hitbPlast->Get_wr_t() - hitFatima->Get_wr_t());
                    }
                }
            }
        }
        for (Int_t i = 0; i < nHitsFatima; i++){
            FatimaTwinpeaksCalData* hitFatima = (FatimaTwinpeaksCalData*)fHitFatimaTwinpeaks->At(i);
            if (hitFatima)
            {
                for (Int_t j = 0; j < nHitsGe; j++)
                {
                    GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(j);
                    if (hitGe)
                    {
                        h1_whiterabbit_correlation_fatima_ge->Fill(hitFatima->Get_wr_t() - hitGe->Get_wr_t());
                    }
                }
            }
        }
        for (Int_t i = 0; i < nHitsbPlast; i++){
            bPlastTwinpeaksCalData* hitbPlast = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(i);
            if (hitbPlast)
            {
                for (Int_t j = 0; j < nHitsGe; j++)
                {
                    GermaniumCalData* hitGe = (GermaniumCalData*)fHitGe->At(j);
                    if (hitGe)
                    {
                        h1_whiterabbit_correlation_bplast_ge->Fill(hitbPlast->Get_wr_t() - hitGe->Get_wr_t());
                    }
                }
            }
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
        c4LOG(info, "WhiteRabbit histograms written to file.");
    }
}

ClassImp(WhiterabbitCorrelationOnline)
