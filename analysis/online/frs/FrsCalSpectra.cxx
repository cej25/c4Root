// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsCalSpectra.h"
#include "FrsCalData.h"
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


FrsCalSpectra::FrsCalSpectra()
    :   FrsCalSpectra("FrsCalSpectra", 1)
{
}

FrsCalSpectra::FrsCalSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fFrsMainCalArray(NULL)
    ,   fFrsUserCalArray(NULL)
    ,   fFrsTPCCalArray(NULL)
    ,   fFrsVFTXCalArray(NULL)  
    ,   fNEvents(0)
    ,   header(nullptr)  
{
}

FrsCalSpectra::~FrsCalSpectra()
{
    c4LOG(info, "");
    if (fCalMainArray) delete fCalMainArray;
}


InitStatus FrsCalSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fFrsMainCalArray = (TClonesArray*)mgr->GetObject("FrsMainCalData");
    c4LOG_IF(fatal, !fFrsMainCalArray, "Branch FrsMainCalData not found");
    fFrsUserCalArray = (TClonesArray*)mgr->GetObject("FrsUserCalData");
    c4LOG_IF(fatal, !fFrsUserCalArray, "Branch FrsUserCalData not found");
    fFrsTPCArray = (TClonesArray*)mgr->GetObject("FrsTPCData");
    c4LOG_IF(fatal, !fFrsTPCArray, "Branch FrsTPCData not found");
    fFrsTPCCalArray = (TClonesArray*)mgr->GetObject("FrsTPCCalData");
    c4LOG_IF(fatal, !fFrsTPCCalArray, "Branch FrsTPCCalData not found");
    fFrsVFTXCalArray = (TClonesArray*)mgr->GetObject("FrsVFTXCalData");
    c4LOG_IF(fatal, !fFrsVFTXCalArray, "Branch FrsVFTXCalData not found");

    // we should define this somewhere...
    frs_hists = (TFolder*)mgr->GetObject("FRS");
    c4LOG_IF(fatal, !frs_hists, "FRS Histograms folder not found!");

    frs_cal_hists = new TFolder("Calib", "Calib");
    frs_hists->Add(frs_cal_hists);


    // CEJ: most of what we need in this class is already
    // done in FrsDetectorsOnline
    // TBD with JELL


}