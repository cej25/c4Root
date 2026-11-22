#include "DegasRaw2Cal.h"

#include "DegasRawData.h"
#include "FebexConversions.h"
#include "GermaniumCalData.h"
#include "GermaniumCalibration.h"
#include "TGermaniumConfiguration.h"
#include "TimeMachineData.h"

#include "FairRootManager.h"
#include "TClonesArray.h"
#include "c4Logger.h"

DegasRaw2Cal::DegasRaw2Cal()
    : FairTask("DegasRaw2Cal", 1),
      fCal(new TClonesArray("GermaniumCalData")), fTimeMachine(new TClonesArray("TimeMachineData"))
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
    fConfig = TGermaniumConfiguration::GetInstance();
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

    const auto mapping = fConfig->Mapping();
    const auto coefficients = fConfig->CalibrationCoefficients();
    const bool calibrateEnergy = fConfig->CalibrationCoefficientsLoaded();
    for (const auto& board : fRaw->FEBEX)
    {
        // Use the S100 Germanium selection during the parallel validation.
        if (board.eventTicks == 0) continue;
        for (const auto& hit : board.hits)
        {
            if ((fVetoPileup && hit.pileup) || (fVetoOverflow && hit.overflow)) continue;

            // Older RAW trees store only the original FEBEX values.
            const auto signedEnergy = hit.hasConvertedValues ? hit.signedEnergy
                : febex::GammaSignedEnergy(hit.energyWord);
            // The legacy detector map uses the UCESB slot as its board key.
            const auto cal = germanium::CalibrateHit(mapping, coefficients, board.slot, hit.channel,
                                                       signedEnergy, calibrateEnergy);
            if (!cal) continue;

            const auto channelTime = hit.hasConvertedValues ? hit.legacyChannelTimeNs
                : febex::LegacyChannelTimeNs(hit.channelTicks, hit.cfd);
            if (cal->detector == fConfig->TM_Delayed())
                new ((*fTimeMachine)[fTimeMachine->GetEntriesFast()])
                    TimeMachineData(0, channelTime, board.wrId, board.wrTimestamp);
            else if (cal->detector == fConfig->TM_Undelayed())
                new ((*fTimeMachine)[fTimeMachine->GetEntriesFast()])
                    TimeMachineData(channelTime, 0, board.wrId, board.wrTimestamp);

            const auto offset = hit.hasConvertedValues ? hit.hitOffsetNs
                : febex::HitOffsetNs(board.eventTicks, hit.channelTicks, hit.cfd);
            new ((*fCal)[fCal->GetEntriesFast()])
                GermaniumCalData(board.trigger, board.eventTicks * 10, hit.pileup, hit.overflow,
                                 channelTime, cal->energy, cal->crystal, cal->detector,
                                 board.wrId, board.wrTimestamp, static_cast<std::int64_t>(board.wrTimestamp) + offset);
        }
    }
}

void DegasRaw2Cal::FinishEvent()
{
    fCal->Clear();
    fTimeMachine->Clear();
}

ClassImp(DegasRaw2Cal)
