#ifndef GermaniumReader_H
#define GermaniumReader_H

#include "c4Reader.h"

#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_ge_febex.h"
}

class TClonesArray;

struct EXT_STR_h101_GE_FEBEX_t;
typedef struct EXT_STR_h101_GE_FEBEX_t EXT_STR_h101_GE_FEBEX;
typedef struct EXT_STR_h101_GE_FEBEX_onion_t EXT_STR_h101_GE_FEBEX_onion;
class ext_data_struct_info;

class GermaniumReader : public c4Reader
{
    public:
        GermaniumReader(EXT_STR_h101_GE_FEBEX_onion*, size_t);

        virtual ~GermaniumReader();

        void PrintDetectorMap();
        void PrintDetectorCal();

        Bool_t SetDetectorMapFile(TString);
        Bool_t SetDetectorCalFile(TString);

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }
    
    private:
        unsigned int fNEvent;

        EXT_STR_h101_GE_FEBEX_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;


        uint16_t detector_id;
        uint16_t crystal_id;

        uint64_t event_trigger_time_long;
        uint64_t channel_trigger_time_long;

        int32_t channel_energy;
        double channel_energy_cal;

        uint64_t wr_t;

        //internal status flags for detector map and calibration map:
        Bool_t DetectorMap_loaded = 0;
        Bool_t DetectorCal_loaded = 0;

        //maps:
        std::map<std::pair<int,int>,std::pair<int,int>> detector_mapping; // [board_id][channel_id] -> [detector_id][crystal_id]
        std::map<std::pair<int,int>,std::pair<double,double>> calibration_coeffs; // key: [detector id][crystal id] -> [a0][a1]
    
    public:
        ClassDefOverride(GermaniumReader, 0);
};

#endif