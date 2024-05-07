#ifndef FrsUserRaw2Cal_H
#define FrsUserRaw2Cal_H

#include "TFRSParameter.h"
#include "FrsUserCalData.h"
#include "FrsUserData.h"
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

        void ZeroArrays();
        void ClearVectors();

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online) { fOnline = set_online; }

    private:
        Bool_t fOnline;

        TClonesArray* fCalArray;
        TClonesArray* fRawArray;

        std::vector<FrsUserV830Item> const* v830array;
        std::vector<FrsUserV7X5Item> const* v7x5array;
        std::vector<FrsUserCalScalerItem>* scalerArray;
        std::vector<FrsUserCalSciItem>* sciArray;
        std::vector<FrsUserCalMusicItem>* musicArray;


        FrsUserData* fRawHit;

        EventHeader* header;
        Int_t fNEvents = 0;

        std::vector<uint32_t>* v7x5_geo_user;
        std::vector<uint32_t>* v7x5_channel_user;
        std::vector<uint32_t>* v7x5_data_user;

        uint32_t* dt_array;
        uint32_t* music_e1;
        uint32_t* music_e2;

       /* uint32_t dt_array[16];
        uint32_t music_e1[8];
        uint32_t music_e2[8];*/

    public:
        ClassDef(FrsUserRaw2Cal, 1);
};

#endif