#ifndef H10MCPTwinpeaksCalData_H
#define H10MCPTwinpeaksCalData_H

#include "TObject.h"

class H10MCPTwinpeaksCalData : public TObject
{
    public:
        // Default Constructor
        H10MCPTwinpeaksCalData();

        H10MCPTwinpeaksCalData(
        UShort_t trig,
        UShort_t board_id,
        UShort_t ch_ID,
        Int_t mcp_id,
        Int_t type,
        Int_t number,
        
        Long64_t slow_lead_epoch,
        Double_t slow_lead_time,

        Long64_t slow_trail_epoch,
        Double_t slow_trail_time,

        Long64_t fast_lead_epoch,
        Double_t fast_lead_time,

        Long64_t fast_trail_epoch,
        Double_t fast_trail_time,

        Double_t fast_ToT,
        Double_t slow_ToT,
        
        Double_t energy,

        UShort_t wr_subsystem_id,
        Long64_t wr_t,
        Long64_t absolute_event_time);

        // Destructor
        virtual ~H10MCPTwinpeaksCalData() {}

        // Getters
        inline const UShort_t Get_trigger() const { return ftrig; }
        inline const UShort_t Get_board_id() const {return fboard_id; }
        inline const UShort_t Get_ch_ID() const {return fch_ID; }
        inline const Int_t Get_mcp_id() const {return fmcp_id; }
        inline const Int_t Get_type() const {return ftype; }
        inline const Int_t Get_number() const {return fnumber; }
        
        inline const int64_t Get_slow_lead_epoch() const {return fslow_lead_epoch; }
        inline const Double_t Get_slow_lead_time() const {return fslow_lead_time; }
        
        inline const int64_t Get_slow_trail_epoch() const {return fslow_trail_epoch; }
        inline const Double_t Get_slow_trail_time() const {return fslow_trail_time; }
        
        inline const int64_t Get_fast_lead_epoch() const {return ffast_lead_epoch; } 
        inline const Double_t Get_fast_lead_time() const {return ffast_lead_time; }
        
        inline const int64_t Get_fast_trail_epoch() const {return ffast_trail_epoch; }
        inline const Double_t Get_fast_trail_time() const {return ffast_trail_time; }

        inline const Double_t Get_fast_ToT() const {return ffast_ToT; }
        inline const Double_t Get_slow_ToT() const {return fslow_ToT; }
        inline const Double_t Get_energy() const {return fenergy; }
        inline const UShort_t Get_wr_subsystem_id() const {return fwr_subsystem_id; }
        inline const Long64_t Get_wr_t() const {return fwr_t; }
        inline const Long64_t Get_absolute_event_time() const { return fabsolute_event_time; }

        // Setters
        void Set_trigger(UShort_t v) { ftrig = v; } 
        void Set_board_id(UShort_t v){ fboard_id = v; }
        void Set_ch_ID(UShort_t v){ fch_ID = v; }
        
        void Set_slow_lead_epoch(Long64_t v){ fslow_lead_epoch = v; }
        void Set_slow_lead_time(Double_t v){ fslow_lead_time = v; }
        
        void Set_slow_trail_epoch(Long64_t v){ fslow_trail_epoch = v; }
        void Set_slow_trail_time(Double_t v){ fslow_trail_time = v; }
        
        void Set_fast_lead_epoch(Long64_t v){ ffast_lead_epoch = v; }
        void Set_fast_lead_time(Double_t v){ ffast_lead_time = v; }
        
        void Set_fast_trail_epoch(Long64_t v){ ffast_trail_epoch = v; }
        void Set_fast_trail_time(Double_t v){ ffast_trail_time = v; }

        void Set_fast_ToT(Double_t v){ ffast_ToT = v; }
        void Set_slow_ToT(Double_t v){ fslow_ToT = v; }
        void Set_energy(Double_t v){ fenergy = v; }
        void Set_wr_subsystem_id(UShort_t v){ fwr_subsystem_id = v; }
        void Set_wr_t(Long64_t v){ fwr_t = v; }
        void Set_absolute_event_time(Long64_t v){ fabsolute_event_time = v; }


    protected:
        // Data items
        UShort_t ftrig;
        UShort_t fboard_id;
        UShort_t fch_ID;
        Int_t fmcp_id;
        Int_t ftype;
        Int_t fnumber;
        
        Long64_t fslow_lead_epoch;
        Double_t fslow_lead_time;
        Long64_t fslow_trail_epoch;
        Double_t fslow_trail_time;

        Long64_t ffast_lead_epoch;
        Double_t ffast_lead_time;
        Long64_t ffast_trail_epoch;
        Double_t ffast_trail_time;

        Double_t ffast_ToT;
        Double_t fslow_ToT;
        
        Double_t fenergy;

        UShort_t fwr_subsystem_id;
        Long64_t fwr_t;
        Long64_t fabsolute_event_time;
    

    public:
        ClassDef(H10MCPTwinpeaksCalData, 1);
};

#endif
