#ifndef TCorrelationsConfiguration_H
#define TCorrelationsConfiguration_H

#include <map>
#include <vector>
#include "c4Logger.h"

class TCorrelationsConfiguration
{
    public:
        static TCorrelationsConfiguration const* GetInstance();
        static void Create();
        static void SetCorrelationsFile(std::string fp) { filepath = fp; }

        std::map<std::string, std::vector<int>> CorrelationsMap() const;
        std::map<std::string, std::vector<int>> TimeMachineMap() const;

    private:
        static std::string filepath;
        TCorrelationsConfiguration();
        void ReadCorrelationsFile();

        static TCorrelationsConfiguration* instance;

        std::map<std::string, std::vector<int>> correlations_map;
        std::map<std::string, std::vector<int>> timemachine_map;

        bool CorrelationsMap_Loaded = 0;
        bool TimeMachineMap_Loaded = 0;

        // stuff
    
};

inline TCorrelationsConfiguration const* TCorrelationsConfiguration::GetInstance()
{
    if (!instance)
    {
        c4LOG(info, "creating instance of correlationsconfig, testing.. ");
        TCorrelationsConfiguration::Create();
    }
    return instance;
}

inline void TCorrelationsConfiguration::Create()
{
    delete instance;
    instance = new TCorrelationsConfiguration();
}

inline std::map<std::string, std::vector<int>> TCorrelationsConfiguration::CorrelationsMap() const
{
    c4LOG(info, "Passing correlations map to some function...testing");
    return correlations_map;
}

inline std::map<std::string, std::vector<int>> TCorrelationsConfiguration::TimeMachineMap() const
{
    return timemachine_map;
}



#endif
