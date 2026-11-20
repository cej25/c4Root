#include "DegasReader.h"

#include "DegasRawData.h"
#include "FebexRegistration.h"
#include "FebexSummary.h"

#include "FairRootManager.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"

DegasReader::DegasReader(EXT_STR_h101_febex_onion_t* input, std::size_t offset,
                         std::uint16_t procid, const std::string& bankName, BankAccess access)
    : c4Reader("DegasReader"), fInput(input), fOffset(offset), fProcId(procid),
      fBankName(bankName), fAccess(access), fOutput(new DegasRawData)
{
}

DegasReader::~DegasReader()
{
    delete fOutput;
}

Bool_t DegasReader::Init(ext_data_struct_info* info)
{
    auto* manager = FairRootManager::Instance();
    if (!fInput || !info || !manager || fBankName.empty())
    {
        c4LOG(error, "DegasReader requires a FEBEX bank, structure info, and FairRootManager");
        return kFALSE;
    }
    if (fAccess == BankAccess::Register)
    {
        if (!febex::RegisterBank(*info, fOffset, fBankName))
        {
            c4LOG(error, "Failed to register DEGAS FEBEX bank " << fBankName);
            return kFALSE;
        }
        *fInput = {};
    }

    manager->RegisterAny("DegasRawData", fOutput, !fOnline);
    return kTRUE;
}

Bool_t DegasReader::Read()
{
    static const std::string detectorName = "DEGAS";
    if (!febex::DecodeSummary(*fInput, fProcId, detectorName, [this]() -> FebexRawData& {
            return fOutput->FEBEX.emplace_back();
        }))
    {
        c4LOG(error, fBankName << ": invalid FEBEX RAW columns for DEGAS");
        return kFALSE;
    }
    return kTRUE;
}

void DegasReader::Reset()
{
    fOutput->FEBEX.clear();
}
