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
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "TString.h"

// c4
#include "BB7FebexRaw2Cal.h"
#include "BB7RawData.h"
#include "FebexConversions.h"
#include "BB7FebexIndexSafety.h"
#include "c4Logger.h"

// ROOT
#include <vector>

BB7FebexRaw2Cal::BB7FebexRaw2Cal()
    :   FairTask()
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   bb7calImplants(new std::vector<BB7FebexCalItem>)
    ,   bb7calDecays(new std::vector<BB7FebexCalItem>)
{
    bb7_config = TBB7FebexConfiguration::GetInstance();
    detector_mapping = bb7_config->Mapping();   // ??
}



BB7FebexRaw2Cal::~BB7FebexRaw2Cal()
{
    delete bb7calImplants;
    delete bb7calDecays;
}

InitStatus BB7FebexRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fRaw = mgr->InitObjectAs<decltype(fRaw)>("BB7FebexRawData");
    c4LOG_IF(fatal, !fRaw, "Branch BB7FebexRawData not found!");
    
    mgr->RegisterAny("BB7FebexCalImplants", bb7calImplants, !fOnline);
    mgr->RegisterAny("BB7FebexCalDecays", bb7calDecays, !fOnline);

    return kSUCCESS;
}


void BB7FebexRaw2Cal::Exec(Option_t* option)
{
    bb7calImplants->clear();
    bb7calDecays->clear();

    if (!bb7_config->MappingLoaded()) return;
    CalibrateCrate(fRaw->first, 0);
    CalibrateCrate(fRaw->second, 1);
}

void BB7FebexRaw2Cal::CalibrateCrate(const BB7FebexRawCrate& crate, int crateId)
{
    for (const auto& board : crate.boards)
    {
        const auto eventTime = board.summary.eventTicks * 10;
        for (std::size_t i = 0; i < board.summary.hits.size(); ++i)
        {
            const auto& hit = board.summary.hits[i];
            const auto mapped = detector_mapping.find({crateId, {board.summary.card, hit.channel}});
            if (mapped == detector_mapping.end())
            {
                if (count_in_event == 0)
                {
                    nUnmapped++;
                    count_in_event++;
                }
                continue;
            }

            const auto& [dssd, sideAndStrip] = mapped->second;
            const auto& [side, strip] = sideAndStrip;
            std::size_t channelIndex = 0;
            if (!bb7_febex_index_safety::TryChannelIndex(
                    dssd, side, strip, bb7_config->DSSDs(), channelIndex)) continue;

            const auto energy = febex::GammaSignedEnergy(hit.energyWord);
            // Preserve the original cut: negative energies were rejected after conversion to unsigned.
            if (energy < 0) continue;

            const bool implant = hit.overflow || energy > implantThreshold;
            if (!implant && energy <= decayThreshold)
            {
                if (count_in_event == 0)
                {
                    nNothings++;
                    count_in_event++;
                }
                continue;
            }

            const auto channelTime = hit.channelTicks * 10;
            const auto absoluteTime = crate.wrTimestamp + channelTime - eventTime;
            auto& output = implant ? *bb7calImplants : *bb7calDecays;
            output.emplace_back().SetAll(crate.wrTimestamp, dssd, side, strip, energy,
                board.traces[i], energy, eventTime, channelTime, absoluteTime, hit.pileup, hit.overflow);
        }
    }
}

void BB7FebexRaw2Cal::FinishEvent()
{
    count_in_event = 0;
}

void BB7FebexRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Unmapped item:: %i", nUnmapped));
    c4LOG(info, Form("Nothing items:: %i", nNothings));
}