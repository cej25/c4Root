#include "../c4source/digitisers/clocktdc/ClockTdcReader.h"
#include "../c4source/fimp/ext_h101_fimp.h"
#include "../c4source/fimp/FimpFineTimeBins.h"
#include "../c4source/fimp/FimpMultihitSafety.h"

#include <cassert>
#include <cstddef>
#include <limits>
#include <vector>

static void TestMultihitBounds()
{
    using fimp_multihit_safety::MatchedHitCount;
    using fimp_multihit_safety::ValidFineTimeIndex;

    // Well-formed events reconstruct every pair.
    assert(MatchedHitCount(0, 0, 0, 0) == 0);
    assert(MatchedHitCount(1, 1, 1, 1) == 1);
    assert(MatchedHitCount(3, 3, 3, 3) == 3);

    // A short vector in any of the four positions limits reconstruction.
    assert(MatchedHitCount(1, 3, 3, 3) == 1);
    assert(MatchedHitCount(3, 1, 3, 3) == 1);
    assert(MatchedHitCount(3, 3, 1, 3) == 1);
    assert(MatchedHitCount(3, 3, 3, 1) == 1);
    assert(MatchedHitCount(0, 3, 3, 3) == 0);
    assert(MatchedHitCount(3, 0, 3, 3) == 0);
    assert(MatchedHitCount(3, 3, 0, 3) == 0);
    assert(MatchedHitCount(3, 3, 3, 0) == 0);

    // The calculation does not overflow with large size_t inputs.
    assert(MatchedHitCount(std::numeric_limits<std::size_t>::max(),
                           2, 3, 4) == 2);
    assert(ValidFineTimeIndex(258, 259, 1023, 1024));
    assert(!ValidFineTimeIndex(258, 259, 1024, 1024));
    assert(ValidFineTimeIndex(0, 259, 0, 18));
    assert(ValidFineTimeIndex(258, 259, 17, 18));
    assert(!ValidFineTimeIndex(-1, 259, 0, 18));
    assert(!ValidFineTimeIndex(259, 259, 0, 18));
    assert(!ValidFineTimeIndex(258, 259, 18, 18));
    assert(!ValidFineTimeIndex(0, 259, 65535, 18));

}

static void TestClockTdcEdges()
{
    static_assert(clocktdc::TriggerCoarseTime(2, 3) == (std::uint64_t{2} << 22) + 3);
    EXT_STR_h101_fimp_onion_t bank{};
    const auto read = [&bank] {
        std::vector<clocktdc::RawEdge> edges;
        clocktdc::ReadEdges(bank.fimp_data_time_coarseM,
            bank.fimp_data_time_coarseMI, bank.fimp_data_time_coarseME,
            clocktdc::PackedColumn{bank.fimp_data_time_coarse, bank.fimp_data_time_coarsev},
            clocktdc::PackedColumn{bank.fimp_data_time_fine, bank.fimp_data_time_finev},
            clocktdc::PackedColumn{bank.fimp_data_lead_or_trail, bank.fimp_data_lead_or_trailv},
            [&](const auto& edge) { edges.push_back(edge); });
        return edges;
    };
    assert(read().empty());

    bank.fimp_data_time_coarseM = 300; // Limit the walk to the generated array capacity.
    bank.fimp_data_time_coarse = bank.fimp_data_time_fine = bank.fimp_data_lead_or_trail = 6;
    const std::uint32_t indices[] = {1, 0, 2, 3, 257, 258};
    const std::uint32_t ends[] = {2, 3, 4, 3, 5, 6}; // Block 3 ends before its start.
    for (std::size_t i = 0; i < 6; ++i)
    {
        bank.fimp_data_time_coarseMI[i] = indices[i];
        bank.fimp_data_time_coarseME[i] = ends[i];
        bank.fimp_data_time_coarsev[i] = 100 + i;
        bank.fimp_data_time_finev[i] = i;
    }
    bank.fimp_data_lead_or_trailv[3] = 0x81;
    bank.fimp_data_lead_or_trailv[5] = 1;

    const auto edges = read();
    assert(edges.size() == 5);
    assert(edges[0].sparseIndex == 1 && edges[0].channel == 0 && !edges[0].trailing);
    assert(edges[1].coarse == 101 && edges[1].fine == 1);
    assert(edges[2].channel == 0 && edges[2].trailing && edges[2].coarse == 103);
    assert(edges[3].sparseIndex == 257 && edges[3].channel == 128 && !edges[3].trailing);
    assert(edges[4].sparseIndex == 258 && edges[4].trailing);
    for (auto* count : {&bank.fimp_data_time_coarse, &bank.fimp_data_time_fine,
                        &bank.fimp_data_lead_or_trail})
    {
        *count = 4;
        assert(read().size() == 3);
        *count = 6;
    }

    bank.fimp_data_time_coarseM = 1;
    bank.fimp_data_time_coarseME[0] = bank.fimp_data_time_coarse =
        bank.fimp_data_time_fine = bank.fimp_data_lead_or_trail = 33025;
    assert(read().empty());
}

static void TestFineTimeBins()
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
}

int main()
{
    TestMultihitBounds();
    TestClockTdcEdges();
    TestFineTimeBins();
}
