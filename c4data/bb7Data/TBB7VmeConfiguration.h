#ifndef TBB7VmeConfiguration_H
#define TBB7VmeConfiguration_H

#include <string>
#include <set>
#include <map>
#include <string>

class TBB7VmeConfiguration
{
    public:
        static TBB7VmeConfiguration const* GetInstance();
        static void Create();
        static void SetDetectorConfigurationFile(std::string fp) { configuration_file = fp; }
        static void SetResidualSignalsFile(std::string fp) { residuals_file = fp; }
        //static void SetDetectorCoefficientFile(std::string fp) { calibration_file = fp; }

        static void SetImplantThreshold(uint32_t th) { implantThreshold = th; }

        std::map<std::pair<int,int>,std::pair<int,int>> Mapping() const;
        std::map<std::pair<int, int>, int> Residuals() const;
        bool MappingLoaded() const;
        bool ResidualsLoaded() const;
        bool CalibrationCoefficientsLoaded() const;
        //std::map<int,std::vector<double>> CalibrationCoefficients() const;
        int NDetectors() const;
        int NSides() const;
        int NStrips() const;
        int TM_Undelayed() const;
        int TM_Delayed() const;
        int SC41L() const;
        int SC41R() const;
        //std::pair<int, int> FRS_accept() const;
        //std::pair<int, int> bPlast_accept() const;
        //std::pair<int, int> bPlast_free() const;
        std::set<std::pair<int, int>> ExtraSignals() const;

        static uint32_t implantThreshold;
    
    private:

        static std::string configuration_file;
        static std::string calibration_file;
        static std::string residuals_file;

        TBB7VmeConfiguration();
        void ReadConfiguration();
        void ReadResiduals();
        //void ReadCalibrationCoefficients();

        static TBB7VmeConfiguration* instance;

        
        std::map<std::pair<int,int>,std::pair<int, int>> detector_mapping; // [board_id][channel_id] -> [side][strip]
        std::map<std::pair<int, int>, int> residual_mapping;
        //std::map<int,std::vector<double>> calibration_coeffs; // key: [detector id] -> vector[a0 - a3] index is coefficient number 0 = offset +++ expects quadratic.

        std::set<std::pair<int, int>> extra_signals;

        int num_detectors;
        int num_sides;
        int num_strips;
        int num_v7x5_boards;

        // std::pair<int, int> tm_undelayed;
        // std::pair<int, int> tm_delayed;
        // std::pair<int, int> sc41l_d;
        // std::pair<int, int> sc41r_d;
        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;

        // std::pair<int, int> frs_accept;
        // std::pair<int, int> bplast_accept;
        // std::pair<int, int> bplast_free;

        bool detector_map_loaded = 0;
        bool residuals_loaded = 0;
        bool detector_calibrations_loaded = 0;
};

inline TBB7VmeConfiguration const* TBB7VmeConfiguration::GetInstance()
{
    if (!instance)
    {
        TBB7VmeConfiguration::Create();
    }
    return instance;
}

inline void TBB7VmeConfiguration::Create()
{
    delete instance;
    instance = new TBB7VmeConfiguration();
}

inline std::map<std::pair<int,int>,std::pair<int,int>> TBB7VmeConfiguration::Mapping() const
{
  return detector_mapping;
}

inline std::map<std::pair<int, int>, int> TBB7VmeConfiguration::Residuals() const
{
  return residual_mapping;
}

inline bool TBB7VmeConfiguration::MappingLoaded() const
{
    return detector_map_loaded;
}

inline bool TBB7VmeConfiguration::ResidualsLoaded() const
{
    return residuals_loaded;
}


inline int TBB7VmeConfiguration::NDetectors() const
{
    return num_detectors;
}

inline int TBB7VmeConfiguration::NSides() const
{
    return num_sides;
}

inline int TBB7VmeConfiguration::NStrips() const
{
    return num_strips;
}

// these are ints while we're mapping to a single value
// from a separate v1290 tdc module
inline int TBB7VmeConfiguration::TM_Undelayed() const
{
    return tm_undelayed;
}

inline int TBB7VmeConfiguration::TM_Delayed() const
{
    return tm_delayed;
}

inline int TBB7VmeConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TBB7VmeConfiguration::SC41R() const
{
    return sc41r_d;
}

/*
inline std::pair<int, int> TBB7VmeConfiguration::FRS_accept() const
{
    return frs_accept;
}

inline std::pair<int, int> TBB7VmeConfiguration::bPlast_accept() const
{
    return bplast_accept;
}

inline std::pair<int, int> TBB7VmeConfiguration::bPlast_free() const
{
    return bplast_free;
}
*/

inline std::set<std::pair<int, int>> TBB7VmeConfiguration::ExtraSignals() const
{
    return extra_signals;
}

#endif
