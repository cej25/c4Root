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

#include <algorithm>
#include <cstring>
#include <iterator>
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

    const auto readV7x5 = [this](std::uint32_t module, std::uint32_t n, const auto& values,
                               std::uint32_t nChannels, const auto& channels,
                               std::uint32_t nGeos, const auto& geos) {
        const auto count = std::min<std::size_t>({n, nChannels, nGeos, std::size(values),
                                                  std::size(channels), std::size(geos)});
        for (std::size_t i = 0; i < count; ++i)
            fRaw->V7x5.push_back({module, geos[i], channels[i], values[i]});
    };
    readV7x5(1, input.bbseven_v7x5_module1n, input.bbseven_v7x5_module1data,
              input.bbseven_v7x5_module1channel, input.bbseven_v7x5_module1channelv,
              input.bbseven_v7x5_module1geo, input.bbseven_v7x5_module1geov);
    readV7x5(2, input.bbseven_v7x5_module2n, input.bbseven_v7x5_module2data,
              input.bbseven_v7x5_module2channel, input.bbseven_v7x5_module2channelv,
              input.bbseven_v7x5_module2geo, input.bbseven_v7x5_module2geov);
    readV7x5(3, input.bbseven_v7x5_module3n, input.bbseven_v7x5_module3data,
              input.bbseven_v7x5_module3channel, input.bbseven_v7x5_module3channelv,
              input.bbseven_v7x5_module3geo, input.bbseven_v7x5_module3geov);
    readV7x5(4, input.bbseven_v7x5_module4n, input.bbseven_v7x5_module4data,
              input.bbseven_v7x5_module4channel, input.bbseven_v7x5_module4channelv,
              input.bbseven_v7x5_module4geo, input.bbseven_v7x5_module4geov);

    c4::vme::DecodeV1290Blocks(input.bbseven_v1290_module_nM, input.bbseven_v1290_module_nMI,
        input.bbseven_v1290_module_nME, input.bbseven_v1290_module_n, input.bbseven_v1290_module_leadOrTrail,
        [&](std::uint32_t channel, std::uint32_t index) {
            if (channel == 0 || channel > std::size(input.bbseven_v1290_module_nMI)) return;
            auto& hit = fRaw->V1290.emplace_back();
            hit.procid = fRaw->procid;
            hit.geo = input.bbseven_v1290_module_geo;
            hit.channel = channel - 1; // BB7's UCESB index is one-based.
            hit.wr_subsystem = fRaw->wrId;
            hit.wr_timestamp = fRaw->wrTimestamp;
            hit.measurement = input.bbseven_v1290_module_data[index];
            hit.leading_or_trailing = input.bbseven_v1290_module_leadOrTrailv[index];
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
