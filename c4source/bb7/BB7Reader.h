#ifndef BB7Reader_H
#define BB7Reader_H

#include "BB7VmeData.h"
#include "c4Reader.h"

#include <Rtypes.h>
#include <vector>

extern "C"
{
    #include "ext_h101_bb7vme.h"
}

class TClonesArray;
class BB7V7x5Item;

struct EXT_STR_h101_bb7vme_t;
typedef struct EXT_STR_h101_bb7vme_t EXT_STR_h101_bb7vme;
typedef struct EXT_STR_h101_bb7vme_onion_t EXT_STR_h101_bb7vme_onion;
class ext_data_struct_info;

class BB7Reader : public c4Reader
{
    public:
        BB7Reader(EXT_STR_h101_bb7vme_onion*, size_t);

        virtual ~BB7Reader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        Int_t fNEvent;

        EXT_STR_h101_bb7vme_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;
        std::vector<BB7V7x5Item>* v7x5array;

        // 
        uint64_t wr_t;

        std::vector<uint32_t> v7x5_geo;
        std::vector<uint32_t> v7x5_channel;
        std::vector<uint32_t> v7x5_data;
    
    public:
        ClassDefOverride(BB7Reader, 1);


};

#endif