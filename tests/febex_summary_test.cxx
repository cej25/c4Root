#include "../c4source/digitisers/febex/FebexSummary.h"

#include <cassert>
#include <vector>

// Match the fields populated by the shared decoder without linking ROOT.
struct Hit
{
    std::uint64_t channelTicks = 0;
    std::uint32_t energyWord = 0;
    std::uint8_t channel = 0, cfd = 0;
    bool pileup = false, overflow = false;
};

struct Board
{
    std::string detectorName;
    std::uint64_t eventTicks = 0, wrTimestamp = 0;
    std::uint16_t wrId = 0, procid = 0, hitPattern = 0;
    std::uint8_t slot = 0, sfp = 0, card = 0, trigger = 0;
    std::vector<Hit> hits;
};

int main()
{
    static_assert(sizeof(EXT_STR_h101_febex) == sizeof(EXT_STR_h101_febex_onion));

    EXT_STR_h101_febex_onion bank{};
    assert(febex::ValidSummary(bank));

    bank.FEBEX_PRESENT[11] = 1;
    bank.FEBEX_WR_T[0] = 0x1234;
    bank.FEBEX_WR_T[3] = 0xffff;
    assert(febex::WhiteRabbitTimestamp(bank) == 0xffff000000001234ULL);
    assert(febex::JoinTicks(0xffff, 0xffffffff) == 0xffffffffffffULL);

    bank.FEBEX_HITHI = bank.FEBEX_HITLO = bank.FEBEX_ENERGY =
        bank.FEBEX_CFD = bank.FEBEX_PILEUP = bank.FEBEX_OVERFLOW = 1;
    bank.FEBEX_HITHII[0] = bank.FEBEX_HITLOI[0] = bank.FEBEX_ENERGYI[0] =
        bank.FEBEX_CFDI[0] = bank.FEBEX_PILEUPI[0] = bank.FEBEX_OVERFLOWI[0] = 192;
    assert(febex::ValidSummary(bank)); // All-zero hit on the last channel.
    bank.FEBEX_WR_ID = 0x400;
    bank.FEBEX_SFP[11] = 3;
    bank.FEBEX_CARD[11] = 4;
    bank.FEBEX_PRESENT[0] = 1; // Present board with no hit.
    bank.FEBEX_EVENTHI[11] = 0x1234;
    bank.FEBEX_EVENTLO[11] = 0x56789abc;
    std::vector<Board> boards;
    const auto append = [&]() -> Board& { return boards.emplace_back(); };
    assert(febex::DecodeSummary(bank, 60, "DEGAS", append));
    assert(boards.size() == 2 && boards[0].hits.empty());
    const auto& last = boards[1];
    assert(last.slot == 11 && last.sfp == 3 && last.card == 4 && last.procid == 60);
    assert(last.detectorName == "DEGAS" && last.wrId == 0x400);
    assert(last.eventTicks == 0x123456789abcULL && last.wrTimestamp == 0xffff000000001234ULL);
    assert(last.hits.size() == 1 && last.hits[0].channel == 15);
    assert(last.hits[0].channelTicks == 0 && last.hits[0].energyWord == 0);


    bank.FEBEX_OVERFLOWI[0] = 191;
    assert(!febex::ValidSummary(bank));
    assert(!febex::DecodeSummary(bank, 60, "DEGAS", append));
    assert(boards.size() == 2); // A malformed bank never produces partial output.
    bank.FEBEX_OVERFLOWI[0] = 192;
    bank.FEBEX_PRESENT[11] = 0;
    assert(!febex::ValidSummary(bank));
    bank.FEBEX_PRESENT[11] = 1;
    bank.FEBEX_HITHI = 193;
    assert(!febex::ValidSummary(bank));
}
