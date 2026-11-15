#ifndef C4_TAMEX_FAMILY_DECODER_H
#define C4_TAMEX_FAMILY_DECODER_H

#include "../../base/TamexPackedSafety.h"

#include <cstdint>
#include <utility>

namespace c4_tamex
{
// Borrowed view of one board's UCESB-unpacked packed-word columns.
// Each count is independent; the owning unpacker retains the memory.
struct PackedBoardView
{
    std::uint32_t event_size_bytes = 0;
    const std::uint32_t* epoch = nullptr;
    const std::uint32_t* coarse = nullptr;
    const std::uint32_t* fine = nullptr;
    const std::uint32_t* channel = nullptr;
    const std::uint32_t* edge = nullptr;
    std::uint32_t epoch_count = 0;
    std::uint32_t coarse_count = 0;
    std::uint32_t fine_count = 0;
    std::uint32_t channel_count = 0;
    std::uint32_t edge_count = 0;
};

enum class WordKind : std::uint8_t { Epoch, Edge };

// Raw electronics facts, deliberately not a detector hit or a lead/trail pair.
struct RawWord
{
    WordKind kind = WordKind::Epoch;
    std::uint16_t board = 0;
    std::uint32_t packed_index = 0;
    std::uint32_t epoch = 0;
    std::uint16_t channel = 0;
    std::uint16_t coarse = 0;
    std::uint16_t fine = 0;
    bool leading = false;
    bool has_preceding_epoch = false;
    bool changed_channel_without_epoch = false;
    bool channel_order_decreased = false;
    bool invalid_fine = false;
};

struct DecodeStats
{
    std::uint32_t epoch_words = 0;
    std::uint32_t edge_words = 0;
    std::uint32_t incomplete_words = 0;
    std::uint32_t invalid_channels = 0;
    std::uint32_t invalid_fine_words = 0;
    std::uint32_t missing_epoch_on_change = 0;
    std::uint32_t descending_channels = 0;
};

// A format describes electronics layout, not detector identity.
// New TAMEX versions can provide different traits without cloning the loop.
struct Tamex4Format
{
    static constexpr std::uint32_t channel_count = 33; // 0 = trigger
    static constexpr std::uint32_t fine_bins = 1024;
    static constexpr std::uint32_t invalid_fine_code = 0x3ff;
    static constexpr std::uint32_t epoch_mask = 0x0fffffff;
    static constexpr std::uint32_t channel_mask = 0x7f;
    static constexpr std::uint32_t coarse_mask = 0x7ff;
    static constexpr std::uint32_t leading_mask = 1;
};

template <typename Format>
class Decoder
{
public:
    template <typename Emit>
    static DecodeStats Decode(const PackedBoardView& input, std::uint16_t board, Emit&& emit)
    {
        DecodeStats stats{};
        const auto budget = c4_tamex_packed_safety::EventHitBudget(input.event_size_bytes);
        std::uint32_t previous_epoch = 0;
        std::uint32_t previous_channel = 0;
        bool has_epoch = false;
        bool last_word_was_epoch = false;

        for (std::uint32_t i = 0; i < budget; ++i)
        {
            if (!c4_tamex_packed_safety::HasCompleteHit(
                    i, input.epoch_count, input.coarse_count, input.fine_count,
                    input.channel_count, input.edge_count) ||
                !input.epoch || !input.coarse || !input.fine ||
                !input.channel || !input.edge)
            {
                ++stats.incomplete_words;
                continue;
            }

            if (input.epoch[i] != 0)
            {
                previous_epoch = input.epoch[i] & Format::epoch_mask;
                has_epoch = true;
                last_word_was_epoch = true;
                RawWord word{};
                word.kind = WordKind::Epoch;
                word.board = board;
                word.packed_index = i;
                word.epoch = previous_epoch;
                word.has_preceding_epoch = true;
                emit(word);
                ++stats.epoch_words;
                continue;
            }

            const auto channel = input.channel[i] & Format::channel_mask;
            if (channel >= Format::channel_count)
            {
                ++stats.invalid_channels;
                continue;
            }

            RawWord word{};
            word.kind = WordKind::Edge;
            word.board = board;
            word.packed_index = i;
            word.epoch = previous_epoch;
            word.channel = static_cast<std::uint16_t>(channel);
            word.coarse = static_cast<std::uint16_t>(input.coarse[i] & Format::coarse_mask);
            word.fine = static_cast<std::uint16_t>(input.fine[i]);
            word.leading = (input.edge[i] & Format::leading_mask) != 0;
            word.has_preceding_epoch = has_epoch;
            word.changed_channel_without_epoch =
                channel != 0 && channel != previous_channel && !last_word_was_epoch;
            word.channel_order_decreased = channel < previous_channel;
            word.invalid_fine = input.fine[i] >= Format::fine_bins ||
                                input.fine[i] == Format::invalid_fine_code;

            // Preserve anomalous electronics words and their flags in Raw.
            // A downstream detector task chooses any rejection/matching policy.
            if (word.changed_channel_without_epoch) ++stats.missing_epoch_on_change;
            if (word.channel_order_decreased) ++stats.descending_channels;
            if (word.invalid_fine) ++stats.invalid_fine_words;
            emit(word);
            ++stats.edge_words;
            previous_channel = channel;
            last_word_was_epoch = false;
        }
        return stats;
    }
};

using Tamex4Decoder = Decoder<Tamex4Format>;
} // namespace c4_tamex

#endif
