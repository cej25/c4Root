// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsVFTXRaw2Cal.h"
#include "FrsVFTXData.h"
#include "FrsVFTXCalData.h"
#include "TFRSParameter.h"
#include "c4Logger.h"

#include "TClonesArray.h"

#include <vector>
#include <iostream>

FrsVFTXRaw2Cal::FrsVFTXRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsVFTXData"))
    ,   fCalArray(new TClonesArray("FrsVFTXCalData"))
{
}

FrsVFTXRaw2Cal::FrsVFTXRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsVFTXData"))
    ,   fCalArray(new TClonesArray("FrsVFTXCalData"))
{
}

FrsVFTXRaw2Cal::~FrsVFTXRaw2Cal()
{
    c4LOG(info, "Deleting FrsVFTXRaw2Cal task");
    if (fRawArray) delete fRawArray;
    if (fCalArray) delete fCalArray;
}



InitStatus FrsVFTXRaw2Cal::Init()
{
    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fRawArray = (TClonesArray*)mgr->GetObject("FrsVFTXData");
    c4LOG_IF(fatal, !fRawArray, "FRS branch of VFTXData not found");

    FairRootManager::Instance()->Register("FrsVFTXCalData", "FRS VFTX Cal Data", fCalArray, !fOnline);

    fRawArray->Clear();
    fCalArray->Clear();

    return kSUCCESS;
}

void FrsVFTXRaw2Cal::Exec(Option_t* option)
{

    // check there is actual data from module(s)
    int mult = fRawArray->GetEntriesFast();
    if (!mult) return;


    fNEvents += 1;

}

void FrsVFTXRaw2Cal::FinishEvent()
{
    // clears
}

void FrsVFTXRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.", fNEvents));
}

ClassImp(FrsVFTXRaw2Cal)