#ifndef TAMEX_RAW_ADAPTER_H
#define TAMEX_RAW_ADAPTER_H

#include "TamexDecoder.h"

#include <cstdint>

class TamexRawData;

namespace tamex
{
// Append one TAMEX4 board's decoded electronics words to its TamexRawData.
// The caller owns board metadata, including trigger and White Rabbit time.
DecodeStats DecodeIntoRawData(const PackedBoardView& input,
                              std::uint16_t board,
                              TamexRawData& output);
} // namespace tamex

#endif
