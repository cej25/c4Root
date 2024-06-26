#ifndef LisaReader_H
#define LisaReader_H 

#include "LisaData.h"
#include "c4Reader.h"

#include "TClonesArray.h"
#include <Rtypes.h>
#include <vector>

extern "C"
{
    #include "ext_h101_lisa.h"
}

class TClonesArray;
class LisaItem;

struct EXT_STR_h101_lisa_t;
typedef struct EXT_STR_h101_lisa_t EXT_STR_h101_lisa;
typedef struct EXT_STR_h101_lisa_onion_t EXT_STR_h101_lisa_onion;
class ext_data_struct_info;

class LisaReader : public c4Reader
{
    public:
        LisaReader(EXT_STR_h101_lisa_onion*, size_t);

        virtual ~LisaReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        void ZeroArrays();
        void ClearVectors();

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        unsigned fNEvent;

        EXT_STR_h101_lisa_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        int NBoards = 1;
        
        int32_t energy;

        std::vector<LisaItem>* lisaArray;


    public:
        ClassDefOverride(LisaReader, 0);
};

#endif
