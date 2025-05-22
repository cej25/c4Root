// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "TString.h"

// c4
#include "LisaCal2Hit.h"
#include "c4Logger.h"

// ROOT

#include <vector>
#include <numeric>
#include "TVector.h"

LisaCal2Hit::LisaCal2Hit()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   lisaArray(nullptr)
    ,   lisaAnaArray(nullptr)
    ,   lisaCalArray(nullptr)
    ,   lisaHitArray(new std::vector<LisaHitItem>)

{
    lisa_config = TLisaConfiguration::GetInstance();
    detector_mapping = lisa_config->Mapping();   
}



LisaCal2Hit::~LisaCal2Hit()
{
    delete lisaArray;
    delete lisaCalArray;
    delete lisaHitArray;

}

InitStatus LisaCal2Hit::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaArray = mgr->InitObjectAs<decltype(lisaArray)>("LisaData");
    c4LOG_IF(fatal, !lisaArray, "Branch LisaData not found!");

    lisaCalArray = mgr->InitObjectAs<decltype(lisaCalArray)>("LisaCalData");
    c4LOG_IF(fatal, !lisaCalArray, "Branch LisaCalData not found!");
    
    mgr->RegisterAny("LisaHitData", lisaHitArray, !fOnline);

    return kSUCCESS;
}


//::: from here


void LisaCal2Hit::Exec(Option_t* option)
{
    lisaHitArray->clear();

    for (auto const & lisaHitItem : *lisaHitArray)
    {          

        if (lisa_config->MappingLoaded())
        {
            if (detector_mapping.count(unmapped_channel) > 0)
            {
                int layer_id = detector_mapping.at(unmapped_channel).first.first;
                TString city = detector_mapping.at(unmapped_channel).first.second; //Debugging. std::string to Tstring 
                int xpos = detector_mapping.at(unmapped_channel).second.first;
                int ypos = detector_mapping.at(unmapped_channel).second.second;
                uint64_t EVTno = header->GetEventno();

                auto & entry = lisaCalArray->emplace_back();

                entry.SetAll(
                    lisaCalItem.Get_wr_t(),
                    lisaCalItem.Get_wr_id(),
                    lisaCalItem.Get_board_id(),
                    layer_id,
                    city,
                    xpos,
                    ypos,
                    lisaCalItem.Get_energy(),
                    lisaCalItem.Get_energy_MWD(),
                    lisaCalItem.Get_trace_febex(),
                    lisaCalItem.Get_trace_x(),
                    lisaCalItem.Get_energy_GM(),
                    lisaCalItem.Get_energy_MWD_GM(),
                    z_lisa,
                    lisaCalItem.Get_board_event_time(),
                    lisaCalItem.Get_channel_event_time(),
                    EVTno,
                    lisaCalItem.Get_pileup(),
                    //lisaAnaItem.Get_pileup_MWD(),
                    lisaCalItem.Get_overflow()
                    //lisaAnaItem.Get_overflow_MWD()
                );

            }

        }


    }
}

void LisaCal2Hit::FinishEvent()
{

}

void LisaCal2Hit::FinishTask()
{
}