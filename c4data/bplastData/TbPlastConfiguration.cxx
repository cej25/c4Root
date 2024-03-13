#include "TbPlastConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

TbPlastConfiguration* TbPlastConfiguration::instance = nullptr;
std::string TbPlastConfiguration::filepath = "bplast_alloc.txt";

TbPlastConfiguration::TbPlastConfiguration()
    :   num_detectors(0)
    ,   num_up_detectors(0)
    ,   num_down_detectors(0)
    ,   num_top_detectors(0)
    ,   num_bottom_detectors(0)
    ,   num_left_detectors(0)
    ,   num_right_detectors(0)
    ,   num_tamex_boards(0)
{
    ReadConfiguration();
}

void TbPlastConfiguration::ReadConfiguration()
{
    std::ifstream detector_map_file(filepath);
    std::string line;
    std::set<int> tamex_boards;
    std::set<int> detector_ids;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open bPlast Twinpeaks allocation");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal;
        int tamex_board, tamex_channel, detector_id;
        std::string stream, orientation;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            tamex_board = std::stoi(signal);

            iss >> tamex_channel >> detector_id >> stream >> orientation;

            // stream
            if (stream == "U") up_detectors.insert(detector_id);
            else if (stream == "D") down_detectors.insert(detector_id);

            // orientation
            if (orientation == "T") top_detectors.insert(detector_id);
            else if (orientation == "B") bottom_detectors.insert(detector_id);
            else if (orientation == "L") left_detectors.insert(detector_id);
            else if (orientation == "R") right_detectors.insert(detector_id);
        }
        else // some additional signal
        {
            iss >> tamex_board >> tamex_channel >> detector_id >> stream >> orientation;

            if (signal == "TimeMachineU") tm_undelayed = detector_id;
            else if (signal == "TimeMachineD") tm_delayed = detector_id;
            else if (signal == "SC41L_D") sc41l_d = detector_id;
            else if (signal == "SC41R_D") sc41r_d = detector_id;
            else if (signal == "FATIMA_ACCEPT") fatima_accept = detector_id;
            else if (signal == "FATIMA_FREE") fatima_free = detector_id;

            extra_signals.insert(detector_id);
        }

        if (tamex_board > -1) tamex_boards.insert(tamex_board);
        if (detector_id > -1) detector_ids.insert(detector_id);

        std::pair<int, int> tamex_mc = {tamex_board, tamex_channel};
        std::pair<std::string, std::string> position = {stream, orientation};

        detector_mapping.insert(std::make_pair(tamex_mc, std::make_pair(detector_id, position)));

    }

    num_tamex_boards = tamex_boards.size();
    num_detectors = detector_ids.size();
    num_up_detectors = up_detectors.size();
    num_down_detectors = down_detectors.size();
    num_top_detectors = top_detectors.size();
    num_bottom_detectors = bottom_detectors.size();
    num_left_detectors = left_detectors.size();
    num_right_detectors = right_detectors.size();

    DetectorMap_loaded = 1;
    detector_map_file.close();
    return;
}
