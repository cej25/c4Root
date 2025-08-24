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
 *                                 08.25                                      *
 ******************************************************************************/

#include "LisaCalData.h"
#include "TString.h"
#include "TVector.h"

// This is the adjustment to use TVectors instead of std::vector
//This was to try to read vectors of vectors form external macro without sourcing c4. It does not work.
//template <typename T>
//using StdVector = std::vector<T>;

//Debugging. Replaced std::string with TString nov24


LisaCalItem::LisaCalItem()
{

}

void LisaCalItem::SetAll(uint64_t wr,
                        uint16_t w_id,
                        int b_id,
                        int layer,
                        TString c,
                        int xpos,
                        int ypos,
                        float e,
                        float e_MWD,
                        std::vector<float> tr,
                        //std::vector<int16_t> tr_MWD,
                        std::vector<int16_t> tr_x,
                        float e_GM,
                        float e_MWD_GM,
                        float dedx,
                        float dedx_GM,
                        uint64_t evt_t,
                        uint64_t ch_t,
                        uint64_t evtno,
                        int pu,
                        //int pu_MWD,
                        int ov
                        //int ov_MWD
                        )
{   
    wr_t = wr;
    wr_id = w_id;
    board_id = b_id;
    layer_id = layer;
    city = c;
    xposition = xpos;
    yposition = ypos;
    energy = e;
    energy_MWD = e_MWD;
    trace_febex = tr;
    //trace_MWD = tr_MWD;
    trace_x = tr_x;
    energy_GM = e_GM;
    energy_MWD_GM = e_MWD_GM;
    de_dx = dedx;
    de_dx_GM = dedx_GM;
    board_event_time = evt_t;
    ch_event_time = ch_t;
    event_no = evtno;
    pileup = pu;
    //pileup_MWD = pu;
    overflow = ov;
    //overflow_MWD = ov_MWD;
}


void LisaCalItem::Reset()
{   
    // maybe reset stuff to -1 since 0 is used occasionally for positions
    wr_t = 0;
    wr_id = 0;
    board_id = 0; //reset to -1
    layer_id = 0;
    city = "";
    xposition = 0;
    yposition = 0;
    energy = 0;
    energy_MWD = 0;
    trace_febex = {};
    //trace_MWD = {};
    trace_x = {};
    event_no = 0;
    energy_GM = 0;
    energy_MWD_GM = 0;
    de_dx = 0;
    de_dx_GM = 0;
    board_event_time = 0;
    ch_event_time = 0;
    pileup = 0;
    //pileup_MWD = 0; //-1
    overflow = 0;
    //overflow_MWD = 0; //-1
}

ClassImp(LisaCalItem)
