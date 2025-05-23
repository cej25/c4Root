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
 *                               C.E. Jones                                   *
 *                                06.05.25                                    *
 ******************************************************************************/

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
        int crate = -1, board = -1, channel = -1, dssd = -1, side = -1, strip = -1;

        std::pair<int, int> febex_mc;
        std::pair<int, std::pair<int, int>> febex_cmc;
        std::pair<int, int> bb7_ss;
        std::pair<int, std::pair<int, int>> bb7_dp;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            crate = std::stoi(signal);

            iss >> board >> channel >> dssd >> side >> strip;

            if (crate < 0 || board < 0 || channel < 0 || dssd < 0 || side < 0 || strip < 0) continue;
            
            bb7_ss = {side, strip};
            bb7_dp = {dssd, bb7_ss};

        }
        else // some additional signal
        {
            
        }

        if (dssd > -1) dssds.insert(dssd);

        febex_mc = {board, channel};
        febex_cmc = {crate, febex_mc};

        detector_mapping.insert(std::pair<std::pair<int, std::pair<int, int>>, std::pair<int, std::pair<int,int>>> {febex_cmc, bb7_dp});  
        
    }

    num_dssds = dssds.size();
    
    detector_map_loaded = 1;
    detector_map_file.close();
    return;
}
