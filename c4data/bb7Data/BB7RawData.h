#ifndef BB7_RAW_DATA_H
#define BB7_RAW_DATA_H

#include "FebexRawData.h"
#include "VmeDigitiserRawData.h"

struct BB7FebexRawBoard
{
    FebexRawData summary;
    std::uint32_t reportedHits = 0;
    // One trace per summary hit, in the same order.
    std::vector<std::vector<std::uint16_t>> traces;

    ClassDefNV(BB7FebexRawBoard, 1);
};

struct BB7FebexRawCrate
{
    std::uint64_t wrTimestamp = 0;
    std::uint16_t wrId = 0;
    std::uint16_t procid = 0;
    std::vector<BB7FebexRawBoard> boards;

    ClassDefNV(BB7FebexRawCrate, 1);
};

class BB7FebexRawData : public TObject
{
public:
    BB7FebexRawCrate first;
    BB7FebexRawCrate second;

    ClassDef(BB7FebexRawData, 1);
};

struct BB7V7x5RawHit
{
    std::uint32_t module = 0;
    std::uint32_t geo = 0;
    std::uint32_t channel = 0;
    std::uint32_t value = 0;

    ClassDefNV(BB7V7x5RawHit, 1);
};

class BB7VmeRawData : public TObject
{
public:
    std::uint64_t wrTimestamp = 0;
    std::uint16_t wrId = 0;
    std::uint16_t procid = 0;
    std::vector<BB7V7x5RawHit> V7x5;
    std::vector<V1290RawData> V1290;

    ClassDef(BB7VmeRawData, 1);
};

#endif
