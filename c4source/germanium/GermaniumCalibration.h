#ifndef GERMANIUM_CALIBRATION_H
#define GERMANIUM_CALIBRATION_H

#include <optional>
#include <utility>

namespace germanium
{
struct CalibratedHit
{
    int detector;
    int crystal;
    double energy;
};

template <typename Mapping, typename Coefficients>
std::optional<CalibratedHit> CalibrateHit(const Mapping& mapping, const Coefficients& coefficients,
                                         int board, int channel, double energy, bool calibrateEnergy)
{
    const auto mapped = mapping.find({board, channel});
    if (mapped == mapping.end()) return std::nullopt;
    const auto [detector, crystal] = mapped->second;
    if (detector == -1 || crystal == -1) return std::nullopt;

    if (calibrateEnergy)
    {
        const auto calibration = coefficients.find(mapped->second);
        if (calibration != coefficients.end())
        {
            const auto& a = calibration->second;
            energy = a.at(0) + a.at(1) * energy + a.at(2) * energy * energy;
        }
    }
    return CalibratedHit{detector, crystal, energy};
}
}

#endif
