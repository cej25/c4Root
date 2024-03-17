#include "TFatimaTwinpeaksConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

TFatimaTwinpeaksConfiguration* TFatimaTwinpeaksConfiguration::instance = nullptr;
std::string TFatimaTwinpeaksConfiguration::configuration_file = "blank";
std::string TFatimaTwinpeaksConfiguration::calibration_file = "blank";

TFatimaTwinpeaksConfiguration::TFatimaTwinpeaksConfiguration()
    :   num_detectors(0)
    ,   num_tamex_boards(0)
    ,   num_tamex_channels(0)
{
    if (configuration_file != "blank") ReadConfiguration();
    if (calibration_file != "blank") ReadCalibrationCoefficients();
}

void TFatimaTwinpeaksConfiguration::ReadConfiguration()
{

    std::ifstream detector_map_file(configuration_file);
    std::string line;
    std::set<int> tamex_boards;
    std::set<int> detectors;
    int tamex_channels = 0;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open Fatima Twinpeaks allocation file");

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
    return; 
}