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
#include "s100_tamex_experiment_config.h"

extern "C"
{
#include "ext_data_client.h"
#include "ext_h101_unpack.h"
#include "ext_h101_fatima.h"
#include "ext_h101_bplast.h"
#include "ext_h101_bgo.h"
}

// Electronics-only smoke test: one event-level TamexRawData branch from
// three independent UCESB input structures. No detector calibration is run.
void s100_tamex_combined_validation(
    TString input_file = "",
    TString c4root_path = ".",
    Int_t max_events = 200000)
{
    if (input_file.IsNull())
    {
        std::cerr << "Supply an s100 .lmd input file.\n";
        return;
    }

    const TString config = c4root_path + "/config/s100/experiment.yaml";
    std::uint16_t fatima_procid = 0, fatima_wr = 0;
    std::uint16_t bplast_procid = 0, bplast_wr = 0;
    std::uint16_t bgo_procid = 0, bgo_wr = 0;

    if (!s100_config::LoadTamexConfig(config, "FATIMA", fatima_procid, fatima_wr) ||
        !s100_config::LoadTamexConfig(config, "bPlast", bplast_procid, bplast_wr) ||
        !s100_config::LoadTamexConfig(config, "BGO", bgo_procid, bgo_wr))
        return;

    // These WR subsystem IDs are currently compiled into s100.spec.
    if (fatima_procid != 75 || bplast_procid != 80 || bgo_procid != 100 ||
        fatima_wr != 0x1600 || bplast_wr != 0x500 || bgo_wr != 0x1900)
    {
        std::cerr << "experiment.yaml differs from the current compiled s100 UCESB routing.\n";
        return;
    }

    struct EXT_STR_h101
    {
        EXT_STR_h101_unpack_t eventheaders;
        EXT_STR_h101_fatima_onion_t fatima;
        EXT_STR_h101_bplast_onion_t bplast;
        EXT_STR_h101_bgo_onion_t bgo;
    };

    auto* unpacked = new EXT_STR_h101{};
    auto* run = new FairRunOnline();
    run->SetEventHeader(new EventHeader());
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink("s100_tamex_combined_validation.root"));

    TString ucesb_path = c4root_path + "/unpack/exps/s100/s100";
    ucesb_path += " --input-buffer=200Mi --event-sizes --allow-errors";
    auto* source = new UcesbSource(input_file, "UNPACK", ucesb_path,
                                  unpacked, sizeof(*unpacked));
    source->SetMaxEvents(max_events);
    run->SetSource(source);

    source->AddReader(new UnpackReader(
        &unpacked->eventheaders, offsetof(EXT_STR_h101, eventheaders)));
    auto add_reader = [source](TamexReader* reader) {
        reader->SetOnline(false);
        source->AddReader(reader);
    };
    add_reader(new TamexReader(&unpacked->fatima, offsetof(EXT_STR_h101, fatima),
                               fatima_procid, "FATIMA"));
    add_reader(new TamexReader(&unpacked->bplast, offsetof(EXT_STR_h101, bplast),
                               bplast_procid, "bPlast"));
    add_reader(new TamexReader(&unpacked->bgo, offsetof(EXT_STR_h101, bgo),
                               bgo_procid, "BGO"));

    run->Init();
    run->Run((max_events < 0) ? max_events : 0,
             (max_events < 0) ? 0 : max_events);
    std::cout << "Combined raw-data output: s100_tamex_combined_validation.root\n"
              << "Inspect it with s100_tamex_combined_inspect.C.\n";
}
