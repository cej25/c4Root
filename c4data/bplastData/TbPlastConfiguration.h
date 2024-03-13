#ifndef TbPlastConfiguration_H
#define TbPlastConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

class TbPlastConfiguration
{
    public:
        static TbPlastConfiguration const* GetInstance();
        static void Create();
        static void SetDetectorMapFile(std::string fp) { filepath = fp; }

        std::map<std::pair<int, int>, std::pair<int, std::pair<std::string, std::string>>> Mapping() const;
        int NDetectors() const;
        int NUpDetectors() const;
        std::set<int> UpDetectors() const;
        int NDownDetectors() const;
        std::set<int> DownDetectors() const;
        int NTopDetectors() const;
        std::set<int> TopDetectors() const;
        int NBottomDetectors() const;
        std::set<int> BottomDetectors() const;
        int NLeftDetectors() const;
        std::set<int> LeftDetectors() const;
        int NRightDetectors() const;
        std::set<int> RightDetectors() const;
        int NTamexBoards() const;
        bool MappingLoaded() const;
        int TM_Undelayed() const;
        int TM_Delayed() const;
        int SC41L() const;
        int SC41R() const;
        std::set<int> ExtraSignals() const;
    
    private:

        static std::string filepath;
        TbPlastConfiguration();
        void ReadConfiguration();

        static TbPlastConfiguration* instance;

        std::map<std::pair<int, int>, std::pair<int, std::pair<std::string, std::string>>> detector_mapping;
        std::set<int> up_detectors;
        std::set<int> down_detectors;
        std::set<int> top_detectors;
        std::set<int> bottom_detectors;
        std::set<int> left_detectors;
        std::set<int> right_detectors;
        std::set<int> extra_signals;

        int num_detectors;
        int num_tamex_boards;
        // stream
        int num_up_detectors;
        int num_down_detectors;
        // orientation
        int num_top_detectors;
        int num_bottom_detectors;
        int num_left_detectors;
        int num_right_detectors;

        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;
        int fatima_accept;
        int fatima_free;

        bool DetectorMap_loaded = 0;

};

inline TbPlastConfiguration const* TbPlastConfiguration::GetInstance()
{
    if (!instance)
    {
        TbPlastConfiguration::Create();
    }
    return instance;
}

inline void TbPlastConfiguration::Create()
{
    delete instance;
    instance = new TbPlastConfiguration();
}

inline std::map<std::pair<int, int>, std::pair<int, std::pair<std::string, std::string>>> TbPlastConfiguration::Mapping() const
{
    return detector_mapping;
}

inline bool TbPlastConfiguration::MappingLoaded() const
{
    return DetectorMap_loaded;
}

inline std::set<int> TbPlastConfiguration::UpDetectors() const
{
    return up_detectors;
}

inline std::set<int> TbPlastConfiguration::DownDetectors() const
{
    return down_detectors;
}

inline std::set<int> TbPlastConfiguration::TopDetectors() const
{
    return top_detectors;
}

inline std::set<int> TbPlastConfiguration::BottomDetectors() const
{
    return bottom_detectors;
}

inline std::set<int> TbPlastConfiguration::LeftDetectors() const
{
    return left_detectors;
}

inline std::set<int> TbPlastConfiguration::RightDetectors() const
{
    return right_detectors;
}

inline int TbPlastConfiguration::TM_Undelayed() const
{
    return tm_undelayed;
}

inline int TbPlastConfiguration::TM_Delayed() const
{
    return tm_delayed;
}

inline int TbPlastConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TbPlastConfiguration::SC41R() const
{
    return sc41r_d;
}


#endif