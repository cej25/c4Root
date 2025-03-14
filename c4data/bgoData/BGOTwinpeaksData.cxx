#include "BGOTwinpeaksData.h"

BGOTwinpeaksData::BGOTwinpeaksData()
    : 
    ftrig(0),
    fboard_id(0),
    fch_ID(0),
    faccepted_trigger_time(0),
    faccepted_lead_epoch_counter(0),
    faccepted_lead_coarse_T(0),
    faccepted_lead_fine_T(0),
    flead_epoch_counter(0),
    flead_coarse_T(0),
    flead_fine_T(0),
    ftrail_epoch_counter(0),
    ftrail_coarse_T(0),
    ftrail_fine_T(0),
    fwr_subsystem_id(0),
    fwr_t(0)
{
}

BGOTwinpeaksData::BGOTwinpeaksData(
        uint16_t trig,
        uint16_t board_id,
        uint32_t ch_ID,

        int64_t accepted_trigger_time,
        uint32_t accepted_lead_epoch_counter,
        uint32_t accepted_lead_coarse_T,
        double accepted_lead_fine_T,

        uint32_t lead_epoch_counter,
        uint32_t lead_coarse_T,
        double lead_fine_T,

        uint32_t trail_epoch_counter,
        uint32_t trail_coarse_T,
        double trail_fine_T,
        uint16_t wr_subsystem_id,
        uint64_t wr_t)
    : 
    ftrig(trig),
    fboard_id(board_id),
    fch_ID(ch_ID),
    faccepted_trigger_time(accepted_trigger_time),
    faccepted_lead_epoch_counter(accepted_lead_epoch_counter),
    faccepted_lead_coarse_T(accepted_lead_coarse_T),
    faccepted_lead_fine_T(accepted_lead_fine_T),
    flead_epoch_counter(lead_epoch_counter),
    flead_coarse_T(lead_coarse_T),
    flead_fine_T(lead_fine_T),
    ftrail_epoch_counter(trail_epoch_counter),
    ftrail_coarse_T(trail_coarse_T),
    ftrail_fine_T(trail_fine_T),
    fwr_subsystem_id(wr_subsystem_id),
    fwr_t(wr_t)
{
}

ClassImp(BGOTwinpeaksData)