#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AidaCal2Hit.h"
#include "TAidaConfiguration.h"
#include "c4Logger.h"
#include "AidaData.h"
#include "AidaCalData.h"
#include <FairTask.h>
#include <unordered_map>
#include <chrono>

// AIDA coordinate (DSSD, Side, Strip)
using aida_coord_t = std::tuple<int, int, int>;

// https://stackoverflow.com/a/7222201/916549
template<typename T>
inline void hash_combine(std::size_t& seed, const T& val)
{
  std::hash<T> hasher;
  seed ^= hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct aida_coord_hash
{
  inline size_t operator()(const aida_coord_t& val) const
  {
    size_t seed = 0;
    hash_combine(seed, std::get<0>(val));
    hash_combine(seed, std::get<1>(val));
    hash_combine(seed, std::get<2>(val));
    return seed;
  }
};

AidaCal2Hit::AidaCal2Hit() :
    implantCalArray(nullptr),
    decayCalArray(nullptr),
    implantHitArray(new std::vector<AidaHit>),
    decayHitArray(new std::vector<AidaHit>),
    fImplantOnline(false),
    fDecayOnline(false),
    header(nullptr),
    conf(nullptr)
{
}

AidaCal2Hit::~AidaCal2Hit()
{
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fExecs << " microseconds.");
}

void AidaCal2Hit::SetParContainers()
{
}

InitStatus AidaCal2Hit::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)FairRootManager::Instance()->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    implantCalArray = mgr->InitObjectAs<decltype(implantCalArray)>("AidaImplantCalAdcData");
    decayCalArray = mgr->InitObjectAs<decltype(decayCalArray)>("AidaDecayCalAdcData");
    c4LOG_IF(fatal, !implantCalArray, "Branch AidaImplantCalAdcData not found!");
    c4LOG_IF(fatal, !decayCalArray, "Branch AidaDecayCalAdcData not found!");

    mgr->RegisterAny("AidaImplantHits", implantHitArray, !fImplantOnline);
    mgr->RegisterAny("AidaDecayHits", decayHitArray, !fDecayOnline);

    conf = TAidaConfiguration::GetInstance();

    return kSUCCESS;
}

void AidaCal2Hit::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();

    implantHitArray->clear();
    decayHitArray->clear();

    // Process implants if there are any
    // Decays should be 0, but we skip them anyway
    if (implantCalArray->size() > 0)
    {
        // Cluster events from adjacent strips
        auto clusters = ItemsToClusters(*implantCalArray);
        // List of front-back matched clusters for a physical hit
        static std::vector<std::pair<AidaCluster, AidaCluster>> hits;
        // Stopped tracking: count implants in each DSSD
        static std::vector<int> counts(conf->DSSDs(), 0);
        hits.clear();
        std::fill(counts.begin(), counts.end(), 0);
        int max_dssd = 0;

        // Check all (X) clusters
        for (auto& i: clusters)
        {
            // TODO: is this possible in c4Root?
            if (i.DSSD == -1) continue;

            // Track highest DSSD with implant and counts per DSSD
            counts[i.DSSD -1]++;
            if (i.DSSD > max_dssd) max_dssd = i.DSSD;

            // Only look at X clusters
            if (i.Side != conf->DSSD(i.DSSD - 1).XSide) continue;

            // Check all clusters again for a corresponding Y
            for (auto& j: clusters)
            {
                // Must be same DSSD and Y side
                if (j.DSSD != i.DSSD || j.Side != conf->DSSD(j.DSSD - 1).YSide) continue;
                // Check gates from config
                if (std::abs(i.Energy - j.Energy) < conf->FrontBackEnergyH()
                        && i.IsGoodTime(j, conf->FrontBackWindow()))
                {
                    hits.push_back({i, j});
                }
            }
        }

        // Produce hits
        for (auto& i : hits)
        {
            AidaHit hit = ClusterPairToHit(i);
            hit.Stopped = (hit.DSSD == max_dssd);
            // Check every DSSD before has at least one implant event
            for (int j = hit.DSSD - 1; j > 0; j--)
            {
                if (counts[j - 1] == 0) hit.Stopped = false;
            }

            implantHitArray->push_back(hit);
            //if (hit.Time != 0) std::cout << "Event: " << header->GetEventno() << " - AIDA WR: " << hit.Time << std::endl;
        }
    }
    else if (decayCalArray->size() > 1)
    {
        // Track channel multiplicty
        static std::vector<int> channels(conf->FEEs() * 64);
        std::fill(channels.begin(), channels.end(), 0);
        for (auto& i : *decayCalArray)
        {
            channels[(i.Fee() - 1) * 64 +  i.Channel()]++;
        }
        int channelM = 0;
        for (size_t i = 0; i < channels.size(); ++i)
        {
            if (channels[i] > 0) ++channelM;
        }

        if (channelM > conf->PulserThreshold())
        {
            // Pulser event - do nothing for now
            // TODO: Save somewhere for plotting energies?
            // TODO: Support alignment routine
            return;
        }

        if (decayCalArray->size() > conf->HugeThreshold())
        {
            // If too many hits (and not a pulser - above)
            // Ignore the event, front-back matching would take ages
            return;
        }

        // Cluster decays
        auto clusters = ItemsToClusters(*decayCalArray);
        // List of front-back matched clusters for a physical hit
        static std::vector<std::pair<AidaCluster, AidaCluster>> hits;
        // Track hit mutliplicty for noise reduction
        static std::unordered_map<aida_coord_t, int, aida_coord_hash> mults;
        hits.clear();
        mults.clear();

        for (auto& i : clusters)
        {
            // TODO: is this possible in c4Root?
            if (i.DSSD == -1) continue;

            // Only look at X clusters
            if (i.Side != conf->DSSD(i.DSSD - 1).XSide) continue;

            // Check all clusters again for a corresponding Y
            for (auto& j: clusters)
            {
                // Must be same DSSD and Y side
                if (j.DSSD != i.DSSD || j.Side != conf->DSSD(j.DSSD - 1).YSide) continue;
                // Check gates from config
                if (std::abs(i.Energy - j.Energy) < conf->FrontBackEnergyL()
                        && i.IsGoodTime(j, conf->FrontBackWindow()))
                {
                    aida_coord_t x{i.DSSD, i.Side, i.Strip};
                    aida_coord_t y{j.DSSD, j.Side, j.Strip};
                    mults[x]++;
                    mults[y]++;
                    hits.push_back({i, j});
                }
            }
        }

        // Produce hits
        for (auto& i : hits)
        {
            AidaHit hit = ClusterPairToHit(i);

            aida_coord_t x{i.first.DSSD, i.first.Side, i.first.Strip};
            aida_coord_t y{i.second.DSSD, i.second.Side, i.second.Strip};
            if (conf->ReduceNoise() && (mults[x] > 1 || mults[y] > 1))
                continue;

            decayHitArray->push_back(hit);
        }
    }

    fExecs++;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();
}

void AidaCal2Hit::FinishTask()
{
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fExecs << " microseconds.");
}

// Perform clustering: adjacent strips firing simultaenously are summed into one cluster
std::vector<AidaCluster> AidaCal2Hit::ItemsToClusters(std::vector<AidaCalAdcItem> const& items)
{
    // Track strip multiplicity to reject rapid-fire strips
    static std::unordered_map<aida_coord_t, int, aida_coord_hash> stripm;

    static std::vector<AidaCluster> clusters;

    stripm.clear();
    clusters.clear();
    for (auto& i : items)
    {
        // TODO: is this possible in c4Root?
        if (i.DSSD() == -1) continue;

        aida_coord_t coord{i.DSSD(), i.Side(), i.Strip()};
        // If strip fired more than once ignore it
        if (conf->ReduceNoise() && ++stripm[coord] > 1)
            continue;

        bool added = false;
        AidaCluster* cluster = nullptr;
        // Try to add the adc item to an existing cluster
        // Weird loop (not for) because we can combine clusters
        auto it = std::begin(clusters);
        while (it != std::end(clusters))
        {
            auto& j = *it;
            bool docluster = false;
            // Check options for which cluster
            if (j.HighEnergy && conf->ClusterImplants()) docluster = true;
            if (!j.HighEnergy && conf->ClusterDecays()) docluster = false;
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
            AidaCluster c_new;
            c_new.AddItem(i);
            clusters.push_back(c_new);
        }
    }

    // re-check multiplicty and destroy clusters with multiple same-strip
    if (conf->ReduceNoise())
    {
        auto it = std::begin(clusters);
        while (it != std::end(clusters))
        {
            auto& j = *it;
            bool destroy = false;
            for (int s = j.StripMin; s <= j.StripMax; s++)
            {
                aida_coord_t coord{j.DSSD, j.Side, s};
                if (stripm[coord] > 1) {
                    destroy = true;
                }
            }
            if (destroy) {
                it = clusters.erase(it);
                continue;
            }
            ++it;
        }
    }

    return clusters;
}

// Transform a pair (X, Y) of clusters into an AidaHit
AidaHit AidaCal2Hit::ClusterPairToHit(std::pair<AidaCluster, AidaCluster> const& i)
{
    // Debuggy sanity checks on the pair
    //c4LOG_IF(error, i.first.DSSD != i.second.DSSD, "Cluster pair of mismatched DSSDS");
    //c4LOG_IF(error, i.first.Side == i.second.Side, "Cluster pair not of X and Y");

    AidaHit hit;
    hit.DSSD = i.first.DSSD;

    hit.StripX = i.first.Strip;
    hit.StripY = i.second.Strip;
    // Position is in mm, with the centre as (0, 0)
    if (conf->Wide()) {
        hit.PosX = 226.8 * i.first.Strip / 386. - 113.45;
    }
    else {
        hit.PosX = 75.6 * i.first.Strip / 128. - 37.75;
    }
    hit.PosY = 75.6 * i.second.Strip / 128. - 37.75;

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
    // TODO: if one FastTime is 0, take the non-zero one
    hit.FastTime = std::min(i.first.FastTime, i.second.FastTime);
    hit.FastTimeX = i.first.FastTime;
    hit.FastTimeY = i.second.FastTime;

    return hit;
}

ClassImp(AidaCal2Hit)

void AidaCluster::Zero()
{
  DSSD = -1;
  Side = 0;
  HighEnergy = false;
  Energy = 0;
  Intensity = 0;
  Strip = 0;
  Time = 0;
  FastTime = 0;
  StripMin = 0;
  StripMax = 0;
  TimeMin = 0;
  TimeMax = 0;
  FastTimeMin = 0;
  FastTimeMax = 0;
  StripSum = 0;
  N = 0;
}

void AidaCluster::AddItem(AidaCalAdcItem const& item)
{
  if (DSSD == -1)
  {
    DSSD = item.DSSD();
    Side = item.Side();
    HighEnergy = item.Range();
    StripMin = item.Strip();
    StripMax = item.Strip();
    TimeMin = item.SlowTime();
    TimeMax = item.SlowTime();
    FastTimeMin = item.FastTime();
    FastTimeMax = item.FastTime();;
  }
  Energy += item.Energy();
  Intensity += item.Intensity();
  if(item.Strip() < StripMin) StripMin = item.Strip();
  if(item.Strip() > StripMax) StripMax = item.Strip();
  if(item.SlowTime() < TimeMin) TimeMin = item.SlowTime();
  if(item.SlowTime() > TimeMax) TimeMax = item.SlowTime();
  if(item.FastTime() < FastTimeMin) FastTimeMin = item.FastTime();
  if(item.FastTime() > FastTimeMax) FastTimeMax = item.FastTime();
  StripSum += item.Strip();
  Strip = (double)StripSum / ++N;
  Time = TimeMin;
  FastTime = FastTimeMin;
}

void AidaCluster::AddCluster(AidaCluster const& cluster)
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
  if (cluster.FastTimeMin < FastTimeMin) FastTimeMin = cluster.FastTimeMin;
  if (cluster.FastTimeMax > FastTimeMax) FastTimeMax = cluster.FastTimeMax;
  Energy += cluster.Energy;
  StripSum += cluster.StripSum;
  N += cluster.N;
  Strip = (double)StripSum / N;
  Time = TimeMin;
  FastTime = FastTimeMin;
}

bool AidaCluster::IsAdjacent(AidaCalAdcItem const& item) const
{
  if (DSSD == -1) return true;
  if (item.DSSD() != DSSD || item.Side() != Side) return false;
  if (item.Strip() >= StripMin - 1 && item.Strip() <= StripMax + 1) return true;
  return false;
}

bool AidaCluster::IsGoodTime(AidaCalAdcItem const& item, int window) const
{
  if (DSSD == -1) return true;

  if (item.SlowTime() >= TimeMin - window && item.SlowTime() <= TimeMax + window) return true;
  return false;
}

bool AidaCluster::IsGoodTime(AidaCluster const& event, int window) const
{
  if (DSSD == -1) return true;

  if (event.TimeMin >= TimeMin - window && event.TimeMin <= TimeMax + window) return true;
  if (event.TimeMax >= TimeMin - window && event.TimeMax <= TimeMax + window) return true;
  return false;
}

