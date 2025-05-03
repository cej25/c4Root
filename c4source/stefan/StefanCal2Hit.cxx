#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "StefanCal2Hit.h"
#include "c4Logger.h"
#include <FairTask.h>
#include <unordered_map>
#include <chrono>

// (DSSD, Side, Strip)
using stefan_coord_t = std::tuple<int, int, int>;

// https://stackoverflow.com/a/7222201/916549
template<typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
  std::hash<T> hasher;
  seed ^= hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct stefan_coord_hash
{
  inline size_t operator()(const stefan_coord_t& val) const
  {
    size_t seed = 0;
    hash_combine(seed, std::get<0>(val));
    hash_combine(seed, std::get<1>(val));
    hash_combine(seed, std::get<2>(val));
    return seed;
  }
};

StefanCal2Hit::StefanCal2Hit() :
    calArray(nullptr),
    hitArray(new std::vector<StefanHitItem>),
    fOnline(false),
    header(nullptr)
{
    stefan_config = TBB7FebexConfiguration::GetInstance();
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

    implantHitArray->clear();
    decayHitArray->clear();

    if (calArray->size() > 0) calEvents++;

    // Process implants if there are any
    // Decays should be 0, but we skip them anyway
    if (calArray->size() > 0)
    { 

        // Cluster events from adjacent strips
        auto clusters = ItemsToClusters(*calArray);
        // List of front-back matched clusters for a physical hit
        static std::vector<std::pair<StefanCluster, StefanCluster>> hits;
        // Stopped tracking: count implants in each DSSD
        static std::vector<int> counts(stefan_config->DSSDs(), 0);
        hits.clear();
        std::fill(counts.begin(), counts.end(), 0);
        int max_dssd = 0;

        // Check all (X) clusters
        for (auto& i: clusters)
        {
            if (i.DSSD == -1) continue;

            // Track highest DSSD with implant and counts per DSSD
            counts[i.DSSD]++;
            if (i.DSSD > max_dssd) max_dssd = i.DSSD;

            // Only look at X clusters -- define X as 0 and Y as 1 or whatever
            if (i.Side != 0) continue;

            // Check all clusters again for a corresponding Y
            for (auto& j: clusters)
            {
                // Must be same DSSD and Y side
                if (j.DSSD != i.DSSD || j.Side != 1) continue;
                // Check gates from config
                if (std::abs(i.Energy - j.Energy) < 3500000000 // frontbackenergyL
                        && i.IsGoodTime(j, 4400))
                {
                    hits.push_back({i, j});
                }
            }
        }

        // Produce hits
        for (auto& i : hits)
        {
            BB7FebexHitItem hit = ClusterPairToHit(i);
            hit.Stopped = (hit.DSSD == max_dssd);
            // Check every DSSD before has at least one implant event
            for (int j = hit.DSSD; j > -1; j--) // dssd-1,>0
            {
                if (counts[j] == 0) hit.Stopped = false; // j-1
            }

            implantHitArray->push_back(hit);
        }
    }
    

    fExecs++;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void StefanCal2Hit::FinishTask()
{
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fExecs << " microseconds.");
}

// Perform clustering: adjacent strips firing simultaenously are summed into one cluster
std::vector<StefanCluster> StefanCal2Hit::ItemsToClusters(std::vector<BB7FebexCalItem> const& items)
{
    // Track strip multiplicity to reject rapid-fire strips
    static std::unordered_map<stefan_coord_t, int, stefan_coord_hash> stripm;

    static std::vector<BB7Cluster> clusters;

    stripm.clear();
    clusters.clear();
    for (auto& i : items)
    {
        if (i.DSSD == -1) continue;

        bb7_coord_t coord{i.DSSD, i.Side, i.Strip};
        // If strip fired more than once ignore it
        // false for now
        // if (bb7_config->ReduceNoise() && ++stripm[coord] > 1)
        //     continue;

        bool added = false;
        BB7Cluster* cluster = nullptr;
        // Try to add the adc item to an existing cluster
        // Weird loop (not for) because we can combine clusters
        auto it = std::begin(clusters);
        while (it != std::end(clusters))
        {
            auto& j = *it;
            bool docluster = false;
            // Check options for which cluster
            // can add checks for "clusterimplants"/"clusterdecays" - both true for now
            if (j.HighEnergy) docluster = true;
            if (!j.HighEnergy) docluster = true; // true?

            if (docluster && j.IsAdjacent(i) && j.IsGoodTime(i))
            {
                if (!added)
                {
                    j.AddItem(i);
                    cluster = &j;
                    added = true;
                }
                // If we match again the two clusters are merged into one
                // The old cluster is then removed
                else
                {
                    cluster->AddCluster(j);
                    it = clusters.erase(it);
                    continue;
                }
            }
            ++it;
        }
        // If not added already, make a new cluster
        if (!added)
        {
            BB7Cluster c_new;
            c_new.AddItem(i);
            clusters.push_back(c_new);
        }
    }

    // re-check multiplicty and destroy clusters with multiple same-strip
    // false for now
    // if (bb7_config->ReduceNoise())
    // {
    //     auto it = std::begin(clusters);
    //     while (it != std::end(clusters))
    //     {
    //         auto& j = *it;
    //         bool destroy = false;
    //         for (int s = j.StripMin; s <= j.StripMax; s++)
    //         {
    //             bb7_coord_t coord{j.DSSD, j.Side, s};
    //             if (stripm[coord] > 1) {
    //                 destroy = true;
    //             }
    //         }
    //         if (destroy) {
    //             it = clusters.erase(it);
    //             continue;
    //         }
    //         ++it;
    //     }
    // }

    return clusters;
}

BB7FebexHitItem StefanCal2Hit::ClusterPairToHit(std::pair<BB7Cluster, BB7Cluster> const& i)
{

    BB7FebexHitItem hit;
    hit.DSSD = i.first.DSSD;

    hit.StripX = i.first.Strip;
    hit.StripY = i.second.Strip;

    // ok this depends on dimensions, irrelevant for now
    // ------------------------------------------------------
    // Position is in mm, with the centre as (0, 0)
    // if (conf->Wide()) {
    //     hit.PosX = 226.8 * i.first.Strip / 386. - 113.45;
    // }
    // else {
    //     hit.PosX = 75.6 * i.first.Strip / 128. - 37.75;
    // }
    // hit.PosY = 75.6 * i.second.Strip / 128. - 37.75;
    
    // ------------------------------------------------------

    hit.StripXMin = i.first.StripMin;
    hit.StripXMax = i.first.StripMax;
    hit.StripYMin = i.second.StripMin;
    hit.StripYMax = i.second.StripMax;
    hit.ClusterSizeX = i.first.N;
    hit.ClusterSizeY = i.second.N;

    // Possible energy choices: average (if X, Y equally good)
    hit.Energy = (i.first.Energy + i.second.Energy) / 2.;
    // Alternative for bad Y
    // hit.Energy = i.first.Energy;
    hit.EnergyX = i.first.Energy;
    hit.EnergyY = i.second.Energy;

    // Time is always the earliest
    hit.Time = std::min(i.first.Time, i.second.Time);
    hit.TimeX = i.first.Time;
    hit.TimeY = i.second.Time;

    return hit;
}

ClassImp(StefanCal2Hit)

void BB7Cluster::Zero()
{
  DSSD = -1;
  Side = 0;
  HighEnergy = false;
  Energy = 0;
  Strip = 0;
  Time = 0;
  StripMin = 0;
  StripMax = 0;
  TimeMin = 0;
  TimeMax = 0;
  StripSum = 0;
  N = 0;
}

void BB7Cluster::AddItem(BB7FebexCalItem const& item)
{
  if (DSSD == -1)
  {
    DSSD = item.DSSD;
    Side = item.Side;
    HighEnergy = item.Energy > 10000000; //bb7_config->ImplantTreshold();
    StripMin = item.Strip;
    StripMax = item.Strip;
    TimeMin = item.AbsoluteTime;
    TimeMax = item.AbsoluteTime;
  }
  Energy += item.Energy;
  if(item.Strip < StripMin) StripMin = item.Strip;
  if(item.Strip > StripMax) StripMax = item.Strip;
  if(item.AbsoluteTime < TimeMin) TimeMin = item.AbsoluteTime;
  if(item.AbsoluteTime > TimeMax) TimeMax = item.AbsoluteTime;
  StripSum += item.Strip;
  Strip = (double)StripSum / ++N;
  Time = TimeMin;
}

void BB7Cluster::AddCluster(BB7Cluster const& cluster)
{
  if (DSSD == -1)
  {
    *this = cluster;
    return;
  }

  if (cluster.StripMin < StripMin) StripMin = cluster.StripMin;
  if (cluster.StripMax > StripMax) StripMax = cluster.StripMax;
  if (cluster.TimeMin < TimeMin) TimeMin = cluster.TimeMin;
  if (cluster.TimeMax > TimeMax) TimeMax = cluster.TimeMax;
  Energy += cluster.Energy;
  StripSum += cluster.StripSum;
  N += cluster.N;
  Strip = (double)StripSum / N;
  Time = TimeMin;
}

bool BB7Cluster::IsAdjacent(BB7FebexCalItem const& item) const
{
  if (DSSD == -1) return true;
  if (item.DSSD != DSSD || item.Side != Side) return false;
  if (item.Strip >= StripMin - 1 && item.Strip <= StripMax + 1) return true;
  return false;
}

bool BB7Cluster::IsGoodTime(BB7FebexCalItem const& item, int window) const
{
  if (DSSD == -1) return true;

  if (item.AbsoluteTime >= TimeMin - window && item.AbsoluteTime <= TimeMax + window) return true;
  return false;
}

bool BB7Cluster::IsGoodTime(BB7Cluster const& event, int window) const
{
  if (DSSD == -1) return true;

  if (event.TimeMin >= TimeMin - window && event.TimeMin <= TimeMax + window) return true;
  if (event.TimeMax >= TimeMin - window && event.TimeMax <= TimeMax + window) return true;
  return false;
}

