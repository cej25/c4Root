#ifndef FrsCalData_H
#define FrsCalData_H

#include <vector>
#include "TObject.h"

class FrsCalData : public TObject
{
    public:
        FrsCalData();

        FrsCalData(uint64_t WR_TS, uint32_t time_in_ms, 
                uint32_t ibin_for_s, uint32_t ibin_for_100ms, 
                const uint32_t* increase_scaler_temp, 
                uint32_t extraction_time_ms, 
                uint32_t ibin_clean_for_s, 
                uint32_t ibin_clean_for_100ms,
                // V792
                const uint32_t* de_array,
                // V1290
                const std::vector<uint32_t>* tdc_array,
                const uint32_t* music_t1,
                const uint32_t* music_t2);

        ~FrsCalData();

        // Getters -- what did we need these for again?
        inline const uint64_t Get_WR() const { return fWR_TS; }
        inline const uint32_t* Get_De_array() const { return fDe_array; }
        inline const std::vector<uint32_t>* Get_TDC_array() const { return fTdc_array; }


        // Setters

    protected:

        uint64_t fWR_TS;

        // could also put these in an array
        uint32_t fTimeMs;
        uint32_t fIBinS;
        uint32_t fIBin100Ms;
        uint32_t fIncreaseScalerTemp[32]; // 32 length array // // gives strange error in TStreamerBuild
        uint32_t fExtractionTime;
        uint32_t fIBinSClean;
        uint32_t fIBin100MsClean;

        // put these in arrays
       // uint32_t* fDe_array; // 14 length
        uint32_t fDe_array[14];
     
        // put this in TObjectArray?
        std::vector<uint32_t> fTdc_array[15]; // 15 length

        // we have to figure out how to make these work.
        uint32_t fMusicT1[8]; // 8 length
        uint32_t fMusicT2[8]; // 8 length

    public:
        ClassDef(FrsCalData, 1);
    
};


#endif