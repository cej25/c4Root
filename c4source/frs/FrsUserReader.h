#ifndef FrsUserReader_H
#define FrsUserReader_H


#include "FrsUserData.h"
#include "c4Reader.h"
#include <Rtypes.h>
#include <vector>

extern "C"
{
    #include "ext_h101_frsuser.h"
}

class TClonesArray;
class FrsUserData;

struct EXT_STR_h101_frsuser_t;
typedef struct EXT_STR_h101_frsuser_t EXT_STR_h101_frsuser;
typedef struct EXT_STR_h101_frsuser_onion_t EXT_STR_h101_frsuser_onion;
class ext_data_struct_info;

class FrsUserReader : public c4Reader
{
    public:
        FrsUserReader(EXT_STR_h101_frsuser_onion*, size_t);

        virtual ~FrsUserReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        void ZeroArrays();
        void ClearVectors();

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }
    
    private:
        Int_t fNEvent = 0;

        EXT_STR_h101_frsuser_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;
        std::vector<FrsUserV7X5Item>* v7x5array;
        std::vector<FrsUserV830Item>* v830array;



        uint32_t scalers_n;
        std::vector<uint32_t> scalers_index;
        std::vector<uint32_t> scalers_user;

        std::vector<uint32_t> v7x5_geo[4];
        std::vector<uint32_t> v7x5_channel[4];
        std::vector<uint32_t> v7x5_data[4];

        


    public:
        ClassDefOverride(FrsUserReader, 0);

};

#endif
