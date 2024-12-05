#ifndef FrsMainRaw2Cal_H
#define FrsMainRaw2Cal_H


#include "TFrsConfiguration.h"

#include <vector>
#include "TFolder.h"
#include "FrsMainData.h"
#include "FrsMainCalData.h"

class TClonesArray;
class EventHeader;

class FrsMainRaw2Cal : public FairTask
{
    public:
        FrsMainRaw2Cal();
        FrsMainRaw2Cal(const TString& name, Int_t verbose);
        
        ~FrsMainRaw2Cal();

        virtual InitStatus Init();

        void Exec(Option_t* option);

        void ZeroArrays();
        void ClearVectors();

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online) { fOnline = set_online; }


    private:
        Bool_t fOnline;

        TFrsConfiguration const* frs_config;        
        
        std::vector<FrsMainV830Item> const* v830array;
        std::vector<FrsMainV792Item> const* v792array;
        std::vector<FrsMainV1290Item> const* v1290array;
        std::vector<FrsMainCalScalerItem>* scalerArray;
        std::vector<FrsMainCalSciItem>* sciArray;
        std::vector<FrsMainCalMusicItem>* musicArray;

        uint64_t WR_TS;

        uint32_t v830_scalers_n;
        std::vector<uint32_t> v830_scalers_index;
        std::vector<uint32_t> v830_scalers_main;
        
        uint32_t scaler_check_first_event = 1; // can we define it here? idk
        uint32_t scaler_ch_1kHz = 7; // main -- can we .config this?
        uint32_t sc_main_initial[32];
        uint32_t sc_main_previous[32];
        uint32_t increase_scaler_temp[32]; // main?

        uint32_t time_in_ms;
        uint32_t ibin_for_s;
        uint32_t ibin_for_100ms;
        uint32_t extraction_time_ms;
        uint32_t ibin_clean_for_s;
        uint32_t ibin_clean_for_100ms;

        uint32_t v792_geo;
        std::vector<uint32_t> v792_data;
        std::vector<uint32_t> v792_channel;

        std::vector<uint32_t> v1290_data;
        std::vector<uint32_t> v1290_channel;
        std::vector<uint32_t> v1290_lot;


        EventHeader* header;
        Int_t fNEvents = 0;

        uint32_t* de;
        uint32_t* music_t1;
        uint32_t* music_t2;

        const int max_hits_in_v1290 = 100;

    
        uint32_t de_21l = 0;
        uint32_t de_21r = 0;
        uint32_t de_22l = 0;
        uint32_t de_22r = 0;
        uint32_t de_31l = 0;
        uint32_t de_31r = 0;
        uint32_t de_41l = 0;
        uint32_t de_41r = 0;
        uint32_t de_42l = 0;
        uint32_t de_42r = 0;
        uint32_t de_43l = 0;
        uint32_t de_43r = 0;
        uint32_t de_81l = 0;
        uint32_t de_81r = 0;




    public:
        ClassDef(FrsMainRaw2Cal, 1);

};


#endif