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
#include "AgataSuperTraceData.h"

AgataSuperTraceData::AgataSuperTraceData()
    : nfired_segments(0),
      fevent_trigger_time(0),
      fhit_pattern(0),
      fcore_trigger_time(0),
      fcore_energy(0),
      fwr_subsystem_id(0),
      fwr_t(0)
{
    for (int i = 0; i < 36; ++i) {
        fsegment_energy[i] = 0;
        fsegment_trigger_time[i] = 0;
    }

    for (int i = 0; i < 18500; ++i) {
        supertrace[i] = 0;
    }
}

ClassImp(AgataSuperTraceData)
