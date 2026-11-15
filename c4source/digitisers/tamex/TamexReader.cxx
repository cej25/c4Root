#include "TamexReader.h"

#include "TamexDecoder.h"
#include "TamexRawData.h"

#include "FairRootManager.h"
#include "TClonesArray.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"

extern "C"
{
#include "ext_h101_bgo.h"
#include "ext_h101_fatima.h"
#include "ext_h101_bplast.h"
#include "ext_h101_mcp.h"
}

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace
{
template <typename Board, std::size_t N>
void ReadBoards(const Board (&banks)[N], std::uint16_t source,
                std::uint16_t wr_subsystem, std::uint64_t wr_timestamp,
                TClonesArray& output)
{
    static_assert(N <= 65535, "TAMEX board identifier exceeds Raw data capacity");
    for (std::size_t i = 0; i < N; ++i)
    {
        const auto& bank = banks[i];
        // Preserve trigger-only records, including legacy bPlast trigger 3.
        if (bank.event_size == 0 && bank.trig == 0) continue;

        const auto index = output.GetEntriesFast();
        auto* raw = static_cast<TamexRawData*>(output.ConstructedAt(index));
        raw->SetMetadata(source, static_cast<std::uint16_t>(i),
                         static_cast<std::uint16_t>(bank.trig),
                         wr_subsystem, wr_timestamp, 4);

        const auto view = tamex::MakeBoardView(bank);
        raw->ReserveWords(c4_tamex_packed_safety::EventHitBudget(bank.event_size));
        tamex::Tamex4Decoder::Decode(
            view, static_cast<std::uint16_t>(i),
            [raw](const tamex::RawWord& word) {
                TamexRawWord persisted{};
                persisted.kind = word.kind == tamex::WordKind::Epoch
                                     ? TamexRawWord::Epoch : TamexRawWord::Edge;
                persisted.packed_index = word.packed_index;
                persisted.epoch = word.epoch;
                persisted.channel = word.channel;
                persisted.coarse = word.coarse;
                persisted.fine = word.fine;
                persisted.leading = word.leading;
                if (word.has_preceding_epoch)
                    persisted.flags |= TamexRawWord::HasPrecedingEpoch;
                if (word.changed_channel_without_epoch)
                    persisted.flags |= TamexRawWord::MissingEpochOnChannelChange;
                if (word.channel_order_decreased)
                    persisted.flags |= TamexRawWord::DescendingChannel;
                if (word.invalid_fine)
                    persisted.flags |= TamexRawWord::InvalidFine;
                raw->AddWord(persisted);
            });
    }
}
} // namespace

TamexReader::TamexReader(void* input, std::size_t offset,
                         std::uint16_t source, InputKind kind)
    : c4Reader("TamexReader"),
      fInput(input),
      fOffset(offset),
      fSource(source),
      fKind(kind),
      fArray(new TClonesArray("TamexRawData"))
{
}

TamexReader::TamexReader(EXT_STR_h101_bgo_onion_t* input, std::size_t offset,
                         std::uint16_t source)
    : TamexReader(input, offset, source, InputKind::BGO) {}

TamexReader::TamexReader(EXT_STR_h101_fatima_onion_t* input, std::size_t offset,
                         std::uint16_t source)
    : TamexReader(input, offset, source, InputKind::Fatima) {}

TamexReader::TamexReader(EXT_STR_h101_bplast_onion_t* input, std::size_t offset,
                         std::uint16_t source)
    : TamexReader(input, offset, source, InputKind::bPlast) {}

TamexReader::TamexReader(EXT_STR_h101_mcp_onion_t* input, std::size_t offset,
                         std::uint16_t source)
    : TamexReader(input, offset, source, InputKind::MCP) {}

TamexReader::~TamexReader()
{
    delete fArray;
}

Bool_t TamexReader::Init(ext_data_struct_info* info)
{
    if (!fInput || !info || !FairRootManager::Instance())
    {
        c4LOG(error, "TamexReader requires UCESB input, structure info, and FairRootManager");
        return kFALSE;
    }

    Int_t ok = 0;
    switch (fKind)
    {
    case InputKind::BGO:
        EXT_STR_h101_bgo_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_bgo, 0);
        if (ok) std::memset(fInput, 0, sizeof(EXT_STR_h101_bgo_onion));
        break;
    case InputKind::Fatima:
        EXT_STR_h101_fatima_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_fatima, 0);
        if (ok) std::memset(fInput, 0, sizeof(EXT_STR_h101_fatima_onion));
        break;
    case InputKind::bPlast:
        EXT_STR_h101_bplast_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_bplast, 0);
        if (ok) std::memset(fInput, 0, sizeof(EXT_STR_h101_bplast_onion));
        break;
    case InputKind::MCP:
        EXT_STR_h101_mcp_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_mcp, 0);
        if (ok) std::memset(fInput, 0, sizeof(EXT_STR_h101_mcp_onion));
        break;
    }
    if (!ok)
    {
        c4LOG(error, "Failed to register TAMEX UCESB structure");
        return kFALSE;
    }

    // Distinct sources can coexist, provided their identifiers are unique.
    // Branch persistence follows the same online/offline convention as readers.
    const TString branch = TString::Format("TamexRawData_%u", static_cast<unsigned>(fSource));
    FairRootManager::Instance()->Register(
        branch.Data(), "TamexRawDataFolder", fArray, !fOnline);
    fArray->Clear("C");
    return kTRUE;
}

Bool_t TamexReader::Read()
{
    if (!fInput) return kFALSE;
    fArray->Clear("C");
    switch (fKind)
    {
    case InputKind::BGO:
    {
        const auto& data = *static_cast<const EXT_STR_h101_bgo_onion*>(fInput);
        ReadBoards(data.bgo_tamex, fSource, static_cast<std::uint16_t>(data.bgo_ts_subsystem_id),
                   tamex::AssembleWhiteRabbitTimestamp(data.bgo_ts_t), *fArray);
        break;
    }
    case InputKind::Fatima:
    {
        const auto& data = *static_cast<const EXT_STR_h101_fatima_onion*>(fInput);
        ReadBoards(data.fatima_tamex, fSource, static_cast<std::uint16_t>(data.fatima_ts_subsystem_id),
                   tamex::AssembleWhiteRabbitTimestamp(data.fatima_ts_t), *fArray);
        break;
    }
    case InputKind::bPlast:
    {
        const auto& data = *static_cast<const EXT_STR_h101_bplast_onion*>(fInput);
        ReadBoards(data.bplast_tamex, fSource, static_cast<std::uint16_t>(data.bplast_ts_subsystem_id),
                   tamex::AssembleWhiteRabbitTimestamp(data.bplast_ts_t), *fArray);
        break;
    }
    case InputKind::MCP:
    {
        const auto& data = *static_cast<const EXT_STR_h101_mcp_onion*>(fInput);
        ReadBoards(data.mcp_tamex, fSource, static_cast<std::uint16_t>(data.mcp_ts_subsystem_id),
                   tamex::AssembleWhiteRabbitTimestamp(data.mcp_ts_t), *fArray);
        break;
    }
    }
    return kTRUE;
}

void TamexReader::Reset()
{
    if (fArray) fArray->Clear("C");
}

ClassImp(TamexReader)
