#include "DegasReader.h"

#include "DegasRawData.h"
#include "FebexReader.h"

#include "FairRootManager.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"

#include <cstring>
#include <utility>

extern "C"
{
#include "ext_data_client.h"
#include "ext_h101_degas.h"
#include "ext_h101_degas_traces.h"
#include "ext_h101_germanium_traces.h"
}

DegasReader::DegasReader(EXT_STR_h101_degas_onion_t* input, std::size_t offset,
                         std::uint16_t procid)
    : c4Reader("DegasReader"), fInput(input), fOffset(offset), fProcId(procid),
      fOutput(new DegasRawData)
{
}

DegasReader::DegasReader(EXT_STR_h101_degas_traces_onion_t* input, std::size_t offset,
                         std::uint16_t procid)
    : c4Reader("DegasReader"), fTraceInput(input), fOffset(offset), fProcId(procid),
      fOutput(new DegasRawData)
{
}

DegasReader::DegasReader(EXT_STR_h101_germanium_traces_onion_t* input, std::size_t offset,
                         std::uint16_t procid)
    : c4Reader("DegasReader"), fLegacyTraceInput(input), fOffset(offset), fProcId(procid),
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
    if ((!fInput && !fTraceInput && !fLegacyTraceInput) || !info || !manager)
    {
        c4LOG(error, "DegasReader requires a FEBEX bank, structure info, and FairRootManager");
        return kFALSE;
    }
    Int_t ok;
    if (fTraceInput)
    {
        EXT_STR_h101_degas_traces_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_degas_traces, 0);
    }
    else if (fLegacyTraceInput)
    {
        EXT_STR_h101_germanium_traces_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_germanium_traces, 0);
    }
    else
    {
        EXT_STR_h101_degas_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_degas, 0);
    }
    if (!ok)
    {
        c4LOG(error, "Failed to register DEGAS FEBEX structure");
        return kFALSE;
    }
    if (fTraceInput) std::memset(fTraceInput, 0, sizeof *fTraceInput);
    else if (fLegacyTraceInput) std::memset(fLegacyTraceInput, 0, sizeof *fLegacyTraceInput);
    else *fInput = {};

    manager->RegisterAny("DegasRawData", fOutput, !fOnline);
    return kTRUE;
}

namespace
{
struct TraceBoard
{
    FebexRawData summary;
    std::uint32_t reportedHits = 0;
    std::vector<std::vector<UShort_t>> traces;
};

struct TraceCrate
{
    std::uint64_t wrTimestamp;
    std::uint16_t wrId;
    std::uint16_t procid;
    std::vector<TraceBoard> boards;
};

template <febex::TraceLayout Layout, typename Board, std::size_t N>
void ReadTraceBank(const Board (&boards)[N], const std::uint32_t (&wrWords)[4],
                   std::uint16_t wrId, std::uint16_t procid, DegasRawData& output)
{
    TraceCrate crate{febex::WhiteRabbitTimestamp(wrWords), wrId, procid, {}};
    febex::ReadTraceBoards<Layout>(boards, crate, "DEGAS");
    for (auto& board : crate.boards)
    {
        for (std::size_t i = 0; i < board.summary.hits.size(); ++i)
            board.summary.hits[i].trace = std::move(board.traces[i]);
        output.FEBEX.emplace_back(std::move(board.summary));
    }
}
}

Bool_t DegasReader::Read()
{
    if (fTraceInput)
    {
        const auto& input = *fTraceInput;
        ReadTraceBank<febex::TraceLayout::Nested>(input.degastrace_data, input.degastrace_ts_t,
            input.degastrace_ts_subsystem_id, fProcId, *fOutput);
        return kTRUE;
    }
    if (fLegacyTraceInput)
    {
        const auto& input = *fLegacyTraceInput;
        ReadTraceBank<febex::TraceLayout::Flat>(input.germanium_traces_data, input.germanium_traces_ts_t,
            input.germanium_traces_ts_subsystem_id, fProcId, *fOutput);
        return kTRUE;
    }

    const auto& input = *fInput;
    if (const auto badSlot = febex::ReadBoards(input.germanium_data, input.germanium_ts_t,
                                              input.germanium_ts_subsystem_id, fProcId,
                                              "DEGAS", fOutput->FEBEX))
    {
        c4LOG(error, "Inconsistent FEBEX hit columns for DEGAS slot " << *badSlot);
        Reset();
        return kFALSE;
    }
    return kTRUE;
}

void DegasReader::Reset()
{
    fOutput->FEBEX.clear();
}
