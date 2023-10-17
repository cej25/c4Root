// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

// c4
#include "FatimaTwinpeaksData.h"
#include "FatimaReader.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "ext_data_struct_info.hh"

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_fatima.h"
}

FatimaReader::FatimaReader(EXT_STR_h101_FATIMA_onion* data, size_t offset)
    : c4Reader("FatimaReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("FatimaTwinpeaksData"))
{
}

FatimaReader::~FatimaReader() { 
    
    c4LOG(info, Form("Epochs read %i",(int)fNepochwordsread));
    c4LOG(info, Form("Trails read %i",(int)fNtrails_read));
    c4LOG(info, Form("Leads read  %i",(int)fNleads_read));
    c4LOG(info, Form("Matches     %i",(int)fNmatched));
    
    for (int i = 0; i < NBoards; i++) {

        for (int j = 0; j < NChannels; j++) {
            delete[] fine_time_calibration_coeffs[i][j];
            fine_time_calibration_coeffs[i][j] = nullptr;
        }
        delete[] fine_time_calibration_coeffs[i];
        fine_time_calibration_coeffs[i] = nullptr
        
        if (fine_time_hits[i] != nullptr){
            delete[] fine_time_hits[i];
            fine_time_hits[i] = nullptr;
        }

        if (last_hits[i] != nullptr) {
            delete[] last_hits[i];
            last_hits[i] = nullptr;  // Set the pointer to nullptr after deletion
        }
    }
    delete[] fine_time_calibration_coeffs;
    delete[] fine_time_hits;
    delete[] last_hits;


    delete fArray;

    c4LOG(info, "Destroyed FatimaReader properly.");

}

Bool_t FatimaReader::Init(ext_data_struct_info* a_struct_info)
{
    Int_t ok;
    c4LOG(info, "");

    EXT_STR_h101_FATIMA_ITEMS_INFO(ok, *a_struct_info, fOffset, EXT_STR_h101_FATIMA, 0);

    if (!ok)
    {
        c4LOG(error, "Failed to set up structure information");
        return kFALSE;
    }

    last_hits = new last_lead_hit_struct*[NBoards];
    for (int i = 0; i < NBoards; i++) last_hits[i] = new last_lead_hit_struct[NChannels];

    for (int i = 0; i < NBoards; i++) {
        for (int j = 0; j < NChannels; j++) {
            last_hits[i][j].hit = false;
            last_hits[i][j].lead_coarse_T = 0;
            last_hits[i][j].lead_fine_T = 0;
            last_hits[i][j].lead_epoch_counter = 0;
            
            
            fine_time_hits[i][j] = new TH1I(Form("fine_time_calibration_coeffs_%i_%i",i,j),"Fine time calibration hist",1024,0,1024); //channel size of fine time
            for (int k = 0; k<1024; k++) fine_time_calibration_coeffs[i][j][k] = 0.0;
        }
    }


    // Register output array in a tree
    FairRootManager::Instance()->Register("FatimaTwinpeaksData", "Fatima Twinpeaks Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    return kTRUE;
}

void FatimaReader::DoFineTimeCalibrationEveryN(){
    for (int i = 0; i < NBoards; i++) {
        for (int j = 0; j < NChannels; j++) {
            int running_sum = 0;
            int total_counts = fine_time_hits->GetEntries();
            for (int k = 0; k < 1024; k++) {
                running_sum += fine_time_hits->GetBinContent(k+1); //bin 0 is the underflow bin, hence we start at [1,1024].
                fine_time_calibration_coeffs[i][j][k] = TAMEX_fine_time_clock*(double)running_sum/(double)total_counts;
            }
        }
    }
    fine_time_calibration_set = true;
}

double FatimaReader::GetFineTime(int tdc_fine_time_channel, int board_id, int channel_id){
    return fine_time_calibration_coeffs[board_id][channel_id][tdc_fine_time_channel];
}


void FatimaReader::WriteFineTimeCalibrationsToFile(TString filename){
    if (!fine_time_calibration_set) {
        c4LOG(info,"Fine time calibrations not set, cannot write to file.");
        return;
    }
    
    std::ofstream outputfile(filename);

    outputfile << "#TAMEX WhiteRabbit Fine time calibrations\n";
    outputfile << "#Number of boards    Number of channels \n";
    outputfile << NBoards << "  " << NChannels << std::endl;
    outputfile << "#coeffs , 0-1024" << std::endl;

    for (int i = 0; i < NBoards; i++) {
        outputfile << "Board number: " << i << std::endl;
        for (int j = 0; j < NChannels; j++) {
            int running_sum = 0;
            int total_counts = fine_time_hits->GetEntries();
            for (int k = 0; k < 1024; k++) {
                outputfile << std::setprecision(5) << fine_time_calibration_coeffs[i][j][k] << " ";
            }
            outputfile << std::endl;
        }
    }

    outputfile.close();
}
void FatimaReader::ReadFineTimeCalibrationFromFile(TString filename){
    return;
}

Bool_t FatimaReader::Read() //do fine time here:
{
    c4LOG(debug1, "Event Data");

    if (!fData) return kTRUE;

    if (fNEvent % fine_time_calibration_freq == 0 & fNEvent!=0){
        DoFineTimeCalibrationEveryN();
    }

    //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->fatima_ts_t[3]) << 48) + (((uint64_t)fData->fatima_ts_t[2]) << 32) + (((uint64_t)fData->fatima_ts_t[1]) << 16) + (uint64_t)(fData->fatima_ts_t[0]);
    

    for (int it_board_number = 0; it_board_number < NBoards; it_board_number++){ //per board:
        
        last_epoch = 0;
        look_ahead_counter = 0;
        //reset last hits?

        if (fData->fatima_tamex[it_board_number].event_size == 0) continue; // empty event skip

        //std::cout << fData->fatima_tamex[it_board_number].event_size << std::endl;

        for (int it_hits = 0; it_hits < fData->fatima_tamex[it_board_number].event_size/4 - 3 ; it_hits++){ // if no data is written this loop never starts (?)
            //this distinguishes epoch words from time words by checking if the epoch/coarse and fine words are zero. This would potentially be a problem if epoch truly is zero...

            //look ahead to grab epoch:
            if (last_epoch == 0 && fData->fatima_tamex[it_board_number].time_epochv[it_hits] == 0){
                look_ahead_counter ++; //keep track of how far ahead you skip.
                continue;
            }else if (last_epoch == 0 && fData->fatima_tamex[it_board_number].time_epochv[it_hits] != 0){
                last_epoch = fData->fatima_tamex[it_board_number].time_epochv[it_hits]; //subtract one?
                it_hits = it_hits - look_ahead_counter; // jumps back
                fNepochwordsread ++;
            }else if (last_epoch != 0 && fData->fatima_tamex[it_board_number].time_epochv[it_hits] != 0){ // next epoch:
                last_epoch = 0;
                look_ahead_counter = 0;
                continue;
            }

            //should not pass this point if this is an epoch:
            //if ((fData->fatima_tamex[it_board_number].time_epochv[it_hits] !=0)  | (last_epoch == 0)) {c4LOG(fatal,"Epoch is non zero!");}

            int channelid = fData->fatima_tamex[it_board_number].time_channelv[it_hits]; // 1-32
            if (channelid == 0) continue; // skip channel 0 for now
            int coarse_T = fData->fatima_tamex[it_board_number].time_coarsev[it_hits];
            
            if (flag_collect_fine_times) {
                fine_time_hits[NBoards][NChannels].Fill(fData->fatima_tamex[it_board_number].time_finev[it_hits]);
            }
            
            if (!fine_time_calibration_set) continue; //drop uncalibrated events

            double fine_T = GetFineTime(fData->fatima_tamex[it_board_number].time_finev[it_hits],it_board_number,channelid-1);



            if (fData->fatima_tamex[it_board_number].time_edgev[it_hits] == 1){ // rise signal:
                fNleads_read ++;
                if (last_hits[it_board_number][channelid-1].hit==true){
                    //second rise time found.

                    //write the old trail ...
                    new ((*fArray)[fArray->GetEntriesFast()]) FatimaTwinpeaksData(
                        it_board_number,
                        channelid,
                        last_hits[it_board_number][channelid-1].lead_epoch_counter,
                        last_hits[it_board_number][channelid-1].lead_coarse_T,
                        last_hits[it_board_number][channelid-1].lead_fine_T,

                        0,
                        0,
                        0,
                        fData->fatima_ts_subsystem_id,
                        wr_t);


                    // but keep the recent one
                    last_hits[it_board_number][channelid-1].hit = true;
                    last_hits[it_board_number][channelid-1].lead_epoch_counter = last_epoch;
                    last_hits[it_board_number][channelid-1].lead_coarse_T = coarse_T;
                    last_hits[it_board_number][channelid-1].lead_fine_T = fine_T;
                }

                last_hits[it_board_number][channelid-1].hit = true;
                last_hits[it_board_number][channelid-1].lead_epoch_counter = last_epoch;
                last_hits[it_board_number][channelid-1].lead_coarse_T = coarse_T;
                last_hits[it_board_number][channelid-1].lead_fine_T = fine_T;

                continue;
            }

            if (fData->fatima_tamex[it_board_number].time_edgev[it_hits] == 0 && last_hits[it_board_number][channelid-1].hit){ 
                fNmatched ++;
                fNtrails_read++;
                //trail and rise are matched
                new ((*fArray)[fArray->GetEntriesFast()]) FatimaTwinpeaksData(
                    it_board_number,
                    channelid,
                    last_hits[it_board_number][channelid-1].lead_epoch_counter,
                    last_hits[it_board_number][channelid-1].lead_coarse_T,
                    last_hits[it_board_number][channelid-1].lead_fine_T,

                    last_epoch,
                    coarse_T,
                    fine_T,
                    fData->fatima_ts_subsystem_id,
                    wr_t);
                
                //reset:
                last_hits[it_board_number][channelid-1].hit=false;
                last_hits[it_board_number][channelid-1].lead_epoch_counter = 0;
                last_hits[it_board_number][channelid-1].lead_coarse_T = 0;
                last_hits[it_board_number][channelid-1].lead_fine_T = 0;
            }else{
                // do nothing, trail found with no rise.
                fNtrails_read++;
            }
        }
    }


    

    fNEvent += 1;
    return kTRUE;
}

void FatimaReader::Reset()
{
    // reset output array
    fArray->Clear();
       
}

ClassImp(FatimaReader)
