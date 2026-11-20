#include "TamexReader.h"

#include "TamexRawDecode.h"

#include "FairRootManager.h"
#include "TClonesArray.h"
#include "TClass.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"

extern "C"
{
#include "ext_data_client.h"
#include "ext_h101_bgo.h"
#include "ext_h101_fatima.h"
#include "ext_h101_bplast.h"
#include "ext_h101_mcp.h"
}

#include <cstddef>
#include <cstdint>
#include <cstring>

TamexReader::TamexReader(void* input, std::size_t offset,
                         std::uint16_t procid, InputKind kind,
                         const std::string& detectorName)
    : c4Reader("TamexReader"),
      fInput(input),
      fOffset(offset),
      fProcId(procid),
      fDetectorName(detectorName),
      fKind(kind)
{
}

TamexReader::TamexReader(EXT_STR_h101_bgo_onion_t* input, std::size_t offset,
                         std::uint16_t procid, const std::string& detectorName)
    : TamexReader(input, offset, procid, InputKind::BGO, detectorName) {}

TamexReader::TamexReader(EXT_STR_h101_fatima_onion_t* input, std::size_t offset,
                         std::uint16_t procid, const std::string& detectorName)
    : TamexReader(input, offset, procid, InputKind::Fatima, detectorName) {}

TamexReader::TamexReader(EXT_STR_h101_bplast_onion_t* input, std::size_t offset,
                         std::uint16_t procid, const std::string& detectorName)
    : TamexReader(input, offset, procid, InputKind::bPlast, detectorName) {}

TamexReader::TamexReader(EXT_STR_h101_mcp_onion_t* input, std::size_t offset,
                         std::uint16_t procid, const std::string& detectorName)
    : TamexReader(input, offset, procid, InputKind::MCP, detectorName) {}

TamexReader::~TamexReader()
{
    if (fOwnsArray) delete fArray;
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

    // All TAMEX readers append board records to the same event-level collection.
    // Configured procid and detector name are stored in each board record, not the branch name.
    // UcesbSource calls each reader's Reset() after the event, so no Read()
    // may clear this shared array.
    auto* mgr = FairRootManager::Instance();
    if (auto* existing = mgr->GetObject("TamexRawData"))
    {
        fArray = dynamic_cast<TClonesArray*>(existing);
        if (!fArray || TString(fArray->GetClass()->GetName()) != "TamexRawData")
        {
            c4LOG(error, "Existing TamexRawData branch has an incompatible type");
            return kFALSE;
        }
        fOwnsArray = false;
    }
    else
    {
        fArray = new TClonesArray("TamexRawData");
        fOwnsArray = true;
        mgr->Register("TamexRawData", "TamexRawDataFolder", fArray, !fOnline);
        fArray->Clear("C");
    }
    return kTRUE;
}

Bool_t TamexReader::Read()
{
    if (!fInput || !fArray) return kFALSE;
    const auto nextBoard = [this]() -> TamexRawData& {
        return *static_cast<TamexRawData*>(fArray->ConstructedAt(fArray->GetEntriesFast()));
    };
    switch (fKind)
    {
    case InputKind::BGO:
    {
        const auto& data = *static_cast<const EXT_STR_h101_bgo_onion*>(fInput);
        tamex::ReadBoards(data.bgo_tamex, fProcId, fDetectorName, static_cast<std::uint16_t>(data.bgo_ts_subsystem_id),
                   tamex::AssembleWhiteRabbitTimestamp(data.bgo_ts_t), nextBoard);
        break;
    }
    case InputKind::Fatima:
    {
        const auto& data = *static_cast<const EXT_STR_h101_fatima_onion*>(fInput);
        tamex::ReadBoards(data.fatima_tamex, fProcId, fDetectorName, static_cast<std::uint16_t>(data.fatima_ts_subsystem_id),
                   tamex::AssembleWhiteRabbitTimestamp(data.fatima_ts_t), nextBoard);
        break;
    }
    case InputKind::bPlast:
    {
        const auto& data = *static_cast<const EXT_STR_h101_bplast_onion*>(fInput);
        tamex::ReadBoards(data.bplast_tamex, fProcId, fDetectorName, static_cast<std::uint16_t>(data.bplast_ts_subsystem_id),
                   tamex::AssembleWhiteRabbitTimestamp(data.bplast_ts_t), nextBoard);
        break;
    }
    case InputKind::MCP:
    {
        const auto& data = *static_cast<const EXT_STR_h101_mcp_onion*>(fInput);
        tamex::ReadBoards(data.mcp_tamex, fProcId, fDetectorName, static_cast<std::uint16_t>(data.mcp_ts_subsystem_id),
                   tamex::AssembleWhiteRabbitTimestamp(data.mcp_ts_t), nextBoard);
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
