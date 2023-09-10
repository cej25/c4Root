#ifndef GermaniumReader_H
#define GermaniumReader_H

#include "c4Reader.h"

#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_ge_febex.h" // name??
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
    
    public:
        ClassDefOverride(GermaniumReader, 0);
};

#endif