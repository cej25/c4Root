#ifndef FrsUserCalData_H
#define FrsUserCalData_H

#include <vector>
#include "TObject.h"

class FrsUserCalData : public TObject
{
    public:
        FrsUserCalData();

        FrsUserCalData(uint32_t Scalers_N, 
                    std::vector<uint32_t> Scalers_Index, 
                    std::vector<uint32_t> V830_Scalers,
                    uint32_t* dt_array,
                    uint32_t* music_e1,
                    uint32_t* music_e2);

        virtual ~FrsUserCalData() {}

        // Getters
        inline const Int_t Get_Scalers_N() const { return fScalers_N; }
        inline const std::vector<uint32_t>& Get_Scalers_Index() const { return fScalers_Index; }
        inline const std::vector<uint32_t>& Get_V830_Scalers() const { return fV830_Scalers; }

        inline uint32_t* Get_dt_array() { return fdt_array; }
        inline uint32_t* Get_music_e1() { return fmusic_e1; }
        inline uint32_t* Get_music_e2() { return fmusic_e2; }

    private:

        Int_t fScalers_N;
        std::vector<uint32_t> fScalers_Index;
        std::vector<uint32_t> fV830_Scalers;

        uint32_t fdt_array[16];
        uint32_t fmusic_e1[8];
        uint32_t fmusic_e2[8];
        

    public:
        ClassDef(FrsUserCalData, 1);
    
};


#endif