#include "V1290Reader.h"
#include "VmeRawDecode.h"
#include "FairRootManager.h"
#include "TClonesArray.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"
#include <iterator>

extern "C" {
#include "ext_data_client.h"
#include "ext_h101_fatimavme.h"
}

V1290Reader::V1290Reader(EXT_STR_h101_fatimavme_onion_t* input,
                         std::size_t offset, std::uint16_t procid)
    : c4Reader("V1290Reader"), fInput(input), fOffset(offset), fProcId(procid) {}

V1290Reader::~V1290Reader() { delete fOutput; }

Bool_t V1290Reader::Init(ext_data_struct_info* info) {
    if (!info || !fInput || !FairRootManager::Instance()) return kFALSE;
    Int_t ok = 1;
    if (fRegisterStructure) {
        EXT_STR_h101_fatimavme_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_fatimavme, 0);
    }
    if (!ok) {
        c4LOG(error, "V1290Reader: cannot register UCESB FATIMA VME bank");
        return kFALSE;
    }
    // Do not clear fInput: V1751Reader shares the same UCESB subevent.
    fOutput = new TClonesArray("V1290RawData");
    FairRootManager::Instance()->Register("V1290RawData", "VmeRawData", fOutput, !fOnline);
    return kTRUE;
}

Bool_t V1290Reader::Read() {
    const auto* input = fInput;
    if (!input || !fOutput) return kFALSE;
    const auto wr = c4::vme::Timestamp(input->fatimavme_ts_t);
    const auto subsystem = input->fatimavme_ts_subsystem_id;
    for (std::size_t slot = 0; slot < std::size(input->fatimavme_tdc); ++slot) {
        c4::vme::DecodeV1290(input->fatimavme_tdc[slot], slot,
            [this, wr, subsystem](std::size_t slot, int geo,
                                  std::uint32_t channel, std::uint32_t index,
                                  const auto& bank) {
                auto* hit = static_cast<V1290RawData*>(
                    fOutput->ConstructedAt(fOutput->GetEntriesFast()));
                c4::vme::FillV1290(*hit, fProcId, subsystem, wr, slot, geo, channel, index, bank);
            });
    }
    return kTRUE;
}

void V1290Reader::Reset() {
    if (fOutput) fOutput->Clear("C");
}
ClassImp(V1290Reader)
