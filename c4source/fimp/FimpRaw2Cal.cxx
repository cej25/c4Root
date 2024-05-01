// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FimpRaw2Cal.h"
#include "c4Logger.h"

// ROOT

#include <vector>
#include <numeric>

FimpRaw2Cal::FimpRaw2Cal()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   fimpArray(nullptr)
    ,   fimpCalArray(new std::vector<FimpCalItem>)
{
    fimp_config = TFimpConfiguration::GetInstance();
    // detector_mapping = fimp_config->Mapping();
}

FimpRaw2Cal::~FimpRaw2Cal()
{
    delete fimpArray;
    delete fimpCalArray;
}

InitStatus FimpRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fimpArray = mgr->InitObjectAs<decltype(fimpArray)>("FimpData");
    c4LOG_IF(fatal, !fimpArray, "Branch FimpData not found!");
    
    mgr->RegisterAny("FimpCalData", fimpCalArray, !fOnline);

    return kSUCCESS;
}

void FimpRaw2Cal::Exec(Option_t* option)
{
    fimpCalArray->clear();

    // several loops possibly needed
    // combine coarse+fine+lot into full lead/trails
    // work out tots

    for (auto const & fimpItem : *fimpArray)
    {
        uint16_t channel = fimpItem.Get_channel();
        uint16_t coarse_time = fimpItem.Get_lead_coarse_time();
        uint16_t fine_time = fimpItem.Get_lead_fine_time();
        //bool leadOrTrail = fimpItem.Get_leadOrTrail(); // lead 0, trail 1

        if (fimp_config->MappingLoaded())
        {
            // do mapping
        }

        if (fimp_config->CalibrationLoaded())
        {
            // do calibration
        }
    }
  
}

void FimpRaw2Cal::FinishEvent()
{

}

void FimpRaw2Cal::FinishTask()
{
}