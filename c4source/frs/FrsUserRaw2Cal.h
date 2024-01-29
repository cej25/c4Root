#ifndef FrsUserRaw2Cal_H
#define FrsUserRaw2Cal_H

#include "TFRSParameter.h"
#include "FrsUserCalData.h"
#include <vector>

class TClonesArray;
class EventHeader;
class FrsUserData;
class FrsUserCalData;

class FrsUserRaw2Cal : public FairTask
{
    public:
        FrsUserRaw2Cal();
        FrsUserRaw2Cal(const TString& name, Int_t verbose);

        ~FrsUserRaw2Cal();

        virtual InitStatus Init();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online) { fOnline = set_online; }

    private:
        Bool_t fOnline;

        TClonesArray* fCalArray;
        TClonesArray* fRawArray;

        FrsUserData* fRawHit;

        EventHeader* header;
        Int_t fNEvents = 0;

        const std::vector<uint32_t>* v7x5_geo;
        const std::vector<uint32_t>* v7x5_channel;
        const std::vector<uint32_t>* v7x5_data;

        uint32_t dt_array[16];
        uint32_t music_e1[8];
        uint32_t music_e2[8];

    public:
        ClassDef(FrsUserRaw2Cal, 1);
};

#endif