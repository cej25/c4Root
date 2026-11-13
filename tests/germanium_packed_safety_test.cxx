#include "../c4source/germanium/GermaniumPackedSafety.h"

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    using germanium_packed_safety::CompleteChannelCount;
    using germanium_packed_safety::ValidTraceChannel;
    using germanium_packed_safety::PopulatedTraceSamples;

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
    assert(PopulatedTraceSamples(0) == 0);
    assert(PopulatedTraceSamples(1) == 1);
    assert(PopulatedTraceSamples(1250) == 1250);
    assert(PopulatedTraceSamples(4000) == 4000);
    assert(PopulatedTraceSamples(4001) == 4000);
    assert(PopulatedTraceSamples(std::numeric_limits<std::uint32_t>::max()) == 4000);
    return 0;
}
