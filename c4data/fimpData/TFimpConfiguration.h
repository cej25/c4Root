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
        //std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> Mapping() const;
        std::map<std::pair<int,int>, std::pair<std::pair<int,std::string>, std::pair<int,int>>> Mapping() const;
        bool MappingLoaded() const;
        bool CalibrationLoaded() const;

        //std::map<std::pair<int,int>,std::pair<double,double>> CalibrationCoefficients() const;

        int NLayers() const;
        int XMax() const;
        int YMax() const;
        int NDetectors() const;
        int NFebexBoards() const;
        int TM_Undelayed() const;
        int TM_Delayed() const;
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

        //std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> detector_mapping;
        std::map<std::pair<int,int>, std::pair<std::pair<int,std::string>, std::pair<int,int>>> detector_mapping;
        //std::map<std::pair<int,int>,std::pair<double,double>> calibration_coeffs;
        std::set<int> extra_signals;

        int num_layers;   
        int xmax;
        int ymax;     
        int num_detectors;
        int num_febex_boards;
        // layer arrangement (set/get with function?)

        // will you have extra signals?
        int tm_undelayed;
        int tm_delayed;
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

//inline std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> TFimpConfiguration::Mapping() const
inline std::map<std::pair<int,int>, std::pair<std::pair<int,std::string>, std::pair<int,int>>> TFimpConfiguration::Mapping() const
{
    return detector_mapping;
}

/*
inline std::map<std::pair<int,int>,std::pair<double,double>> TFimpConfiguration::CalibrationCoefficients() const
{
    return calibration_coeffs;
}
*/

inline int TFimpConfiguration::NLayers() const
{
    return num_layers;
}

inline int TFimpConfiguration::XMax() const
{
    return xmax;
}

inline int TFimpConfiguration::YMax() const
{
    return ymax;
}

inline int TFimpConfiguration::NDetectors() const
{
    return num_detectors;
}

inline int TFimpConfiguration::NFebexBoards() const
{
    return num_febex_boards;
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

inline int TFimpConfiguration::TM_Undelayed() const
{
    return tm_undelayed;
}

inline int TFimpConfiguration::TM_Delayed() const
{
    return tm_delayed;
}

inline int TFimpConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TFimpConfiguration::SC41R() const
{
    return sc41r_d;
}

#endif
