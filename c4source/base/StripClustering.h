#ifndef STRIP_CLUSTERING_H
#define STRIP_CLUSTERING_H

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

namespace strip_clustering
{
// Order endpoints before subtracting as unsigned to cover the full int64 range.
inline bool IntervalsOverlap(std::int64_t a_min, std::int64_t a_max,
                             std::int64_t b_min, std::int64_t b_max,
                             std::int64_t tolerance)
{
    if (tolerance < 0 || a_min > a_max || b_min > b_max) return false;
    const auto allowed = static_cast<std::uint64_t>(tolerance);
    if (a_min > b_max)
    {
        return static_cast<std::uint64_t>(a_min) -
               static_cast<std::uint64_t>(b_max) <= allowed;
    }
    if (b_min > a_max)
    {
        return static_cast<std::uint64_t>(b_min) -
               static_cast<std::uint64_t>(a_max) <= allowed;
    }
    return true;
}

struct StripCluster
{
    int DSSD = -1;
    int Side = 0;
    int Strip = 0;
    double Energy = 0;
    std::int64_t Time = 0;

    int StripMin = 0;
    int StripMax = 0;
    std::int64_t TimeMin = 0;
    std::int64_t TimeMax = 0;

    int StripSum = 0;
    int N = 0;

    template <typename Item>
    bool Matches(const Item& item, int window) const
    {
        return item.DSSD == DSSD && item.Side == Side &&
               item.Strip >= StripMin - 1 && item.Strip <= StripMax + 1 &&
               IntervalsOverlap(TimeMin, TimeMax, item.AbsoluteTime, item.AbsoluteTime, window);
    }

    template <typename Item>
    void AddItem(const Item& item)
    {
        const std::int64_t time = item.AbsoluteTime;
        if (N == 0)
        {
            DSSD = item.DSSD;
            Side = item.Side;
            StripMin = StripMax = item.Strip;
            TimeMin = TimeMax = time;
        }
        StripMin = std::min(StripMin, item.Strip);
        StripMax = std::max(StripMax, item.Strip);
        TimeMin = std::min(TimeMin, time);
        TimeMax = std::max(TimeMax, time);
        Energy += item.Energy;
        StripSum += item.Strip;
        Strip = StripSum / ++N;
        Time = TimeMin;
    }

    void Merge(const StripCluster& other)
    {
        StripMin = std::min(StripMin, other.StripMin);
        StripMax = std::max(StripMax, other.StripMax);
        TimeMin = std::min(TimeMin, other.TimeMin);
        TimeMax = std::max(TimeMax, other.TimeMax);
        Energy += other.Energy;
        StripSum += other.StripSum;
        N += other.N;
        Strip = StripSum / N;
        Time = TimeMin;
    }
};

template <typename Item>
std::vector<StripCluster> BuildClusters(const std::vector<Item>& items, int window = 2000)
{
    std::vector<StripCluster> clusters;
    for (const auto& item : items)
    {
        if (item.DSSD == -1) continue;

        StripCluster* first = nullptr;
        for (auto cluster = clusters.begin(); cluster != clusters.end();)
        {
            if (!cluster->Matches(item, window))
            {
                ++cluster;
                continue;
            }
            if (first == nullptr)
            {
                first = &*cluster;
                first->AddItem(item);
                ++cluster;
                continue;
            }

            // This strip joins two clusters. Erasing the later one leaves the first valid.
            first->Merge(*cluster);
            cluster = clusters.erase(cluster);
        }
        if (first == nullptr) clusters.emplace_back().AddItem(item);
    }
    return clusters;
}

inline bool MatchesFrontBack(const StripCluster& front, const StripCluster& back,
                             double energyWindow, int timeWindow)
{
    return front.Side == 0 && back.Side == 1 && front.DSSD == back.DSSD &&
           std::abs(front.Energy - back.Energy) < energyWindow &&
           IntervalsOverlap(front.TimeMin, front.TimeMax, back.TimeMin, back.TimeMax, timeWindow);
}

template <typename Hit>
Hit MakeHit(const StripCluster& front, const StripCluster& back)
{
    Hit hit;
    hit.DSSD = front.DSSD;
    hit.StripX = front.Strip;
    hit.StripY = back.Strip;
    hit.StripXMin = front.StripMin;
    hit.StripXMax = front.StripMax;
    hit.StripYMin = back.StripMin;
    hit.StripYMax = back.StripMax;
    hit.ClusterSizeX = front.N;
    hit.ClusterSizeY = back.N;
    hit.Energy = (front.Energy + back.Energy) / 2.;
    hit.EnergyX = front.Energy;
    hit.EnergyY = back.Energy;
    hit.Time = std::min(front.Time, back.Time);
    hit.TimeX = front.Time;
    hit.TimeY = back.Time;
    return hit;
}
} // namespace strip_clustering

#endif
