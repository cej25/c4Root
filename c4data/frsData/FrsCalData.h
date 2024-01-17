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
                //uint32_t increase_scaler_temp[32], 
                uint32_t extraction_time_ms, 
                uint32_t ibin_clean_for_s, 
                uint32_t ibin_clean_for_100ms);//,
                // V792
                //uint32_t de_array[14],
                // V1290
               // std::vector<uint32_t> tdc_array[15]);//,
                //uint32_t music_t1[8],
                //uint32_t music_t2[8]);

        virtual ~FrsCalData() {}

        // Getters -- what did we need these for again?
        // Setters

    protected:

        uint64_t fWR_TS;

        // could also put these in an array
        uint32_t fTimeMs;
        uint32_t fIBinS;
        uint32_t fIBin100Ms;
        //uint32_t* fIncreaseScalerTemp; // 32 length array
        uint32_t fExtractionTime;
        uint32_t fIBinSClean;
        uint32_t fIBin100MsClean;

        // put these in arrays
        //uint32_t* fDe_array; // 14 length
     
        // put this in TObjectArray?
        //std::vector<uint32_t>* fTdc_array; // 15 length
        //uint32_t* test[3];

        // we have to figure out how to make these work.
        //uint32_t* fMusicT1; // 8 length
        //uint32_t* fMusicT2; // 8 length

    public:
        ClassDef(FrsCalData, 1);
    
};



#endif















/*
class FrsCalData : public TObject
{
    public:
       // FrsCalData();

        FrsCalData(uint64_t WR_TS, uint32_t time_in_ms, 
                uint32_t ibin_for_s, uint32_t ibin_for_100ms, 
                int increase_scaler_temp[32], 
                uint32_t extraction_time_ms, 
                uint32_t ibin_clean_for_s, 
                uint32_t ibin_clean_for_100ms,
                // V792
                // mapped array?
                uint32_t de_array[14],
                uint32_t de_41r, uint32_t de_21l, uint32_t de_21r, 
                uint32_t de_42l, uint32_t de_42r, uint32_t de_81l,
                uint32_t de_22r, uint32_t de_31l, uint32_t de_31r, 
                uint32_t de_43l, uint32_t de_43r, uint32_t de_41l,
                uint32_t de_81r, uint32_t de_22l,
                // V1290
                std::vector<uint32_t> tdc_array[15]//,
                std::vector<uint32_t> tdc_sc41l, 
                std::vector<uint32_t> tdc_sc41r, 
                std::vector<uint32_t> tdc_sc21l, 
                std::vector<uint32_t> tdc_sc21r,
                std::vector<uint32_t> tdc_sc42l,
                std::vector<uint32_t> tdc_sc43l, 
                std::vector<uint32_t> tdc_sc43r, 
                std::vector<uint32_t> tdc_sc81l,
                std::vector<uint32_t> tdc_sc81r, 
                std::vector<uint32_t> tdc_sc31l, 
                std::vector<uint32_t> tdc_sc31r, 
                std::vector<uint32_t> tdc_sc11,
                std::vector<uint32_t> tdc_sc22l, 
                std::vector<uint32_t> tdc_sc22r, 
                std::vector<uint32_t> tdc_sc42r,
                // these are [8] arrays, howwww
                uint32_t music_t1[8], 
                uint32_t music_t2[8]);

        virtual ~FrsCalData() {}

        // Getters -- what did we need these for again?
        // Setters

    private:

        uint64_t fWR_TS;

        // could also put these in an array
        uint32_t fTimeMs;
        uint32_t fIBinS;
        uint32_t fIBin100Ms;
        int fIncreaseScalerTemp[32];
        uint32_t fExtractionTime;
        uint32_t fIBinSClean;
        uint32_t fIBin100MsClean;

        // put these in arrays
        uint32_t fDe_array[14];
        uint32_t fDe41r; 
        uint32_t fDe21l;
        uint32_t fDe21r;
        uint32_t fDe42l;
        uint32_t fDe42r;
        uint32_t fDe81l;
        uint32_t fDe22r;
        uint32_t fDe31l;
        uint32_t fDe31r;
        uint32_t fDe43l;
        uint32_t fDe43r;
        uint32_t fDe41l;
        uint32_t fDe81r;
        uint32_t fDe22l;

        // put this in TObjectArray
        std::vector<uint32_t> fTdc_array[15];
        std::vector<uint32_t> fSc41l;
        std::vector<uint32_t> fSc41r;
        std::vector<uint32_t> fSc21l;
        std::vector<uint32_t> fSc21r;
        std::vector<uint32_t> fSc42l;
        std::vector<uint32_t> fSc43l;
        std::vector<uint32_t> fSc43r;
        std::vector<uint32_t> fSc81l;
        std::vector<uint32_t> fSc81r;
        std::vector<uint32_t> fSc31l;
        std::vector<uint32_t> fSc31r;
        std::vector<uint32_t> fSc11;
        std::vector<uint32_t> fSc22l;
        std::vector<uint32_t> fSc22r;
        std::vector<uint32_t> fSc42r;

        // we have to figure out how to make these work.
        uint32_t fMusicT1[8];
        uint32_t fMusicT2[8];

    public:
        ClassDef(FrsCalData, 1);
    
};

*/