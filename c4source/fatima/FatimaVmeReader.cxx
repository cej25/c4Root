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
    c4LOG(debug2, "Event Data");

    if (!fData) return kTRUE;

    FatimaVmeData* FatimaHit = new FatimaVmeData();

    //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->fatimavme_ts_t[3]) << 48) + (((uint64_t)fData->fatimavme_ts_t[2]) << 32) + (((uint64_t)fData->fatimavme_ts_t[1]) << 16) + (uint64_t)(fData->fatimavme_ts_t[0]);
    if (wr_t == 0) return kTRUE;
    
    FatimaHit->Set_wr_t(wr_t);

    // currently nothing is being done with Scalers, so ignore for now

    std::vector<uint32_t> qdc_detectors;
    std::vector<uint32_t> QDC_time_coarse;
    std::vector<uint64_t> QDC_time_fine;
    std::vector<uint32_t> QLong_raw;
    std::vector<uint32_t> QShort_raw;
    int qdcs_fired = 0;

    //std::cout << "num qdc boards from config: " << num_qdc_boards << std::endl;
    for (int qdc = 0; qdc < 4; qdc++)
    {
        Int_t board_id = fData->fatimavme_qdc[qdc].board_id;
        
        Int_t channel_mask = fData->fatimavme_qdc[qdc].channels;
        std::vector<int> channels_fired = Get_Channels(channel_mask);

        for (uint32_t channel = 0; channel < channels_fired.size(); channel++)
        {  
            int current_detector = dets_qdc[std::make_pair(board_id, channels_fired[channel])];
            qdc_detectors.emplace_back(current_detector);

            QDC_time_coarse.emplace_back(fData->fatimavme_qdc[qdc].channel_timev[channel]);

            QDC_time_fine.emplace_back((uint64_t)fData->fatimavme_qdc[qdc].channel_timev[channel] + ((uint64_t)(fData->fatimavme_qdc[qdc].chan_ext_timev[channel]) << 32) + fData->fatimavme_qdc[qdc].chan_fine_timev[channel] / 1024.);

            QLong_raw.emplace_back(fData->fatimavme_qdc[qdc].qlongv[channel]);

            QShort_raw.emplace_back(fData->fatimavme_qdc[qdc].qshortv[channel]);

            qdcs_fired++;
        }

    }

    FatimaHit->Set_QDC_detectors(qdc_detectors);
    FatimaHit->Set_QDC_coarse_time(QDC_time_coarse);
    FatimaHit->Set_QDC_fine_time(QDC_time_fine);
    FatimaHit->Set_QLong_raw(QLong_raw);
    FatimaHit->Set_QShort_raw(QShort_raw);
    FatimaHit->Set_QDCs_fired(qdcs_fired);

    int tdcs_fired = 0;
    std::vector<uint32_t> tdc_detectors;
    std::vector<uint32_t> v1290_data;
    std::vector<uint32_t> v1290_lot;


    for (int tdc = 0; tdc < 2; tdc++)
    {
        int geo = fData->fatimavme_tdc[tdc]._geo;
        
        int hit_index = 0;
        for (uint32_t channel_index = 0; channel_index < fData->fatimavme_tdc[tdc]._nM; channel_index++)
        {
            int current_channel = fData->fatimavme_tdc[tdc]._nMI[channel_index]; // channel to read now!
            int next_channel_start = fData->fatimavme_tdc[tdc]._nME[channel_index];

            int current_detector = dets_tdc[std::make_pair(geo, current_channel)];

            for (uint32_t j = hit_index; j < next_channel_start; j++)
            {
                tdc_detectors.emplace_back(current_detector);
                v1290_data.emplace_back(fData->fatimavme_tdc[tdc]._data[j]);
                v1290_lot.emplace_back(fData->fatimavme_tdc[tdc]._leadOrTrailv[j]);

                tdcs_fired++;
            }

            hit_index = next_channel_start;

        }

    }

    FatimaHit->Set_TDC_detectors(tdc_detectors);
    FatimaHit->Set_v1290_data(v1290_data);
    FatimaHit->Set_v1290_lot(v1290_lot);
    FatimaHit->Set_TDCs_fired(tdcs_fired);
    

    new ((*fArray)[fArray->GetEntriesFast()]) FatimaVmeData(*FatimaHit);

    fNEvent++;
    return kTRUE;


}

void FatimaVmeReader::Set_Allocation(TString& filepath)
{
    std::ifstream file(filepath);
    std::string line;
    std::set<int> qdc_boards;
    std::set<int> tdc_boards;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss;
        std::string signal;
        int det, qdc_board, qdc_chan, tdc_board, tdc_chan;

        iss >> signal;

        // detector signal
        if (isdigit(signal[0]))
        {
            det = std::stoi(signal);
            iss >> qdc_board >> qdc_chan >> tdc_board >> tdc_chan;

            if (qdc_board > -1) qdc_boards.insert(qdc_board);
            if (tdc_board > -1) tdc_boards.insert(tdc_board); 

            dets_qdc[std::make_pair(qdc_board, qdc_chan)] = det;
            dets_tdc[std::make_pair(tdc_board, tdc_chan)] = det;
        }
        else
        {
            if (signal == "TimeMachineU")
            {
                iss >> qdc_board >> qdc_chan >> tdc_board >> tdc_chan;
                dets_qdc[std::make_pair(qdc_board, qdc_chan)] = TM_U;
                dets_tdc[std::make_pair(tdc_board, tdc_chan)] = TM_U;
            }
            else if (signal == "TimeMachineD")
            {
                iss >> qdc_board >> qdc_chan >> tdc_board >> tdc_chan;
                dets_qdc[std::make_pair(qdc_board, qdc_chan)] = TM_D;
                dets_tdc[std::make_pair(tdc_board, tdc_chan)] = TM_D;
            } 
            else if (signal == "SC41L_A")
            {
                iss >> qdc_board >> qdc_chan >> tdc_board >> tdc_chan;
                dets_qdc[std::make_pair(qdc_board, qdc_chan)] = SC41L_A;
                dets_tdc[std::make_pair(tdc_board, tdc_chan)] = SC41L_A;
            }
            else if (signal == "SC41R_A")
            {
                iss >> qdc_board >> qdc_chan >> tdc_board >> tdc_chan;
                dets_qdc[std::make_pair(qdc_board, qdc_chan)] = SC41R_A;
                dets_tdc[std::make_pair(tdc_board, tdc_chan)] = SC41R_A;
            }
            else if (signal == "SC41L_D")
            {
                iss >> qdc_board >> qdc_chan >> tdc_board >> tdc_chan;
                dets_qdc[std::make_pair(qdc_board, qdc_chan)] = SC41L_D;
                dets_tdc[std::make_pair(tdc_board, tdc_chan)] = SC41L_D;
            }
            else if (signal == "SC41R_D")
            {
                iss >> qdc_board >> qdc_chan >> tdc_board >> tdc_chan;
                dets_qdc[std::make_pair(qdc_board, qdc_chan)] = SC41R_D;
                dets_tdc[std::make_pair(tdc_board, tdc_chan)] = SC41R_D;
            }
        }

    }

    num_qdc_boards = qdc_boards.size();
    num_tdc_boards = tdc_boards.size();
    
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
