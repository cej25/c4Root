// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

#include "TH1.h"
#include "TFile.h"

#include <iomanip>

// c4
#include "FatimaVmeData.h"
#include "FatimaVmeReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

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
    c4LOG(info, "");

    EXT_STR_h101_fatimavme_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_fatimavme, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    // bunch of stuff


    FairRootManager::Instance()->Register("FatimaVmeData", "FatimaVmeDataFolder", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    c4LOG(info, "FatimaVmeReader init setup completed.");

    return kTRUE;

}

Bool_t FatimaVmeReader::Read()
{
    c4LOG(debug1, "Event Data");

    if (!fData) return kTRUE;

    FatimaVmeData* FatimaHit = new FatimaVmeData();

    //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->fatimavme_ts_t[3]) << 48) + (((uint64_t)fData->fatimavme_ts_t[2]) << 32) + (((uint64_t)fData->fatimavme_ts_t[1]) << 16) + (uint64_t)(fData->fatimavme_ts_t[0]);
    if (wr_t == 0) return kTRUE;
    
    FatimaHit->Set_wr_t(wr_t);

    // currently nothing is being done with Scalers, so ignore for now


    #define QDC_BOARDS 5 // quick lazy testing only, put in some config
    for (int qdc = 0; qdc < QDC_BOARDS; qdc++)
    {
        Int_t board_id = fData->fatimavme_qdc[qdc].board_id;
        FatimaHit->Set_board_id(qdc, board_id);
        uint32_t board_time = fData->fatimavme_qdc[qdc].board_time;
        FatimaHit->Set_board_time(qdc, board_time);
        Int_t channel_mask = fData->fatimavme_qdc[qdc].channels;
        std::vector<int> channels_fired = Get_Channels(channel_mask);
        FatimaHit->Set_num_channels_fired(qdc, channels_fired.size());

        for (uint32_t channel = 0; channel < channels_fired.size(); channel++)
        {
            uint32_t QDC_time_coarse = fData->fatimavme_qdc[qdc].channel_timev[channel];
            FatimaHit->Set_channel_time_coarse(qdc, channels_fired[channel], QDC_time_coarse);

            double QDC_time_fine = (uint64_t)fData->fatimavme_qdc[qdc].channel_timev[channel] + ((uint64_t)(fData->fatimavme_qdc[qdc].chan_ext_timev[channel]) << 32) + fData->fatimavme_qdc[qdc].chan_fine_timev[channel] / 1024.;
            FatimaHit->Set_channel_time_fine(qdc, channels_fired[channel], QDC_time_fine);

            uint32_t QLong_raw = fData->fatimavme_qdc[qdc].qlongv[channel];
            FatimaHit->Set_channel_QLong(qdc, channels_fired[channel], QLong_raw);

            uint32_t QShort_raw = fData->fatimavme_qdc[qdc].qshortv[channel];
            FatimaHit->Set_channel_QShort(qdc, channels_fired[channel], QShort_raw);

        }

    }

    #define TDC_BOARDS 2 // quick lazy testing only, put in some config
    for (int tdc = 0; tdc < TDC_BOARDS; tdc++)
    {
        int hit_index = 0;
        for (uint32_t channel_index = 0; channel_index < fData->fatimavme_tdc[tdc]._nM; channel_index++)
        {
            int current_channel = fData->fatimavme_tdc[tdc]._nMI[channel_index]; // channel to read now!
            int next_channel_start = fData->fatimavme_tdc[tdc]._nME[channel_index];

            for (uint32_t j = hit_index; j < next_channel_start; j++)
            {
                v1290_channel.emplace_back(current_channel);
                v1290_data.emplace_back(fData->fatimavme_tdc[tdc]._data[j]);
                v1290_lot.emplace_back(fData->fatimavme_tdc[tdc]._leadOrTrailv[j]);
            }

            hit_index = next_channel_start;

        }

        FatimaHit->Set_v1290_channel(tdc, v1290_channel);
        FatimaHit->Set_v1290_data(tdc, v1290_data);
        FatimaHit->Set_v1290_lot(tdc, v1290_lot);
    }
    







    new ((*fArray)[fArray->GetEntriesFast()]) FatimaVmeData(*FatimaHit);

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
    fArray->Clear();
    //c4LOG(info, Form("%d events read.", fNEvent));
}


ClassImp(FatimaVmeReader)