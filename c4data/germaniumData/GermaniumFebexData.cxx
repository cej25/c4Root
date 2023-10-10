#include "GermaniumFebexData.h"

GermaniumFebexData::GermaniumFebexData()
    : fnum_channels_fired(0),
      fevent_trigger_time(0),
      fhit_pattern(0),
      fboard_id(0),
      fpileup(0),
      foverflow(0),
      fchannel_id(0),
      fchannel_trigger_time(0),
      fchannel_energy(0),
      //fcrystal_id(0),
      //fdetector_id(0),
      fwr_subsystem_id(0),
      fwr_t(0)
{
}

GermaniumFebexData::GermaniumFebexData(
        uint32_t num_channels_fired,
        uint64_t event_trigger_time,
        uint16_t hit_pattern,
        uint8_t board_id,
        uint8_t pileup,
        uint8_t overflow,
        uint8_t channel_id,
        double channel_trigger_time,
        int32_t channel_energy, // from the FEBEX manual: bit 23 denotes the sign of the energy (i.e. negative pulses?)
        uint16_t wr_subsystem_id,
        uint64_t wr_t)
    : 
    fnum_channels_fired(num_channels_fired),
    fevent_trigger_time(event_trigger_time),
    fhit_pattern(hit_pattern),
    fboard_id(board_id),
    fpileup(pileup),
    foverflow(overflow),
    fchannel_id(channel_id),
    fchannel_trigger_time(channel_trigger_time),
    fchannel_energy(channel_energy),
    fwr_subsystem_id(wr_subsystem_id),
    fwr_t(wr_t)
{
}

ClassImp(GermaniumFebexData)