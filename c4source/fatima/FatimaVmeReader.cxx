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

#include "TH1.h"
#include "TFile.h"

#include <iomanip>

// c4
#include "FatimaVmeData.h"
#include "FatimaVmeReader.h"
#include "TFatimaVmeConfiguration.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"
#include <set>

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_fatimavme.h"
}

FatimaVmeReader::FatimaVmeReader(EXT_STR_h101_fatimavme_onion* data, size_t offset)
    :   c4Reader("FatimaVmeReader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
    ,   fArray(new TClonesArray("FatimaVmeData"))
    ,   qdcArray(new std::vector<FatimaVmeQDCItem>)
    ,   tdcArray(new std::vector<FatimaVmeTDCItem>)
{
}

FatimaVmeReader::~FatimaVmeReader()
{   
    c4LOG(info, "");
    if (fArray) delete fArray;
}

Bool_t FatimaVmeReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;

    EXT_STR_h101_fatimavme_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_fatimavme, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // bunch of stuff


    FairRootManager::Instance()->Register("FatimaVmeData", "FatimaVmeDataFolder", fArray, !fOnline);
    FairRootManager::Instance()->RegisterAny("FatimaVmeQDCData", qdcArray, !fOnline);
    FairRootManager::Instance()->RegisterAny("FatimaVmeTDCData", tdcArray, !fOnline);

    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    TFatimaVmeConfiguration const* fatvme_conf = TFatimaVmeConfiguration::GetInstance();
    num_qdc_boards = fatvme_conf->NQDCBoards();
    num_tdc_boards = fatvme_conf->NTDCBoards();
    dets_qdc = fatvme_conf->QDCMapping();
    dets_tdc = fatvme_conf->TDCMapping();

    return kTRUE;

}

Bool_t FatimaVmeReader::Read()
{
    if (!fData) return kTRUE;
    qdcArray->clear();
    tdcArray->clear();
    
    
    //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->fatimavme_ts_t[3]) << 48) + (((uint64_t)fData->fatimavme_ts_t[2]) << 32) + (((uint64_t)fData->fatimavme_ts_t[1]) << 16) + (uint64_t)(fData->fatimavme_ts_t[0]);
    // if (wr_t == 0) return kTRUE;

    uint32_t wr_subsystem_id = fData->fatimavme_ts_subsystem_id;

    int qdcs_fired = 0;
    
    for (int qdc = 0; qdc < 5; qdc++)
    {
        Int_t board_id = fData->fatimavme_qdc[qdc]._board_id;
        
        Int_t channel_mask = fData->fatimavme_qdc[qdc]._channels;
        std::vector<int> channels_fired = Get_Channels(channel_mask);

        for (uint32_t channel = 0; channel < channels_fired.size(); channel++)
        {  
            auto & entry = qdcArray->emplace_back();

            int current_detector = dets_qdc[std::make_pair(board_id, channels_fired[channel])];
            //qdc_detectors.emplace_back(current_detector);
            
            uint32_t ct = fData->fatimavme_qdc[qdc]._channel_timev[channel];
            //QDC_time_coarse.emplace_back(fData->fatimavme_qdc[qdc]._channel_timev[channel]);

            uint64_t ft = (uint64_t)fData->fatimavme_qdc[qdc]._channel_timev[channel] + ((uint64_t)(fData->fatimavme_qdc[qdc]._chan_ext_timev[channel]) << 32) + fData->fatimavme_qdc[qdc]._chan_fine_timev[channel] / 1024.;
            //QDC_time_fine.emplace_back((uint64_t)fData->fatimavme_qdc[qdc]._channel_timev[channel] + ((uint64_t)(fData->fatimavme_qdc[qdc]._chan_ext_timev[channel]) << 32) + fData->fatimavme_qdc[qdc]._chan_fine_timev[channel] / 1024.);

            uint32_t qlr = fData->fatimavme_qdc[qdc]._qlongv[channel];
            //QLong_raw.emplace_back(fData->fatimavme_qdc[qdc]._qlongv[channel]);

            uint32_t qsr = fData->fatimavme_qdc[qdc]._qlongv[channel];
            //QShort_raw.emplace_back(fData->fatimavme_qdc[qdc]._qshortv[channel]);

            entry.SetAll(wr_t, current_detector, ct, ft, qlr, qsr);

            qdcs_fired++;
        }

    }
    
    int tdcs_fired = 0;
    
    for (int tdc = 0; tdc < 2; tdc++)
    {
        int geo = fData->fatimavme_tdc[tdc]._geo;
        
        int hit_index = 0;
        for (uint32_t channel_index = 0; channel_index < fData->fatimavme_tdc[tdc]._measurement_nM; channel_index++)
        {
            int current_channel = fData->fatimavme_tdc[tdc]._measurement_nMI[channel_index]; // channel to read now!
            int next_channel_start = fData->fatimavme_tdc[tdc]._measurement_nME[channel_index];

            int current_detector = dets_tdc[std::make_pair(geo, current_channel)];

            for (uint32_t j = hit_index; j < next_channel_start; j++)
            {
                auto & entry = tdcArray->emplace_back();
                //tdc_detectors.emplace_back(current_detector);
                uint32_t data = fData->fatimavme_tdc[tdc]._measurement_data[j];
                uint8_t lot = fData->fatimavme_tdc[tdc]._measurement_leadOrTrailv[j];
                //v1290_data.emplace_back(fData->fatimavme_tdc[tdc]._data[j]);
                //v1290_lot.emplace_back(fData->fatimavme_tdc[tdc]._leadOrTrailv[j]);


                entry.SetAll(wr_t, wr_subsystem_id, current_detector, data, lot);
                tdcs_fired++;
            }

            hit_index = next_channel_start;

        }

    }
    
    /*new ((*fArray)[fArray->GetEntriesFast()]) FatimaVmeData(
                    wr_t,
                    qdc_detectors,
                    QDC_time_coarse,
                    QDC_time_fine,
                    QLong_raw,
                    QShort_raw,
                    qdcs_fired,
                    tdc_detectors,
                    v1290_data,
                    v1290_lot,
                    tdcs_fired
                );*/

    fNEvent++;
    return kTRUE;
}


// CEJ: for 8 channel mode at the moment
std::vector<int> FatimaVmeReader::Get_Channels(Int_t channel_mask)
{
    std::vector<int> channels;

    for (int i = 7; i >= 0; i--)
    {
        if (channel_mask >= pow(2, i))
        {
            channels.push_back(i);
            channel_mask -= pow(2, i);
        }
    }

    std::sort(channels.begin(), channels.end());

    return channels;
}

void FatimaVmeReader::Reset()
{   
    tdc_detectors.clear();
    v1290_data.clear();
    v1290_lot.clear();
    qdc_detectors.clear();
    QDC_time_coarse.clear();
    QDC_time_fine.clear();
    QLong_raw.clear();
    QShort_raw.clear();
    fArray->Clear();
    //c4LOG(info, Form("%d events read.", fNEvent));
}


ClassImp(FatimaVmeReader)
