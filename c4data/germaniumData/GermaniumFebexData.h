#ifndef GermaniumFebexData_H
#define GermaniumFebexData_H

#include "TObject.h"

class GermaniumFebexData : public TObject
{
    public:
        // Default Constructor
        GermaniumFebexData();

        GermaniumFebexData( 
                            uint16_t trig, 
                            uint32_t num_channels_fired,
                             uint64_t event_trigger_time,
                             uint16_t hit_pattern,
                             uint8_t board_id,
                             bool pileup,
                             uint8_t overflow,
                             uint8_t channel_id,
                             double channel_trigger_time,
                             int32_t channel_energy,
                             uint16_t wr_subsystem_id,
                             uint64_t wr_t
                             );

        // Destructor
        virtual ~GermaniumFebexData() {};

        // Getters
        inline const uint16_t Get_trigger() const { return ftrig; }
        inline const uint32_t Get_num_channels_fired() const { return fnum_channels_fired; }
        inline const uint64_t Get_event_trigger_time() const { return fevent_trigger_time; }
        inline const uint16_t Get_hit_pattern() const { return fhit_pattern; }
        inline const uint8_t Get_board_id() const { return fboard_id; }
        inline const bool Get_pileup() const { return fpileup; }
        inline const uint8_t Get_overflow() const { return foverflow; }
        inline const uint8_t Get_channel_id() const { return fchannel_id; }
        inline const double Get_channel_trigger_time() const { return fchannel_trigger_time; }
        inline const int32_t Get_channel_energy() const { return fchannel_energy; }
        //inline const double Get_channel_energy_cal() const { return fchannel_energy_cal; }
        //inline const uint32_t Get_crystal_id() const { return fcrystal_id; }
        //inline const uint32_t Get_detector_id() const { return fdetector_id; }
        inline const uint16_t Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        inline const uint64_t Get_wr_t() const { return fwr_t; }



        // Setters
        void Set_trigger(uint16_t v) { ftrig = v; }
        void Set_num_channels_fired(uint32_t v) { fnum_channels_fired = v; }
        void Set_event_trigger_time(uint64_t v) { fevent_trigger_time = v; }
        void Set_hit_pattern(uint16_t v) { fhit_pattern = v; }
        void Set_board_id(uint8_t v) { fboard_id = v; }
        void Set_pileup(bool v) { fpileup = v; }
        void Set_overflow(uint8_t v) { foverflow = v; }
        void Set_channel_id(uint8_t v) { fchannel_id = v; }
        void Set_channel_trigger_time(double v) { fchannel_trigger_time = v; }
        void Set_channel_energy(int32_t v) { fchannel_energy = v; }
        //void Set_channel_energy_cal(double v) { fchannel_energy_cal = v; }
        //void Set_crystal_id(uint32_t v) { fcrystal_id = v; }
        //void Set_detector_id(uint32_t v) { fdetector_id = v; }
        void Set_wr_subsystem_id(uint32_t v) { fwr_subsystem_id = v; }
        void Set_wr_t(uint64_t v) { fwr_t = v; }

    protected:
        // Data items
        uint16_t ftrig;
        uint32_t fnum_channels_fired;
        uint64_t fevent_trigger_time;
        uint16_t fhit_pattern;
        uint8_t fboard_id;
        bool fpileup;
        uint8_t foverflow;
        uint8_t fchannel_id;
        double fchannel_trigger_time;
        int32_t fchannel_energy;
        //double fchannel_energy_cal;
        //uint32_t fcrystal_id;
        //uint32_t fdetector_id;

        //whiterabbit
        uint32_t fwr_subsystem_id;
        uint64_t fwr_t;
    

    public:
        ClassDef(GermaniumFebexData, 1);
};


const int MAX_TRACE_LENGTH = 4000;

class GermaniumFebexTraceData : public TObject
{
    public:
        // Default Constructor
        GermaniumFebexTraceData();

        GermaniumFebexTraceData(  uint32_t num_channels_fired,
                             uint64_t event_trigger_time,
                             uint16_t hit_pattern,
                             uint8_t board_id,
                             bool pileup,
                             uint8_t overflow,
                             uint8_t channel_id,
                             double channel_trigger_time,
                             int32_t channel_energy,
                             uint16_t wr_subsystem_id,
                             uint64_t wr_t
                             );

        // Destructor
        virtual ~GermaniumFebexTraceData() {};

        // Getters
        inline const uint32_t Get_num_channels_fired() const { return fnum_channels_fired; }
        inline const uint64_t Get_event_trigger_time() const { return fevent_trigger_time; }
        inline const uint16_t Get_hit_pattern() const { return fhit_pattern; }
        inline const uint8_t Get_board_id() const { return fboard_id; }
        inline const bool Get_pileup() const { return fpileup; }
        inline const uint8_t Get_overflow() const { return foverflow; }
        inline const uint8_t Get_channel_id() const { return fchannel_id; }
        inline const double Get_channel_trigger_time() const { return fchannel_trigger_time; }
        inline const int32_t Get_channel_energy() const { return fchannel_energy; }
        //inline const double Get_channel_energy_cal() const { return fchannel_energy_cal; }
        //inline const uint32_t Get_crystal_id() const { return fcrystal_id; }
        //inline const uint32_t Get_detector_id() const { return fdetector_id; }
        inline const uint16_t Get_wr_subsystem_id() const { return fwr_subsystem_id; }
        inline const uint64_t Get_wr_t() const { return fwr_t; }


        inline const int32_t Get_trace_value(int index) {return ftrace[index];}



        // Setters
        void Set_num_channels_fired(uint32_t v) { fnum_channels_fired = v; }
        void Set_event_trigger_time(uint64_t v) { fevent_trigger_time = v; }
        void Set_hit_pattern(uint16_t v) { fhit_pattern = v; }
        void Set_board_id(uint8_t v) { fboard_id = v; }
        void Set_pileup(bool v) { fpileup = v; }
        void Set_overflow(uint8_t v) { foverflow = v; }
        void Set_channel_id(uint8_t v) { fchannel_id = v; }
        void Set_channel_trigger_time(double v) { fchannel_trigger_time = v; }
        void Set_channel_energy(int32_t v) { fchannel_energy = v; }
        //void Set_channel_energy_cal(double v) { fchannel_energy_cal = v; }
        //void Set_crystal_id(uint32_t v) { fcrystal_id = v; }
        //void Set_detector_id(uint32_t v) { fdetector_id = v; }
        void Set_wr_subsystem_id(uint32_t v) { fwr_subsystem_id = v; }
        void Set_wr_t(uint64_t v) { fwr_t = v; }
        
        void Set_trace_value(int32_t v, int index) {ftrace[index] = v;}

    protected:
        // Data items
        
        uint32_t fnum_channels_fired;
        uint64_t fevent_trigger_time;
        uint16_t fhit_pattern;
        uint8_t fboard_id;
        bool fpileup;
        uint8_t foverflow;
        uint8_t fchannel_id;
        double fchannel_trigger_time;
        int32_t fchannel_energy;

        int32_t ftrace[MAX_TRACE_LENGTH];
        
        

        

        //whiterabbit
        uint32_t fwr_subsystem_id;
        uint64_t fwr_t;
    

    public:
        ClassDef(GermaniumFebexTraceData, 1);
};

#endif
