#ifndef FatimaReader_H
#define FatimaReader_H

#include "c4Reader.h"

#include "TH1.h"



#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_fatima.h"
}

class TClonesArray;

struct EXT_STR_h101_FATIMA_t;
typedef struct EXT_STR_h101_FATIMA_t EXT_STR_h101_FATIMA;
typedef struct EXT_STR_h101_FATIMA_onion_t EXT_STR_h101_FATIMA_onion;
class ext_data_struct_info;


struct last_lead_hit_struct{
    bool hit = false;
    //uint16_t board_id; index using these:
    //uint32_t ch_ID;
    uint32_t lead_epoch_counter = 0;
    uint32_t lead_coarse_T = 0;
    double lead_fine_T = 0;
};


class FatimaReader : public c4Reader
{
    public:
        FatimaReader(EXT_STR_h101_FATIMA_onion*, size_t);

        virtual ~FatimaReader();


        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }


        void DoFineTimeCalibration();
        
        double GetFineTime(int tdc_fine_time_channel, int board_id, int channel_id);

        void WriteFineTimeHistosToFile();
        void ReadFineTimeHistosFromFile();
        void SetInputFileFineTimeHistos(char * inputfile){
            fine_time_histo_infile = inputfile;
            fine_time_calibration_read_from_file = true;
        };

        void DoFineTimeCalOnline(){
            fine_time_calibration_set = false;
            fine_time_calibration_save = false;
        }; //creates and does not save it.
        void DoFineTimeCalOnline(char * outputfile, int nevents_to_include){
            fine_time_histo_outfile = outputfile;
            fine_time_calibration_save = true;
            fine_time_calibration_set = false;
            fine_time_calibration_after = nevents_to_include;
        }; //creates and saves it.



    private:
        unsigned int fNEvent;

        EXT_STR_h101_FATIMA_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;

        last_lead_hit_struct ** last_hits;

        uint64_t wr_t;


        const int NBoards = 4; // in the .spec file!
        const int NChannels = 32; //per board



        uint32_t last_epoch[32];
        uint32_t next_channel = 0;



        uint64_t fNepochwordsread = 0;
        uint64_t fNtrails_read = 0;
        uint64_t fNleads_read = 0;
        uint64_t fNevents_lacking_epoch = 0;
        uint64_t fNmatched = 0;


        char * fine_time_histo_outfile; 
        char * fine_time_histo_infile; 

        const int Nbins_fine_time = 1024; //number of bins in the fine time - it is a 10 bit word (2^10 = 1024) but seemingly no event is >512 - true, fine time calibration does this.

        TH1I *** fine_time_hits; //array of TH1 hisots [NBoards][NChannels]
        double *** fine_time_calibration_coeffs; //[NBoards][NChannels][1024] last index is bin nr. - this is the lookup table
        
        int fine_time_calibration_after = 10000000;
        double TAMEX_fine_time_clock = 5.0; // ns in one fine time cycle.
        //need some status flags:
        bool fine_time_calibration_set = false;
        bool fine_time_calibration_save = false;
        bool fine_time_calibration_read_from_file = false;



    public:
        ClassDefOverride(FatimaReader, 0);
};

#endif
