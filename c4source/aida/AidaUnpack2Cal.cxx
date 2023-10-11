#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AidaUnpack2Cal.h"
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
  calArray(new std::vector<AidaCalAdcItem>),
  fOnline(false),
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

  mgr->RegisterAny("AidaCalAdcData", calArray, !fOnline);

  conf = TAidaConfiguration::GetInstance();

  return kSUCCESS;
}


void AidaUnpack2Cal::Exec(Option_t* option)
{
  calArray->clear();

  for (auto const& unpack : *unpackArray)
  {
    auto& cal = calArray->emplace_back();
    int dssd = 0;
    int side = 0;
    int strip = 0;
    double intensity = 0;
    double energy = 0;
    cal.SetAll(unpack.SlowTime(), unpack.FastTime(), dssd, side, strip,
        false, intensity, energy);
  }
}

ClassImp(AidaUnpack2Cal)

