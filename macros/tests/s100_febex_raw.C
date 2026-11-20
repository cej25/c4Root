#include "FairRootFileSink.h"
#include "FairRunOnline.h"
#include "FebexReader.h"
#include "GermaniumRaw2Cal.h"
#include "GermaniumReader.h"
#include "TGermaniumConfiguration.h"
#include "UcesbSource.h"
#include "UnpackReader.h"
#include "ext_h101_febex.h"
#include "ext_h101_unpack.h"

#include <cstddef>
#include <stdexcept>

R__LOAD_LIBRARY(libc4source)

struct EXT_STR_h101_t
{
    EXT_STR_h101_unpack header;
    EXT_STR_h101_germanium_onion germanium;
    EXT_STR_h101_febex_onion febex;
};

void s100_febex_raw(const char* input = "../calum.lmd",
                    const char* output = "s100_febex_raw_25k.root", int events = 25000)
{
    if (events < 1) throw std::invalid_argument("The replay needs a positive event limit");
    static EXT_STR_h101_t data{};

    TGermaniumConfiguration::SetDetectorConfigurationFile("config/s100/germanium/ge_alloc_apr15.txt");
    TGermaniumConfiguration::SetDetectorCoefficientFile("config/s100/germanium/ge_calib_0904.txt");

    auto* run = new FairRunOnline();
    run->SetEventHeader(new EventHeader());
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(output));

    auto* source = new UcesbSource(input, "UNPACK,RAW", "./unpack/exps/s100/s100 --input-buffer=200Mi",
                                   &data, sizeof(data));
    source->SetMaxEvents(events);
    source->AddReader(new UnpackReader(&data.header, offsetof(EXT_STR_h101_t, header)));
    source->AddReader(new GermaniumReader(&data.germanium, offsetof(EXT_STR_h101_t, germanium)));
    source->AddReader(new FebexReader(&data.febex, offsetof(EXT_STR_h101_t, febex), 60, "DEGAS"));
    run->SetSource(source);

    run->AddTask(new GermaniumRaw2Cal());
    run->Init();
    run->Run(0, events);
}
