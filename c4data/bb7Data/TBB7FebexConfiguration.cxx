#include "TBB7FebexConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

TBB7FebexConfiguration* TBB7FebexConfiguration::instance = nullptr;
std::string TBB7FebexConfiguration::mapping_file = "blank";

uint32_t TBB7FebexConfiguration::implantThreshold = 5000;
uint32_t TBB7FebexConfiguration::decayThreshold = 100;

TBB7FebexConfiguration::TBB7FebexConfiguration()
    :   num_dssds(0)
{
    ReadConfiguration();
}

void TBB7FebexConfiguration::ReadConfiguration()
{

    std::ifstream detector_map_file(mapping_file);
    std::string line;
    std::set<int> dssds;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open BB7_Detector_Map file");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal;
        int board = -1, channel = -1, dssd = -1, side = -1, strip = -1;

        std::pair<int, int> febex_mc;
        std::pair<int, int> bb7_ss;
        std::pair<int, std::pair<int, int>> bb7_dp;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            board = std::stoi(signal);

            iss >> channel >> dssd >> side >> strip;

            if (board < 0 || channel < 0 || dssd < 0 || side < 0 || strip < 0) continue;
            
            bb7_ss = {side, strip};
            bb7_dp = {dssd, bb7_ss};

        }
        else // some additional signal
        {
            
        }

        if (dssd > -1) dssds.insert(dssd);

        febex_mc = {board, channel};

        detector_mapping.insert(std::pair<std::pair<int, int>, std::pair<int, std::pair<int,int>>> {febex_mc, bb7_dp});  
        
    }

    num_dssds = dssds.size();
    
    detector_map_loaded = 1;
    detector_map_file.close();
    return;
}
