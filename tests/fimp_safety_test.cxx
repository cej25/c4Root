#include "../c4source/fimp/FimpFineTimeBins.h"
#include "../c4source/fimp/FimpMultihitSafety.h"

#include <cassert>
#include <cstddef>
#include <limits>

static void TestMultihitBounds()
{
    using fimp_multihit_safety::MatchedHitCount;
    using fimp_multihit_safety::ValidPackedHitBlock;
    using fimp_multihit_safety::ValidFineTimeIndex;

    // Well-formed events reconstruct every pair.
    assert(MatchedHitCount(0, 0, 0, 0) == 0);
    assert(MatchedHitCount(1, 1, 1, 1) == 1);
    assert(MatchedHitCount(3, 3, 3, 3) == 3);

    // A short vector in any of the four positions limits reconstruction.
    assert(MatchedHitCount(1, 3, 3, 3) == 1);
    assert(MatchedHitCount(3, 1, 3, 3) == 1);
    assert(MatchedHitCount(3, 3, 1, 3) == 1);
    assert(MatchedHitCount(3, 3, 3, 1) == 1);
    assert(MatchedHitCount(0, 3, 3, 3) == 0);
    assert(MatchedHitCount(3, 0, 3, 3) == 0);
    assert(MatchedHitCount(3, 3, 0, 3) == 0);
    assert(MatchedHitCount(3, 3, 3, 0) == 0);

    // The calculation does not overflow with large size_t inputs.
    assert(MatchedHitCount(std::numeric_limits<std::size_t>::max(),
                           2, 3, 4) == 2);
    assert(ValidPackedHitBlock(0, 3, 3, 3, 3, 33024));
    assert(ValidPackedHitBlock(3, 3, 3, 3, 3, 33024));
    assert(!ValidPackedHitBlock(0, 4, 3, 4, 4, 33024));
    assert(!ValidPackedHitBlock(0, 4, 4, 3, 4, 33024));
    assert(!ValidPackedHitBlock(0, 4, 4, 4, 3, 33024));
    assert(!ValidPackedHitBlock(4, 3, 4, 4, 4, 33024));
    assert(!ValidPackedHitBlock(-1, 1, 4, 4, 4, 33024));
    assert(!ValidPackedHitBlock(0, 33025, 33025, 33025, 33025, 33024));
    assert(ValidFineTimeIndex(258, 259, 1023, 1024));
    assert(!ValidFineTimeIndex(258, 259, 1024, 1024));
    assert(ValidFineTimeIndex(0, 259, 0, 18));
    assert(ValidFineTimeIndex(258, 259, 17, 18));
    assert(!ValidFineTimeIndex(-1, 259, 0, 18));
    assert(!ValidFineTimeIndex(259, 259, 0, 18));
    assert(!ValidFineTimeIndex(258, 259, 18, 18));
    assert(!ValidFineTimeIndex(0, 259, 65535, 18));

}

static void TestFineTimeBins()
{
    using fimp_fine_time_bins::RootBinForRawFineTime;

    // FIMP currently uses an 18-bin histogram for raw codes 0..17.
    assert(RootBinForRawFineTime(0) == 1);
    assert(RootBinForRawFineTime(1) == 2);
    assert(RootBinForRawFineTime(8) == 9);
    assert(RootBinForRawFineTime(17) == 18);

    // Every raw code must map to a unique regular histogram bin.
    for (int raw = 0; raw < 18; ++raw)
        assert(RootBinForRawFineTime(raw) > 0 &&
               RootBinForRawFineTime(raw) <= 18);
}

int main()
{
    TestMultihitBounds();
    TestFineTimeBins();
}
