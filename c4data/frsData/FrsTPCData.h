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

        FrsTPCData(std::vector<uint32_t> V775_Geo,
                std::vector<uint32_t> V775_Channel,
                std::vector<uint32_t> V775_Data,
                std::vector<uint32_t> V785_Geo,
                std::vector<uint32_t> V785_Channel,
                std::vector<uint32_t> V785_Data,
                std::vector<uint32_t> V1190_Channel,
                std::vector<uint32_t> V1190_Data,
                std::vector<uint32_t> V1190_LoT);
        
        virtual ~FrsTPCData() {}

        // Getters
        inline const std::vector<uint32_t>& Get_V775_Geo() const { return fV775_Geo; }
        inline const std::vector<uint32_t>& Get_V775_Channel() const { return fV775_Channel; }
        inline const std::vector<uint32_t>& Get_V775_Data() const { return fV775_Data; }
        inline const std::vector<uint32_t>& Get_V785_Geo() const { return fV785_Geo; }
        inline const std::vector<uint32_t>& Get_V785_Channel() const { return fV785_Channel; }
        inline const std::vector<uint32_t>& Get_V785_Data() const { return fV785_Data; }
        inline const std::vector<uint32_t>& Get_V1190_Channel() const { return fV1190_Channel; }
        inline const std::vector<uint32_t>& Get_V1190_Data() const { return fV1190_Data; }
        inline const std::vector<uint32_t>& Get_V1190_LoT() const { return fV1190_LoT; }

        // Setters
    
    private:

        std::vector<uint32_t> fV775_Geo;
        std::vector<uint32_t> fV775_Channel;
        std::vector<uint32_t> fV775_Data;
        
        std::vector<uint32_t> fV785_Geo;
        std::vector<uint32_t> fV785_Channel;
        std::vector<uint32_t> fV785_Data;

        std::vector<uint32_t> fV1190_Channel;
        std::vector<uint32_t> fV1190_Data;
        std::vector<uint32_t> fV1190_LoT;

    public:
        ClassDef(FrsTPCData, 1)
};


#endif