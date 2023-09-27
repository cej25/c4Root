#ifndef bPlastReader_H
#define bPlastReader_H

// c4
#include "c4Reader.h"

#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_bplast.h"
}

class TClonesArray;

struct EXT_STR_h101_BPLAST_t;
typedef struct EXT_STR_h101_BPLAST_t EXT_STR_h101_BPLAST;
typedef struct EXT_STR_h101_BPLAST_onion_t EXT_STR_h101_BPLAST_onion;
class ext_data_struct_info;

class bPlastReader : public c4Reader
{
    public:
        bPlastReader(EXT_STR_h101_BPLAST_onion*, size_t);

        virtual ~bPlastReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        unsigned int fNEvent;

        EXT_STR_h101_BPLAST_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;
    
    public:
        ClassDefOverride(bPlastReader, 0);

};

#endif