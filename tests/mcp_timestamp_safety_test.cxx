#include "../c4source/mcp/McpTimestampSafety.h"

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    using mcp_timestamp_safety::AssembleWhiteRabbitTimestamp;
    assert(AssembleWhiteRabbitTimestamp(0, 0, 0, 0) == 0);
    assert(AssembleWhiteRabbitTimestamp(0x5678, 0x1234, 0xdef0, 0x9abc) ==
           UINT64_C(0x9abcdef012345678));
    assert(AssembleWhiteRabbitTimestamp(0xffff, 0xffff, 0xffff, 0x7fff) ==
           static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()));
    assert(AssembleWhiteRabbitTimestamp(0, 0, 0, 0x8000) ==
           (UINT64_C(1) << 63));
    assert(AssembleWhiteRabbitTimestamp(0xffff, 0xffff, 0xffff, 0xffff) ==
           std::numeric_limits<std::uint64_t>::max());
    assert(AssembleWhiteRabbitTimestamp(0x10001, 0x10002, 0x10003, 0x10004) ==
           UINT64_C(0x0004000300020001));
    return 0;
}
