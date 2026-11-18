#include <TFile.h>
#include <TTree.h>
#include <TClonesArray.h>
#include <TString.h>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

#include "../../c4data/fatimaData/VmeDigitiserRawData.h"
#include "../../c4data/fatimaData/FatimaVmeData.h"
#include "../../c4data/fatimaData/FatimaVmeElectronicsCalData.h"
#include "../../c4data/fatimaData/TFatimaVmeConfiguration.h"

// Inspect calibrated hits against the legacy mapped raw hits in the same
// file and against the calibration coefficients. No random dither is expected.
// This is deliberately independent of the old Raw2Cal fixed-array matching.
void s100_vme_cal_inspect(
    TString filename = "s100_vme_parallel_validation.root",
    TString c4root_path = ".",
    unsigned max_examples = 10)
{
    TString cfgdir = c4root_path + "/config/s100/fatima/";
    TFatimaVmeConfiguration::SetDetectorMapFile(
        (cfgdir + "Fatima_VME_allocation.txt").Data());
    TFatimaVmeConfiguration::Set_QDC_E_CalFile(
        (cfgdir + "Fatima_QDC_Energy_Calibration.txt").Data());
    TFatimaVmeConfiguration::Set_QDC_T_CalFile(
        (cfgdir + "Fatima_QDC_Time_Calibration.txt").Data());
    TFatimaVmeConfiguration::Set_TDC_T_CalFile(
        (cfgdir + "Fatima_TDC_Time_Calibration.txt").Data());
    const auto* cfg = TFatimaVmeConfiguration::GetInstance();
    const auto qdcMapping = cfg->QDCMapping();
    const auto tdcMapping = cfg->TDCMapping();
    auto** energyCoeffs = cfg->QDC_E_Calib();
    auto* qdcOffsets = cfg->QDC_T_Calib();
    auto* tdcOffsets = cfg->TDC_T_Calib();

    TFile file(filename, "READ");
    if (file.IsZombie()) { std::cerr << "Cannot open " << filename << '\n'; return; }
    TTree* tree = nullptr;
    file.GetObject("evt", tree);
    if (!tree) { std::cerr << "Missing evt tree\n"; return; }
    for (const char* branch : {"V1751RawData", "V1290RawData",
                               "FatimaVmeQdcCalHit", "FatimaVmeTdcCalHit",
                               "FatimaVmeQDCData", "FatimaVmeTDCData"}) {
        if (!tree->GetBranch(branch)) {
            std::cerr << "Missing branch: " << branch << '\n';
            return;
        }
    }
    TClonesArray* qdc = nullptr;
    TClonesArray* tdc = nullptr;
    TClonesArray* qdcCal = nullptr;
    TClonesArray* tdcCal = nullptr;
    std::vector<FatimaVmeQDCItem>* oldQdc = nullptr;
    std::vector<FatimaVmeTDCItem>* oldTdc = nullptr;
    if (tree->SetBranchAddress("V1751RawData", &qdc) < 0 ||
        tree->SetBranchAddress("V1290RawData", &tdc) < 0 ||
        tree->SetBranchAddress("FatimaVmeQdcCalHit", &qdcCal) < 0 ||
        tree->SetBranchAddress("FatimaVmeTdcCalHit", &tdcCal) < 0 ||
        tree->SetBranchAddress("FatimaVmeQDCData", &oldQdc) < 0 ||
        tree->SetBranchAddress("FatimaVmeTDCData", &oldTdc) < 0) {
        std::cerr << "Failed to bind input branches\n";
        return;
    }

    std::uint64_t rawQ = 0, rawT = 0, mappedQ = 0, mappedT = 0;
    std::uint64_t unmappedQ = 0, unmappedT = 0;
    std::uint64_t missingQ = 0, missingT = 0;
    std::uint64_t disabledQ = 0, disabledT = 0;
    std::uint64_t countErrors = 0, valueErrors = 0, mappingErrors = 0;
    unsigned examples = 0;
    auto report = [&](Long64_t event, const char* issue) {
        if (examples++ < max_examples)
            std::cout << "Mismatch event=" << event << ": " << issue << '\n';
    };
    for (Long64_t event = 0; event < tree->GetEntries(); ++event) {
        tree->GetEntry(event);
        if (!qdc || !tdc || !qdcCal || !tdcCal || !oldQdc || !oldTdc) {
            std::cerr << "Null collection at event " << event << '\n';
            return;
        }
        rawQ += qdc->GetEntriesFast();
        rawT += tdc->GetEntriesFast();
        mappedQ += qdcCal->GetEntriesFast();
        mappedT += tdcCal->GetEntriesFast();

        std::size_t missingEventQ = 0, missingEventT = 0;
        std::vector<const V1751RawData*> expectedQ;
        std::vector<const V1290RawData*> expectedT;
        for (int i = 0; i < qdc->GetEntriesFast(); ++i) {
            auto* raw = static_cast<const V1751RawData*>(qdc->At(i));
            auto it = qdcMapping.find({raw->board_id, raw->channel});
            if (it == qdcMapping.end()) {
                ++unmappedQ; ++missingQ; ++missingEventQ;
                if (examples++ < max_examples)
                    std::cout << "Unmapped QDC event=" << event
                              << " board=" << raw->board_id
                              << " channel=" << raw->channel << '\n';
            } else if (it->second < 0) {
                ++unmappedQ; ++disabledQ;
            } else expectedQ.push_back(raw);
        }
        for (int i = 0; i < tdc->GetEntriesFast(); ++i) {
            auto* raw = static_cast<const V1290RawData*>(tdc->At(i));
            auto it = tdcMapping.find({raw->geo, raw->channel});
            if (it == tdcMapping.end()) {
                ++unmappedT; ++missingT; ++missingEventT;
                if (examples++ < max_examples)
                    std::cout << "Unmapped TDC event=" << event
                              << " geo=" << raw->geo
                              << " channel=" << raw->channel
                              << " measurement=" << raw->measurement << '\n';
            } else if (it->second < 0) {
                ++unmappedT; ++disabledT;
            } else expectedT.push_back(raw);
        }
        if (expectedQ.size() != static_cast<std::size_t>(qdcCal->GetEntriesFast()) ||
            expectedT.size() != static_cast<std::size_t>(tdcCal->GetEntriesFast())) {
            ++countErrors;
            report(event, "calibrated multiplicity differs from mapped raw multiplicity");
        }
        std::size_t legacyQ = 0, legacyT = 0;
        for (const auto& hit : *oldQdc) if (hit.Get_detector() >= 0) ++legacyQ;
        for (const auto& hit : *oldTdc) if (hit.Get_detector() >= 0) ++legacyT;
        // The legacy reader used std::map::operator[] on an unknown
        // hardware key: this silently creates detector 0. Preserve this
        // behaviour only as an expected discrepancy in the comparator,
        // not in the modern calibration task.
        if (legacyQ != expectedQ.size() + missingEventQ ||
            legacyT != expectedT.size() + missingEventT) {
            ++mappingErrors;
            report(event, "legacy mapped multiplicity differs from new mapping");
        }
        for (std::size_t i = 0; i < std::min(expectedQ.size(),
                                    static_cast<std::size_t>(qdcCal->GetEntriesFast())); ++i) {
            auto* raw = expectedQ[i];
            auto* hit = static_cast<const FatimaVmeQdcCalHit*>(qdcCal->At(i));
            const int det = qdcMapping.at({raw->board_id, raw->channel});
            const double fullTime = static_cast<double>(raw->coarse) +
                static_cast<double>(std::uint64_t(raw->extended) << 32) +
                static_cast<double>(raw->fine) / 1024.;
            double energy = energyCoeffs[det][0];
            for (int k = 1; k < 5; ++k)
                energy = energy * raw->qlong + energyCoeffs[det][k];
            if (hit->detector_id != det || hit->board_id != raw->board_id ||
                hit->channel != raw->channel || hit->wr_timestamp != raw->wr_timestamp ||
                hit->qlong_raw != raw->qlong || hit->qshort_raw != raw->qshort ||
                hit->coarse_raw != raw->coarse || hit->fine_raw != raw->fine ||
                std::abs(hit->coarse_time - (raw->coarse + qdcOffsets[det])) > 1e-6 ||
                std::abs(hit->fine_time - (fullTime + qdcOffsets[det])) > 1e-5 ||
                !std::isfinite(hit->energy) ||
                std::abs(hit->energy - energy) > 1e-6) {
                ++valueErrors;
                report(event, "QDC calibration or mapping");
            }
        }
        for (std::size_t i = 0; i < std::min(expectedT.size(),
                                    static_cast<std::size_t>(tdcCal->GetEntriesFast())); ++i) {
            auto* raw = expectedT[i];
            auto* hit = static_cast<const FatimaVmeTdcCalHit*>(tdcCal->At(i));
            const int det = tdcMapping.at({raw->geo, raw->channel});
            if (hit->detector_id != det || hit->geo != raw->geo ||
                hit->channel != raw->channel || hit->wr_timestamp != raw->wr_timestamp ||
                hit->wr_subsystem != raw->wr_subsystem ||
                hit->measurement_raw != raw->measurement ||
                hit->leading_or_trailing != raw->leading_or_trailing ||
                std::abs(hit->time - (raw->measurement + tdcOffsets[det])) > 1e-6) {
                ++valueErrors;
                report(event, "TDC calibration or mapping");
            }
        }
    }
    std::cout << "Events: " << tree->GetEntries()
              << "\nRaw QDC/TDC: " << rawQ << " / " << rawT
              << "\nMapped calibrated QDC/TDC: " << mappedQ << " / " << mappedT
              << "\nUnmapped QDC/TDC: " << unmappedQ << " / " << unmappedT
              << "\nMissing hardware mappings QDC/TDC: " << missingQ << " / " << missingT
              << "\nExplicit negative mappings QDC/TDC: " << disabledQ << " / " << disabledT
              << "\nEvents with multiplicity mismatches: " << countErrors
              << "\nEvents with legacy mapping-count mismatches: " << mappingErrors
              << "\nCalibrated hit value mismatches: " << valueErrors << '\n';
    if (!countErrors && !mappingErrors && !valueErrors)
        std::cout << "PASS: new calibrated hits match mapping and coefficients.\n";
    else
        std::cout << "FAIL: calibrated validation mismatches detected.\n";
    if (missingQ || missingT)
        std::cout << "NOTE: legacy reader maps unknown hardware channels to detector 0; new calibration skips them.\n";
}
