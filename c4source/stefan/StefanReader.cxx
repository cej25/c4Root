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
 *                         C.E. Jones, G. Kosir                               *
 *                               06.05.25                                     *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "StefanReader.h"
#include "FebexRawData.h"
#include "FebexReader.h"
#include "c4Logger.h"

#include <cstring>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_stefan.h"
}

StefanReader::StefanReader(EXT_STR_h101_stefan_onion* data, size_t offset)
    : c4Reader("StefanReader")
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , stefanArray(new std::vector<StefanFebexItem>)
{
}

StefanReader::~StefanReader() { 
    delete stefanArray;

}

Bool_t StefanReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

    EXT_STR_h101_stefan_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_stefan, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // Register output array in a tree
    FairRootManager::Instance()->RegisterAny("StefanFebexData", stefanArray, !fOnline);
    stefanArray->clear();

    std::memset(fData, 0, sizeof *fData);

    return kTRUE;
}


Bool_t StefanReader::Read()
{
    if (!fData) return kTRUE;

    const auto& input = *fData;
    std::vector<FebexRawData> boards;
    febex::ReadBoards<febex::SummaryLayout::WithTriggerTimestamp>(
        input.stefan_data, input.stefan_ts_t, input.stefan_ts_subsystem_id, 0, "Stefan", boards);

    for (const auto& board : boards)
    {
        for (const auto& hit : board.hits)
        {
            if ((VetoPileup && hit.pileup) || (VetoOverflow && hit.overflow)) continue;

            // Preserve the slot, one-based channel and whole-nanosecond time
            // used by the existing Stefan branch and detector map.
            stefanArray->emplace_back().SetAll(
                static_cast<Long64_t>(board.wrTimestamp), board.wrId, board.slot,
                board.eventTicks * 10, hit.channel + 1,
                static_cast<ULong64_t>(hit.legacyChannelTimeNs), hit.pileup, hit.overflow,
                static_cast<UInt_t>(hit.signedEnergy));
        }
    }
    return kTRUE;
}

void StefanReader::Reset()
{
    // reset output array
    stefanArray->clear();
}

ClassImp(StefanReader)
