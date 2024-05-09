#ifndef FrsTravMusRaw2Cal_H
#define FrsTravMusRaw2Cal_H

#include <vector>
#include "TFolder.h"
#include "FrsTravMusData.h"
#include "FrsTravMusCalData.h"
#include "TFrsConfiguration.h"

class EventHeader;
class FrsTravMusAdcItem;
class FrsTravMusTdcItem;
class FrsTravMusCalItem;

class FrsTravMusRaw2Cal : public FairTask
{
    public:
        FrsTravMusRaw2Cal();
        FrsTravMusRaw2Cal(const TString& name, Int_t verbose);
        
        ~FrsTravMusRaw2Cal();

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

        std::vector<FrsTravMusAdcItem> const* adcArray;
        std::vector<FrsTravMusTdcItem> const* tdcArray;
        std::vector<FrsTravMusCalItem>* calArray;
        
        // init
        uint16_t* music_e;
        uint16_t* music_t;
        Float_t cMusic_E[8][2];
        Bool_t music_b_e[8];


    public:
        ClassDef(FrsTravMusRaw2Cal, 1);

};


#endif