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
#include "TClonesArray.h"

#include <vector>
#include <numeric>

LisaRaw2Cal::LisaRaw2Cal()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   fLisaArray(new TClonesArray("LisaData"))
    ,   fLisaCalArray(new TClonesArray("LisaCalData"))
    //,   fTimeMachineArray(new TClonesArray("TimeMachineData"))
{
    lisa_config = TLisaConfiguration::GetInstance();
    detector_mapping = lisa_config->Mapping();   
}

LisaRaw2Cal::~LisaRaw2Cal()
{
    if (fLisaArray) delete fLisaArray;
    if (fLisaCalArray) delete fLisaCalArray;
    //if (fTimeMachineArray) delete fTimeMachineArray;
}

InitStatus LisaRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fLisaArray = (TClonesArray*)mgr->GetObject("LisaData");
    c4LOG_IF(fatal, !fLisaArray, "Lisa branch of LisaData not found.");
    
    FairRootManager::Instance()->Register("LisaCalData", "Lisa Cal Data", fLisaCalArray, !fOnline);
    //FairRootManager::Instance()->Register("LisaTimeMachineData", "Lisa TimeMachine Data", fTimeMachineArray, !fOnline);

    fLisaArray->Clear();
    fLisaCalArray->Clear();

    return kSUCCESS;
}

void LisaRaw2Cal::Exec(Option_t* option)
{
    if (fLisaArray && fLisaArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fLisaArray->GetEntriesFast();
        //std::cout<< nHits <<std::endl;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            LisaData* lisa_item = (LisaData*)fLisaArray->At(ihit);
            if (!lisa_item) continue;

            // get boards, channel ids (vectors)
            data_boards = lisa_item->GetBoardNum();
            data_channel = lisa_item->GetID();
            data_energy = lisa_item->GetEnergy();
            data_traces = lisa_item->GetTraces();
            data_multiplicity = lisa_item->GetMultiplicity();

            int tot_multiplicity = 0;
            for (int i=0; i<data_multiplicity.size(); i++)
            {
               tot_multiplicity += data_multiplicity[i]; 
            } 

            uint32_t traceLength;
            if(tot_multiplicity == 0)
            {
                traceLength = 0;
            } else {

                traceLength = data_traces.size()/tot_multiplicity;
            }
            
            std::vector<int> layers;
            std::vector<std::string> cities;
            std::vector<int> xpositions;
            std::vector<int> ypositions;
            std::vector<uint32_t> raw_energy;
            std::vector<uint32_t> raw_traces;


            int count = 0;
            for (int i=0; i < data_boards.size(); i++)
            {
                for (int j=count; j < data_multiplicity[i] + count; j++)
                {
                    std::pair<int,int> unmapped_channel = {data_boards.at(i), data_channel.at(j)};
                    if (detector_mapping.count(unmapped_channel) > 0)
                    {
                        int layer = detector_mapping.at(unmapped_channel).first.first;
                        std::string city = detector_mapping.at(unmapped_channel).first.second;
                        int xpos = detector_mapping.at(unmapped_channel).second.first;
                        int ypos = detector_mapping.at(unmapped_channel).second.second;

                        layers.emplace_back(layer);
                        cities.emplace_back(city);
                        xpositions.emplace_back(xpos);
                        ypositions.emplace_back(ypos);
                        raw_energy.emplace_back(data_energy.at(j));

                        std::cout<<layers[j]<<std::endl;
                        std::cout<<cities[j]<<std::endl;

                        for (int n = 0; n < traceLength ; n++)
                        {
                            raw_traces.emplace_back(data_traces.at(j*traceLength + n));
                        }

                    }
                }
                count += data_multiplicity[i];
            }
            
            
            LisaCalData* lisa_cal_item = new LisaCalData();

            // set layer, x, y, e, traces etc. vectors into new caldata_item
            lisa_cal_item->SetLayers(layers);
            lisa_cal_item->SetCities(cities);
            lisa_cal_item->SetXPositions(xpositions);
            lisa_cal_item->SetYPositions(ypositions);
            lisa_cal_item->SetRawEnergy(raw_energy);
            lisa_cal_item->SetRawTraces(raw_traces);

            new ((*fLisaCalArray)[fLisaCalArray->GetEntriesFast()]) LisaCalData(*lisa_cal_item);
            
        }
    }


}


void LisaRaw2Cal::FinishEvent()
{
    fLisaArray->Clear();
    fLisaCalArray->Clear();
    //fTimeMachineArray->Clear();
}

void LisaRaw2Cal::FinishTask()
{
}