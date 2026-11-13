#include "../c4source/frs/FrsReaderSafety.h"

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    using frs_reader_safety::AssembleWhiteRabbitTimestamp;
    using frs_reader_safety::ValidPackedBlock;
    using frs_reader_safety::ValidOneBasedChannel;
    using frs_reader_safety::ZeroDetectorArray;

    // The four 16-bit input words are in least-significant-first order.
    assert(AssembleWhiteRabbitTimestamp(0, 0, 0, 0) == 0);
    assert(AssembleWhiteRabbitTimestamp(0x5678, 0x1234, 0xdef0, 0x9abc) ==
           UINT64_C(0x9abcdef012345678));
    assert(AssembleWhiteRabbitTimestamp(0xffff, 0xffff, 0xffff, 0x7fff) ==
           static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()));
    assert(AssembleWhiteRabbitTimestamp(0, 0, 0, 0x8000) ==
           (UINT64_C(1) << 63));
    assert(AssembleWhiteRabbitTimestamp(0xffff, 0xffff, 0xffff, 0xffff) ==
           std::numeric_limits<std::uint64_t>::max());

    // Valid endpoints may equal the populated counts or the array capacity.
    assert(ValidPackedBlock(0, 2, 2, 2, 4096));
    assert(ValidPackedBlock(2, 2, 2, 2, 4096));
    assert(ValidPackedBlock(0, 1024, 1024, 1024, 1024));

    // Incomplete, descending, negative and oversized packed blocks are rejected.
    assert(!ValidPackedBlock(0, 3, 2, 3, 4096));
    assert(!ValidPackedBlock(0, 3, 3, 2, 4096));
    assert(!ValidPackedBlock(3, 2, 4, 4, 4096));
    assert(!ValidPackedBlock(-1, 2, 4, 4, 4096));
    assert(!ValidPackedBlock(0, -1, 4, 4, 4096));
    assert(!ValidPackedBlock(0, 1025, 1025, 1025, 1024));
    assert(!ValidPackedBlock(0, 1, 0, 0, 4096));

    // The same one-based channel guards used by SCI, MUSIC and TPC.
    assert(ValidOneBasedChannel(1, 32));
    assert(ValidOneBasedChannel(32, 32));
    assert(!ValidOneBasedChannel(0, 32));
    assert(!ValidOneBasedChannel(33, 32));
    assert(!ValidOneBasedChannel(-1, 32));
    assert(ValidOneBasedChannel(8, 8));
    assert(!ValidOneBasedChannel(9, 8));
    assert(ValidOneBasedChannel(128, 128));
    assert(!ValidOneBasedChannel(129, 128));
    assert(!ValidOneBasedChannel(1, 0));

    // Reproduce all five FrsReader fixed-array shapes used by Reset().
    // Fill every element, including the last channel/row, as event 1 data.
    std::uint32_t sciDE[32], sciDT[32], musicE[5][8], musicT[5][8], adcData[7][8];
    for (auto &value : sciDE) value = 123;
    for (auto &value : sciDT) value = 456;
    for (auto &row : musicE) for (auto &value : row) value = 789;
    for (auto &row : musicT) for (auto &value : row) value = 321;
    for (auto &row : adcData) for (auto &value : row) value = 654;

    // Event 2 has no new hits; every element must be reset to zero.
    ZeroDetectorArray(sciDE);
    ZeroDetectorArray(sciDT);
    ZeroDetectorArray(musicE);
    ZeroDetectorArray(musicT);
    ZeroDetectorArray(adcData);
    for (auto value : sciDE) assert(value == 0);
    for (auto value : sciDT) assert(value == 0);
    for (const auto &row : musicE) for (auto value : row) assert(value == 0);
    for (const auto &row : musicT) for (auto value : row) assert(value == 0);
    for (const auto &row : adcData) for (auto value : row) assert(value == 0);

    return 0;
}
