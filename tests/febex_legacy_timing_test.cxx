#include "../c4source/digitisers/febex/FebexConversions.h"

#include "../c4source/germanium/GermaniumCalibration.h"

#include <cassert>
#include <cstdint>
#include <map>
#include <vector>

int main()
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
    return 0;
}
