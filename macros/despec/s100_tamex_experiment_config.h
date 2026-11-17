#ifndef C4ROOT_S100_TAMEX_EXPERIMENT_CONFIG_H
#define C4ROOT_S100_TAMEX_EXPERIMENT_CONFIG_H

#include <TString.h>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <string>

namespace s100_config
{
// Minimal parser for the deliberately flat detector-keyed experiment.yaml.
// This is configuration metadata, not an independent read of MBS procid or WR ID.
inline bool LoadTamexConfig(const TString& path, const std::string& wanted,
                     std::uint16_t& procid, std::uint16_t& whiterabbit)
{
    std::ifstream file(path.Data());
    if (!file)
    {
        std::cerr << "Cannot open experiment configuration: " << path << '\n';
        return false;
    }

    const std::regex detector_pattern(R"(^([A-Za-z][A-Za-z0-9_-]*):\s*(?:#.*)?$)");
    const std::regex field_pattern(R"(^[ \t]+(digitiser|version|procid|whiterabbit):\s*([^ \t#]+)\s*(?:#.*)?$)");
    std::string line, current_detector, digitiser;
    bool seen_detector = false;
    bool have_digitiser = false, have_version = false;
    bool have_procid = false, have_wr = false;
    unsigned long version = 0;

    auto parse_number = [](const std::string& value, unsigned long& output) {
        try
        {
            std::size_t end = 0;
            output = std::stoul(value, &end, 0);
            return end == value.size();
        }
        catch (const std::exception&) { return false; }
    };

    while (std::getline(file, line))
    {
        std::smatch match;
        if (std::regex_match(line, match, detector_pattern))
        {
            const auto detector = match[1].str();
            if (detector == wanted)
            {
                if (seen_detector)
                {
                    std::cerr << "Duplicate detector entry: " << wanted << '\n';
                    return false;
                }
                seen_detector = true;
            }
            current_detector = detector;
            continue;
        }
        if (current_detector != wanted) continue;
        if (!std::regex_match(line, match, field_pattern)) continue;

        const auto key = match[1].str();
        const auto value = match[2].str();
        unsigned long number = 0;
        if (key == "digitiser")
        {
            if (have_digitiser) return false;
            digitiser = value;
            have_digitiser = true;
        }
        else if (key == "version")
        {
            if (have_version || !parse_number(value, version)) return false;
            have_version = true;
        }
        else if (key == "procid")
        {
            if (have_procid || !parse_number(value, number) ||
                number > std::numeric_limits<std::uint16_t>::max()) return false;
            procid = static_cast<std::uint16_t>(number);
            have_procid = true;
        }
        else if (key == "whiterabbit")
        {
            if (have_wr || !parse_number(value, number) ||
                number > std::numeric_limits<std::uint16_t>::max()) return false;
            whiterabbit = static_cast<std::uint16_t>(number);
            have_wr = true;
        }
    }

    if (!seen_detector || !have_digitiser || !have_version ||
        !have_procid || !have_wr || digitiser != "tamex" || version != 4)
    {
        std::cerr << "Missing or unsupported TAMEX4 configuration for "
                  << wanted << " in " << path << '\n';
        return false;
    }
    return true;
}
} // namespace s100_config

#endif
