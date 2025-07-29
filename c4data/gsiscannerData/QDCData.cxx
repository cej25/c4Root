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

#include "QDCData.h"

QDCData::QDCData()
    : 
    fboard_id(0),
    fch_ID(0),
    fcharge(0),
    fwr_subsystem_id(0),
    fwr_t(0)
{
}

QDCData::QDCData(
        int board_id,
        int ch_ID,
        int16_t charge,
        int wr_subsystem_id,
        int64_t wr_t)
    : 
    fboard_id(board_id),
    fch_ID(ch_ID),
    fcharge(charge),
    fwr_subsystem_id(wr_subsystem_id),
    fwr_t(wr_t)
{
}

ClassImp(QDCData)