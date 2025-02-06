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
 *                               25.11.24                                    *
 ******************************************************************************/

#include "LisaAnaData.h"

// LisaAnaData::LisaAnaData()
// {

// }

LisaAnaItem::LisaAnaItem()
{

}

void LisaAnaItem::SetAll(uint64_t wr,
                    uint16_t id,
                    uint8_t b_id,
                    uint64_t ev_time,
                    uint8_t ch_id,
                    uint64_t ch_time,
                    int p,
                    //int p_MWD,
                    int o,
                    //int o_MWD,
                    uint32_t ch_energy,
                    uint32_t ch_energy_MWD,
                    uint8_t ch_id_tr,
                    std::vector<int16_t> tr,
                    std::vector<int16_t> tr_MWD,
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
    //pileup_MWD = p_MWD;
    overflow = o;
    //overflow_MWD = o_MWD;
    channel_energy = ch_energy;
    channel_energy_MWD = ch_energy_MWD;
    channel_id_traces = ch_id_tr;
    trace_febex = tr;
    trace_MWD = tr_MWD;
    trace_x = tr_x;
}


void LisaAnaItem::Reset()
{   
    // maybe reset stuff to -1 since 0 is used occasionally for positions
    wr_t = 0;
    wr_id = 0;
    board_id = 0;
    board_event_time = 0;
    channel_id = 0;
    channel_time = 0;
    pileup = 0;
    //pileup_MWD = 0;
    overflow = 0;
    //overflow_MWD = 0;
    channel_energy = 0;
    channel_energy_MWD = 0;
    channel_id = 0;
    trace_febex = {};
    trace_MWD = {};
    trace_x = {};

}

ClassImp(LisaAnaItem)