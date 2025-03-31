#ifndef TH10MCPConfiguration_H
#define TH10MCPConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "TCutG.h"
#include "GainShift.h"


//structs

class TH10MCPConfiguration
{
    public:
        static TH10MCPConfiguration const* GetInstance();
        static void Create();
        static void SetDetectorConfigurationFile(std::string fp) { configuration_file = fp; }
        static void SetDetectorCoefficientFile(std::string fp) { calibration_file = fp; }
        static void SetDetectorTimeshiftsFile(std::string fp) { timeshift_calibration_file = fp; }
        static void SetPromptFlashCutFile(std::string fp) {promptflash_cut_file = fp; }
        static void SetGainShiftFile(std::string fp) {gain_shifts_file = fp; }


        std::map<std::pair<int,int>,int> Mapping() const;
        bool MappingLoaded() const;
        
        bool CalibrationCoefficientsLoaded() const;
        std::map<int,std::vector<double>> CalibrationCoefficients() const;

        bool TimeshiftCalibrationCoefficientsLoaded() const;
        std::map<std::pair<int,int>,double> TimeshiftCalibrationCoefficients() const;
        inline double GetTimeshiftCoefficient(int detector_id1, int detector_id2) const;

        bool GainShiftsLoaded() const;
        inline double GetGainShift(int detector_id1, uint64_t wr_t) const;


        inline bool IsDetectorAuxilliary(int detector_id) const;



        inline bool IsInsidePromptFlashCut(double timediff, double energy) const{
            if (prompt_flash_cut != nullptr){
                return prompt_flash_cut->IsInside(timediff,energy);
            }else{
                return false;
            }
        }



        int NDetectors() const;
        int NTamexBoards() const;
        int TM_Undelayed() const;
        int TM_Delayed() const;
        int SC41L() const;
        int SC41R() const;
        int FRS_accept() const;
        int bPlast_accept() const;
        int bPlast_free() const;
        std::set<int> ExtraSignals() const;

    private:

        static std::string configuration_file;
        static std::string calibration_file;
        static std::string timeshift_calibration_file;
        static std::string promptflash_cut_file;
        static std::string gain_shifts_file;


        TH10MCPConfiguration();
        void ReadConfiguration();
        void ReadCalibrationCoefficients();
        void ReadTimeshiftCoefficients();
        void ReadPromptFlashCut();
        void ReadGainShifts();

        static TH10MCPConfiguration* instance;
        
        std::map<std::pair<int,int>,int> detector_mapping; // [board_id][channel_id] -> [detector_id]
        std::map<int,std::vector<double>> calibration_coeffs; // key: [detector id] -> vector[a0 - a3] index is coefficient number 0 = offset +++ expects quadratic.
        std::map<std::pair<int,int>,double> timeshift_calibration_coeffs;

        std::set<int> extra_signals;


        TCutG* prompt_flash_cut = nullptr;

        std::vector<GainShift*> gain_shifts;


        int num_detectors;
        int num_tamex_boards;
        int num_tamex_channels;

        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;

        int frs_accept;
        int bplast_accept;
        int bplast_free;

        bool detector_map_loaded = 0;
        bool detector_calibrations_loaded = 0;
        bool timeshift_calibration_coeffs_loaded = 0;
        bool gain_shifts_loaded = 0;

};




inline bool TH10MCPConfiguration::IsDetectorAuxilliary(int detector_id) const{
    if (extra_signals.count(detector_id)>0){
        return true;
    }else{
        return false;
    }
};

inline std::map<int,std::vector<double>> TH10MCPConfiguration::CalibrationCoefficients() const 
{
    return calibration_coeffs;
}

inline bool TH10MCPConfiguration::CalibrationCoefficientsLoaded() const {
    return detector_calibrations_loaded;
}

inline bool TH10MCPConfiguration::GainShiftsLoaded() const {
    return gain_shifts_loaded;
}


inline std::map<std::pair<int,int>,double> TH10MCPConfiguration::TimeshiftCalibrationCoefficients() const
{
    return timeshift_calibration_coeffs;
}

inline double TH10MCPConfiguration::GetTimeshiftCoefficient(int detector_id1, int detector_id2) const
{
    // where t2 - t1:
    std::pair<int,int> dets;
    if (!timeshift_calibration_coeffs_loaded){
        return 0;
    }
    
    if(detector_id2 > detector_id1){
        dets.first = detector_id1;
        dets.second = detector_id2;
        if (timeshift_calibration_coeffs.count(dets) > 0){
            return timeshift_calibration_coeffs.at(dets);
        }else return 0;

    } else if (detector_id1 > detector_id2){
        dets.first = detector_id2;
        dets.second = detector_id1;
        if (timeshift_calibration_coeffs.count(dets) > 0){
            return - timeshift_calibration_coeffs.at(dets);
        }else return 0;
    }else{
        return 0;
    }
     
}

inline double TH10MCPConfiguration::GetGainShift(int detector_id1, uint64_t wr_t) const
{
    if (IsDetectorAuxilliary(detector_id1)) return 1;
    return gain_shifts.at(detector_id1-1)->GetGain(wr_t);     
}

inline TH10MCPConfiguration const* TH10MCPConfiguration::GetInstance()
{
    if (!instance)
    {
        TH10MCPConfiguration::Create();
    }
    return instance;
}

inline void TH10MCPConfiguration::Create()
{
    delete instance;
    instance = new TH10MCPConfiguration();
}


inline bool TH10MCPConfiguration::TimeshiftCalibrationCoefficientsLoaded() const
{
    return timeshift_calibration_coeffs_loaded;
}


inline std::map<std::pair<int,int>,int> TH10MCPConfiguration::Mapping() const
{
  return detector_mapping;
}

inline bool TH10MCPConfiguration::MappingLoaded() const
{
    return detector_map_loaded;
}

inline int TH10MCPConfiguration::NDetectors() const
{
    return num_detectors;
}

inline int TH10MCPConfiguration::NTamexBoards() const
{
    return num_tamex_boards;
}

inline int TH10MCPConfiguration::TM_Undelayed() const
{
    return tm_undelayed;
}

inline int TH10MCPConfiguration::TM_Delayed() const
{
    return tm_delayed;
}

inline int TH10MCPConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TH10MCPConfiguration::SC41R() const
{
    return sc41r_d;
}

inline int TH10MCPConfiguration::FRS_accept() const
{
    return frs_accept;
}

inline int TH10MCPConfiguration::bPlast_accept() const
{
    return bplast_accept;
}

inline int TH10MCPConfiguration::bPlast_free() const
{
    return bplast_free;
}

inline std::set<int> TH10MCPConfiguration::ExtraSignals() const
{
    return extra_signals;
}

#endif