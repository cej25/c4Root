#include "../c4source/digitisers/tamex/TamexRawBridge.h"

#include <cassert>
#include <cstdint>
#include <vector>

// Mirrors the public, ROOT-persistable TamexRawWord fields without depending
// on ROOT in the standalone regression workflow.
struct PersistedWordFixture
{
    enum : std::uint8_t { Epoch = 0, Edge = 1 };
    enum : std::uint8_t
    {
        HasPrecedingEpoch = 1u << 0,
        MissingEpochOnChannelChange = 1u << 1,
        DescendingChannel = 1u << 2,
        InvalidFine = 1u << 3
    };
    std::uint8_t kind = Epoch;
    std::uint32_t packed_index = 0;
    std::uint32_t epoch = 0;
    std::uint16_t channel = 0;
    std::uint16_t coarse = 0;
    std::uint32_t fine = 0;
    bool leading = false;
    std::uint8_t flags = 0;
};

struct RawBoardFixture
{
    std::vector<PersistedWordFixture> words;
    void AddWord(const PersistedWordFixture& word) { words.push_back(word); }
};

int main()
{
    const std::uint32_t epochs[] = {0x10000001u, 0, 0, 0, 0};
    const std::uint32_t coarse[] = {0, 200, 201, 202, 203};
    const std::uint32_t fine[] = {0, 10, 1023, 11, 65536};
    const std::uint32_t channels[] = {0, 0, 4, 2, 3};
    const std::uint32_t edges[] = {0, 1, 1, 0, 1};
    const tamex::PackedBoardView input{
        32, epochs, coarse, fine, channels, edges, 5, 5, 5, 5, 5};

    RawBoardFixture output;
    const auto stats = tamex::AppendRawWords<tamex::Tamex4Format, PersistedWordFixture>(
        input, 3, output);
    assert(stats.epoch_words == 1);
    assert(stats.edge_words == 4);
    assert(stats.invalid_fine_words == 2);
    assert(stats.descending_channels == 1);
    assert(stats.missing_epoch_on_change == 3);
    assert(output.words.size() == 5);
    assert(output.words[0].kind == PersistedWordFixture::Epoch);
    assert(output.words[0].epoch == 1);
    assert(output.words[0].packed_index == 0);
    assert(output.words[1].kind == PersistedWordFixture::Edge);
    assert(output.words[1].channel == 0 && output.words[1].leading);
    assert(output.words[1].fine == 10);
    assert(output.words[1].flags == PersistedWordFixture::HasPrecedingEpoch);
    assert(output.words[2].channel == 4 && output.words[2].fine == 1023);
    assert((output.words[2].flags & PersistedWordFixture::InvalidFine) != 0);
    assert((output.words[2].flags & PersistedWordFixture::MissingEpochOnChannelChange) != 0);
    assert(output.words[3].channel == 2 && !output.words[3].leading);
    assert((output.words[3].flags & PersistedWordFixture::DescendingChannel) != 0);
    assert(output.words[4].fine == 65536);
    assert((output.words[4].flags & PersistedWordFixture::InvalidFine) != 0);

    const tamex::PackedBoardView empty{};
    RawBoardFixture trigger_only;
    const auto empty_stats =
        tamex::AppendRawWords<tamex::Tamex4Format, PersistedWordFixture>(
            empty, 0, trigger_only);
    assert(trigger_only.words.empty());
    assert(empty_stats.edge_words == 0 && empty_stats.epoch_words == 0);

    // Converting an explicit raw word should not silently truncate anomalies.
    tamex::RawWord anomaly{};
    anomaly.kind = tamex::WordKind::Edge;
    anomaly.packed_index = 19;
    anomaly.epoch = 0x0fffffff;
    anomaly.channel = 32;
    anomaly.coarse = 0x7ff;
    anomaly.fine = 0xffffffffu;
    anomaly.leading = true;
    anomaly.has_preceding_epoch = true;
    anomaly.changed_channel_without_epoch = true;
    anomaly.channel_order_decreased = true;
    anomaly.invalid_fine = true;
    const auto converted = tamex::MakeRawWord<PersistedWordFixture>(anomaly);
    assert(converted.packed_index == 19 && converted.epoch == 0x0fffffff);
    assert(converted.channel == 32 && converted.coarse == 0x7ff);
    assert(converted.fine == 0xffffffffu);
    assert(converted.flags == 0x0f);
    return 0;
}
