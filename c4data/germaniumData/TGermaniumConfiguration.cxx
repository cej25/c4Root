#include "TGermaniumConfiguration.h"

#include "c4Logger.h"
#include "TCutG.h"
#include "TFile.h"
#include "FairLogger.h"


#include <iostream>
#include <sstream>
#include <string>

TGermaniumConfiguration* TGermaniumConfiguration::instance = nullptr;
std::string TGermaniumConfiguration::configuration_file = "blank";
std::string TGermaniumConfiguration::calibration_file = "blank";
std::string TGermaniumConfiguration::timeshift_calibration_file = "blank";
std::string TGermaniumConfiguration::promptflash_cut_file = "blank";


TGermaniumConfiguration::TGermaniumConfiguration()
:   num_detectors(0)
,   num_crystals(0)
,   num_febex_boards(0)
{
    if (configuration_file != "blank") ReadConfiguration();
    else c4LOG(fatal,"You must set TGermaniumConfiguration::SetConfigurationFile()!!");

    if (calibration_file != "blank") ReadCalibrationCoefficients();
    if (timeshift_calibration_file != "blank") ReadTimeshiftCoefficients();
    if (promptflash_cut_file != "blank") ReadPromptFlashCut();
 }


void TGermaniumConfiguration::ReadConfiguration()
{   
    std::set<int> febex_boards;
    std::set<int> detector_ids;
    int crystals = 0;

    std::ifstream detector_map_file(configuration_file);
    std::string line;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open Germanium Detector Map");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal;
        int febex_board, febex_channel, detector_id, crystal_id;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            febex_board = std::stoi(signal);

            iss >> febex_channel >> detector_id >> crystal_id;
        }
        else
        {
            iss >> febex_board >> febex_channel >> detector_id >> crystal_id;

            if (signal == "TimeMachineU") tm_undelayed = detector_id;
            else if (signal == "TimeMachineD") tm_delayed = detector_id;
            else if (signal == "SC41L_D") sc41l_d = detector_id;
            else if (signal == "SC41R_D") sc41r_d = detector_id;
            else if (signal == "FRS_ACCEPT") frs_accept = detector_id;
            else if (signal == "BPLAST_ACCEPT") bplast_accept = detector_id;
            else if (signal == "BPLAST_FREE") bplast_free = detector_id;

            extra_signals.insert(detector_id);
        }

        febex_boards.insert(febex_board);
        if (detector_id >= 0) detector_ids.insert(detector_id);
        if (auto result_crystals_per_detector = crystals_per_detector.find(detector_id); result_crystals_per_detector != crystals_per_detector.end()){
            crystals_per_detector[detector_id]++;
        }else{
            crystals_per_detector.insert(std::pair<int,int> {detector_id,1});
        }
        
        crystals++;

        std::pair<int, int> febex_mc = {febex_board, febex_channel};
        std::pair<int, int> ge_cd = {detector_id, crystal_id};

        detector_mapping.insert(std::pair<std::pair<int, int>, std::pair<int, int>> {febex_mc, ge_cd});
    
    }

    num_detectors = detector_ids.size();
    num_crystals = crystals;
    num_febex_boards = febex_boards.size();

    detector_mapping_loaded = 1;
    detector_map_file.close();

    LOG(info) << "Germanium Configuration File: " + configuration_file;
    return;

}




void TGermaniumConfiguration::ReadCalibrationCoefficients()
{

    std::ifstream cal_map_file (calibration_file);
    if (cal_map_file.fail()) c4LOG(fatal, "Could not open Germanium calibration coefficients");    

    int rdetector_id,rcrystal_id; // temp read variables
    double a0,a1;
    
    //assumes the first line in the file is num-modules used
    while(!cal_map_file.eof()){
        if(cal_map_file.peek()=='#') cal_map_file.ignore(256,'\n');
        else{
            cal_map_file >> rdetector_id >> rcrystal_id >> a1 >> a0;
            std::pair<int,int> detector_crystal = {rdetector_id,rcrystal_id};
            std::pair<double,double> cals = {a0,a1};
            calibration_coeffs.insert(std::pair<std::pair<int,int>,std::pair<double,double>>{detector_crystal,cals});
            cal_map_file.ignore(256,'\n');
        }
    }
    detector_calibrations_loaded = 1;
    cal_map_file.close();

    LOG(info) << "Germanium Calibration File: " + calibration_file;
};


void TGermaniumConfiguration::ReadTimeshiftCoefficients()
{
    std::ifstream timeshift_file (timeshift_calibration_file);


    if (timeshift_file.fail()) c4LOG(fatal, "Could not open Germanium timeshifts");    
    int rdetector_id,rcrystal_id; // temp read variables
    double t0;
    
    //assumes the first line in the file is num-modules used
    while(!timeshift_file.eof()){
        if(timeshift_file.peek()=='#') timeshift_file.ignore(256,'\n');
        else{
            timeshift_file >> rdetector_id >> rcrystal_id >> t0;
            c4LOG(info,Form("det = %i , cr = %i, t = %f",rdetector_id,rcrystal_id,t0));
            std::pair<int,int> detector_crystal = {rdetector_id,rcrystal_id};
            timeshift_calibration_coeffs.insert(std::pair<std::pair<int,int>,double>{detector_crystal,t0});
            timeshift_file.ignore(256,'\n');
        }
    }
    timeshift_calibration_coeffs_loaded = 1;

    timeshift_file.close();

    LOG(info) << "Germanium Timeshift File: " + timeshift_calibration_file;
};

void TGermaniumConfiguration::ReadPromptFlashCut()
{
    // must be a root file (not always the case from saving TCuts)
    // must be named "ge_prompt_flash_cut" precisely 
    TFile* cut = TFile::Open(TString(promptflash_cut_file),"READ");
    
    if (!cut || cut->IsZombie() || cut->TestBit(TFile::kRecovered))
    {
        c4LOG(warn, "Germanium prompt flash cut file provided (" << promptflash_cut_file << ") is not a ROOT file.");
        return;
    }
    
    if (cut->Get("ge_prompt_flash_cut"))
    {
        prompt_flash_cut = (TCutG*)cut->Get("ge_prompt_flash_cut");
    }
    else
    {
        c4LOG(warn, "Germanium prompt flash cut does not exist in file: " << promptflash_cut_file);
    }

    cut->Close();
}

