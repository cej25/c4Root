#ifndef FimpReader_H
#define FimpReader_H 

#include "FimpData.h"
#include "c4Reader.h"

#include <Rtypes.h>
#include <vector>

extern "C"
{
    #include "ext_h101_fimp.h"
}

class TClonesArray;
class FimpItem;

struct EXT_STR_h101_fimp_t;
typedef struct EXT_STR_h101_fimp_t EXT_STR_h101_fimp;
typedef struct EXT_STR_h101_fimp_onion_t EXT_STR_h101_fimp_onion;
class ext_data_struct_info;

class FimpReader : public c4Reader
{
    public:
        FimpReader(EXT_STR_h101_fimp_onion*, size_t);

        virtual ~FimpReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        void ZeroArrays();
        void ClearVectors();

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        unsigned fNEvent;

        EXT_STR_h101_fimp_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        int NBoards = 1;
        
        int32_t energy;

        std::vector<FimpItem>* fimpArray;


    public:
        ClassDefOverride(FimpReader, 0);
};

#endif
