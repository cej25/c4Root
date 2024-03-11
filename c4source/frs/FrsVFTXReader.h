#ifndef FrsVFTXReader_H
#define FrsVFTXReader_H

#include "FrsVFTXData.h"
#include "c4Reader.h"

#include <TRandom3.h>
#include <Rtypes.h>
#include <vector>

#include "../../config/setup.h"

extern "C"
{
    #include "ext_h101_frsvftx.h"
}

class TClonesArray;
class FrsVFTXData;

struct EXT_STR_h101_frsvftx_t;
typedef struct EXT_STR_h101_frsvftx_t EXT_STR_h101_frsvftx;
typedef struct EXT_STR_h101_frsvftx_onion_t EXT_STR_h101_frsvftx_onion;
class ext_data_struct_info;

class FrsVFTXReader : public c4Reader
{
    public:
        FrsVFTXReader(EXT_STR_h101_frsvftx_onion*, size_t);

        virtual ~FrsVFTXReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        void ZeroArrays();
        void ClearVectors();

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

        void m_VFTX_Bin2Ps();
        Double_t VFTX_GetTRaw_ps(int channel, int cc, int ft, float r);
    
    private:
        Int_t fNEvent = 0;

        EXT_STR_h101_frsvftx_onion* fData;

        size_t fOffset;

        Bool_t fOnline;

        TClonesArray* fArray;

        TRandom3 rand;
        float VFTX_Bin2Ps[VFTX_N][VFTX_MAX_CHN][1000];

        // CEJ: we only seem to use VFTX_MAX_CHN whatever the case
        // (in fact, half of them)
        std::vector<uint32_t> vftx_leading_cc[VFTX_MAX_CHN];
        std::vector<uint32_t> vftx_leading_ft[VFTX_MAX_CHN];
        std::vector<uint32_t> vftx_leading_time[VFTX_MAX_CHN];
        std::vector<uint32_t> vftx_trailing_cc[VFTX_MAX_CHN];
        std::vector<uint32_t> vftx_trailing_ft[VFTX_MAX_CHN];
        std::vector<uint32_t> vftx_trailing_time[VFTX_MAX_CHN];

        bool b_vftx_data = false;

    public:
        ClassDefOverride(FrsVFTXReader, 0);

};

#endif
