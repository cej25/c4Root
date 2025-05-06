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
 *                               C.E. Jones                                   *
 *                                06.05.25                                    *
 ******************************************************************************/

#include "BB7FebexData.h"

BB7FebexItem::BB7FebexItem()
{
}

void BB7FebexItem::SetAll(Long64_t wr,
                        UShort_t id,
                        Int_t cr_id,
                        UInt_t b_id,
                        ULong64_t ev_time,
                        UInt_t ch_id,
                        ULong64_t ch_time,
                        Bool_t p,
                        Bool_t o,
                        UInt_t ch_energy,
                        UInt_t ch_id_tr,
                        std::vector<UShort_t> tr)
{
    wr_t = wr;
    wr_id = id;
    crate_id = cr_id;
    board_id = b_id;
    board_event_time = ev_time;
    channel_id = ch_id;
    channel_time = ch_time;
    pileup = p;
    overflow = o;
    channel_energy = ch_energy;
    channel_id_traces = ch_id_tr;
    trace = tr;
}

void BB7FebexItem::Reset()
{
    wr_t = 0;
    wr_id = 0;
    crate_id = 0; // -1?
    board_id = 0;
    board_event_time = 0;
    channel_id = 0;
    channel_time = 0;
    pileup = 0;
    overflow = 0;
    channel_energy = 0;
    channel_id = 0;
    trace = {};
}

ClassImp(BB7FebexItem)


BB7EmptyItem::BB7EmptyItem() {}

void BB7EmptyItem::SetAll(Long64_t wr,
                    UShort_t id,
                    Int_t cr_id,
                    UInt_t b_id,
                    ULong64_t ev_time)
{
    wr_t = wr;
    wr_id = id;
    crate_id = cr_id;
    board_id = b_id;
    board_event_time = ev_time;
}