// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "bPlastTamexData.h"
#include "bPlastReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_bplast.h"
}

bPlastReader::bPlastReader(EXT_STR_h101_BPLAST_onion* data, size_t offset)
    : c4Reader("bPlastReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("bPlastTamexData"))
{
}

bPlastReader::~bPlastReader() { delete fArray; }

Bool_t bPlastReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_BPLAST_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_BPLAST, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }
    
    // Register output array in a tree
    FairRootManager::Instance()->Register("bPlastTamexData", "bPlast Tamex Data", fArray, !fOnline);
    fArray->Clear();
    
    memset(fData, 0, sizeof *fData);

    return kTRUE;
}
//

struct fineTimeCalib
{
  int min;
  int max;
  double lookup[600];
};

fineTimeCalib calibrations[NCards][NChannels];

double getFineTime(int card, int channel, int fine, double scale = 5000.)
{
  if (fine < calibrations[card][channel].min)
    return 0;
  if (fine > calibrations[card][channel].max)
    return scale;
  return (calibrations[card][channel].lookup[fine]) * scale;
}

Bool_t bPlastReader::Read()
{
    c4LOG(debug1, "Event Data");

    // Would you look at the time!
    plastic_ts_t = (((uint64_t)fData->plastic_ts_t[3]) << 48) + (((uint64_t)fData->plastic_ts_t[2]) << 32) + (((uint64_t)fData->plastic_ts_t[1]) << 16) + (uint64_t)(fData->plastic_ts_t[0]);


    // TAMEX Epoch correction
    std::array<double, NChannel> leads = {0};
    std::array<double, NChannel> trails = {0};
    std::array<double, NChannel> tot = {0};
    std::array<double, NChannel> epoch = {0};

    // BPLAST_TAMEX_MODULES
    for (int det = 0; NCards < 4; det++)
    {   
        int32_t epoch_base = 0;
        int32_t last_epoch = 0;

        // BPLAST_TAMEX_HITS
        for (int hit = 0; hit < plastic_tamex[det].event_size/4 - 3; hit++) // this will have to change as the variable size is indicated by the variable leading it, we will usually set hits to 5
        {  

            // Time correction

            if (plastic_tamex[det].time_epochv[hit] !=0){
                last_epoch = plastic_tamex[det].time_epochv[hit];
            }
            else{
                if (plastic_tamex[det].time_finev[hit] == 0x3ff) continue;
                int channel = plastic_tamex[det].time_channelv[hit];
                if (channel >= NChannel) continue;

                if (last_epoch != 0){
                    if (epoch_base == 0 && channel == 0){
                        epoch_base = last_epoch;
                    }
                    else if (epoch_base == 0){
                        throw std::runtime_error("Unexpected TDC epoch before trigger");
                    }
                    epoch[channel] = last_epoch - epoch_base;
                    last_epoch = 0;
                }
            }

            // Calculate time event time

            double time = (epoch[channel] * 1024e4) + plastic_tamex[det].time_coarsev[hit] * 5000 - getFineTime(cardid, channel, plastic_tamex[det].time_finev[hit]);

            // Leading edge = 1

            if (plastic_tamex[det].time_edgev[hit] == 1){
                leads[channel] = time;
            }

            // Trailing edge = 0

            else {
                if (leads[channel]){
                    trails[channel] = time;
                    tot[channel] = time - leads[channel];
                }

            // Fill TAMEX data arrays

            new ((*fArray)[fArray->GetEntriesFast()]) bPlastTamexData(
                fData->leads[channel],
                fData->trails[channel],
                fData->tot[channel],
                fData->channel,
                fData->epoch[channel],
                fData->plastic_ts_subsystem_id,
                plastic_ts_t
            );

            leads[channel] = 0;
            trails[channel] = 0;
            }
        } 
    }
    fNEvent += 1;
    return kTRUE;    
}


void bPlastReader::Reset()
{
    // reset output array
    fArray->Clear();
}

ClassImp(bPlastReader);