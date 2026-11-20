#include "FebexReader.h"

#include "FebexRawData.h"
#include "FebexSummary.h"

#include "FairRootManager.h"
#include "TClonesArray.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"

extern "C"
{
#include "ext_data_client.h"
}

#include <iterator>

FebexReader::FebexReader(EXT_STR_h101_febex_onion_t* input, std::size_t offset,
                         std::uint16_t procid, const std::string& detectorName)
    : c4Reader("FebexReader"), fInput(input), fOffset(offset), fProcId(procid),
      fDetectorName(detectorName)
{
}

FebexReader::~FebexReader()
{
    delete fArray;
}

Bool_t FebexReader::Init(ext_data_struct_info* info)
{
    auto* manager = FairRootManager::Instance();
    if (!fInput || !info || !manager || manager->GetObject("FebexRawData"))
    {
        c4LOG(error, "FebexReader requires one FEBEX RAW bank, structure info, and FairRootManager");
        return kFALSE;
    }

    Int_t ok = 0;
    EXT_STR_h101_febex_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_febex, 0);
    if (!ok)
    {
        c4LOG(error, "Failed to register FEBEX RAW structure");
        return kFALSE;
    }

    *fInput = {};
    fArray = new TClonesArray("FebexRawData");
    manager->Register("FebexRawData", "FEBEX raw data", fArray, !fOnline);
    return kTRUE;
}

Bool_t FebexReader::Read()
{
    const auto& bank = *fInput;
    if (!febex::ValidSummary(bank))
    {
        c4LOG(error, "FEBEX RAW hit columns disagree or refer to an absent board");
        return kFALSE;
    }

    const auto wr = febex::WhiteRabbitTimestamp(bank);
    std::uint32_t hitIndex = 0;
    for (std::size_t slot = 0; slot < std::size(bank.FEBEX_PRESENT); ++slot)
    {
        if (!bank.FEBEX_PRESENT[slot]) continue;

        auto* output = static_cast<FebexRawData*>(fArray->ConstructedAt(fArray->GetEntriesFast()));
        output->detectorName = fDetectorName;
        output->eventTicks = febex::JoinTicks(bank.FEBEX_EVENTHI[slot], bank.FEBEX_EVENTLO[slot]);
        output->wrTimestamp = wr;
        output->wrId = bank.FEBEX_WR_ID;
        output->procid = fProcId;
        output->hitPattern = bank.FEBEX_PATTERN[slot];
        output->slot = slot;
        output->sfp = bank.FEBEX_SFP[slot];
        output->card = bank.FEBEX_CARD[slot];
        output->trigger = bank.FEBEX_TRIGGER[slot];
        output->hits.clear();
        const auto lastChannel = (slot + 1) * febex::ChannelsPerBoard;
        while (hitIndex < bank.FEBEX_HITHI && bank.FEBEX_HITHII[hitIndex] <= lastChannel)
        {
            auto& hit = output->hits.emplace_back();
            hit.channel = (bank.FEBEX_HITHII[hitIndex] - 1) % febex::ChannelsPerBoard;
            hit.channelTicks = febex::JoinTicks(bank.FEBEX_HITHIv[hitIndex], bank.FEBEX_HITLOv[hitIndex]);
            hit.cfd = bank.FEBEX_CFDv[hitIndex];
            hit.energyWord = bank.FEBEX_ENERGYv[hitIndex];
            hit.pileup = bank.FEBEX_PILEUPv[hitIndex] != 0;
            hit.overflow = bank.FEBEX_OVERFLOWv[hitIndex] != 0;
            ++hitIndex;
        }
    }
    return kTRUE;
}

void FebexReader::Reset()
{
    if (fArray) fArray->Clear();
}
