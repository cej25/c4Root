#ifndef FrsVFTXCalData_H
#define FrsVFTXCalData_H

#include <vector>
#include "TObject.h"

class FrsVFTXCalData : public TObject
{
    public:
        FrsVFTXCalData();

        FrsVFTXCalData(std::vector<uint32_t>* TRaw_vftx);

        virtual ~FrsVFTXCalData() {};

        inline const std::vector<uint32_t>* Get_TRaw_vftx() const { return fTRaw_vftx; }

    private:

        std::vector<uint32_t> fTRaw_vftx[8];

    public:
        ClassDef(FrsVFTXCalData, 1);
    
};


#endif