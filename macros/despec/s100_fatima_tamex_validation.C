#include <TROOT.h>
#include <TString.h>
#include <cstddef>
#include <cstdint>
#include <iostream>

#include "FairRunOnline.h"
#include "FairRootFileSink.h"
#include "EventHeader.h"
#include "UcesbSource.h"
#include "UnpackReader.h"
#include "TamexReader.h"
#include "FatimaReader.h"
#include "FatimaRaw2Cal.h"
#include "TFatimaTwinpeaksConfiguration.h"

extern "C"
{
#include "ext_h101_unpack.h"
#include "ext_h101_fatima.h"
}

// Based on macros/despec/old/s100_online_new.C, limited to FATIMA.
// Run twice on the same input for physics comparison (legacy and TAMEX).
// Automatic mode learns from the first calibration_events, then outputs hits.
typedef struct EXT_STR_h101_t
{
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatima_onion_t fatima;
} EXT_STR_h101;

void s100_fatima_tamex_validation(
    TString input_file = "",
    TString c4root_path = ".",
    bool use_tamex = true,
    bool automatic_calibration = false,
    Int_t max_events = 200000,
    std::uint64_t calibration_events = 50000)
{
    if (input_file.IsNull())
    {
        std::cerr << "Supply an s100 .lmd input file as the first argument." << std::endl;
        return;
    }
    if (automatic_calibration && !use_tamex)
    {
        std::cerr << "Automatic calibration in this macro requires use_tamex=true." << std::endl;
        return;
    }
    if (automatic_calibration && calibration_events == 0)
    {
        std::cerr << "calibration_events must be nonzero." << std::endl;
        return;
    }
    if (automatic_calibration && max_events >= 0 &&
        calibration_events >= static_cast<std::uint64_t>(max_events))
    {
        std::cerr << "Calibration will consume all input events: increase max_events." << std::endl;
        return;
    }

    const TString config_path = c4root_path + "/config/s100";
    const TString calibration_file =
        config_path + "/fatima/fine_time_4apr_test.root";
    const TString output_file = use_tamex
        ? "s100_fatima_tamex_validation.root"
        : "s100_fatima_legacy_validation.root";
    const TString fine_time_output = "s100_fatima_tamex_fine_time.root";

    TFatimaTwinpeaksConfiguration::SetDetectorConfigurationFile(
        config_path + "/fatima/fatima_alloc_apr18.txt");
    TFatimaTwinpeaksConfiguration::SetDetectorCoefficientFile(
        config_path + "/fatima/fatima_cal_apr18.txt");
    TFatimaTwinpeaksConfiguration::SetDetectorTimeshiftsFile(
        config_path + "/fatima/fatima_timeshifts_apr20.txt");

    auto* run = new FairRunOnline();
    run->SetEventHeader(new EventHeader());
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(output_file));

    EXT_STR_h101 ucesb_struct{};
    TString ucesb_path = c4root_path + "/unpack/exps/s100/s100";
    ucesb_path += " --input-buffer=200Mi --event-sizes --allow-errors";
    auto* source = new UcesbSource(
        input_file, "UNPACK", ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
    source->SetMaxEvents(max_events);
    run->SetSource(source);

    source->AddReader(new UnpackReader(
        (EXT_STR_h101_unpack*)&ucesb_struct.eventheaders,
        offsetof(EXT_STR_h101, eventheaders)));

    constexpr std::uint16_t fatima_source = 10;
    if (use_tamex)
    {
        auto* reader = new TamexReader(
            (EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima,
            offsetof(EXT_STR_h101, fatima), fatima_source);
        reader->SetOnline(false);
        source->AddReader(reader);
    }
    else
    {
        auto* reader = new FatimaReader(
            (EXT_STR_h101_fatima_onion*)&ucesb_struct.fatima,
            offsetof(EXT_STR_h101, fatima));
        reader->SetInputFileFineTimeHistos(calibration_file);
        reader->SetOnline(false);
        source->AddReader(reader);
    }

    auto* calfatima = new FatimaRaw2Cal();
    calfatima->SetOnline(false);
    if (use_tamex)
    {
        if (automatic_calibration)
        {
            calfatima->UseTamexRawInput(fatima_source);
            calfatima->CalibrateTamexFineTimeOnline(
                fine_time_output, calibration_events);
        }
        else
        {
            calfatima->UseTamexRawInput(fatima_source, calibration_file);
        }
    }
    run->AddTask(calfatima);

    run->Init();
    run->Run((max_events < 0) ? max_events : 0,
             (max_events < 0) ? 0 : max_events);

    std::cout << "FATIMA validation output: " << output_file << std::endl;
    if (automatic_calibration)
        std::cout << "Fine-time histograms: " << fine_time_output << std::endl;
}
