#ifndef TLYSOConfiguration_H
#define TLYSOConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "TCutG.h"

//structs

class TLYSOConfiguration
{
    public:
        static TLYSOConfiguration const* GetInstance();
        static void Create();


        static void SetDetectorConfigurationFile(std::string fp) { configuration_file = fp; }

        bool ConfigurationLoaded() const;


        inline std::pair<int,int> GetDetectorID(int board, int channel) const;
        inline std::vector<double> GetCalibrationCoeff(int board, int channel) const;
        inline double GetThreshold(int board, int channel) const;
        

    private:

        static std::string configuration_file;

        TLYSOConfiguration();
        void ReadConfiguration();

        static TLYSOConfiguration* instance;
        
        std::map<std::pair<int,int>,std::pair<int,int>> detector_mapping; //board, ch -> x=0/y=1 , anode number
        std::map<std::pair<int,int>,std::vector<double>> calibration_coeffs; // board, ch -> a0, a1, a2 ... 
        std::map<std::pair<int,int>,double> thresholds; // board, ch -> theshold
        
        bool config_loaded = false;
};

inline TLYSOConfiguration const* TLYSOConfiguration::GetInstance()
{
    if (!instance)
    {
        TLYSOConfiguration::Create();
    }
    return instance;
}


inline void TLYSOConfiguration::Create()
{
    delete instance;
    instance = new TLYSOConfiguration();
}


inline bool TLYSOConfiguration::ConfigurationLoaded() const
{
    return config_loaded;
}


inline std::pair<int,int> TLYSOConfiguration::GetDetectorID(int board, int channel) const
{
    auto key = std::make_pair(board, channel);
    auto it = detector_mapping.find(key);
    if (it != detector_mapping.end()) {
        return it->second;
    }
    return std::make_pair(-1, -1); 
}

inline std::vector<double> TLYSOConfiguration::GetCalibrationCoeff(int board, int channel) const
{
    auto key = std::make_pair(board, channel);
    auto it = calibration_coeffs.find(key);
    if (it != calibration_coeffs.end()) {
        return it->second;
    }
    return {}; 
}

inline double TLYSOConfiguration::GetThreshold(int board, int channel) const
{
    auto key = std::make_pair(board, channel);
    auto it = thresholds.find(key);
    if (it != thresholds.end()) {
        return it->second;
    }
    return 0.0; 
}




#endif