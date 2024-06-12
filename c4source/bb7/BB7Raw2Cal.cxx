// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BB7Raw2Cal.h"
#include "BB7VmeData.h"
#include "BB7VmeCalData.h"
#include "TimeMachineData.h"
#include "BB7Raw2Cal.h"
#include "TBB7VmeConfiguration.h"
#include "c4Logger.h"

// ROOT
#include "TClonesArray.h"
#include <vector>

BB7Raw2Cal::BB7Raw2Cal()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   v7x5array(nullptr)
    ,   v1290array(nullptr)
    ,   implantArray(new std::vector<BB7VmeImplantItem>)
    ,   decayArray(new std::vector<BB7VmeDecayItem>)
    ,   residualArray(new std::vector<BB7VmeResidualItem>)
    ,   fTimeMachineArray(new TClonesArray("TimeMachineData"))
{
    bb7_config = TBB7VmeConfiguration::GetInstance();
    detector_mapping = bb7_config->Mapping();
}

BB7Raw2Cal::~BB7Raw2Cal()
{
    if (fTimeMachineArray) delete fTimeMachineArray;
    delete v7x5array;
    delete implantArray;
    delete decayArray;
    delete residualArray;
}

InitStatus BB7Raw2Cal::Init()
{
    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    v7x5array = mgr->InitObjectAs<decltype(v7x5array)>("BB7V7x5Data");
    c4LOG_IF(fatal, !v7x5array, "Branch BB7V7x5Data not found!");
    v1290array = mgr->InitObjectAs<decltype(v1290array)>("BB7V1290Data");
    c4LOG_IF(fatal, !v1290array, "Branch BB7V1290Data not found!");
    
    FairRootManager::Instance()->Register("BB7TimeMachineData", "BB7 TimeMachine Data", fTimeMachineArray, !fOnline);
    mgr->RegisterAny("BB7ImplantData", implantArray, !fOnline);
    mgr->RegisterAny("BB7DecayData", decayArray, !fOnline);
    mgr->RegisterAny("BB7ResidualData", residualArray, !fOnline);

    implantArray->clear();
    decayArray->clear();
    residualArray->clear();

    return kSUCCESS;
}

void BB7Raw2Cal::Exec(Option_t* option)
{
    uint64_t wr_t = 0;
    for (auto const & v7x5item : *v7x5array)
    {
        wr_t = v7x5item.Get_wr_t();
        uint32_t geo = v7x5item.Get_geo();
        uint32_t data = v7x5item.Get_v7x5_data();
        uint32_t channel = v7x5item.Get_channel();

        // add skipping of time machine
        int detector = 0; int side = 0; int strip = 1; // all hits in 0 0 1 if no mapping
        if (bb7_config->MappingLoaded())
        {
            std::pair<int, int> unmapped_strip = {geo, channel};

            if (detector_mapping.count(unmapped_strip) > 0)
            {   
                detector = detector_mapping.at(unmapped_strip).first;
                side = detector_mapping.at(unmapped_strip).second.first;
                strip = detector_mapping.at(unmapped_strip).second.second;
            }    
        }

        if (data >= bb7_config->implantThreshold)
        {
            auto & entry = implantArray->emplace_back();
            entry.SetAll(wr_t, detector, side, strip, data);
        }
        else
        {
            auto & entry = decayArray->emplace_back();
            entry.SetAll(wr_t, detector, side, strip, data);
        }
    }

    uint32_t sc41l = 0, sc41r = 0, tmd = 0, tmu = 0;
    for (auto const & v1290item : *v1290array)
    {
        uint32_t channel = v1290item.Get_channel();
        uint32_t data = v1290item.Get_v1290_data();
        data *= 0.025; // factor from frs, using same module i think? testing..

        if (channel == bb7_config->SC41L()) sc41l = data;
        if (channel == bb7_config->SC41R()) sc41r = data;
        else if (channel == bb7_config->TM_Delayed()) tmd = data;
        else if (channel == bb7_config->TM_Undelayed()) tmu = data;

    }

    if (tmd > 0 && tmu > 0)
    {
        // create delayed and undelayed entries, only if we have both
        new ((*fTimeMachineArray)[fTimeMachineArray->GetEntriesFast()]) TimeMachineData(0, tmd, 1800, wr_t);
        new ((*fTimeMachineArray)[fTimeMachineArray->GetEntriesFast()]) TimeMachineData(tmu, 0, 1800, wr_t);
    }
    
    auto & entry = residualArray->emplace_back();
    entry.SetAll(sc41l, sc41r, tmd, tmu);

}



void BB7Raw2Cal::FinishEvent()
{
    fTimeMachineArray->Clear();
    implantArray->clear();
    decayArray->clear();
    residualArray->clear();
}

void BB7Raw2Cal::FinishTask()
{

}
