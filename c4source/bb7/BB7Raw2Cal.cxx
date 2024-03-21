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
    
    //need to have the name of the detector subsystem here:
    FairRootManager::Instance()->Register("BB7VmeCalData", "BB7 Cal Data", fBB7VmeCalArray, !fOnline);
    FairRootManager::Instance()->Register("BB7TimeMachineData", "BB7 TimeMachine Data", fTimeMachineArray, !fOnline);

    fBB7VmeArray->Clear();
    fBB7VmeCalArray->Clear();

    return kSUCCESS;
}

void BB7Raw2Cal::Exec(Option_t* option)
{
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
                        int side = detector_mapping.at(unmapped_strip).first;
                        int strip = detector_mapping.at(unmapped_strip).second; 

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


}



void BB7Raw2Cal::FinishEvent()
{
    fBB7VmeArray->Clear();
    fBB7VmeCalArray->Clear();
    fTimeMachineArray->Clear();
}

void BB7Raw2Cal::FinishTask()
{

}