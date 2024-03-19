#ifndef TFatimaTwinpeaksConfiguration_H
#define TFatimaTwinpeaksConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>


//structs

class TFatimaTwinpeaksConfiguration
{
    public:
        static TFatimaTwinpeaksConfiguration const* GetInstance();
        static void Create();
        static void SetDetectorConfigurationFile(std::string fp) { configuration_file = fp; }
        static void SetDetectorCoefficientFile(std::string fp) { calibration_file = fp; }

        std::map<std::pair<int,int>,int> Mapping() const;
        bool MappingLoaded() const;
        bool CalibrationCoefficientsLoaded() const;
        std::map<int,std::vector<double>> CalibrationCoefficients() const;
        int NDetectors() const;
        int NTamexBoards() const;
        int TM_Undelayed() const;
        int TM_Delayed() const;
        int SC41L() const;
        int SC41R() const;
        int FRS_accept() const;
        int bPlast_accept() const;
        int bPlast_free() const;
        std::set<int> ExtraSignals() const;

    private:

        static std::string configuration_file;
        static std::string calibration_file;

        TFatimaTwinpeaksConfiguration();
        void ReadConfiguration();
        void ReadCalibrationCoefficients();

        static TFatimaTwinpeaksConfiguration* instance;
        
        std::map<std::pair<int,int>,int> detector_mapping; // [board_id][channel_id] -> [detector_id]
        std::map<int,std::vector<double>> calibration_coeffs; // key: [detector id] -> vector[a0 - a3] index is coefficient number 0 = offset +++ expects quadratic.


        std::set<int> extra_signals;

        int num_detectors;
        int num_tamex_boards;
        int num_tamex_channels;

        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;
        int frs_accept;
        int bplast_accept;
        int bplast_free;

        bool detector_map_loaded = 0;
        bool detector_calibrations_loaded = 0;
};

inline std::map<int,std::vector<double>> TFatimaTwinpeaksConfiguration::CalibrationCoefficients() const 
{
    return calibration_coeffs;
}

inline bool TFatimaTwinpeaksConfiguration::CalibrationCoefficientsLoaded() const {
    return detector_calibrations_loaded;
}

inline TFatimaTwinpeaksConfiguration const* TFatimaTwinpeaksConfiguration::GetInstance()
{
    if (!instance)
    {
        TFatimaTwinpeaksConfiguration::Create();
    }
    return instance;
}

inline void TFatimaTwinpeaksConfiguration::Create()
{
    delete instance;
    instance = new TFatimaTwinpeaksConfiguration();
}

inline std::map<std::pair<int,int>,int> TFatimaTwinpeaksConfiguration::Mapping() const
{
  return detector_mapping;
}

inline bool TFatimaTwinpeaksConfiguration::MappingLoaded() const
{
    return detector_map_loaded;
}

inline int TFatimaTwinpeaksConfiguration::NDetectors() const
{
    return num_detectors;
}

inline int TFatimaTwinpeaksConfiguration::NTamexBoards() const
{
    return num_tamex_boards;
}

inline int TFatimaTwinpeaksConfiguration::TM_Undelayed() const
{
    return tm_undelayed;
}

inline int TFatimaTwinpeaksConfiguration::TM_Delayed() const
{
    return tm_delayed;
}

inline int TFatimaTwinpeaksConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TFatimaTwinpeaksConfiguration::SC41R() const
{
    return sc41r_d;
}

inline int TFatimaTwinpeaksConfiguration::FRS_accept() const
{
    return frs_accept;
}

inline int TFatimaTwinpeaksConfiguration::bPlast_accept() const
{
    return bplast_accept;
}

inline int TFatimaTwinpeaksConfiguration::bPlast_free() const
{
    return bplast_free;
}

inline std::set<int> TFatimaTwinpeaksConfiguration::ExtraSignals() const
{
    return extra_signals;
}

#endif