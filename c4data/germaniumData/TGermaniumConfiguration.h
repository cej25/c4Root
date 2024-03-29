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


        static void SetDetectorConfigurationFile(std::string fp) { configuration_file = fp; }
        static void SetDetectorCoefficientFile(std::string fp) { calibration_file = fp; }
        static void SetDetectorTimeshiftsToSCI41File(std::string fp) { timeshift_calibration_file = fp; }



        std::map<std::pair<int,int>,std::pair<int,int>> Mapping() const;
        bool MappingLoaded() const;
        bool CalibrationCoefficientsLoaded() const;
        std::map<std::pair<int,int>,std::pair<double,double>> CalibrationCoefficients() const;
        bool TimeshiftCalibrationCoefficientsLoaded() const;
        std::map<std::pair<int,int>,double> TimeshiftCalibrationCoefficients() const;

        int NDetectors() const;
        int NCrystals() const;
        int CrystalsPerDetector(int detector_id) const;
        int NFebexBoards() const;
        int TM_Undelayed() const;
        int TM_Delayed() const;
        int SC41L() const;
        int SC41R() const;
        std::set<int> ExtraSignals() const;

    private:

        static std::string configuration_file;
        static std::string calibration_file;
        static std::string timeshift_calibration_file;


        TGermaniumConfiguration();
        void ReadConfiguration();
        void ReadCalibrationCoefficients();
        void ReadTimeshiftSCI41Coefficients();

        static TGermaniumConfiguration* instance;
        
        std::map<std::pair<int,int>,std::pair<int,int>> detector_mapping;
        std::map<std::pair<int,int>,std::pair<double,double>> calibration_coeffs;
        std::map<std::pair<int,int>,double> timeshift_calibration_coeffs;
        std::set<int> extra_signals;

        int num_detectors;
        int num_crystals;
        std::map<int,int> crystals_per_detector;
        int num_febex_boards;

        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;

        bool detector_mapping_loaded = 0;
        bool detector_calibrations_loaded = 0;
        bool timeshift_calibration_coeffs_loaded = 0;
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

inline std::map<std::pair<int,int>,std::pair<double,double>> TGermaniumConfiguration::CalibrationCoefficients() const
{
    return calibration_coeffs;
}

inline std::map<std::pair<int,int>,double> TGermaniumConfiguration::TimeshiftCalibrationCoefficients() const
{
    return timeshift_calibration_coeffs;
}

inline int TGermaniumConfiguration::NDetectors() const
{
    return num_detectors;
}

inline int TGermaniumConfiguration::NCrystals() const
{
    return num_crystals;
}


//return the number of crystals per detector.
inline int TGermaniumConfiguration::CrystalsPerDetector(int detector_id) const
{
    if (auto result_crystals_per_detector = crystals_per_detector.find(detector_id); result_crystals_per_detector != crystals_per_detector.end()){
        return crystals_per_detector.at(detector_id);
    }else{
        return 0;
    }
}

inline int TGermaniumConfiguration::NFebexBoards() const
{
    return num_febex_boards;
}

inline bool TGermaniumConfiguration::MappingLoaded() const
{
    return detector_mapping_loaded;
}

inline bool TGermaniumConfiguration::CalibrationCoefficientsLoaded() const
{
    return detector_calibrations_loaded;
}

inline bool TGermaniumConfiguration::TimeshiftCalibrationCoefficientsLoaded() const
{
    return timeshift_calibration_coeffs_loaded;
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
