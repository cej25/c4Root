// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaVmeOnlineSpectra.h"
#include "EventHeader.h"
#include "FatimaVmeCalData.h"
#include "TFatimaVmeConfiguration.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TFile.h"
#include "TRandom.h"
#include "TDirectory.h"

FatimaVmeOnlineSpectra::FatimaVmeOnlineSpectra() : FatimaVmeOnlineSpectra("FatimaVmeOnlineSpectra")
{
}

FatimaVmeOnlineSpectra::(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fHitFatimaVme(NULL)
    ,   fNEvents(0)
    ,   header(nullptr)
{

}

FatimaVmeOnlineSpectra::~FatimaVmeOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitFatimaVme) delete fHitFatimaVme;
}

// par containers

InitStatus FatimaVmeOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance()
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatimaVme = (TClonesArray*)mgr->GetObject("FatimaVmeCalData");
    c4LOG_IF(fatal, !fHitFatimaVme, "Branch FatimaVmeCalData not found!");

    TFatimaVmeConfiguration const* fatima_vme_config = new TFatimaVmeConfiguration();

    TDirectory::TContext ctx(nullptr);

    folder_fatima_vme = new TFolder("Fatima VME", "Fatima VME");

    run->AddObject(folder_fatima_vme);

    folder_raw_vme = new TFolder("Raw Spectra", "Raw Spectra");
    folder_fatima_vme->Add(folder_raw_vme);
    folder_raw_energy = new TFolder("Raw Energy", "Raw Energy");
    folder_raw_time = new TFolder("Raw Time", "Raw Time");
    folder_fatima_vme->Add(folder_raw_energy);
    folder_fatima_vme->Add(folder_raw_time);

    // Scalers?

    // for now just plot detectors?
    for (int i = 0; i < fatima_vme_config->NDetectors(); i++)
    {
        h1_FatVme_RawE[i] = new TH1D(Form("h1_FatVme_RawE%i", i), Form("Fatima VME Raw Energy - Detector %i", i), 2000, 0, 40000);
        folder_raw_energy->Add(h1_FatVme_RawE[i]);
    }

    for (int i = 0; i < fatima_vme_config->NDetectors(); i++)
    {
        h1_FatVme_RawT[i] = new TH1D(Form("h1_FatVme_RawT%i", i), Form("Fatima VME Raw Time - Detector %i", i), 5000, -1e6, 7e7);
        folder_raw_time->Add(h1_FatVme_RawT[i]);
    }

    // canvases etc

    run->GetHttpServer()->RegisterCommand("Reset_Histo", "/Objects/%s/->Reset_Histo()", GetName());
    run->GetHttpServer()->RegisterCommand("Snapshot_Histo", "/Objects/%s/->Snapshot_Histo()", GetName());
    
    return kSUCCESS;

}

void FatimaVmeOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "Resetting Fatima VME Histograms");
}

void FatimaVmeOnlineSpectra::Snapshot_Histo()
{
    c4LOG(info, "Snapshotting Fatima VME Histograms");

    c4LOG(info, "Snapshots saved in: ");
}

void FatimaVmeOnlineSpectra::Exec(Option_t* option)
{
    if (fHitFatimaVme && fHitFatimaVme->GetEntriesFast())
    {
        Int_t nHits = fHitFatimaVme->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            FatimaVmeCalData* hit = (FatimaVmeCalData*)fHitFatimaVme->At(hit);
            if (!hit) continue;

            
        }
    }
}