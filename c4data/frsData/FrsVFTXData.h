#ifndef FrsVFTXData_H
#define FrsVFTXData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class TClonesArray;

class FrsVFTXData : public TObject
{
    public:
        FrsVFTXData();

        FrsVFTXData(std::vector<uint32_t>* vftx_lead_times);
        
        virtual ~FrsVFTXData() {}

        // Getters
        inline const std::vector<uint32_t>* Get_vftx_lead_times() const { return fvftx_lead_times; }

        // Setters
    
    private:

        std::vector<uint32_t> fvftx_lead_times[16];

    public:
        ClassDef(FrsVFTXData, 1)
};


#endif