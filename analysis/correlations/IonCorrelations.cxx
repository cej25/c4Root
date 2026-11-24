#include "IonCorrelations.h"

#include "AidaHitData.h"
#include "BB7FebexHitData.h"
#include "StefanHitData.h"
#include "FrsGate.h"
#include "FrsHitData.h"
#include "DegasNearlineSpectra.h"
#include "DegasOnlineSpectra.h"
#include "FatimaNearlineSpectra.h"
#include "FatimaOnlineSpectra.h"
#include "bPlastNearlineSpectra.h"
#include "bPlastOnlineSpectra.h"

#include "FairRootManager.h"
#include "TDirectory.h"
#include "TFolder.h"
#include "TFile.h"
#include "TH2.h"
#include "TH1.h"
#include "c4Logger.h"

#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <set>
#include <utility>

namespace
{
struct TargetHit
{
    Long64_t time;
    Int_t dssd;
    Int_t minX;
    Int_t maxX;
    Int_t minY;
    Int_t maxY;
    Double_t x;
    Double_t y;
    Double_t energy;
    Bool_t stopped;
};

using ReadTarget = std::function<void(std::vector<TargetHit>&)>;

template<class Hit>
ReadTarget BindTarget(FairRootManager& manager, const char* branch)
{
    const auto* hits = manager.InitObjectAs<const std::vector<Hit>*>(branch);
    if (!hits)
    {
        c4LOG(error, "IonCorrelations requires " << branch);
        return {};
    }
    return [hits](std::vector<TargetHit>& output) {
        output.clear();
        for (const auto& hit : *hits)
            output.push_back({hit.Time, hit.DSSD, hit.StripXMin, hit.StripXMax,
                              hit.StripYMin, hit.StripYMax, hit.StripX, hit.StripY, hit.Energy, hit.Stopped});
    };
}

bool Overlaps(const TargetHit& implant, const TargetHit& beta)
{
    return implant.dssd == beta.dssd
        && implant.minX <= beta.maxX && beta.minX <= implant.maxX
        && implant.minY <= beta.maxY && beta.minY <= implant.maxY;
}

bool Passes(FrsGate& gate, const FrsHitItem& hit)
{
    return gate.PassedGate(hit.Get_ID_z41(), hit.Get_ID_z42(), hit.Get_ID_x2(), hit.Get_ID_x4(),
                           hit.Get_ID_AoQ_s2s4(), hit.Get_ID_dEdeg_z41(), hit.Get_sci_e_42());
}

struct Spectra
{
    std::function<void()> fill;
    std::function<void()> finish;
};

template<class Task>
bool MakeSpectra(std::vector<Spectra>& output, const TString& name)
{
    auto task = std::make_shared<Task>(name);
    task->SetSpectraDirectory(name);
    TDirectory::TContext context(gDirectory);
    if (task->Init() != kSUCCESS) return false;
    output.push_back({[task] { task->FillEvent(); }, [task] { task->FinishTask(); }});
    return true;
}

struct GateOutput
{
    std::vector<Spectra> spectra;
    TH1D* implantEnergy = nullptr;
    TH2D* implantPosition = nullptr;
    TH1D* betaEnergy = nullptr;
    TH1D* implantBetaTime = nullptr;
};
}

struct IonCorrelations::State
{
    const std::vector<FrsHitItem>* frs = nullptr;
    ReadTarget readImplants;
    ReadTarget readBetas;
    std::vector<TargetHit> implants;
    std::vector<TargetHit> betas;
    std::vector<GateOutput> outputs;
    std::multimap<Long64_t, std::pair<TargetHit, std::vector<std::size_t>>> history;
    Long64_t latestTargetTime = 0;
};

IonCorrelations::IonCorrelations(const char* name, bool online) : FairTask(name), fOnline(online)
{
}

IonCorrelations::~IonCorrelations() = default;

void IonCorrelations::CorrelateImplantBetas(std::chrono::nanoseconds window)
{
    fUseBetas = true;
    fBetaWindow = window;
}

void IonCorrelations::CorrelateGammas(const std::string& detector)
{
    if (std::find(fGammas.begin(), fGammas.end(), detector) == fGammas.end()) fGammas.push_back(detector);
}

void IonCorrelations::CorrelateGammas(std::initializer_list<std::string> detectors)
{
    for (const auto& detector : detectors) CorrelateGammas(detector);
}

InitStatus IonCorrelations::Init()
{
    auto* manager = FairRootManager::Instance();
    if (!manager) return kFATAL;

    const bool useTarget = fUseImplants || fUseBetas;
    if ((!fRequireFrs && !fGates.empty())
        || (!useTarget && !fTarget.empty()) || (fUseBetas && fBetaWindow.count() <= 0)
        || (!useTarget && fGammas.empty() && !fPlastic))
    {
        c4LOG(error, "IonCorrelations: check the FRS, target, implant-beta window and spectra settings");
        return kFATAL;
    }
    for (const auto& detector : fGammas)
    {
        if (detector == "DEGAS" || detector == "FATIMA") continue;
        c4LOG(error, "IonCorrelations: unsupported gamma detector " << detector);
        return kFATAL;
    }

    fState = std::make_unique<State>();
    if (fRequireFrs)
    {
        fState->frs = manager->InitObjectAs<const std::vector<FrsHitItem>*>("FrsHitData");
        if (!fState->frs)
        {
            c4LOG(error, "IonCorrelations requires FrsHitData");
            return kFATAL;
        }
    }
    if (useTarget)
    {
        if (fTarget == "AIDA")
        {
            fState->readImplants = BindTarget<AidaHit>(*manager, "AidaImplantHits");
            if (fUseBetas) fState->readBetas = BindTarget<AidaHit>(*manager, "AidaDecayHits");
        }
        else if (fTarget == "BB7")
        {
            fState->readImplants = BindTarget<BB7FebexHitItem>(*manager, "BB7FebexImplants");
            if (fUseBetas) fState->readBetas = BindTarget<BB7FebexHitItem>(*manager, "BB7FebexDecays");
        }
        else if (fTarget == "STEFAN" && !fUseBetas)
        {
            fState->readImplants = BindTarget<StefanHitItem>(*manager, "StefanHitData");
        }
        else
        {
            c4LOG(error, "IonCorrelations: unsupported target or target mode " << fTarget);
            return kFATAL;
        }
        if (!fState->readImplants || (fUseBetas && !fState->readBetas)) return kFATAL;
    }

    std::vector<std::string> names;
    std::set<std::string> uniqueNames;
    for (auto* gate : fGates)
    {
        const auto name = gate ? gate->GetName() : "";
        if (name.empty() || name.find('/') != std::string::npos || !uniqueNames.insert(name).second)
        {
            c4LOG(error, "IonCorrelations requires unique, nonempty ROOT directory names for PID gates");
            return kFATAL;
        }
        names.push_back(name);
    }
    if (names.empty()) names.emplace_back(fRequireFrs ? "AnyFRS" : "NoFRS");

    TFolder* histograms = nullptr;
    if (fOnline)
    {
        histograms = dynamic_cast<TFolder*>(manager->GetObject("Histograms"));
        if (!histograms) return kFATAL;
    }
    for (const auto& name : names)
    {
        auto& output = fState->outputs.emplace_back();
        const TString prefix = TString::Format("%s_%s", GetName(), name.c_str());
        if (useTarget)
        {
            TDirectory::TContext context(fOnline ? nullptr : static_cast<TDirectory*>(gDirectory));
            auto* directory = fOnline ? new TDirectory(prefix, prefix, "", 0) : gDirectory->mkdir(prefix);
            if (!directory) return kFATAL;
            if (histograms) histograms->Add(directory);
            directory->cd();
            output.implantEnergy = new TH1D("implant_energy", "Stopped implant energy;Energy;Implants", 2000, 0, 20000);
            output.implantEnergy->SetDirectory(directory);
            output.implantPosition = new TH2D("implant_strip_xy", "Stopped implant position;X strip;Y strip",
                                                512, -0.5, 511.5, 512, -0.5, 511.5);
            output.implantPosition->SetDirectory(directory);
            if (fUseBetas)
            {
                output.betaEnergy = new TH1D("beta_energy", "Matched decay energy;Energy;Decays", 2000, 0, 10000);
                output.betaEnergy->SetDirectory(directory);
                output.implantBetaTime = new TH1D("implant_beta_dt", "Implant to beta;Time [s];Decays",
                                                  500, 0, fBetaWindow.count() / 1e9);
                output.implantBetaTime->SetDirectory(directory);
            }
        }
        for (const auto& detector : fGammas)
        {
            const TString directory = prefix + "_" + detector.c_str();
            const bool ok = detector == "DEGAS"
                ? (fOnline ? MakeSpectra<DegasOnlineSpectra>(output.spectra, directory)
                           : MakeSpectra<DegasNearlineSpectra>(output.spectra, directory))
                : (fOnline ? MakeSpectra<FatimaOnlineSpectra>(output.spectra, directory)
                           : MakeSpectra<FatimaNearlineSpectra>(output.spectra, directory));
            if (!ok) return kFATAL;
        }
        if (fPlastic && !(fOnline ? MakeSpectra<bPlastOnlineSpectra>(output.spectra, prefix + "_bPlast")
                                  : MakeSpectra<bPlastNearlineSpectra>(output.spectra, prefix + "_bPlast")))
            return kFATAL;
    }
    return kSUCCESS;
}

void IonCorrelations::Exec(Option_t*)
{
    auto& state = *fState;
    std::vector<std::size_t> selected;
    if (!state.frs || (!state.frs->empty() && fGates.empty())) selected.push_back(0);
    for (std::size_t i = 0; i < fGates.size(); ++i)
    {
        if (std::any_of(state.frs->begin(), state.frs->end(),
                        [gate = fGates[i]](const auto& hit) { return Passes(*gate, hit); }))
            selected.push_back(i);
    }

    std::vector<bool> fill(state.outputs.size(), false);
    if (state.readImplants)
    {
        state.readImplants(state.implants);
        for (const auto& implant : state.implants)
        {
            if (!implant.stopped || implant.time <= 0) continue;
            state.latestTargetTime = std::max(state.latestTargetTime, implant.time);
            for (const auto i : selected)
            {
                state.outputs[i].implantEnergy->Fill(implant.energy);
                state.outputs[i].implantPosition->Fill(implant.x, implant.y);
                if (!fUseBetas) fill[i] = true;
            }
            if (fUseBetas) state.history.emplace(implant.time, std::make_pair(implant, selected));
        }
    }
    else
    {
        for (const auto i : selected) fill[i] = true;
    }

    if (state.readBetas)
    {
        state.readBetas(state.betas);
        for (const auto& beta : state.betas)
        {
            if (beta.time <= 0) continue;
            state.latestTargetTime = std::max(state.latestTargetTime, beta.time);
            const auto first = state.history.lower_bound(beta.time - fBetaWindow.count());
            const auto end = state.history.lower_bound(beta.time);
            for (auto candidate = end; candidate != first;)
            {
                --candidate;
                if (!Overlaps(candidate->second.first, beta)) continue;
                for (const auto i : candidate->second.second)
                {
                    state.outputs[i].betaEnergy->Fill(beta.energy);
                    state.outputs[i].implantBetaTime->Fill((beta.time - candidate->first) / 1e9);
                    fill[i] = true;
                }
                break;
            }
        }
        state.history.erase(state.history.begin(), state.history.lower_bound(state.latestTargetTime - fBetaWindow.count()));
    }

    for (std::size_t i = 0; i < fill.size(); ++i)
        if (fill[i])
            for (const auto& spectra : state.outputs[i].spectra) spectra.fill();
}

void IonCorrelations::FinishTask()
{
    if (!fState) return;
    auto* file = FairRootManager::Instance()->GetOutFile();
    for (const auto& output : fState->outputs)
    {
        for (const auto& spectra : output.spectra)
            if (fOnline || file) spectra.finish();
        if (!fOnline && file && output.implantEnergy)
        {
            TDirectory::TContext context(file);
            output.implantEnergy->GetDirectory()->Write();
        }
    }
}

ClassImp(IonCorrelations)
