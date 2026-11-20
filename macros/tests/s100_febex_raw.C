#include "DegasRawData.h"
#include "DegasRaw2Cal.h"
#include "DegasReader.h"
#include "FairRootFileSink.h"
#include "FairRunOnline.h"
#include "FebexReader.h"
#include "GermaniumCalData.h"
#include "GermaniumRaw2Cal.h"
#include "GermaniumReader.h"
#include "TGermaniumConfiguration.h"
#include "TimeMachineData.h"
#include "UcesbSource.h"
#include "UnpackReader.h"
#include "ext_h101_febex.h"
#include "ext_h101_unpack.h"
#include "../../unpack/exps/s100/s100_febex_banks.gen.hh"

#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>

R__LOAD_LIBRARY(libc4source)

struct EXT_STR_h101_t
{
    EXT_STR_h101_unpack header;
    EXT_STR_h101_germanium_onion germanium;
    std::array<EXT_STR_h101_febex_onion, s100FebexBanks.size()> febex;
};

namespace
{
bool SameBoard(const FebexRawData& first, const FebexRawData& second)
{
    const auto boardFields = [](const FebexRawData& board) {
        return std::tie(board.detectorName, board.eventTicks, board.wrTimestamp, board.wrId,
                        board.procid, board.hitPattern, board.slot, board.sfp, board.card, board.trigger);
    };
    const auto hitFields = [](const FebexRawHit& hit) {
        return std::tie(hit.channelTicks, hit.energyWord, hit.channel, hit.cfd, hit.pileup, hit.overflow);
    };
    return boardFields(first) == boardFields(second) &&
           std::equal(first.hits.begin(), first.hits.end(), second.hits.begin(), second.hits.end(),
                      [&](const FebexRawHit& a, const FebexRawHit& b) {
                          return hitFields(a) == hitFields(b);
                      });
}

auto CalFields(const GermaniumCalData& hit)
{
    return std::make_tuple(hit.Get_trigger(), hit.Get_event_trigger_time(), hit.Get_pileup(),
                           hit.Get_overflow(), hit.Get_channel_trigger_time(), hit.Get_channel_energy(),
                           hit.Get_crystal_id(), hit.Get_detector_id(), hit.Get_wr_subsystem_id(),
                           hit.Get_wr_t(), hit.Get_absolute_event_time());
}

auto TimeMachineFields(const TimeMachineData& hit)
{
    return std::make_tuple(hit.Get_undelayed_time(), hit.Get_delayed_time(),
                           hit.Get_wr_subsystem_id(), hit.Get_wr_t());
}

template <typename Hit, typename Fields>
void CheckCalibrated(const TClonesArray& reference, const TClonesArray& candidate,
                     Long64_t entry, const char* branch, Fields fields)
{
    if (reference.GetEntriesFast() != candidate.GetEntriesFast())
        throw std::runtime_error(std::string(branch) + " count mismatch at entry " + std::to_string(entry));
    for (int i = 0; i < reference.GetEntriesFast(); ++i)
    {
        const auto& first = *static_cast<const Hit*>(reference.At(i));
        const auto& second = *static_cast<const Hit*>(candidate.At(i));
        if (fields(first) != fields(second))
            throw std::runtime_error(std::string(branch) + " value mismatch at entry " +
                                     std::to_string(entry) + ", hit " + std::to_string(i));
    }
}

void CheckDegasRaw(const char* output, int events, std::uint16_t procid)
{
    TFile file(output, "READ");
    auto* tree = file.Get<TTree>("evt");
    if (!tree) tree = file.Get<TTree>("cbmsim");
    if (!tree || !tree->GetBranch("GermaniumCalData"))
        throw std::runtime_error("Missing event tree or GermaniumCalData");
    if (tree->GetEntries() != events)
        throw std::runtime_error("Event count differs from the requested replay");

    TClonesArray* shared = nullptr;
    TClonesArray* germaniumCal = nullptr;
    TClonesArray* degasCal = nullptr;
    TClonesArray* germaniumTiming = nullptr;
    TClonesArray* degasTiming = nullptr;
    DegasRawData* degas = nullptr;
    const char* degasBranch = tree->GetBranch("DegasRawData") ? "DegasRawData" : "DegasRawData.";
    if (tree->SetBranchAddress("FebexRawData", &shared) < 0 ||
        tree->SetBranchAddress(degasBranch, &degas) < 0 ||
        tree->SetBranchAddress("GermaniumCalData", &germaniumCal) < 0 ||
        tree->SetBranchAddress("DegasCalData", &degasCal) < 0 ||
        tree->SetBranchAddress("GermaniumTimeMachineData", &germaniumTiming) < 0 ||
        tree->SetBranchAddress("DegasTimeMachineData", &degasTiming) < 0)
        throw std::runtime_error("Could not bind the raw and calibrated comparison branches");

    std::size_t boards = 0, hits = 0, calibrated = 0, timing = 0;
    for (Long64_t entry = 0; entry < tree->GetEntries(); ++entry)
    {
        if (tree->GetEntry(entry) <= 0 || !degas || !shared ||
            !germaniumCal || !degasCal || !germaniumTiming || !degasTiming)
            throw std::runtime_error("Could not read entry " + std::to_string(entry));

        std::size_t slot = 0;
        for (int i = 0; i < shared->GetEntriesFast(); ++i)
        {
            const auto& reference = *static_cast<const FebexRawData*>(shared->At(i));
            if (reference.procid != procid) continue;
            if (slot >= degas->FEBEX.size() || !SameBoard(reference, degas->FEBEX[slot++]))
                throw std::runtime_error("DEGAS board or hit mismatch at entry " + std::to_string(entry));
            ++boards;
            hits += reference.hits.size();
        }
        if (slot != degas->FEBEX.size())
            throw std::runtime_error("Extra DEGAS board data at entry " + std::to_string(entry));

        CheckCalibrated<GermaniumCalData>(*germaniumCal, *degasCal, entry, "DegasCalData", CalFields);
        CheckCalibrated<TimeMachineData>(*germaniumTiming, *degasTiming, entry,
                                        "DegasTimeMachineData", TimeMachineFields);
        calibrated += degasCal->GetEntriesFast();
        timing += degasTiming->GetEntriesFast();
    }
    if (!hits || !calibrated) throw std::runtime_error("No DEGAS raw or calibrated hits compared");
    std::cout << "PASS: DegasRawData matches FebexRawData across " << tree->GetEntries()
              << " events, " << boards << " boards and " << hits << " hits.\n";
    std::cout << "PASS: DEGAS matches Germanium across " << calibrated << " calibrated hits and "
              << timing << " Time Machine records.\n";
}
}

void s100_febex_raw(const char* input = "../calum.lmd",
                    const char* output = "s100_febex_raw_25k.root", int events = 25000,
                    bool checkOnly = false)
{
    if (events < 1) throw std::invalid_argument("The replay needs a positive event limit");
    const auto degas = std::find_if(s100FebexBanks.begin(), s100FebexBanks.end(), [](const auto& bank) {
        return std::string_view(bank.detector) == "DEGAS";
    });
    if (degas == s100FebexBanks.end())
        throw std::runtime_error("The S100 setup needs a DEGAS FEBEX bank for this replay");
    if (checkOnly)
    {
        CheckDegasRaw(output, events, degas->procid);
        return;
    }
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
    for (std::size_t i = 0; i < s100FebexBanks.size(); ++i)
    {
        const auto& bank = s100FebexBanks[i];
        const auto offset = offsetof(EXT_STR_h101_t, febex) + i * sizeof(data.febex[i]);
        source->AddReader(new FebexReader(&data.febex[i], offset, bank.procid, bank.detector, bank.name));
    }
    const auto degasIndex = static_cast<std::size_t>(degas - s100FebexBanks.begin());
    const auto degasOffset = offsetof(EXT_STR_h101_t, febex) + degasIndex * sizeof(data.febex[degasIndex]);
    source->AddReader(new DegasReader(&data.febex[degasIndex], degasOffset, degas->procid, degas->name,
                                       DegasReader::BankAccess::AlreadyRegistered));
    run->SetSource(source);

    run->AddTask(new GermaniumRaw2Cal());
    run->AddTask(new DegasRaw2Cal());
    run->Init();
    run->Run(0, events);
}
