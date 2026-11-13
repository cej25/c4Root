#include "../c4source/germanium/GermaniumPackedSafety.h"

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    using germanium_packed_safety::CompleteChannelCount;
    using germanium_packed_safety::ValidTraceChannel;

    assert(CompleteChannelCount(0, 0, 0, 0, 0, 0) == 0);
    assert(CompleteChannelCount(1, 1, 1, 1, 1, 1) == 1);
    assert(CompleteChannelCount(16, 16, 16, 16, 16, 16) == 16);
    assert(CompleteChannelCount(99, 99, 99, 99, 99, 99) == 16);
    assert(CompleteChannelCount(1, 2, 2, 2, 2, 2) == 1);
    assert(CompleteChannelCount(2, 1, 2, 2, 2, 2) == 1);
    assert(CompleteChannelCount(2, 2, 1, 2, 2, 2) == 1);
    assert(CompleteChannelCount(2, 2, 2, 1, 2, 2) == 1);
    assert(CompleteChannelCount(2, 2, 2, 2, 1, 2) == 1);
    assert(CompleteChannelCount(2, 2, 2, 2, 2, 1) == 1);
    assert(CompleteChannelCount(2, 2, 2, 2, 2, 0) == 0);

    assert(ValidTraceChannel(1));
    assert(ValidTraceChannel(16));
    assert(!ValidTraceChannel(0));
    assert(!ValidTraceChannel(17));
    assert(!ValidTraceChannel(std::numeric_limits<std::uint32_t>::max()));
    return 0;
}
