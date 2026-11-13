#include "../c4source/bgo/BGOPackedSafety.h"

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    using bgo_packed_safety::EventHitBudget;
    using bgo_packed_safety::ValidChannel;
    using bgo_packed_safety::ValidFineBin;

    assert(EventHitBudget(0) == 0);
    assert(EventHitBudget(4) == 0);
    assert(EventHitBudget(8) == 0);
    assert(EventHitBudget(11) == 0);
    assert(EventHitBudget(12) == 0);
    assert(EventHitBudget(16) == 1);
    assert(EventHitBudget(20) == 2);
    assert(EventHitBudget(4 * (1024 + 3)) == 1024);
    assert(EventHitBudget(std::numeric_limits<std::uint32_t>::max()) == 1024);

    assert(ValidChannel(0));
    assert(ValidChannel(32));
    assert(!ValidChannel(33));
    assert(!ValidChannel(127));
    assert(!ValidChannel(std::numeric_limits<std::uint32_t>::max()));
    assert(ValidFineBin(0));
    assert(ValidFineBin(1023));
    assert(!ValidFineBin(1024));
    assert(!ValidFineBin(65535));
    return 0;
}
