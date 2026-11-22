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
 *                              C.E. Jones                                    *
 *                               06.05.25                                     *
 ******************************************************************************/

#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "StefanCal2Hit.h"
#include "StefanIndexSafety.h"
#include "StripClustering.h"
#include "c4Logger.h"
#include <FairTask.h>
#include <chrono>

StefanCal2Hit::StefanCal2Hit() :
    calArray(nullptr),
    hitArray(new std::vector<StefanHitItem>),
    fOnline(false),
    header(nullptr)
{
    stefan_config = TStefanConfiguration::GetInstance();
}

StefanCal2Hit::~StefanCal2Hit()
{
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fExecs << " microseconds.");
}

InitStatus StefanCal2Hit::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)FairRootManager::Instance()->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    calArray = mgr->InitObjectAs<decltype(calArray)>("StefanCalData");
    c4LOG_IF(fatal, !calArray, "Branch StefanCalData not found!");

    mgr->RegisterAny("StefanHitData", hitArray, !fOnline);


    return kSUCCESS;
}

void StefanCal2Hit::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();

    if (calArray->size() > 0) calEvents++;

    // Process implants if there are any
    // Decays should be 0, but we skip them anyway
    if (calArray->size() > 0)
    { 

        // Cluster events from adjacent strips
        auto clusters = strip_clustering::BuildClusters(*calArray);
        // List of front-back matched clusters for a physical hit
        static std::vector<std::pair<strip_clustering::StripCluster, strip_clustering::StripCluster>> hits;
        // Stopped tracking: count implants in each DSSD
        static std::vector<int> counts(stefan_config->DSSDs(), 0);
        hits.clear();
        std::fill(counts.begin(), counts.end(), 0);
        int max_dssd = 0;

        // Check all (X) clusters
        for (auto& i: clusters)
        {
            if (!stefan_index_safety::ValidDssd(i.DSSD, counts.size())) continue;

            // Track highest DSSD with implant and counts per DSSD
            counts[i.DSSD]++;
            if (i.DSSD > max_dssd) max_dssd = i.DSSD;

            // Only look at X clusters -- define X as 0 and Y as 1 or whatever
            if (i.Side != 0) continue;

            // Check all clusters again for a corresponding Y
            for (auto& j: clusters)
            {
                if (strip_clustering::MatchesFrontBack(i, j, stefan_config->fbe, stefan_config->fbt))
                {
                    hits.push_back({i, j});
                }
            }
        }

        // Produce hits
        for (auto& i : hits)
        {
            StefanHitItem hit = strip_clustering::MakeHit<StefanHitItem>(i.first, i.second);
            hit.Stopped = (hit.DSSD == max_dssd);
            // Check every DSSD before has at least one implant event
            for (int j = hit.DSSD; j > -1; j--) // dssd-1,>0
            {
                if (counts[j] == 0) hit.Stopped = false; // j-1
            }

            hitArray->push_back(hit);
        }
    }
    

    fExecs++;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void StefanCal2Hit::FinishEvent()
{
    hitArray->clear();
}

void StefanCal2Hit::FinishTask()
{
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fExecs << " microseconds.");
}

ClassImp(StefanCal2Hit)
