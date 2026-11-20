#include "EventHeader.h"
#include "FairRootFileSink.h"
#include "FairRunOnline.h"
#include "FatimaEventReader.h"
#include "FatimaRawData.h"
#include "FatimaRaw2Cal.h"
#include "FatimaTwinpeaksCalData.h"
#include "FatimaVmeElectronicsCalData.h"
#include "FatimaVmeData.h"
#include "bPlastTwinpeaksCalData.h"
#include "TFatimaVmeConfiguration.h"
#include "TimeMachineData.h"
#include "TamexReader.h"
#include "UcesbSource.h"
#include "UnpackReader.h"
#include "V1290Reader.h"
#include "V1751Reader.h"
#include "ext_h101_fatima.h"
#include "ext_h101_fatimavme.h"
#include "ext_h101_unpack.h"
#include "../../unpack/exps/s100/s100_config.gen.spec"

#include <TClonesArray.h>
#include <TFile.h>
#include <TTree.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>

R__LOAD_LIBRARY(libc4source)

struct EXT_STR_h101_t
{
    EXT_STR_h101_unpack header;
    EXT_STR_h101_fatima_onion tamex;
    EXT_STR_h101_fatimavme_onion vme;
};

namespace
{
auto TamexWordFields(const TamexRawWord& word)
{
    return std::tie(word.kind, word.packed_index, word.epoch, word.channel, word.coarse, word.fine,
                    word.leading, word.flags);
}

bool SameTamexBoard(const TamexRawData& a, const TamexRawData& b)
{
    const auto metadata = [](const TamexRawData& board) {
        return std::make_tuple(board.ProcId(), board.DetectorName(), board.Board(), board.Trigger(),
                               board.WrSubsystem(), board.WrTimestamp(), board.FormatVersion());
    };
    return metadata(a) == metadata(b) &&
           std::equal(a.Words().begin(), a.Words().end(), b.Words().begin(), b.Words().end(),
                      [](const auto& x, const auto& y) { return TamexWordFields(x) == TamexWordFields(y); });
}

template <typename Record, typename Same>
std::size_t Compare(const TClonesArray& reference, const std::vector<Record>& actual,
                    const char* chain, Long64_t entry, Same same)
{
    if (static_cast<std::size_t>(reference.GetEntriesFast()) != actual.size())
        throw std::runtime_error(std::string(chain) + " count mismatch at entry " + std::to_string(entry));
    for (std::size_t i = 0; i < actual.size(); ++i)
    {
        if (!same(*static_cast<const Record*>(reference.At(i)), actual[i]))
            throw std::runtime_error(std::string(chain) + " data mismatch at entry " + std::to_string(entry));
    }
    return actual.size();
}

void CheckFatimaRaw(const char* output, int events)
{
    TFile file(output, "READ");
    auto* tree = file.Get<TTree>("evt");
    if (!tree) tree = file.Get<TTree>("cbmsim");
    if (!tree || tree->GetEntries() != events)
        throw std::runtime_error("Missing event tree or incorrect number of entries");

    FatimaRawData* fatima = nullptr;
    TClonesArray* tamex = nullptr;
    TClonesArray* qdc = nullptr;
    TClonesArray* tdc = nullptr;
    const char* branch = tree->GetBranch("FatimaRawData") ? "FatimaRawData" : "FatimaRawData.";
    if (tree->SetBranchAddress(branch, &fatima) < 0 ||
        tree->SetBranchAddress("TamexRawData", &tamex) < 0 ||
        tree->SetBranchAddress("V1751RawData", &qdc) < 0 ||
        tree->SetBranchAddress("V1290RawData", &tdc) < 0)
        throw std::runtime_error("Could not bind the FATIMA raw and reference branches");

    const auto qdcFields = [](const V1751RawData& hit) {
        return std::tie(hit.procid, hit.board_slot, hit.board_id, hit.channel, hit.wr_subsystem,
                        hit.wr_timestamp, hit.coarse, hit.extended, hit.fine, hit.qlong,
                        hit.qshort, hit.sazc, hit.sbzc, hit.midscale, hit.waveform);
    };
    const auto tdcFields = [](const V1290RawData& hit) {
        return std::tie(hit.procid, hit.board_slot, hit.geo, hit.channel, hit.wr_subsystem,
                        hit.wr_timestamp, hit.measurement, hit.leading_or_trailing);
    };
    std::size_t tamexBoards = 0, qdcHits = 0, tdcHits = 0, both = 0;
    for (Long64_t entry = 0; entry < tree->GetEntries(); ++entry)
    {
        if (tree->GetEntry(entry) <= 0 || !fatima || !tamex || !qdc || !tdc)
            throw std::runtime_error("Could not read FATIMA entry " + std::to_string(entry));
        const auto& t = fatima->TAMEX;
        const auto& v = fatima->VMEChain;
        tamexBoards += Compare(*tamex, t.boards, "TAMEX", entry, [&](const auto& a, const auto& b) {
            return b.WrSubsystem() == t.wrId && b.WrTimestamp() == t.wrTimestamp && SameTamexBoard(a, b);
        });
        qdcHits += Compare(*qdc, v.QDC, "V1751", entry, [&](const auto& a, const auto& b) {
            return b.wr_subsystem == v.wrId && b.wr_timestamp == v.wrTimestamp && qdcFields(a) == qdcFields(b);
        });
        tdcHits += Compare(*tdc, v.TDC, "V1290", entry, [&](const auto& a, const auto& b) {
            return b.wr_subsystem == v.wrId && b.wr_timestamp == v.wrTimestamp && tdcFields(a) == tdcFields(b);
        });
        both += !t.boards.empty() && (!v.QDC.empty() || !v.TDC.empty());
    }
    if (!tamexBoards || !qdcHits || !tdcHits)
        throw std::runtime_error("The replay did not exercise all three digitiser paths");
    std::cout << "PASS: FatimaRawData matches the three electronics readers across " << events
              << " events, " << tamexBoards << " TAMEX boards, " << qdcHits << " QDC hits and "
              << tdcHits << " TDC hits.\nEvents with board or hit data from both chains: " << both << '\n';
}
template <typename Hit, typename Fields>
std::size_t CompareCal(const TClonesArray& reference, const TClonesArray& actual,
                       const char* branch, Long64_t entry, Fields fields)
{
    const auto mismatch = [&]() {
        return std::runtime_error(std::string(branch) + " mismatch at entry " + std::to_string(entry));
    };
    if (reference.GetEntriesFast() != actual.GetEntriesFast()) throw mismatch();
    for (int i = 0; i < reference.GetEntriesFast(); ++i)
    {
        if (fields(*static_cast<const Hit*>(reference.At(i))) !=
            fields(*static_cast<const Hit*>(actual.At(i)))) throw mismatch();
    }
    return actual.GetEntriesFast();
}

auto FatimaCalFields(const FatimaTwinpeaksCalData& hit)
{
    return std::make_tuple(hit.Get_trigger(), hit.Get_board_id(), hit.Get_ch_ID(),
        hit.Get_detector_id(), hit.Get_slow_lead_epoch(), hit.Get_slow_lead_time(),
        hit.Get_slow_trail_epoch(), hit.Get_slow_trail_time(), hit.Get_fast_lead_epoch(),
        hit.Get_fast_lead_time(), hit.Get_fast_trail_epoch(), hit.Get_fast_trail_time(),
        hit.Get_fast_ToT(), hit.Get_slow_ToT(), hit.Get_energy(), hit.Get_wr_subsystem_id(),
        hit.Get_wr_t(), hit.Get_absolute_event_time());
}

void CheckFatimaCal(const char* reference, const char* output, int events)
{
    constexpr std::array<const char*, 4> branches{
        "FatimaTwinpeaksCalData", "FatimaVmeQdcCalHit", "FatimaVmeTdcCalHit", "FatimaTimeMachineData"
    };
    TFile files[]{TFile(reference, "READ"), TFile(output, "READ")};
    TTree* trees[2]{};
    EventHeader* headers[2]{};
    TClonesArray* hits[2][branches.size()]{};
    for (std::size_t file = 0; file < 2; ++file)
    {
        trees[file] = files[file].Get<TTree>("evt");
        if (!trees[file]) trees[file] = files[file].Get<TTree>("cbmsim");
        if (!trees[file] || trees[file]->GetEntries() != events ||
            trees[file]->SetBranchAddress("EventHeader.", &headers[file]) < 0)
            throw std::runtime_error("Missing event tree, event header or incorrect event count");
        for (std::size_t branch = 0; branch < branches.size(); ++branch)
            if (trees[file]->SetBranchAddress(branches[branch], &hits[file][branch]) < 0)
                throw std::runtime_error(std::string("Missing branch ") + branches[branch]);
    }

    std::array<std::size_t, branches.size()> totals{};
    for (Long64_t entry = 0; entry < events; ++entry)
    {
        if (trees[0]->GetEntry(entry) <= 0 || trees[1]->GetEntry(entry) <= 0 ||
            !headers[0] || !headers[1] ||
            headers[0]->GetEventno() != headers[1]->GetEventno() ||
            headers[0]->GetTrigger() != headers[1]->GetTrigger())
            throw std::runtime_error("Event header mismatch at entry " + std::to_string(entry));

        for (std::size_t branch = 0; branch < branches.size(); ++branch)
            if (!hits[0][branch] || !hits[1][branch])
                throw std::runtime_error(std::string("Could not read branch ") + branches[branch]);

        totals[0] += CompareCal<FatimaTwinpeaksCalData>(*hits[0][0], *hits[1][0], branches[0], entry,
            FatimaCalFields);
        totals[1] += CompareCal<FatimaVmeQdcCalHit>(*hits[0][1], *hits[1][1], branches[1], entry,
            [](const auto& hit) {
                return std::tie(hit.wr_timestamp, hit.detector_id, hit.board_id, hit.channel,
                    hit.coarse_raw, hit.fine_raw, hit.qlong_raw, hit.qshort_raw,
                    hit.coarse_time, hit.fine_time, hit.energy);
            });
        totals[2] += CompareCal<FatimaVmeTdcCalHit>(*hits[0][2], *hits[1][2], branches[2], entry,
            [](const auto& hit) {
                return std::tie(hit.wr_timestamp, hit.wr_subsystem, hit.detector_id, hit.geo,
                    hit.channel, hit.measurement_raw, hit.leading_or_trailing, hit.time);
            });
        totals[3] += CompareCal<TimeMachineData>(*hits[0][3], *hits[1][3], branches[3], entry,
            [](const auto& hit) {
                return std::make_tuple(hit.Get_undelayed_time(), hit.Get_delayed_time(),
                                       hit.Get_wr_subsystem_id(), hit.Get_wr_t());
            });
    }
    if (!totals[0] || !totals[1] || !totals[2])
        throw std::runtime_error("The replay did not produce calibrated hits on all three digitiser paths");
    for (std::size_t branch = 0; branch < branches.size(); ++branch)
        std::cout << branches[branch] << ": " << totals[branch] << " entries\n";
    std::cout << "PASS: FATIMA calibrated output agrees across " << events << " events.\n";
}
template <typename Record, typename Fields>
std::size_t CompareVector(const std::vector<Record>& reference, const std::vector<Record>& actual,
                          const char* branch, Long64_t entry, Fields fields)
{
    if (!std::equal(reference.begin(), reference.end(), actual.begin(), actual.end(),
                    [&](const auto& x, const auto& y) { return fields(x) == fields(y); }))
        throw std::runtime_error(std::string(branch) + " mismatch at entry " + std::to_string(entry));
    return actual.size();
}

struct S100AnalysisBranches
{
    S100AnalysisBranches(const char* path, int events) : file(path, "READ")
    {
        tree = file.Get<TTree>("evt");
        if (!tree) tree = file.Get<TTree>("cbmsim");
        if (!tree || tree->GetEntries() != events ||
            tree->SetBranchAddress("EventHeader.", &header) < 0 ||
            tree->SetBranchAddress("FatimaTwinpeaksCalData", &fatima) < 0 ||
            tree->SetBranchAddress("FatimaVmeQDCData", &qdc) < 0 ||
            tree->SetBranchAddress("FatimaVmeTDCData", &tdc) < 0 ||
            tree->SetBranchAddress("bPlastTwinpeaksCalData", &bplast) < 0 ||
            tree->SetBranchAddress("bPlastTimeMachineData", &bplastTimeMachine) < 0)
            throw std::runtime_error(std::string("Missing S100 analysis branch or incorrect event count in ") + path);
    }

    TFile file;
    TTree* tree = nullptr;
    EventHeader* header = nullptr;
    TClonesArray* fatima = nullptr;
    std::vector<FatimaVmeQDCItem>* qdc = nullptr;
    std::vector<FatimaVmeTDCItem>* tdc = nullptr;
    TClonesArray* bplast = nullptr;
    TClonesArray* bplastTimeMachine = nullptr;
};

void CheckS100Analysis(const char* reference, const char* output, int events)
{
    S100AnalysisBranches before(reference, events);
    S100AnalysisBranches after(output, events);
    std::size_t fatima = 0, qdc = 0, tdc = 0, bplast = 0, timeMachine = 0;
    for (Long64_t entry = 0; entry < events; ++entry)
    {
        for (auto* data : {&before, &after})
            if (data->tree->GetEntry(entry) <= 0 || !data->header || !data->fatima || !data->qdc ||
                !data->tdc || !data->bplast || !data->bplastTimeMachine)
                throw std::runtime_error("Could not read S100 event " + std::to_string(entry));

        if (before.header->GetEventno() != after.header->GetEventno() ||
            before.header->GetTrigger() != after.header->GetTrigger())
            throw std::runtime_error("S100 event header mismatch at entry " + std::to_string(entry));
        fatima += CompareCal<FatimaTwinpeaksCalData>(*before.fatima, *after.fatima,
            "FatimaTwinpeaksCalData", entry, FatimaCalFields);
        qdc += CompareVector(*before.qdc, *after.qdc, "FatimaVmeQDCData", entry, [](const auto& hit) {
            return std::make_tuple(hit.Get_wr_t(), hit.Get_detector(), hit.Get_coarse_time(),
                hit.Get_fine_time(), hit.Get_fine_bin(), hit.Get_qlong_raw(), hit.Get_qshort_raw(),
                hit.Get_waveform_one());
        });
        tdc += CompareVector(*before.tdc, *after.tdc, "FatimaVmeTDCData", entry, [](const auto& hit) {
            return std::make_tuple(hit.Get_wr_t(), hit.Get_wr_subsystem_id(), hit.Get_detector(),
                                   hit.Get_v1290_tdc_data(), hit.Get_leadOrTrail());
        });
        bplast += CompareCal<bPlastTwinpeaksCalData>(*before.bplast, *after.bplast,
            "bPlastTwinpeaksCalData", entry, [](const auto& hit) {
                return std::make_tuple(hit.Get_trigger(), hit.Get_board_id(), hit.Get_ch_ID(),
                    hit.Get_detector_id(), hit.Get_slow_lead_epoch(), hit.Get_slow_lead_time(),
                    hit.Get_slow_trail_epoch(), hit.Get_slow_trail_time(), hit.Get_fast_lead_epoch(),
                    hit.Get_fast_lead_time(), hit.Get_fast_trail_epoch(), hit.Get_fast_trail_time(),
                    hit.Get_fast_ToT(), hit.Get_slow_ToT(), hit.Get_wr_subsystem_id(),
                    hit.Get_wr_t(), hit.Get_absolute_event_time());
            });
        timeMachine += CompareCal<TimeMachineData>(*before.bplastTimeMachine, *after.bplastTimeMachine,
            "bPlastTimeMachineData", entry, [](const auto& hit) {
                return std::make_tuple(hit.Get_undelayed_time(), hit.Get_delayed_time(),
                                       hit.Get_wr_subsystem_id(), hit.Get_wr_t());
            });
    }
    if (!fatima || !qdc || !tdc || !bplast)
        throw std::runtime_error("The replay did not exercise FATIMA TAMEX, QDC, TDC and calibrated bPlast");
    std::cout << "PASS: " << events << " S100 events, " << fatima << " calibrated FATIMA TAMEX hits, "
              << qdc << " FATIMA QDC hits, " << tdc
              << " FATIMA TDC hits, " << bplast << " calibrated bPlast hits and "
              << timeMachine << " bPlast Time Machine entries match.\n";
}
}

void s100_fatima_raw(const char* input = "../calum.lmd",
                     const char* output = "s100_fatima_raw_compare.root", int events = 25000,
                     bool checkOnly = false, const std::string& mode = "raw",
                     const char* fineTimeFile = "config/s100/fatima/fine_time_23apr_beamON.root")
{
    if (events < 1) throw std::invalid_argument("The replay needs a positive event limit");
    if (checkOnly && mode == "analysis")
    {
        CheckS100Analysis(input, output, events);
        return;
    }
    if (mode != "raw" && mode != "split" && mode != "combined")
        throw std::invalid_argument("Expected FATIMA replay mode raw, split or combined");
    if (checkOnly)
    {
        if (mode == "raw") CheckFatimaRaw(output, events);
        else CheckFatimaCal(input, output, events);
        return;
    }
    static EXT_STR_h101_t data{};

    auto* run = new FairRunOnline();
    run->SetEventHeader(new EventHeader());
    run->SetRunId(1);
    run->SetSink(new FairRootFileSink(output));

    auto* source = new UcesbSource(input, "UNPACK,RAW", "./unpack/exps/s100/s100 --input-buffer=200Mi",
                                   &data, sizeof(data));
    source->SetMaxEvents(events);
    source->AddReader(new UnpackReader(&data.header, offsetof(EXT_STR_h101_t, header)));
    const FatimaEventReader::TamexInput tamex{&data.tamex, offsetof(EXT_STR_h101_t, tamex), S100_PROCID_FATIMA};
    const FatimaEventReader::VmeInput vme{&data.vme, offsetof(EXT_STR_h101_t, vme), S100_PROCID_FATIMAVME};
    if (mode != "combined")
    {
        auto* tamexReader = new TamexReader(tamex.bank, tamex.offset, tamex.procid, "FATIMA");
        auto* qdcReader = new V1751Reader(vme.bank, vme.offset, vme.procid);
        tamexReader->SetOnline(mode == "split");
        qdcReader->SetOnline(mode == "split");
        source->AddReader(tamexReader);
        source->AddReader(qdcReader);
        auto* tdcReader = new V1290Reader(vme.bank, vme.offset, vme.procid);
        tdcReader->SetRegisterStructure(false);
        tdcReader->SetOnline(mode == "split");
        source->AddReader(tdcReader);
    }
    if (mode == "raw")
        source->AddReader(new FatimaEventReader(tamex, vme, FatimaEventReader::BankAccess::AlreadyRegistered));
    if (mode == "combined")
    {
        auto* reader = new FatimaEventReader(tamex, vme);
        reader->SetOnline(true);
        source->AddReader(reader);
    }

    if (mode != "raw")
    {
        const std::string config = "config/s100/fatima/";
        TFatimaTwinpeaksConfiguration::SetDetectorConfigurationFile(config + "fatima_alloc_apr18.txt");
        TFatimaTwinpeaksConfiguration::SetDetectorCoefficientFile(config + "fatima_cal_apr18.txt");
        TFatimaVmeConfiguration::SetDetectorMapFile(config + "Fatima_VME_allocation.txt");
        TFatimaVmeConfiguration::Set_QDC_E_CalFile(config + "Rough_Cal_2005.txt");
        TFatimaVmeConfiguration::Set_QDC_T_CalFile(config + "Fatima_QDC_Time_Calibration.txt");
        TFatimaVmeConfiguration::Set_TDC_T_CalFile(config + "Fatima_TDC_Time_Calibration.txt");
        auto* cal = new FatimaRaw2Cal();
        cal->Electronics("tamex", "vme");
        if (mode == "combined") cal->UseFatimaRawInput(fineTimeFile);
        else cal->UseTamexRawInput(tamex.procid, fineTimeFile);
        run->AddTask(cal);
    }
    run->SetSource(source);
    run->Init();
    run->Run(0, events);
}
