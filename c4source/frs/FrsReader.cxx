// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FrsMainData.h"
#include "FrsReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "TFolder.h"
#include <vector>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_frsmain.h"
}

FrsReader::FrsReader(EXT_STR_h101_frsmain_onion* data, size_t offset)
    : c4Reader("FrsReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , v830array(new std::vector<FrsMainV830Item>)
    , v792array(new std::vector<FrsMainV792Item>)
    , v1290array(new std::vector<FrsMainV1290Item>)
{
}

FrsReader::~FrsReader() 
{ 
    c4LOG(info, "Destroyed FrsReader properly.");
}

Bool_t FrsReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    
    EXT_STR_h101_frsmain_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frsmain, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    FairRootManager::Instance()->RegisterAny("FrsMainV830Data", v830array, !fOnline);
    FairRootManager::Instance()->RegisterAny("FrsMainV792Data", v792array, !fOnline);
    FairRootManager::Instance()->RegisterAny("FrsMainV1290Data", v1290array, !fOnline);

    v1290array->clear();
    v792array->clear();
    v830array->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsReader::Read()
{
    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;

    int spill_on = fData->SPILL_ON;
    int spill_off = fData->SPILL_OFF;
    if (spill_on == 1) spill_flag = true;
    if (spill_off == 1) spill_flag = false;
    header->SetSpillFlag(spill_flag);

    // V830 Scalers -- we should rename to be general
    for (int i = 0; i < fData->MAIN_SCALERS; i++)
    {
        uint32_t index = fData->MAIN_SCALERSI[i];
        uint32_t scaler = fData->MAIN_SCALERSv[i];
        auto & entry = v830array->emplace_back();
        entry.SetAll(index, scaler);
    }


    // // V830 -- we can change this
    // for (uint32_t i = 0; i < fData->frsmain_data_v830_n; i++)
    // {       
    //     uint32_t index = fData->frsmain_data_v830_nI[i];
    //     uint32_t scaler = fData->frsmain_data_v830_data[i];
    //     auto & entry = v830array->emplace_back();
    //     entry.SetAll(index, scaler);
    // } 

    // V792

    uint32_t geo = fData->SCI_DE_GEO;
    for (int i = 0; i < fData->SCI_DE_TAC; i++)
    {
        int channel = fData->SCI_DE_TACI[i] - 1;
        int data = fData->SCI_DE_TACv[channel];
        auto & entry = v792array->emplace_back();
        entry.SetAll(channel, data, geo);
    }

    // uint32_t geo = fData->frsmain_data_v792_geo;
    // int hit_index = 0;
    // for (uint32_t channel_index = 0; channel_index < fData->frsmain_data_v792_nM; channel_index++)
    // {
    //     int current_channel = fData->frsmain_data_v792_nMI[channel_index];
    //     int next_channel_start = fData->frsmain_data_v792_nME[channel_index];

    //     for (uint32_t j = hit_index; j < next_channel_start; j++)
    //     {
    //         uint32_t channel = current_channel - 1; // also needs a -1 as below.
    //         uint32_t data = fData->frsmain_data_v792_data[j];

    //         // std::cout << "channel:: " << channel << std::endl;
    //         // std::cout << "data:: " << data << std::endl;

    //         auto & entry = v792array->emplace_back();
    //         entry.SetAll(channel, data, geo);
    //     }
    //     hit_index = next_channel_start;
    // }

    // V1290
    int hit_index = 0;
    for (int channel_index = 0; channel_index < fData->SCI_T_MHTDCM; channel_index++)
    {
        int current_channel = fData->SCI_T_MHTDCMI[channel_index];
        int next_channel_start = fData->SCI_T_MHTDCME[channel_index];

        for (int j = hit_index; j < next_channel_start; j++)
        {
            uint32_t channel = current_channel - 1;
            uint32_t data = fData->SCI_T_MHTDCv[j];
            uint32_t lot = fData->SCI_LOT_MHTDCv[j];

            auto & entry = v1290array->emplace_back();
            entry.SetAll(channel, data, lot);

        }
        hit_index = next_channel_start;
    }

    // MUSIC1 T
    hit_index = 0;
    for (int channel_index = 0; channel_index < fData->MUSIC[0].TM; channel_index++)
    {
        int current_channel = fData->MUSIC[0].TMI[channel_index];
        int next_channel_start = fData->MUSIC[0].TME[channel_index];

        for (int j = hit_index; j < next_channel_start; j++)
        {
            uint32_t channel = current_channel - 1 + 16;
            uint32_t data = fData->MUSIC[0].Tv[j];
            uint32_t lot = fData->MUSIC[0].LOT_Tv[j];

            auto & entry = v1290array->emplace_back();
            entry.SetAll(channel, data, lot);

        }
        hit_index = next_channel_start;
    }

    // MUSIC2 T
    hit_index = 0;
    for (int channel_index = 0; channel_index < fData->MUSIC[1].TM; channel_index++)
    {
        int current_channel = fData->MUSIC[1].TMI[channel_index];
        int next_channel_start = fData->MUSIC[1].TME[channel_index];

        for (int j = hit_index; j < next_channel_start; j++)
        {
            uint32_t channel = current_channel - 1 + 24;
            uint32_t data = fData->MUSIC[1].Tv[j];
            uint32_t lot = fData->MUSIC[1].LOT_Tv[j];

            auto & entry = v1290array->emplace_back();
            entry.SetAll(channel, data, lot);

        }
        hit_index = next_channel_start;
    }

    // V1290
    // hit_index = 0;
    // for (uint32_t channel_index = 0; channel_index < fData->frsmain_data_v1290_nM; channel_index++)
    // {   
    //     int current_channel = fData->frsmain_data_v1290_nMI[channel_index];
    //     int next_channel_start = fData->frsmain_data_v1290_nME[channel_index];
        
    //     for (uint32_t j = hit_index; j < next_channel_start; j++)
    //     {
    //         uint32_t channel = current_channel - 1;
    //         uint32_t data = fData->frsmain_data_v1290_data[j];
    //         uint32_t lot = fData->frsmain_data_v1290_leadOrTrailv[j];
            
    //         auto & entry = v1290array->emplace_back();
    //         entry.SetAll(channel, data, lot);
    //     }
    //     hit_index = next_channel_start;
    // }
    

    return kTRUE;

}

void FrsReader::ZeroArrays()
{
    
}

void FrsReader::ClearVectors()
{
    v830array->clear();
    v792array->clear();
    v1290array->clear();
}

void FrsReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(FrsReader);
