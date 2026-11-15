#include "TamexRawAdapter.h"

#include "TamexRawBridge.h"
#include "TamexRawData.h"

namespace tamex
{
DecodeStats DecodeIntoRawData(const PackedBoardView& input,
                              std::uint16_t board,
                              TamexRawData& output)
{
    return AppendRawWords<Tamex4Format, TamexRawWord>(input, board, output);
}
} // namespace tamex
