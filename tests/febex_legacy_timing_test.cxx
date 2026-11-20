#include "../c4source/digitisers/febex/FebexTiming.h"

#include <cstdint>

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
    return 0;
}
