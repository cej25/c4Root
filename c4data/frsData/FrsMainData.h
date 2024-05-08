#ifndef FrsMainData_H
#define FrsMainData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class TClonesArray;

class FrsMainData : public TObject
{
    public:
        // Default Constructor
        FrsMainData();

        FrsMainData(uint32_t Scalers_N, 
                std::vector<uint32_t> Scalers_Index, 
                std::vector<uint32_t> V830_Scalers,
                uint32_t V792_Geo,
                std::vector<uint32_t> V792_Channel,
                std::vector<uint32_t> V792_Data,
                std::vector<uint32_t> V1290_Channel,
                std::vector<uint32_t> V1290_Data,
                std::vector<uint32_t> V1290_LoT);

        // Destructor
        virtual ~FrsMainData() {}

        //inline const uint64_t Get_wr_t() const { return fWR_TS; }
        inline const Int_t Get_Scalers_N() const { return fScalers_N; }

        inline const std::vector<uint32_t>& Get_Scalers_Index() const { return fScalers_Index; }
        inline const std::vector<uint32_t>& Get_V830_Scalers() const { return fV830_Scalers; }
        inline const uint32_t Get_V792_Geo() const { return fV792_Geo; }
        inline const std::vector<uint32_t>& Get_V792_Channel() const { return fV792_Channel; }
        inline const std::vector<uint32_t>& Get_V792_Data() const { return fV792_Data; }
        inline const std::vector<uint32_t>& Get_V1290_Channel() const { return fV1290_Channel; }
        inline const std::vector<uint32_t>& Get_V1290_Data() const { return fV1290_Data; }
        inline const std::vector<uint32_t>& Get_V1290_LoT() const { return fV1290_LoT; }


        // Getters
 


    private:

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
        ClassDef(FrsMainData, 1)
        
};


class FrsMainV1290Item : public TObject
{
    public:
        FrsMainV1290Item();

        void SetAll(uint32_t ch, uint32_t data, uint32_t lot);
        uint32_t Get_channel() const;
        uint32_t Get_v1290_data() const;
        uint32_t Get_leadOrTrail() const;
        void Reset();

        ClassDefNV(FrsMainV1290Item, 2);
    private:
        // members
        uint32_t channel;
        uint32_t v1290_data;
        uint32_t leadOrTrail;
};


class FrsMainV830Item : public TObject
{
    public:
        FrsMainV830Item();
        
        void SetAll(uint32_t in, uint32_t sc);
        void Reset();
        uint32_t Get_index() const;
        uint32_t Get_scaler() const;

        ClassDefNV(FrsMainV830Item, 2);
    private:
        // members
        uint32_t index;
        uint32_t scaler;

};

class FrsMainV792Item : public TObject
{
    public:
        FrsMainV792Item();

        void SetAll(uint32_t ch, uint32_t data, uint32_t g);
        void Reset();
        uint32_t Get_channel() const;
        uint32_t Get_v792_data() const;
        uint32_t Get_geo() const;

        ClassDefNV(FrsMainV792Item, 2);
    private:
        // members
        uint32_t channel;
        uint32_t v792_data;
        uint32_t geo;

};

inline uint32_t FrsMainV792Item::Get_channel() const
{
    return channel;
}

inline uint32_t FrsMainV792Item::Get_v792_data() const
{
    return v792_data;
}

inline uint32_t FrsMainV792Item::Get_geo() const
{
    return geo;
}

inline uint32_t FrsMainV1290Item::Get_v1290_data() const
{
    return v1290_data;
}

inline uint32_t FrsMainV1290Item::Get_leadOrTrail() const
{
    return leadOrTrail;
}

inline uint32_t FrsMainV1290Item::Get_channel() const
{
    return channel;
}

inline uint32_t FrsMainV830Item::Get_index() const
{
    return index;
}

inline uint32_t FrsMainV830Item::Get_scaler() const
{
    return scaler;
}


#endif


