#ifndef FimpReader_H
#define FimpReader_H 

#include "FimpData.h"
#include "c4Reader.h"

#include <Rtypes.h>
#include <vector>
#include "TH1.h"

extern "C"
{
    #include "ext_h101_fimpy2025.h"
}

class FimpItem;

struct EXT_STR_h101_fimp_t;
typedef struct EXT_STR_h101_fimp_t EXT_STR_h101_fimp;
typedef struct EXT_STR_h101_fimp_onion_t EXT_STR_h101_fimp_onion;
class ext_data_struct_info;

struct ctdc_data_store
{   
    uint16_t channel = 0;
    uint16_t coarse_time = 0;
    double fine_time = 0.0;
    int leadOrTrail = -1;
    uint16_t raw_ft = 0; // maybe setting to 0 causes some issue, we'll see
};

class FimpReader : public c4Reader
{
    public:
        FimpReader(EXT_STR_h101_fimp_onion*, size_t);

        virtual ~FimpReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        void ZeroArrays();
        void ClearVectors();

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

        // variable names etc will change, this is the method from TAMEX
        void DoFineTimeCalibration();
        double GetFineTime(int channel_id, int tdc_ft_channel);
        void WriteFineTimeHistosToFile();
        void ReadFineTimeHistosFromFile();
        void SetInputFileFineTimeHistos(TString inputfile)
        {
            fine_time_histo_infile = inputfile;
            fine_time_calibration_read_from_file = true;
        }

        void DoFineTimeCalOnline()
        {
            fine_time_calibration_set = false;
            fine_time_calibration_save = false;
        } // creates and does not save it.

        void DoFineTimeCalOnline(TString outputfile, int nevents)
        {
            fine_time_calibration_set = false;
            fine_time_calibration_save = true;
            fine_time_histo_outfile = outputfile;
            fine_time_calibration_after = nevents;
        } // creates and saves it.


    private:
        unsigned fNEvent;

        EXT_STR_h101_fimp_onion* fData;

        size_t fOffset;

        Bool_t fOnline;
        
        std::vector<FimpItem>* fimpArray;
        //ctdc_data_store last_hit;

        std::vector<uint16_t> lead_coarse;
        std::vector<double> lead_fine;
        std::vector<uint16_t> lead_raw_ft;
        std::vector<uint16_t> trail_coarse;
        std::vector<double> trail_fine;
        std::vector<uint16_t> trail_raw_ft;

        int unmatchedLeads = 0;
        int counter = 0;
        int lead_trail_unmatched_counter = 0;

        int chans_per_tdc = 259; // 259 because 128 lead/trail + trig
        int max_fine_time_bins = 18; // 8_12 is 9_13?, 16 is 18
        int cycle_time = 6667; // or 4000

        TString fine_time_histo_outfile;
        TString fine_time_histo_infile;
        TH1I** fine_time_hits;
        double** fine_time_calibration_coeffs;
        int fine_time_calibration_after = 100000;
        bool fine_time_calibration_set = false;
        bool fine_time_calibration_save = false;
        bool fine_time_calibration_read_from_file = false;


    public:
        ClassDefOverride(FimpReader, 0);
};

#endif
