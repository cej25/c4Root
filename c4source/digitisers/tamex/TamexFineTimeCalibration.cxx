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
std::vector<std::array<double, Tamex4Format::fine_bins>>
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
            times.push_back(calibration.Times());
        }
    }
    return times;
}
void WriteFineTimeHistograms(const TString& path,
                             const std::vector<std::array<std::uint64_t, Tamex4Format::fine_bins>>& boardCounts)
{
    TFile output(path, "RECREATE");
    if (output.IsZombie())
        throw std::runtime_error(std::string("Cannot write fine-time histograms: ") + path.Data());
    constexpr auto channels_per_board = Tamex4Format::channel_count;
    constexpr auto bins = Tamex4Format::fine_bins;
    for (std::size_t board = 0; board < boardCounts.size() / channels_per_board; ++board)
    {
        for (std::size_t channel = 0; channel < channels_per_board; ++channel)
        {
            const TString name = TString::Format("fine_time_hits_%u_%u",
                static_cast<unsigned>(board), static_cast<unsigned>(channel));
            TH1I histogram(name, name, bins, 0, bins);
            const auto& counts = boardCounts[board * channels_per_board + channel];
            double total = 0.0;
            for (std::size_t bin = 0; bin < counts.size(); ++bin)
            {
                // Use TH1I for compatibility with existing fine-time files.
                if (counts[bin] > static_cast<std::uint64_t>(std::numeric_limits<int>::max()))
                    throw std::runtime_error(std::string("Fine-time histogram bin exceeds TH1I capacity: ") + name.Data());
                const double count = static_cast<double>(counts[bin]);
                histogram.SetBinContent(static_cast<int>(bin + 1), count);
                total += count;
            }
            histogram.SetEntries(total);
            histogram.Write();
        }
    }
    output.Close();
}
}
