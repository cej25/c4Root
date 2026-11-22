#include "DegasReader.h"

#include "DegasRawData.h"
#include "FebexReader.h"

#include "FairRootManager.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"

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
