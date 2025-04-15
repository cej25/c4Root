/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25.11.24                                     *
 ******************************************************************************/

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

        static void SetMWDParametersFile(std::string fp) { MWD_file = fp; }
        static void SetMappingFile(std::string fp) { mapping_file = fp; }
        static void SetGMFile(std::string fp) { gain_matching_file = fp; }
        static void SetGMFileMWD(std::string fp) { gain_matching_file_MWD = fp; }
        static void SetDetectorCoefficientFile(std::string fp) { calibration_file = fp; }

        //::: MWD Parameters
        bool MWDParametersLoaded() const;

        //:::: Mapping
        //std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> Mapping() const;
        std::map<std::pair<int,int>, std::pair<std::pair<int,std::string>, std::pair<int,int>>> Mapping() const;
        bool MappingLoaded() const;

        //:::: Gain Matching
        std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> GainMatchingCoefficients() const;
        bool GainMatchingLoaded() const;

        //:::: Gain Matching for MWD 
        std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> GainMatchingMWDCoefficients() const;
        bool GainMatchingMWDLoaded() const;

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
        static void SetAmplitudeBin(int bin_amp) { amplitude_bin = bin_amp; }
        static void SetAmplitudeMax(int max_amp) { amplitude_max = max_amp; }
        static void SetAmplitudeMin(int min_amp) { amplitude_min = min_amp; }

        static void SetEnergyRange(int min, int max) { min_energy = min; max_energy = max; }
        static void SetEnergyBin(int bin_e) { bin_energy = bin_e; }
        
        static void SetEnergyRangeMWD(int min_MWD, int max_MWD) { min_energy_MWD = min_MWD; max_energy_MWD = max_MWD; }
        static void SetEnergyBinMWD(int bin_e_mwd) { bin_energy_MWD = bin_e_mwd; }

        static void SetEnergyRangeGM(int min_GM, int max_GM) { min_energy_GM = min_GM; max_energy_GM = max_GM; }
        static void SetEnergyBinGM(int bin_e_GM) { bin_energy_GM = bin_e_GM; }

        static void SetEnergyRangeMWDGM(int min_MWD_GM, int max_MWD_GM) { min_energy_MWD_GM = min_MWD_GM; max_energy_MWD_GM = max_MWD_GM; }
        static void SetEnergyBinMWDGM(int bin_e_MWD_GM) { bin_energy_MWD_GM = bin_e_MWD_GM; }

        static void SetWrDiffRange(long min_wr, long max_wr) { min_wr_diff = min_wr; max_wr_diff = max_wr; }
        static void SetWrDiffBin(int bin_wr) { bin_wr_diff = bin_wr; }

        static void SetWrRateRange(int min_wr_r, int max_wr_r) { min_wr_rate = min_wr_r; max_wr_rate = max_wr_r; }
        static void SetWrRateBin(int bin_wr_r) { bin_wr_rate = bin_wr_r; }

        static void SetTracesRange(int min_tr, int max_tr) { min_traces = min_tr; max_traces = max_tr; }
        static void SetTracesBin(int bin_tr) { bin_traces = bin_tr; }
        
        static void SetWREnable(bool wr_en) { wr_enable = wr_en; }

        static void SetLISAGate(int min_de, int max_de) { fMin_dE_LISA1_gate = min_de; fMax_dE_LISA1_gate = max_de; }

        static void SetRunNumber(int run_num) { frun_num = run_num; }

        static void SetBoardNumber(int b_num) { board_num = b_num; }

        static void SetEventToAnalyze(int evt_num) { event_ana = evt_num; }

        static void SetEventNO(int start_evt, int stop_evt) {start_evtno = start_evt; stop_evtno = stop_evt;}



        //int AmplitudeMax = 10500;
        //int AmplitudeMin = 7500;
        static int amplitude_bin; // = 10500;
        static int amplitude_max; // = 10500;
        static int amplitude_min; // = 7500;
        static int min_energy;
        static int max_energy;
        static int bin_energy;
        static int min_energy_MWD;
        static int max_energy_MWD;
        static int bin_energy_MWD;
        static int min_energy_GM;
        static int max_energy_GM;
        static int bin_energy_GM;
        static int min_energy_MWD_GM;
        static int max_energy_MWD_GM;
        static int bin_energy_MWD_GM;
        static long min_wr_diff;
        static long max_wr_diff;
        static int bin_wr_diff;
        static int min_wr_rate;
        static int max_wr_rate;
        static int bin_wr_rate;
        static int min_traces;
        static int max_traces;
        static int bin_traces;
        static int fMin_dE_LISA1_gate;
        static int fMax_dE_LISA1_gate;
        static int frun_num;
        static int board_num;
        static int event_ana;
        static int start_evtno;
        static int stop_evtno;

        static bool wr_enable;

        // ::: MDW parameters getters
        float Get_Smoothing_L() const { return smoothing_L; }
        float Get_MWD_Length() const { return MWD_length; }
        //float Get_Decay_Time() const { return decay_time; }
        const float (&Get_Decay_Time() const) [2] { return decay_time; }
        float Get_MWD_Amp_Start() const { return MWD_amp_start; }
        float Get_MWD_Amp_Stop() const { return MWD_amp_stop; }
        float Get_Sampling() const { return sampling; }
        float Get_MWD_Trace_Start() const { return MWD_trace_start; }
        float Get_MWD_Trace_Stop() const { return MWD_trace_stop; }
        float Get_MWD_Baseline_Start() const { return MWD_baseline_start; }
        float Get_MWD_Baseline_Stop() const { return MWD_baseline_stop; }




        //:::::::




    private:


        static std::string MWD_file;
        static std::string mapping_file;
        static std::string gain_matching_file;
        static std::string gain_matching_file_MWD;
        static std::string calibration_file;

        TLisaConfiguration();

        void ReadMWDParameters();
        void ReadMappingFile();
        void ReadGMFile();
        void ReadGMFileMWD();
        void ReadCalibrationCoefficients();

        static TLisaConfiguration* instance;

        //std::map<std::pair<int, int>, std::pair<int, std::pair<int, int>>> detector_mapping;
        std::map<std::pair<int,int>, std::pair<std::pair<int,std::string>, std::pair<int,int>>> detector_mapping;
        std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> gain_matching_coeffs;
        std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> gain_matching_MWD_coeffs;
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


        bool MWD_parameters_loaded = 0;
        bool detector_mapping_loaded = 0;
        bool gain_matching_loaded = 0;
        bool gain_matching_MWD_loaded = 0;
        bool detector_calibrations_loaded = 0;
        bool timeshift_calibration_coeffs_loaded = 0;

        int trace_length = 4000; // default 4k


        //::: Parameter for MWD
        //::: Used for trapezoid calculation (getMWDTrace from anatraces)
        float smoothing_L = 0.1;
        float MWD_length = 0.1;
        float decay_time[2] = {0.1};
        float MWD_amp_start = 0.1;
        float MWD_amp_stop = 0.1;
        float sampling = 0.1;
        float MWD_trace_start = 0.1;
        float MWD_trace_stop = 0.1;
        float MWD_baseline_start = 0.1;
        float MWD_baseline_stop = 0.1;

        //:: test for decay time

        //::: Used for energy calculation (calcEnergy from anatraces)

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

//::: Gain Matching for MWD
inline std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> TLisaConfiguration::GainMatchingMWDCoefficients() const
{
    return gain_matching_MWD_coeffs;
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

inline bool TLisaConfiguration::MWDParametersLoaded() const
{
    return MWD_parameters_loaded;
}


inline bool TLisaConfiguration::MappingLoaded() const
{
    return detector_mapping_loaded;
}


inline bool TLisaConfiguration::GainMatchingLoaded() const
{
    return gain_matching_loaded;
}

inline bool TLisaConfiguration::GainMatchingMWDLoaded() const
{
    return gain_matching_MWD_loaded;
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
