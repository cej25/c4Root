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

#include "TBGOTwinpeaksConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

TBGOTwinpeaksConfiguration* TBGOTwinpeaksConfiguration::instance = nullptr;
std::string TBGOTwinpeaksConfiguration::configuration_file = "blank";
//std::string TBGOTwinpeaksConfiguration::calibration_file = "blank";
int TBGOTwinpeaksConfiguration::window = 2000;
int TBGOTwinpeaksConfiguration::offset = 0;


TBGOTwinpeaksConfiguration::TBGOTwinpeaksConfiguration()
    :   num_detectors(0)
    ,   num_tamex_boards(0)
    ,   num_tamex_channels(0)
{
    if (configuration_file != "blank") ReadConfiguration();
    //if (calibration_file != "blank") ReadCalibrationCoefficients();
}

void TBGOTwinpeaksConfiguration::ReadConfiguration()
{

    std::ifstream detector_map_file(configuration_file);
    std::string line;
    std::set<int> tamex_boards;
    std::set<int> detectors;
    int tamex_channels = 0;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open BGO Twinpeaks allocation file");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal;
        int tamex_board, tamex_channel, detector, crystal;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            tamex_board = std::stoi(signal);

            iss >> tamex_channel >> detector >> crystal;

        }
        else // some additional signal
        {
            iss >> tamex_board >> tamex_channel >> detector >> crystal;

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
        if (detector > -1) {
            detectors.insert(detector);
        }
        tamex_channels++;

        std::pair<int, int> tamex_mc = {tamex_board, tamex_channel};
        std::pair<int, int> fc = {detector, crystal};

        detector_mapping.insert(std::pair<std::pair<int, int>, std::pair<int,int>> {tamex_mc, fc});  
        
    }

    num_tamex_boards = tamex_boards.size();
    num_detectors = detectors.size();
    num_tamex_channels = tamex_channels;

    detector_map_loaded = 1;
    detector_map_file.close();
    return;
}


/*
void TBGOTwinpeaksConfiguration::ReadCalibrationCoefficients(){

    std::ifstream calibration_coeff_file (calibration_file);

    if (calibration_coeff_file.fail()) c4LOG(fatal, "Could not open BGO calibration coefficients file.");


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
    return; 
}
*/