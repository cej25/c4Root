#include "TBB7VmeConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

TBB7VmeConfiguration* TBB7VmeConfiguration::instance = nullptr;
std::string TBB7VmeConfiguration::configuration_file = "blank";
std::string TBB7VmeConfiguration::residuals_file = "blank";
std::string TBB7VmeConfiguration::calibration_file = "blank";

uint32_t TBB7VmeConfiguration::implantThreshold = 5000;

TBB7VmeConfiguration::TBB7VmeConfiguration()
    :   num_detectors(0)
    ,   num_sides(0)
    ,   num_strips(0)
    ,   num_v7x5_boards(0)
{
    ReadConfiguration();
    if (residuals_file != "blank") ReadResiduals();
    // ReadCalibrationCoefficients();
}

void TBB7VmeConfiguration::ReadConfiguration()
{

    std::ifstream detector_map_file(configuration_file);
    std::string line;
    std::set<int> v7x5_boards;
    std::set<int> detectors;
    std::set<int> sides;
    std::set<int> strips; // per side

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open BB7_Detector_Map file");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal;
        int v7x5_board, v7x5_channel, side, strip;

        std::pair<int, int> v7x5_mc;
        std::pair<int, int> bb7_ss;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            v7x5_board = std::stoi(signal);

            iss >> v7x5_channel >> side >> strip;

            if (side < 0 || strip < 0 || v7x5_channel < 0 || v7x5_board < 0) continue;
            
            bb7_ss = {side, strip};

        }
        else // some additional signal
        {
            // CEJ: for now we read residuals separately, 
            // so a different module, a different mapping

            /*iss >> v7x5_board >> v7x5_channel >> side >> strip;

            bb7_ss = {side, strip};

            if (signal == "TimeMachineU") tm_undelayed = bb7_ss;
            else if (signal == "TimeMachineD") tm_delayed = bb7_ss;
            else if (signal == "SC41L_D") sc41l_d = bb7_ss;
            else if (signal == "SC41R_D") sc41r_d = bb7_ss; */
            /*else if (signal == "FRS_ACCEPT") frs_accept = bb7_ss;
            else if (signal == "BPLAST_ACCEPT") bplast_accept = bb7_ss;
            else if (signal == "BPLAST_FREE") bplast_free = bb7_ss;*/

            /*extra_signals.insert(bb7_ss);*/
        }

        if (v7x5_board > -1) v7x5_boards.insert(v7x5_board);
        if (side > -1) sides.insert(side);
        if (strip > -1) strips.insert(strip);

        v7x5_mc = {v7x5_board, v7x5_channel};

        detector_mapping.insert(std::pair<std::pair<int, int>, std::pair<int, int>> {v7x5_mc, bb7_ss});  
        
    }

    num_v7x5_boards = v7x5_boards.size();
    num_sides = sides.size();
    num_strips = strips.size();
    
    detector_map_loaded = 1;
    detector_map_file.close();
    return;
}


void TBB7VmeConfiguration::ReadResiduals()
{
    std::ifstream file(residuals_file);
    std::string line;

    if (file.fail()) c4LOG(fatal, "Could not open BB7_Residuals file");

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal;
        int residual, v1290_board, v1290_channel;
        std::pair<int, int> v1290_mc;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            // ignore! this is a residuals file!

        }
        else
        {
            iss >> residual >> v1290_board >> v1290_channel;

            v1290_mc = {v1290_board, v1290_channel};

            if (signal == "TimeMachineU") tm_undelayed = residual;
            else if (signal == "TimeMachineD") tm_delayed = residual;
            else if (signal == "SC41L_D") sc41l_d = residual;
            else if (signal == "SC41R_D") sc41r_d = residual;

        }

        residual_mapping.insert(std::make_pair(v1290_mc, residual));  
        
    }

    residuals_loaded = 1;
    file.close();
    return;
}