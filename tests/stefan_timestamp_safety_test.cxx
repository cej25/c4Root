#include "../c4source/stefan/StefanTimestampSafety.h"

#include <cassert>
#include <cstdint>
#include <limits>

int main()
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
    return 0;
}
