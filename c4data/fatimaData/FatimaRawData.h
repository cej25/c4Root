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

    // ROOT sets this to one when reading version-1 FATIMA data.
    std::uint16_t tdcChannelBase = 0;

    int TdcHardwareChannel(const V1290RawData& hit) const
    {
        return static_cast<int>(hit.channel) - tdcChannelBase;
    }

    ClassDefNV(FatimaVmeChainRaw, 2);
};

class FatimaRawData : public TObject
{
public:
    FatimaTamexRaw TAMEX;
    FatimaVmeChainRaw VMEChain;

    ClassDef(FatimaRawData, 1);
};

#endif
