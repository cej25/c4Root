#ifndef FEBEX_RAW_DATA_H
#define FEBEX_RAW_DATA_H

#include "TObject.h"

#include <cstdint>
#include <string>
#include <vector>

struct FebexRawHit
{
    std::uint64_t channelTicks = 0;
    std::uint32_t energyWord = 0;
    std::uint8_t channel = 0;
    std::uint8_t cfd = 0;
    bool pileup = false;
    bool overflow = false;

    ClassDefNV(FebexRawHit, 1);
};

// One present board in the FEBEX summary stream.
class FebexRawData : public TObject
{
public:
    std::string detectorName;
    std::uint64_t eventTicks = 0;
    std::uint64_t wrTimestamp = 0;
    std::uint16_t wrId = 0;
    std::uint16_t procid = 0;
    std::uint16_t hitPattern = 0;
    std::uint8_t slot = 0;
    std::uint8_t sfp = 0;
    std::uint8_t card = 0;
    std::uint8_t trigger = 0;
    std::vector<FebexRawHit> hits;

    ClassDef(FebexRawData, 1);
};

#endif
