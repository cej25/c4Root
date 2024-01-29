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


#endif