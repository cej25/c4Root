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

#include "FimpCalData.h"

FimpCalItem::FimpCalItem()
{

}

void FimpCalItem::SetAll(uint64_t wr, 
                        uint16_t id, 
                        int chan, 
                        double tot, 
                        double lead, 
                        double trail)
{
    wr_t = wr;
    wr_id = id;
    channel = chan;
    time_over_threshold = tot;
    lead_time = lead;
    trail_time = trail;
}
