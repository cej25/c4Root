#include "bPlastTwinpeaksData.h"

bPlastTwinpeaksData::bPlastTwinpeaksData()
    : 
    fboard_id(0),
    fch_ID(0),
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

bPlastTwinpeaksData::bPlastTwinpeaksData(
        uint16_t board_id,
        uint32_t ch_ID,
        uint32_t lead_epoch_counter,
        uint32_t lead_coarse_T,
        double lead_fine_T,

        uint32_t trail_epoch_counter,
        uint32_t trail_coarse_T,
        double trail_fine_T,
        uint16_t wr_subsystem_id,
        uint64_t wr_t)
    : 
    fboard_id(board_id),
    fch_ID(ch_ID),
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

ClassImp(bPlastTwinpeaksData)