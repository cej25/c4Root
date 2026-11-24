#include "../c4source/base/StripClustering.h"

#include <cassert>
#include <cstdint>
#include <limits>

struct StripItem
{
    int DSSD;
    int Side;
    int Strip;
    std::int64_t AbsoluteTime;
    double Energy;
};

int main()
{
    using strip_clustering::IntervalsOverlap;
    assert(IntervalsOverlap(100, 200, 150, 250, 0));
    assert(IntervalsOverlap(100, 200, 100, 200, 0));
    assert(IntervalsOverlap(100, 200, 200, 220, 0));
    assert(IntervalsOverlap(100, 200, 50, 250, 0)); // Full containment.
    assert(IntervalsOverlap(50, 250, 100, 200, 0)); // Symmetric containment.
    assert(!IntervalsOverlap(100, 200, 211, 300, 10));
    assert(IntervalsOverlap(100, 200, 210, 300, 10));
    assert(IntervalsOverlap(210, 300, 100, 200, 10));
    assert(!IntervalsOverlap(100, 200, 210, 300, 9));
    assert(!IntervalsOverlap(200, 100, 150, 160, 0));
    assert(!IntervalsOverlap(100, 200, 150, 160, -1));

    // Production BB7/Stefan point-to-cluster matching now shares this helper.
    assert(IntervalsOverlap(100, 200, 100, 100, 0));
    assert(IntervalsOverlap(100, 200, 200, 200, 0));
    assert(IntervalsOverlap(100, 200, 90, 90, 10));
    assert(IntervalsOverlap(100, 200, 210, 210, 10));
    assert(!IntervalsOverlap(100, 200, 89, 89, 10));
    assert(!IntervalsOverlap(100, 200, 211, 211, 10));
    assert(!IntervalsOverlap(100, 200, 150, 150, -1));

    const auto low = std::numeric_limits<std::int64_t>::min();
    const auto high = std::numeric_limits<std::int64_t>::max();
    assert(!IntervalsOverlap(low, low, high, high, 100));
    assert(IntervalsOverlap(low, low + 5, low + 10, low + 15, 5));
    assert(IntervalsOverlap(high - 15, high - 10, high - 5, high, 5));
    assert(IntervalsOverlap(low, low + 10, low, low, 0));
    assert(IntervalsOverlap(high - 10, high, high, high, 0));
    assert(IntervalsOverlap(low + 10, low + 20, low, low, 10));
    assert(IntervalsOverlap(high - 20, high - 10, high, high, 10));
    assert(!IntervalsOverlap(low + 11, low + 20, low, low, 10));
    assert(!IntervalsOverlap(high - 20, high - 11, high, high, 10));
    assert(!IntervalsOverlap(low, low, high, high, high));
    // Strip 11 joins the clusters on strips 10 and 12. The other DSSD,
    // opposite side, out-of-window hit and invalid DSSD exercise the filters.
    const std::vector<StripItem> items{
        {0, 0, 10, 100, 1}, {0, 0, 12, 110, 2}, {0, 0, 11, 105, 3},
        {1, 0, 11, 105, 1}, {0, 1, 15, 105, 7}, {0, 0, 11, 121, 9},
        {-1, 0, 11, 105, 1}
    };
    const auto clusters = strip_clustering::BuildClusters(items, 10);
    assert(clusters.size() == 4);
    const auto& front = clusters[0];
    assert(front.N == 3 && front.Strip == 11 && front.Energy == 6);
    assert(front.StripMin == 10 && front.StripMax == 12);
    assert(front.Time == 100 && front.TimeMin == 100 && front.TimeMax == 110);
    assert(strip_clustering::MatchesFrontBack(front, clusters[2], 2, 0));
    assert(!strip_clustering::MatchesFrontBack(front, clusters[2], 1, 0));
    assert(!strip_clustering::MatchesFrontBack(front, clusters[1], 10, 0));
    return 0;
}
