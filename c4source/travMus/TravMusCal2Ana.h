#ifndef TravMusCal2Ana_H
#define TravMusCal2Ana_H

#include <vector>
#include "TravMusCalData.h"
#include "TravMusAnaData.h"
#include "TFrsConfiguration.h"
#include "TFRSParameter.h"

class EventHeader;
class TravMusAdcItem;
class TravMusTdcItem;
class TravMusCalItem;

class TravMusCal2Ana : public FairTask
{
    public:
        TravMusCal2Ana();
        TravMusCal2Ana(const TString& name, Int_t verbose);
        
        ~TravMusCal2Ana();

        virtual InitStatus Init();

        void Exec(Option_t* option);

        void ZeroArrays();
        void ClearVectors();

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online) { fOnline = set_online; }


    private:
        TFrsConfiguration const* frs_config;
        TMUSICParameter* music;

        Bool_t fOnline;
        EventHeader* header;
        Int_t fNEvents;

        std::vector<TravMusCalItem> const* travMusArray;
        std::vector<TravMusAnaItem>* anaArray;

        uint16_t travmusic_e[8];
        uint16_t travmusic_t[8];
        
        Float_t de_travmus;
        Float_t de_cor_travmus;
        Bool_t b_de_travmus;
        Int_t travmusic_anodes_cnt;
        Bool_t travmusic_b_e[8] = {0};


    public:
        ClassDef(TravMusCal2Ana, 1);

};


#endif