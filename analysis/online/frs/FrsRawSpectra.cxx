// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsRawSpectra.h"
#include "FrsMainData.h"
#include "FrsTPCData.h"
#include "FrsUserData.h"
#include "FrsVFTXData.h"
#include "EventHeader.h"
#include "c4Logger.h"

// ROOT
#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"


FrsRawSpectra::FrsRawSpectra()
    :   FrsRawSpectra("FrsRawSpectra", 1)
{
}

FrsRawSpectra::FrsRawSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fFrsMainArray(NULL)
    ,   fFrsUserArray(NULL)
    ,   fFrsTPCArray(NULL)
    ,   fFrsVFTXArray(NULL)  
    ,   fNEvents(0)
    ,   header(nullptr)  
{
}

FrsRawSpectra::~FrsRawSpectra()
{
    c4LOG(info, "");
    if (fMainArray) delete fMainArray;
}


InitStatus FrsRawSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fFrsMainArray = (TClonesArray*)mgr->GetObject("FrsMainData");
    c4LOG_IF(fatal, !fFrsMainArray, "Branch FrsMainData not found");
    fFrsUserArray = (TClonesArray*)mgr->GetObject("FrsUserData");
    c4LOG_IF(fatal, !fFrsUserArray, "Branch FrsUserData not found");
    fFrsTPCArray = (TClonesArray*)mgr->GetObject("FrsTPCData");
    c4LOG_IF(fatal, !fFrsTPCArray, "Branch FrsTPCData not found");
    fFrsVFTXArray = (TClonesArray*)mgr->GetObject("FrsVFTXData");
    c4LOG_IF(fatal, !fFrsVFTXArray, "Branch FrsVFTXData not found");

    // we should define this somewhere...
    folder_frs_hists = (TFolder*)mgr->GetObject("FRS");
    c4LOG_IF(fatal, !folder_frs_hists, "FRS Histograms folder not found!");

    folder_frs_raw_hists = new TFolder("Raw_Histograms", "Raw_Histograms");
    folder_frs_hists->Add(folder_frs_raw_hists);

    // Main Crate

    h1_main_v1290_leading_hits[chans] = new TH1F(); // v1290 data only leads
    h1_main_v1290_hits[chans] = new TH1F(); // multiplicity


    // TPC crate
    h2_tpc_v1190_data_per_chan_1st_hit = new TH2F(); // tpc only first hit
    h2_tpc_v1190_data_per_chan = new TH2F(); // kinda covered by histograms demanded below?

    // unsure where this goes
    h1_Trigger = new TH1I();
    h1_pTrigger = new TH1I();
    h1_NbTrig = new TH1I();
    h2_CombiTrig2 = new TH2I();
    h1_Tpat = new TH1F(); // tpat crate? functional?

    // User Crate


    // VFTX Crate
    h1_vftx_lead_mult = new TH1F(); // by module/channel
    h1_vftx_trail_mult = new TH1F(); // by module/channel
    h1_vftx_leading_cc = new TH1F(); // by module/channel
    h1_vftx_leading_ft = new TH1F(); // by module/channel
    h1_vftx_trailing_cc = new TH1F(); // by module/channel
    h1_vftx_trailing_ft = new TH1F(); // by module/channel
    h1_vftx_leading_time = new TH1F(); // by module/channel
    h1_vftx_leading_time_ref_ch0 = new TH1F(); // by module/channel
    h2_vftx_leading_time_ref_ch0_event = new TH2F(); // event vs above
    h2_vftx_leading_time_ref_ch8_event = new TH2F(); // event vs above
    h2_vftx_leading_time_ch0vs4 = new TH2F();

    // basically here dump all data from main and user into 1d and 2d histograms
    // (per channel and vs channel)
    h1_v792[chan] = new TH1I();
    h2_v792_all = new TH2I(); // above but all in one 2d histogram
    // h1_vme_main_11 // is this scalers? print out geo next run
    // etc etc ...

    // do same as above for TPC crate

    // maybe same for eventual tpat crate

    // same for travelling music crate

    // the end..

    // do we need more from DESPEC Go4?

}


// reset histos



void FrsRawSpectra::Exec(Option_t* option)
{



}