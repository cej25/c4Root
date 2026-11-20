#ifndef TAMEX_FINE_TIME_HISTOGRAMS_H
#define TAMEX_FINE_TIME_HISTOGRAMS_H

#include "TamexFineTimeCalibration.h"
#include "TFile.h"
#include "TH1.h"
#include "TString.h"

#include <cmath>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

namespace tamex
{
inline std::vector<std::array<double, Tamex4Format::fine_bins>>
ReadFineTimeHistograms(const TString& path, std::size_t max_boards)
{
    TFile file(path, "READ");
    if (file.IsZombie())
        throw std::runtime_error(std::string("Cannot open fine-time histogram file ") + path.Data());

    constexpr auto channels = Tamex4Format::channel_count;
    constexpr auto bins = Tamex4Format::fine_bins;
    std::vector<std::array<double, bins>> times;
    for (std::size_t board = 0; board < max_boards; ++board)
    {
        for (unsigned channel = 0; channel < channels; ++channel)
        {
            const auto key = TString::Format("fine_time_hits_%u_%u", static_cast<unsigned>(board), channel);
            TH1* histogram = nullptr;
            file.GetObject(key.Data(), histogram);
            if (channel == 0 && !histogram)
            {
                if (times.empty()) throw std::runtime_error("Fine-time file contains no calibrated TAMEX boards");
                return times;
            }
            if (!histogram || histogram->GetNbinsX() != static_cast<int>(bins))
                throw std::runtime_error(std::string("Missing or incompatible histogram ") + key.Data());

            std::array<std::uint64_t, bins> counts{};
            std::uint64_t total = 0;
            for (std::size_t bin = 0; bin < bins; ++bin)
            {
                const double count = histogram->GetBinContent(static_cast<int>(bin + 1));
                if (!std::isfinite(count) || count < 0 || count >= 0x1p64 || std::trunc(count) != count)
                    throw std::runtime_error(std::string("Invalid bin count in ") + key.Data());

                counts[bin] = static_cast<std::uint64_t>(count);
                if (counts[bin] > std::numeric_limits<std::uint64_t>::max() - total)
                    throw std::runtime_error(std::string("Invalid total bin count in ") + key.Data());
                total += counts[bin];
            }
            FineTimeCalibration<> calibration;
            calibration.SetCounts(counts);
            calibration.Calculate();
            auto& channel_times = times.emplace_back();
            for (std::size_t bin = 0; bin < bins; ++bin) channel_times[bin] = calibration.Time(bin);
        }
    }
    return times;
}
}

#endif
