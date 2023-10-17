#ifndef FatimaReader_H
#define FatimaReader_H

#include "c4Reader.h"

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


        void DoFineTimeCalibrationEveryN(int event); //options to write
        
        double GetFineTime(int tdc_fine_time_channel, int board_id, int channel_id);

        void WriteFineTimeCalibrationsToFile(TString filename);
        void ReadFineTimeCalibrationFromFile();
    
    private:
        unsigned int fNEvent;

        EXT_STR_h101_FATIMA_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;

        last_lead_hit_struct ** last_hits;

        uint32_t last_epoch = 0;
        uint32_t look_ahead_counter = 0;

        uint64_t wr_t;


        const int NBoards = 9;
        const int NChannels = 32;

        uint64_t fNepochwordsread = 0;
        uint64_t fNtrails_read = 0;
        uint64_t fNleads_read = 0;
        uint64_t fNmatched = 0;


        TH1I fine_time_hits[NBoards][NChannels];
        double fine_time_calibration_coeffs[NBoards][NChannels][1024]; //last index is bin nr. - this is the lookup table
        bool flag_collect_fine_times = true;
        int fine_time_calibration_freq = 10000000;
        bool fine_time_calibration_set = false;



    public:
        ClassDefOverride(FatimaReader, 0);
};

#endif