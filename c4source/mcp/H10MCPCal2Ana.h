#ifndef H10MCPCal2Ana_H
#define H10MCPCal2Ana_H

#include "FairTask.h"
#include "H10MCPTwinpeaksCalData.h"
#include "H10MCPTwinpeaksAnaData.h"
#include "TClonesArray.h"

class TClonesArray;
class EventHeader;
class TimeMachineData;

class H10MCPCal2Ana : public FairTask
{
    public:
        H10MCPCal2Ana();

        H10MCPCal2Ana(const TString& name, Int_t verbose);

        ~H10MCPCal2Ana();

        void Exec(Option_t* option);

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online){fOnline = set_online;}

        virtual InitStatus Init();


    private:

        TClonesArray* fcal_data;
        TClonesArray* fana_data;

        Bool_t fOnline;

        Long64_t absolute_event_time = 0;
        Long64_t wr_t = 0;
        Int_t t1_discard = 0;
        Int_t x11_discard = 0;
        Int_t x12_discard = 0;
        Int_t y11_discard = 0;
        Int_t y12_discard = 0;
        Int_t t2_discard = 0;
        Int_t x21_discard = 0;
        Int_t x22_discard = 0;
        Int_t y21_discard = 0;
        Int_t y22_discard = 0;
        Bool_t t1_seen = false;
        Bool_t x11_seen = false;
        Bool_t x12_seen = false;
        Bool_t y11_seen = false;
        Bool_t y12_seen = false;
        Bool_t t2_seen = false;
        Bool_t x21_seen = false;
        Bool_t x22_seen = false;
        Bool_t y21_seen = false;
        Bool_t y22_seen = false;
        Bool_t full_event = false;
        Bool_t mcp1_complete = false;
        Bool_t mcp2_complete = false;
        Double_t T1 = 0;
        Double_t X11 = 0;
        Double_t X12 = 0;
        Double_t Y11 = 0;
        Double_t Y12 = 0;
        Double_t T2 = 0;
        Double_t X21 = 0;
        Double_t X22 = 0;
        Double_t Y21 = 0;
        Double_t Y22 = 0;
        Int_t full_event_counter = 0;

    
        EventHeader * header;
        Int_t fNEvents = 0;
        Int_t fExecs = 0;
        int total_time_microsecs = 0;


    public:
        ClassDef(H10MCPCal2Ana, 1);
};

#endif

