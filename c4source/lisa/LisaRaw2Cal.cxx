// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "LisaRaw2Cal.h"
#include "c4Logger.h"

// ROOT

#include <vector>
#include <numeric>

LisaRaw2Cal::LisaRaw2Cal()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   lisaArray(nullptr)
    ,   lisaCalArray(new std::vector<LisaCalItem>)
{
    lisa_config = TLisaConfiguration::GetInstance();
    detector_mapping = lisa_config->Mapping();   
}

LisaRaw2Cal::~LisaRaw2Cal()
{
    delete lisaArray;
    delete lisaCalArray;
}

InitStatus LisaRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaArray = mgr->InitObjectAs<decltype(lisaArray)>("LisaData");
    c4LOG_IF(fatal, !lisaArray, "Branch LisaData not found!");
    
    mgr->RegisterAny("LisaCalData", lisaCalArray, !fOnline);

    return kSUCCESS;
}

void LisaRaw2Cal::Exec(Option_t* option)
{
    lisaCalArray->clear();

    for (auto const & lisaItem : *lisaArray)
    {
        std::pair<int, int> unmapped_channel = {lisaItem.Get_board_id(), lisaItem.Get_channel_id()};
        if (detector_mapping.count(unmapped_channel) > 0)
        {
            int layer_id = detector_mapping.at(unmapped_channel).first.first;
            std::string city = detector_mapping.at(unmapped_channel).first.second;
            int xpos = detector_mapping.at(unmapped_channel).second.first;
            int ypos = detector_mapping.at(unmapped_channel).second.second;
            uint64_t EVTno = header->GetEventno();

            auto & entry = lisaCalArray->emplace_back();
            entry.SetAll(
                lisaItem.Get_wr_t(),
                layer_id,
                city,
                xpos,
                ypos,
                lisaItem.Get_channel_energy(),
                lisaItem.Get_trace(),
                EVTno,
                lisaItem.Get_pileup(),
                lisaItem.Get_overflow()
            );
            //c4LOG(info,"event num: "<< EVTno);

        }
        else c4LOG(warn, "Unmapped data? Board: "  << unmapped_channel.first << " Channel: " << unmapped_channel.second);

    }
}

void LisaRaw2Cal::FinishEvent()
{

}

void LisaRaw2Cal::FinishTask()
{
}