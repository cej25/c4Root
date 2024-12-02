#ifndef FrsMainReader_H
#define FrsMainReader_H

#include "FrsMainData.h"
#include "c4Reader.h"
#include <Rtypes.h>
#include <vector>
#include "EventHeader.h"

extern "C"
{
    #include "ext_h101_frsmain.h"
}

class TClonesArray;

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

        std::vector<FrsMainV830Item>* v830array;
        std::vector<FrsMainV792Item>* v792array;
        std::vector<FrsMainV1290Item>* v1290array;

        EventHeader* header;

        bool spill_flag = false;
        
    
    public:
        ClassDefOverride(FrsMainReader, 1);
};

#endif