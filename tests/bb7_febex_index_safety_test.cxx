#include "../c4source/bb7/BB7FebexIndexSafety.h"

#include <cassert>
#include <cstddef>

int main()
{
    using bb7_febex_index_safety::ValidDssd;
    using bb7_febex_index_safety::TryChannelIndex;

    assert(ValidDssd(0, 3));
    assert(ValidDssd(2, 3));
    assert(!ValidDssd(-1, 3));
    assert(!ValidDssd(3, 3));
    assert(!ValidDssd(0, 0));

    std::size_t index = 999;
    assert(TryChannelIndex(0, 0, 0, 3, index) && index == 0);
    assert(TryChannelIndex(0, 1, 31, 3, index) && index == 63);
    assert(TryChannelIndex(1, 0, 0, 3, index) && index == 64);
    assert(TryChannelIndex(2, 1, 31, 3, index) && index == 191);

    assert(!TryChannelIndex(-1, 0, 0, 3, index));
    assert(!TryChannelIndex(3, 0, 0, 3, index));
    assert(!TryChannelIndex(0, -1, 0, 3, index));
    assert(!TryChannelIndex(0, 2, 0, 3, index));
    assert(!TryChannelIndex(0, 0, -1, 3, index));
    assert(!TryChannelIndex(0, 0, 32, 3, index));
    assert(!TryChannelIndex(0, 0, 0, 0, index));
    return 0;
}
