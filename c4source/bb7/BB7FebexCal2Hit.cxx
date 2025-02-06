#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BB7FebexCal2Hit.h"
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

    mgr->RegisterAny("BB7ImplantHits", implantHitArray, !fOnline);
    mgr->RegisterAny("BB7DecayHits", decayHitArray, !fOnline);

   // bb7_config = TBB7FebexConfiguration::GetInstance();

    return kSUCCESS;
}

void BB7FebexCal2Hit::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();

    implantHitArray->clear();
    decayHitArray->clear();

    // Process implants if there are any
    // Decays should be 0, but we skip them anyway
    if (bb7calImplants->size() > 0)
    {
        // Cluster events from adjacent strips
        auto clusters = ItemsToClusters(*bb7calImplants);
        // List of front-back matched clusters for a physical hit
        static std::vector<std::pair<BB7Cluster, BB7Cluster>> hits;
        // Stopped tracking: count implants in each DSSD
        static std::vector<int> counts(bb7_config->DSSDs(), 0);
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
                if (std::abs(i.Energy - j.Energy) < 1000 // frontbackenergyL
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
    
    // was "else if", not sure what the issue is here
    if (bb7calDecays->size() > 1)
    {
        // Track channel multiplicty
        static std::vector<int> channels(bb7_config->DSSDs() * 64);
        std::fill(channels.begin(), channels.end(), 0);
        for (auto& i : *bb7calDecays)
        {
            channels[i.Strip + i.Side * 32 + i.DSSD * 64]++;
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
        auto clusters = ItemsToClusters(*bb7calDecays);
        // List of front-back matched clusters for a physical hit
        static std::vector<std::pair<BB7Cluster, BB7Cluster>> hits;
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
                // Must be same DSSD and Y side
                if (j.DSSD != i.DSSD || j.Side != 1) continue;
                // Check gates from config
                if (std::abs(i.Energy - j.Energy) < 350 // frontbackenergyL
                        && i.IsGoodTime(j, 4400))
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
            BB7FebexHitItem hit = ClusterPairToHit(i);

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

// Perform clustering: adjacent strips firing simultaenously are summed into one cluster
std::vector<BB7Cluster> BB7FebexCal2Hit::ItemsToClusters(std::vector<BB7FebexCalItem> const& items)
{
    // Track strip multiplicity to reject rapid-fire strips
    static std::unordered_map<bb7_coord_t, int, bb7_coord_hash> stripm;

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

BB7FebexHitItem BB7FebexCal2Hit::ClusterPairToHit(std::pair<BB7Cluster, BB7Cluster> const& i)
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

ClassImp(BB7FebexCal2Hit)

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
    HighEnergy = item.Energy > 1500; //bb7_config->ImplantTreshold();
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

