#ifndef FrsMainCalData_H
#define FrsMainCalData_H

#include <vector>
#include "TObject.h"
#include "c4Logger.h"

class FrsMainCalData : public TObject
{
    public:
        FrsMainCalData();

        FrsMainCalData(uint64_t WR_TS, 
                uint32_t Scalers_N, 
                std::vector<uint32_t> Scalers_Index, 
                std::vector<uint32_t> V830_Scalers,
                // V792
                const uint32_t* de_array,
                // V1290
                const std::vector<uint32_t>* tdc_array,
                const uint32_t* music_t1,
                const uint32_t* music_t2);

        ~FrsMainCalData();

        inline const uint64_t Get_wr_t() const { return fWR_TS; }
        
        
        inline const Int_t Get_Scalers_N() const { return fScalers_N; }
        inline const std::vector<uint32_t>& Get_Scalers_Index() const { return fScalers_Index; }
        inline const std::vector<uint32_t>& Get_V830_Scalers() const { return fV830_Scalers; }
        
        inline const uint32_t* Get_De_array() const { return fDe_array; }
        inline const uint32_t Get_De_channel(int channel) const {
            c4LOG_IF(fatal,channel>=14,"Index too large.");
            return fDe_array[channel];
        }

        
        inline const std::vector<uint32_t>* Get_TDC_array() const { return fTdc_array; }
        inline const std::vector<uint32_t> Get_TDC_channel(int channel) const { 
            c4LOG_IF(fatal,channel>14,"Index too large");
            return fTdc_array[channel]; 
        }

        inline const uint32_t* Get_music_t1() const { return fmusic_t1; }
        inline const uint32_t* Get_music_t2() const { return fmusic_t2; }
        // Setters

    private:

        uint64_t fWR_TS;

        Int_t fScalers_N;
        std::vector<uint32_t> fScalers_Index;
        std::vector<uint32_t> fV830_Scalers;

        // put these in arrays
        uint32_t fDe_array[14];
     
        std::vector<uint32_t> fTdc_array[15]; // 15 length

        uint32_t fmusic_t1[8]; // 8 length
        uint32_t fmusic_t2[8]; // 8 length

    public:
        ClassDef(FrsMainCalData, 1);
    
};


#endif