#ifndef FATIMA_RAW_DATA_H
#define FATIMA_RAW_DATA_H

#include "TamexRawData.h"
#include "VmeDigitiserRawData.h"

#include <cstdint>
#include <vector>

struct FatimaTamexRaw
{
    std::uint16_t wrId = 0;
    std::uint64_t wrTimestamp = 0;
    std::vector<TamexRawData> boards;

    ClassDefNV(FatimaTamexRaw, 1);
};

struct FatimaVmeChainRaw
{
    std::uint16_t wrId = 0;
    std::uint64_t wrTimestamp = 0;
    std::vector<V1751RawData> QDC;
    std::vector<V1290RawData> TDC;

    ClassDefNV(FatimaVmeChainRaw, 1);
};

class FatimaRawData : public TObject
{
public:
    FatimaTamexRaw TAMEX;
    FatimaVmeChainRaw VMEChain;

    ClassDef(FatimaRawData, 1);
};

#endif
