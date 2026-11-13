#include "../c4source/fatima/FatimaVmePackedSafety.h"

#include <cassert>
#include <cstdint>
#include <limits>

int main()
{
    using namespace fatima_vme_packed_safety;

    assert(ValidTdcBlock(0, 1, 1, 1));
    assert(ValidTdcBlock(1, 2, 2, 2));
    assert(ValidTdcBlock(2, 2, 2, 2));
    assert(ValidTdcBlock(0, 16384, 16384, 16384));
    assert(!ValidTdcBlock(3, 2, 3, 3));
    assert(!ValidTdcBlock(0, 2, 1, 2));
    assert(!ValidTdcBlock(0, 2, 2, 1));
    assert(!ValidTdcBlock(0, 16385, 16385, 16385));
    assert(!ValidTdcBlock(0, std::numeric_limits<std::uint32_t>::max(), 10, 10));

    assert(BoundedBlockCount(0) == 0);
    assert(BoundedBlockCount(1) == 1);
    assert(BoundedBlockCount(128) == 128);
    assert(BoundedBlockCount(129) == 128);
    assert(BoundedBlockCount(std::numeric_limits<std::uint32_t>::max()) == 128);
    return 0;
}
