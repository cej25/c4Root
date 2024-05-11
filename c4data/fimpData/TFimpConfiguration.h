#ifndef TFimpConfiguration_H
#define TFimpConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "TCutG.h"


//structs

class TFimpConfiguration
{
    public:
        static TFimpConfiguration const* GetInstance();
        static void Create();

        static void SetMappingFile(std::string fp) { mapping_file = fp; }
        static void SetDetectorCoefficientFile(std::string fp) { calibration_file = fp; }

        // mapping
        std::map<int, std::pair<std::pair<int, int>, std::string>> Mapping() const;
        bool MappingLoaded() const;
        bool CalibrationLoaded() const;


        int NCTDCChannels() const;
        int NDetectors() const;
        int NEGroups() const;
        int NTGroups() const;
        int SC41L() const;
        int SC41R() const;
        std::set<int> ExtraSignals() const;

        void SetAmplitudeMax(int max) { AmplitudeMax = max; }
        void SetAmplitudeMin(int min) { AmplitudeMin = min; }

        int AmplitudeMax = 8500;
        int AmplitudeMin = 7500;


    private:

        static std::string mapping_file;
        static std::string calibration_file;

        TFimpConfiguration();
        void ReadMappingFile();
        void ReadCalibrationCoefficients();

        static TFimpConfiguration* instance;

        std::map<int, std::pair<std::pair<int, int>, std::string>> detector_mapping;
        std::set<int> extra_signals;

        int num_ctdc_channels = 0;    
        int num_detectors = 0;
        int num_e_groups = 0;
        int num_t_groups = 0;

        int sc41l_d = 0;
        int sc41r_d = 1;

        bool detector_mapping_loaded = 0;
        bool detector_calibrations_loaded = 0;
        bool timeshift_calibration_coeffs_loaded = 0;

};


inline TFimpConfiguration const* TFimpConfiguration::GetInstance()
{
    if (!instance)
    {
        TFimpConfiguration::Create();
    }
    return instance;
}

inline void TFimpConfiguration::Create()
{
    delete instance;
    instance = new TFimpConfiguration();
}

inline std::map<int, std::pair<std::pair<int, int>, std::string>>  TFimpConfiguration::Mapping() const
{
    return detector_mapping;
}

/*
inline std::map<std::pair<int,int>,std::pair<double,double>> TFimpConfiguration::CalibrationCoefficients() const
{
    return calibration_coeffs;
}
*/

inline int TFimpConfiguration::NCTDCChannels() const
{
    return num_detectors;
}

inline int TFimpConfiguration::NDetectors() const
{
    return num_detectors;
}

inline int TFimpConfiguration::NEGroups() const
{
    return num_e_groups;
}

inline int TFimpConfiguration::NTGroups() const
{
    return num_t_groups;
}

inline bool TFimpConfiguration::MappingLoaded() const
{
    return detector_mapping_loaded;
}

inline bool TFimpConfiguration::CalibrationLoaded() const
{
    return detector_calibrations_loaded;
}


/*
inline bool TFimpConfiguration::CalibrationCoefficientsLoaded() const
{
    return detector_calibrations_loaded;
}
*/

inline int TFimpConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TFimpConfiguration::SC41R() const
{
    return sc41r_d;
}

#endif
