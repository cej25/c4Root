#include "FatimaVmeCalibrator.h"
#include "FatimaVmeCalData.h"
#include "FatimaRawData.h"
#include "TFatimaVmeConfiguration.h"
#include "FairRootManager.h"
#include "c4Logger.h"
#include <cstdint>

FatimaVmeCalibrator::FatimaVmeCalibrator()
    : fQdcOutput(new TClonesArray("FatimaVmeQdcCalHit")),
      fTdcOutput(new TClonesArray("FatimaVmeTdcCalHit")) {}

FatimaVmeCalibrator::~FatimaVmeCalibrator() {
    delete fQdcOutput;
    delete fTdcOutput;
}

bool FatimaVmeCalibrator::Init(FairRootManager* manager, Bool_t persist,
                             const FatimaVmeChainRaw* chain) {
    if (!manager) {
        c4LOG(error, "FATIMA VME calibration: missing FairRootManager");
        return false;
    }
    fChain = chain;
    if (!fChain) {
        fQdcInput = dynamic_cast<TClonesArray*>(manager->GetObject("V1751RawData"));
        fTdcInput = dynamic_cast<TClonesArray*>(manager->GetObject("V1290RawData"));
        if (!fQdcInput || !fTdcInput) {
            c4LOG(error, "FATIMA VME calibration needs V1751RawData and V1290RawData");
            return false;
        }
    }
    const auto* config = TFatimaVmeConfiguration::GetInstance();
    fQdcMapping = config->QDCMapping();
    fTdcMapping = config->TDCMapping();
    fEnergyCoefficients = config->QDC_E_Calib();
    fQdcTimeOffsets = config->QDC_T_Calib();
    fTdcTimeOffsets = config->TDC_T_Calib();
    manager->Register("FatimaVmeQdcCalHit", "FatimaVmeCal", fQdcOutput, persist);
    manager->Register("FatimaVmeTdcCalHit", "FatimaVmeCal", fTdcOutput, persist);
    return true;
}

void FatimaVmeCalibrator::Process() {
    Clear();
    if (fChain) {
        for (const auto& raw : fChain->QDC) ProcessQdc(raw);
        for (const auto& raw : fChain->TDC) ProcessTdc(raw);
        return;
    }
    for (int i = 0; i < fQdcInput->GetEntriesFast(); ++i)
        ProcessQdc(*static_cast<const V1751RawData*>(fQdcInput->At(i)));
    for (int i = 0; i < fTdcInput->GetEntriesFast(); ++i)
        ProcessTdc(*static_cast<const V1290RawData*>(fTdcInput->At(i)));
}

void FatimaVmeCalibrator::ProcessQdc(const V1751RawData& raw) {
    const auto mapping = fQdcMapping.find({raw.board_id, raw.channel});
    if (mapping == fQdcMapping.end() || mapping->second < 0) return;
    const int detector = mapping->second;
    auto* hit = static_cast<FatimaVmeQdcCalHit*>(
        fQdcOutput->ConstructedAt(fQdcOutput->GetEntriesFast()));
    hit->wr_timestamp = raw.wr_timestamp;
    hit->detector_id = detector;
    hit->board_id = raw.board_id;
    hit->channel = raw.channel;
    hit->coarse_raw = raw.coarse;
    hit->fine_raw = raw.fine;
    hit->qlong_raw = raw.qlong;
    hit->qshort_raw = raw.qshort;
    const double fullTime = static_cast<double>(raw.coarse) +
        static_cast<double>(std::uint64_t(raw.extended) << 32) +
        static_cast<double>(raw.fine) / 1024.;
    hit->coarse_time = raw.coarse + fQdcTimeOffsets[detector];
    hit->fine_time = fullTime + fQdcTimeOffsets[detector];
    double energy = fEnergyCoefficients[detector][0];
    for (int j = 1; j < 5; ++j)
        energy = energy * raw.qlong + fEnergyCoefficients[detector][j];
    // Preserve the deterministic part of legacy calibration. Legacy
    // FatimaVmeRaw2Cal adds a random [0,1) dither per hit; a direct
    // energy comparison must account for that deliberately.
    hit->energy = energy;
}

void FatimaVmeCalibrator::ProcessTdc(const V1290RawData& raw) {
    const auto mapping = fTdcMapping.find({raw.geo, raw.channel});
    if (mapping == fTdcMapping.end() || mapping->second < 0) return;
    const int detector = mapping->second;
    auto* hit = static_cast<FatimaVmeTdcCalHit*>(
        fTdcOutput->ConstructedAt(fTdcOutput->GetEntriesFast()));
    hit->wr_timestamp = raw.wr_timestamp;
    hit->wr_subsystem = raw.wr_subsystem;
    hit->detector_id = detector;
    hit->geo = raw.geo;
    hit->channel = raw.channel;
    hit->measurement_raw = raw.measurement;
    hit->leading_or_trailing = raw.leading_or_trailing;
    hit->time = static_cast<double>(raw.measurement) + fTdcTimeOffsets[detector];
}

void FatimaVmeCalibrator::Clear() {
    fQdcOutput->Clear("C");
    fTdcOutput->Clear("C");
}
