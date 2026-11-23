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

#include "DegasCalData.h"

DegasCalData::DegasCalData()
    :
        ftrig(0),
        fevent_trigger_time(0),
        fpileup(0),
        foverflow(0),
        fchannel_trigger_time(0),
        fchannel_energy(0),
        fcrystal_id(0),
        fdetector_id(0),
        fwr_subsystem_id(0),
        fwr_t(0),
        fabsolute_event_time(0)
{
}

DegasCalData::DegasCalData(
        UShort_t trig,
        ULong64_t event_trigger_time,
        Bool_t pileup,
        UChar_t overflow,
        Double_t channel_trigger_time,
        Double_t channel_energy, // calibrated in energy of keVs
        UInt_t crystal_id,
        UInt_t detector_id,
        UShort_t wr_subsystem_id,
        ULong64_t wr_t,
        Long64_t absolute_event_time)
    :
    ftrig(trig),
    fevent_trigger_time(event_trigger_time),
    fpileup(pileup),
    foverflow(overflow),
    fchannel_trigger_time(channel_trigger_time),
    fchannel_energy(channel_energy),
    fcrystal_id(crystal_id),
    fdetector_id(detector_id),
    fwr_subsystem_id(wr_subsystem_id),
    fwr_t(wr_t),
    fabsolute_event_time(absolute_event_time)
{
}

ClassImp(DegasCalData)
