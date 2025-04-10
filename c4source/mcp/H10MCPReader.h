#ifndef H10MCPReader_H
#define H10MCPReader_H

#include "H10MCPTwinpeaksData.h"
#include "c4Reader.h"

#include "TH1.h"

#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_mcp.h"
}

class TClonesArray;

struct EXT_STR_h101_mcp_t;
typedef struct EXT_STR_h101_mcp_t EXT_STR_h101_mcp;
typedef struct EXT_STR_h101_mcp_onion_t EXT_STR_h101_mcp_onion;
class ext_data_struct_info;


struct mcp_last_lead_hit_struct
{
    bool hit = false;
    UInt_t lead_epoch_counter = 0;
    UInt_t lead_coarse_T = 0;
    double lead_fine_T = 0;
};


class H10MCPReader : public c4Reader
{
    public:
        H10MCPReader(EXT_STR_h101_mcp_onion*, size_t);

        virtual ~H10MCPReader();


        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }


        void DoFineTimeCalibration();
        
        double GetFineTime(int tdc_fine_time_channel, int board_id, int channel_id);

        void WriteFineTimeHistosToFile();
        void ReadFineTimeHistosFromFile();
        void SetInputFileFineTimeHistos(TString inputfile)
        {
            fine_time_histo_infile = inputfile;
            fine_time_calibration_read_from_file = true;
        };

        void PrintStatistics();

        void DoFineTimeCalOnline()
        {
            fine_time_calibration_set = false;
            fine_time_calibration_save = false;
        }; //creates and does not save it.
        void DoFineTimeCalOnline(TString outputfile, int nevents_to_include)
        {
            fine_time_histo_outfile = outputfile;
            fine_time_calibration_save = true;
            fine_time_calibration_set = false;
            fine_time_calibration_after = nevents_to_include;
        }; //creates and saves it.



    private:
        Int_t fNEvent;
        int total_time_microsecs = 0;
        

        EXT_STR_h101_mcp_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        Bool_t fPrintStatistics = false;

        TClonesArray* fArray;

        Long64_t wr_t;


        static const int NBoards = sizeof(fData->mcp_tamex) / sizeof(fData->mcp_tamex[0]);
        static const int NChannels = 33; //slow + fast per board + trigger channel 0.


        //global
        ULong64_t fNepochwordsread = 0;
        ULong64_t fNevents_skipped = 0; //because the size of the array does not match internally (UCESB/c4 error likely)
        
        // per channel/board    
        ULong64_t fNtrails_read[NBoards][NChannels];
        ULong64_t fNleads_read[NBoards][NChannels];
        ULong64_t fNmatched[NBoards][NChannels]; //successfully matched lead/trail combinations.

        ULong64_t fNevents_lacking_epoch[NBoards][NChannels]; //events where there is a time data word in a new channel without having seen an epoch word for this channel before.
        ULong64_t fNevents_TAMEX_fail[NBoards][NChannels]; //number of 0x3FF data words indicating TAMEX failure of the fast filter.
        ULong64_t fNevents_second_lead_seen[NBoards][NChannels]; // number of times a second lead is seen (i.e. a lead-lead in the channel) keeping only the last lead.
        ULong64_t fNevents_trail_seen_no_lead[NBoards][NChannels]; // number of times a trail is seen without a preceeding lead - skipping this event.

        int last_channel_read = 0;
        bool last_word_read_was_epoch = false;

        TString fine_time_histo_outfile;
        TString fine_time_histo_infile;

        const int Nbins_fine_time = 1024; //number of bins in the fine time - it is a 10 bit word (2^10 = 1024)

        TH1I *** fine_time_hits; //array of TH1 hisots [NBoards][NChannels+1] accounting also for the trigger channel
        double *** fine_time_calibration_coeffs; //[NBoards][NChannels+1][1024] last index is bin nr. - this is the lookup table
        
        int fine_time_calibration_after = 10000000;
        Double_t TAMEX_fine_time_clock = 5.0; // ns in one fine time cycle.
        //need some status flags:
        bool fine_time_calibration_set = false;
        bool fine_time_calibration_save = false;
        bool fine_time_calibration_read_from_file = false;

        Double_t accepted_trigger_time = 0;
        UInt_t accepted_lead_epoch_counter = 0;
        UInt_t accepted_lead_coarse_T = 0;
        Double_t accepted_lead_fine_T = 0;

        int hits[21] = {0};


    public:
        ClassDefOverride(H10MCPReader, 0);
};

#endif
