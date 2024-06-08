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
    ,   fBB7VmeArray(new TClonesArray("BB7VmeData"))
    ,   fBB7VmeCalArray(new TClonesArray("BB7VmeCalData"))
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
    if (fBB7VmeArray) delete fBB7VmeArray;
    if (fBB7VmeCalArray) delete fBB7VmeCalArray;
    if (fTimeMachineArray) delete fTimeMachineArray;
    delete v7x5array;
    delete implantArray;
    delete decayArray;
}

InitStatus BB7Raw2Cal::Init()
{
    c4LOG(info, "Grabbing FairRootManager, RunOnline and EventHeader.");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fBB7VmeArray = (TClonesArray*)mgr->GetObject("BB7VmeData");
    c4LOG_IF(fatal, !fBB7VmeArray, "BB7 branch of BB7VmeData not found.");

    v7x5array = mgr->InitObjectAs<decltype(v7x5array)>("BB7V7x5Data");
    c4LOG_IF(fatal, !v7x5array, "Branch BB7V7x5Data not found!");
    v1290array = mgr->InitObjectAs<decltype(v1290array)>("BB7V1290Data");
    c4LOG_IF(fatal, !v1290array, "Branch BB7V1290Data not found!");
    
    //need to have the name of the detector subsystem here:
    FairRootManager::Instance()->Register("BB7VmeCalData", "BB7 Cal Data", fBB7VmeCalArray, !fOnline);
    FairRootManager::Instance()->Register("BB7TimeMachineData", "BB7 TimeMachine Data", fTimeMachineArray, !fOnline);
    mgr->RegisterAny("BB7ImplantData", implantArray, !fOnline);
    mgr->RegisterAny("BB7DecayData", decayArray, !fOnline);
    mgr->RegisterAny("BB7ResidualData", residualArray, !fOnline);

    fBB7VmeArray->Clear();
    fBB7VmeCalArray->Clear();

    implantArray->clear();
    decayArray->clear();
    residualArray->clear();

    return kSUCCESS;
}

void BB7Raw2Cal::Exec(Option_t* option)
{
    // CEJ: old - will be removed
    if (fBB7VmeArray && fBB7VmeArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fBB7VmeArray->GetEntriesFast() > 0;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            BB7VmeData* BB7VmeHit = (BB7VmeData*)fBB7VmeArray->At(ihit);
            if (!BB7VmeHit) continue;

            v7x5_geo = BB7VmeHit->Get_v7x5_geo();
            v7x5_channel = BB7VmeHit->Get_v7x5_channel();
            v7x5_data = BB7VmeHit->Get_v7x5_data();

            std::vector<int> Sides;
            std::vector<int> Strips;
            std::vector<uint32_t> Raw_ADC;

            for (int i = 0; i < v7x5_data.size(); i++)
            {
                // add skipping of time machine
                if (bb7_config->MappingLoaded())
                {
                    std::pair<int, int> unmapped_strip = {v7x5_geo.at(i), v7x5_channel.at(i)};
                    if (detector_mapping.count(unmapped_strip) > 0)
                    {
                        int side = detector_mapping.at(unmapped_strip).second.first;
                        int strip = detector_mapping.at(unmapped_strip).second.second; 

                        Sides.emplace_back(side);
                        Strips.emplace_back(strip);
                        Raw_ADC.emplace_back(v7x5_data.at(i));
                    }    
                }

                // calibrate energy etc ..
            }

            BB7VmeCalData* BB7VmeCalHit = new BB7VmeCalData();

            BB7VmeCalHit->Set_wr_t(BB7VmeHit->Get_wr_t());
            BB7VmeCalHit->Set_Sides(Sides);
            BB7VmeCalHit->Set_Strips(Strips);
            BB7VmeCalHit->Set_Raw_ADC(Raw_ADC);

            new ((*fBB7VmeCalArray)[fBB7VmeCalArray->GetEntriesFast()]) BB7VmeCalData(*BB7VmeCalHit);
            
        }
    }

    // end of old

    uint32_t wr_t = 0;
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

        if (channel == bb7_config->SC41L()) sc41l = data;
        if (channel == bb7_config->SC41R()) sc41r = data;
        else if (channel == bb7_config->TM_Delayed()) tmd = data;
        else if (channel == bb7_config->TM_Undelayed()) tmu = data;

        // CEJ: this is poorly done for now while I figure out residual mapping
        if (((channel == bb7_config->TM_Delayed()) || (channel == bb7_config->TM_Undelayed())) && bb7_config->TM_Delayed() != -1 && bb7_config->TM_Undelayed() != -1)
        {
            new ((*fTimeMachineArray)[fTimeMachineArray->GetEntriesFast()]) TimeMachineData((channel == bb7_config->TM_Undelayed()) ? (data) : (0), (data == bb7_config->TM_Undelayed()) ? (0) : (data), 1800, wr_t);
        }

    }
    
    auto & entry = residualArray->emplace_back();
    entry.SetAll(sc41l, sc41r, tmd, tmu);

}



void BB7Raw2Cal::FinishEvent()
{
    fBB7VmeArray->Clear();
    fBB7VmeCalArray->Clear();
    fTimeMachineArray->Clear();
    implantArray->clear();
    decayArray->clear();
    residualArray->clear();
}

void BB7Raw2Cal::FinishTask()
{

}