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
        //std::map<int, std::pair<std::pair<int, int>, std::string>> Mapping() const;
        bool MappingLoaded() const;
        bool CalibrationLoaded() const;


        int NCTDCChannels() const;
        int NDetectors() const;
        int NRGroups() const;
        int NEGroups() const;
        int NBGroups() const;
        int NLGroups() const;
        int NTGroups() const;
        int GetX(const int& id) const;
        int GetY(const int& id) const;
        int GetZ(const int& id) const;
        int SC41L() const;
        int SC41R() const;
        std::set<int> ExtraSignals() const;

        static void SetEnergyToTRange(int min, int max) { EnergyToTMin = min; EnergyToTMax = max; }

        static int EnergyToTMax;
        static int EnergyToTMin;


        struct Mapping_item{
            int chan, ctdc_num, ctdc_chan, cable, fimp_chan;
            char t_b_l_r;
        };
    private:

        static std::string mapping_file;
        static std::string calibration_file;

        TFimpConfiguration();
        void ReadMappingFile();
        void ReadCalibrationCoefficients();

        static TFimpConfiguration* instance;

        std::map<int, Mapping_item> detector_mapping;
        std::set<int> extra_signals;

        int num_channels = 0;    
        int num_detectors = 0;

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

//inline std::map<int, std::pair<std::pair<int, int>, std::string>>  TFimpConfiguration::Mapping() const
//{
//    return detector_mapping;
//}

/*
inline std::map<std::pair<int,int>,std::pair<double,double>> TFimpConfiguration::CalibrationCoefficients() const
{
    return calibration_coeffs;
}
*/

inline int TFimpConfiguration::NCTDCChannels() const
{
    return num_channels;
}

inline int TFimpConfiguration::NDetectors() const
{
    return num_detectors;
}

inline bool TFimpConfiguration::MappingLoaded() const
{
    return detector_mapping_loaded;
}

inline bool TFimpConfiguration::CalibrationLoaded() const
{
    return detector_calibrations_loaded;
}

inline int TFimpConfiguration::GetX(const int& id) const
{
    auto it = detector_mapping.find(id);
    if (it != detector_mapping.end())
    {
        if(it->second.t_b_l_r == 'L' || it->second.t_b_l_r == 'R')
        {
            return it->second.fimp_chan%16;
        }
    }
    return -1; // or throw an exception
}

inline int TFimpConfiguration::GetY(const int& id) const
{
    auto it = detector_mapping.find(id);
    if (it != detector_mapping.end())
    {
        if(it->second.t_b_l_r == 'T' || it->second.t_b_l_r == 'B')
        {
            return it->second.fimp_chan%16;
        }
    }
    return -1; // or throw an exception
}
inline int TFimpConfiguration::GetZ(const int& id) const
{
    auto it = detector_mapping.find(id);
    if (it != detector_mapping.end())
    {
        return it->second.cable%3;
    }
    return -1; // or throw an exception
}

/*
inline bool TFimpConfiguration::CalibrationCoefficientsLoaded() const
{
    return detector_calibrations_loaded;
}
*/

//inline int TFimpConfiguration::SC41L() const
//{
//    return sc41l_d;
//}
//
//inline int TFimpConfiguration::SC41R() const
//{
//    return sc41r_d;
//}

#endif
