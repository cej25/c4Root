#include "../c4source/base/ClusterTimeOverlap.h"

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    using c4_cluster_time::IntervalsOverlap;
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

    const auto low = std::numeric_limits<std::int64_t>::min();
    const auto high = std::numeric_limits<std::int64_t>::max();
    assert(!IntervalsOverlap(low, low, high, high, 100));
    assert(IntervalsOverlap(low, low + 5, low + 10, low + 15, 5));
    assert(IntervalsOverlap(high - 15, high - 10, high - 5, high, 5));
    return 0;
}
