#ifndef TFatimaVmeConfiguration_H
#define TFatimaVmeConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>

// structs

class TFatimaVmeConfiguration
{
    public:
        static TFatimaVmeConfiguration const* GetInstance();
        static void Create();
        static void SetDetectorMapFile(std::string fp) { filepath = fp; }

        std::map<std::pair<int, int>, int> QDCMapping() const;
        int NQDCBoards() const;
        std::map<std::pair<int, int>, int> TDCMapping() const;
        int NTDCBoards() const;
        bool MappingLoaded() const;
        int TM_Undelayed() const;
        int TM_Delayed() const;
        int SC41L() const;
        int SC41R() const;
        std::set<int> ExtraSignals() const;

    private:
        static std::string filepath;
        TFatimaVmeConfiguration();
        void ReadConfiguration();

        static TFatimaVmeConfiguration* instance;

        std::map<std::pair<int, int>, int> dets_qdc;
        std::map<std::pair<int, int>, int> dets_tdc;
        std::set<int> extra_signals;

        int detectors;
        int num_qdc_boards;
        int num_tdc_boards;

        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;
        int sc41l_a;
        int sc41r_a;

        bool DetectorMap_loaded = 0;

};

inline TFatimaVmeConfiguration const* TFatimaVmeConfiguration::GetInstance()
{
    if (!instance)
    {
        TFatimaVmeConfiguration::Create();
    }
    return instance;
}

inline void TFatimaVmeConfiguration::Create()
{
    delete instance;
    instance = new TFatimaVmeConfiguration();
}

inline std::map<std::pair<int, int>, int> TFatimaVmeConfiguration::QDCMapping() const
{
    return dets_qdc;
}

inline int TFatimaVmeConfiguration::NQDCBoards() const
{
    return num_qdc_boards;
}

inline std::map<std::pair<int, int>, int> TFatimaVmeConfiguration::TDCMapping() const
{
    return dets_tdc;
}

inline int TFatimaVmeConfiguration::NTDCBoards() const
{
    return num_tdc_boards;
}

inline bool TFatimaVmeConfiguration::MappingLoaded() const
{
    return DetectorMap_loaded;
}

inline int TFatimaVmeConfiguration::TM_Undelayed() const
{
    return tm_undelayed;
}

inline int TFatimaVmeConfiguration::TM_Delayed() const
{
    return tm_delayed;
}

inline int TFatimaVmeConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TFatimaVmeConfiguration::SC41R() const
{
    return sc41r_d;
}

inline std::set<int> TFatimaVmeConfiguration::ExtraSignals() const
{
    return extra_signals;
}



#endif