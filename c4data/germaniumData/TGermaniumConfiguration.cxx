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

#include "TGermaniumConfiguration.h"

#include "c4Logger.h"
#include "TCutG.h"
#include "TFile.h"
#include "FairLogger.h"


#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

TGermaniumConfiguration* TGermaniumConfiguration::instance = nullptr;
std::string TGermaniumConfiguration::configuration_file = "blank";
std::string TGermaniumConfiguration::calibration_file = "blank";
std::string TGermaniumConfiguration::timeshift_calibration_file = "blank";
std::string TGermaniumConfiguration::promptflash_cut_file = "blank";
std::string TGermaniumConfiguration::promptflash_cut_file_multi = "blank";


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
    if (promptflash_cut_file_multi != "blank") ReadPromptFlashCutMulti();
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



/*
Takes second order polynomials
*/
void TGermaniumConfiguration::ReadCalibrationCoefficients()
{
    std::ifstream input(calibration_file);
    if (!input) c4LOG(fatal, "Could not open Germanium calibration coefficients: " << calibration_file);

    std::string line;
    std::size_t line_number = 0;
    while (std::getline(input, line))
    {
        ++line_number;
        // Allow blank lines, comments, and trailing comments.
        line = line.substr(0, line.find('#'));
        std::istringstream row(line);
        int detector_id, crystal_id;
        double first, second, third;
        if (!(row >> detector_id))
        {
            if (row.eof()) continue;
            c4LOG(fatal, "Invalid Germanium calibration line " << line_number << " in " << calibration_file);
        }
        if (!(row >> crystal_id >> first >> second))
            c4LOG(fatal, "Incomplete Germanium calibration line " << line_number << " in " << calibration_file);

        // Standard format: det crystal a0 a1 a2.
        // Legacy four-column format (a1, a0): det crystal a1 a0.
        std::vector<double> coefficients;
        if (row >> third)
        {
            coefficients = {first, second, third};
        }
        else if (row.eof())
        {
            coefficients = {second, first, 0.0};
            row.clear();
        }
        else
        {
            c4LOG(fatal, "Invalid Germanium calibration coefficient on line " << line_number << " in " << calibration_file);
        }

        std::string unexpected;
        if (row >> unexpected)
            c4LOG(fatal, "Extra column in Germanium calibration line " << line_number << " in " << calibration_file);
        if (!std::isfinite(coefficients[0]) || !std::isfinite(coefficients[1]) || !std::isfinite(coefficients[2]))
            c4LOG(fatal, "Non-finite Germanium calibration coefficient on line " << line_number << " in " << calibration_file);

        if (!calibration_coeffs.emplace(std::make_pair(detector_id, crystal_id), coefficients).second)
            c4LOG(fatal, "Duplicate Germanium calibration entry on line " << line_number << " in " << calibration_file);
    }

    detector_calibrations_loaded = 1;
    LOG(info) << "Germanium Calibration File: " + calibration_file;
}

void TGermaniumConfiguration::ReadTimeshiftCoefficients()
{
    std::ifstream input(timeshift_calibration_file);
    if (!input) c4LOG(fatal, "Could not open Germanium timeshifts: " << timeshift_calibration_file);

    std::string line;
    std::size_t line_number = 0;
    while (std::getline(input, line))
    {
        ++line_number;
        line = line.substr(0, line.find('#'));
        std::istringstream row(line);
        int detector_id, crystal_id;
        double timeshift;
        if (!(row >> detector_id))
        {
            if (row.eof()) continue;
            c4LOG(fatal, "Invalid Germanium timeshift line " << line_number << " in " << timeshift_calibration_file);
        }
        if (!(row >> crystal_id >> timeshift))
            c4LOG(fatal, "Incomplete Germanium timeshift line " << line_number << " in " << timeshift_calibration_file);

        std::string unexpected;
        if (row >> unexpected)
            c4LOG(fatal, "Extra column in Germanium timeshift line " << line_number << " in " << timeshift_calibration_file);
        if (!std::isfinite(timeshift))
            c4LOG(fatal, "Non-finite Germanium timeshift on line " << line_number << " in " << timeshift_calibration_file);

        if (!timeshift_calibration_coeffs.emplace(std::make_pair(detector_id, crystal_id), timeshift).second)
            c4LOG(fatal, "Duplicate Germanium timeshift entry on line " << line_number << " in " << timeshift_calibration_file);
    }

    timeshift_calibration_coeffs_loaded = 1;
    LOG(info) << "Germanium Timeshift File: " + timeshift_calibration_file;
}

void TGermaniumConfiguration::ReadPromptFlashCut()
{
    // must be a root file (not always the case from saving TCuts)
    // must be named "ge_prompt_flash_cut" precisely 
    TFile* cut = TFile::Open(TString(promptflash_cut_file),"READ");
    
    
    if (!cut || cut->IsZombie() || cut->TestBit(TFile::kRecovered))
    {
        c4LOG(warn, "Germanium prompt flash cut file provided (" << promptflash_cut_file << ") failed to load!.");
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
    
        c4LOG(info, "Germanium prompt flash cut file provided (" << promptflash_cut_file << ") loaded.");


    cut->Close();
}


void TGermaniumConfiguration::ReadPromptFlashCutMulti()
{
    // Open the root file containing the cuts
    c4LOG(info, TString("Opening prompt flash mutli: ") + promptflash_cut_file_multi);
    TFile* cutFile = TFile::Open(TString(promptflash_cut_file_multi), "READ");

    if (!cutFile || cutFile->IsZombie() || cutFile->TestBit(TFile::kRecovered))
    {
        c4LOG(warn, "Germanium prompt flash cut file provided (" << promptflash_cut_file_multi << ") failed to load!");
        return;
    }

    int index = 0;  // Start index
    while (true)
    {
        TString cutName = TString::Format("ge_prompt_flash_cut_%d", index);  // Construct cut name

        TCutG* cut = (TCutG*)cutFile->Get(cutName);  // Try to retrieve the cut

        if (cut) // If a cut is found, set it to prompt_flash_cut_multi and break
        {
            prompt_flash_cut_multi.push_back(cut);
        }else{
            break;
        }
        
        ++index;  // Move to the next cut in sequence

    }

    c4LOG(info,"Read " << prompt_flash_cut_multi.size() << " prompt flash cuts");

    if (prompt_flash_cut_multi.size() == 0) // Log warning if no cut found at all
    {
        c4LOG(warn, "No prompt flash cuts found in file: " << promptflash_cut_file_multi);
    }

    cutFile->Close();
}
