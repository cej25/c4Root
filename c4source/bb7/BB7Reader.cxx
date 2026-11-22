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

#include "BB7VmeData.h"
#include "BB7RawData.h"
#include "VmeDigitiserDecode.h"
#include "BB7Reader.h"
#include "c4Logger.h"

#include <cstring>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_bb7vme.h"
}

BB7Reader::BB7Reader(EXT_STR_h101_bb7vme_onion* data, size_t offset)
    :   c4Reader("BB7Reader")
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   v7x5array(new std::vector<BB7V7x5Item>)
    ,   v1290array(new std::vector<BB7V1290Item>)
    ,   fRaw(new BB7VmeRawData)
{

}

BB7Reader::~BB7Reader()
{
    delete v7x5array;
    delete v1290array;
    delete fRaw;
}

Bool_t BB7Reader::Init(ext_data_struct_info* a_struct_info)
{
    if (!a_struct_info || !fData || !FairRootManager::Instance()) return kFALSE;
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_bb7vme_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_bb7vme, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    FairRootManager::Instance()->RegisterAny("BB7V7x5Data", v7x5array, !fOnline);
    FairRootManager::Instance()->RegisterAny("BB7V1290Data", v1290array, !fOnline);
    FairRootManager::Instance()->RegisterAny("BB7VmeRawData", fRaw, !fOnline);
    Reset();

    std::memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t BB7Reader::Read()
{
    if (!fData) return kTRUE;
    Reset();
    const auto& input = *fData;
    fRaw->wrTimestamp = c4::vme::Timestamp(input.bbseven_ts_t);
    fRaw->wrId = input.bbseven_ts_subsystem_id;
    fRaw->procid = 31;

    const auto readModule = [this](std::uint32_t module, std::uint32_t geo,
                                   std::uint32_t count, const auto& indices, const auto& samples) {
        c4::vme::DecodeV775(count, indices, samples,
            [&](std::uint32_t channel, std::uint32_t value, std::int32_t status) {
                fRaw->V7x5.push_back({module, geo, channel, value, status});
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
            if (channel == 0 || channel > 32) return;
            auto& hit = fRaw->V1290.emplace_back();
            hit.procid = fRaw->procid;
            hit.geo = input.bbseven_v1290_geo;
            hit.channel = channel - 1; // UCESB's sparse index is one-based.
            hit.wr_subsystem = fRaw->wrId;
            hit.wr_timestamp = fRaw->wrTimestamp;
            hit.measurement = input.bbseven_v1290_measurement_data[index];
            hit.leading_or_trailing = input.bbseven_v1290_measurement_leadOrTrailv[index];
        });

    for (const auto& hit : fRaw->V7x5)
        v7x5array->emplace_back().SetAll(fRaw->wrTimestamp, hit.geo, hit.value, hit.channel);
    for (const auto& hit : fRaw->V1290)
        v1290array->emplace_back().SetAll(hit.channel, hit.measurement, hit.leading_or_trailing);

    return kTRUE;
}

void BB7Reader::Reset()
{
    fRaw->wrTimestamp = 0;
    fRaw->wrId = 0;
    fRaw->procid = 0;
    fRaw->V7x5.clear();
    fRaw->V1290.clear();
    v7x5array->clear();
    v1290array->clear();
}

ClassImp(BB7Reader)
