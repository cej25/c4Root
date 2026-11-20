#include "../c4source/digitisers/febex/FebexSummary.h"

#include <cassert>

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

    bank.FEBEX_OVERFLOWI[0] = 191;
    assert(!febex::ValidSummary(bank));
    bank.FEBEX_OVERFLOWI[0] = 192;
    bank.FEBEX_PRESENT[11] = 0;
    assert(!febex::ValidSummary(bank));
    bank.FEBEX_PRESENT[11] = 1;
    bank.FEBEX_HITHI = 193;
    assert(!febex::ValidSummary(bank));
}
