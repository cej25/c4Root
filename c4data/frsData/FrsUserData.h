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
        FrsUserData(uint32_t Scalers_N, 
                    std::vector<uint32_t> Scalers_Index, 
                    std::vector<uint32_t> V830_Scalers,
                    std::vector<uint32_t>* v7x5_geo,
                    std::vector<uint32_t>* v7x5_channel,
                    std::vector<uint32_t>* v7x5_data);
        
        virtual ~FrsUserData() {}

        // Getters
        inline const Int_t Get_Scalers_N() const { return fScalers_N; }

        inline const std::vector<uint32_t>& Get_Scalers_Index() const { return fScalers_Index; }
        inline const std::vector<uint32_t>& Get_V830_Scalers() const { return fV830_Scalers; }

        inline std::vector<uint32_t>* Get_v7x5_geo_user() { return fv7x5_geo_user; }
        inline std::vector<uint32_t>* Get_v7x5_channel_user() { return fv7x5_channel_user; }
        inline std::vector<uint32_t>* Get_v7x5_data_user() { return fv7x5_data_user; }


        // Setters
    
    private:
        Int_t fScalers_N;
        std::vector<uint32_t> fScalers_Index;
        std::vector<uint32_t> fV830_Scalers;

        std::vector<uint32_t> fv7x5_geo_user[4];
        std::vector<uint32_t> fv7x5_channel_user[4];
        std::vector<uint32_t> fv7x5_data_user[4];
    

    public:
        ClassDef(FrsUserData, 1)
};


#endif