#ifndef TGermaniumConfiguration_H
#define TGermaniumConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "TCutG.h"


//structs

class TGermaniumConfiguration
{
    public:
        static TGermaniumConfiguration const* GetInstance();
        static void Create();


        static void SetDetectorConfigurationFile(std::string fp) { configuration_file = fp; }
        static void SetDetectorCoefficientFile(std::string fp) { calibration_file = fp; }
        static void SetDetectorTimeshiftsFile(std::string fp) { timeshift_calibration_file = fp; }
        static void SetPromptFlashCut(std::string fp) {promptflash_cut_file = fp; }



        std::map<std::pair<int,int>,std::pair<int,int>> Mapping() const;
        bool MappingLoaded() const;
        bool CalibrationCoefficientsLoaded() const;
        std::map<std::pair<int,int>,std::pair<double,double>> CalibrationCoefficients() const;
        bool TimeshiftCalibrationCoefficientsLoaded() const;
        std::map<std::pair<int,int>,double> TimeshiftCalibrationCoefficients() const;
        inline double GetTimeshiftCoefficient(int detector_id, int crystal_id) const;


        inline bool IsInsidePromptFlashCut(double timediff, double energy) const{
            if (prompt_flash_cut != nullptr){
                return prompt_flash_cut->IsInside(timediff,energy);
            }else{
                return true;
            }
        }

        inline bool IsDetectorAuxilliary(int detector_id) const;

        int NDetectors() const;
        int NCrystals() const;
        int CrystalsPerDetector(int detector_id) const;
        int NFebexBoards() const;
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


        TGermaniumConfiguration();
        void ReadConfiguration();
        void ReadCalibrationCoefficients();
        void ReadTimeshiftCoefficients();
        void ReadPromptFlashCut();

        static TGermaniumConfiguration* instance;
        
        std::map<std::pair<int,int>,std::pair<int,int>> detector_mapping;
        std::map<std::pair<int,int>,std::pair<double,double>> calibration_coeffs;
        std::map<std::pair<int,int>,double> timeshift_calibration_coeffs;
        std::set<int> extra_signals;

        TCutG* prompt_flash_cut = nullptr;

        int num_detectors;
        int num_crystals;
        std::map<int,int> crystals_per_detector;
        int num_febex_boards;

        int tm_undelayed;
        int tm_delayed;
        int sc41l_d;
        int sc41r_d;


        int frs_accept;
        int bplast_accept;
        int bplast_free;


        bool detector_mapping_loaded = 0;
        bool detector_calibrations_loaded = 0;
        bool timeshift_calibration_coeffs_loaded = 0;
};


inline bool TGermaniumConfiguration::IsDetectorAuxilliary(int detector_id) const{
    if (extra_signals.count(detector_id)>0){
        return true;
    }else{
        return false;
    }
};


inline TGermaniumConfiguration const* TGermaniumConfiguration::GetInstance()
{
    if (!instance)
    {
        TGermaniumConfiguration::Create();
    }
    return instance;
}

inline void TGermaniumConfiguration::Create()
{
    delete instance;
    instance = new TGermaniumConfiguration();
}

inline std::map<std::pair<int,int>,std::pair<int,int>> TGermaniumConfiguration::Mapping() const
{
    return detector_mapping;
}

inline std::map<std::pair<int,int>,std::pair<double,double>> TGermaniumConfiguration::CalibrationCoefficients() const
{
    return calibration_coeffs;
}

inline std::map<std::pair<int,int>,double> TGermaniumConfiguration::TimeshiftCalibrationCoefficients() const
{
    return timeshift_calibration_coeffs;
}

inline double TGermaniumConfiguration::GetTimeshiftCoefficient(int detector_id, int crystal_id) const
{
    if (!timeshift_calibration_coeffs_loaded){
        return 0;
    }else{
        if (timeshift_calibration_coeffs.count(std::pair<int,int>(detector_id,crystal_id)) > 0){
            return timeshift_calibration_coeffs.at(std::pair<int,int>(detector_id,crystal_id));
        }else{
            return 0;
        }
    }
}

inline int TGermaniumConfiguration::NDetectors() const
{
    return num_detectors;
}

inline int TGermaniumConfiguration::NCrystals() const
{
    return num_crystals;
}


//return the number of crystals per detector.
inline int TGermaniumConfiguration::CrystalsPerDetector(int detector_id) const
{
    if (auto result_crystals_per_detector = crystals_per_detector.find(detector_id); result_crystals_per_detector != crystals_per_detector.end()){
        return crystals_per_detector.at(detector_id);
    }else{
        return 0;
    }
}

inline int TGermaniumConfiguration::NFebexBoards() const
{
    return num_febex_boards;
}

inline bool TGermaniumConfiguration::MappingLoaded() const
{
    return detector_mapping_loaded;
}

inline bool TGermaniumConfiguration::CalibrationCoefficientsLoaded() const
{
    return detector_calibrations_loaded;
}

inline bool TGermaniumConfiguration::TimeshiftCalibrationCoefficientsLoaded() const
{
    return timeshift_calibration_coeffs_loaded;
}

inline int TGermaniumConfiguration::TM_Undelayed() const
{
    return tm_undelayed;
}

inline int TGermaniumConfiguration::TM_Delayed() const
{
    return tm_delayed;
}

inline int TGermaniumConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TGermaniumConfiguration::SC41R() const
{
    return sc41r_d;
}


inline int TGermaniumConfiguration::FRS_accept() const
{
    return frs_accept;
}

inline int TGermaniumConfiguration::bPlast_accept() const
{
    return bplast_accept;
}

inline int TGermaniumConfiguration::bPlast_free() const
{
    return bplast_free;
}

inline std::set<int> TGermaniumConfiguration::ExtraSignals() const
{
    return extra_signals;
}


#endif
