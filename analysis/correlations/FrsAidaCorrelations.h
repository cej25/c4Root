#ifndef FrsAidaCorrelations_H
#define FrsAidaCorrelations_H

#include "TClonesArray.h"

class FrsAidaCorrelations : public FairTask
{
    public:
        FrsAidaCorrelations();

        FrsAidaCorrelations(const TString& name, Int_t verbose);

        virtual ~FrsAidaCorrelations();

        void FinishEvent();
        void FinishTask();

    private:

        TClonesArray* fFrsHitArray;
        TClonesArray* fAidaImplants;
        TClonesArray* fFrsAidaCorrelation;

        Int_t fNEvents;
        EventHeader* header;

    public:
        ClassDef(FrsAidaCorrelations, 1)
};



#endif
