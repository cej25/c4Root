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
 *                              C.E. Jones                                    *
 *                               06.05.25                                     *
 ******************************************************************************/

#include "H10MCPTwinpeaksCalData.h"

H10MCPTwinpeaksCalData::H10MCPTwinpeaksCalData()
    :
    ftrig(0),
    fboard_id(0),
    fch_ID(0),
    fmcp_id(0),
    ftype(0),
    fnumber(0),
    
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
        UShort_t trig,
        UShort_t board_id,
        UShort_t ch_ID,
        Int_t mcp_id,
        Int_t type,
        Int_t number,
        
        Long64_t slow_lead_epoch,
        Double_t slow_lead_time,

        Long64_t slow_trail_epoch,
        Double_t slow_trail_time,

        Long64_t fast_lead_epoch,
        Double_t fast_lead_time,

        Long64_t fast_trail_epoch,
        Double_t fast_trail_time,

        Double_t fast_ToT,
        Double_t slow_ToT,
        
        Double_t energy,

        UShort_t wr_subsystem_id,
        Long64_t wr_t,
        Long64_t absolute_event_time)
    : 
        ftrig(trig),
        fboard_id(board_id),
        fch_ID(ch_ID),
        fmcp_id(mcp_id),
        ftype(type),
        fnumber(number),
        
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