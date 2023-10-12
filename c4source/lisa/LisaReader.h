#ifndef LisaReader_H
#define LisaReader_H 

#include "c4Reader.h"
#include <Rtypes.h>

extern "C"
{
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
    
    public:
        ClassDefOverride(LisaReader, 0);
};

#endif
