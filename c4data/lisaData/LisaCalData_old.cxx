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

#include "LisaCalData.h"
#include "TString.h"

//Debugging. Replaced std::string with TString nov24


LisaCalData::LisaCalData()
{

}

LisaCalItem::LisaCalItem()
{

}

void LisaCalItem::SetAll(uint64_t wr,
                        int layer,
                        TString c,
                        int xpos,
                        int ypos,
                        int e,
                        std::vector<uint16_t> tr,
                        double e_GM,
                        uint64_t evt_t,
                        uint64_t ch_t,
                        uint64_t evtno,
                        int pu,
                        int ov
                        )
{   
    wr_t = wr;
    layer_id = layer;
    city = c;
    xposition = xpos;
    yposition = ypos;
    energy = e;
    trace = tr;
    energy_GM = e_GM;
    board_event_time = evt_t;
    ch_event_time = ch_t;
    event_no = evtno;
    pileup = pu;
    overflow = ov;
}


void LisaCalItem::Reset()
{   
    // maybe reset stuff to -1 since 0 is used occasionally for positions
    wr_t = 0;
    layer_id = 0;
    city = "";
    xposition = 0;
    yposition = 0;
    energy = 0;
    trace = {};
    event_no = 0;
    energy_GM = 0;
    board_event_time = 0;
    ch_event_time = 0;
    pileup = 0;
    overflow = 0;

}

ClassImp(LisaCalData)