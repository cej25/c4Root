//WIP
// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"
#include "TString.h"

// c4
#include "LisaAna2Cal.h"
#include "c4Logger.h"

// ROOT

#include <vector>
#include <numeric>
#include "TVector.h"

LisaAna2Cal::LisaAna2Cal()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   lisaArray(nullptr)
    ,   lisaAnaArray(nullptr)
    ,   lisaCalArray(new std::vector<LisaCalItem>)
{
    lisa_config = TLisaConfiguration::GetInstance();
    detector_mapping = lisa_config->Mapping();   
}



LisaAna2Cal::~LisaAna2Cal()
{
    delete lisaArray;
    delete lisaAnaArray;
    delete lisaCalArray;
}

InitStatus LisaAna2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaArray = mgr->InitObjectAs<decltype(lisaArray)>("LisaData");
    c4LOG_IF(fatal, !lisaArray, "Branch LisaData not found!");

    lisaAnaArray = mgr->InitObjectAs<decltype(lisaAnaArray)>("LisaAnaData");
    c4LOG_IF(fatal, !lisaAnaArray, "Branch LisaAnaData not found!");
    
    mgr->RegisterAny("LisaCalData", lisaCalArray, !fOnline);

    return kSUCCESS;
}


//:::
void LisaAna2Cal::PrintDetectorGainM()
{
    if (lisa_config->GainMatchingLoaded())
    {
        for (const auto& entry : lisa_config->GainMatchingCoefficients())
        {
            std::cout << "Detector (#layer,#x,#y): " << entry.first.first << " " << entry.first.second.first << " " << entry.first.second.second << "\n";
            std::cout << " slope : " << entry.second.first << " intercept : " << entry.second.second << "\n";
        }
    }
    else
    {
        c4LOG(info, "Gain matching parameters are not loaded");
    }
}   

void LisaAna2Cal::PrintDetectorGainM_MWD()
{
    if (lisa_config->GainMatchingMWDLoaded())
    {
        for (const auto& entry : lisa_config->GainMatchingMWDCoefficients())
        {
            std::cout << "Detector (#layer,#x,#y): " << entry.first.first << " " << entry.first.second.first << " " << entry.first.second.second << "\n";
            std::cout << " slope MWD : " << entry.second.first << " intercept MWD : " << entry.second.second << "\n";
        }
    }
    else
    {
        c4LOG(info, "Gain matching MWD parameters are not loaded");
    }
}  
//:::


void LisaAna2Cal::Exec(Option_t* option)
{
    lisaCalArray->clear();

    for (auto const & lisaAnaItem : *lisaAnaArray)
    {          
        std::pair<int, int> unmapped_channel = {lisaAnaItem.Get_board_id(), lisaAnaItem.Get_channel_id_traces()};
        //Get_channel_id_traces() when taking the id information from the trace header
        //Get_channel_id() when taking the id information from the header

        if (lisa_config->MappingLoaded())
        {
            if (detector_mapping.count(unmapped_channel) > 0)
            {
                int layer_id = detector_mapping.at(unmapped_channel).first.first;
                TString city = detector_mapping.at(unmapped_channel).first.second; //Debugging. std::string to Tstring 
                int xpos = detector_mapping.at(unmapped_channel).second.first;
                int ypos = detector_mapping.at(unmapped_channel).second.second;
                uint64_t EVTno = header->GetEventno();

                //std::cout << "Layer, x , y: (" << layer_id << ", (" << xpos << ", " << ypos << "))"<< std::endl;


                if (lisa_config->GainMatchingLoaded())
                {
                    energy_GM = 0;
                    std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> GM_coeffs = lisa_config->GainMatchingCoefficients();
                    std::pair< int, std::pair<int,int> > detector_lxy = std::make_pair( layer_id, std::make_pair(xpos, ypos) );

                    /*
                    std::cout << "Contents of GM_coeffs:" << std::endl;
                    for (const auto& entry : GM_coeffs) 
                    {
                        std::cout << "Key: (" << entry.first.first << ", (" << entry.first.second.first << ", " << entry.first.second.second << "))";
                        std::cout << " Value: (" << entry.second.first << ", " << entry.second.second << ")" << std::endl;
                    }
                    */
                    
                    if (auto result_find_GM = GM_coeffs.find(detector_lxy); result_find_GM != GM_coeffs.end()) 
                    {
                        std::pair<double,double> coeffs = result_find_GM->second; //find returns an iterator over the pairs matching key
                        slope = coeffs.first;
                        intercept = coeffs.second;
                        
                        energy_GM = intercept + slope*lisaAnaItem.Get_channel_energy(); 

                        //std::cout<< " Energy GM - in loop " << "\n";
                    }
                    
                }

                if (lisa_config->GainMatchingMWDLoaded())
                {
                    energy_MWD_GM = 0;
                    std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> GM_MWD_coeffs = lisa_config->GainMatchingMWDCoefficients();
                    std::pair< int, std::pair<int,int> > detector_lxy = std::make_pair( layer_id, std::make_pair(xpos, ypos) );
                    

                    if (auto result_find_GM_MWD = GM_MWD_coeffs.find(detector_lxy); result_find_GM_MWD != GM_MWD_coeffs.end()) 
                    {
                        std::pair<double,double> coeffs = result_find_GM_MWD->second;
                        slope_MWD = coeffs.first;
                        intercept_MWD = coeffs.second;
                        
                        energy_MWD_GM = intercept_MWD + slope_MWD*lisaAnaItem.Get_channel_energy_MWD(); 

                        //std::cout<< " Energy GM - in loop " << "\n";
                    }
                    
                }
                        
                auto & entry = lisaCalArray->emplace_back();

                entry.SetAll(
                    lisaAnaItem.Get_wr_t(),
                    lisaAnaItem.Get_wr_id(),
                    lisaAnaItem.Get_board_id(),
                    layer_id,
                    city,
                    xpos,
                    ypos,
                    lisaAnaItem.Get_channel_energy(),
                    lisaAnaItem.Get_channel_energy_MWD(),
                    lisaAnaItem.Get_trace_febex(),
                    lisaAnaItem.Get_trace_MWD(),
                    lisaAnaItem.Get_trace_x(),
                    energy_GM,
                    energy_MWD_GM,
                    lisaAnaItem.Get_board_event_time(),
                    lisaAnaItem.Get_channel_time(),
                    EVTno,
                    lisaAnaItem.Get_pileup(),
                    //lisaAnaItem.Get_pileup_MWD(),
                    lisaAnaItem.Get_overflow()
                    //lisaAnaItem.Get_overflow_MWD()
                );
                //c4LOG(info,"event num: "<< EVTno);

            }
            else c4LOG(warn, "Unmapped data? Board: "  << unmapped_channel.first << " Channel: " << unmapped_channel.second);

        }


    }
}

void LisaAna2Cal::FinishEvent()
{

}

void LisaAna2Cal::FinishTask()
{
}