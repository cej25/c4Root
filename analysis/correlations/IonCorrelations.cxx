#include "IonCorrelations.h"

#include "AidaHitData.h"
#include "TAidaConfiguration.h"
#include "TCorrelationsConfiguration.h"
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
    Double_t positionX;
    Double_t positionY;
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
                              hit.StripYMin, hit.StripYMax, hit.StripX, hit.StripY, hit.PosX, hit.PosY, hit.Energy, hit.Stopped});
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

struct ImplantSpectra
{
    TH1D* energy;
    TH2D* strips;
    TH2D* position;

    void Fill(const TargetHit& hit) const
    {
        energy->Fill(hit.energy);
        strips->Fill(hit.x, hit.y);
        position->Fill(hit.positionX, hit.positionY);
    }
};

struct AidaPlaneSpectra
{
    ImplantSpectra all;
    ImplantSpectra stopped;
};

struct GateOutput
{
    std::vector<Spectra> spectra;
    TH1D* implantEnergy = nullptr;
    std::vector<AidaPlaneSpectra> aidaPlanes;
    TH2D* implantPosition = nullptr;
    TH1D* betaEnergy = nullptr;
    TH1D* implantBetaTime = nullptr;
};
}

struct IonCorrelations::State
{
    const std::vector<FrsHitItem>* frs = nullptr;
    const TAidaConfiguration* aida = nullptr;
    Long64_t frsAidaLower = 0;
    Long64_t frsAidaUpper = 0;
    ULong64_t noFrsMatch = 0;
    ULong64_t ambiguousFrsMatch = 0;
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
            if (fRequireFrs)
            {
                const auto gates = TCorrelationsConfiguration::GetInstance()->CorrelationsMap();
                const auto window = gates.find("FRS-AIDA WR Gate");
                if (window == gates.end() || window->second.size() != 2
                    || window->second[0] >= window->second[1])
                {
                    c4LOG(error, "IonCorrelations requires an increasing FRS_AIDA_WR window (ns) in correlations.dat");
                    return kFATAL;
                }
                fState->frsAidaLower = window->second[0];
                fState->frsAidaUpper = window->second[1];
                fState->aida = TAidaConfiguration::GetInstance();
            }
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
            if (fState->aida)
            {
                const int xStrips = fState->aida->Wide() ? 386 : 128;
                const double xMax = fState->aida->Wide() ? 113.4 : 37.8;
                for (int dssd = 1; dssd <= fState->aida->DSSDs(); ++dssd)
                {
                    auto* plane = directory->mkdir(Form("DSSD%d", dssd));
                    if (!plane) return kFATAL;
                    TDirectory::TContext planeContext(plane);
                    const auto book = [&](const char* stem, const char* label) {
                        auto* energy = new TH1D(TString::Format("%s_energy", stem),
                                                TString::Format("%s energy;Energy [MeV];Hits", label),
                                                2000, 0, 20000);
                        auto* strips = new TH2D(TString::Format("%s_strip_xy", stem),
                                                TString::Format("%s hit pattern;X strip;Y strip", label),
                                                xStrips, 0, xStrips, 128, 0, 128);
                        auto* position = new TH2D(TString::Format("%s_pos_xy", stem),
                                                  TString::Format("%s position;X [mm];Y [mm]", label),
                                                  xStrips, -xMax, xMax, 128, -37.8, 37.8);
                        energy->SetDirectory(plane);
                        strips->SetDirectory(plane);
                        position->SetDirectory(plane);
                        return ImplantSpectra{energy, strips, position};
                    };
                    output.aidaPlanes.push_back({
                        book("target_hit", "Target Stack hit"),
                        book("implant", "Stopped implant")
                    });
                }
            }
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
    std::vector<std::size_t> eventGates;
    if (!state.aida)
    {
        if (!state.frs || (!state.frs->empty() && fGates.empty())) eventGates.push_back(0);
        for (std::size_t i = 0; i < fGates.size(); ++i)
        {
            if (std::any_of(state.frs->begin(), state.frs->end(),
                            [gate = fGates[i]](const auto& hit) { return Passes(*gate, hit); }))
                eventGates.push_back(i);
        }
    }

    std::vector<bool> fill(state.outputs.size(), false);
    if (state.readImplants)
    {
        state.readImplants(state.implants);
        for (const auto& implant : state.implants)
        {
            if (implant.time <= 0 || (!implant.stopped && !state.aida)) continue;
            if (implant.stopped) state.latestTargetTime = std::max(state.latestTargetTime, implant.time);
            const auto* selected = &eventGates;
            std::vector<std::size_t> implantGates;
            if (state.aida)
            {
                const auto inTime = [&](const FrsHitItem& hit) {
                    const auto time = hit.Get_wr_t();
                    if (time <= 0) return false;
                    const auto difference = implant.time - time;
                    return state.frsAidaLower < difference && difference < state.frsAidaUpper;
                };
                const auto end = state.frs->end();
                const auto match = std::find_if(state.frs->begin(), end, inTime);
                if (match == end)
                {
                    if (implant.stopped) ++state.noFrsMatch;
                }
                else if (std::any_of(std::next(match), end, inTime))
                {
                    if (implant.stopped) ++state.ambiguousFrsMatch;
                }
                else if (fGates.empty()) implantGates.push_back(0);
                else
                {
                    for (std::size_t i = 0; i < fGates.size(); ++i)
                        if (Passes(*fGates[i], *match)) implantGates.push_back(i);
                }
                selected = &implantGates;
            }
            for (const auto i : *selected)
            {
                auto& output = state.outputs[i];
                const auto& planes = output.aidaPlanes;
                if (implant.dssd > 0 && static_cast<std::size_t>(implant.dssd) <= planes.size())
                {
                    const auto& plane = planes[implant.dssd - 1];
                    plane.all.Fill(implant);
                    if (implant.stopped) plane.stopped.Fill(implant);
                }
                if (!implant.stopped) continue;
                output.implantEnergy->Fill(implant.energy);
                output.implantPosition->Fill(implant.x, implant.y);
                if (!fUseBetas) fill[i] = true;
            }
            if (fUseBetas && implant.stopped)
                state.history.emplace(implant.time, std::make_pair(implant, *selected));
        }
    }
    else
    {
        for (const auto i : eventGates) fill[i] = true;
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
    if (fState->aida)
        c4LOG(info, "Stopped AIDA implants without an in-window FRS hit: " << fState->noFrsMatch
                     << ", with multiple in-window FRS hits: " << fState->ambiguousFrsMatch);
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
