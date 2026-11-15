#include "../c4source/digitisers/tamex/TamexDecoder.h"

#include <cassert>
#include <cstdint>
#include <vector>

using c4_tamex::PackedBoardView;
using c4_tamex::RawWord;
using c4_tamex::Tamex4Decoder;
using c4_tamex::WordKind;

static std::vector<RawWord> Decode(const PackedBoardView& input, c4_tamex::DecodeStats& stats)
{
    std::vector<RawWord> output;
    stats = Tamex4Decoder::Decode(input, 7, [&](const RawWord& word) {
        output.push_back(word);
    });
    return output;
}

int main()
{
    // Two epoch markers; one trigger channel and two detector edges.
    const std::uint32_t epochs[] = {0x10000003u, 0, 0, 0x10000004u, 0};
    const std::uint32_t coarse[] = {0, 0x1234u, 42, 0, 43};
    const std::uint32_t fine[] = {0, 12, 1023, 0, 32};
    const std::uint32_t channels[] = {0, 0, 2, 0, 2};
    const std::uint32_t edges[] = {0, 1, 1, 0, 0};
    const PackedBoardView input{32, epochs, coarse, fine, channels, edges, 5, 5, 5, 5, 5};
    // 32 bytes => 8 words minus 3 headers = 5 unpacked positions.
    c4_tamex::DecodeStats stats{};
    auto words = Decode(input, stats);
    assert(words.size() == 5);
    assert(stats.epoch_words == 2 && stats.edge_words == 3);
    assert(stats.invalid_fine_words == 1);
    assert(stats.missing_epoch_on_change == 1);
    assert(stats.incomplete_words == 0);
    assert(words[0].kind == WordKind::Epoch && words[0].epoch == 3);
    assert(words[0].board == 7 && words[0].packed_index == 0);
    assert(words[1].kind == WordKind::Edge && words[1].channel == 0);
    assert(words[1].coarse == (0x1234u & 0x7ffu));
    assert(words[1].leading && words[1].has_preceding_epoch);
    assert(words[2].channel == 2 && words[2].invalid_fine);
    assert(words[2].fine == 1023);
    assert(words[2].changed_channel_without_epoch);
    assert(words[3].kind == WordKind::Epoch && words[3].epoch == 4);
    assert(words[4].kind == WordKind::Edge && !words[4].leading);
    assert(words[4].epoch == 4 && !words[4].invalid_fine);
    assert(!words[4].changed_channel_without_epoch);

    // A channel ordering violation must be reported, not fatal in raw decode.
    const std::uint32_t zero_epochs[] = {0, 0};
    const std::uint32_t low_coarse[] = {2, 3};
    const std::uint32_t low_fine[] = {1, 2};
    const std::uint32_t falling_channels[] = {5, 3};
    const std::uint32_t lead_edges[] = {1, 1};
    const PackedBoardView descending{20, zero_epochs, low_coarse, low_fine,
                                     falling_channels, lead_edges, 2, 2, 2, 2, 2};
    words = Decode(descending, stats);
    assert(words.size() == 2 && stats.descending_channels == 1);
    assert(!words[0].has_preceding_epoch && words[0].changed_channel_without_epoch);
    assert(words[1].channel_order_decreased && stats.missing_epoch_on_change == 2);

    // Truncated independently populated channel array: never read beyond it.
    const PackedBoardView incomplete{20, zero_epochs, low_coarse, low_fine,
                                     falling_channels, lead_edges, 2, 2, 2, 1, 2};
    words = Decode(incomplete, stats);
    assert(words.size() == 1 && stats.incomplete_words == 1);

    // Non-empty event with a null buffer is safely reported as incomplete.
    const PackedBoardView missing{16, nullptr, low_coarse, low_fine,
                                  falling_channels, lead_edges, 1, 1, 1, 1, 1};
    words = Decode(missing, stats);
    assert(words.empty() && stats.incomplete_words == 1);

    // Unphysical channel indices are rejected, while invalid fine codes
    // remain available in raw records with an explicit anomaly flag.
    const std::uint32_t invalid_channels[] = {33, 127};
    const PackedBoardView invalid{20, zero_epochs, low_coarse, low_fine,
                                  invalid_channels, lead_edges, 2, 2, 2, 2, 2};
    words = Decode(invalid, stats);
    assert(words.empty() && stats.invalid_channels == 2);

    const std::uint32_t huge_fine[] = {65536};
    const PackedBoardView large_fine{16, zero_epochs, low_coarse, huge_fine,
                                     falling_channels, lead_edges, 1, 1, 1, 1, 1};
    words = Decode(large_fine, stats);
    assert(words.size() == 1 && words[0].fine == 65536 &&
           words[0].invalid_fine && stats.invalid_fine_words == 1);

    // Empty/short events must not underflow the word count.
    const PackedBoardView empty{8, zero_epochs, low_coarse, low_fine,
                                 falling_channels, lead_edges, 2, 2, 2, 2, 2};
    words = Decode(empty, stats);
    assert(words.empty() && stats.epoch_words == 0 && stats.edge_words == 0);
    return 0;
}
