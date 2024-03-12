#include "TGermaniumConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>

TGermaniumConfiguration* TGermaniumConfiguration::instance = nullptr;
std::string TGermaniumConfiguration::filepath = "Germanium_Detector_Map.txt";

TGermaniumConfiguration::TGermaniumConfiguration()
:   num_detectors(0)
,   num_crystals(0)
,   num_febex_boards(0)
{
    ReadConfiguration();
}

void TGermaniumConfiguration::ReadConfiguration()
{   
    std::set<int> febex_boards;
    std::set<int> detector_ids;
    std::set<int> crystals_per;
    int crystals = 0;

    std::ifstream detector_map_file(filepath);
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

            extra_signals.insert(detector_id);
        }

        if (febex_board > -1) febex_boards.insert(febex_board);
        if (detector_id > -1) detector_ids.insert(detector_id);
        if (detector_id > -1) crystals_per.insert(crystal_id);
        crystals++;

        std::pair<int, int> febex_mc = {febex_board, febex_channel};
        std::pair<int, int> ge_cd = {detector_id, crystal_id};

        detector_mapping.insert(std::pair<std::pair<int, int>, std::pair<int, int>> {febex_mc, ge_cd});
    
    }

    num_detectors = detector_ids.size();
    crystals_per_det = crystals_per.size();
    num_crystals = crystals;
    num_febex_boards = febex_boards.size();

    DetectorMap_loaded = 1;
    detector_map_file.close();
    return;

}

