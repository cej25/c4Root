#ifndef FrsMainRaw2Cal_H
#define FrsMainRaw2Cal_H

#include <vector>
#include "TFolder.h"

class TClonesArray;
class EventHeader;
class FrsMainData;
class FrsMainCalData;

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

        TClonesArray* fCalArray;
        TClonesArray* fRawArray; // from FrsReader

        FrsMainData* fRawHit;

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

        uint32_t de_array[14];
        std::vector<uint32_t> v1290_data;
        std::vector<uint32_t> v1290_channel;
        std::vector<uint32_t> v1290_lot;

        std::vector<uint32_t> tdc_array[15];
        uint32_t music_t1[8];
        uint32_t music_t2[8];
        
        EventHeader* header;
        Int_t fNEvents = 0;


    public:
        ClassDef(FrsMainRaw2Cal, 1);

};


#endif