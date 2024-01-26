#ifndef FrsVFTXReader_H
#define FrsVFTXReader_H


#include "FrsVFTXData.h"
#include "c4Reader.h"
#include <Rtypes.h>
#include <vector>

extern "C"
{
    #include "ext_h101_frsvftx.h"
}

class TClonesArray;
class FrsVFTXData;

struct EXT_STR_h101_frsvftx_t;
typedef struct EXT_STR_h101_frsvftx_t EXT_STR_h101_frsvftx;
typedef struct EXT_STR_h101_frsvftx_onion_t EXT_STR_h101_frsvftx_onion;
class ext_data_struct_info;

class FrsVFTXReader : public c4Reader
{
    public:
        FrsVFTXReader(EXT_STR_h101_frsvftx_onion*, size_t);

        virtual ~FrsVFTXReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }
    
    private:
        Int_t fNEvent = 0;

        EXT_STR_h101_frsvftx_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;

    public:
        ClassDefOverride(FrsVFTXReader, 0);

};

#endif
