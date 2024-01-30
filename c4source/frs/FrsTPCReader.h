#ifndef FrsTPCReader_H
#define FrsTPCReader_H

#include "FrsTPCData.h"
#include "c4Reader.h"
#include <Rtypes.h>
#include <vector>

extern "C"
{
    #include "ext_h101_frstpc.h"
}

class TClonesArray;
class FrsTPCData;


struct EXT_STR_h101_frstpc_t;
typedef struct EXT_STR_h101_frstpc_t EXT_STR_h101_frstpc;
typedef struct EXT_STR_h101_frstpc_onion_t EXT_STR_h101_frstpc_onion;
class ext_data_struct_info;

class FrsTPCReader : public c4Reader
{
    public:
        FrsTPCReader(EXT_STR_h101_frstpc_onion*, size_t);
        
        virtual ~FrsTPCReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        void ZeroArrays();
        void ClearVectors();

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }
    
    private:
        Int_t fNEvent;
        
        EXT_STR_h101_frstpc_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;

        uint64_t fWR_TS;

        std::vector<uint32_t> v7x5_geo[2];
        std::vector<uint32_t> v7x5_channel[2];
        std::vector<uint32_t> v7x5_data[2];

        std::vector<uint32_t> v1190_channel;
        std::vector<uint32_t> v1190_data;
        std::vector<uint32_t> v1190_lot;
    
    public:
        ClassDefOverride(FrsTPCReader, 0);


};

#endif