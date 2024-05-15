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
    ReadMappingFile();
    //ReadCalibrationCoefficients();

}


void TFimpConfiguration::ReadMappingFile()
{   
    std::set<int> fimp_e_groups;
    std::set<int> fimp_t_groups;
    std::set<int> ctdc_channels;
    int detectors = 0;

    std::ifstream detector_map_file(mapping_file);
    std::string line;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open FIMP mapping file!");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal, e_or_t;
        int ctdc_chan, group, fimp_chan;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            ctdc_chan = std::stoi(signal);

            iss >> group >> fimp_chan >> e_or_t;

            if (e_or_t == 'E') fimp_e_groups.insert(group);
            else if (e_or_t == 'T') fimp_t_groups.insert(group);

            detectors++;

        }
        else
        {
            iss >> ctdc_chan >> group >> fimp_chan >> e_or_t;

            if (signal == "SC41L_D") sc41l_d = group;
            else if (signal == "SC41R_D") sc41r_d = group;

            extra_signals.insert(group);
        }

        ctdc_channels.insert(ctdc_chan);

        std::pair<int, int> gc = std::make_pair(group, fimp_chan);
        std::pair<std::pair<int,int>, std::string> gc_type = std::make_pair(gc, e_or_t);
        detector_mapping.insert(std::make_pair(ctdc_chan, gc_type));
    }

    num_ctdc_channels = ctdc_channels.size();
    num_detectors = detectors;
    num_e_groups = fimp_e_groups.size();
    num_t_groups = fimp_t_groups.size();

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
