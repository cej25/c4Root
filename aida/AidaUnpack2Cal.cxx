#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AidaUnpack2Cal.h"
#include "TAidaConfiguration.h"
#include "c4Logger.h"
#include "AidaData.h"
#include "AidaCalData.h"
#include <FairTask.h>

// Static mapping of a FEE channel to DSSD Strip 
// Defined by AIDA hardware, not configurable
// 0 refers to the "edge" and 63 the middle
// For the "high" side thus 0 is strip 127
static const int FeeToStrip[64] = {
    62, 63, 59, 60, 61, 56, 57, 58, 52, 53, 54, 55, 49, 50, 51, 45,
    46, 47, 48, 42, 43, 44, 38, 39, 40, 41, 35, 36, 37, 31, 32, 33,
    34, 28, 29, 30, 24, 25, 26, 27, 21, 22, 23, 17, 18, 19, 20, 14,
    15, 16, 10, 11, 12,  7,  3,  0,  8,  4,  1,  9,  5,  2, 13,  6
};

AidaUnpack2Cal::AidaUnpack2Cal() :
  unpackArray(nullptr),
  implantCalArray(new std::vector<AidaCalAdcItem>),
  decayCalArray(new std::vector<AidaCalAdcItem>),
  fImplantOnline(false),
  fDecayOnline(false),
  conf(nullptr)
{
}

AidaUnpack2Cal::~AidaUnpack2Cal()
{
}

void AidaUnpack2Cal::SetParContainers()
{
}

InitStatus AidaUnpack2Cal::Init()
{
  c4LOG(info, "");
  FairRootManager* mgr = FairRootManager::Instance();
  c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

  unpackArray = mgr->InitObjectAs<decltype(unpackArray)>("AidaAdcData");
  c4LOG_IF(fatal, !unpackArray, "Branch AidaAdcData not found!");

  mgr->RegisterAny("AidaImplantCalAdcData", implantCalArray, !fImplantOnline);
  mgr->RegisterAny("AidaDecayCalAdcData", decayCalArray, !fDecayOnline);

  conf = TAidaConfiguration::GetInstance();

  return kSUCCESS;
}


void AidaUnpack2Cal::Exec(Option_t* option)
{
  implantCalArray->clear();
  decayCalArray->clear();


  for (auto const& unpack : *unpackArray)
  {
    // TODO?: Clock correction

    auto feeConf = conf->FEE(unpack.Fee() - 1);
    if (feeConf.DSSD <= 0)
    {
      c4LOG(error, "Invalid DSSD Mapping for AIDA fee " << unpack.Fee() << ", ignoring event");
      return;
    }
    int dssd = feeConf.DSSD;
    int side = feeConf.Side;
    int strip = 0;
    if (feeConf.High)
    {
      strip = 127 - FeeToStrip[unpack.Channel()];
    }
    else
    {
      strip = FeeToStrip[unpack.Channel()];
    }
    if (conf->Wide() && feeConf.Side == conf->DSSD(dssd - 1).XSide)
    {
      int shift = 0;
      if (feeConf.Segment == WideAIDASegment::Centre) shift = 128;
      if (feeConf.Segment == WideAIDASegment::Right) shift = 256;
      strip += shift;
    }
    double intensity = (unpack.Value() - 32768) * side;
    intensity = (intensity - conf->GetAdcOffset(unpack.Fee() - 1, unpack.Channel()));
    bool range = unpack.Range();
    double energy = 0;
    if (range)
    {
      energy = intensity * 0.7; // Energy in MeV
    }
    else
    {
      energy = intensity * conf->GetDssdGain(dssd - 1,
          side == conf->DSSD(dssd - 1).XSide ? 0 : 1, strip);
    }

    // Split into implant and decay arrays, check threshold for decays
    if (range) {
      auto& cal = implantCalArray->emplace_back();
      cal.SetAll(unpack.SlowTime(), unpack.FastTime(), unpack.Fee(),
          unpack.Channel(), dssd, side, strip,
          range, intensity, energy);
    }
    else {
      double thrs = conf->GetDssdStripThreshold(dssd - 1, side == - 1 ? 0 : 1, strip);
      if (thrs >= 0 && energy > thrs) {
        auto& cal = decayCalArray->emplace_back();
        cal.SetAll(unpack.SlowTime(), unpack.FastTime(), unpack.Fee(),
            unpack.Channel(), dssd, side, strip,
            range, intensity, energy);
      }
    }
  }

  // Clear decay array if implants present
  if (implantCalArray->size() > 0) {
    decayCalArray->clear();
  }
}

ClassImp(AidaUnpack2Cal)

