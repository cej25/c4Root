#include "H10MCPTwinpeaksCalData.h"

H10MCPTwinpeaksCalData::H10MCPTwinpeaksCalData()
    :
    ftrig(0),
    fboard_id(0),
    fch_ID(0),
    fdetector_id(0),
    
    fslow_lead_epoch(0),
    fslow_lead_time(0),
    fslow_trail_epoch(0),
    fslow_trail_time(0),

    ffast_lead_epoch(0),
    ffast_lead_time(0),
    ffast_trail_epoch(0),
    ffast_trail_time(0),

    ffast_ToT(0),
    fslow_ToT(0),

    fenergy(0),

    fwr_subsystem_id(0),
    fwr_t(0),
    fabsolute_event_time(0)
{
}

H10MCPTwinpeaksCalData::H10MCPTwinpeaksCalData(
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
        uint64_t absolute_event_time)
    : 
        ftrig(trig),
        fboard_id(board_id),
        fch_ID(ch_ID),
        fdetector_id(detector_id),
        
        fslow_lead_epoch(slow_lead_epoch),
        fslow_lead_time(slow_lead_time),
        fslow_trail_epoch(slow_trail_epoch),
        fslow_trail_time(slow_trail_time),
        ffast_lead_epoch(fast_lead_epoch),
        ffast_lead_time(fast_lead_time),
        ffast_trail_epoch(fast_trail_epoch),
        ffast_trail_time(fast_trail_time),
        ffast_ToT(fast_ToT),
        fslow_ToT(slow_ToT),
        fenergy(energy),
        fwr_subsystem_id(wr_subsystem_id),
        fwr_t(wr_t),
        fabsolute_event_time(absolute_event_time)
{
}

ClassImp(H10MCPTwinpeaksCalData)