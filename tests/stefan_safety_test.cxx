#include "../c4source/stefan/StefanIndexSafety.h"
#include "../c4source/digitisers/febex/FebexReader.h"
#include "../c4source/stefan/ext_h101_stefan.h"

#include <cassert>
#include <cstdint>
#include <limits>
#include <string>
#include <vector>

static void TestDetectorIndices()
{
    using stefan_index_safety::ValidDssd;

    assert(ValidDssd(0, 1));
    assert(ValidDssd(0, 3));
    assert(ValidDssd(2, 3));

    assert(!ValidDssd(-1, 3));
    assert(!ValidDssd(-2, 3));
    assert(!ValidDssd(3, 3));
    assert(!ValidDssd(4, 3));
    assert(!ValidDssd(0, 0));
}

struct SummaryHit
{
    std::uint64_t channelTicks = 0;
    std::uint32_t energyWord = 0;
    std::uint32_t channel = 0;
    std::uint32_t cfd = 0;
    bool pileup = false;
    bool overflow = false;
    std::int32_t signedEnergy = 0;
    double legacyChannelTimeNs = 0;
};

struct SummaryBoard
{
    std::string detectorName;
    std::uint64_t eventTicks = 0;
    std::uint64_t wrTimestamp = 0;
    std::uint16_t wrId = 0;
    std::uint16_t procid = 0;
    std::uint32_t slot = 0;
    std::uint32_t card = 0;
    std::uint32_t trigger = 0;
    std::uint32_t hitPattern = 0;
    std::vector<SummaryHit> hits;
};

static void TestTimestampedSummary()
{
    EXT_STR_h101_stefan_onion_t input{};
    const auto read = [&input] {
        std::vector<SummaryBoard> boards;
        assert(!febex::ReadBoards<febex::SummaryLayout::WithTriggerTimestamp>(
            input.stefan_data, input.stefan_ts_t, input.stefan_ts_subsystem_id, 70, "Stefan", boards));
        return boards;
    };

    assert(read().empty());
    input.stefan_ts_subsystem_id = 0x700;
    auto& board = input.stefan_data[3];
    board.event_trigger_time_hi = 1;
    board.event_trigger_time_lo = 100;
    board.trig = 3;
    board.hit_pattern = 1u << 15;
    board.channel_energy = board.channel_cfd = board.pileup = board.overflow = 3;
    board.channel_trigger_time_lo = 2; // The third hit has no complete timestamp.
    board.channel_energyI[0] = 16;
    board.channel_energyI[1] = 0; // Invalid sparse index.
    board.channel_energyI[2] = 1;
    board.channel_energyv[0] = 0x800123;
    board.channel_trigger_time_lov[0] = 0x1000001;
    board.channel_cfdv[0] = 33;
    board.pileupv[0] = 1;
    board.overflowv[0] = 1;

    for (auto& word : input.stefan_ts_t) word = 0xffff;
    const auto decoded = read();
    assert(decoded.size() == 1);
    const auto& output = decoded.front();
    assert(output.slot == 3 && output.card == 3);
    assert(output.eventTicks == (UINT64_C(1) << 32) + 100);
    assert(output.wrId == 0x700 && output.wrTimestamp == std::numeric_limits<std::uint64_t>::max());
    assert(output.trigger == 3 && output.hitPattern == (1u << 15));
    assert(output.hits.size() == 1);
    const auto& hit = output.hits.front();
    assert(hit.channel == 15 && hit.signedEnergy == -0x123);
    assert(hit.legacyChannelTimeNs == 15.15625);
    assert(hit.pileup && hit.overflow);

    board.channel_energy = board.channel_trigger_time_lo = board.channel_cfd = board.pileup = board.overflow = 17;
    for (std::uint32_t i = 0; i < 16; ++i) board.channel_energyI[i] = i + 1;
    assert(read().front().hits.size() == 16);
}

int main()
{
    TestDetectorIndices();
    TestTimestampedSummary();
}
