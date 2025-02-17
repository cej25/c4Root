#ifndef TBB7FebexConfiguration_H
#define TBB7FebexConfiguration_H

#include <string>
#include <set>
#include <map>
#include <string>

class TBB7FebexConfiguration
{
    public:
        static TBB7FebexConfiguration const* GetInstance();
        static void Create();
        static void SetMappingFile(std::string fp) { mapping_file = fp; }

        static void SetImplantThreshold(uint32_t th) { implantThreshold = th; }
        static void SetDecayThreshold(uint32_t th) { decayThreshold = th; }

        std::map<std::pair<int,int>, std::pair<int, std::pair<int, int>>> Mapping() const;
        bool MappingLoaded() const;
        bool CalibrationLoaded() const;
        int DSSDs() const;
        int TM_Undelayed() const;
        int TM_Delayed() const;
        int SC41L() const;
        int SC41R() const;

        static uint32_t implantThreshold;
        static uint32_t decayThreshold;
    
    private:

        static std::string mapping_file;
        static std::string calibration_file;

        TBB7FebexConfiguration();
        void ReadConfiguration();
        //void ReadCalibrationCoefficients();

        static TBB7FebexConfiguration* instance;

        // febid,febch --> detector, side,strip
        std::map<std::pair<int,int>, std::pair<int, std::pair<int, int>>> detector_mapping;

        int num_dssds;
        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;

        bool detector_map_loaded = 0;
        bool calibration_loaded = 0;
};

inline TBB7FebexConfiguration const* TBB7FebexConfiguration::GetInstance()
{
    if (!instance)
    {
        TBB7FebexConfiguration::Create();
    }
    return instance;
}

inline void TBB7FebexConfiguration::Create()
{
    delete instance;
    instance = new TBB7FebexConfiguration();
}

inline std::map<std::pair<int,int>, std::pair<int, std::pair<int, int>>> TBB7FebexConfiguration::Mapping() const
{
  return detector_mapping;
}

inline bool TBB7FebexConfiguration::MappingLoaded() const
{
    return detector_map_loaded;
}

inline bool TBB7FebexConfiguration::CalibrationLoaded() const
{
    return calibration_loaded;
}

inline int TBB7FebexConfiguration::DSSDs() const
{
    return num_dssds;
}

inline int TBB7FebexConfiguration::TM_Undelayed() const
{
    return tm_undelayed;
}

inline int TBB7FebexConfiguration::TM_Delayed() const
{
    return tm_delayed;
}

inline int TBB7FebexConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TBB7FebexConfiguration::SC41R() const
{
    return sc41r_d;
}


#endif
