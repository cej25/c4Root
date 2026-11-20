#include "FairRootFileSink.h"
#include "FairRunOnline.h"
#include "FatimaEventReader.h"
#include "FatimaRawData.h"
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
}

void s100_fatima_raw(const char* input = "../calum.lmd",
                     const char* output = "s100_fatima_raw_compare.root", int events = 25000,
                     bool checkOnly = false)
{
    if (events < 1) throw std::invalid_argument("The replay needs a positive event limit");
    if (checkOnly)
    {
        CheckFatimaRaw(output, events);
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
    source->AddReader(new TamexReader(tamex.bank, tamex.offset, tamex.procid, "FATIMA"));
    source->AddReader(new V1751Reader(vme.bank, vme.offset, vme.procid));
    auto* tdcReader = new V1290Reader(vme.bank, vme.offset, vme.procid);
    tdcReader->SetRegisterStructure(false);
    source->AddReader(tdcReader);
    source->AddReader(new FatimaEventReader(tamex, vme, FatimaEventReader::BankAccess::AlreadyRegistered));
    run->SetSource(source);
    run->Init();
    run->Run(0, events);
}
