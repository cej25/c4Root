#include "FrsCalSpectra.h"

#include "FairTask.h"

FrsCalSpectra::FrsCalSpectra()
    :   FrsCalSpectra("FrsCalSpectra", 1)
{
}

FrsCalSpectra::FrsCalSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fCalMainArray(NULL)  
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

    fCalMainArray = (TClonesArray*)mgr->GetObject("FrsMainCalData");
    c4LOG_IF(fatal, !fCalMainArray, "Branch FrsMainCalData not found!");

    frs_cal_hists = new TFolder("Calib", "Calib");
}