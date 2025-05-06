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
 *                              C.E. Jones                                    *
 *                               06.05.25                                     *
 ******************************************************************************/

#include "TH10MCPConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include "TFile.h"

TH10MCPConfiguration* TH10MCPConfiguration::instance = nullptr;
std::string TH10MCPConfiguration::configuration_file = "blank";
std::string TH10MCPConfiguration::calibration_file = "blank";
std::string TH10MCPConfiguration::timeshift_calibration_file = "blank";


TH10MCPConfiguration::TH10MCPConfiguration()
    :   num_mcps(0)
    ,   num_tamex_boards(0)
    ,   num_tamex_channels(0)
{
    if (configuration_file != "blank") ReadConfiguration();
    if (calibration_file != "blank") ReadCalibrationCoefficients();
    if (timeshift_calibration_file != "blank") ReadTimeshiftCoefficients();
}


void TH10MCPConfiguration::ReadConfiguration()
{

    std::ifstream detector_map_file(configuration_file);
    std::string line;
    std::set<int> tamex_boards;
    std::set<int> mcps;
    int tamex_channels = 0;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open H10MCP Twinpeaks allocation file");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal;
        int tamex_board, tamex_channel, mcp, type, number;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            tamex_board = std::stoi(signal);

            iss >> tamex_channel >> mcp >> type >> number;

        }
        else // some additional signal
        {
            iss >> tamex_board >> tamex_channel >> mcp >> type >> number;

            // CEJ deal with this if we come to it.. 
            if (signal == "TimeMachineU") tm_undelayed = mcp;
            else if (signal == "TimeMachineD") tm_delayed = mcp;
            else if (signal == "SC41L_D") sc41l_d = mcp;
            else if (signal == "SC41R_D") sc41r_d = mcp;
            else if (signal == "FRS_ACCEPT") frs_accept = mcp;

            extra_signals.insert(mcp);
        }

        if (tamex_board > -1) tamex_boards.insert(tamex_board);
        if (mcp > -1) mcps.insert(mcp);
        tamex_channels++;

        std::pair<int, int> tamex_mc = {tamex_board, tamex_channel};
        std::pair<int, std::pair<int, int>> mcp_output = {mcp, std::make_pair(type, number)};
        std::pair<std::pair<int, int>, std::pair<int, std::pair<int, int>>> mapped = {tamex_mc, mcp_output};

        detector_mapping.insert(mapped);
        
    }

    num_tamex_boards = tamex_boards.size();
    num_mcps = mcps.size();
    num_tamex_channels = tamex_channels;

    detector_map_loaded = 1;
    detector_map_file.close();
    LOG(info) << "H10MCPTwinpeaks Allocation coefficients file: " + configuration_file;
    return;
}

void TH10MCPConfiguration::ReadCalibrationCoefficients(){

    std::ifstream calibration_coeff_file (calibration_file);

    if (calibration_coeff_file.fail()) c4LOG(fatal, "Could not open H10MCP calibration coefficients file.");


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

    LOG(info) << "H10MCPTwinpeaks Calibration coefficients File: " + calibration_file;
    return; 
}






void TH10MCPConfiguration::ReadTimeshiftCoefficients()
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

