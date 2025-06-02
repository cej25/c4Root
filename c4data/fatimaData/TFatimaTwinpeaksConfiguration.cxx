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
 *                             J.E.L. Larsson                                 *
 *                                06.05.25                                    *
 ******************************************************************************/

#include "TFatimaTwinpeaksConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include "TFile.h"

TFatimaTwinpeaksConfiguration* TFatimaTwinpeaksConfiguration::instance = nullptr;
std::string TFatimaTwinpeaksConfiguration::configuration_file = "blank";
std::string TFatimaTwinpeaksConfiguration::calibration_file = "blank";
std::string TFatimaTwinpeaksConfiguration::timeshift_calibration_file = "blank";
std::string TFatimaTwinpeaksConfiguration::promptflash_cut_file = "blank";
std::string TFatimaTwinpeaksConfiguration::gain_shifts_file = "blank";


TFatimaTwinpeaksConfiguration::TFatimaTwinpeaksConfiguration()
    :   num_detectors(0)
    ,   num_tamex_boards(0)
    ,   num_tamex_channels(0)
{
    if (configuration_file != "blank") ReadConfiguration();
    if (calibration_file != "blank") ReadCalibrationCoefficients();
    if (timeshift_calibration_file != "blank") ReadTimeshiftCoefficients();
    if (promptflash_cut_file != "blank") ReadPromptFlashCut();
    if (gain_shifts_file != "blank") ReadGainShifts();
}

void TFatimaTwinpeaksConfiguration::ReadConfiguration()
{

    std::ifstream detector_map_file(configuration_file);
    std::string line;
    std::set<int> tamex_boards;
    std::set<int> detectors;
    int tamex_channels = 0;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open Fatima Twinpeaks allocation file: " + configuration_file);

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal;
        int tamex_board, tamex_channel, detector;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            tamex_board = std::stoi(signal);

            iss >> tamex_channel >> detector;

        }
        else // some additional signal
        {
            iss >> tamex_board >> tamex_channel >> detector;

            if (signal == "TimeMachineU") tm_undelayed = detector;
            else if (signal == "TimeMachineD") tm_delayed = detector;
            else if (signal == "SC41L_D") sc41l_d = detector;
            else if (signal == "SC41R_D") sc41r_d = detector;
            else if (signal == "FRS_ACCEPT") frs_accept = detector;
            else if (signal == "BPLAST_ACCEPT") bplast_accept = detector;
            else if (signal == "BPLAST_FREE") bplast_free = detector;

            extra_signals.insert(detector);
        }

        if (tamex_board > -1) tamex_boards.insert(tamex_board);
        if (detector > -1) detectors.insert(detector);
        tamex_channels++;

        std::pair<int, int> tamex_mc = {tamex_board, tamex_channel};

        detector_mapping.insert(std::pair<std::pair<int, int>, int> {tamex_mc, detector});  
        
    }

    num_tamex_boards = tamex_boards.size();
    num_detectors = detectors.size();
    num_tamex_channels = tamex_channels;

    detector_map_loaded = 1;
    detector_map_file.close();
    LOG(info) << "FatimaTwinpeaks Allocation coefficients File: " + configuration_file;
    return;
}

void TFatimaTwinpeaksConfiguration::ReadCalibrationCoefficients(){

    std::ifstream calibration_coeff_file (calibration_file);

    if (calibration_coeff_file.fail()) c4LOG(fatal, "Could not open Fatima calibration coefficients file.");


    int rdetector_id; // temp read variables
    
    //assumes the first line in the file is num-modules used
    while(!calibration_coeff_file.eof()){
        if(calibration_coeff_file.peek()=='#') calibration_coeff_file.ignore(256,'\n');
        else{
            double a0,a1,a2,a3;
            calibration_coeff_file >> rdetector_id >> a0 >> a1 >> a2 >> a3;
            std::vector<double> cals = {a0,a1,a2,a3};

            calibration_coeffs.insert(std::pair<int,std::vector<double>>{rdetector_id,cals});
            calibration_coeff_file.ignore(256,'\n');
        }
    }
    detector_calibrations_loaded = 1;
    calibration_coeff_file.close();

    LOG(info) << "FatimaTwinpeaks Calibration coefficients File: " + calibration_file;
    return; 
}






void TFatimaTwinpeaksConfiguration::ReadTimeshiftCoefficients()
{
    c4LOG(info, "Reading Timeshift coefficients.");
    c4LOG(info, "File reading");
    c4LOG(info, timeshift_calibration_file);

    std::ifstream timeshift_file (timeshift_calibration_file);

    int rdetector_id1, rdetector_id2; // temp read variables
    double timeshift;
    
    //assumes the first line in the file is num-modules used
    while(!timeshift_file.eof()){
        if(timeshift_file.peek()=='#') timeshift_file.ignore(256,'\n');
        else{
            timeshift_file >> rdetector_id1 >> rdetector_id2 >> timeshift;

            timeshift_calibration_coeffs.insert(std::pair<std::pair<int,int>,double>{std::pair<int,int>(rdetector_id1,rdetector_id2),timeshift});
            timeshift_file.ignore(256,'\n');
        }
    }
    timeshift_calibration_coeffs_loaded = 1;
    timeshift_file.close();
    return; 

};


void TFatimaTwinpeaksConfiguration::ReadPromptFlashCut()
{
    // must be a root file (not always the case from saving TCuts)
    // must be named "fatima_prompt_flash_cut"!
    TFile* cut = TFile::Open(TString(promptflash_cut_file),"READ");
    
    if (!cut || cut->IsZombie() || cut->TestBit(TFile::kRecovered))
    {
        c4LOG(warn, "FatimaTwinpeaks prompt flash cut file provided (" << promptflash_cut_file << ") is not a ROOT file.");
        return;
    }
    
    if (cut->Get("fatima_prompt_flash_cut"))
    {
        
        prompt_flash_cut = (TCutG*)cut->Get("fatima_prompt_flash_cut");
        LOG(info) << "FatimaTwinpeaks Prompt flash cut File: " + promptflash_cut_file;
    }
    else
    {
        c4LOG(warn, "FatimaTwinpeaks prompt flash cut does not exist in file: " << promptflash_cut_file);
    }

    cut->Close();
}


void TFatimaTwinpeaksConfiguration::ReadGainShifts()
{
    // must be a root file (not always the case from saving TCuts)
    // must be named "fatima_prompt_flash_cut"!

    for (int i = 1; i<=NDetectors(); i++){
        if (IsDetectorAuxilliary(i)) continue;
        c4LOG(info, TString("Creating GainShifts for ") + TString(Form("fatima_gain_shift_det_%i",i)) + TString(" at ") + TString(gain_shifts_file));
        GainShift * g = new GainShift(TString(Form("fatima_gain_shift_det_%i",i)),TString(gain_shifts_file));
        gain_shifts.push_back(g);
    }
    gain_shifts_loaded = 1;
}

