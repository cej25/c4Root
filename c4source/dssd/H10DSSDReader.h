#ifndef H10DSSDReader_H
#define H10DSSDReader_H

#include "BB7FebexData.h"
#include "c4Reader.h"

#include <Rtypes.h>
#include <vector>

extern "C"
{
    #include "ext_h101_bbfebex.h"
}

class TClonesArray;

struct EXT_STR_h101_bbfebex_t;
typedef struct EXT_STR_h101_bbfebex_t EXT_STR_h101_bbfebex;
typedef struct EXT_STR_h101_bbfebex_onion_t EXT_STR_h101_bbfebex_onion;
class ext_data_struct_info;

class H10DSSDReader : public c4Reader
{
    public:
        H10DSSDReader(EXT_STR_h101_bbfebex_onion*, size_t);

        virtual ~H10DSSDReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        Int_t fNEvent;

        EXT_STR_h101_bbfebex_onion* fData;

        size_t fOffset;

        Bool_t fOnline;
        
        TClonesArray* fArray;

        const int NBoards = 4; // maximum 4 FEBEX boards best case scenario?

        int32_t energy;
        int64_t wr_t_first = 0;
        int64_t wr_t_second = 0;

        std::vector<BB7FebexItem>* bb7array;
        std::vector<BB7EmptyItem>* bb7empty;

        Int_t nReads = 0;
        Int_t n_zero_f0_0 = 0;
        Int_t n_zero_f0_1 = 0;

    
    public:
        ClassDefOverride(H10DSSDReader, 1);


};

#endif