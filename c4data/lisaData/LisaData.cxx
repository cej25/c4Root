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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25.11.24                                     *
 ******************************************************************************/
#include "LisaData.h"

// This is the adjustment to use TVectors instead of std::vector
//This was to try to read vectors of vectors form external macro without sourcing c4. It does not work.
//template <typename T>
//using StdVector = std::vector<T>;

LisaItem::LisaItem()
{

}

void LisaItem::SetAll(uint64_t wr,
                    uint16_t id,
                    int b_id,
                    uint64_t ev_time,
                    int ch_id,
                    uint64_t ch_time,
                    bool p,
                    bool o,
                    float ch_energy,
                    int ch_id_tr,
                    std::vector<float> tr,
                    std::vector<int16_t> tr_x
                    )
{
    wr_t = wr;
    wr_id = id;
    board_id = b_id;
    board_event_time = ev_time;
    channel_id = ch_id;
    channel_time = ch_time;
    pileup = p;
    overflow = o;
    channel_energy = ch_energy;
    channel_id_traces = ch_id_tr;
    trace = tr;
    trace_x = tr_x;
}

void LisaItem::Reset()
{
    wr_t = 0;
    wr_id = 0;
    board_id = 0;
    board_event_time = 0;
    channel_id = 0;
    channel_time = 0;
    pileup = 0;
    overflow = 0;
    channel_energy = 0;
    channel_id = 0;
    trace = {};
    trace_x = {};
}

ClassImp(LisaItem)
