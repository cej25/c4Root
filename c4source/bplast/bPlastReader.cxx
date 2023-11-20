// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

#include "TH1.h"
#include "TFile.h"

#include <iomanip>

// c4
#include "bPlastTwinpeaksData.h"
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
    , fArray(new TClonesArray("bPlastTwinpeaksData"))
{
}

bPlastReader::~bPlastReader() { 
    
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
        fine_time_calibration_coeffs[i] = nullptr;
        
        if (fine_time_hits[i] != nullptr){
            delete[] fine_time_hits[i];
            fine_time_hits[i] = nullptr;
        }

        if (last_hits[i] != nullptr) {
            delete[] last_hits[i];
            last_hits[i] = nullptr;  // Set the pointer to nullptr after deletion
        }
    }
    delete[] fine_time_hits;
    delete[] fine_time_calibration_coeffs;
    delete[] last_hits;


    delete fArray;

    c4LOG(info, "Destroyed bPlastReader properly.");

}

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

    last_hits = new plast_lead_hit_struct*[NBoards];
    fine_time_calibration_coeffs = new double**[NBoards];
    for (int i = 0; i < NBoards; i++) {
        last_hits[i] = new plast_lead_hit_struct[NChannels];
        fine_time_calibration_coeffs[i] = new double*[NChannels];    
    }

    for (int i = 0; i < NBoards; i++) {
        for (int j = 0; j < NChannels; j++) {
            last_hits[i][j].hit = false;
            last_hits[i][j].lead_coarse_T = 0;
            last_hits[i][j].lead_fine_T = 0;
            last_hits[i][j].lead_epoch_counter = 0;
            
            
            
            fine_time_calibration_coeffs[i][j] = new double[Nbins_fine_time];
            for (int k = 0; k<Nbins_fine_time; k++) fine_time_calibration_coeffs[i][j][k] = 0.0;
        }
    }


    if (fine_time_calibration_read_from_file){
        ReadFineTimeHistosFromFile();
        DoFineTimeCalibration();
        fine_time_calibration_set = true;
        c4LOG(info,"Fine Time calibration set from file. ");
    }else{
        fine_time_hits = new TH1I**[NBoards];
        for (int i = 0; i < NBoards; i++) {
            fine_time_hits[i] = new TH1I*[NChannels];
            for (int j = 0; j<NChannels; j++){
                fine_time_hits[i][j] = new TH1I(Form("fine_time_hits_%i_%i", i, j),Form("fine_time_hits_%i_%i", i, j),Nbins_fine_time,0,Nbins_fine_time);
            }
        }
        fine_time_calibration_set = false;
    }

    // Register output array in a tree
    FairRootManager::Instance()->Register("bPlastTwinpeaksData", "bPlast Twinpeaks Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    c4LOG(info,"bPlastReader init setup.");

    return kTRUE;
}

void bPlastReader::DoFineTimeCalibration(){
    c4LOG(info, "Doing fine time calibrations.");
    for (int i = 0; i < NBoards; i++) {
        for (int j = 0; j < NChannels; j++) {
            int running_sum = 0;
            int total_counts = fine_time_hits[i][j]->GetEntries();
            if (total_counts == 0) {c4LOG(warning,Form("Channel %i on board %i does not have any fine time hits in the interval.",j,i));}
            for (int k = 0; k < Nbins_fine_time; k++) {
                running_sum += fine_time_hits[i][j]->GetBinContent(k+1); //bin 0 is the underflow bin, hence we start at [1,Nbins_fine_time].
                //no counts?
                if (total_counts == 0) {
                    fine_time_calibration_coeffs[i][j][k] = k*TAMEX_fine_time_clock/(double)Nbins_fine_time;
                    continue;
                }

                fine_time_calibration_coeffs[i][j][k] = TAMEX_fine_time_clock*(double)running_sum/(double)total_counts;
                //if (i == 1) std::cout << i << " " << j << " " << k << " " << TAMEX_fine_time_clock << " " << running_sum << " " << total_counts << " " << fine_time_calibration_coeffs[i][j][k] << std::endl;
            }
        }
    }
    fine_time_calibration_set = true;
}

double bPlastReader::GetFineTime(int tdc_fine_time_channel, int board_id, int channel_id){
    return fine_time_calibration_coeffs[board_id][channel_id][tdc_fine_time_channel];
}


void bPlastReader::WriteFineTimeHistosToFile(){

    if (!fine_time_calibration_set) {
        c4LOG(info,"Fine time calibrations not set, cannot write to file.");
        return;
    }
    c4LOG(info,"Fine time calibrations starting to write to file.");

    TFile * outputfile = TFile::Open(Form("%s",fine_time_histo_outfile),"recreate");
    
    std::cout << outputfile << std::endl;
    
    if (!outputfile->IsOpen()) {c4LOG(warning, "File to write histos not opened, skipping writing. "); return;}
    // i think the easiest is to write the histograms of the fine times themselves - please let me know if you disagree (JEL)
    for (int i = 0; i < NBoards; i++) {
        for (int j = 0; j < NChannels; j++) {
            if (fine_time_hits[i][j] != nullptr) 
            {
                //c4LOG(info, "Found pointer to histogram.");
                outputfile->WriteObject(fine_time_hits[i][j], Form("fine_time_hits_%i_%i", i, j),"RECREATE");
                //  c4LOG(info, "Wrote object.");
            }
        }
    }
    c4LOG(info,Form("Written fine time calibrations (i.e. raw fine time histograms) to  %s",fine_time_histo_outfile));

    outputfile->Close();

}
void bPlastReader::ReadFineTimeHistosFromFile() {

    TFile* inputfile = TFile::Open(fine_time_histo_infile, "READ");
    if (!inputfile || inputfile->IsZombie()) {
        c4LOG(fatal, "File to read histos not opened.");
    }

    c4LOG(info,"Reading the histograms used in fine time calibration from file.");
    fine_time_hits = new TH1I**[NBoards];
    for (int i = 0; i < NBoards; i++) {
        fine_time_hits[i] = new TH1I*[NChannels];
        for (int j = 0; j < NChannels; j++) fine_time_hits[i][j] = nullptr;
    }


    if (!fine_time_hits) {c4LOG(fatal,"fine_time_hits not declared.");}
    for (int i = 0; i < NBoards; i++) {
        if (!fine_time_hits[i]) {c4LOG(fatal,"fine_time_hits[i] not declared.");}
        for (int j = 0; j < NChannels; j++) {
            if (fine_time_hits[i][j] != nullptr) {c4LOG(fatal,"fine_time_hits[i][j] not declared.");}
            TH1I* a = nullptr;
            inputfile->GetObject(Form("fine_time_hits_%i_%i", i, j), a);
            if (a) {
                c4LOG(info,Form("Accessing i = %i, j = %i",i,j));
                fine_time_hits[i][j] = (TH1I*)a->Clone();
                c4LOG_IF(fatal,fine_time_hits==nullptr,"Failed reading the file for fine time calibration histograms");
                delete a;
                a = nullptr;
                fine_time_hits[i][j]->SetDirectory(0); // this was the trick to access the histos after closing the inputfile.
            }
        }
    }

    inputfile->Close();
    c4LOG(info, Form("Read fine time calibrations (i.e. raw fine time histograms) from %s", fine_time_histo_infile));
}

Bool_t bPlastReader::Read() //do fine time here:
{
    c4LOG(debug1, "Event Data");

    if (!fData) return kTRUE;

    if ((fNEvent==fine_time_calibration_after)  & (!fine_time_calibration_set)){
        c4LOG(info, "Doing fine time calibration now.");
        DoFineTimeCalibration();
        if (fine_time_calibration_save) WriteFineTimeHistosToFile();
    }



    //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->bplast_ts_t[3]) << 48) + (((uint64_t)fData->bplast_ts_t[2]) << 32) + (((uint64_t)fData->bplast_ts_t[1]) << 16) + (uint64_t)(fData->bplast_ts_t[0]);
    

    for (int it_board_number = 0; it_board_number < NBoards; it_board_number++){ //per board:
        
        for (int i = 0; i<32; i++) last_epoch[i] = 0;
        //look_ahead_counter = 0;
        //reset last hits?


        if (fData->bplast_tamex[it_board_number].event_size == 0) continue; // empty event skip

        for (int it_hits = 0; it_hits < fData->bplast_tamex[it_board_number].event_size/4 - 3 ; it_hits++){ // if no data is written this loop never starts (?)
            //this distinguishes epoch words from time words by checking if the epoch/coarse and fine words are zero. This would potentially be a problem if epoch truly is zero...


            /*
            //look ahead to grab epoch: (i think this is wrong)
            if (last_epoch == 0 && fData->bplast_tamex[it_board_number].time_epochv[it_hits] == 0){
                look_ahead_counter ++; //keep track of how far ahead you skip.
                continue;
            }else if (last_epoch == 0 && fData->bplast_tamex[it_board_number].time_epochv[it_hits] != 0){
                last_epoch = fData->bplast_tamex[it_board_number].time_epochv[it_hits] - 1; //subtract one?
                it_hits = it_hits - look_ahead_counter; // jumps back
            }else if (last_epoch != 0 && fData->bplast_tamex[it_board_number].time_epochv[it_hits] != 0){ // next epoch:
                last_epoch = 0;
                look_ahead_counter = 0;
                continue;
            }
            */
            if (fData->bplast_tamex[it_board_number].time_epoch <= it_hits) {continue;}
            if (fData->bplast_tamex[it_board_number].time_epochv[it_hits] != 0){
                    if (it_hits + 1 == fData->bplast_tamex[it_board_number].event_size/4 - 3) c4LOG(fatal, "Data ends on a epoch...");

                    next_channel = fData->bplast_tamex[it_board_number].time_channelv[it_hits+1];

                    if (next_channel == 0 || next_channel < 0 || it_hits+1 >= fData->bplast_tamex[it_board_number].time_channel) continue; // skip channel 0 for now. TODO: we got some channelid = - 1000000 online from bplast? could be pursued?
                    last_epoch[next_channel-1] = fData->bplast_tamex[it_board_number].time_epochv[it_hits];
                    fNepochwordsread++;
                    continue;
            }
            


            //from this point we should have seen an epoch for channel id.
            int channelid = fData->bplast_tamex[it_board_number].time_channelv[it_hits]; // 1-32

            if (channelid == 0 || channelid < 0 || it_hits >= fData->bplast_tamex[it_board_number].time_channel) continue; // skip channel 0 for now. TODO: we got some channelid = - 1000000 online from bplast? could be pursued?
            if (fData->bplast_tamex[it_board_number].time_finev[it_hits] == 0x3FF) continue; // this happens if TAMEX loses the fine time - skip it
            
            //c4LOG(info, Form("Channel %i - last_epoch = %i"))
            
            //should not pass this point if this is an epoch:
            if (last_epoch[channelid-1] == 0 || fData->bplast_tamex[it_board_number].time_epochv[it_hits] != 0){
                //case no epoch seen, this is not an epoch word.
                
                //this does indeed seem to happen sometimes - there are hits with no preceeding epoch.

                //c4LOG(info, Form("channel %i , last epoch = %i, and this epoch = %i",channelid, last_epoch[channelid-1], fData->bplast_tamex[it_board_number].time_epochv[it_hits]));
                //c4LOG(info, Form("coarse: %i, fine %i ",fData->bplast_tamex[it_board_number].time_coarsev[it_hits],fData->bplast_tamex[it_board_number].time_finev[it_hits]));
                //c4LOG(fatal,"HIT SEEN AT START WITH NO EPOCH!");
                fNevents_lacking_epoch++;
                continue;
            }


            
            
            int coarse_T = fData->bplast_tamex[it_board_number].time_coarsev[it_hits];
            //if (channelid%2 == 0) std::cout << channelid << std::endl;
            
            if (!fine_time_calibration_set) {
                //c4LOG(debug1,"Filling the fine time histograms to collect data for fine time calibration.");
                fine_time_hits[it_board_number][channelid-1]->Fill(fData->bplast_tamex[it_board_number].time_finev[it_hits]);
                continue;
            }

            double fine_T = GetFineTime(fData->bplast_tamex[it_board_number].time_finev[it_hits],it_board_number,channelid-1);


            if (fData->bplast_tamex[it_board_number].time_edgev[it_hits] == 1){ // rise signal:
                fNleads_read ++;
                if (last_hits[it_board_number][channelid-1].hit==true){
                    //second rise time found.

                    //write the old trail ...
                    new ((*fArray)[fArray->GetEntriesFast()]) bPlastTwinpeaksData(
                        it_board_number,
                        channelid,
                        last_hits[it_board_number][channelid-1].lead_epoch_counter,
                        last_hits[it_board_number][channelid-1].lead_coarse_T,
                        last_hits[it_board_number][channelid-1].lead_fine_T,
                        0,
                        0,
                        0,
                        fData->bplast_ts_subsystem_id,
                        wr_t);


                    // but keep the recent one
                    last_hits[it_board_number][channelid-1].hit = true;
                    last_hits[it_board_number][channelid-1].lead_epoch_counter = last_epoch[channelid-1];
                    last_hits[it_board_number][channelid-1].lead_coarse_T = coarse_T;
                    last_hits[it_board_number][channelid-1].lead_fine_T = fine_T;
                }

                last_hits[it_board_number][channelid-1].hit = true;
                last_hits[it_board_number][channelid-1].lead_epoch_counter = last_epoch[channelid-1];
                last_hits[it_board_number][channelid-1].lead_coarse_T = coarse_T;
                last_hits[it_board_number][channelid-1].lead_fine_T = fine_T;

                continue;
            }

            if (fData->bplast_tamex[it_board_number].time_edgev[it_hits] == 0 && last_hits[it_board_number][channelid-1].hit){ 
                fNmatched ++;
                fNtrails_read++;
                //trail and rise are matched
                new ((*fArray)[fArray->GetEntriesFast()]) bPlastTwinpeaksData(
                    it_board_number,
                    channelid,
                    last_hits[it_board_number][channelid-1].lead_epoch_counter,
                    last_hits[it_board_number][channelid-1].lead_coarse_T,
                    last_hits[it_board_number][channelid-1].lead_fine_T,

                    last_epoch[channelid-1],
                    coarse_T,
                    fine_T,
                    fData->bplast_ts_subsystem_id,
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

void bPlastReader::Reset()
{
    // reset output array
    fArray->Clear();
       
}

ClassImp(bPlastReader)
