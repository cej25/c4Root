#include "DegasRaw2Cal.h"

#include "DegasRawData.h"
#include "FebexConversions.h"
#include "DegasCalData.h"
#include "TDegasConfiguration.h"
#include "TimeMachineData.h"

#include "FairRootManager.h"
#include "TClonesArray.h"
#include "c4Logger.h"

DegasRaw2Cal::DegasRaw2Cal()
    : FairTask("DegasRaw2Cal", 1),
      fCal(new TClonesArray("DegasCalData")), fTimeMachine(new TClonesArray("TimeMachineData"))
{
}

DegasRaw2Cal::~DegasRaw2Cal()
{
    delete fCal;
    delete fTimeMachine;
}

InitStatus DegasRaw2Cal::Init()
{
    auto* manager = FairRootManager::Instance();
    if (!manager) return kFATAL;
    fRaw = manager->InitObjectAs<decltype(fRaw)>("DegasRawData");
    fConfig = TDegasConfiguration::GetInstance();
    if (!fRaw || !fConfig->MappingLoaded())
    {
        c4LOG(error, "DegasRaw2Cal needs DegasRawData and a detector map");
        return kFATAL;
    }

    manager->Register("DegasCalData", "DEGAS calibrated hits", fCal, !fOnline);
    manager->Register("DegasTimeMachineData", "DEGAS timing data", fTimeMachine, !fOnline);
    return kSUCCESS;
}

void DegasRaw2Cal::Exec(Option_t*)
{
    if (fRaw->FEBEX.empty()) return;

    const auto& mapping = fConfig->Mapping();
    const auto& coefficients = fConfig->CalibrationCoefficients();
    const bool calibrateEnergy = fConfig->CalibrationCoefficientsLoaded();
    for (const auto& board : fRaw->FEBEX)
    {
        if (board.eventTicks == 0) continue;
        for (const auto& hit : board.hits)
        {
            if ((fVetoPileup && hit.pileup) || (fVetoOverflow && hit.overflow)) continue;

            // Older RAW trees store only the original FEBEX values.
            const auto signedEnergy = hit.hasConvertedValues ? hit.signedEnergy
                : febex::GammaSignedEnergy(hit.energyWord);
            // Allocation files use the UCESB board slot and one-based channel numbers.
            const auto mapped = mapping.find({board.slot, hit.channel + 1});
            if (mapped == mapping.end()) continue;
            const auto [detector, crystal] = mapped->second;
            if (detector < 0 || crystal < 0) continue;

            double energy = signedEnergy;
            if (calibrateEnergy)
            {
                const auto calibration = coefficients.find(mapped->second);
                if (calibration != coefficients.end())
                {
                    const auto& a = calibration->second;
                    energy = a[0] + energy * (a[1] + energy * a[2]);
                }
            }

            const auto channelTime = hit.hasConvertedValues ? hit.legacyChannelTimeNs
                : febex::LegacyChannelTimeNs(hit.channelTicks, hit.cfd);
            if (detector == fConfig->TM_Delayed())
                new ((*fTimeMachine)[fTimeMachine->GetEntriesFast()])
                    TimeMachineData(0, channelTime, board.wrId, board.wrTimestamp);
            else if (detector == fConfig->TM_Undelayed())
                new ((*fTimeMachine)[fTimeMachine->GetEntriesFast()])
                    TimeMachineData(channelTime, 0, board.wrId, board.wrTimestamp);

            const auto offset = hit.hasConvertedValues ? hit.hitOffsetNs
                : febex::HitOffsetNs(board.eventTicks, hit.channelTicks, hit.cfd);
            auto& calibrated = *static_cast<DegasCalData*>(fCal->ConstructedAt(fCal->GetEntriesFast()));
            calibrated = DegasCalData(board.trigger, board.eventTicks * 10, hit.pileup, hit.overflow,
                                 channelTime, energy, crystal, detector,
                                 board.wrId, board.wrTimestamp, static_cast<Long64_t>(board.wrTimestamp) + offset);
            calibrated.Set_trace(hit.trace);
        }
    }
}

void DegasRaw2Cal::FinishEvent()
{
    fCal->Clear();
    fTimeMachine->Clear();
}

ClassImp(DegasRaw2Cal)
