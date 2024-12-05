#ifndef TestReader_H
#define TestReader_H

#include "c4Reader.h"

#include <Rtypes.h>
#include <vector>

extern "C"
{
    #include "ext_h101_test.h"
}

class TClonesArray;

struct FatimaData_t;
typedef struct FatimaData_t FatimaData;
struct EXT_STR_h101_test_t;
typedef struct EXT_STR_h101_test_t EXT_STR_h101_test;
typedef struct EXT_STR_h101_test_onion_t EXT_STR_h101_test_onion;
class ext_data_struct_info;

class TestReader : public c4Reader
{
    public:
        TestReader(EXT_STR_h101_test_onion*, size_t);

        virtual ~TestReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        Int_t fNEvent;
        
        FatimaData* fatima_data;
        EXT_STR_h101_test_onion* fData;

        size_t fOffset;

        Bool_t fOnline;
        
        uint64_t wr_t;

    
    public:
        ClassDefOverride(TestReader, 1);


};

#endif