#include "FairLogger.h"
#include "FairRootManager.h"

#include "FimpReader.h"
#include "c4Logger.h"

#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_fimp.h"
}

FimpReader::FimpReader(EXT_STR_h101_fimp_onion* data, size_t offset)
    : c4Reader("FimpReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fimpArray(new std::vector<FimpItem>)
{
}

FimpReader::~FimpReader() 
{
    c4LOG(info, "Counter: " << counter);
    c4LOG(info, "unmatched lead trail counter: " << lead_trail_unmatched_counter);
    c4LOG(info, "fNEvents: " << fNEvent);
}

Bool_t FimpReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
  
    EXT_STR_h101_fimp_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_fimp, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to setup structure information");
        return kFALSE;
    }

    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    // register output array in a tree
    mgr->RegisterAny("FimpData", fimpArray, !fOnline);

    fimpArray->clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t FimpReader::Read()
{
    fimpArray->clear();
    ctdc_data_store last_hit;

    uint64_t wr_t = (((uint64_t)fData->fimp_ts_t[3]) << 48) + 
    (((uint64_t)fData->fimp_ts_t[2]) << 32) + 
    (((uint64_t)fData->fimp_ts_t[1]) << 16) + 
    (uint64_t)(fData->fimp_ts_t[0]);

    uint32_t wr_id = fData->fimp_ts_subsystem_id;

    uint64_t trig_time_long = (((uint64_t)fData->fimp_data_trig_coarse_time_hi) << 32) +
                            ((uint64_t)fData->fimp_data_trig_coarse_time_lo);

    // coarse time
    int hit_index = 0;
    for (uint32_t channel_index = 0; channel_index < fData->fimp_data_time_coarseM; channel_index++)
    {
        int current_channel = fData->fimp_data_time_coarseMI[channel_index]; // channel to read now
        int next_channel_start = fData->fimp_data_time_coarseME[channel_index]; // read current channel data until this index

        for (uint32_t j = hit_index; j < next_channel_start; j++)
        {
            counter++;
            uint16_t coarse_time = fData->fimp_data_time_coarsev[j];
            uint16_t fine_time = fData->fimp_data_time_finev[j];
            bool leadOrTrail = fData->fimp_data_lead_or_trailv[j] & 0x1;
            uint16_t channel = (current_channel - leadOrTrail)/2;

            //std::cout << "channel: " << channel << std::endl;
            //std::cout << "leadOrTrail: " << leadOrTrail << std::endl;

            // trigger leading edge - maybe not necessary here
            if (channel == 128 && !leadOrTrail)
            {
                // do trigger stuff
            }
            else if (channel < 128)
            {
                // check == is_leading
                if (!leadOrTrail)
                {   
                    // 2 leads in a row
                    if (last_hit.leadOrTrail == 0) 
                    {
                        unmatchedLeads++;
                        c4LOG(warn, "Unmatched lead in FIMP data: " << unmatchedLeads);
                    }

                    last_hit.channel = channel;
                    last_hit.coarse_time = coarse_time;
                    last_hit.fine_time = fine_time;
                    last_hit.leadOrTrail = leadOrTrail;
                }
                else
                {   
                    // we start with a trail somehow
                    if (last_hit.leadOrTrail == -1) c4LOG(warn, "First data item is a trail");
                    else if (last_hit.leadOrTrail == 1) 
                    {
                        c4LOG(warn, "Two trails in a row");
                        continue;
                    }
                    else
                    {   
                        if (channel != last_hit.channel)
                        {
                            c4LOG(warn, "Couldn't match lead and trail channels!");
                            lead_trail_unmatched_counter++;
                            last_hit.channel = channel;
                            last_hit.coarse_time = coarse_time;
                            last_hit.fine_time = fine_time;
                            last_hit.leadOrTrail = leadOrTrail;
                            continue;
                        }
                        auto & entry = fimpArray->emplace_back();
                        entry.SetAll(wr_t, 
                                    wr_id,
                                    trig_time_long, 
                                    channel, 
                                    last_hit.coarse_time, // lead coarse
                                    last_hit.fine_time, // lead fine
                                    coarse_time, // trail coarse
                                    fine_time // trail fine
                                    );

                        last_hit.channel = channel;
                        last_hit.coarse_time = coarse_time;
                        last_hit.fine_time = fine_time;
                        last_hit.leadOrTrail = leadOrTrail;
                    }
                }

            }
            else continue; // dummy data

        }
        hit_index = next_channel_start;
    }

    fNEvent++;

    return kTRUE;
}

// You must clear any arrays and vectors you use or things will get weird
void FimpReader::ZeroArrays()
{ 

}

void FimpReader::ClearVectors()
{

}

void FimpReader::Reset()
{
    ZeroArrays();
    ClearVectors();
}

ClassImp(FimpReader);
