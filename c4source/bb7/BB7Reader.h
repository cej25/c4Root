#ifndef BB7Reader_H
#define BB7Reader_H

#include "c4Reader.h"

#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_bb7febex.h"
}

class TClonesArray;

struct EXT_STR_h101_bb7febex_t;
typedef struct EXT_STR_h101_bb7febex_t EXT_STR_h101_bb7febex;
typedef struct EXT_STR_h101_bb7febex_onion_t EXT_STR_h101_bb7febex_onion;
class ext_data_struct_info;

class BB7Reader : public c4Reader
{
    public:
        BB7Reader(EXT_STR_h101_bb7febex_onion*, size_t);

        virtual ~BB7Reader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        Int_t fNEvent;

        EXT_STR_h101_bb7febex_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;

        // 
        uint64_t wr_t;
    
    public:
        ClassDefOverride(BB7Reader, 1);


};

#endif