#ifndef FatimaVmeRaw2Cal_H
#define FatimaVmeRaw2Cal_H

#include "FairTask.h"

class TClonesArray;
class EventHeader;
class FatimaVmeData;
class FatimaVmeCalData;
//class TimeMachineData;

class FatimaVmeRaw2Cal : public FairTask
{
    public:
        FatimaVmeRaw2Cal();
        
        virtual ~FatimaVmeRaw2Cal();

        virtual InitStatus Init();

        void Exec();

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t option) { fOnline = option; }

    private:

        Bool_t fOnline;
        TClonesArray* fcal_data;

        Int_t fNEvents = 0;
        EventHeader* header;

        // Stuff we need

    public:
        ClassDef(FatimaVmeRaw2Cal, 1);

};



#endif