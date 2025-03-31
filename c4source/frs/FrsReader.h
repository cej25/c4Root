#ifndef FrsReader_H
#define FrsReader_H

#include "FrsData.h"
#include "c4Reader.h"
#include <Rtypes.h>
#include <vector>
#include "EventHeader.h"

extern "C"
{
    #include "ext_h101_frs.h"
}

class TClonesArray;

struct EXT_STR_h101_frs_t;
typedef struct EXT_STR_h101_frs_t EXT_STR_h101_frs;
typedef struct EXT_STR_h101_frs_onion_t EXT_STR_h101_frs_onion;
class ext_data_struct_info;

class FrsReader : public c4Reader
{
    public:
        FrsReader(EXT_STR_h101_frs_onion*, size_t);

        virtual ~FrsReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        void ScalerReader();
        void ScintillatorReader();
        void MusicReader();
        void TpcReader();

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:

        unsigned int fNEvent;
        
        EXT_STR_h101_frs_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        EventHeader* header;

        // Arrays
        std::vector<FrsTpatItem>* tpatArray;
        FrsTpatItem* tpatItem;
        std::vector<FrsScalerItem>* scalerArray;
        FrsScalerItem* scalerItem;
        std::vector<FrsSciItem>* sciArray;
        FrsSciItem* sciItem;
        std::vector<FrsMusicItem>* musicArray;
        FrsMusicItem* musicItem;
        std::vector<FrsTpcItem>* tpcArray;
        FrsTpcItem* tpcItem;
        
        // Dummies
        bool spill_flag = false;

        // should probably just make all of these 32
        uint32_t sciDE[32]; // ~18 -> 2025
        uint32_t sciDT[32]; // ~19 -> 2025
        std::vector<int32_t> sciMHTDC[32]; // ~24 -> 2025

        uint32_t musicE[5][8]; // 5 as of 2025
        uint32_t musicT[5][8];

        uint32_t adcData[7][8];
        std::vector<uint32_t> tdcData[128];
        
    
    public:
        ClassDefOverride(FrsReader, 1);
};

#endif