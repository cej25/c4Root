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

#include "BB7Reader.h"

#include "BB7RawData.h"
#include "FairRootManager.h"
#include "FebexReader.h"
#include "VmeReader.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"

#include <cstring>

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_bbfebex.h"
    #include "ext_h101_bb7vme.h"
}

BB7Reader::BB7Reader(EXT_STR_h101_bbfebex_onion_t* data, std::size_t offset)
    : c4Reader("BB7Reader")
    , fFebexData(data)
    , fOffset(offset)
    , fFebexRaw(new BB7FebexRawData)
{
}

BB7Reader::BB7Reader(EXT_STR_h101_bb7vme_onion_t* data, std::size_t offset)
    : c4Reader("BB7Reader")
    , fVmeData(data)
    , fOffset(offset)
    , fVmeRaw(new BB7VmeRawData)
{
}

BB7Reader::~BB7Reader()
{
    delete fFebexRaw;
    delete fVmeRaw;
}

Bool_t BB7Reader::Init(ext_data_struct_info* structInfo)
{
    auto* manager = FairRootManager::Instance();
    if (!structInfo || !manager || (!fFebexData && !fVmeData)) return kFALSE;

    Int_t ok;
    if (fFebexData)
    {
        EXT_STR_h101_bbfebex_ITEMS_INFO(ok, *structInfo, fOffset, EXT_STR_h101_bbfebex, 0);
    }
    else
    {
        EXT_STR_h101_bb7vme_ITEMS_INFO(ok, *structInfo, fOffset, EXT_STR_h101_bb7vme, 0);
    }

    if (!ok)
    {
        c4LOG(error, "Failed to set up BB7 structure information");
        return kFALSE;
    }

    if (fFebexData)
    {
        manager->RegisterAny("BB7FebexRawData", fFebexRaw, !fOnline);
        std::memset(fFebexData, 0, sizeof *fFebexData);
    }
    else
    {
        manager->RegisterAny("BB7VmeRawData", fVmeRaw, !fOnline);
        std::memset(fVmeData, 0, sizeof *fVmeData);
    }
    Reset();
    return kTRUE;
}

Bool_t BB7Reader::Read()
{
    Reset();
    if (fFebexData) ReadFebex();
    if (fVmeData) ReadVme();
    return kTRUE;
}

void BB7Reader::ReadFebex()
{
    auto& first = fFebexRaw->first;
    first.wrTimestamp = c4::vme::Timestamp(fFebexData->bbfirst_ts_t);
    first.wrId = fFebexData->bbfirst_ts_subsystem_id;
    first.procid = 35;
    febex::ReadTraceBoards(fFebexData->bbfirst_data, first, "BB7");

    auto& second = fFebexRaw->second;
    second.wrTimestamp = c4::vme::Timestamp(fFebexData->bbsecond_ts_t);
    second.wrId = fFebexData->bbsecond_ts_subsystem_id;
    second.procid = 36;
    febex::ReadTraceBoards(fFebexData->bbsecond_data, second, "BB7");
}

void BB7Reader::ReadVme()
{
    const auto& input = *fVmeData;
    fVmeRaw->wrTimestamp = c4::vme::Timestamp(input.bbseven_ts_t);
    fVmeRaw->wrId = input.bbseven_ts_subsystem_id;
    fVmeRaw->procid = 31;

    const auto readModule = [this](std::uint32_t module, std::uint32_t geo,
                                   std::uint32_t count, const auto& indices, const auto& samples) {
        c4::vme::DecodeV775(count, indices, samples,
            [&](std::uint32_t channel, std::uint32_t value, std::int32_t status) {
                fVmeRaw->V7x5.push_back({module, geo, channel, value, status});
            });
    };
    readModule(1, input.bbseven_v7x51geo, input.bbseven_v7x51n, input.bbseven_v7x51nI, input.bbseven_v7x51data);
    readModule(2, input.bbseven_v7x52geo, input.bbseven_v7x52n, input.bbseven_v7x52nI, input.bbseven_v7x52data);
    readModule(3, input.bbseven_v7x53geo, input.bbseven_v7x53n, input.bbseven_v7x53nI, input.bbseven_v7x53data);
    readModule(4, input.bbseven_v7x54geo, input.bbseven_v7x54n, input.bbseven_v7x54nI, input.bbseven_v7x54data);

    c4::vme::DecodeV1290Blocks(input.bbseven_v1290_measurement_nM, input.bbseven_v1290_measurement_nMI,
        input.bbseven_v1290_measurement_nME, input.bbseven_v1290_measurement_n,
        input.bbseven_v1290_measurement_leadOrTrail,
        [&](std::uint32_t channel, std::uint32_t index) {
            auto& hit = fVmeRaw->V1290.emplace_back();
            hit.procid = fVmeRaw->procid;
            hit.geo = input.bbseven_v1290_geo;
            hit.channel = channel;
            hit.wr_subsystem = fVmeRaw->wrId;
            hit.wr_timestamp = fVmeRaw->wrTimestamp;
            hit.measurement = input.bbseven_v1290_measurement_data[index];
            hit.leading_or_trailing = input.bbseven_v1290_measurement_leadOrTrailv[index];
        });
}

void BB7Reader::Reset()
{
    if (fFebexRaw)
    {
        fFebexRaw->first = {};
        fFebexRaw->second = {};
    }
    if (fVmeRaw)
    {
        fVmeRaw->wrTimestamp = 0;
        fVmeRaw->wrId = 0;
        fVmeRaw->procid = 0;
        fVmeRaw->V7x5.clear();
        fVmeRaw->V1290.clear();
    }
}

ClassImp(BB7Reader)
