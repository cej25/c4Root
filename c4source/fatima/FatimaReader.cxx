#include "FatimaReader.h"

#include "FatimaRawData.h"
#include "TamexRawDecode.h"
#include "VmeRawDecode.h"
#include "FairRootManager.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"

extern "C"
{
#include "ext_data_client.h"
#include "ext_h101_fatima.h"
#include "ext_h101_fatimavme.h"
}

#include <iterator>
#include <string>

FatimaReader::FatimaReader(TamexInput tamex, VmeInput vme, BankAccess access)
    : c4Reader("FatimaReader"), fTamex(tamex), fVme(vme), fAccess(access),
      fOutput(new FatimaRawData)
{
}

FatimaReader::~FatimaReader()
{
    delete fOutput;
}

Bool_t FatimaReader::Init(ext_data_struct_info* info)
{
    auto* manager = FairRootManager::Instance();
    if (!info || !manager || (!fTamex.bank && !fVme.bank)) return kFALSE;
    if (fAccess == BankAccess::Register)
    {
        Int_t ok = 1;
        if (fTamex.bank)
        {
            EXT_STR_h101_fatima_ITEMS_INFO(ok, *info, fTamex.offset, EXT_STR_h101_fatima, 0);
            if (!ok)
            {
                c4LOG(error, "Could not register the FATIMA TAMEX bank");
                return kFALSE;
            }
            *fTamex.bank = {};
        }
        if (fVme.bank)
        {
            EXT_STR_h101_fatimavme_ITEMS_INFO(ok, *info, fVme.offset, EXT_STR_h101_fatimavme, 0);
            if (!ok)
            {
                c4LOG(error, "Could not register the FATIMA VME bank");
                return kFALSE;
            }
            *fVme.bank = {};
        }
    }
    manager->RegisterAny("FatimaRawData", fOutput, !fOnline);
    return kTRUE;
}

Bool_t FatimaReader::Read()
{
    if (fTamex.bank)
    {
        static const std::string detector = "FATIMA";
        const auto& input = *fTamex.bank;
        auto& output = fOutput->TAMEX;
        output.wrId = input.fatima_ts_subsystem_id;
        output.wrTimestamp = tamex::AssembleWhiteRabbitTimestamp(input.fatima_ts_t);
        tamex::ReadBoards(input.fatima_tamex, fTamex.procid, detector, output.wrId, output.wrTimestamp,
                          [&]() -> TamexRawData& { return output.boards.emplace_back(); });
    }

    if (fVme.bank)
    {
        const auto& input = *fVme.bank;
        auto& output = fOutput->VMEChain;
        output.wrId = input.fatimavme_ts_subsystem_id;
        output.wrTimestamp = c4::vme::Timestamp(input.fatimavme_ts_t);
        for (std::size_t slot = 0; slot < std::size(input.fatimavme_qdc); ++slot)
            c4::vme::DecodeV1751(input.fatimavme_qdc[slot], slot,
                [&](std::size_t index, int board, std::uint32_t channel, std::uint32_t packed, const auto& bank) {
                    c4::vme::FillV1751(output.QDC.emplace_back(), fVme.procid, output.wrId,
                                      output.wrTimestamp, index, board, channel, packed, bank);
                });
        for (std::size_t slot = 0; slot < std::size(input.fatimavme_tdc); ++slot)
            c4::vme::DecodeV1290(input.fatimavme_tdc[slot], slot,
                [&](std::size_t index, int geo, std::uint32_t channel, std::uint32_t packed, const auto& bank) {
                    c4::vme::FillV1290(output.TDC.emplace_back(), fVme.procid, output.wrId,
                                      output.wrTimestamp, index, geo, channel, packed, bank);
                });
    }
    return kTRUE;
}

void FatimaReader::Reset()
{
    fOutput->TAMEX.wrId = 0;
    fOutput->TAMEX.wrTimestamp = 0;
    fOutput->TAMEX.boards.clear();
    fOutput->VMEChain.wrId = 0;
    fOutput->VMEChain.wrTimestamp = 0;
    fOutput->VMEChain.QDC.clear();
    fOutput->VMEChain.TDC.clear();
}

ClassImp(FatimaReader)
