#ifndef FrsVFTXRaw2Cal_H
#define FrsVFTXRaw2Cal_H

#include "TFRSParameter.h"
#include "FrsVFTXCalData.h"
#include <vector>

class TClonesArray;
class EventHeader;
class FrsVFTXData;
class FrsVFTXCalData;

class FrsVFTXRaw2Cal : public FairTask
{
    public:
        FrsVFTXRaw2Cal();
        FrsVFTXRaw2Cal(const TString& name, Int_t verbose);

        ~FrsVFTXRaw2Cal();

        virtual InitStatus Init();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online) { fOnline = set_online; }

    private:
        Bool_t fOnline;

        TClonesArray* fCalArray;
        TClonesArray* fRawArray;

        FrsVFTXData* fRawHit;

        EventHeader* header;
        Int_t fNEvents = 0;

        // Output

    public:
        ClassDef(FrsVFTXRaw2Cal, 1);
};

#endif