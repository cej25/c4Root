#ifndef FrsAnalysisSpectra_H
#define FrsAnalysisSpectra_H

#include "FairTask.h"

class EventHeader;
class TClonesArray;
class FrsHitData;

class FrsAnalysisSpectra : public FairTask
{
    public:
        FrsAnalysisSpectra();

        FrsAnalysisSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsAnalysisSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

    private:

        Int_t fNEvents;
        EventHeader* header;
        Bool_t fOnline;

        TClonesArray* fFrsHitArray;
        TClonesArray* fFrsAnalysisArray;

    public:
        ClassDef(FrsAnalysisSpectra, 1);
};

#endif