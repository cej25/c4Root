// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "TravMusRaw2Cal.h"
#include "c4Logger.h"

#include <vector>
#include <iostream>

TravMusRaw2Cal::TravMusRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   adcArray(nullptr)
    ,   tdcArray(nullptr)
    ,   calArray(new std::vector<TravMusCalItem>)
{
}

TravMusRaw2Cal::TravMusRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    ,   adcArray(nullptr)
    ,   tdcArray(nullptr)
    ,   calArray(new std::vector<TravMusCalItem>)
{

}

TravMusRaw2Cal::~TravMusRaw2Cal()
{
    c4LOG(info, "Deleting TravMusRaw2Cal task");
    delete adcArray;
    delete tdcArray;
    delete calArray;
}

InitStatus TravMusRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    adcArray = mgr->InitObjectAs<decltype(adcArray)>("TravMusAdcData");
    c4LOG_IF(fatal, !adcArray, "Branch TravMusAdcData not found!");
    tdcArray = mgr->InitObjectAs<decltype(tdcArray)>("TravMusTdcData");
    c4LOG_IF(fatal, !tdcArray, "Branch TravMusTdcData not found!");

    mgr->RegisterAny("TravMusCalData", calArray, !fOnline);
    calArray->clear();

    music_e = new uint16_t[8];
    music_t = new uint16_t[8];

    return kSUCCESS;
}

void TravMusRaw2Cal::Exec(Option_t* option)
{
    calArray->clear();

    uint64_t wr_t = 0;
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

void TravMusRaw2Cal::ZeroArrays()
{

}

void TravMusRaw2Cal::ClearVectors()
{

}

void TravMusRaw2Cal::FinishEvent()
{   
    ZeroArrays();
    ClearVectors();
};

void TravMusRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.",fNEvents));
}

ClassImp(TravMusRaw2Cal)