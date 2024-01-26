#ifndef FrsUserData_H
#define FrsUserData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class TClonesArray;

class FrsUserData : public TObject
{
    public:
        FrsUserData();
        FrsUserData(uint32_t, std::vector<uint32_t> ,  std::vector<uint32_t>);
        
        virtual ~FrsUserData() {}

        // Getters
        inline const Int_t Get_Scalers_N() const { return fScalers_N; }

        inline const std::vector<uint32_t>& Get_Scalers_Index() const { return fScalers_Index; }
        inline const std::vector<uint32_t>& Get_V830_Scalers() const { return fV830_Scalers; }


        // Setters
    
    private:
        Int_t fScalers_N;
        std::vector<uint32_t> fScalers_Index;
        std::vector<uint32_t> fV830_Scalers;

    

    public:
        ClassDef(FrsUserData, 1)
};


#endif