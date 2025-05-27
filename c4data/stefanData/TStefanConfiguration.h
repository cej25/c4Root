#ifndef TStefanConfiguration_H
#define TStefanConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "TCutG.h"

//structs

class TStefanConfiguration
{
    public:
        static TStefanConfiguration const* GetInstance();
        static void Create();

        static void SetDetectorConfigurationFile(std::string fp) { mapping_file = fp; }
        static void SetDetectorCoefficientFile(std::string fp) { calibration_file = fp; }


        std::map<std::pair<int, int>, std::pair<int, std::pair<int,int>>> Mapping() const;
        bool MappingLoaded() const;
        bool CalibrationLoaded() const;
        std::map<std::pair<int, std::pair<int, int>>, int> CalibrationCoefficients() const;


        inline bool IsInsidePromptFlashCut(double timediff, double energy) const{
            if (prompt_flash_cut != nullptr){
                return prompt_flash_cut->IsInside(timediff,energy);
            }else{
                return true;
            }
        }

        inline bool IsInsidePromptFlashCutMulti(double timediff, double energy, int id) const{
            if ((prompt_flash_cut_multi.size() >= 1) && (prompt_flash_cut_multi.size() >= id)){
                return prompt_flash_cut_multi.at(id)->IsInside(timediff,energy);
            }else{
                return IsInsidePromptFlashCut(timediff, energy);
            }
        }

        inline bool IsDetectorAuxilliary(int detector_id) const;

        int DSSDs() const;
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

        static void SetFrontBackTime(Double_t tdiff) { fbt = tdiff; }
        static void SetFrontBackEnergy(Double_t ediff) { fbe = ediff; }
        static Double_t fbt;
        static Double_t fbe;

    private:

        static std::string calibration_file;
        static std::string mapping_file;


        TStefanConfiguration();
        void ReadConfiguration();
        void ReadCalibrationCoefficients();
        void ReadTimeshiftCoefficients();
        void ReadPromptFlashCut();
        void ReadPromptFlashCutMulti();

        static TStefanConfiguration* instance;
        
        std::map<std::pair<int, int>, std::pair<int, std::pair<int,int>>> detector_mapping;
        std::map<std::pair<int, std::pair<int, int>>, int>  calibration_coeffs;
        std::set<int> extra_signals;

        TCutG* prompt_flash_cut = nullptr;

        std::vector<TCutG *> prompt_flash_cut_multi = {};

        int num_dssds;
        std::map<int,int> crystals_per_detector;
        int num_febex_boards;

        int tm_undelayed = -1;
        int tm_delayed = -1;
        int sc41l_d = -1;
        int sc41r_d = -1;


        int frs_accept = -1;
        int bplast_accept = -1;
        int bplast_free = -1;


        bool detector_mapping_loaded = 0;
        bool detector_calibrations_loaded = 0;
        bool timeshift_calibration_coeffs_loaded = 0;
};


inline bool TStefanConfiguration::IsDetectorAuxilliary(int detector_id) const{
    if (extra_signals.count(detector_id)>0){
        return true;
    }else{
        return false;
    }
};


inline TStefanConfiguration const* TStefanConfiguration::GetInstance()
{
    if (!instance)
    {
        TStefanConfiguration::Create();
    }
    return instance;
}

inline void TStefanConfiguration::Create()
{
    delete instance;
    instance = new TStefanConfiguration();
}

inline std::map<std::pair<int, int>, std::pair<int, std::pair<int,int>>>TStefanConfiguration::Mapping() const
{
    return detector_mapping;
}

inline std::map<std::pair<int, std::pair<int, int>>, int> TStefanConfiguration::CalibrationCoefficients() const
{
    return calibration_coeffs;
}

inline int TStefanConfiguration::DSSDs() const
{
    return num_dssds;
}

inline int TStefanConfiguration::NFebexBoards() const
{
    return num_febex_boards;
}

inline bool TStefanConfiguration::MappingLoaded() const
{
    return detector_mapping_loaded;
}

inline bool TStefanConfiguration::CalibrationLoaded() const
{
    return detector_calibrations_loaded;
}


inline int TStefanConfiguration::TM_Undelayed() const
{
    return tm_undelayed;
}

inline int TStefanConfiguration::TM_Delayed() const
{
    return tm_delayed;
}

inline int TStefanConfiguration::SC41L() const
{
    return sc41l_d;
}

inline int TStefanConfiguration::SC41R() const
{
    return sc41r_d;
}


inline int TStefanConfiguration::FRS_accept() const
{
    return frs_accept;
}

inline int TStefanConfiguration::bPlast_accept() const
{
    return bplast_accept;
}

inline int TStefanConfiguration::bPlast_free() const
{
    return bplast_free;
}

inline std::set<int> TStefanConfiguration::ExtraSignals() const
{
    return extra_signals;
}


#endif