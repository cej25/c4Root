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

#include "v1751TraceData.h"

v1751TraceData::v1751TraceData()
    : 
      fnum_channels_fired(0),
      fboard_id(0),
      fchannel_id(0),
      fwr_subsystem_id(0),
      fwr_t(0)
{
    flength = 0;
    for (int i = 0; i<VMEV1751_TRACE_SIZE; i++){
        trace[i] = 0;
    }
}

v1751TraceData::v1751TraceData(
        uint32_t num_channels_fired,
        uint8_t board_id,
        uint8_t channel_id,
        uint16_t wr_subsystem_id,
        uint64_t wr_t)
    : 
    fnum_channels_fired(num_channels_fired),
    fboard_id(board_id),
    fchannel_id(channel_id),
    fwr_subsystem_id(wr_subsystem_id),
    fwr_t(wr_t)
{
    flength = 0;
    for (int i = 0; i<VMEV1751_TRACE_SIZE; i++){
        trace[i] = 0;
    }
}

ClassImp(v1751TraceData)
