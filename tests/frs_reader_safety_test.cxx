#include "../c4source/frs/FrsReaderSafety.h"

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    using frs_reader_safety::AssembleWhiteRabbitTimestamp;
    using frs_reader_safety::ValidPackedBlock;

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

    return 0;
}
