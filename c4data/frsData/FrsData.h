#ifndef FrsData_H
#define FrsData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class TClonesArray;

class FrsData : public TObject
{
    public:
        // Default Constructor
        FrsData();

        FrsData(uint64_t WR_TS, 
                uint32_t Scalers_N, 
                std::vector<uint32_t> Scalers_Index, 
                std::vector<uint32_t> V830_Scalers,
                uint32_t V792_Geo,
                std::vector<uint32_t> V792_Channel,
                std::vector<uint32_t> V792_Data,
                std::vector<uint32_t> V1290_Channel,
                std::vector<uint32_t> V1290_Data,
                std::vector<uint32_t> V1290_LoT);

        // Destructor
        virtual ~FrsData() {}

        inline const uint64_t Get_WR() const { return fWR_TS; }
        inline const Int_t Get_Scalers_N() const { return fScalers_N; }
        // return pointer?
        inline const std::vector<uint32_t>& Get_Scalers_Index() const { return fScalers_Index; }
        inline const std::vector<uint32_t>& Get_V830_Scalers() const { return fV830_Scalers; }
        inline const uint32_t Get_V792_Geo() const { return fV792_Geo; }
        inline const std::vector<uint32_t>& Get_V792_Channel() const { return fV792_Channel; }
        inline const std::vector<uint32_t>& Get_V792_Data() const { return fV792_Data; }
        inline const std::vector<uint32_t>& Get_V1290_Channel() const { return fV1290_Channel; }
        inline const std::vector<uint32_t>& Get_V1290_Data() const { return fV1290_Data; }
        inline const std::vector<uint32_t>& Get_V1290_LoT() const { return fV1290_LoT; }


        // Getters
       /* inline const UInt_t GetTdcData() const { return tdcData; }
        inline const int GetChan() const { return channel; }
        inline const int GetLot() const { return leadOrTrail; }

        inline const UInt_t GetTpatTs() const { return tpat_ts; }
        inline const UInt_t GetTpatTrig() const { return tpat_trig; }
        inline const UInt_t GetTpatData() const { return tpat_data; }


        // Setters
        void SetTdcData(UInt_t v) { tdcData = v; }
        void SetChan(int v) { channel = v; }
        void SetLot(int v) { leadOrTrail = v; }


        void SetTpatTs(UInt_t v) { tpat_ts = v; }
        void SetTpatTrig(UInt_t v) { tpat_trig = v; }
        void SetTpatData(UInt_t v) { tpat_data = v; }*/


    protected:

        uint64_t fWR_TS;

        Int_t fScalers_N;
        std::vector<uint32_t> fScalers_Index;
        std::vector<uint32_t> fV830_Scalers;

        uint32_t fV792_Geo;
        std::vector<uint32_t> fV792_Channel;
        std::vector<uint32_t> fV792_Data;

        std::vector<uint32_t> fV1290_Channel;
        std::vector<uint32_t> fV1290_Data;
        std::vector<uint32_t> fV1290_LoT;

    public:
        ClassDef(FrsData, 1)
};


#endif


