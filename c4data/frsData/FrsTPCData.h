#ifndef FrsTPCData_H
#define FrsTPCData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class TClonesArray;

class FrsTPCData : public TObject
{
    public:
        FrsTPCData();

        FrsTPCData(std::vector<uint32_t>* v7x5_geo,
                std::vector<uint32_t>* v7x5_channel,
                std::vector<uint32_t>* v7x5_data,
                std::vector<uint32_t> V1190_Channel,
                std::vector<uint32_t> V1190_Data,
                std::vector<uint32_t> V1190_LoT);
        
        virtual ~FrsTPCData() {}

        // Getters
        inline std::vector<uint32_t>* Get_v7x5_geo() { return fv7x5_geo; }
        inline std::vector<uint32_t>* Get_v7x5_channel() { return fv7x5_channel; }
        inline std::vector<uint32_t>* Get_v7x5_data() { return fv7x5_data; }

        inline const std::vector<uint32_t>& Get_V1190_Channel() const { return fV1190_Channel; }
        inline const std::vector<uint32_t>& Get_V1190_Data() const { return fV1190_Data; }
        inline const std::vector<uint32_t>& Get_V1190_LoT() const { return fV1190_LoT; }

        // Setters
    
    private:

        std::vector<uint32_t> fv7x5_geo[2];
        std::vector<uint32_t> fv7x5_channel[2];
        std::vector<uint32_t> fv7x5_data[2];

        std::vector<uint32_t> fV1190_Channel;
        std::vector<uint32_t> fV1190_Data;
        std::vector<uint32_t> fV1190_LoT;

    public:
        ClassDef(FrsTPCData, 1)
};

class FrsTPCV7X5Item : public TObject
{
    public:
        FrsTPCV7X5Item();

        void SetAll(uint32_t g, uint32_t data, uint32_t ch);
        void Reset();

        uint32_t Get_geo() const;
        uint32_t Get_v7x5_data() const;
        uint32_t Get_channel() const;

        ClassDefNV(FrsTPCV7X5Item, 2);
    
    private:
        // members
        uint32_t geo;
        uint32_t v7x5_data;
        uint32_t channel;
};

class FrsTPCV1190Item : public TObject
{
    public:
        FrsTPCV1190Item();

        void SetAll(uint32_t ch, uint32_t data, uint32_t lot);
        void Reset();

        uint32_t Get_channel() const;
        uint32_t Get_v1190_data() const;
        uint32_t Get_leadOrTrail() const;

        ClassDefNV(FrsTPCV1190Item, 2);
    
    private:
        // members
        uint32_t channel;
        uint32_t v1190_data;
        uint32_t leadOrTrail;
};

inline uint32_t FrsTPCV7X5Item::Get_channel() const
{
    return channel;
}

inline uint32_t FrsTPCV7X5Item::Get_v7x5_data() const
{
    return v7x5_data;
}

inline uint32_t FrsTPCV7X5Item::Get_geo() const
{
    return geo;
}

inline uint32_t FrsTPCV1190Item::Get_channel() const
{
    return channel;
}

inline uint32_t FrsTPCV1190Item::Get_leadOrTrail() const
{
    return leadOrTrail;
}

inline uint32_t FrsTPCV1190Item::Get_v1190_data() const
{
    return v1190_data;
}

#endif