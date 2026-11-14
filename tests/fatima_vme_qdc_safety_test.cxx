#include "../c4source/fatima/FatimaVmeQdcSafety.h"

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    using namespace fatima_vme_qdc_safety;

    assert(CompleteEntry(0, 1, 1, 1, 1, 1));
    assert(CompleteEntry(7, 8, 8, 8, 8, 8));
    assert(CompleteEntry(63, 64, 64, 64, 64, 64));
    assert(!CompleteEntry(64, 100, 100, 100, 100, 100));
    assert(!CompleteEntry(1, 1, 2, 2, 2, 2));
    assert(!CompleteEntry(1, 2, 1, 2, 2, 2));
    assert(!CompleteEntry(1, 2, 2, 1, 2, 2));
    assert(!CompleteEntry(1, 2, 2, 2, 1, 2));
    assert(!CompleteEntry(1, 2, 2, 2, 2, 1));

    assert(CompleteWaveformTriplets(0, 120, 120) == 0);
    assert(CompleteWaveformTriplets(1, 1, 1) == 1);
    assert(CompleteWaveformTriplets(120, 120, 120) == 120);
    assert(CompleteWaveformTriplets(224, 224, 224) == 120);
    assert(CompleteWaveformTriplets(80, 90, 100) == 80);
    assert(CompleteWaveformTriplets(100, 80, 90) == 80);
    assert(CompleteWaveformTriplets(100, 90, 80) == 80);
    assert(CompleteWaveformTriplets(std::numeric_limits<std::uint32_t>::max(),
                                   120, 120) == 120);
    return 0;
}
