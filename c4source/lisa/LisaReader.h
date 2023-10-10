#ifndef LisaReader_H
#define LisaReader_H 

#include "c4Reader.h"
#include <Rtypes.h>

extern "C"
{
    #include "ext_data_client.h"
    #include "ext_h101_lisa.h"
}

class TClonesArray;

struct EXT_STR_h101_LISA_t;
typedef struct EXT_STR_h101_LISA_t EXT_STR_h101_LISA;
typedef struct EXT_STR_h101_LISA_onion_t EXT_STR_h101_LISA_onion;
class ext_data_struct_info;

class LisaReader : public c4Reader
{
    public:
        LisaReader(EXT_STR_h101_LISA_onion*, size_t);

        virtual ~LisaReader();

        void PrintDetectorMap();
        void PrintDetectorCal();

        Bool_t SetDetectorMapFile(TString);
        Bool_t SetDetectorCalFile(TString);

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        unsigned fNEvent;

        EXT_STR_h101_LISA_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;
        TClonesArray* fTraceArray;

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

        // maps
    
    public:
        ClassDefOverride(LisaReader, 0);
};

#endif
