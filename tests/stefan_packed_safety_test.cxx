#include "../c4source/stefan/StefanPackedSafety.h"

#include <cassert>
#include <cstdint>

int main()
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
    return 0;
}
