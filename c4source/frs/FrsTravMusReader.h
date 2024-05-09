#ifndef FrsTravMusReader_H
#define FrsTravMusReader_H

#include "FrsTravMusData.h"
#include "c4Reader.h"
#include <Rtypes.h>
#include <vector>
#include "EventHeader.h"

extern "C"
{
    #include "ext_h101_travmus.h"
}

class FrsTravMusData;

struct EXT_STR_h101_travmus_t;
typedef struct EXT_STR_h101_travmus_t EXT_STR_h101_travmus;
typedef struct EXT_STR_h101_travmus_onion_t EXT_STR_h101_travmus_onion;
class ext_data_struct_info;

class FrsTravMusReader : public c4Reader
{
    public:
        FrsTravMusReader(EXT_STR_h101_travmus_onion*, size_t);

        virtual ~FrsTravMusReader();

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

        std::vector<FrsTravMusAdcItem>* adcArray;
        std::vector<FrsTravMusTdcItem>* tdcArray;

    public:
        ClassDefOverride(FrsTravMusReader, 0);
};

#endif