#ifndef GermaniumFebexData_H
#define GermaniumFebexData_H

#include "TObject.h"

class GermaniumFebexData : public TObject
{
    public:
        // Default Constructor
        GermaniumFebexData();

        GermaniumFebexData(  uint32_t num_channels_fired,
                             uint64_t event_trigger_time,
                             uint16_t hit_pattern,
                             uint8_t board_id,
                             uint8_t pileup,
                             uint8_t overflow,
                             uint8_t channel_id,
                             double channel_trigger_time,
                             int32_t channel_energy,
                             //double channel_energy_cal,
                             //uint32_t crystal_id,
                             //uint32_t detector_id,

                             //whiterabbit timestamps:
                             uint16_t wr_subsystem_id,
                             uint64_t wr_t
                             );

        // Destructor
        virtual ~GermaniumFebexData() {};

        // Getters
        inline const uint32_t Get_num_channels_fired() const { return fnum_channels_fired; }
        inline const uint64_t Get_event_trigger_time() const { return fevent_trigger_time; }
        inline const uint16_t Get_hit_pattern() const { return fhit_pattern; }
        inline const uint8_t Get_board_id() const { return fboard_id; }
        inline const uint8_t Get_pileup() const { return fpileup; }
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
        void Set_num_channels_fired(uint32_t v) { fnum_channels_fired = v; }
        void Set_event_trigger_time(uint64_t v) { fevent_trigger_time = v; }
        void Set_hit_pattern(uint16_t v) { fhit_pattern = v; }
        void Set_board_id(uint8_t v) { fboard_id = v; }
        void Set_pileup(uint8_t v) { fpileup = v; }
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
        
        uint32_t fnum_channels_fired;
        uint64_t fevent_trigger_time;
        uint16_t fhit_pattern;
        uint8_t fboard_id;
        uint8_t fpileup;
        uint8_t foverflow;
        uint8_t fchannel_id;
        double fchannel_trigger_time;
        int32_t fchannel_energy;
        //double fchannel_energy_cal;
        //uint32_t fcrystal_id;
        //uint32_t fdetector_id;

        //whiterabbit
        uint32_t fwr_subsystem_id;
        uint32_t fwr_t;
    

    public:
        ClassDef(GermaniumFebexData, 1);
};

#endif
