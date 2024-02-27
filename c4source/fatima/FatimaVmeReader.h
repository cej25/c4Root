#ifndef FatimaVmeReader_H
#define FatimaVmeReader_H

#include "c4Reader.h"

#include <Rtypes.h>

extern "C"
{
    #include "ext_h101_fatimavme.h"
}

class TClonesArray;

struct EXT_STR_h101_fatimavme_t;
typedef struct EXT_STR_h101_fatimavme_t EXT_STR_h101_fatimavme;
typedef struct EXT_STR_h101_fatimavme_onion_t EXT_STR_h101_fatimavme_onion;
class ext_data_struct_info;

// struct
// jesus fatima reader got weird

class FatimaVmeReader : public c4Reader
{
    public:
        FatimaVmeReader(EXT_STR_h101_fatimavme_onion*, size_t);

        virtual ~FatimaVmeReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

        // FT Calib?

        // GetFT?

        // misc...........


    private:

        Int_t fNEvent = 0;
        Bool_t fOnline;

        EXT_STR_h101_fatimavme_onion* fData;
        size_t fOffset;

        TClonesArray* fArray;

        // bunch of stuff we might need

        // number of QDC boards. etc

        uint64_t wr_t;


    public:
        ClassDefOverride(FatimaVmeReader, 1);

};


#endif