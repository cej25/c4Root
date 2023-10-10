#ifndef FrsReader_H
#define FrsReader_H

#include "c4Reader.h"
#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_frs.h"
}

class TClonesArray;

struct EXT_STR_h101_FRS_t;
typedef struct EXT_STR_h101_FRS_t EXT_STR_h101_FRS;
typedef struct EXT_STR_h101_FRS_onion_t EXT_STR_h101_FRS_onion;
class ext_data_struct_info;

class FrsReader : public c4Reader
{
    public:
        FrsReader(EXT_STR_h101_FRS_onion*, size_t);

        virtual ~FrsReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        unsigned int fNEvent;
        
        EXT_STR_h101_FRS_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;
    
    public:
        ClassDefOverride(FrsReader, 0);
};

#endif