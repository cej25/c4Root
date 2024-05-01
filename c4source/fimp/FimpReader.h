#ifndef FimpReader_H
#define FimpReader_H 

#include "FimpData.h"
#include "c4Reader.h"

#include <Rtypes.h>
#include <vector>

extern "C"
{
    #include "ext_h101_fimp.h"
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
    uint16_t fine_time = 0;
    int leadOrTrail = -1;
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

    private:
        unsigned fNEvent;

        EXT_STR_h101_fimp_onion* fData;

        size_t fOffset;

        Bool_t fOnline;
        
        std::vector<FimpItem>* fimpArray;
        //ctdc_data_store last_hit;

        int unmatchedLeads = 0;
        int counter = 0;
        int lead_trail_unmatched_counter = 0;


    public:
        ClassDefOverride(FimpReader, 0);
};

#endif
