#include "../c4source/fimp/FimpMultihitSafety.h"

#include <cassert>
#include <cstddef>
#include <limits>

int main()
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
    assert(ValidFineTimeIndex(0, 259, 0, 18));
    assert(ValidFineTimeIndex(258, 259, 17, 18));
    assert(!ValidFineTimeIndex(-1, 259, 0, 18));
    assert(!ValidFineTimeIndex(259, 259, 0, 18));
    assert(!ValidFineTimeIndex(258, 259, 18, 18));
    assert(!ValidFineTimeIndex(0, 259, 65535, 18));

    return 0;
}
