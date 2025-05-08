/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                             J.E.L. Larsson                                 *
 *                                06.05.25                                    *
 ******************************************************************************/

#include "GermaniumFebexData.h"

GermaniumFebexData::GermaniumFebexData()
    : 
        ftrig(0),
        fnum_channels_fired(0),
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
        uint16_t trig,
        uint32_t num_channels_fired,
        uint64_t event_trigger_time,
        uint16_t hit_pattern,
        uint8_t board_id,
        bool pileup,
        uint8_t overflow,
        uint8_t channel_id,
        double channel_trigger_time,
        int32_t channel_energy, // from the FEBEX manual: bit 23 denotes the sign of the energy (i.e. negative pulses?)
        uint16_t wr_subsystem_id,
        uint64_t wr_t)
    : 
    ftrig(trig),
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


GermaniumFebexTraceData::GermaniumFebexTraceData()
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
    for (int i = 0; i < MAX_TRACE_LENGTH; i++) ftrace[i] = 0;
}

GermaniumFebexTraceData::GermaniumFebexTraceData(
        uint32_t num_channels_fired,
        uint64_t event_trigger_time,
        uint16_t hit_pattern,
        uint8_t board_id,
        bool pileup,
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
    for (int i = 0; i < MAX_TRACE_LENGTH; i++) ftrace[i] = 0;
}

ClassImp(GermaniumFebexTraceData)