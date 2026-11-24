#include "DegasCal2Anl.h"

#include "DegasBGOCoincidence.h"
#include "TDegasConfiguration.h"

#include "FairRootManager.h"
#include "TClonesArray.h"
#include "c4Logger.h"

#include <cmath>
#include <vector>

DegasCal2Anl::DegasCal2Anl(const TString& name, Int_t verbose)
    : FairTask(name, verbose), fAnl(new TClonesArray("DegasCalData"))
{
}

DegasCal2Anl::~DegasCal2Anl()
{
    delete fAnl;
}

InitStatus DegasCal2Anl::Init()
{
    auto* manager = FairRootManager::Instance();
    if (!manager) return kFATAL;

    fCal = dynamic_cast<TClonesArray*>(manager->GetObject("DegasCalData"));
    if (!fCal || fCal->GetClass() != DegasCalData::Class())
    {
        c4LOG(error, "DegasCal2Anl requires the calibrated DEGAS hit branch");
        return kFATAL;
    }
    fConfig = TDegasConfiguration::GetInstance();

    if (fBGOVeto)
    {
        fBGO = dynamic_cast<TClonesArray*>(manager->GetObject("BGOTwinpeaksCalData"));
        if (!fBGO || fBGO->GetClass() != BGOTwinpeaksCalData::Class())
        {
            c4LOG(error, "DegasCal2Anl requires BGOTwinpeaksCalData when BGO veto is enabled");
            return kFATAL;
        }
        fBGOConfig = TBGOTwinpeaksConfiguration::GetInstance();
    }

    manager->Register("DegasAnlData", "DEGAS analyzed hits", fAnl, !fOnline);
    return kSUCCESS;
}

void DegasCal2Anl::Exec(Option_t*)
{
    constexpr double minimumEnergy = 25; // keV
    constexpr double addBackWindow = 100; // ns

    std::vector<const DegasCalData*> hits;
    hits.reserve(fCal->GetEntriesFast());
    for (Int_t i = 0; i < fCal->GetEntriesFast(); ++i)
    {
        const auto* hit = static_cast<const DegasCalData*>(fCal->At(i));
        if (!hit || hit->Get_channel_energy() < minimumEnergy) continue;

        bool veto = false;
        if (fBGOVeto && fBGO && !fConfig->IsDetectorAuxilliary(hit->Get_detector_id()))
        {
            for (Int_t j = 0; j < fBGO->GetEntriesFast(); ++j)
            {
                const auto* shield = static_cast<const BGOTwinpeaksCalData*>(fBGO->At(j));
                if (shield && degas::IsBGOCoincidence(*hit, *shield, *fBGOConfig))
                {
                    veto = true;
                    break;
                }
            }
        }
        if (!veto) hits.push_back(hit);
    }

    // Add back to the seed within its time gate. The highest-energy contributor
    // supplies the crystal, time and waveform.
    for (std::size_t i = 0; i < hits.size(); ++i)
    {
        const auto* seed = hits[i];
        if (!seed) continue;
        const auto* representative = seed;
        double energy = seed->Get_channel_energy();
        if (fAddBack && energy > fAddBackThreshold
            && !fConfig->IsDetectorAuxilliary(seed->Get_detector_id()))
        {
            for (std::size_t j = i + 1; j < hits.size(); ++j)
            {
                const auto* neighbor = hits[j];
                if (!neighbor || neighbor->Get_detector_id() != seed->Get_detector_id()
                    || neighbor->Get_channel_energy() <= fAddBackThreshold
                    || std::abs(neighbor->Get_absolute_event_time() - seed->Get_absolute_event_time())
                        >= addBackWindow)
                    continue;

                energy += neighbor->Get_channel_energy();
                if (neighbor->Get_channel_energy() > representative->Get_channel_energy())
                    representative = neighbor;
                hits[j] = nullptr;
            }
        }
        auto& analyzed = *static_cast<DegasCalData*>(fAnl->ConstructedAt(fAnl->GetEntriesFast()));
        analyzed = *representative;
        analyzed.Set_channel_energy(energy);
    }
}

void DegasCal2Anl::FinishEvent()
{
    fAnl->Clear();
}

ClassImp(DegasCal2Anl)
