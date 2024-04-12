#ifndef TLisaConfiguration_H
#define TLisaConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "TCutG.h"


//structs

class TLisaConfiguration
{
    public:
        static TLisaConfiguration const* GetInstance();
        static void Create();

        static void SetMappingFile(std::string fp) { mapping_file = fp; }
        static void SetDetectorCoefficientFile(std::string fp) { calibration_file = fp; }

        // mapping
        std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> Mapping() const;
        bool MappingLoaded() const;

        void SetTraceLength(int length) { trace_length = length; }
        int GetTraceLength() { return trace_length; }

        //std::map<std::pair<int,int>,std::pair<double,double>> CalibrationCoefficients() const;

        int NLayers() const;
        int NDetectors() const;
        int NFebexBoards() const;
        int TM_Undelayed() const;
        int TM_Delayed() const;
        int SC41L() const;
        int SC41R() const;
        std::set<int> ExtraSignals() const;

    private:

        static std::string mapping_file;
        static std::string calibration_file;

        TLisaConfiguration();
        void ReadMappingFile();
        void ReadCalibrationCoefficients();

        static TLisaConfiguration* instance;

        std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> detector_mapping;
        //std::map<std::pair<int,int>,std::pair<double,double>> calibration_coeffs;
        std::set<int> extra_signals;

        int num_layers;        
        int num_detectors;
        int num_febex_boards;
        // layer arrangement (set/get with function?)

        // will you have extra signals?
        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;

        bool detector_mapping_loaded = 0;
        bool detector_calibrations_loaded = 0;
        bool timeshift_calibration_coeffs_loaded = 0;

        int trace_length = 4000; // default 4k
};


inline TLisaConfiguration const* TLisaConfiguration::GetInstance()
{
    if (!instance)
    {
        TLisaConfiguration::Create();
    }
    return instance;
}

inline void TLisaConfiguration::Create()
{
    delete instance;
    instance = new TLisaConfiguration();
}

inline std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> TLisaConfiguration::Mapping() const
{
    return detector_mapping;
}

/*
inline std::map<std::pair<int,int>,std::pair<double,double>> TLisaConfiguration::CalibrationCoefficients() const
{
    return calibration_coeffs;
}
*/

inline int TLisaConfiguration::NLayers() const
{
    return num_layers;
}

inline int TLisaConfiguration::NDetectors() const
{
    return num_detectors;
}

inline int TLisaConfiguration::NFebexBoards() const
{
    return num_febex_boards;
}

inline bool TLisaConfiguration::MappingLoaded() const
{
    return detector_mapping_loaded;
}

/*
inline bool TLisaConfiguration::CalibrationCoefficientsLoaded() const
{
    return detector_calibrations_loaded;
}
*/

inline int TLisaConfiguration::TM_Undelayed() const
{
    return tm_undelayed;
}

inline int TLisaConfiguration::TM_Delayed() const
{
    return tm_delayed;
}

inline int TLisaConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TLisaConfiguration::SC41R() const
{
    return sc41r_d;
}

#endif
