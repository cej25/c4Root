// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "bPlastOnlineSpectra.h"
#include "EventHeader.h"
#include "bPlastTamexData.h"
#include "c4Logger.h"

// some stuff from nic
#include <TDirectory.h>
#include <TH1.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

bPlastOnlineSpectra::bPlastOnlineSpectra()
{
}

bPlastOnlineSpectra::bPlastOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitbPlast(NULL)
    , fNEvent(0)
    , header(nullptr)
{
}

bPlastOnlineSpectra::~bPlastOnlineSpectra()
{
    // c4LOG(info, "");
    if (fHitbPlast)
        delete fHitbPlast;
}

void bPlastOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus bPlastOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitbPlast = (TClonesArray*)mgr->GetObject("bPlastTamexData");
    c4LOG_IF(fatal, !fHitbPlast, "Branch bPlastTamexData not found!");


    TFolder * bplast_spectra_folder = new TFolder("bPlast", "bPlast");

    run->AddObject(bplast_spectra_folder);

    // Create histograms

    cLeadTime = new TCanvas("Lead_Time", "Lead Time", 10, 10, 800, 700);

    fh1_LeadTime = new TH1F("bplast_leadtime", "bPlast Lead Time spectrum", 2500, 0, 2000);
    fh1_LeadTime->GetXaxis()->SetTitle("Lead Time");
    fh1_LeadTime->GetYaxis()->SetTitle("Counts");
    fh1_LeadTime->GetYaxis()->SetTitleOffset(1.15);
    fh1_LeadTime->GetXaxis()->CenterTitle(true);
    fh1_LeadTime->GetYaxis()->CenterTitle(true);
    fh1_LeadTime->GetXaxis()->SetLabelSize(0.045);
    fh1_LeadTime->GetXaxis()->SetTitleSize(0.045);
    fh1_LeadTime->GetYaxis()->SetLabelSize(0.045);
    fh1_LeadTime->GetYaxis()->SetTitleSize(0.045);
    fh1_LeadTime->SetLineColor(1);
    fh1_LeadTime->Draw("");

    bplast_spectra_folder->Add(cLeadTime);

    run->GetHttpServer()->RegisterCommand("Reset_bPlast_Histo", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void bPlastOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
    fh1_LeadTime->Reset();
}

void bPlastOnlineSpectra::Exec(Option_t* option)
{   

    if (fHitbPlast && fHitbPlast->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitbPlast->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            bPlastTamexData* hit = (bPlastTamexData*)fHitbPlast->At(ihit);
            if (!hit)
                continue;
            
            // just show me 0 for now
            if (hit->GetDet() == 1 && hit->GetChan() == 1)
            {
                if (hit->GetPMT_Lead() != 0)
                {
                    fh1_LeadTime->Fill(hit->GetPMT_Lead());
                }
            }

        }
    }

    fNEvent += 1;
}

void bPlastOnlineSpectra::FinishEvent()
{
    if (fHitbPlast)
    {
        fHitbPlast->Clear();
    }
}

void bPlastOnlineSpectra::FinishTask()
{
    if (fHitbPlast)
    {
        cLeadTime->Write();
    }
}

ClassImp(bPlastOnlineSpectra)