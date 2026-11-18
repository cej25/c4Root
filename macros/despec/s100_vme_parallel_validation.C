#include <TString.h>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "FairRunOnline.h"
#include "FairRootFileSink.h"
#include "EventHeader.h"
#include "UcesbSource.h"
#include "UnpackReader.h"
#include "V1751Reader.h"
#include "V1290Reader.h"
#include "FatimaVmeReader.h"
#include "FatimaRaw2Cal.h"
#include "TFatimaVmeConfiguration.h"
#include "ExperimentReadoutConfig.h"

extern "C" {
#include "ext_data_client.h"
#include "ext_h101_unpack.h"
#include "ext_h101_fatimavme.h"
}

typedef struct EXT_STR_h101_t {
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatimavme_onion_t fatimavme;
} EXT_STR_h101;

// Validation of generic electronics against the original FATIMA VME reader.
// No calibrator: writes both raw electronics and legacy mapped records.
void s100_vme_parallel_validation(TString input_file = "",
                            TString c4root_path = ".",
                            Int_t max_events = 200000) {
    if (input_file.IsNull()) {
        std::cerr << "Provide an s100 LMD input file.\n";
        return;
    }
    std::uint16_t procid = 0;
    try {
        const auto model = c4::experiment::ReadoutConfig::LoadFile(
            std::string(c4root_path.Data()) + "/config/s100/readouts.yaml");
        const auto& path = model.Select("FATIMA", "vme");
        if (path.sources.size() != 1 ||
            path.sources[0].event_member != "fatimavme" ||
            path.sources[0].procid != 70 ||
            path.sources[0].whiterabbit != 0x1500)
            throw std::invalid_argument("FATIMA VME routing differs from s100.spec");
        bool qdc = false, tdc = false;
        for (const auto& module : path.sources[0].modules) {
            if (module.type == "caen_v1751" && module.role == "energy") qdc = true;
            if (module.type == "caen_v1290" && module.role == "timing") tdc = true;
        }
        if (!qdc || !tdc || path.sources[0].modules.size() != 2)
            throw std::invalid_argument("Expected V1751 energy and V1290 timing modules");
        procid = path.sources[0].procid;
    } catch (const std::exception& ex) {
        std::cerr << "Invalid readout selection: " << ex.what() << '\n';
        return;
    }

    const TString config_path = c4root_path + "/config/s100/fatima";
    TFatimaVmeConfiguration::SetDetectorMapFile(
        (config_path + "/Fatima_VME_allocation.txt").Data());
    TFatimaVmeConfiguration::Set_QDC_E_CalFile(
        (config_path + "/Fatima_QDC_Energy_Calibration.txt").Data());
    TFatimaVmeConfiguration::Set_QDC_T_CalFile(
        (config_path + "/Fatima_QDC_Time_Calibration.txt").Data());
    TFatimaVmeConfiguration::Set_TDC_T_CalFile(
        (config_path + "/Fatima_TDC_Time_Calibration.txt").Data());

    auto* run = new FairRunOnline();
    run->SetEventHeader(new EventHeader());
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink("s100_vme_parallel_validation.root"));
    auto* unpacked = new EXT_STR_h101{};
    TString ucesb_path = c4root_path + "/unpack/exps/s100/s100";
    ucesb_path += " --input-buffer=200Mi --event-sizes --allow-errors";
    auto* source = new UcesbSource(input_file, "UNPACK", ucesb_path,
                                  unpacked, sizeof(*unpacked));
    source->SetMaxEvents(max_events);
    run->SetSource(source);
    source->AddReader(new UnpackReader(
        &unpacked->eventheaders, offsetof(EXT_STR_h101, eventheaders)));

    auto* qdc = new V1751Reader(
        &unpacked->fatimavme, offsetof(EXT_STR_h101, fatimavme), procid);
    qdc->SetOnline(false);
    source->AddReader(qdc);

    auto* tdc = new V1290Reader(
        &unpacked->fatimavme, offsetof(EXT_STR_h101, fatimavme), procid);
    tdc->SetRegisterStructure(false); // qdc reader registers shared bank
    tdc->SetOnline(false);
    source->AddReader(tdc);

    // This must come after the generic reader that registers the shared bank.
    auto* legacy = new FatimaVmeReader(
        &unpacked->fatimavme, offsetof(EXT_STR_h101, fatimavme));
    legacy->SetSharedInput(kTRUE);
    legacy->SetOnline(false);
    source->AddReader(legacy);

    auto* calibrated = new FatimaRaw2Cal();
    calibrated->UseVmeRawInput();
    calibrated->SetOnline(false);
    run->AddTask(calibrated);

    run->Init();
    run->Run(max_events < 0 ? max_events : 0,
             max_events < 0 ? 0 : max_events);
    qdc->PrintDiagnostics(std::cout);
    std::cout << "Parallel FATIMA VME validation output: s100_vme_parallel_validation.root\n";
}
