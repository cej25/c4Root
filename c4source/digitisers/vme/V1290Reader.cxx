#include "V1290Reader.h"
#include "VmeDigitiserDecode.h"
#include "VmeDigitiserRawData.h"
#include "FairRootManager.h"
#include "TClonesArray.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"
#include <iterator>

extern "C" {
#include "ext_data_client.h"
#include "ext_h101_fatimavme.h"
#include "ext_h101_fatimavme_s100.h"
}

V1290Reader::V1290Reader(EXT_STR_h101_fatimavme_onion_t* input,
                         std::size_t offset, std::uint16_t procid)
    : c4Reader("V1290Reader"), fInput(input), fOffset(offset), fProcId(procid) {}

V1290Reader::V1290Reader(EXT_STR_h101_fatimavme_s100_onion_t* input,
                         std::size_t offset, std::uint16_t procid)
    : c4Reader("V1290Reader"), fS100Input(input), fOffset(offset), fProcId(procid) {}

V1290Reader::~V1290Reader() { delete fOutput; }

Bool_t V1290Reader::Init(ext_data_struct_info* info) {
    if (!info || (!fInput && !fS100Input) || !FairRootManager::Instance()) return kFALSE;
    Int_t ok = 1;
    if (fRegisterStructure) {
        if (fS100Input) {
            EXT_STR_h101_fatimavme_s100_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_fatimavme_s100, 0);
        } else {
            EXT_STR_h101_fatimavme_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_fatimavme, 0);
        }
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
    return fS100Input ? ReadBanks(fS100Input) : ReadBanks(fInput);
}

template <typename Bank>
Bool_t V1290Reader::ReadBanks(const Bank* input) {
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
                hit->procid = fProcId;
                hit->board_slot = static_cast<std::uint16_t>(slot);
                hit->geo = geo;
                hit->channel = static_cast<std::uint16_t>(channel);
                hit->wr_timestamp = wr;
                hit->wr_subsystem = subsystem;
                hit->measurement = bank._measurement_data[index];
                hit->leading_or_trailing = bank._measurement_leadOrTrailv[index];
            });
    }
    return kTRUE;
}

void V1290Reader::Reset() {
    if (fOutput) fOutput->Clear("C");
}
ClassImp(V1290Reader)
