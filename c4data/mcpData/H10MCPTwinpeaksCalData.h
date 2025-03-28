#ifndef H10MCPTwinpeaksCalData_H
#define H10MCPTwinpeaksCalData_H

#include "TObject.h"

class H10MCPTwinpeaksCalData : public TObject
{
    public:
        // Default Constructor
        H10MCPTwinpeaksCalData();

        H10MCPTwinpeaksCalData(
        uint16_t trig,
        uint16_t board_id,
        uint16_t ch_ID,
        uint16_t detector_id,
        
        int64_t slow_lead_epoch,
        double slow_lead_time,

        int64_t slow_trail_epoch,
        double slow_trail_time,


        int64_t fast_lead_epoch,
        double fast_lead_time,

        int64_t fast_trail_epoch,
        double fast_trail_time,


        double fast_ToT,
        double slow_ToT,
        
        double energy,

        uint16_t wr_subsystem_id,
        uint64_t wr_t,
        uint64_t absolute_event_time);

        // Destructor
        virtual ~H10MCPTwinpeaksCalData() {}

        // Getters
        inline const uint16_t Get_trigger() const { return ftrig; }
        inline const uint16_t Get_board_id() const {return fboard_id; }
        inline const uint16_t Get_ch_ID() const {return fch_ID; }
        inline const uint16_t Get_detector_id() const {return fdetector_id; }
        
        inline const int64_t Get_slow_lead_epoch() const {return fslow_lead_epoch; }
        inline const double Get_slow_lead_time() const {return fslow_lead_time; }
        
        inline const int64_t Get_slow_trail_epoch() const {return fslow_trail_epoch; }
        inline const double Get_slow_trail_time() const {return fslow_trail_time; }
        
        inline const int64_t Get_fast_lead_epoch() const {return ffast_lead_epoch; } 
        inline const double Get_fast_lead_time() const {return ffast_lead_time; }
        
        inline const int64_t Get_fast_trail_epoch() const {return ffast_trail_epoch; }
        inline const double Get_fast_trail_time() const {return ffast_trail_time; }

        inline const double Get_fast_ToT() const {return ffast_ToT; }
        inline const double Get_slow_ToT() const {return fslow_ToT; }
        inline const double Get_energy() const {return fenergy; }
        inline const uint16_t Get_wr_subsystem_id() const {return fwr_subsystem_id; }
        inline const uint64_t Get_wr_t() const {return fwr_t; }
        inline const uint64_t Get_absolute_event_time() const { return fabsolute_event_time; }


        // Setters
        void Set_trigger(uint16_t v) { ftrig = v; } 
        void Set_board_id(uint16_t v){ fboard_id = v; }
        void Set_ch_ID(uint16_t v){ fch_ID = v; }
        void Set_detector_id(uint16_t v){ fdetector_id = v; }
        
        void Set_slow_lead_epoch(int64_t v){ fslow_lead_epoch = v; }
        void Set_slow_lead_time(double v){ fslow_lead_time = v; }
        
        void Set_slow_trail_epoch(int64_t v){ fslow_trail_epoch = v; }
        void Set_slow_trail_time(double v){ fslow_trail_time = v; }
        
        void Set_fast_lead_epoch(int64_t v){ ffast_lead_epoch = v; }
        void Set_fast_lead_time(double v){ ffast_lead_time = v; }
        
        void Set_fast_trail_epoch(int64_t v){ ffast_trail_epoch = v; }
        void Set_fast_trail_time(double v){ ffast_trail_time = v; }

        void Set_fast_ToT(double v){ ffast_ToT = v; }
        void Set_slow_ToT(double v){ fslow_ToT = v; }
        void Set_energy(double v){ fenergy = v; }
        void Set_wr_subsystem_id(uint16_t v){ fwr_subsystem_id = v; }
        void Set_wr_t(uint64_t v){ fwr_t = v; }
        void Set_absolute_event_time(uint64_t v){ fabsolute_event_time = v; }


    protected:
        // Data items
        uint16_t ftrig;
        uint16_t fboard_id;
        uint16_t fch_ID;
        uint16_t fdetector_id;
        
        int64_t fslow_lead_epoch;
        double fslow_lead_time;
        int64_t fslow_trail_epoch;
        double fslow_trail_time;

        int64_t ffast_lead_epoch;
        double ffast_lead_time;
        int64_t ffast_trail_epoch;
        double ffast_trail_time;

        double ffast_ToT;
        double fslow_ToT;
        
        double fenergy;

        uint16_t fwr_subsystem_id;
        uint64_t fwr_t;
        uint64_t fabsolute_event_time;
    

    public:
        ClassDef(H10MCPTwinpeaksCalData, 1);
};

#endif
