#ifndef FEBEX_SUMMARY_H
#define FEBEX_SUMMARY_H

#include "ext_h101_febex.h"

#include <cstdint>
#include <iterator>

namespace febex
{
constexpr unsigned ChannelsPerBoard = 16;

inline std::uint64_t JoinTicks(std::uint32_t high, std::uint32_t low)
{
    return (std::uint64_t{high} << 32) | low;
}

inline std::uint64_t WhiteRabbitTimestamp(const EXT_STR_h101_febex_onion& bank)
{
    std::uint64_t timestamp = 0;
    for (unsigned word = 0; word < std::size(bank.FEBEX_WR_T); ++word)
        timestamp |= std::uint64_t{bank.FEBEX_WR_T[word]} << (16 * word);
    return timestamp;
}

// UCESB exports six parallel zero-suppressed columns. Their indices are
// one-based and ordered by (slot, channel), including hits with zero values.
inline bool ValidSummary(const EXT_STR_h101_febex_onion& bank)
{
    const auto count = bank.FEBEX_HITHI;
    if (count > std::size(bank.FEBEX_HITHII) || count != bank.FEBEX_HITLO ||
        count != bank.FEBEX_ENERGY || count != bank.FEBEX_CFD ||
        count != bank.FEBEX_PILEUP || count != bank.FEBEX_OVERFLOW)
        return false;

    std::uint32_t previous = 0;
    for (std::uint32_t i = 0; i < count; ++i)
    {
        const auto index = bank.FEBEX_HITHII[i];
        if (index <= previous || index > std::size(bank.FEBEX_HITHII) ||
            index != bank.FEBEX_HITLOI[i] || index != bank.FEBEX_ENERGYI[i] ||
            index != bank.FEBEX_CFDI[i] || index != bank.FEBEX_PILEUPI[i] ||
            index != bank.FEBEX_OVERFLOWI[i] ||
            !bank.FEBEX_PRESENT[(index - 1) / ChannelsPerBoard])
            return false;
        previous = index;
    }
    return true;
}
}

#endif
