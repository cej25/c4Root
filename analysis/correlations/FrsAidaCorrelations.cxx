#include "FrsAidaCorrelations.h"


#include "FrsHitData.h"
#include "AidaHitData.h"

FrsAidaCorrelations::FrsAidaCorrelations()
    :   FairTask()
    ,   fNEvents()
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fAidaHitArray(new TClonesArray("AidaHitData"))
    ,   fFrsAidaCorrelation(new TClonesArray("FrsAidaCorrelationData"))
{
}

FrsAidaCorrelations::FrsAidaCorrelations(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fAidaHitArray(new TClonesArray("AidaHitData"))
    ,   fFrsAidaCorrelation(new TClonesArray("FrsAidaCorrelationData"))
{

}

FrsAidaCorrelations::~FrsAidaCorrelations()
{
    c4LOG(info, "Deleting FrsAidaCorrelations task.");
    if (fHitArray) delete fHitArray;
}

InitStatus FrsAidaCorrelations::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    fFrsHitArray = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fFrsHitArray, "FrsHitData branch not found!");

    fAidaHitArray = (TClonesArray*)mgr->GetObject("AidaHitData");
    c4LOG_IF(fatal, !fAidaHitArray, "FrsHitData branch not found!");

    mgr->Register("FrsAidaCorrelationData", "FRS-AIDA Correlation Data", fFrsAidaCorrelation, !fOnline);


    // clear stuff

    return kSUCCESS;


}