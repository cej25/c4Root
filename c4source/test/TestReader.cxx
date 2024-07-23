#include "FairLogger.h"
#include "FairRootManager.h"

#include "TestReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_test.h"
}

TestReader::TestReader(EXT_STR_h101_test_onion* data, size_t offset)
    :   c4Reader("TestReader")
    ,   fNEvent(0)
    ,   fData(data)
    ,   fOffset(offset)
    ,   fOnline(kFALSE)
{

}

TestReader::~TestReader()
{
}

Bool_t TestReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_test_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_test, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    fatima_data = new FatimaData[4];
    // for (int i = 0; i < 4; i++) fatima_data[i] = fData->fatima_data[i]; // i actually think this does nothing


    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

Bool_t TestReader::Read() //do fine time here:
{
    // auto start = std::chrono::high_resolution_clock::now();

    if (!fData) return kTRUE;

    /*if ((fNEvent==fine_time_calibration_after)  & (!fine_time_calibration_set)){
        DoFineTimeCalibration();
        if (fine_time_calibration_save) WriteFineTimeHistosToFile();
    }*/
    
    //whiterabbit timestamp:
    // wr_t = (((uint64_t)fData->fatima_ts_t[3]) << 48) + (((uint64_t)fData->fatima_ts_t[2]) << 32) + (((uint64_t)fData->fatima_ts_t[1]) << 16) + (uint64_t)(fData->fatima_ts_t[0]);
    
    // for (int it_board_number = 0; it_board_number < NBoards; it_board_number++)
    // { //per board:

    //     uint16_t trig =  fData->fatima_tamex[it_board_number].trig;       
    //     if (fData->fatima_tamex[it_board_number].event_size == 0) continue; // empty event skip
        
    //     last_word_read_was_epoch = false;
    //     last_channel_read = 0;

    //     uint32_t previous_epoch_word = 0; // last seen epoch word

    //     fatima_last_lead_hit_struct last_tdc_hit; // initialized and reset - this keeps the information of the last lead that was seen
    //     last_tdc_hit.hit=false;
    //     last_tdc_hit.lead_epoch_counter = 0;
    //     last_tdc_hit.lead_coarse_T = 0;
    //     last_tdc_hit.lead_fine_T = 0;

    //     accepted_trigger_time = 0;


    //     //c4LOG(info,"\n\n\n\n New event:");
    //     //c4LOG(info,Form("Board_id = %i",it_board_number));
    //     //c4LOG(info,Form("event size: %i",fData->fatima_tamex[it_board_number].event_size));
    //     //c4LOG(info,Form("time_epoch =  %i, time_coarse = %i, time_fine = %i, time_edge = %i, time_channel = %i",fData->fatima_tamex[it_board_number].time_epoch,fData->fatima_tamex[it_board_number].time_coarse,fData->fatima_tamex[it_board_number].time_fine,fData->fatima_tamex[it_board_number].time_edge,fData->fatima_tamex[it_board_number].time_channel));
    //     //c4LOG(info,"Here comes data:");

    //     for (int it_hits = 0; it_hits < fData->fatima_tamex[it_board_number].event_size/4 - 3 ; it_hits++)
    //     {
    //         // now operating under the assumption 16.01.2024:
    //         /*
    //         the TAMEX readout happens channel after channel with increasing channel number. Multiple hits within one channel are time ordered.
    //         e.g.: ch1-hit1, ch1-hit2, ch1-hit3, ch2-hit1, ch2-hit2, ch3-hit1, ....., chN-hitN.
    //         from M Reese 08.12.23
    //         */

    //         // check if arrays are overflowing. These could be placed outside this inner loop, but now it sums up the number of lost events in case they are not equal. This indicates an error in UCESB/MBS i believe if this fails.
    //         if (fData->fatima_tamex[it_board_number].time_epoch <= it_hits) {fNevents_skipped++; continue;}
    //         if (fData->fatima_tamex[it_board_number].time_fine <= it_hits) {fNevents_skipped++; continue;}
    //         if (fData->fatima_tamex[it_board_number].time_coarse <= it_hits) {fNevents_skipped++; continue;}
    //         //the length of the arrays should be equal. 
    //         if (!(fData->fatima_tamex[it_board_number].time_coarse == fData->fatima_tamex[it_board_number].time_fine && fData->fatima_tamex[it_board_number].time_coarse == fData->fatima_tamex[it_board_number].time_epoch)) {fNevents_skipped++; continue;}

    //         //any time you see an epoch - this epoch will apply to the next time data words until a new epoch word is written. If the following data in the buffer is another channel then it must be preceeded with another epoch. 
    //         if (fData->fatima_tamex[it_board_number].time_epochv[it_hits] != 0)
    //         {
    //                 previous_epoch_word = fData->fatima_tamex[it_board_number].time_epochv[it_hits] & 0xFFFFFFF;
    //                 //if (it_board_number == 1) c4LOG(info,Form("Found epoch for ch = %i, e = %i",next_channel,fData->fatima_tamex[it_board_number].time_epochv[it_hits] & 0xFFFFFFF));
    //                 fNepochwordsread++;
    //                 last_word_read_was_epoch = true;
    //                 continue;
    //         }


    //         //from this point we should have seen an epoch for channel id.

    //         uint32_t channelid = fData->fatima_tamex[it_board_number].time_channelv[it_hits] & 0x7F; // 0-32
            
    //         //if (it_board_number == 1) c4LOG(info,Form("ch = %i, coarse = %i, edge = %i", channelid, fData->fatima_tamex[it_board_number].time_coarsev[it_hits], fData->fatima_tamex[it_board_number].time_edgev[it_hits]));

    //         if (fData->fatima_tamex[it_board_number].time_finev[it_hits] == 0x3FF) {fNevents_TAMEX_fail[it_board_number][channelid]++; continue;} // this happens if TAMEX loses the fine time - skip it

    //         if (channelid != 0 && channelid != last_channel_read && !last_word_read_was_epoch){fNevents_lacking_epoch[it_board_number][channelid]++; c4LOG(debug2, "Event lacking epoch.");} // if the channel has changed but no epoch word was seen in between, channel 0 is always the first one so dont check if that s the case.

    //         if (!(channelid >= last_channel_read)) {c4LOG(fatal, Form("Data format is inconcistent with assumption: Channels are not read out in increasing order. This channel = %i, last channel = %i",channelid,last_channel_read));}

        
    //         last_word_read_was_epoch = false;
    //         last_channel_read = channelid;

    //         bool is_leading = fData->fatima_tamex[it_board_number].time_edgev[it_hits] & 0x1;
            
    //         //Fill fine times and skip.
    //         if (!fine_time_calibration_set && is_leading)
    //         {
    //             fine_time_hits[it_board_number][channelid]->Fill(fData->fatima_tamex[it_board_number].time_finev[it_hits]);
    //             continue;
    //         }


    //         uint32_t coarse_T = fData->fatima_tamex[it_board_number].time_coarsev[it_hits] & 0x7FF;
    //         double fine_T = GetFineTime(fData->fatima_tamex[it_board_number].time_finev[it_hits],it_board_number,channelid);

    //         if (channelid == 0) 
    //         {
    //             accepted_trigger_time = ((double)previous_epoch_word)*10.24e3 + ((double)coarse_T)*5.0 - (double)fine_T; // round it off to ns resolution
    //             continue;
    //         } // skip channel 0 for now. This is the trigger information. The trigger time is kept, the wr timestamp is corrected by the difference of the hit and the acc trigger time.

    //         //if(it_board_number == 1) c4LOG(info,fData->fatima_tamex[it_board_number].time_edgev[it_hits]);

    //         if (is_leading)
    //         { // rise signal:
    //             //if (it_board_number == 1) c4LOG(info,Form("Found rise: ch = %i, le = %i, lc = %i, lf = %f", channelid, previous_epoch_word,coarse_T,fine_T));
                
    //             //count number of double leads
    //             if (last_tdc_hit.hit) {fNevents_second_lead_seen[it_board_number][channelid]++;}
                
    //             last_tdc_hit.hit = true;
    //             last_tdc_hit.lead_epoch_counter = previous_epoch_word;
    //             last_tdc_hit.lead_coarse_T = coarse_T;
    //             last_tdc_hit.lead_fine_T = fine_T;

    //             fNleads_read[it_board_number][channelid]++;
    //             continue;
    //         }
    //         else if (!is_leading && last_tdc_hit.hit)
    //         { 
    //             //trail and rise are matched
    //             //if (it_board_number == 1) c4LOG(info,Form("Writing: ch = %i, le = %i lc = %i, lf = %f, te = %i tc = %i, tf = %f ",channelid,last_tdc_hit.lead_epoch_counter, last_tdc_hit.lead_coarse_T, last_tdc_hit.lead_fine_T,last_tdc_hit.lead_epoch_counter,coarse_T,fine_T));

    //             new ((*fArray)[fArray->GetEntriesFast()]) FatimaTwinpeaksData(
    //                 trig,
    //                 it_board_number,
    //                 channelid,
    //                 accepted_trigger_time,

    //                 last_tdc_hit.lead_epoch_counter,
    //                 last_tdc_hit.lead_coarse_T,
    //                 last_tdc_hit.lead_fine_T,

    //                 previous_epoch_word,
    //                 coarse_T,
    //                 fine_T,
                    
    //                 fData->fatima_ts_subsystem_id,
    //                 wr_t //+ 0*( (((int64_t)previous_epoch_word)*10.24e3 + ((int64_t)coarse_T)*5.0 - (int64_t)fine_T) - accepted_trigger_time) // corrected by the time difference to the acc trigger time
    //             );

                
    //             //reset:

    //             last_tdc_hit.hit=false;
    //             last_tdc_hit.lead_epoch_counter = 0;
    //             last_tdc_hit.lead_coarse_T = 0;
    //             last_tdc_hit.lead_fine_T = 0;
                
    //             fNmatched[it_board_number][channelid]++;
    //             fNtrails_read[it_board_number][channelid]++;

    //             continue;
    //         }
    //         else
    //         {
    //             // do nothing, trail found with no rise.
    //             fNevents_trail_seen_no_lead[it_board_number][channelid]++;
    //             fNtrails_read[it_board_number][channelid]++;
                
    //         }
    //     }

    // } // boards
    
    
        
    // fNEvent += 1;
    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // total_time_microsecs += duration.count();
    
    return kTRUE;
}



void TestReader::Reset()
{
   
}

ClassImp(TestReader)