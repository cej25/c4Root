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

#include "TLYSOConfiguration.h"

#include "c4Logger.h"
#include "TCutG.h"
#include "TFile.h"
#include "FairLogger.h"


#include <iostream>
#include <sstream>
#include <string>

TLYSOConfiguration* TLYSOConfiguration::instance = nullptr;
std::string TLYSOConfiguration::configuration_file = "blank";

TLYSOConfiguration::TLYSOConfiguration()
{
    if (configuration_file != "blank") ReadConfiguration();
    else c4LOG(fatal,"You must set TLYSOConfiguration::SetConfigurationFile()!!");
 }


void TLYSOConfiguration::ReadConfiguration()
{   

    std::ifstream detector_map_file(configuration_file);
    std::string line;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open LYSO Detector Configuration ");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string flag;
        int boardid, chid, anodeid;
        double a0, a1, a2, threshold;

        iss >> boardid >> chid >> anodeid >> flag >> a0 >> a1 >> a2 >> threshold;


        int type = -1;
        if (flag == 'x'){
            type = 0;
        }else if (flag == 'y'){
            type = 1;
        }else{
            type = -1;
        }
        c4LOG(info, Form("bid = %i, chid = %i, type = %i, anodeid = %i, a0 = %f, a1 = %f, a2 = %f",boardid,chid, type,anodeid,a0,a1,a2));
        std::pair<int, int> bcd = {boardid, chid};
        std::vector<double> calib = {a0,a1,a2};
        std::pair<int, int> mapped_ch = {type, anodeid};

        detector_mapping.insert(std::pair<std::pair<int, int>, std::pair<int, int>> {bcd, mapped_ch});
        calibration_coeffs.insert(std::pair<std::pair<int,int>,std::vector<double>> {bcd, calib});
        thresholds.insert(std::pair<std::pair<int,int>,double> {bcd, threshold});
    
    }


    config_loaded = 1;
    detector_map_file.close();

    LOG(info) << "Germanium Configuration File: " + configuration_file;
    return;

}


