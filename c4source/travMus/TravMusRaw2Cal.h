#ifndef TravMusRaw2Cal_H
#define TravMusRaw2Cal_H

#include <vector>
#include "TFolder.h"
#include "TravMusData.h"
#include "TravMusCalData.h"
#include "TFrsConfiguration.h"

class EventHeader;
class TravMusAdcItem;
class TravMusTdcItem;
class TravMusCalItem;

class TravMusRaw2Cal : public FairTask
{
    public:
        TravMusRaw2Cal();
        TravMusRaw2Cal(const TString& name, Int_t verbose);
        
        ~TravMusRaw2Cal();

        virtual InitStatus Init();

        void Exec(Option_t* option);

        void ZeroArrays();
        void ClearVectors();

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online) { fOnline = set_online; }


    private:
        Bool_t fOnline;
        EventHeader* header;
        Int_t fNEvents;

        std::vector<TravMusAdcItem> const* adcArray;
        std::vector<TravMusTdcItem> const* tdcArray;
        std::vector<TravMusCalItem>* calArray;
        
        // init
        uint16_t* music_e;
        uint16_t* music_t;
        Float_t cMusic_E[8][2];
        Bool_t music_b_e[8];


    public:
        ClassDef(TravMusRaw2Cal, 1);

};


#endif