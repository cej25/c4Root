/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                               C.E. Jones                                   *
 *                                06.05.25                                    *
 ******************************************************************************/

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

#define CYCLE_TIME 6667 // 16PH, find a way to work this out without compilation

FimpRaw2Cal::FimpRaw2Cal()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   fimpArray(nullptr)
    ,   fimpCalArray(new std::vector<FimpCalItem>)
{
    fimp_config = TFimpConfiguration::GetInstance();
    detector_mapping = fimp_config->Mapping();
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

    for (auto const & fimpItem : *fimpArray)
    {
        uint16_t channel = fimpItem.Get_channel();
        std::vector<uint16_t> lead_coarse_time = fimpItem.Get_lead_coarse_time();
        std::vector<double> lead_fine_time = fimpItem.Get_lead_fine_time();
        std::vector<uint16_t> trail_coarse_time = fimpItem.Get_trail_coarse_time();
        std::vector<double> trail_fine_time = fimpItem.Get_trail_fine_time();

        for (int i = 0; i < std::min(lead_coarse_time.size(), trail_coarse_time.size()); i++)
        {
            double lead_time = (double)lead_coarse_time[i] * (double)CYCLE_TIME  - (double)lead_fine_time[i];
            double trail_time = (double)trail_coarse_time[i] * (double)CYCLE_TIME - (double)trail_fine_time[i];
            double tot = trail_time - lead_time;

            // if there is some mapping loaded, do mapping after FT CAL
            if (fimp_config->MappingLoaded())
            {
                // here we need some mapping function to dig out the 4->16 or 1->16 FIMP channels
            }

            auto & entry = fimpCalArray->emplace_back();
            entry.SetAll(fimpItem.Get_wr_t(), 
                        fimpItem.Get_wr_id(),
                        channel, 
                        tot, 
                        lead_time, 
                        trail_time // times in ps
                        );
        }
      
    }

    fNEvents++;
  
}

void FimpRaw2Cal::FinishEvent()
{
   fimpCalArray->clear(); 
}

void FimpRaw2Cal::FinishTask()
{
}