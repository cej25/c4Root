#ifndef TAgataConfiguration_H
#define TAgataConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "TCutG.h"

//structs

class TAgataConfiguration
{
    public:
        static TAgataConfiguration const* GetInstance();
        static void Create();


        static void SetDetectorConfigurationFile(std::string fp) { configuration_file = fp; }

        bool ConfigurationLoaded() const;


        inline std::pair<char,int> GetDetectorID(int board, int channel) const;
        inline std::vector<double> GetCalibrationCoeff(int board, int channel) const;
        
    private:

        static std::string configuration_file;

        TAgataConfiguration();
        void ReadConfiguration();

        static TAgataConfiguration* instance;
        
        std::map<std::pair<char,int>,std::pair<int,int>> detector_mapping; //board, ch -> layer id, segment sector A-F + S
        std::map<std::pair<int,int>,std::vector<double>> calibration_coeffs; // board, ch -> a0, a1, a2 ... 


        bool config_loaded = false;
};

inline TAgataConfiguration const* TAgataConfiguration::GetInstance()
{
    if (!instance)
    {
        TAgataConfiguration::Create();
    }
    return instance;
}


inline void TAgataConfiguration::Create()
{
    delete instance;
    instance = new TAgataConfiguration();
}


inline bool TAgataConfiguration::ConfigurationLoaded() const
{
    return config_loaded;
}


inline std::pair<char,int> TAgataConfiguration::GetDetectorID(int board, int channel) const
{
    auto key = std::make_pair(board, channel);
    auto it = detector_mapping.find(key);
    if (it != detector_mapping.end()) {
        return it->second;
    }
    return std::make_pair(-1, -1); 
}

inline std::vector<double> TAgataConfiguration::GetCalibrationCoeff(int board, int channel) const
{
    auto key = std::make_pair(board, channel);
    auto it = calibration_coeffs.find(key);
    if (it != calibration_coeffs.end()) {
        return it->second;
    }
    return {}; 
}


#endif