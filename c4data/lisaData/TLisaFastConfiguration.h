#ifndef TLisaFastConfiguration_H
#define TLisaFastConfiguration_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>
#include "TCutG.h"
#include "GainShift.h"
#include <tuple>


//structs

class TLisaFastConfiguration
{
    public:
        static TLisaFastConfiguration const* GetInstance();
        static void Create();
        static void SetDetectorConfigurationFile(std::string fp) { configuration_file = fp; }
        static void SetDetectorCoefficientFile(std::string fp) { calibration_file = fp; }
        static void SetDetectorTimeshiftsFile(std::string fp) { timeshift_calibration_file = fp; } //what is this ??
        static void SetPromptFlashCutFile(std::string fp) {promptflash_cut_file = fp; } //what is this ??
        static void SetGainShiftFile(std::string fp) {gain_shifts_file = fp; }


        typedef std::pair<std::pair<int, std::pair<int,int>>,std::pair<float, std::pair<std::string,std::string>>> LisaDiamondInfo;
        
        std::map<std::pair<int,int>, int>             LaBr_Mapping() const;
        std::map<std::pair<int,int>, LisaDiamondInfo> Diamond_Mapping() const;  

        //std::map<std::pair<int,int>,int> Mapping() const;
        bool MappingLoaded() const;
        bool DiamondMappingLoaded() const;
        bool LaBrMappingLoaded() const; 
        
        bool CalibrationCoefficientsLoaded() const;

        std::map<int,std::vector<double>> LaBrCalibrationCoefficients() const;
        std::map<std::tuple<int,int,int>,std::vector<double>> DiamondCalibrationCoefficients() const;

        bool GetLaBrCalibration(int detector_id, std::vector<double>& coeffs) const;
        bool GetDiamondCalibration(int layer, int x, int y, std::vector<double>& coeffs) const;
        
        //bool CalibrationCoefficientsLoaded() const;
        //std::map<int,std::vector<double>> CalibrationCoefficients() const;

        bool TimeshiftCalibrationCoefficientsLoaded() const;
        std::map<std::pair<int,int>,double> TimeshiftCalibrationCoefficients() const;
        inline double GetTimeshiftCoefficient(int detector_id1, int detector_id2) const;

        bool GainShiftsLoaded() const;
        inline double GetGainShift(int tamex_board, int tamex_channel, uint64_t wr_t) const;
        //inline double GetGainShift(int detector_id1, uint64_t wr_t) const;


        inline bool IsDetectorAuxilliary(int detector_id) const; //what is this


        inline bool IsInsidePromptFlashCut(double timediff, double energy) const{
            if (prompt_flash_cut != nullptr){
                return prompt_flash_cut->IsInside(timediff,energy);
            }else{
                return false;
            }
        } //what is this

        int NDiamondDetectors() const;
        int NDiamondLayers() const;
        int NLaBrDetectors() const;          
        int XMax() const;                // diamond x
        int YMax() const;                // diamond y
        int NTamexBoards() const;

 
        std::set<int> ExtraSignals() const;

        //:::::Ranges in Histos
        // Slow Tot
        static void SetSlowToT_bin(int bin_slowToT) { slowToT_bin = bin_slowToT; }
        static void SetSlowToT_max(int max_slowToT) { slowToT_max = max_slowToT; }
        static void SetSlowToT_min(int min_slowToT) { slowToT_min = min_slowToT; }

        // Fast Tot
        static void SetFastToT_bin(int bin_fastToT) { fastToT_bin = bin_fastToT; }
        static void SetFastToT_max(int max_fastToT) { fastToT_max = max_fastToT; }
        static void SetFastToT_min(int min_fastToT) { fastToT_min = min_fastToT; }

        // Energy
        static void SetEnergy_bin(int bin_energy) { energy_bin = bin_energy; }
        static void SetEnergy_max(int max_energy) { energy_max = max_energy; }
        static void SetEnergy_min(int min_energy) { energy_min = min_energy; }

        // dTime
        static void SetdT_bin(int bin_dt) { dt_bin = bin_dt; }
        static void SetdT_max(int max_dt) { dt_max = max_dt; }
        static void SetdT_min(int min_dt) { dt_min = min_dt; }

        // Energy gate witdh
        static void SetEnergyGateWidth(int width) { en_gate_width = width; }

        
        
        static int slowToT_bin;
        static int slowToT_max;
        static int slowToT_min;

        static int fastToT_bin;
        static int fastToT_max;
        static int fastToT_min;

        static int energy_bin;
        static int energy_max;
        static int energy_min;

        static int dt_bin;
        static int dt_max;
        static int dt_min;

        static int en_gate_width;
        
        

    private:

        static std::string configuration_file;
        static std::string calibration_file;
        static std::string timeshift_calibration_file;
        static std::string promptflash_cut_file;
        static std::string gain_shifts_file;


        TLisaFastConfiguration();
        ~TLisaFastConfiguration();

        void ReadConfiguration();
        void ReadCalibrationCoefficients();
        void ReadTimeshiftCoefficients();
        void ReadPromptFlashCut();
        void ReadGainShifts();

        static TLisaFastConfiguration* instance;
        
        // (layer, (x, y)), (thickness, (name, serial number))
        std::map<std::pair<int,int>, LisaDiamondInfo> diamond_mapping;
        
        // ((board_id,chhannel_id), det_id)
        std::map<std::pair<int,int>,int> labr_mapping; // [board_id][channel_id] -> [detector_id]
        
        // LaBr: detector_id -> a0-a3
        std::map<int,std::vector<double>> labr_calibration_coeffs;

        // Diamond: (layer,x,y) -> a0-a3
        std::map<std::tuple<int,int,int>,std::vector<double>> diamond_calibration_coeffs;
        
        //std::map<int,std::vector<double>> calibration_coeffs; // key: [detector id] -> vector[a0 - a3] index is coefficient number 0 = offset +++ expects quadratic.
        std::map<std::pair<int,int>,double> timeshift_calibration_coeffs;

        std::set<int> extra_signals;


        TCutG* prompt_flash_cut = nullptr;

        std::map<std::pair<int,int>, GainShift*> gain_shifts; // (tamex board, channel) -> GainShift, LaBr and Diamond
        //std::vector<GainShift*> gain_shifts;

        int num_labr_detectors;
        int num_diamond_detectors;
        int num_diamond_layers;
        int xmax;
        int ymax;
        int num_tamex_boards;
        int num_tamex_channels;

        //bool detector_map_loaded = 0;
        bool labr_map_loaded = 0;
        bool diamond_map_loaded = 0;
        bool detector_calibrations_loaded = 0;
        bool timeshift_calibration_coeffs_loaded = 0;
        bool gain_shifts_loaded = 0;

};




inline bool TLisaFastConfiguration::IsDetectorAuxilliary(int detector_id) const{ //??
    if (extra_signals.count(detector_id)>0){
        return true;
    }else{
        return false;
    }
};

// inline std::map<int,std::vector<double>> TLisaFastConfiguration::CalibrationCoefficients() const 
// {
//     return calibration_coeffs;
// }

inline std::map<int,std::vector<double>> TLisaFastConfiguration::LaBrCalibrationCoefficients() const {
    return labr_calibration_coeffs;
}

inline std::map<std::tuple<int,int,int>,std::vector<double>>TLisaFastConfiguration::DiamondCalibrationCoefficients() const {
    return diamond_calibration_coeffs;
}

inline bool TLisaFastConfiguration::GetLaBrCalibration(int detector_id,std::vector<double>& coeffs) const {
    auto it = labr_calibration_coeffs.find(detector_id);

    if (it == labr_calibration_coeffs.end())
        return false;

    coeffs = it->second;
    return true;
}


inline bool TLisaFastConfiguration::GetDiamondCalibration(int layer, int x, int y, std::vector<double>& coeffs) const{
    auto key = std::make_tuple(layer, x, y);

    auto it = diamond_calibration_coeffs.find(key);

    if (it == diamond_calibration_coeffs.end())
        return false;

    coeffs = it->second;
    return true;
}

inline bool TLisaFastConfiguration::CalibrationCoefficientsLoaded() const {
    return detector_calibrations_loaded;
}

inline bool TLisaFastConfiguration::GainShiftsLoaded() const {
    return gain_shifts_loaded;
}


inline std::map<std::pair<int,int>,double> TLisaFastConfiguration::TimeshiftCalibrationCoefficients() const
{
    return timeshift_calibration_coeffs;
}

inline double TLisaFastConfiguration::GetTimeshiftCoefficient(int detector_id1, int detector_id2) const
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

// inline double TLisaFastConfiguration::GetGainShift(int detector_id1, uint64_t wr_t) const
// {
//     if (IsDetectorAuxilliary(detector_id1)) return 1;
//     if (detector_id1 < 1 || detector_id1 > (int)gain_shifts.size()) return 1;
//     return gain_shifts.at(detector_id1-1)->GetGain(wr_t);     
// }

inline double TLisaFastConfiguration::GetGainShift(int tamex_board, int tamex_channel, uint64_t wr_t) const
{
    auto it = gain_shifts.find({tamex_board, tamex_channel});
    if (it == gain_shifts.end()) return 1;   // auxiliary signal or unknown channel: no correction
    return it->second->GetGain(wr_t);
}

inline TLisaFastConfiguration const* TLisaFastConfiguration::GetInstance()
{
    if (!instance)
    {
        TLisaFastConfiguration::Create();
    }
    return instance;
}

inline void TLisaFastConfiguration::Create()
{
    delete instance;
    instance = new TLisaFastConfiguration();
}


inline bool TLisaFastConfiguration::TimeshiftCalibrationCoefficientsLoaded() const
{
    return timeshift_calibration_coeffs_loaded;
}


inline std::map<std::pair<int,int>,int> TLisaFastConfiguration::LaBr_Mapping() const
{
  return labr_mapping;
}

inline std::map<std::pair<int,int>, TLisaFastConfiguration::LisaDiamondInfo> TLisaFastConfiguration::Diamond_Mapping() const
{
    return diamond_mapping;
}

inline bool TLisaFastConfiguration::MappingLoaded() const
{
    return labr_map_loaded || diamond_map_loaded;
}

inline bool TLisaFastConfiguration::LaBrMappingLoaded() const
{
    return labr_map_loaded;
}

inline bool TLisaFastConfiguration::DiamondMappingLoaded() const
{
    return diamond_map_loaded;
}

inline int TLisaFastConfiguration::NDiamondLayers() const
{
    return num_diamond_layers;
}

inline int TLisaFastConfiguration::XMax() const
{
    return xmax;
}

inline int TLisaFastConfiguration::YMax() const
{
    return ymax;
}

inline int TLisaFastConfiguration::NDiamondDetectors() const
{
    return num_diamond_detectors;
}

inline int TLisaFastConfiguration::NLaBrDetectors() const
{
    return num_labr_detectors;
}

inline int TLisaFastConfiguration::NTamexBoards() const
{
    return num_tamex_boards;
}


inline std::set<int> TLisaFastConfiguration::ExtraSignals() const
{
    return extra_signals;
}

#endif