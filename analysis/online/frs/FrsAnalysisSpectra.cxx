#include "FrsAnalysisSpectra.h
#include "FrsHitData.h"

#include <vector.h>

FrsAnalysisSpectra::FrsAnalysisSpectra()
    :   FairTask()
    ,   fNEvents()
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fFrsAnalysisArray(new TClonesArray("FrsAnalysedData"))
{
}

FrsAnalysisSpectra::FrsAnalysisSpectra(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents()
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   fFrsHitArray(new TClonesArray("FrsHitData"))
    ,   fFrsAnalysisArray(new TClonesArray("FrsAnalysedData"))
{

}

FrsAnalysisSpectra::~FrsAnalysisSpectra()
{
    c4LOG(info, "Deleting FrsAnalysisSpectra task.");
    if (fFrsHitArray) delete fFrsHitArray;
}

InitStatus FrsAnalysisSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "EventHeader. not found!");

    fFrsHitArray = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fFrsHitArray, "FrsHitData branch not found!");

    mgr->Register("FrsAnalysedData", "FRS Analysed Data", fFrsAnalysisArray, !fOnline);

    // clear stuff

    return kSUCCESS;

}

void FrsAnalysisSpectra::Exec(Option_t* option)
{
    int mult = 0;
    if (multFRS == 0) return;

    // for nHit in array etc etc.

    /* --------  TAC and PID gates ----------- */
    if (fFrsHitArray->Get_ID_z() > 0 && FRS_time_mins > 0) hID_Z1_vs_T->Fill(FRS_time_mins, fFrsHitArray->Get_ID_z());

    if (fFrsHitArray->Get_ID_AoQ() > 0 && FRS_time_mins > 0) hID_AoQ_vs_T->Fill(FRS_time_mins, fFrsHitArray->Get_ID_AoQ());

    if (fFrsHitArray->Get_ID_AoQ() > 0 && fFrsHitArray->Get_ID_z() > 0) hID_Z_AoQ->Fill(fFrsHitArray->Get_ID_AoQ(), fFrsHitArray->Get_ID_z());
    if (fFrsHitArray->Get_ID_AoQ_corr() > 0 && fFrsHitArray->Get_ID_z() > 0) hID_Z_AoQ_corr->Fill(fFrsHitArray->Get_ID_AoQ_corr(), fFrsHitArray->Get_ID_z());

    if (fFrsHitArray->Get_ID_z() > 0 && fFrsHitArray->Get_ID_z2() > 0) hID_Z_Z2->Fill(fFrsHitArray->Get_ID_z(), fFrsHitArray->Get_ID_z2());
    if (TMath::Abs(fFrsHitArray->Get_ID_z() - fFrsHitArray->Get_ID_z2()) < 0.4) // CEJ: should we .config this condition?
    {
        hID_Z_AoQ_zsame->Fill(fFrsHitArray->Get_ID_AoQ(), fFrsHitArray->Get_ID_z());
        hID_x4AoQ_zsame->Fill(fFrsHitArray->Get_ID_AoQ(), fFrsHitArray->Get_ID_x2());
        hID_x2AoQ_zsame->Fill(fFrsHitArray->Get_ID_AoQ(), fFrsHitArray->Get_ID_x4());
    }

    // CEJ: "analysis" taken from Go4 (DESPEC/FRS)
    // is stupid, we already demand the x2 condition to fill the hit.
    // this should be reconidered
    if (fFrsHitArray->Get_ID_AoQ() > 0 && fFrsHitArray->Get_() > 0)


}


void FrsAnalysisSpectra::FinishEvent()
{

}

void FrsAnalysisSpectra::FinishTask()
{

}

ClassImp(FrsAnalysisSpectra)
