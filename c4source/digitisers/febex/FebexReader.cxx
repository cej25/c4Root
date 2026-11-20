#include "FebexReader.h"

#include "FebexRawData.h"
#include "FebexRegistration.h"
#include "FebexSummary.h"

#include "FairRootManager.h"
#include "TClonesArray.h"
#include "TClass.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"

FebexReader::FebexReader(EXT_STR_h101_febex_onion_t* input, std::size_t offset,
                         std::uint16_t procid, const std::string& detectorName,
                         const std::string& bankName)
    : c4Reader("FebexReader"), fInput(input), fOffset(offset), fProcId(procid),
      fDetectorName(detectorName), fBankName(bankName)
{
}

FebexReader::~FebexReader()
{
    if (fOwnsArray) delete fArray;
}

Bool_t FebexReader::Init(ext_data_struct_info* info)
{
    auto* manager = FairRootManager::Instance();
    if (!fInput || !info || !manager || fBankName.empty())
    {
        c4LOG(error, "FebexReader requires a FEBEX RAW bank, structure info, and FairRootManager");
        return kFALSE;
    }

    auto* existing = manager->GetObject("FebexRawData");
    fArray = dynamic_cast<TClonesArray*>(existing);
    if (existing && (!fArray || fArray->GetClass() != FebexRawData::Class()))
    {
        c4LOG(error, "Existing FebexRawData branch has an incompatible type");
        return kFALSE;
    }

    if (!febex::RegisterBank(*info, fOffset, fBankName))
    {
        c4LOG(error, "Failed to register FEBEX RAW bank " << fBankName);
        return kFALSE;
    }

    *fInput = {};
    if (!existing)
    {
        fArray = new TClonesArray("FebexRawData");
        fOwnsArray = true;
        manager->Register("FebexRawData", "FEBEX raw data", fArray, !fOnline);
    }
    return kTRUE;
}

Bool_t FebexReader::Read()
{
    if (!febex::DecodeSummary(*fInput, fProcId, fDetectorName, [this]() -> FebexRawData& {
            return *static_cast<FebexRawData*>(fArray->ConstructedAt(fArray->GetEntriesFast()));
        }))
    {
        c4LOG(error, fBankName << ": FEBEX RAW hit columns disagree or refer to an absent board");
        return kFALSE;
    }
    return kTRUE;
}

void FebexReader::Reset()
{
    // UcesbSource resets all readers after the event. Clear the shared array once.
    if (fOwnsArray) fArray->Clear();
}
