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
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FrsData.h"
#include "FrsReader.h"
#include "FrsReaderSafety.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "TFolder.h" //?
#include <vector>
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h" 
    #include "ext_h101_frs.h"
}

FrsReader::FrsReader(EXT_STR_h101_frs_onion* data, size_t offset)
    :   c4Reader("FrsReader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   tpatArray(new std::vector<FrsTpatItem>)
    ,   scalerArray(new std::vector<FrsScalerItem>)
    ,   sciArray(new std::vector<FrsSciItem>)
    ,   musicArray(new std::vector<FrsMusicItem>)
    ,   tpcArray(new std::vector<FrsTpcItem>)
{
}

FrsReader::~FrsReader() 
{ 
    c4LOG(info, "Destroyed FrsReader properly.");
}

Bool_t FrsReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    
    EXT_STR_h101_frs_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_frs, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    mgr->RegisterAny("FrsTpatData", tpatArray, !fOnline);
    mgr->RegisterAny("FrsScalerData", scalerArray, !fOnline);
    mgr->RegisterAny("FrsSciData", sciArray, !fOnline);
    mgr->RegisterAny("FrsMusicData", musicArray, !fOnline);
    mgr->RegisterAny("FrsTpcData", tpcArray, !fOnline);


    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FrsReader::Read()
{
    if (!fData) return kTRUE;
    if (fData == nullptr) return kFALSE;

    const uint64_t wr_bits = frs_reader_safety::AssembleWhiteRabbitTimestamp(fData->WR_T[0], fData->WR_T[1], fData->WR_T[2], fData->WR_T[3]);
    const int64_t wr_t = static_cast<int64_t>(wr_bits);
    // if (wr_t == 0) return kTRUE; // CEJ: does this screw things up for spillflag? untested, yes most likely

    int16_t tpat = fData->TPAT;
    
 
    const uint64_t travmus_bits = frs_reader_safety::AssembleWhiteRabbitTimestamp(fData->TM_WR_T[0], fData->TM_WR_T[1], fData->TM_WR_T[2], fData->TM_WR_T[3]);
    const Long64_t travmus_wr_t = static_cast<Long64_t>(travmus_bits);

    auto & entry = tpatArray->emplace_back();
    entry.SetAll(wr_t, tpat, travmus_wr_t);

    // std::cout << travmus_wr_t << std::endl;


    ScalerReader();
    ScintillatorReader();
    MusicReader();
    TpcReader();

    return kTRUE;

}

void FrsReader::ScalerReader()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < fData->SCALERS[i]._; j++)
        {
            uint32_t index = fData->SCALERS[i].I[j] + i * 32; // 2 sets of scalers
            uint32_t scaler = fData->SCALERS[i].v[j];
            auto & entry = scalerArray->emplace_back();
            entry.SetAll(index, scaler);
        }
    }
}

void FrsReader::ScintillatorReader()
{
    // TAC - DE
    for (int i = 0; i < fData->SCI_TAC_DE; i++)
    {
        const uint32_t raw_channel = fData->SCI_TAC_DEI[i];
        if (raw_channel == 0 || raw_channel > 32) continue;
        uint32_t channel = raw_channel - 1;
        uint32_t data = fData->SCI_TAC_DEv[i];
        
        sciDE[channel] = data;
    }

    // TAC - DT
    for (int i = 0; i < fData->SCI_TAC_DT; i++)
    {
        const uint32_t raw_channel = fData->SCI_TAC_DTI[i];
        if (raw_channel == 0 || raw_channel > 32) continue;
        uint32_t channel = raw_channel - 1;
        uint32_t data = fData->SCI_TAC_DTv[i];

        sciDT[channel] = data;
    }

    // MHTDC - T
    int hit_index = 0;
    for (int channel_index = 0; channel_index < fData->SCI_MHTDC_TM; channel_index++)
    {
        int current_channel = fData->SCI_MHTDC_TMI[channel_index];
        int next_channel_start = fData->SCI_MHTDC_TME[channel_index];

        // Both packed arrays must cover the complete channel block.
        if (!frs_reader_safety::ValidPackedBlock(hit_index, next_channel_start,
                                                 fData->SCI_MHTDC_T, fData->SCI_MHTDC_LOT, 4096))
        {
            if (next_channel_start > hit_index) hit_index = next_channel_start;
            continue;
        }

        if (current_channel < 1 || current_channel > 32)
        {
            hit_index = next_channel_start;
            continue;
        }

        for (int j = hit_index; j < next_channel_start; j++)
        {
            uint32_t channel = current_channel - 1;
            uint32_t data = fData->SCI_MHTDC_Tv[j];
            uint32_t lot = fData->SCI_MHTDC_LOTv[j];

            if (lot == 0) sciMHTDC[channel].emplace_back(data);

        }

        hit_index = next_channel_start;
    }

    auto & entry = sciArray->emplace_back();
    entry.SetAll(sciDE, sciDT, sciMHTDC);
}

void FrsReader::MusicReader()
{

    for (int i = 0; i < 5; i++)
    {   
        // MUSIC E
        for (int j = 0; j < fData->MUSIC[i].E; j++)
        {
            const uint32_t raw_channel = fData->MUSIC[i].EI[j];
            if (raw_channel == 0 || raw_channel > 8) continue;
            uint32_t channel = raw_channel - 1;
            uint32_t data = fData->MUSIC[i].Ev[j];

            musicE[i][channel] = data;
        }

        // MUSIC T
        if (i > 1) continue; // for now.... 
        int hit_index = 0;
        for (int channel_index = 0; channel_index < fData->MUSIC[i].TM; channel_index++)
        {
            int current_channel = fData->MUSIC[i].TMI[channel_index];
            int next_channel_start = fData->MUSIC[i].TME[channel_index];

            // Both packed arrays must cover the complete channel block.
            if (!frs_reader_safety::ValidPackedBlock(hit_index, next_channel_start,
                                                     fData->MUSIC[i].T, fData->MUSIC[i].LOT, 1024))
            {
                if (next_channel_start > hit_index) hit_index = next_channel_start;
                continue;
            }

            if (current_channel < 1 || current_channel > 8)
            {
                hit_index = next_channel_start;
                continue;
            }

            for (int j = hit_index; j < next_channel_start; j++)
            {
                uint32_t channel = current_channel - 1;
                uint32_t data = fData->MUSIC[i].Tv[j];
                uint32_t lot = fData->MUSIC[i].LOTv[j];
                
                // for now take first hit? we don't even analyse the timing
                if (lot == 0 && musicT[i][channel] == 0) musicT[i][channel] = data;
            }

            hit_index = next_channel_start;
        }
    }

    auto & entry = musicArray->emplace_back();
    entry.SetAll(musicE, musicT);
}

void FrsReader::TpcReader()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < fData->TPC_ADC[i]._; j++)
        {   
            const uint32_t raw_channel = fData->TPC_ADC[i].I[j];
            if (raw_channel == 0 || raw_channel > 8) continue;
            uint32_t channel = raw_channel - 1;
            uint32_t data = fData->TPC_ADC[i].v[j];

            adcData[i][channel] = data;
        }
    }

    int hit_index = 0;
    for (int channel_index = 0; channel_index < fData->TPC_TDC_TM; channel_index++)
    {
        int current_channel = fData->TPC_TDC_TMI[channel_index];
        int next_channel_start = fData->TPC_TDC_TME[channel_index];

        // Both packed arrays must cover the complete channel block.
        if (!frs_reader_safety::ValidPackedBlock(hit_index, next_channel_start,
                                                 fData->TPC_TDC_T, fData->TPC_TDC_LOT, 16384))
        {
            if (next_channel_start > hit_index) hit_index = next_channel_start;
            continue;
        }

        if (current_channel < 1 || current_channel > 128)
        {
            hit_index = next_channel_start;
            continue;
        }

        for (uint32_t j = hit_index; j < next_channel_start; j++)
        {   
            uint32_t channel = current_channel - 1;
            uint32_t data = fData->TPC_TDC_Tv[j];
            uint32_t lot = fData->TPC_TDC_LOTv[j];

            // anl / software limit of 64 hits
            if (lot == 0 && tdcData[channel].size() < 64) tdcData[channel].emplace_back(data);

        }

        hit_index = next_channel_start;
    }

    auto & entry = tpcArray->emplace_back();
    entry.SetAll(adcData, tdcData);
}




void FrsReader::Reset()
{
    tpatArray->clear();
    scalerArray->clear();
    sciArray->clear();
    musicArray->clear();
    tpcArray->clear();
    memset(sciDE, 0, sizeof sciDE);
    memset(sciDT, 0, sizeof sciDT);
    for (int i = 0; i < 32; i++) sciMHTDC[i].clear();
    memset(musicE, 0, sizeof musicE);
    memset(musicT, 0, sizeof musicT);
    memset(adcData, 0, sizeof adcData);
    for (int i = 0; i < 128; i++) tdcData[i].clear();

}

ClassImp(FrsReader);
