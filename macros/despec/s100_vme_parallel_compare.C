#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
#include "../../c4data/fatimaData/VmeDigitiserRawData.h"
#include "../../c4data/fatimaData/FatimaVmeData.h"

// Compare legacy and generic records produced from the same UCESB event.
// Legacy records hold mapped detector IDs rather than hardware channels;
// compare measurement quantities and their within-event order instead.
void s100_vme_parallel_compare(
    TString filename = "s100_vme_parallel_validation.root",
    Long64_t max_events = -1,
    unsigned max_examples = 12)
{
    TFile file(filename, "READ");
    if (file.IsZombie()) {
        std::cerr << "Cannot open " << filename << '\n';
        return;
    }
    TTree* tree = nullptr;
    file.GetObject("evt", tree);
    if (!tree) {
        std::cerr << "Missing evt tree\n";
        return;
    }
    const char* branches[] = {
        "V1751RawData", "V1290RawData", "FatimaVmeQDCData", "FatimaVmeTDCData"
    };
    for (auto name : branches) {
        if (!tree->GetBranch(name)) {
            std::cerr << "Missing branch: " << name << '\n';
            return;
        }
    }
    TClonesArray* qdc = nullptr;
    TClonesArray* tdc = nullptr;
    std::vector<FatimaVmeQDCItem>* old_qdc = nullptr;
    std::vector<FatimaVmeTDCItem>* old_tdc = nullptr;
    if (tree->SetBranchAddress("V1751RawData", &qdc) < 0 ||
        tree->SetBranchAddress("V1290RawData", &tdc) < 0 ||
        tree->SetBranchAddress("FatimaVmeQDCData", &old_qdc) < 0 ||
        tree->SetBranchAddress("FatimaVmeTDCData", &old_tdc) < 0) {
        std::cerr << "Failed to bind one or more ROOT branches\n";
        return;
    }

    std::uint64_t qdc_new_count = 0, qdc_old_count = 0;
    std::uint64_t tdc_new_count = 0, tdc_old_count = 0;
    std::uint64_t qdc_count_mismatch = 0, tdc_count_mismatch = 0;
    std::uint64_t qdc_value_mismatch = 0, tdc_value_mismatch = 0;
    std::uint64_t qdc_waveform_mismatch = 0;
    unsigned examples = 0;
    const auto n = max_events < 0 ? tree->GetEntries()
                                  : std::min(max_events, tree->GetEntries());
    for (Long64_t event = 0; event < n; ++event) {
        tree->GetEntry(event);
        if (!qdc || !tdc || !old_qdc || !old_tdc) {
            std::cerr << "Null data branch at event " << event << '\n';
            return;
        }
        const auto nq = static_cast<std::size_t>(qdc->GetEntriesFast());
        const auto nt = static_cast<std::size_t>(tdc->GetEntriesFast());
        qdc_new_count += nq;
        qdc_old_count += old_qdc->size();
        tdc_new_count += nt;
        tdc_old_count += old_tdc->size();
        if (nq != old_qdc->size()) {
            ++qdc_count_mismatch;
            if (examples++ < max_examples)
                std::cout << "QDC count mismatch event=" << event
                          << " new=" << nq << " legacy=" << old_qdc->size() << '\n';
        }
        if (nt != old_tdc->size()) {
            ++tdc_count_mismatch;
            if (examples++ < max_examples)
                std::cout << "TDC count mismatch event=" << event
                          << " new=" << nt << " legacy=" << old_tdc->size() << '\n';
        }
        for (std::size_t i = 0; i < std::min(nq, old_qdc->size()); ++i) {
            const auto* raw = static_cast<const V1751RawData*>(qdc->At(i));
            const auto& old = old_qdc->at(i);
            const double reconstructed_time =
                double(raw->coarse) + double(std::uint64_t(raw->extended) << 32)
                + double(raw->fine) / 1024.;
            if (raw->wr_timestamp != old.Get_wr_t() ||
                raw->coarse != old.Get_coarse_time() ||
                raw->fine != static_cast<std::uint32_t>(old.Get_fine_bin()) ||
                raw->qlong != old.Get_qlong_raw() ||
                raw->qshort != old.Get_qshort_raw() ||
                std::abs(reconstructed_time - old.Get_fine_time()) > 1e-5) {
                ++qdc_value_mismatch;
                if (examples++ < max_examples)
                    std::cout << "QDC value mismatch event=" << event
                              << " hit=" << i << " board=" << raw->board_id
                              << " channel=" << raw->channel << '\n';
            }
            const auto legacy_waveform = old.Get_waveform_one();
            if (raw->waveform.size() != legacy_waveform.size() ||
                !std::equal(raw->waveform.begin(), raw->waveform.end(),
                            legacy_waveform.begin(), legacy_waveform.end())) {
                ++qdc_waveform_mismatch;
                if (examples++ < max_examples)
                    std::cout << "QDC waveform mismatch event=" << event
                              << " hit=" << i << '\n';
            }
        }
        for (std::size_t i = 0; i < std::min(nt, old_tdc->size()); ++i) {
            const auto* raw = static_cast<const V1290RawData*>(tdc->At(i));
            const auto& old = old_tdc->at(i);
            if (raw->wr_timestamp != old.Get_wr_t() ||
                raw->wr_subsystem != old.Get_wr_subsystem_id() ||
                raw->measurement != old.Get_v1290_tdc_data() ||
                raw->leading_or_trailing != old.Get_leadOrTrail()) {
                ++tdc_value_mismatch;
                if (examples++ < max_examples)
                    std::cout << "TDC value mismatch event=" << event
                              << " hit=" << i << " geo=" << raw->geo
                              << " channel=" << raw->channel << '\n';
            }
        }
    }
    std::cout << "Parallel comparison of " << n << " events\n"
              << "QDC new/legacy: " << qdc_new_count << " / " << qdc_old_count << '\n'
              << "TDC new/legacy: " << tdc_new_count << " / " << tdc_old_count << '\n'
              << "QDC events with count mismatch: " << qdc_count_mismatch << '\n'
              << "TDC events with count mismatch: " << tdc_count_mismatch << '\n'
              << "QDC values mismatched: " << qdc_value_mismatch << '\n'
              << "TDC values mismatched: " << tdc_value_mismatch << '\n'
              << "QDC waveforms mismatched: " << qdc_waveform_mismatch << '\n';
    if (!qdc_count_mismatch && !tdc_count_mismatch &&
        !qdc_value_mismatch && !tdc_value_mismatch && !qdc_waveform_mismatch)
        std::cout << "PASS: legacy and generic measurements agree.\n";
    else
        std::cout << "FAIL: differences detected; inspect examples above.\n";
}
