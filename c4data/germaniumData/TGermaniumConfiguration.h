#ifndef TGermaniumConfiguration_H
#define TGermaniumConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>


//structs

class TGermaniumConfiguration
{
    public:
        static TGermaniumConfiguration const* GetInstance();
        static void Create();
        static void SetDetectorMapFile(std::string fp) { filepath = fp; }

        std::map<std::pair<int,int>,std::pair<int,int>> Mapping() const;
        bool MappingLoaded() const;
        int NDetectors() const;
        int NCrystals() const;
        int NCrystalsPerDet() const;
        int NFebexBoards() const;
        int TM_Undelayed() const;
        int TM_Delayed() const;
        int SC41L() const;
        int SC41R() const;
        std::set<int> ExtraSignals() const;

    private:

        static std::string filepath;
        TGermaniumConfiguration();
        void ReadConfiguration();

        static TGermaniumConfiguration* instance;
        
        std::map<std::pair<int,int>,std::pair<int,int>> detector_mapping;
        std::set<int> extra_signals;

        int num_detectors;
        int num_crystals;
        int crystals_per_det;
        int num_febex_boards;

        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;

        bool DetectorMap_loaded = 0;
};

inline TGermaniumConfiguration const* TGermaniumConfiguration::GetInstance()
{
    if (!instance)
    {
        TGermaniumConfiguration::Create();
    }
    return instance;
}

inline void TGermaniumConfiguration::Create()
{
    delete instance;
    instance = new TGermaniumConfiguration();
}

inline std::map<std::pair<int,int>,std::pair<int,int>> TGermaniumConfiguration::Mapping() const
{
    return detector_mapping;
}

inline int TGermaniumConfiguration::NDetectors() const
{
    return num_detectors;
}

inline int TGermaniumConfiguration::NCrystals() const
{
    return num_crystals;
}

inline int TGermaniumConfiguration::NCrystalsPerDet() const
{
    return crystals_per_det;
}

inline int TGermaniumConfiguration::NFebexBoards() const
{
    return num_febex_boards;
}

inline bool TGermaniumConfiguration::MappingLoaded() const
{
    return DetectorMap_loaded;
}

inline int TGermaniumConfiguration::TM_Undelayed() const
{
    return tm_undelayed;
}

inline int TGermaniumConfiguration::TM_Delayed() const
{
    return tm_delayed;
}

inline int TGermaniumConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TGermaniumConfiguration::SC41R() const
{
    return sc41r_d;
}

#endif