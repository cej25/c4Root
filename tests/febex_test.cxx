#include "../c4source/bb7/BB7FebexIndexSafety.h"
#include "../c4source/digitisers/febex/FebexConversions.h"
#include "../c4source/germanium/GermaniumCalibration.h"
#include "../c4source/germanium/GermaniumPackedSafety.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <map>
#include <vector>

static void TestTimestampAndEnergyConversions()
{
    using febex::LegacyHitOffsetNs;
    constexpr std::uint64_t periodNs = (std::uint64_t{1} << 24) * 10;
    constexpr std::uint64_t fullPeriodNs = (std::uint64_t{1} << 48) * 10;

    static_assert(LegacyHitOffsetNs(1000, 1015.15625) == 15);
    static_assert(LegacyHitOffsetNs(1000, 797.96875) == -203);
    static_assert(LegacyHitOffsetNs(2772411 * periodNs + 1000, 797.96875) == -203);
    static_assert(LegacyHitOffsetNs(periodNs - 10, 5.15625) == 15);
    static_assert(LegacyHitOffsetNs(periodNs + 10, periodNs - 14.84375) == -25);
    static_assert(LegacyHitOffsetNs(fullPeriodNs - 10, 5.15625) == 15);
    constexpr std::uint64_t counterMask = (std::uint64_t{1} << 48) - 1;
    static_assert(febex::HitOffsetNs(100, 79, 51) == -203);
    static_assert(febex::HitOffsetNs(counterMask, 0, 33) == 15);
    static_assert(febex::HitOffsetNs(0, counterMask, 33) == -5);
    static_assert(febex::LegacyChannelTimeNs(0x1000001, 33) == 15.15625);
    static_assert(febex::GammaSignedEnergy(0x123456) == 0x123456);
    static_assert(febex::GammaSignedEnergy(0x923456) == -0x123456);

    // The paths agree for physically nearby hits throughout both counter wraps.
    for (auto event : {0ULL, 100ULL, 0xffffffULL, 0x1000000ULL, 46513338187776ULL,
                       0xffffffffffffULL})
    {
        for (int delta = -1900; delta <= 1900; delta += 19)
        {
            const auto channel = (event + delta) & counterMask;
            for (std::uint8_t cfd = 0; cfd < 64; ++cfd)
                assert(febex::HitOffsetNs(event, channel, cfd) ==
                       LegacyHitOffsetNs(event * 10, febex::LegacyChannelTimeNs(channel, cfd)));
        }
    }
}

static void TestGermaniumCalibration()
{
    using Address = std::pair<int, int>;
    const std::map<Address, Address> mapping{{{1, 2}, {3, 4}}, {{1, 5}, {-1, 0}},
                                             {{1, 6}, {4, 0}}};
    const std::map<Address, std::vector<double>> coefficients{{{3, 4}, {1, 2, 3}}};
    const auto hit = germanium::CalibrateHit(mapping, coefficients, 1, 2, -4, true);
    assert(hit && hit->detector == 3 && hit->crystal == 4 && hit->energy == 41);
    assert(germanium::CalibrateHit(mapping, coefficients, 1, 2, -4, false)->energy == -4);
    assert(germanium::CalibrateHit(mapping, coefficients, 1, 6, -4, true)->energy == -4);
    assert(!germanium::CalibrateHit(mapping, coefficients, 1, 5, -4, true));
    assert(!germanium::CalibrateHit(mapping, coefficients, 1, 7, -4, true));
}

static void TestGermaniumPackedBounds()
{
    using germanium_packed_safety::CompleteChannelCount;
    using germanium_packed_safety::ValidTraceChannel;
    using germanium_packed_safety::PopulatedTraceSamples;

    assert(CompleteChannelCount(0, 0, 0, 0, 0, 0) == 0);
    assert(CompleteChannelCount(1, 1, 1, 1, 1, 1) == 1);
    assert(CompleteChannelCount(16, 16, 16, 16, 16, 16) == 16);
    assert(CompleteChannelCount(99, 99, 99, 99, 99, 99) == 16);
    assert(CompleteChannelCount(1, 2, 2, 2, 2, 2) == 1);
    assert(CompleteChannelCount(2, 1, 2, 2, 2, 2) == 1);
    assert(CompleteChannelCount(2, 2, 1, 2, 2, 2) == 1);
    assert(CompleteChannelCount(2, 2, 2, 1, 2, 2) == 1);
    assert(CompleteChannelCount(2, 2, 2, 2, 1, 2) == 1);
    assert(CompleteChannelCount(2, 2, 2, 2, 2, 1) == 1);
    assert(CompleteChannelCount(2, 2, 2, 2, 2, 0) == 0);

    assert(ValidTraceChannel(1));
    assert(ValidTraceChannel(16));
    assert(!ValidTraceChannel(0));
    assert(!ValidTraceChannel(17));
    assert(!ValidTraceChannel(std::numeric_limits<std::uint32_t>::max()));
    assert(PopulatedTraceSamples(0) == 0);
    assert(PopulatedTraceSamples(1) == 1);
    assert(PopulatedTraceSamples(1250) == 1250);
    assert(PopulatedTraceSamples(4000) == 4000);
    assert(PopulatedTraceSamples(4001) == 4000);
    assert(PopulatedTraceSamples(std::numeric_limits<std::uint32_t>::max()) == 4000);
}

static void TestBB7Indices()
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
}

int main()
{
    TestTimestampAndEnergyConversions();
    TestGermaniumCalibration();
    TestGermaniumPackedBounds();
    TestBB7Indices();
}
