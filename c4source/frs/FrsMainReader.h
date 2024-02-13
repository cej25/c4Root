#ifndef FrsMainReader_H
#define FrsMainReader_H

#include "FrsMainData.h"
#include "c4Reader.h"
#include <Rtypes.h>
#include <vector>

extern "C"
{
    #include "ext_h101_frsmain.h"
}

class TClonesArray;
class FrsMainData;

struct EXT_STR_h101_frsmain_t;
typedef struct EXT_STR_h101_frsmain_t EXT_STR_h101_frsmain;
typedef struct EXT_STR_h101_frsmain_onion_t EXT_STR_h101_frsmain_onion;
class ext_data_struct_info;

class FrsMainReader : public c4Reader
{
    public:
        FrsMainReader(EXT_STR_h101_frsmain_onion*, size_t);

        virtual ~FrsMainReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        void ZeroArrays();
        void ClearVectors();

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:

        unsigned int fNEvent;
        
        EXT_STR_h101_frsmain_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;

        uint64_t wr_t;

        uint32_t scalers_n;
        std::vector<uint32_t> scalers_index;
        std::vector<uint32_t> scalers_main;

        uint32_t v792_geo;
        std::vector<uint32_t> v792_channel;
        std::vector<uint32_t> v792_data;
        
        std::vector<uint32_t> v1290_channel;
        std::vector<uint32_t> v1290_data;
        std::vector<uint32_t> v1290_lot;
    
    public:
        ClassDefOverride(FrsMainReader, 0);
};

#endif