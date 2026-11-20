#ifndef TAMEX_RAW_DECODE_H
#define TAMEX_RAW_DECODE_H

#include "TamexDecoder.h"
#include "TamexRawData.h"

namespace tamex
{
template <typename Board, std::size_t N, typename NextBoard>
void ReadBoards(const Board (&banks)[N], std::uint16_t procid,
                const std::string& detectorName, std::uint16_t wr_subsystem, std::uint64_t wr_timestamp,
                NextBoard&& nextBoard)
{
    static_assert(N <= 65535, "TAMEX board identifier exceeds Raw data capacity");
    for (std::size_t i = 0; i < N; ++i)
    {
        const auto& bank = banks[i];
        // Preserve trigger-only records, including legacy bPlast trigger 3.
        if (bank.event_size == 0 && bank.trig == 0) continue;

        auto& raw = nextBoard();
        raw.Reset();
        raw.SetMetadata(procid, static_cast<std::uint16_t>(i),
                         static_cast<std::uint16_t>(bank.trig),
                         wr_subsystem, wr_timestamp, 4, detectorName);

        const auto view = tamex::MakeBoardView(bank);
        raw.ReserveWords(c4_tamex_packed_safety::EventHitBudget(bank.event_size));
        tamex::Tamex4Decoder::Decode(
            view, static_cast<std::uint16_t>(i),
            [&raw](const tamex::RawWord& word) {
                TamexRawWord persisted{};
                persisted.kind = word.kind == tamex::WordKind::Epoch
                                     ? TamexRawWord::Epoch : TamexRawWord::Edge;
                persisted.packed_index = word.packed_index;
                persisted.epoch = word.epoch;
                persisted.channel = word.channel;
                persisted.coarse = word.coarse;
                persisted.fine = word.fine;
                persisted.leading = word.leading;
                if (word.has_preceding_epoch)
                    persisted.flags |= TamexRawWord::HasPrecedingEpoch;
                if (word.changed_channel_without_epoch)
                    persisted.flags |= TamexRawWord::MissingEpochOnChannelChange;
                if (word.channel_order_decreased)
                    persisted.flags |= TamexRawWord::DescendingChannel;
                if (word.invalid_fine)
                    persisted.flags |= TamexRawWord::InvalidFine;
                raw.AddWord(persisted);
            });
    }
}
}

#endif
