#include "../c4source/fimp/FimpFineTimeBins.h"

#include <cassert>

int main()
{
    using fimp_fine_time_bins::RootBinForRawFineTime;

    // FIMP currently uses an 18-bin histogram for raw codes 0..17.
    assert(RootBinForRawFineTime(0) == 1);
    assert(RootBinForRawFineTime(1) == 2);
    assert(RootBinForRawFineTime(8) == 9);
    assert(RootBinForRawFineTime(17) == 18);

    // Every raw code must map to a unique regular histogram bin.
    for (int raw = 0; raw < 18; ++raw)
        assert(RootBinForRawFineTime(raw) > 0 &&
               RootBinForRawFineTime(raw) <= 18);
    return 0;
}
