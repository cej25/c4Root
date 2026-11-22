#include "../c4source/stefan/StefanIndexSafety.h"
#include "../c4source/stefan/StefanPackedSafety.h"
#include "../c4source/stefan/StefanTimestampSafety.h"

#include <cassert>
#include <cstdint>
#include <limits>

static void TestDetectorIndices()
{
    using stefan_index_safety::ValidDssd;

    assert(ValidDssd(0, 1));
    assert(ValidDssd(0, 3));
    assert(ValidDssd(2, 3));

    assert(!ValidDssd(-1, 3));
    assert(!ValidDssd(-2, 3));
    assert(!ValidDssd(3, 3));
    assert(!ValidDssd(4, 3));
    assert(!ValidDssd(0, 0));
}

static void TestPackedChannels()
{
    using stefan_packed_safety::CompleteChannelCount;

    assert(CompleteChannelCount(0, 0, 0, 0, 0) == 0);
    assert(CompleteChannelCount(1, 1, 1, 1, 1) == 1);
    assert(CompleteChannelCount(16, 16, 16, 16, 16) == 16);
    assert(CompleteChannelCount(17, 17, 17, 17, 17) == 16);

    // Each independently unpacked array can be shorter than the energy list.
    assert(CompleteChannelCount(4, 3, 4, 4, 4) == 3);
    assert(CompleteChannelCount(4, 4, 2, 4, 4) == 2);
    assert(CompleteChannelCount(4, 4, 4, 1, 4) == 1);
    assert(CompleteChannelCount(4, 4, 4, 4, 0) == 0);
    assert(CompleteChannelCount(2, 4, 4, 4, 4) == 2);
}

static void TestWhiteRabbit()
{
    using stefan_timestamp_safety::AssembleWhiteRabbitTimestamp;

    assert(AssembleWhiteRabbitTimestamp(0, 0, 0, 0) == 0);
    assert(AssembleWhiteRabbitTimestamp(0x5678, 0x1234, 0xdef0, 0x9abc) ==
           UINT64_C(0x9abcdef012345678));
    assert(AssembleWhiteRabbitTimestamp(0xffff, 0xffff, 0xffff, 0x7fff) ==
           static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()));
    assert(AssembleWhiteRabbitTimestamp(0, 0, 0, 0x8000) ==
           (UINT64_C(1) << 63));
    assert(AssembleWhiteRabbitTimestamp(0xffff, 0xffff, 0xffff, 0xffff) ==
           std::numeric_limits<std::uint64_t>::max());
}

int main()
{
    TestDetectorIndices();
    TestPackedChannels();
    TestWhiteRabbit();
}
