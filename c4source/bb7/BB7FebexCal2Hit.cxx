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
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BB7FebexCal2Hit.h"
#include "StripClustering.h"
#include "BB7FebexIndexSafety.h"
#include "c4Logger.h"
#include <FairTask.h>
#include <unordered_map>
#include <chrono>

// (DSSD, Side, Strip)
using bb7_coord_t = std::tuple<int, int, int>;

// https://stackoverflow.com/a/7222201/916549
template<typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
  std::hash<T> hasher;
  seed ^= hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct bb7_coord_hash
{
  inline size_t operator()(const bb7_coord_t& val) const
  {
    size_t seed = 0;
    hash_combine(seed, std::get<0>(val));
    hash_combine(seed, std::get<1>(val));
    hash_combine(seed, std::get<2>(val));
    return seed;
  }
};

BB7FebexCal2Hit::BB7FebexCal2Hit() :
    bb7calImplants(nullptr),
    bb7calDecays(nullptr),
    implantHitArray(new std::vector<BB7FebexHitItem>),
    decayHitArray(new std::vector<BB7FebexHitItem>),
    fOnline(false),
    header(nullptr)
{
    bb7_config = TBB7FebexConfiguration::GetInstance();
}

BB7FebexCal2Hit::~BB7FebexCal2Hit()
{
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fExecs << " microseconds.");
}

InitStatus BB7FebexCal2Hit::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)FairRootManager::Instance()->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    bb7calImplants = mgr->InitObjectAs<decltype(bb7calImplants)>("BB7FebexCalImplants");
    bb7calDecays = mgr->InitObjectAs<decltype(bb7calDecays)>("BB7FebexCalDecays");
    c4LOG_IF(fatal, !bb7calImplants, "Branch BB7FebexCalImplants not found!");
    c4LOG_IF(fatal, !bb7calDecays, "Branch BB7FebexCalDecays not found!");

    mgr->RegisterAny("BB7FebexImplants", implantHitArray, !fOnline);
    mgr->RegisterAny("BB7FebexDecays", decayHitArray, !fOnline);


    return kSUCCESS;
}

void BB7FebexCal2Hit::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();

    implantHitArray->clear();
    decayHitArray->clear();

    if (bb7calImplants->size() > 0) ncalImplantEvents++;
    if (bb7calDecays->size() > 0) ncalDecayEvents++;

    // Process implants if there are any
    // Decays should be 0, but we skip them anyway
    if (bb7calImplants->size() > 0)
    { 

        // Cluster events from adjacent strips
        auto clusters = strip_clustering::BuildClusters(*bb7calImplants);
        // List of front-back matched clusters for a physical hit
        static std::vector<std::pair<strip_clustering::StripCluster, strip_clustering::StripCluster>> hits;
        // Stopped tracking: count implants in each DSSD
        static std::vector<int> counts(bb7_config->DSSDs(), 0);
        hits.clear();
        std::fill(counts.begin(), counts.end(), 0);
        int max_dssd = 0;

        // Check all (X) clusters
        for (auto& i: clusters)
        {
            if (!bb7_febex_index_safety::ValidDssd(i.DSSD, counts.size())) continue;

            // Track highest DSSD with implant and counts per DSSD
            counts[i.DSSD]++;
            if (i.DSSD > max_dssd) max_dssd = i.DSSD;

            // Only look at X clusters -- define X as 0 and Y as 1 or whatever
            if (i.Side != 0) continue;

            // Check all clusters again for a corresponding Y
            for (auto& j: clusters)
            {
                if (strip_clustering::MatchesFrontBack(i, j, 3500000000., 4400))
                {
                    hits.push_back({i, j});
                }
            }
        }

        // Produce hits
        for (auto& i : hits)
        {
            BB7FebexHitItem hit = strip_clustering::MakeHit<BB7FebexHitItem>(i.first, i.second);
            hit.Stopped = (hit.DSSD == max_dssd);
            // Check every DSSD before has at least one implant event
            for (int j = hit.DSSD; j > -1; j--) // dssd-1,>0
            {
                if (counts[j] == 0) hit.Stopped = false; // j-1
            }

            implantHitArray->push_back(hit);
        }
    }
    
    // was "else if", not sure what the issue is here
    if (bb7calDecays->size() > 1)
    {
        // Track channel multiplicty
        static std::vector<int> channels(bb7_config->DSSDs() * 64);
        std::fill(channels.begin(), channels.end(), 0);
        for (auto& i : *bb7calDecays)
        {
            std::size_t channel_index = 0;
            if (!bb7_febex_index_safety::TryChannelIndex(
                    i.DSSD, i.Side, i.Strip, bb7_config->DSSDs(), channel_index)) continue;
            channels[channel_index]++;
        }
        int channelM = 0;
        for (size_t i = 0; i < channels.size(); ++i)
        {
            if (channels[i] > 0) ++channelM;
        }

        // TODO LATER
        if (channelM > 700) // pulserthreshold
        {
            // Pulser event - do nothing for now
            // TODO: Save somewhere for plotting energies?
            // TODO: Support alignment routine
            return;
        }

        if (bb7calDecays->size() > 400) // hugethreshold
        {
            // If too many hits (and not a pulser - above)
            // Ignore the event, front-back matching would take ages
            return;
        }

        // Cluster decays
        auto clusters = strip_clustering::BuildClusters(*bb7calDecays);
        // List of front-back matched clusters for a physical hit
        static std::vector<std::pair<strip_clustering::StripCluster, strip_clustering::StripCluster>> hits;
        // Track hit mutliplicty for noise reduction
        static std::unordered_map<bb7_coord_t, int, bb7_coord_hash> mults;
        hits.clear();
        mults.clear();

        for (auto& i : clusters)
        {
            if (i.DSSD == -1) continue;

            // Only look at X clusters
            if (i.Side != 0) continue;

            // Check all clusters again for a corresponding Y
            for (auto& j: clusters)
            {
                if (strip_clustering::MatchesFrontBack(i, j, 350000000000., 4400))
                {
                    bb7_coord_t x{i.DSSD, i.Side, i.Strip};
                    bb7_coord_t y{j.DSSD, j.Side, j.Strip};
                    mults[x]++;
                    mults[y]++;
                    hits.push_back({i, j});
                }
            }
        }

        // Produce hits
        for (auto& i : hits)
        {
            BB7FebexHitItem hit = strip_clustering::MakeHit<BB7FebexHitItem>(i.first, i.second);

            bb7_coord_t x{i.first.DSSD, i.first.Side, i.first.Strip};
            bb7_coord_t y{i.second.DSSD, i.second.Side, i.second.Strip};
            // false for now
            // if (bb7_config->ReduceNoise() && (mults[x] > 1 || mults[y] > 1))
            //     continue;

            decayHitArray->push_back(hit);
        }
    }

    fExecs++;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void BB7FebexCal2Hit::FinishTask()
{
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fExecs << " microseconds.");
}

ClassImp(BB7FebexCal2Hit)
