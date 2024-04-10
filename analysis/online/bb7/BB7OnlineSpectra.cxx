// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BB7OnlineSpectra.h"
#include "EventHeader.h"
#include "BB7VmeCalData.h"
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

    fHitBB7 = (TClonesArray*)mgr->GetObject("BB7VmeCalData");
    c4LOG_IF(fatal, !fHitBB7, "Branch BB7VmeCalData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    // set up config later

    TDirectory::TContext ctx(nullptr);

    dir_bb7 = new TDirectory("BB7", "BB7", "", 0);
    // mgr->Register("BB7", "BB7 Directory", dir_bb7, false); // allow other tasks to find directory
    histograms->Add(dir_bb7);

    dir_raw_e = dir_bb7->mkdir("Raw Energy");
    dir_stats = dir_bb7->mkdir("Stats");

    // base on config later - add detector loop later also
    for (int side = 0; side < 2; side++)
    {   
        dir_raw_e->cd();
        for (int strip = 0; strip < 32; strip++)
        {
            h1_bb7_RawE[side][strip] = new TH1D(Form("h1_bb7_RawE_Side%i_Strip%i", side, strip+1), Form("Raw Energy BB7 Side %i Strip %i", side, strip+1), 10000, 0, 10000); // 12 bit adc should only be 4096 max but saw higher?
        }

        dir_stats->cd();
        h1_bb7_hitpattern[side] = new TH1I(Form("h1_bb7_hitpattern_Side%i", side), Form("BB7 Hit Pattern Side %i", side), 32, 0, 32);
    }

    
    dir_bb7->cd();

    return kSUCCESS;

}

void BB7OnlineSpectra::Exec(Option_t* option)
{
    if (fHitBB7 && fHitBB7->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitBB7->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            BB7VmeCalData* bb7VmeHit = (BB7VmeCalData*)fHitBB7->At(ihit);
            if (!bb7VmeHit) continue;

            std::vector<int> sides = bb7VmeHit->Get_Sides();
            std::vector<int> strips = bb7VmeHit->Get_Strips();
            std::vector<uint32_t> raw_adc = bb7VmeHit->Get_Raw_ADC();

            for (int j = 0; j < raw_adc.size(); j++)
            {
                h1_bb7_RawE[sides[j]][strips[j]-1]->Fill(raw_adc[j]);

                h1_bb7_hitpattern[sides[j]]->Fill(strips[j]-1);
            }
        }
    }
}

void BB7OnlineSpectra::FinishEvent()
{

}

void BB7OnlineSpectra::FinishTask()
{
    //c4LOG(info, Form("Plotted %i Events", fNEvents));
}
