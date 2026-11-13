#include "../c4source/fimp/FimpMultihitSafety.h"

#include <cassert>
#include <cstddef>
#include <limits>

int main()
{
    using fimp_multihit_safety::MatchedHitCount;

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
    return 0;
}
