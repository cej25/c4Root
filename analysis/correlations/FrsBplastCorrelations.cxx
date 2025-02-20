// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsBplastCorrelations.h"
#include "EventHeader.h"
#include "bPlastTwinpeaksData.h"
#include "bPlastTwinpeaksCalData.h"
#include "FrsGate.h"
#include "FrsHitData.h"
#include "TbPlastConfiguration.h"
#include "TFrsConfiguration.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TDirectory.h"

FrsBplastCorrelations::FrsBplastCorrelations() : FrsBplastCorrelations("FrsBplastCorrelations")
{
    bplast_config = TbPlastConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();

}

FrsBplastCorrelations::FrsBplastCorrelations(FrsGate * fg) : FrsBplastCorrelations("FrsBplastCorrelations")
{
    bplast_config = TbPlastConfiguration::GetInstance();
    frsgate = fg;
    frs_config = TFrsConfiguration::GetInstance();
}

FrsBplastCorrelations::FrsBplastCorrelations(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitbPlast(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    bplast_config = TbPlastConfiguration::GetInstance();
}

FrsBplastCorrelations::~FrsBplastCorrelations()
{
    c4LOG(info, "");
    if (fHitbPlast)
        delete fHitbPlast;
    if (fHitFrs)
        delete fHitFrs;
}

InitStatus FrsBplastCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

//    FairRunOnline* run = FairRunOnline::Instance();
//make it on/offline for now

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitbPlast = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitbPlast, "Branch bPlastTwinpeaksCalData not found!");

    fHitFrs = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fHitFrs, "Branch FrsHitData not found!");

    // try and find frs folder to dumpc
    dir_frs = (TDirectory*)mgr->GetObject("FRS");
    if (dir_frs == nullptr)
    {
        frs_dir_found = false;
        dir_frs = new TDirectory("FRS", "FRS", "", 0);
        mgr->Register("FRS", "FRS Directory", dir_frs, false);
    }

    dir_frs_bplast_corrs = dir_frs->mkdir("FRS-bPlast Correlations");

    dir_frs_bplast_corrs->cd();

    //TDirectory::TContext ctx(nullptr);

    h2_Z_vs_slowToT = new TH2D("h2_Z_vs_slowToT", "Z (MUSIC 1) vs Slow ToT (bPlast)", 2000, 0, 1600, 750, 50, 80);

    
    return kSUCCESS;
}

void FrsBplastCorrelations::Exec(Option_t* option)
{
    if (fHitFrs && fHitFrs->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFrs->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            FrsHitItem* FrsHit = (FrsHitItem*) fHitFrs->At(ihit);
            if (!FrsHit) continue;

            double z = FrsHit->Get_ID_z();

            if (fHitbPlast && fHitbPlast->GetEntriesFast() > 0)
            {
                Int_t nHit_bPlast = fHitbPlast->GetEntriesFast();
                
                for (Int_t ihit_bPlast = 0; ihit_bPlast < nHit_bPlast; ihit_bPlast++)
                {
                    bPlastTwinpeaksCalData* bPlastHit = (bPlastTwinpeaksCalData*)fHitbPlast->At(ihit_bPlast);
                    if (!bPlastHit) continue;

                    double slow_tot = bPlastHit->Get_slow_ToT();

                    h2_Z_vs_slowToT->Fill(slow_tot, z);

                }
            }
        }
    }

}

void FrsBplastCorrelations::FinishEvent()
{

}

void FrsBplastCorrelations::FinishTask()
{
    if (!frs_dir_found)
    {
        TDirectory* tmp = gDirectory;
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_frs->Write();
        gDirectory = tmp;
    }

}