#include "TFimpConfiguration.h"

#include "c4Logger.h"
#include "TCutG.h"
#include "TFile.h"
#include "FairLogger.h"


#include <iostream>
#include <sstream>
#include <string>

TFimpConfiguration* TFimpConfiguration::instance = nullptr;
std::string TFimpConfiguration::mapping_file = "blank";
std::string TFimpConfiguration::calibration_file = "blank";
int TFimpConfiguration::EnergyToTMin = 0;
int TFimpConfiguration::EnergyToTMax = 4e6;


TFimpConfiguration::TFimpConfiguration()
{
    if (mapping_file != "blank") ReadMappingFile();
    //ReadCalibrationCoefficients();

}


void TFimpConfiguration::ReadMappingFile()
{   
    std::set<int> fimp_T_group;
    std::set<int> fimp_B_group;
    std::set<int> fimp_L_group;
    std::set<int> fimp_R_group;
    std::set<int> channels;
    int detectors = 0;

    std::ifstream detector_map_file(mapping_file);
    std::string line;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open FIMP mapping file!");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string t_b_l_r;
        int chan, ctdc_num, ctdc_chan, cable, fimp_chan;

        iss >> chan >> ctdc_num >> ctdc_chan >> cable >> fimp_chan >> t_b_l_r;

        if (t_b_l_r == 'T') fimp_T_group.insert(fimp_chan);
        if (t_b_l_r == 'B') fimp_B_group.insert(fimp_chan);
        if (t_b_l_r == 'L') fimp_L_group.insert(fimp_chan);
        if (t_b_l_r == 'R') fimp_R_group.insert(fimp_chan);

        detectors++;

        channels.insert(chan);

        std::pair<int, int> cc = std::make_pair(cable, fimp_chan);
        std::pair<std::pair<int,int>, std::string> location = std::make_pair(cc, t_b_l_r);
        detector_mapping.insert(std::make_pair(chan, location));
    }

    num_channels = channels.size();
    num_detectors = detectors;
    num_T_group = fimp_T_group.size();
    num_B_group = fimp_B_group.size();
    num_L_group = fimp_L_group.size();
    num_R_group = fimp_R_group.size();

    detector_mapping_loaded = 1;
    detector_map_file.close();

    c4LOG(info, "FIMP Configuration File: " + mapping_file);
    return;
}



void TFimpConfiguration::ReadCalibrationCoefficients()
{
    /*
    std::ifstream cal_map_file (calibration_file);
    if (cal_map_file.fail()) c4LOG(warn, "Could not open Fimp calibration coefficients"); return; 

    */
};
