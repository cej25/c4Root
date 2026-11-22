#include "../c4source/digitisers/tamex/TamexReader.h"

#include <cassert>
#include <cstdint>
#include <vector>

using tamex::PackedBoardView;
using tamex::RawWord;
using tamex::Tamex4Decoder;
using tamex::WordKind;

static std::vector<RawWord> Decode(const PackedBoardView& input, tamex::DecodeStats& stats)
{
    std::vector<RawWord> output;
    stats = Tamex4Decoder::Decode(input, 7, [&](const RawWord& word) {
        output.push_back(word);
    });
    return output;
}

// Matches the field names and types of the generated UCESB onion board,
// without requiring UCESB or ROOT in the standalone test.
struct UcesbBoardFixture
{
    std::uint32_t trig = 0;
    std::uint32_t event_size = 0;
    std::uint32_t time_coarse = 0;
    std::uint32_t time_coarsev[8] = {};
    std::uint32_t time_fine = 0;
    std::uint32_t time_finev[8] = {};
    std::uint32_t time_edge = 0;
    std::uint32_t time_edgev[8] = {};
    std::uint32_t time_channel = 0;
    std::uint32_t time_channelv[8] = {};
    std::uint32_t time_epoch = 0;
    std::uint32_t time_epochv[8] = {};
};

static void TestUcesbBoardView()
{
    UcesbBoardFixture board{};
    board.event_size = 20; // 2 packed records after header
    board.trig = 3;
    board.time_epoch = 2;
    board.time_coarse = 2;
    board.time_fine = 2;
    board.time_edge = 2;
    board.time_channel = 2;
    board.time_epochv[0] = 0x10000007;
    board.time_channelv[1] = 4;
    board.time_coarsev[1] = 0x802;
    board.time_finev[1] = 1023;
    board.time_edgev[1] = 1;

    const auto input = tamex::MakeBoardView(board);
    assert(input.event_size_bytes == 20);
    assert(input.epoch == board.time_epochv);
    assert(input.coarse == board.time_coarsev);
    assert(input.fine == board.time_finev);
    assert(input.channel == board.time_channelv);
    assert(input.edge == board.time_edgev);
    assert(input.epoch_count == 2 && input.coarse_count == 2);
    assert(input.fine_count == 2 && input.channel_count == 2 && input.edge_count == 2);

    unsigned count = 0;
    const auto stats = tamex::Tamex4Decoder::Decode(input, 1, [&](const tamex::RawWord& word) {
        if (count == 0)
            assert(word.kind == tamex::WordKind::Epoch && word.epoch == 7);
        else
        {
            assert(word.kind == tamex::WordKind::Edge);
            assert(word.board == 1 && word.channel == 4);
            assert(word.coarse == 2 && word.fine == 1023);
            assert(word.leading && word.invalid_fine);
        }
        ++count;
    });
    assert(count == 2 && stats.epoch_words == 1 && stats.edge_words == 1);
    assert(stats.invalid_fine_words == 1);

    // The pointer view reflects live unpacked values, without copying.
    board.time_finev[1] = 12;
    assert(input.fine[1] == 12);

    const std::uint32_t wr_words[4] = {0x5678, 0x1234, 0xdef0, 0x9abc};
    assert(tamex::AssembleWhiteRabbitTimestamp(wr_words) ==
           UINT64_C(0x9abcdef012345678));
    const std::uint32_t wr_max[4] = {0xffff, 0xffff, 0xffff, 0xffff};
    assert(tamex::AssembleWhiteRabbitTimestamp(wr_max) == UINT64_MAX);
    const std::uint32_t wr_high_bit[4] = {0, 0, 0, 0x8000};
    assert(tamex::AssembleWhiteRabbitTimestamp(wr_high_bit) ==
           (UINT64_C(1) << 63));

    // Empty trigger-only board: no decoded words, but its trigger can be kept
    // by the reader when it constructs the board-level Raw data record.
    UcesbBoardFixture trigger_only{};
    trigger_only.trig = 3;
    count = 0;
    const auto empty_stats = tamex::Tamex4Decoder::Decode(
        tamex::MakeBoardView(trigger_only), 0,
        [&](const tamex::RawWord&) { ++count; });
    assert(trigger_only.trig == 3 && count == 0);
    assert(empty_stats.edge_words == 0 && empty_stats.epoch_words == 0);
}

int main()
{
    TestUcesbBoardView();

    // Two epoch markers; one trigger channel and two detector edges.
    const std::uint32_t epochs[] = {0x10000003u, 0, 0, 0x10000004u, 0};
    const std::uint32_t coarse[] = {0, 0x1234u, 42, 0, 43};
    const std::uint32_t fine[] = {0, 12, 1023, 0, 32};
    const std::uint32_t channels[] = {0, 0, 2, 0, 2};
    const std::uint32_t edges[] = {0, 1, 1, 0, 0};
    const PackedBoardView input{32, epochs, coarse, fine, channels, edges, 5, 5, 5, 5, 5};
    // 32 bytes => 8 words minus 3 headers = 5 unpacked positions.
    tamex::DecodeStats stats{};
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

    // Complete arrays can contain more words than the payload budget.
    auto limited = descending;
    limited.event_size_bytes = 16;
    words = Decode(limited, stats);
    assert(words.size() == 1 && stats.incomplete_words == 0);

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
