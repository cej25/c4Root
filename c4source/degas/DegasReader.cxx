#include "DegasReader.h"

#include "DegasRawData.h"
#include "FebexTiming.h"

#include "FairRootManager.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"

#include <iterator>

extern "C"
{
#include "ext_data_client.h"
#include "ext_h101_degas.h"
}

DegasReader::DegasReader(EXT_STR_h101_degas_onion_t* input, std::size_t offset,
                         std::uint16_t procid)
    : c4Reader("DegasReader"), fInput(input), fOffset(offset), fProcId(procid),
      fOutput(new DegasRawData)
{
}

DegasReader::~DegasReader()
{
    delete fOutput;
}

Bool_t DegasReader::Init(ext_data_struct_info* info)
{
    auto* manager = FairRootManager::Instance();
    if (!fInput || !info || !manager)
    {
        c4LOG(error, "DegasReader requires a FEBEX bank, structure info, and FairRootManager");
        return kFALSE;
    }
    Int_t ok;
    EXT_STR_h101_degas_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_degas, 0);
    if (!ok)
    {
        c4LOG(error, "Failed to register DEGAS FEBEX structure");
        return kFALSE;
    }
    *fInput = {};

    manager->RegisterAny("DegasRawData", fOutput, !fOnline);
    return kTRUE;
}

Bool_t DegasReader::Read()
{
    const auto& input = *fInput;
    std::uint64_t timestamp = 0;
    for (std::size_t word = 0; word < std::size(input.germanium_ts_t); ++word)
        timestamp |= std::uint64_t{input.germanium_ts_t[word]} << (16 * word);

    for (std::size_t slot = 0; slot < std::size(input.germanium_data); ++slot)
    {
        const auto& board = input.germanium_data[slot];
        if (!board.present) continue;

        auto& output = fOutput->FEBEX.emplace_back();
        output.detectorName = "DEGAS";
        output.procid = fProcId;
        output.wrId = input.germanium_ts_subsystem_id;
        output.wrTimestamp = timestamp;
        output.slot = slot;
        output.sfp = board.sfp;
        output.card = board.board_id;
        output.trigger = board.trig;
        output.hitPattern = board.hit_pattern;
        output.eventTicks = febex::JoinTicks(board.event_trigger_time_hi, board.event_trigger_time_lo);

        const auto count = board.channel_energy;
        if (count > std::size(board.channel_energyv) ||
            count != board.channel_trigger_time_hi || count != board.channel_trigger_time_lo ||
            count != board.channel_cfd || count != board.pileup || count != board.overflow)
        {
            c4LOG(error, "Inconsistent FEBEX hit counts for DEGAS slot " << slot);
            Reset();
            return kFALSE;
        }

        std::uint32_t previousChannel = 0;
        output.hits.reserve(count);
        for (std::size_t i = 0; i < count; ++i)
        {
            const auto channel = board.channel_energyI[i];
            if (channel <= previousChannel || channel > std::size(board.channel_energyv) ||
                channel != board.channel_trigger_time_hiI[i] || channel != board.channel_trigger_time_loI[i] ||
                channel != board.channel_cfdI[i] || channel != board.pileupI[i] || channel != board.overflowI[i])
            {
                c4LOG(error, "Inconsistent FEBEX channel indices for DEGAS slot " << slot);
                Reset();
                return kFALSE;
            }
            previousChannel = channel;

            auto& hit = output.hits.emplace_back();
            hit.channel = channel - 1; // UCESB sparse indices are one-based.
            hit.channelTicks = febex::JoinTicks(board.channel_trigger_time_hiv[i], board.channel_trigger_time_lov[i]);
            hit.energyWord = board.channel_energyv[i];
            hit.cfd = board.channel_cfdv[i];
            hit.pileup = board.pileupv[i] != 0;
            hit.overflow = board.overflowv[i] != 0;
        }
    }
    return kTRUE;
}

void DegasReader::Reset()
{
    fOutput->FEBEX.clear();
}
