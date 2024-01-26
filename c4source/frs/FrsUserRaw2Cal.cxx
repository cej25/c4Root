// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsUserRaw2Cal.h"
#include "FrsUserData.h"
#include "FrsUserCalData.h"
#include "TFRSParameter.h"
#include "c4Logger.h"

#include "TClonesArray.h"

#include <vector>
#include <iostream>

FrsUserRaw2Cal::FrsUserRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsUserData"))
    ,   fCalArray(new TClonesArray("FrsUserCalData"))
{
}

FrsUserRaw2Cal::FrsUserRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fRawArray(new TClonesArray("FrsUserData"))
    ,   fCalArray(new TClonesArray("FrsUserCalData"))
{
}

FrsUserRaw2Cal::~FrsUserRaw2Cal()
{
    c4LOG(info, "Deleting FrsUserRaw2Cal task");
    if (fRawArray) delete fRawArray;
    if (fCalArray) delete fCalArray;
}



InitStatus FrsUserRaw2Cal::Init()
{
    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fRawArray = (TClonesArray*)mgr->GetObject("FrsUserData");
    c4LOG_IF(fatal, !fRawArray, "FRS branch of UserData not found");

    FairRootManager::Instance()->Register("FrsUserCalData", "FRS User Cal Data", fCalArray, !fOnline);

    fRawArray->Clear();
    fCalArray->Clear();

    return kSUCCESS;
}

void FrsUserRaw2Cal::Exec(Option_t* option)
{

    // check there is actual data from module(s)
    int mult = fRawArray->GetEntriesFast();
    if (!mult) return;


    fNEvents += 1;

}

void FrsUserRaw2Cal::FinishEvent()
{
    // clears
}

void FrsUserRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.", fNEvents));
}

ClassImp(FrsUserRaw2Cal)