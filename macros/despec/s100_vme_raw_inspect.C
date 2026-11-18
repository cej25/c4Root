#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <iostream>
#include <cstdint>
#include "../../c4data/fatimaData/VmeDigitiserRawData.h"

// Count new electronics records and check hardware metadata.
// This does NOT establish equality to the legacy FATIMA VME output yet.
void s100_vme_raw_inspect(TString filename = "s100_vme_raw_validation.root") {
    TFile file(filename, "READ");
    if (file.IsZombie()) {
        std::cerr << "Cannot open " << filename << '\n';
        return;
    }
    TTree* tree = nullptr;
    file.GetObject("evt", tree);
    if (!tree) {
        std::cerr << "Expected FairRoot evt tree missing.\n";
        return;
    }
    if (!tree->GetBranch("V1751RawData") ||
        !tree->GetBranch("V1290RawData")) {
        std::cerr << "Expected V1751RawData and V1290RawData branches missing.\n";
        return;
    }
    TClonesArray* qdc = nullptr;
    TClonesArray* tdc = nullptr;
    tree->SetBranchAddress("V1751RawData", &qdc);
    tree->SetBranchAddress("V1290RawData", &tdc);
    std::uint64_t qdc_count = 0, tdc_count = 0, invalid = 0;
    std::uint64_t events_both = 0;
    for (Long64_t entry = 0; entry < tree->GetEntries(); ++entry) {
        tree->GetEntry(entry);
        if (!qdc || !tdc) {
            ++invalid;
            continue;
        }
        if (qdc->GetEntriesFast() && tdc->GetEntriesFast()) ++events_both;
        for (int i = 0; i < qdc->GetEntriesFast(); ++i) {
            const auto* hit = static_cast<V1751RawData*>(qdc->At(i));
            ++qdc_count;
            if (hit->procid != 70 || hit->wr_subsystem != 0x1500 ||
                hit->board_slot >= 5 || hit->channel >= 8) ++invalid;
        }
        for (int i = 0; i < tdc->GetEntriesFast(); ++i) {
            const auto* hit = static_cast<V1290RawData*>(tdc->At(i));
            ++tdc_count;
            if (hit->procid != 70 || hit->wr_subsystem != 0x1500 ||
                hit->board_slot >= 2) ++invalid;
        }
    }
    std::cout << "Events: " << tree->GetEntries()
              << "\nV1751 records: " << qdc_count
              << "\nV1290 records: " << tdc_count
              << "\nEvents with both: " << events_both
              << "\nInvalid metadata: " << invalid << '\n';
}
