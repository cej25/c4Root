#ifndef TAMEX_RAW_BRIDGE_H
#define TAMEX_RAW_BRIDGE_H

#include "TamexDecoder.h"

#include <cstdint>
#include <utility>

namespace tamex
{
// Convert the decoder's electronics-only word to the persistence representation.
// Kept generic so this logic can be tested without loading ROOT or FairRoot.
// OutputWord must expose the fields of TamexRawWord (c4data/tamexData).
template <typename OutputWord>
OutputWord MakeRawWord(const RawWord& input)
{
    OutputWord output{};
    output.kind = input.kind == WordKind::Epoch ? OutputWord::Epoch : OutputWord::Edge;
    output.packed_index = input.packed_index;
    output.epoch = input.epoch;
    output.channel = input.channel;
    output.coarse = input.coarse;
    output.fine = input.fine;
    output.leading = input.leading;

    if (input.has_preceding_epoch)
        output.flags |= OutputWord::HasPrecedingEpoch;
    if (input.changed_channel_without_epoch)
        output.flags |= OutputWord::MissingEpochOnChannelChange;
    if (input.channel_order_decreased)
        output.flags |= OutputWord::DescendingChannel;
    if (input.invalid_fine)
        output.flags |= OutputWord::InvalidFine;
    return output;
}

// Append all electronic words to a board-level Raw object. Does not clear the
// target or decide whether an empty board should be persisted: callers can
// preserve trigger-only events by constructing the board record beforehand.
template <typename Format, typename OutputWord, typename OutputBoard>
DecodeStats AppendRawWords(const PackedBoardView& input, std::uint16_t board,
                           OutputBoard& output)
{
    return Decoder<Format>::Decode(input, board, [&](const RawWord& word) {
        output.AddWord(MakeRawWord<OutputWord>(word));
    });
}

} // namespace tamex

#endif
