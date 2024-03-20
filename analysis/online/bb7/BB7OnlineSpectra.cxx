// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BB7OnlineSpectra.h"
#include "EventHeader.h"
#include "BB7VmeData.h"
#include "c4Logger.h"

// root
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


BB7OnlineSpectra::BB7OnlineSpectra()
    :   FairTask()
    ,   fHitBB7(NULL)
    ,   header(nullptr)
{

}

BB7OnlineSpectra::~BB7OnlineSpectra()
{

}

InitStatus BB7OnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitBB7 = (TClonesArray*)mgr->GetObject("BB7VmeData");
    c4LOG_IF(fatal, !fHitBB7, "Branch BB7VmeData not found!");

    // set up config later

    TDirectory::TContext ctx(nullptr);

    folder_bb7_hists = new TFolder("BB7", "BB7");
    run->AddObject(folder_bb7_hists);

    folder_raw_e = new TFolder("Raw Energy", "Raw Energy");
    folder_bb7_hists->Add(folder_raw_e);

    for (int i = 0; i < 64; i++)
    {
        h1_bb7_RawE[i] = new TH1D(Form("h1_bb7_RawE%i", i), Form("Raw Energy BB7 Channel %i", i), 4096, 0, 4096); // 12 bit adc
        folder_raw_e->Add(h1_bb7_RawE[i]);
    }

    return kSUCCESS;

}

void BB7OnlineSpectra::Exec(Option_t* option)
{
    if (fHitBB7 && fHitBB7->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitBB7->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            BB7VmeData* bb7VmeHit = (BB7VmeData*)fHitBB7->At(ihit);
            if (!bb7VmeHit) continue;

            std::vector<uint32_t> geos = bb7VmeHit->Get_v7x5_geo();
            std::vector<uint32_t> channels = bb7VmeHit->Get_v7x5_channel();
            std::vector<uint32_t> data = bb7VmeHit->Get_v7x5_data();

            for (int j = 0; j < data.size(); j++)
            {
                h1_bb7_RawE[channels[j]]->Fill(data[j]);
            }
        }
    }
}

void BB7OnlineSpectra::FinishEvent()
{

}

void BB7OnlineSpectra::FinishTask()
{
    folder_bb7_hists->Write();
}
