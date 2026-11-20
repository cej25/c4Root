#include "EventHeader.h"
#include "FairRootManager.h"
#include "FairRunOnline.h"
#include "FairTask.h"
#include "FrsReader.h"
#include "TExperimentConfiguration.h"
#include "UcesbSource.h"
#include "UnpackReader.h"
#include "ext_h101_unpack.h"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

R__LOAD_LIBRARY(libc4source)

namespace
{
struct S100FrsEvent
{
    EXT_STR_h101_unpack header;
    EXT_STR_h101_frs_onion frs;
};

class S100FrsAudit : public FairTask
{
public:
    explicit S100FrsAudit(const S100FrsEvent& event) : FairTask("S100FrsAudit", 1), fEvent(event) {}

    InitStatus Init() override
    {
        auto* manager = FairRootManager::Instance();
        fHeader = dynamic_cast<const EventHeader*>(manager->GetObject("EventHeader."));
        fTpat = manager->InitObjectAs<decltype(fTpat)>("FrsTpatData");
        fScalers = manager->InitObjectAs<decltype(fScalers)>("FrsScalerData");
        return fHeader && fTpat && fScalers ? kSUCCESS : kFATAL;
    }

    void Exec(Option_t*) override
    {
        if (fHeader->GetEventno() != fEvent.header.EVENTNO ||
            fHeader->GetTrigger() != static_cast<int>(fEvent.header.TRIGGER))
            Fail("event header mismatch");

        const auto& raw = fEvent.frs;
        std::uint64_t wr = 0;
        for (unsigned i = 0; i < 4; ++i) wr |= std::uint64_t{raw.WR_T[i]} << (16 * i);
        if (fTpat->size() != 1 || static_cast<std::uint64_t>(fTpat->front().Get_wr_t()) != wr ||
            static_cast<std::uint16_t>(fTpat->front().Get_tpat()) != raw.TPAT ||
            fTpat->front().Get_travmus_wr_t() != 0)
            Fail("TPAT or White Rabbit mismatch");

        std::size_t scalerIndex = 0;
        for (unsigned bank = 0; bank < 2; ++bank)
        {
            const auto& scalers = raw.SCALERS[bank];
            if (scalers._ > 32) Fail("scaler count exceeds bank capacity");
            for (unsigned i = 0; i < scalers._; ++i)
            {
                const auto channel = scalers.I[i];
                if (channel < 1 || channel > 32 || scalerIndex >= fScalers->size())
                    Fail("invalid scaler channel or missing record");
                const auto& decoded = fScalers->at(scalerIndex++);
                if (decoded.Get_index() != static_cast<int>(bank * 32 + channel) ||
                    decoded.Get_scaler() != scalers.v[i])
                    Fail("scaler channel or value mismatch");
            }
        }
        if (scalerIndex != fScalers->size()) Fail("extra scaler records");

        if (fEvent.header.TRIGGER == 3)
        {
            fSpill = true;
            ++fStarts;
        }
        if (fEvent.header.TRIGGER == 4)
        {
            fSpill = false;
            ++fEnds;
        }
        if (fHeader->GetSpillFlag() != fSpill) Fail("spill state mismatch");

        ++fEvents;
        fWr += wr != 0;
        fPatterns += raw.TPAT != 0;
        fScalerRecords += scalerIndex;
    }

    void PrintSummary() const
    {
        if (!fEvents || (!fWr && !fPatterns && !fScalerRecords))
            throw std::runtime_error("The replay did not exercise the FRS data path");
        std::cout << "PASS: " << fEvents << " S100 event headers agree with FRS RAW input\n"
                  << "Nonzero WR: " << fWr << " | Nonzero TPAT: " << fPatterns
                  << " | Scaler records: " << fScalerRecords
                  << " | Spill starts: " << fStarts << " | Spill ends: " << fEnds << '\n';
    }

private:
    [[noreturn]] void Fail(const char* reason) const
    {
        throw std::runtime_error("Event " + std::to_string(fEvent.header.EVENTNO) + ": " + reason);
    }

    const S100FrsEvent& fEvent;
    const EventHeader* fHeader = nullptr;
    const std::vector<FrsTpatItem>* fTpat = nullptr;
    const std::vector<FrsScalerItem>* fScalers = nullptr;
    std::size_t fEvents = 0, fWr = 0, fPatterns = 0, fScalerRecords = 0, fStarts = 0, fEnds = 0;
    bool fSpill = false;
};
}

void s100_frs_reader(const char* input = "../calum.lmd", int events = 25000)
{
    if (events < 1) throw std::invalid_argument("Use a positive event limit");
    static S100FrsEvent event{};
    TExperimentConfiguration::SetBOSTrig(3);
    TExperimentConfiguration::SetEOSTrig(4);
    auto* run = new FairRunOnline();
    run->SetEventHeader(new EventHeader());
    run->SetRunId(1);
    auto* source = new UcesbSource(input, "UNPACK,RAW", "./unpack/exps/s100/s100 --input-buffer=200Mi",
                                   &event, sizeof(event));
    source->SetMaxEvents(events);
    source->AddReader(new UnpackReader(&event.header, offsetof(S100FrsEvent, header)));
    auto* reader = new FrsReader(&event.frs, offsetof(S100FrsEvent, frs));
    reader->UseS100Layout();
    reader->SetOnline(true);
    source->AddReader(reader);
    run->SetSource(source);
    auto* audit = new S100FrsAudit(event);
    run->AddTask(audit);
    run->Init();
    run->Run(0, events);
    audit->PrintSummary();
}
