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

#include "StefanHitData.h"

void StefanHitItem::Reset()
{
    DSSD = -1;
    StripX = StripY = PosX = PosY = -1;
    Energy = EnergyX = EnergyY = 0;
    StripXMin = StripXMax = StripYMin = StripYMax = -1;
    ClusterSizeX = ClusterSizeY = 0;
    Time = TimeX = TimeY = 0;
    Stopped = false;
}

ClassImp(StefanHitItem)

