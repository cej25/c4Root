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
        //std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> Mapping() const;
        std::map<std::pair<int,int>, std::pair<std::pair<int,std::string>, std::pair<int,int>>> Mapping() const;
        bool MappingLoaded() const;

        void SetTraceLength(int length) { trace_length = length; }
        int GetTraceLength() { return trace_length; }

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


        //:::::Ranges in Histos
        void SetAmplitudeMax(int max) { AmplitudeMax = max; }
        void SetAmplitudeMin(int min) { AmplitudeMin = min; }

        static void SetEnergyRange(int min, int max) { min_energy = min; max_energy = max; }
        static void SetEnergyBin(int bin_e) { bin_energy = bin_e; }

        static void SetWrDiffRange(int min_wr, int max_wr) { min_wr_diff = min_wr; max_wr_diff = max_wr; }
        static void SetWrDiffBin(int bin_wr) { bin_wr_diff = bin_wr; }

        int AmplitudeMax = 10500;
        int AmplitudeMin = 7500;
        static int min_energy;
        static int max_energy;
        static int bin_energy;
        static int min_wr_diff;
        static int max_wr_diff;
        static int bin_wr_diff;

        //:::::::



    private:

        static std::string mapping_file;
        static std::string calibration_file;

        TLisaConfiguration();
        void ReadMappingFile();
        void ReadCalibrationCoefficients();

        static TLisaConfiguration* instance;

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

//inline std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> TLisaConfiguration::Mapping() const
inline std::map<std::pair<int,int>, std::pair<std::pair<int,std::string>, std::pair<int,int>>> TLisaConfiguration::Mapping() const
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

inline int TLisaConfiguration::XMax() const
{
    return xmax;
}

inline int TLisaConfiguration::YMax() const
{
    return ymax;
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
