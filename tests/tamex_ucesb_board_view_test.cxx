#include "../c4source/digitisers/tamex/TamexDecoder.h"

#include <cassert>
#include <cstdint>

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

int main()
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
    return 0;
}
