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


void LisaRaw2Ana::Exec(Option_t* option)
{
    lisaAnaArray->clear();

    for (auto const & lisaItem : *lisaArray)
    {
               
        if (lisa_config->MWDParametersLoaded())
        {


            // ::: Calculation for MWD trace (trace_MWD) :::
            std::vector<int16_t> trace_febex = lisaItem.Get_trace();
            double par1 = lisa_config->Get_testconstant_1();

            trace_MWD.resize(trace_febex.size());
            for( int i = 0; i < trace_febex.size(); i++)
            {
                trace_MWD.at(i) = trace_febex.at(i) * par1;
            }
            

            // ::: Calculation for MWD energy (energy_MWD) :::
            double energy_febex = lisaItem.Get_channel_energy();
            double par2 = lisa_config->Get_testconstant_2();
            energy_MWD = energy_febex * par2;

            
            
            // ::: Calculation for MWD pileup (pileup_MWD) :::
            // ...
            // ::: Calculation for MWD overflow (overflow_MWD) :::
            // ...


            auto & entry = lisaAnaArray->emplace_back();    
            
            uint64_t EVTno = header->GetEventno();
            entry.SetAll(
                lisaItem.Get_wr_t(),
                lisaItem.Get_wr_id(),
                lisaItem.Get_board_id(),
                lisaItem.Get_board_event_time(),
                lisaItem.Get_channel_id(),
                lisaItem.Get_channel_time(),
                lisaItem.Get_pileup(),
                //pileup_MWD,
                lisaItem.Get_overflow(),
                //overflow_MWD,
                lisaItem.Get_channel_energy(),
                energy_MWD,
                lisaItem.Get_channel_id_traces(),
                lisaItem.Get_trace(),
                trace_MWD
                //EVTno
            );

        }


    }
}

void LisaRaw2Ana::FinishEvent()
{

}

void LisaRaw2Ana::FinishTask()
{
}