#include "../c4source/base/TamexPackedSafety.h"

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    using namespace c4_tamex_packed_safety;

    assert(EventHitBudget(0) == 0);
    assert(EventHitBudget(4) == 0);
    assert(EventHitBudget(8) == 0);
    assert(EventHitBudget(11) == 0);
    assert(EventHitBudget(12) == 0);
    assert(EventHitBudget(16) == 1);
    assert(EventHitBudget(20) == 2);
    assert(EventHitBudget(4 * (1024 + 3)) == 1024);
    assert(EventHitBudget(std::numeric_limits<std::uint32_t>::max()) == 1024);

    assert(ValidChannel(0, 33));
    assert(ValidChannel(32, 33));
    assert(!ValidChannel(33, 33));
    assert(!ValidChannel(127, 33));
    assert(!ValidChannel(0, 0));

    assert(ValidFineBin(0, 1024));
    assert(ValidFineBin(1023, 1024));
    assert(!ValidFineBin(1024, 1024));
    assert(!ValidFineBin(65535, 1024));

    assert(HasCompleteHit(0, 1, 1, 1, 1, 1));
    assert(HasCompleteHit(15, 16, 16, 16, 16, 16));
    assert(!HasCompleteHit(1, 1, 2, 2, 2, 2));
    assert(!HasCompleteHit(1, 2, 1, 2, 2, 2));
    assert(!HasCompleteHit(1, 2, 2, 1, 2, 2));
    assert(!HasCompleteHit(1, 2, 2, 2, 1, 2));
    assert(!HasCompleteHit(1, 2, 2, 2, 2, 1));
    return 0;
}
