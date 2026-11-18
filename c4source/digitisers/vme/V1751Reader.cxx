#include "V1751Reader.h"
#include "VmeDigitiserDecode.h"
#include "VmeDigitiserRawData.h"
#include "FairRootManager.h"
#include "TClonesArray.h"
#include "c4Logger.h"
#include "ext_data_struct_info.hh"

extern "C" {
#include "ext_data_client.h"
#include "ext_h101_fatimavme.h"
}

V1751Reader::V1751Reader(EXT_STR_h101_fatimavme_onion_t* input,
                         std::size_t offset, std::uint16_t procid)
    : c4Reader("V1751Reader"), fInput(input), fOffset(offset), fProcId(procid) {}

V1751Reader::~V1751Reader() { delete fOutput; }

Bool_t V1751Reader::Init(ext_data_struct_info* info) {
    if (!info || !fInput || !FairRootManager::Instance()) return kFALSE;
    Int_t ok = 0;
    EXT_STR_h101_fatimavme_ITEMS_INFO(ok, *info, fOffset, EXT_STR_h101_fatimavme, 0);
    if (!ok) {
        c4LOG(error, "V1751Reader: cannot register UCESB FATIMA VME bank");
        return kFALSE;
    }
    // Do not clear fInput: V1290Reader shares the same UCESB subevent.
    fOutput = new TClonesArray("V1751RawData");
    FairRootManager::Instance()->Register("V1751RawData", "VmeRawData", fOutput, !fOnline);
    return kTRUE;
}

Bool_t V1751Reader::Read() {
    if (!fInput || !fOutput) return kFALSE;
    const auto wr = c4::vme::Timestamp(fInput->fatimavme_ts_t);
    const auto subsystem = fInput->fatimavme_ts_subsystem_id;
    for (std::size_t slot = 0; slot < 5; ++slot) {
        c4::vme::DecodeV1751(fInput->fatimavme_qdc[slot], slot,
            [this, wr, subsystem](std::size_t slot, int board,
                                  std::uint32_t channel, std::uint32_t packed,
                                  const auto& bank) {
                auto* hit = static_cast<V1751RawData*>(
                    fOutput->ConstructedAt(fOutput->GetEntriesFast()));
                hit->procid = fProcId;
                hit->board_slot = static_cast<std::uint16_t>(slot);
                hit->board_id = board;
                hit->channel = static_cast<std::uint16_t>(channel);
                hit->wr_timestamp = wr;
                hit->wr_subsystem = subsystem;
                hit->coarse = bank._channel_timev[packed];
                hit->extended = bank._chan_ext_timev[packed];
                hit->fine = bank._chan_fine_timev[packed];
                hit->qlong = bank._qlongv[packed];
                hit->qshort = bank._qshortv[packed];
                hit->sazc = packed < bank._chan_sazc ? bank._chan_sazcv[packed] : 0;
                hit->sbzc = packed < bank._chan_sbzc ? bank._chan_sbzcv[packed] : 0;
                hit->midscale = packed < bank._chan_midscale ?
                    bank._chan_midscalev[packed] : 0;
                hit->waveform = c4::vme::Waveform(bank, packed);
            });
    }
    return kTRUE;
}

void V1751Reader::Reset() {
    if (fOutput) fOutput->Clear("C");
}
ClassImp(V1751Reader)
