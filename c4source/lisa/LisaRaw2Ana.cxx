// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "LisaRaw2Ana.h"
#include "c4Logger.h"

// ROOT

#include <vector>
#include <numeric>

LisaRaw2Ana::LisaRaw2Ana()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   lisaArray(nullptr)
    ,   lisaAnaArray(new std::vector<LisaAnaItem>)

{
    lisa_config = TLisaConfiguration::GetInstance();
}



LisaRaw2Ana::~LisaRaw2Ana()
{
    delete lisaArray;
    delete lisaAnaArray;
}

InitStatus LisaRaw2Ana::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaArray = mgr->InitObjectAs<decltype(lisaArray)>("LisaData");
    c4LOG_IF(fatal, !lisaArray, "Branch LisaData not found!");
    
    mgr->RegisterAny("LisaAnaData", lisaAnaArray, !fOnline);

    return kSUCCESS;
}


//:::
// void LisaRaw2Cal::PrintMWDParameter()
// {
//     if (lisa_config->MWDParameterLoaded())
//     {
//         for (const auto& entry : lisa_config->MWDParameters())
//         {
//             //print parameters values
//         }
//     }
//     else
//     {
//         c4LOG(info, "MWD parameters are not loaded");
//     }
// }   
//:::



void LisaRaw2Ana::Exec(Option_t* option)
{
    // lisaAnaArray->clear();

    // for (auto const & lisaItem : *lisaArray)
    // {
        
                
    //     if (lisa_config->MWDParametersLoaded())
    //     {

    //         c4LOG(warn, "MWD Parameters loaded? ");

    //     }


    // }
}

void LisaRaw2Ana::FinishEvent()
{

}

void LisaRaw2Ana::FinishTask()
{
}