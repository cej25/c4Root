#ifndef FrsRaw2Cal_H
#define FrsRaw2Cal_H

#include <vector>

class TClonesArray;
class EventHeader;
class FrsData;
class FrsCalData;

class FrsRaw2Cal : public FairTask
{
    public:
        FrsRaw2Cal();
        FrsRaw2Cal(const TString& name, Int_t verbose);
        
        ~FrsRaw2Cal();

        virtual InitStatus Init();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online) { fOnline = set_online; }


    private:
        Bool_t fOnline;

        TClonesArray* fCalArray;
        TClonesArray* fRawArray; // from FrsReader

        FrsData* fRawHit;

        uint32_t v830_scalers_n;
        std::vector<uint32_t> v830_scalers_index;
        std::vector<uint32_t> v830_scalers_main;
        
        uint32_t scaler_check_first_event = 1; // can we define it here? idk
        uint32_t scaler_ch_1kHz = 7; // main
        uint32_t sc_main_initial[32];
        uint32_t sc_main_previous[32];

        uint32_t time_in_ms;
        uint32_t ibin_for_s;
        uint32_t ibin_for_100ms;
        uint32_t extraction_time_ms;
        uint32_t ibin_clean_for_s;
        uint32_t ibin_clean_for_100ms;

        uint32_t v792_geo;
        std::vector<uint32_t> v792_data;
        std::vector<uint32_t> v792_channel;

        uint32_t de_41r;
        uint32_t de_21l;
        uint32_t de_21r;
        uint32_t de_42l; 
        uint32_t de_42r;
        uint32_t de_81l;
        uint32_t de_22r;
        uint32_t de_31l;
        uint32_t de_31r;
        uint32_t de_43l;
        uint32_t de_43r;
        uint32_t de_41l;
        uint32_t de_81r;
        uint32_t de_22l;

        uint32_t music_t1[8];
        uint32_t music_t2[8];
        
        std::vector<uint32_t> v1290_data;
        std::vector<uint32_t> v1290_channel;
        std::vector<uint32_t> v1290_lot;

        EventHeader* header;
        Int_t fNEvents = 0;

    public:
        ClassDef(FrsRaw2Cal, 1);

};


#endif