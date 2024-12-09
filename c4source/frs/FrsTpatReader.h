#ifndef FrsTpatReader_H
#define FrsTpatReader_H

#include "FrsData.h" // temp
#include "c4Reader.h"
#include <Rtypes.h>
#include <vector>
#include "EventHeader.h"

extern "C"
{
    #include "ext_h101_frstpat.h"
}

class TClonesArray;

struct EXT_STR_h101_frstpat_t;
typedef struct EXT_STR_h101_frstpat_t EXT_STR_h101_frstpat;
typedef struct EXT_STR_h101_frstpat_onion_t EXT_STR_h101_frstpat_onion;
class ext_data_struct_info;

class FrsTpatReader : public c4Reader
{
    public:
        FrsTpatReader(EXT_STR_h101_frstpat_onion*, size_t);

        virtual ~FrsTpatReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        //void ZeroArrays();
        //void ClearVectors();

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:

        unsigned int fNEvent;
        EventHeader* header;
        
        EXT_STR_h101_frstpat_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        std::vector<FrsTpatItem>* tpatArray;

        uint64_t wr_t;
        uint16_t tpat;
        
        int tpatEvent = 0;
        bool written = false;

    
    public:
        ClassDefOverride(FrsTpatReader, 1);
};

#endif
