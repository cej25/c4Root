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

#include "TAgataConfiguration.h"

#include "c4Logger.h"
#include "TCutG.h"
#include "TFile.h"
#include "FairLogger.h"


#include <iostream>
#include <sstream>
#include <string>

TAgataConfiguration* TAgataConfiguration::instance = nullptr;
std::string TAgataConfiguration::configuration_file = "blank";

TAgataConfiguration::TAgataConfiguration()
{
    if (configuration_file != "blank") ReadConfiguration();
    else c4LOG(fatal,"You must set TAgataConfiguration::SetConfigurationFile()!!");
 }


void TAgataConfiguration::ReadConfiguration()
{   

    std::ifstream detector_map_file(configuration_file);
    std::string line;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open AGATA Detector Configuration ");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        char sec;
        int boardid, chid, seg;
        double a0, a1, a2, threshold, baseline;

        iss >> boardid >> chid >> seg >> sec >> a0 >> a1 >> a2 >> threshold >> baseline;

        if (seg == -1 ) continue;
        
        c4LOG(info, Form("boardid  = %i chid  = %i seg  = %i sec  = %c a0  = %f a1  = %f a2  = %f ",boardid,chid,seg,sec,a0,a1,a2));
        
        std::pair<int, int> bcd = {boardid, chid};
        std::vector<double> calib = {a0,a1,a2};
        std::pair<char, int> mapped_ch = {sec, seg}; // A-F + S, 1-6

        detector_mapping.insert(std::pair<std::pair<char, int>, std::pair<int, int>> {bcd, mapped_ch});
        calibration_coeffs.insert(std::pair<std::pair<int,int>,std::vector<double>> {bcd, calib});    
    }


    config_loaded = 1;
    detector_map_file.close();

    LOG(info) << "AGATA Configuration File: " + configuration_file;
    return;

}


