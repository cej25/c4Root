// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"

#include "TH1.h"
#include "TFile.h"

#include <iomanip>

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

/*
Constructor. Needs the input data structure obtained from ucesb with the following args:
 --ntuple=UNPACK:fatima,STRUCT_HH,ext_h101_fatima.h (add NOEVENTHEAD also). 

The resulting file must be in the same folder as this file.

*/
FatimaReader::FatimaReader(EXT_STR_h101_FATIMA_onion* data, size_t offset)
    : c4Reader("FatimaReader")
    , fNEvent(0)
    , fData(data)
    , fOffset(offset)
    , fOnline(kFALSE)
    , fArray(new TClonesArray("FatimaTwinpeaksData"))
{
}

/*
Deletes the arrays allocated.
And prints some statistics for the run.
*/
FatimaReader::~FatimaReader() { 
    
    c4LOG(info, Form("Epochs read %i",(int)fNepochwordsread));
    c4LOG(info, Form("Event without epoch read %i",(int)fNevents_lacking_epoch));
    c4LOG(info, Form("Trails read %i",(int)fNtrails_read));
    c4LOG(info, Form("Leads read  %i",(int)fNleads_read));
    c4LOG(info, Form("Matches     %i",(int)fNmatched));
    for (int i = 0; i < NBoards; i++) {
        for (int j = 0; j < NChannels; j++) {
            if (fine_time_calibration_coeffs[i][j] != nullptr) {
                delete[] fine_time_calibration_coeffs[i][j];
                fine_time_calibration_coeffs[i][j] = nullptr;
            }
        }

        if (fine_time_calibration_coeffs[i] != nullptr) {
            delete[] fine_time_calibration_coeffs[i];
            fine_time_calibration_coeffs[i] = nullptr;
        }

        if (fine_time_hits[i] != nullptr) {
            delete[] fine_time_hits[i];
            fine_time_hits[i] = nullptr;
        }

        if (last_hits[i] != nullptr) {
            delete[] last_hits[i];
            last_hits[i] = nullptr;
        }
    }

    if (fine_time_hits != nullptr) {
        delete[] fine_time_hits;
        fine_time_hits = nullptr;
    }

    if (fine_time_calibration_coeffs != nullptr) {
        delete[] fine_time_calibration_coeffs;
        fine_time_calibration_coeffs = nullptr;
    }

    if (last_hits != nullptr) {
        delete[] last_hits;
        last_hits = nullptr;
    }


    if (fArray != nullptr) delete fArray;

    c4LOG(info, "Destroyed FatimaReader properly.");

}

/*
Required set up before reading. 

If the fine time calibration histograms are read from disk, it loads these.
If not new histograms are allocated and ready for filling and calibration.

*/
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
    fine_time_calibration_coeffs = new double**[NBoards];
    for (int i = 0; i < NBoards; i++) {
        last_hits[i] = new last_lead_hit_struct[NChannels];
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

    for (int i = 0; i<32; i++){
        last_epoch[i] = 0;
    }


    if (fine_time_calibration_read_from_file){
        ReadFineTimeHistosFromFile();
        DoFineTimeCalibration();
        fine_time_calibration_set = true;
        c4LOG(info,"Fine Time calibration set from file.");
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
    FairRootManager::Instance()->Register("FatimaTwinpeaksData", "Fatima Twinpeaks Data", fArray, !fOnline);
    fArray->Clear();

    memset(fData, 0, sizeof *fData);

    c4LOG(info,"FatimaReader init setup.");

    return kTRUE;
}

/*
This does the fine time calibrations of the fine times and builds the required look-up table in fine_time_calibrations[board][channel][tdc channel] = time (ns)

This can be called explicitly if desired - but will be done automatically by the rest of the code. Throws a warning if there are channels without hits. These are mapped tdc_channel = tdc_channel/512*5 ns
*/
void FatimaReader::DoFineTimeCalibration(){
    c4LOG(info, "Doing fine time calibrations.");
    for (int i = 0; i < NBoards; i++) {
        for (int j = 0; j < NChannels; j++) {
            int running_sum = 0;
            int total_counts = fine_time_hits[i][j]->GetEntries();
            if (total_counts == 0) {c4LOG(warning,Form("Channel %i on board %i does not have any fine time hits in the interval.",j,i));}

            for (int k = 0; k < Nbins_fine_time; k++) {
                running_sum += fine_time_hits[i][j]->GetBinContent(k+1); //bin 0 is the underflow bin, hence we start at [1,Nbins_fine_time].
                
                if (total_counts == 0) { // in case of no hits.
                    fine_time_calibration_coeffs[i][j][k] = k*TAMEX_fine_time_clock/(double)Nbins_fine_time;
                    continue;
                }

                fine_time_calibration_coeffs[i][j][k] = TAMEX_fine_time_clock*(double)running_sum/(double)total_counts;
            }
        }
    }
    fine_time_calibration_set = true;
}

/*
Uses the conversion table to look-up fine times in ns.
*/
double FatimaReader::GetFineTime(int tdc_fine_time_channel, int board_id, int channel_id){
    return fine_time_calibration_coeffs[board_id][channel_id][tdc_fine_time_channel];
}

/*
Fine time histograms are stored as ROOT TH1I histograms as they are efficient and compresses when written.
This function saves the fine time hits directly to file. On restart this file can then be read and the look-up table reconstructed.
*/
void FatimaReader::WriteFineTimeHistosToFile(){

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

/*
Read the fine time histograms which are written by the function above.

Assumes the names of the histograms are fine_time_hist_module_channel and that they have 1024 bins (since the TAMEX fine time is written with 2^10 bits).
*/
void FatimaReader::ReadFineTimeHistosFromFile() {

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
                c4LOG(debug1,Form("Accessing i = %i, j = %i",i,j));
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

/*
Event read loop. Only called by the FairRootManager.

If no fine time calibrations are set, the fine time histograms are filled until a set number of events have been read. Then the FineTimeCalibration is automatically done and the writing of hits start.
If the fine time calibration is set from the start, hits are written immediately.

Some assumptions:
    - Each time a new channel is hit, it must be preceeded by an epoch word.
    - Each time the epoch word changes it is written again.
    - Time hits are time ordered as they are written by the TAMEX module.

*/
Bool_t FatimaReader::Read() //do fine time here:
{
    c4LOG(debug1, "Event Data");

    if (!fData) return kTRUE;

    if ((fNEvent==fine_time_calibration_after)  & (!fine_time_calibration_set)){
        c4LOG(info, "Doing fine time calibration now.");
        DoFineTimeCalibration();
        if (fine_time_calibration_save) WriteFineTimeHistosToFile();
    }
    
    //whiterabbit timestamp:
    wr_t = (((uint64_t)fData->fatima_ts_t[3]) << 48) + (((uint64_t)fData->fatima_ts_t[2]) << 32) + (((uint64_t)fData->fatima_ts_t[1]) << 16) + (uint64_t)(fData->fatima_ts_t[0]);
    

    for (int it_board_number = 0; it_board_number < NBoards; it_board_number++){ //per board:
        
        for (int i = 0; i<32; i++) last_epoch[i] = 0;


        if (fData->fatima_tamex[it_board_number].event_size == 0) continue; // empty event skip

        for (int it_hits = 0; it_hits < fData->fatima_tamex[it_board_number].event_size/4 - 3 ; it_hits++){
            //this distinguishes epoch words from time words by checking if the epoch/coarse and fine words are zero. This would potentially be a problem if epoch truly is zero...

            if (fData->bplast_tamex[it_board_number].time_epoch <= it_hits) {continue;}
            
            if (fData->fatima_tamex[it_board_number].time_epochv[it_hits] != 0){
                    if (it_hits + 1 == fData->fatima_tamex[it_board_number].event_size/4 - 3) {c4LOG(fatal, "Data ends on a epoch...");}

                    next_channel = fData->fatima_tamex[it_board_number].time_channelv[it_hits+1];

                    if (next_channel == 0) continue;
                    
                    last_epoch[next_channel-1] = fData->fatima_tamex[it_board_number].time_epochv[it_hits];
                    fNepochwordsread++;
                    continue;
            }
            


            //from this point we should have seen an epoch for channel id.
            int channelid = fData->fatima_tamex[it_board_number].time_channelv[it_hits]; // 1-32

            if (channelid == 0) continue; // skip channel 0 for now. TODO...
            if (fData->fatima_tamex[it_board_number].time_finev[it_hits] == 0x3FF) continue; // this happens if TAMEX loses the fine time - skip it
            
            //c4LOG(info, Form("Channel %i - last_epoch = %i"))
            
            //should not pass this point if this is an epoch:
            
            if (last_epoch[channelid-1] == 0 || fData->fatima_tamex[it_board_number].time_epochv[it_hits] != 0){
                //case no epoch seen, this is not an epoch word.
                
                //this does indeed seem to happen sometimes - there are hits with no preceeding epoch - therefore the stats of how often this happens is kept. 

                fNevents_lacking_epoch++;
                continue;
            }


            
            
            int coarse_T = fData->fatima_tamex[it_board_number].time_coarsev[it_hits];

            //Fill fine times and skip.            
            if (!fine_time_calibration_set) {
                fine_time_hits[it_board_number][channelid-1]->Fill(fData->fatima_tamex[it_board_number].time_finev[it_hits]);
                continue;
            }

            double fine_T = GetFineTime(fData->fatima_tamex[it_board_number].time_finev[it_hits],it_board_number,channelid-1);


            if (fData->fatima_tamex[it_board_number].time_edgev[it_hits] == 1){ // rise signal:
                fNleads_read ++;
                if (last_hits[it_board_number][channelid-1].hit==true){
                    //second rise time found.

                    //write the old lead without trail...
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

                    last_epoch[channelid-1],
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


/*
Memory management.
*/
void FatimaReader::Reset()
{
    // reset output array
    fArray->Clear();
       
}

ClassImp(FatimaReader)
