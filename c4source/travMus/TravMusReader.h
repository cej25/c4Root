#ifndef TravMusReader_H
#define TravMusReader_H

#include "TravMusData.h"
#include "c4Reader.h"
#include <Rtypes.h>
#include <vector>
#include "EventHeader.h"

extern "C"
{
    #include "ext_h101_travmus.h"
}

class TravMusData;

struct EXT_STR_h101_travmus_t;
typedef struct EXT_STR_h101_travmus_t EXT_STR_h101_travmus;
typedef struct EXT_STR_h101_travmus_onion_t EXT_STR_h101_travmus_onion;
class ext_data_struct_info;

class TravMusReader : public c4Reader
{
    public:
        TravMusReader(EXT_STR_h101_travmus_onion*, size_t);

        virtual ~TravMusReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        void ZeroArrays();
        void ClearVectors();

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:

        unsigned int fNEvent;
        
        EXT_STR_h101_travmus_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        EventHeader* header;

        std::vector<TravMusAdcItem>* adcArray;
        std::vector<TravMusTdcItem>* tdcArray;

    public:
        ClassDefOverride(TravMusReader, 0);
};

#endif