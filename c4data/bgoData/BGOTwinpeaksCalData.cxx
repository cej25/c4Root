#include "BGOTwinpeaksCalData.h"

BGOTwinpeaksCalData::BGOTwinpeaksCalData()
    :
    ftrig(0),
    fboard_id(0),
    fch_ID(0),
    
    fdetector_id(0),
    fcrystal_id(0),
    
    fslow_lead_time(0),
    fslow_trail_time(0),

    ffast_lead_time(0),
    ffast_trail_time(0),

    ffast_ToT(0),
    fslow_ToT(0),

    fenergy(0),

    fwr_subsystem_id(0),
    fwr_t(0)
{
}

BGOTwinpeaksCalData::BGOTwinpeaksCalData(
        uint16_t trig,
        uint16_t board_id,
        uint16_t ch_ID,
        
        int detector_id,
        int crystal_id,
        
        double slow_lead_time,
        double slow_trail_time,

        double fast_lead_time,
        double fast_trail_time,

        double fast_ToT,
        double slow_ToT,

        double energy,
        
        uint16_t wr_subsystem_id,
        uint64_t wr_t)
    : 
        ftrig(trig),
        fboard_id(board_id),
        fch_ID(ch_ID),
        fdetector_id(detector_id),
        fcrystal_id(crystal_id),
        fslow_lead_time(slow_lead_time),
        fslow_trail_time(slow_trail_time),
        ffast_lead_time(fast_lead_time),
        ffast_trail_time(fast_trail_time),
        ffast_ToT(fast_ToT),
        fslow_ToT(slow_ToT),
        fenergy(energy),
        fwr_subsystem_id(wr_subsystem_id),
        fwr_t(wr_t)
{
}

ClassImp(BGOTwinpeaksCalData)