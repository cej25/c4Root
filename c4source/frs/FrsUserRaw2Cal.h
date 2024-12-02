#ifndef FrsUserRaw2Cal_H
#define FrsUserRaw2Cal_H

#include "TFrsConfiguration.h"
#include "TFRSParameter.h"
#include "FrsUserCalData.h"
#include "FrsUserData.h"
#include <vector>

class TClonesArray;
class EventHeader;


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
        TFrsConfiguration const* frs_config;

        Bool_t fOnline;

        std::vector<FrsUserV830Item> const* v830array;
        std::vector<FrsUserV7X5Item> const* v7x5array;
        std::vector<FrsUserCalScalerItem>* scalerArray;
        std::vector<FrsUserCalSciItem>* sciArray;
        std::vector<FrsUserCalMusicItem>* musicArray;

        EventHeader* header;
        Int_t fNEvents = 0;

        std::vector<uint32_t>* v7x5_geo_user;
        std::vector<uint32_t>* v7x5_channel_user;
        std::vector<uint32_t>* v7x5_data_user;

        uint32_t* dt_array;
        uint32_t* music_e1;
        uint32_t* music_e2;

        uint32_t dt_21l_21r;
        uint32_t dt_41l_41r;
        uint32_t dt_42l_42r;
        uint32_t dt_43l_43r;
        uint32_t dt_81l_81r;
        uint32_t dt_21l_41l;
        uint32_t dt_21r_41r;
        uint32_t dt_42r_21r;
        uint32_t dt_42l_21l;
        uint32_t dt_21l_81l;
        uint32_t dt_21r_81r;
        uint32_t dt_22l_22r;
        uint32_t dt_22l_41l;
        uint32_t dt_22r_41r;
        uint32_t dt_22l_81l;
        uint32_t dt_22r_81r;

    public:
        ClassDef(FrsUserRaw2Cal, 1);
};

#endif