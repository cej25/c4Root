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

#include "FairLogger.h"
#include "FairRootManager.h"

#include "BB7FebexData.h"
#include "BB7RawData.h"
#include "FebexReader.h"
#include "VmeReader.h"
#include "BB7FebexReader.h"
#include "c4Logger.h"

#include <algorithm>
#include <cstring>
#include <iterator>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_bbfebex.h"
}

BB7FebexReader::BB7FebexReader(EXT_STR_h101_bbfebex_onion* data, size_t offset)
    :   c4Reader("BB7FebexReader")
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   fRaw(new BB7FebexRawData)
    ,   bb7array(new std::vector<BB7FebexItem>)
    ,   bb7empty(new std::vector<BB7EmptyItem>)
{

}

BB7FebexReader::~BB7FebexReader()
{
    delete fRaw;
    delete bb7array;
    delete bb7empty;
}

Bool_t BB7FebexReader::Init(ext_data_struct_info* a_struct_info)
{
    if (!a_struct_info || !fData || !FairRootManager::Instance()) return kFALSE;
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_bbfebex_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_bbfebex, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->RegisterAny("BB7FebexData", bb7array, !fOnline);
    FairRootManager::Instance()->RegisterAny("BB7EmptyData", bb7empty, !fOnline);
    FairRootManager::Instance()->RegisterAny("BB7FebexRawData", fRaw, !fOnline);
    Reset();

    std::memset(fData, 0, sizeof *fData);

    return kTRUE;
}

namespace
{
void FillLegacyCrate(const BB7FebexRawCrate& crate, int id, std::vector<BB7FebexItem>& hits,
                     std::vector<BB7EmptyItem>& emptyBoards)
{
    bool recordedEmpty = false;
    for (const auto& board : crate.boards)
    {
        const auto& raw = board.summary;
        if (board.reportedHits == 0 && !recordedEmpty)
        {
            emptyBoards.emplace_back().SetAll(crate.wrTimestamp, crate.wrId, id, raw.card, raw.eventTicks * 10);
            recordedEmpty = true;
        }
        for (std::size_t i = 0; i < raw.hits.size(); ++i)
        {
            const auto& hit = raw.hits[i];
            hits.emplace_back().SetAll(crate.wrTimestamp, crate.wrId, id, raw.card, raw.eventTicks * 10,
                hit.channel, hit.channelTicks * 10, hit.pileup, hit.overflow,
                febex::GammaSignedEnergy(hit.energyWord), hit.channel, board.traces[i]);
        }
    }
}
}

Bool_t BB7FebexReader::Read()
{
    if (!fData) return kTRUE;
    Reset();

    auto& first = fRaw->first;
    first.wrTimestamp = c4::vme::Timestamp(fData->bbfirst_ts_t);
    first.wrId = fData->bbfirst_ts_subsystem_id;
    first.procid = 35;
    febex::ReadTraceBoards(fData->bbfirst_data, first, "BB7");
    FillLegacyCrate(first, 0, *bb7array, *bb7empty);

    auto& second = fRaw->second;
    second.wrTimestamp = c4::vme::Timestamp(fData->bbsecond_ts_t);
    second.wrId = fData->bbsecond_ts_subsystem_id;
    second.procid = 36;
    febex::ReadTraceBoards(fData->bbsecond_data, second, "BB7");
    FillLegacyCrate(second, 1, *bb7array, *bb7empty);

    return kTRUE;
}

void BB7FebexReader::Reset()
{
    fRaw->first = {};
    fRaw->second = {};
    bb7array->clear();
    bb7empty->clear();
}

ClassImp(BB7FebexReader)
