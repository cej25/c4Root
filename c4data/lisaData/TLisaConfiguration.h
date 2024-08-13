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
        static void SetGMFile(std::string fp) { gain_matching_file = fp; }
        static void SetDetectorCoefficientFile(std::string fp) { calibration_file = fp; }

        //:::: Mapping
        //std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> Mapping() const;
        std::map<std::pair<int,int>, std::pair<std::pair<int,std::string>, std::pair<int,int>>> Mapping() const;
        bool MappingLoaded() const;

        //:::: Gain Matching
        std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> GainMatchingCoefficients() const;
        bool GainMatchingLoaded() const;

        void SetTraceLength(int length) { trace_length = length; }
        int GetTraceLength() { return trace_length; }

        //std::map<std::pair<int,int>,std::pair<double,double>> CalibrationCoefficients() const;
        //:::: Calibration
        //std::map<std::pair<int,std::pair<int,int>>, std::pair<int,int>> CalibrationCoefficients() const;
        //bool CalibrationLoaded() const;

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
        //void SetAmplitudeMax(int max) { AmplitudeMax = max; }
        //void SetAmplitudeMin(int min) { AmplitudeMin = min; }

        static void SetAmplitudeMax(int max_amp) { AmplitudeMax = max_amp; }
        static void SetAmplitudeMin(int min_amp) { AmplitudeMin = min_amp; }

        static void SetEnergyRange(int min, int max) { min_energy = min; max_energy = max; }
        static void SetEnergyBin(int bin_e) { bin_energy = bin_e; }

        static void SetWrDiffRange(int min_wr, int max_wr) { min_wr_diff = min_wr; max_wr_diff = max_wr; }
        static void SetWrDiffBin(int bin_wr) { bin_wr_diff = bin_wr; }

        static void SetTracesRange(int min_tr, int max_tr) { min_traces = min_tr; max_traces = max_tr; }
        static void SetTracesBin(int bin_tr) { bin_traces = bin_tr; }

        static void SetWREnable(bool wr_en) { wr_enable = wr_en; }

/*
        static void SetGainM_100(int s100_p, int i100_p) {  s100 = s100_p; i100 = i100_p; }
        static void SetGainM_101(int s101_p, int i101_p) {  s101 = s101_p; i101 = i101_p; }
        static void SetGainM_110(int s110_p, int i110_p) {  s110 = s110_p; i110 = i110_p; }
        static void SetGainM_111(int s111_p, int i111_p) {  s111 = s111_p; i111 = i111_p; }
        static void SetGainM_200(int s200_p, int i200_p) {  s200 = s200_p; i200 = i200_p; }
        static void SetGainM_201(int s201_p, int i201_p) {  s201 = s201_p; i201 = i201_p; }
        static void SetGainM_210(int s210_p, int i210_p) {  s210 = s210_p; i210 = i210_p; }
        static void SetGainM_211(int s211_p, int i211_p) {  s211 = s211_p; i211 = i211_p; }
*/



        //int AmplitudeMax = 10500;
        //int AmplitudeMin = 7500;
        static int AmplitudeMax; // = 10500;
        static int AmplitudeMin; // = 7500;
        static int min_energy;
        static int max_energy;
        static int bin_energy;
        static int min_wr_diff;
        static int max_wr_diff;
        static int bin_wr_diff;
        static int min_traces;
        static int max_traces;
        static int bin_traces;
        
        static bool wr_enable;
        /*
        static int s100;
        static int s101;
        static int s110;
        static int s111;
        static int s200;
        static int s201;
        static int s210;
        static int s211;
        static int i100;
        static int i101;
        static int i110;
        static int i111;
        static int i200;
        static int i201;
        static int i210;
        static int i211;
        */

        //:::::::



    private:

        static std::string mapping_file;
        static std::string gain_matching_file;
        static std::string calibration_file;

        TLisaConfiguration();
        void ReadMappingFile();
        void ReadGMFile();
        void ReadCalibrationCoefficients();

        static TLisaConfiguration* instance;

        //std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> detector_mapping;
        std::map<std::pair<int,int>, std::pair<std::pair<int,std::string>, std::pair<int,int>>> detector_mapping;
        std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> gain_matching_coeffs;
        //std::map<std::pair<int,std::pair<int,int>>, std::pair<int,int>> calibration_coeffs;
        std::set<int> extra_signals;

        int num_layers;   
        int xmax;
        int ymax;     
        int num_detectors;
        int num_febex_boards;
        

        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;

        bool detector_mapping_loaded = 0;
        bool gain_matching_loaded = 0;
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

//::: Mapping
//inline std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> TLisaConfiguration::Mapping() const
inline std::map<std::pair<int,int>, std::pair<std::pair<int,std::string>, std::pair<int,int>>> TLisaConfiguration::Mapping() const
{
    return detector_mapping;
}


//::: Gain Matching
inline std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> TLisaConfiguration::GainMatchingCoefficients() const
{
    return gain_matching_coeffs;
}

//::: Calibration
/*
inline std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> TLisaConfiguration::CalibrationCoefficients() const
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


inline bool TLisaConfiguration::GainMatchingLoaded() const
{
    return gain_matching_loaded;
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
