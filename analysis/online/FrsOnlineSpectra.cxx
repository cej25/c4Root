// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsOnlineSpectra.h"
#include "FrsHitData.h"
#include "EventHeader.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

FrsOnlineSpectra::FrsOnlineSpectra()
    : FrsOnlineSpectra("FrsOnlineSpectra", 1)
{
}

FrsOnlineSpectra::FrsOnlineSpectra(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fHitFrsArray(NULL)
    , fNEvents(0)
    , fMin_Z(30.)
    , fMax_Z(100.)
    , fMin_AoQ(1.6)
    , fMax_AoQ(4.0)
    , fMin_x4(-100.) // no idea
    , fMax_x4(100.0) // no idea
    , fMin_Z_gate(30.)
    , fMax_Z_gate(80.)
    , fMin_AoQ_gate(1.6)
    , fMax_AoQ_gate(3.0)
    , header(nullptr)
{
}

FrsOnlineSpectra::~FrsOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitFrsArray)
        delete fHitFrsArray;
}

// Public Method SetParContainers
void FrsOnlineSpectra::SetParContainers()
{
    // Parameter Containers
    FairRuntimeDb* rtdb = FairRuntimeDb::instance(); // infuriating lack of consistency with capitalisation...
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus FrsOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFrsArray = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fHitFrsArray, "Branch FrsHitData not found");


    TFolder * frs_spectra_folder = new TFolder("frs", "frs");
    TFolder * frs_spectra_folder_histograms = new TFolder("frs_histograms", "frs_histograms");

    run->AddObject(frs_spectra_folder_histograms);
    

    h_frs_z1_vs_AoQ = new TH2F("h_frs_z1_vs_AoQ","Z1 vs A/Q",5000,fMin_AoQ,fMax_AoQ,5000,fMin_Z,fMax_Z);
    frs_spectra_folder_histograms->Add(h_frs_z1_vs_AoQ);


    h_frs_beta_sci = new TH1D("h_frs_beta_sci", "beta from SCI TOF", 1000,0,1);
    frs_spectra_folder_histograms->Add(h_frs_beta_sci);



    // Register command to reset histograms
    run->GetHttpServer()->RegisterCommand("Reset_IncomingID_HIST", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;

}

void FrsOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
   // fh1_TdcRaw->Clear();
   // fh1_TdcChan->Clear();
}

void FrsOnlineSpectra::Exec(Option_t* option)
{
    // Fill hit data
    if (fHitFrsArray && fHitFrsArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitFrsArray->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            fHitFrs = (FrsHitData*)fHitFrsArray->At(ihit);
            if (!fHitFrs)
                continue;

            h_frs_z1_vs_AoQ->Fill(fHitFrs->Get_ID_AoQ_corr(), fHitFrs->Get_ID_z());
            h_frs_beta_sci->Fill(fHitFrs->Get_ID_beta());
        }
    }

    fNEvents += 1;
}

void FrsOnlineSpectra::FinishEvent()
{
    if (fHitFrsArray)
    {
        fHitFrsArray->Clear();
    }
}

void FrsOnlineSpectra::FinishTask()
{
    if (fHitFrsArray){
        h_frs_z1_vs_AoQ->Write();
    }
}

ClassImp(FrsOnlineSpectra)