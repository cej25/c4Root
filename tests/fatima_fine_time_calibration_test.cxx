#include "../c4source/fatima/FatimaFineTimeCalibration.h"

#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <stdexcept>

int main()
{
    fatima::FineTimeCalibration fine;
    // Same zero-occupancy linear fallback as the legacy reader.
    fine.Calculate();
    assert(fine.Entries() == 0);
    assert(fine.Time(0) == 0.0);
    assert(fine.Time(512) == 2.5);
    assert(fine.Time(1023) == 5.0 * 1023.0 / 1024.0);

    // Only valid raw leading edges are counted by the caller.
    fine.ObserveLeadingEdge(0);
    fine.ObserveLeadingEdge(0);
    fine.ObserveLeadingEdge(512);
    fine.ObserveLeadingEdge(1023); // TAMEX4 fast-filter failure
    fine.ObserveLeadingEdge(65536); // malformed word, not truncated
    fine.Calculate();
    assert(fine.Entries() == 3);
    assert(fine.Count(0) == 2);
    assert(fine.Count(512) == 1);
    assert(fine.Count(1023) == 0);
    assert(std::abs(fine.Time(0) - 5.0 / 3.0) < 1e-12);
    assert(std::abs(fine.Time(1) - 10.0 / 3.0) < 1e-12);
    assert(std::abs(fine.Time(512) - 25.0 / 6.0) < 1e-12);
    assert(std::abs(fine.Time(513) - 5.0) < 1e-12);

    // Loading an existing histogram must reproduce the same lookup table.
    std::array<std::uint64_t, 1024> histogram{};
    histogram[0] = 2;
    histogram[512] = 1;
    fatima::FineTimeCalibration from_file;
    from_file.SetCounts(histogram);
    from_file.Calculate();
    assert(from_file.Entries() == fine.Entries());
    for (std::size_t bin = 0; bin < 1024; ++bin)
        assert(from_file.Time(bin) == fine.Time(bin));

    bool rejected = false;
    try { (void)fine.Time(1024); }
    catch (const std::out_of_range&) { rejected = true; }
    assert(rejected);
    return 0;
}
