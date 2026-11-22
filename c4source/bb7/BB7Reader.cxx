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

    for (std::size_t slot = 0; slot < std::size(input.bbseven_v7x5); ++slot)
    {
        const auto& module = input.bbseven_v7x5[slot];
        c4::vme::DecodeV775(module.n, module.nI, module.data,
            [&](std::uint32_t channel, std::uint32_t value, std::int32_t status) {
                fRaw->V7x5.push_back({static_cast<std::uint32_t>(slot + 1), module.geo, channel, value, status});
            });
    }

    const auto& tdc = input.bbseven_v1290;
    c4::vme::DecodeV1290Blocks(tdc.measurement_nM, tdc.measurement_nMI, tdc.measurement_nME,
        tdc.measurement_n, tdc.measurement_leadOrTrail,
        [&](std::uint32_t channel, std::uint32_t index) {
            if (channel == 0 || channel > 32) return;
            auto& hit = fRaw->V1290.emplace_back();
            hit.procid = fRaw->procid;
            hit.geo = tdc.geo;
            hit.channel = channel - 1; // UCESB's sparse index is one-based.
            hit.wr_subsystem = fRaw->wrId;
            hit.wr_timestamp = fRaw->wrTimestamp;
            hit.measurement = tdc.measurement_data[index];
            hit.leading_or_trailing = tdc.measurement_leadOrTrailv[index];
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
