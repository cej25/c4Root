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

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "BeamMonitorData.h"
#include "BeamMonitorReader.h"
#include "c4Logger.h"

#include <algorithm>
#include <cstring>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_beammonitor.h"
}

namespace
{
template <std::size_t N>
void ReadStation(const std::uint32_t (&samples)[N], std::uint32_t count,
                 std::vector<std::uint32_t>& ticks, std::vector<BeamMonitorItem>& intervals)
{
    ticks.assign(samples, samples + std::min<std::size_t>(count, N));
    intervals.clear();
    // Within an event the first sample sets the origin. Unsigned subtraction
    // keeps the established 32-bit counter rollover behaviour.
    for (std::size_t i = 1; i < ticks.size(); ++i)
        intervals.emplace_back().SetAll(ticks[i] - ticks[i - 1]);
}
}

BeamMonitorReader::BeamMonitorReader(EXT_STR_h101_beammonitor_onion* data, size_t offset)
    :   c4Reader("BeamMonitorReader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   s2array(new std::vector<BeamMonitorItem>)
    ,   s4array(new std::vector<BeamMonitorItem>)
    ,   fRaw(new BeamMonitorRawData)
{
}

BeamMonitorReader::~BeamMonitorReader() 
{ 
    delete s2array;
    delete s4array;
    delete fRaw;
}

Bool_t BeamMonitorReader::Init(ext_data_struct_info* a_struct_info)
{
    if (!a_struct_info || !fData || !FairRootManager::Instance()) return kFALSE;
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_beammonitor_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_beammonitor, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->RegisterAny("BeamMonitorS2Data", s2array, !fOnline);
    FairRootManager::Instance()->RegisterAny("BeamMonitorS4Data", s4array, !fOnline);
    FairRootManager::Instance()->RegisterAny("BeamMonitorRawData", fRaw, !fOnline);
    Reset();

    std::memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t BeamMonitorReader::Read()
{
    const auto& words = fData->beammonitor_ts_t;
    fRaw->wrTimestamp = 0;
    for (unsigned i = 0; i < 4; ++i)
        fRaw->wrTimestamp |= std::uint64_t{words[i] & 0xffffu} << (16 * i);
    fRaw->wrId = fData->beammonitor_ts_subsystem_id;
    ReadStation(fData->beammonitor_s2_dataS2v, fData->beammonitor_s2_dataS2, fRaw->S2, *s2array);
    ReadStation(fData->beammonitor_s4_dataS4v, fData->beammonitor_s4_dataS4, fRaw->S4, *s4array);

    fNEvent += 1;
    return kTRUE;
}

void BeamMonitorReader::Reset()
{
    fRaw->wrTimestamp = 0;
    fRaw->wrId = 0;
    fRaw->S2.clear();
    fRaw->S4.clear();
    s2array->clear();
    s4array->clear();
}

ClassImp(BeamMonitorReader);
