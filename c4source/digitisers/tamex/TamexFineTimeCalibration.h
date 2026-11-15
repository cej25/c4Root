#ifndef TAMEX_FINE_TIME_CALIBRATION_H
#define TAMEX_FINE_TIME_CALIBRATION_H

#include <array>
#include <cstddef>
#include <cstdint>

#include "TamexDecoder.h"

namespace tamex
{
// One electronics channel's fine-time occupancy calibration.
// The caller chooses which leading edges are accepted, and owns any ROOT
// histogram persistence or run-level calibration lifecycle.
// Tamex4Format provides the observed bin count, invalid code and clock.
template <typename Format = Tamex4Format>
class FineTimeCalibration
{
public:
    static constexpr std::size_t bins = Format::fine_bins;
    static constexpr double clock_ns = Format::fine_clock_ns;

    void ObserveLeadingEdge(std::uint32_t fine)
    {
        // Legacy readers reject 0x3ff (invalid code) and out-of-range bins
        // before filling their histogram.
        if (fine >= bins || fine == Format::invalid_fine_code) return;
        ++counts_[fine];
        ++entries_;
    }

    void SetCounts(const std::array<std::uint64_t, bins>& counts)
    {
        counts_ = counts;
        entries_ = 0;
        for (const auto count : counts_) entries_ += count;
    }

    void Calculate()
    {
        std::uint64_t cumulative = 0;
        for (std::size_t bin = 0; bin < bins; ++bin)
        {
            // Matches legacy ROOT GetBinContent(k+1) and the midpoint rule.
            times_[bin] = entries_ == 0
                ? static_cast<double>(bin) * clock_ns / static_cast<double>(bins)
                : clock_ns * (static_cast<double>(cumulative) +
                              static_cast<double>(counts_[bin]) / 2.0) /
                      static_cast<double>(entries_);
            cumulative += counts_[bin];
        }
    }

    double Time(std::size_t fine) const { return times_.at(fine); }
    std::uint64_t Entries() const { return entries_; }
    std::uint64_t Count(std::size_t fine) const { return counts_.at(fine); }

private:
    std::array<std::uint64_t, bins> counts_{};
    std::array<double, bins> times_{};
    std::uint64_t entries_ = 0;
};
} // namespace tamex

#endif
