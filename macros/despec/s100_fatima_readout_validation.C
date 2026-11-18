#include <TROOT.h>
#include <TString.h>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

#include "FairRunOnline.h"
#include "FairRootFileSink.h"
#include "EventHeader.h"
#include "UcesbSource.h"
#include "UnpackReader.h"
#include "TamexReader.h"
#include "FatimaRaw2Cal.h"
#include "FatimaVmeReader.h"
#include "FatimaVmeRaw2Cal.h"
#include "TFatimaTwinpeaksConfiguration.h"
#include "TFatimaVmeConfiguration.h"
#include "ExperimentReadoutConfig.h"

extern "C"
{
#include "ext_data_client.h"
#include "ext_h101_unpack.h"
#include "ext_h101_fatima.h"
#include "ext_h101_fatimavme.h"
}

// The event layout stays compatible with UcesbSource's global EXT_STR_h101_t.
// Both UCESB banks exist even when only one analysis path is requested.
typedef struct EXT_STR_h101_t
{
    EXT_STR_h101_unpack_t eventheaders;
    EXT_STR_h101_fatima_onion_t fatima;
    EXT_STR_h101_fatimavme_onion_t fatimavme;
} EXT_STR_h101;

// First experiment-level readout-selection demonstration.
// Existing processing algorithms and ROOT output classes are preserved.
// "tamex" -> generic TamexReader + existing FATIMA TAMEX calibration
// "vme"   -> legacy VME reader + existing QDC/TDC calibration
// "all"   -> both independent calibrated outputs (no implicit merging)
void s100_fatima_readout_validation(
    TString input_file = "",
    TString c4root_path = ".",
    TString readout_selection = "tamex",
    Int_t max_events = 200000)
{
    if (input_file.IsNull())
    {
        std::cerr << "Supply an s100 input .lmd file.\n";
        return;
    }

    const bool use_tamex = readout_selection == "tamex" || readout_selection == "all";
    const bool use_vme = readout_selection == "vme" || readout_selection == "all";
    if (!use_tamex && !use_vme)
    {
        std::cerr << "Unsupported FATIMA readout: " << readout_selection
                  << " (choose tamex, vme or all)\n";
        return;
    }

    std::uint16_t tamex_procid = 0;
    try
    {
        const auto model = c4::experiment::ReadoutConfig::LoadFile(
            std::string(c4root_path.Data()) + "/config/s100/readouts.yaml");

        if (use_tamex)
        {
            const auto& path = model.Select("FATIMA", "tamex");
            if (path.sources.size() != 1 || path.sources[0].event_member != "fatima" ||
                path.sources[0].modules.size() != 1 ||
                path.sources[0].modules[0].type != "tamex" ||
                path.sources[0].modules[0].version != 4)
                throw std::invalid_argument("FATIMA/tamex requires the s100 TAMEX4 bank");
            tamex_procid = path.sources[0].procid;
            if (tamex_procid != 75 || path.sources[0].whiterabbit != 0x1600)
                throw std::invalid_argument(
                    "FATIMA/tamex routing differs from the compiled s100 UCESB unpacker");
        }

        if (use_vme)
        {
            const auto& path = model.Select("FATIMA", "vme");
            if (path.sources.size() != 1 || path.sources[0].event_member != "fatimavme" ||
                path.sources[0].modules.size() != 2)
                throw std::invalid_argument("FATIMA/vme requires the QDC/TDC readout bank");

            bool has_qdc = false, has_tdc = false;
            for (const auto& module : path.sources[0].modules)
            {
                if (module.type == "caen_v1751" && module.role == "energy")
                    has_qdc = true;
                else if (module.type == "caen_v1290" && module.role == "timing")
                    has_tdc = true;
                else
                    throw std::invalid_argument("Unrecognised FATIMA VME module or role");
            }
            if (!has_qdc || !has_tdc || path.sources[0].procid != 70 ||
                path.sources[0].whiterabbit != 0x1500)
                throw std::invalid_argument(
                    "FATIMA/vme module or routing mismatch with s100 UCESB unpacker");
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Readout configuration error: " << error.what() << '\n';
        return;
    }

    const TString config_path = c4root_path + "/config/s100";
    if (use_tamex)
    {
        TFatimaTwinpeaksConfiguration::SetDetectorConfigurationFile(
            (config_path + "/fatima/fatima_alloc_apr18.txt").Data());
        TFatimaTwinpeaksConfiguration::SetDetectorCoefficientFile(
            (config_path + "/fatima/fatima_cal_apr18.txt").Data());
        TFatimaTwinpeaksConfiguration::SetDetectorTimeshiftsFile(
            (config_path + "/fatima/fatima_timeshifts_apr20.txt").Data());
    }
    if (use_vme)
    {
        TFatimaVmeConfiguration::SetDetectorMapFile(
            (config_path + "/fatima/Fatima_VME_allocation.txt").Data());
        TFatimaVmeConfiguration::Set_QDC_E_CalFile(
            (config_path + "/fatima/Fatima_QDC_Energy_Calibration.txt").Data());
        TFatimaVmeConfiguration::Set_QDC_T_CalFile(
            (config_path + "/fatima/Fatima_QDC_Time_Calibration.txt").Data());
        TFatimaVmeConfiguration::Set_TDC_T_CalFile(
            (config_path + "/fatima/Fatima_TDC_Time_Calibration.txt").Data());
    }

    auto* run = new FairRunOnline();
    run->SetEventHeader(new EventHeader());
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(
        TString::Format("s100_fatima_%s_validation.root", readout_selection.Data())));

    // The source must outlive the FairRoot run.
    auto* unpacked = new EXT_STR_h101{};
    TString ucesb_path = c4root_path + "/unpack/exps/s100/s100";
    ucesb_path += " --input-buffer=200Mi --event-sizes --allow-errors";
    auto* source = new UcesbSource(input_file, "UNPACK", ucesb_path,
                                  unpacked, sizeof(*unpacked));
    source->SetMaxEvents(max_events);
    run->SetSource(source);

    auto* header = new UnpackReader(
        &unpacked->eventheaders, offsetof(EXT_STR_h101, eventheaders));
    header->SetOnline(false);
    source->AddReader(header);

    if (use_tamex)
    {
        auto* reader = new TamexReader(
            &unpacked->fatima, offsetof(EXT_STR_h101, fatima),
            tamex_procid, "FATIMA");
        reader->SetOnline(false);
        source->AddReader(reader);

        auto* calibrator = new FatimaRaw2Cal();
        calibrator->SetOnline(false);
        calibrator->UseTamexRawInput(
            tamex_procid, config_path + "/fatima/fine_time_4apr_test.root");
        run->AddTask(calibrator);
    }
    if (use_vme)
    {
        auto* reader = new FatimaVmeReader(
            &unpacked->fatimavme, offsetof(EXT_STR_h101, fatimavme));
        reader->SetOnline(false);
        source->AddReader(reader);

        auto* calibrator = new FatimaVmeRaw2Cal();
        calibrator->SetOnline(false);
        run->AddTask(calibrator);
    }

    std::cout << "FATIMA readouts selected: " << readout_selection << '\n';
    run->Init();
    run->Run(max_events < 0 ? max_events : 0,
             max_events < 0 ? 0 : max_events);
    std::cout << "FATIMA output: s100_fatima_" << readout_selection
              << "_validation.root\n";
}
