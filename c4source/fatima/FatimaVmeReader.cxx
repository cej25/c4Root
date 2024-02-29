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


    // do some stuff

    for (int qdc = 0; qdc < FATIMA_QDC_BOARDS; qdc++)
    {
        board_id = fData->fatimavme_qdc[qdc].board_id;
        channel_mask = fData->fatimavme_qdc[qdc].channels; 
        if (board_id != 13) // hardcode??
        {
            for (int j = 7; j >= 0; j--)
            {
                if (channel_mask >= pow(2, j))
                {
                    if (wired_QDC(board_id, j)) // load qdc_alloc from somewhere
                    {
                        Fired_QDC_Channels[num_channels_fired][0] = board_id;
                        Fired_QDC_Channels[num_channels_fired][1] = j;
                        num_channels_fired++;
                    }
                    else
                    {
                        Fired_QDC_Channels[num_channels_fired][0] = board_id;
                        Fired_QDC_Channels[num_channels_fired][1] = -1;
                        num_channels_fired++;
                    }
                    channel_mask -= pow(2, j);
                }
            }

            int active_channel = 0;
            int active_board = 0;
            int active_det = 0;
            double fine_time = 0;

            for (int i = (num_channels_fired - 1); i >= 0; i--)
            {
                if (Fired_QDC_Channels[i][1] == -1)
                {
                    // bad channel?
                }
                else
                {
                    active_board = Fired_QDC_Channels[i][0];
                    active_channel = Fired_QDC_Channels[i][1];
                    active_det = det_ID_QDC[active_board][active_channel];

                    det_ids_QDC[fired_QDC_amount] = active_det;

                    // now we go through the data slightly differently
                    // (perhaps we can change the unpacker?)
                    QDC_Time_Coarse[fired_QDC_amount] = fData->fatimavme_qdc[qdc]

                }
            }



        }
    }
    



     //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->fatimavme_ts_t[3]) << 48) + (((uint64_t)fData->fatimavme_ts_t[2]) << 32) + (((uint64_t)fData->fatimavme_ts_t[1]) << 16) + (uint64_t)(fData->fatimavme_ts_t[0]);

    for (/*loop over tdcs fired*/)
    {
        for (/*loop over tdcs fired again*/)
        {
            // stuff trues into a bool array 
        }
    }

    


    // CEJ change later obviously
    if (wr_t != 0)
    {
       new ((*fArray)[fArray->GetEntriesFast()]) FatimaVmeData(
                    wr_t); 
    }
   

    fNEvent++;
    return kTRUE;


}

void FatimaVmeReader::Reset()
{
    fArray->Clear();
}


ClassImp(FatimaVmeReader)