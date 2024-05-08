// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsTravMusRaw2Cal.h"
#include "c4Logger.h"

#include <vector>
#include <iostream>

FrsTravMusRaw2Cal::FrsTravMusRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   adcArray(nullptr)
    ,   tdcArray(nullptr)
    ,   calArray(new std::vector<FrsTravMusCalItem>)
{
}

FrsTravMusRaw2Cal::FrsTravMusRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   adcArray(nullptr)
    ,   tdcArray(nullptr)
    ,   calArray(new std::vector<FrsTravMusCalItem>)
{
    /*frs_config = TFrsConfiguration::GetInstance();
    frs = frs_config->FRS();
    music = frs_config->MUSIC();
    id = frs_config->ID();
    pathToConfigFiles = frs_config->GetConfigPath();*/
}

FrsTravMusRaw2Cal::~FrsTravMusRaw2Cal()
{
    c4LOG(info, "Deleting FrsTravMusRaw2Cal task");
    delete adcArray;
    delete tdcArray;
    delete calArray;
}

InitStatus FrsTravMusRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    adcArray = mgr->InitObjectAs<decltype(adcArray)>("FrsTravMusAdcData");
    c4LOG_IF(fatal, !adcArray, "Branch FrsTravMusAdcData not found!");
    tdcArray = mgr->InitObjectAs<decltype(tdcArray)>("FrsTravMusTdcData");
    c4LOG_IF(fatal, !tdcArray, "Branch FrsTravMusTdcData not found!");

    mgr->RegisterAny("FrsTravMusCalData", calArray, !fOnline);
    calArray->clear();

    music_e = new uint16_t[8];
    music_t = new uint16_t[8];

    Setup_Conditions(pathToConfigFiles);

    return kSUCCESS;
}

void FrsTravMusRaw2Cal::Exec(Option_t* option)
{
    calArray->clear();

    uint64_t wr_t;
    int adc_count = 0;
    for (int i = 0; i < 8; i++) music_e[i] = 0;
    for (auto const & adcItem : *adcArray)
    {
        if (adc_count == 0) { wr_t = adcItem.Get_wr_t(); adc_count++; }
        uint8_t channel = adcItem.Get_channel();
        if (channel >= 8) continue;
        music_e[channel] = adcItem.Get_adc_data();
    }

    for (int i = 0; i < 8; i++) music_t[i] = 0;
    for (auto const & tdcItem : *tdcArray)
    {
        uint8_t channel = tdcItem.Get_channel();
        if (channel >= 8) continue;
        music_t[channel] = tdcItem.Get_tdc_data();
    }

    auto & entry = calArray->emplace_back();
    entry.SetAll(wr_t, music_e, music_t);
    
    fNEvents++;

}

void FrsTravMusRaw2Cal::ZeroArrays()
{

}

void FrsTravMusRaw2Cal::ClearVectors()
{

}

void FrsTravMusRaw2Cal::FinishEvent()
{   
    ZeroArrays();
    ClearVectors();
};

void FrsTravMusRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.",fNEvents));
}

ClassImp(FrsTravMusRaw2Cal)