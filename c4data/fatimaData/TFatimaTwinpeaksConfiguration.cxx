#include "TFatimaTwinpeaksConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

TFatimaTwinpeaksConfiguration* TFatimaTwinpeaksConfiguration::instance = nullptr;
std::string TFatimaTwinpeaksConfiguration::filepath = "fatima_alloc.txt";

TFatimaTwinpeaksConfiguration::TFatimaTwinpeaksConfiguration()
    :   num_detectors(0)
    ,   num_tamex_boards(0)
    ,   num_tamex_channels(0)
{
    ReadConfiguration();
}

void TFatimaTwinpeaksConfiguration::ReadConfiguration()
{

    std::ifstream detector_map_file(filepath);
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

    DetectorMap_loaded = 1;
    detector_map_file.close();
    return;

}

