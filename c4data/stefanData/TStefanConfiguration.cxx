#include "TStefanConfiguration.h"

#include "c4Logger.h"
#include "TCutG.h"
#include "TFile.h"
#include "FairLogger.h"


#include <iostream>
#include <sstream>
#include <string>

TStefanConfiguration* TStefanConfiguration::instance = nullptr;
std::string TStefanConfiguration::mapping_file = "blank";
std::string TStefanConfiguration::calibration_file = "blank";

Double_t TStefanConfiguration::fbt = 4400; // just over 2 coarse clocks (for AIDA at least)
Double_t TStefanConfiguration::fbe = 3500000000; // (huge default until decided)


TStefanConfiguration::TStefanConfiguration()
{
    if (mapping_file != "blank") ReadConfiguration();
    else c4LOG(warn,"You must set TStefanConfiguration::SetConfigurationFile(), or things get funky... ");

    if (calibration_file != "blank") ReadCalibrationCoefficients();
 }


void TStefanConfiguration::ReadConfiguration()
{

    std::ifstream detector_map_file(mapping_file);
    std::string line;
    std::set<int> dssds;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open Stefan Map file");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal;
        int crate = -1, board = -1, channel = -1, dssd = -1, side = -1, strip = -1;

        std::pair<int, int> febex_mc;
        std::pair<int, int> stefan_ss;
        std::pair<int, std::pair<int, int>> stefan_dp;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            board = std::stoi(signal);

            iss >> channel >> dssd >> side >> strip;

            if (board < 0 || channel < 0 || dssd < 0 || side < 0 || strip < 0) continue;
            
            stefan_ss = {side, strip};
            stefan_dp = {dssd, stefan_ss};

        }
        else // some additional signal
        {
            
        }

        if (dssd > -1) dssds.insert(dssd);

        febex_mc = {board, channel};

        detector_mapping.insert(std::make_pair(febex_mc, stefan_dp));  
        
    }

    num_dssds = dssds.size();
    
    detector_mapping_loaded = 1;
    detector_map_file.close();
    return;
}


/*
Takes second order polynomials
*/
void TStefanConfiguration::ReadCalibrationCoefficients()
{

    std::ifstream cal_map_file (calibration_file);
    if (cal_map_file.fail()) c4LOG(fatal, "Could not open Germanium calibration coefficients");    

    int dssd, side, strip; // temp read variables
    double a1; // no a0, a2 for now
    
    while(!cal_map_file.eof())
    {
        if (cal_map_file.peek() == '#') cal_map_file.ignore(256,'\n');
        else
        {
            cal_map_file >> dssd >> side >> strip >> a1;

            std::pair<int, int> ss = {side, strip};
            std::pair<int, std::pair<int, int>> ds = {dssd, ss};

            // std::vector<double> cals = {a0,a1,a2};

            calibration_coeffs.insert(std::pair<std::pair<int, std::pair<int, int>>, int> {ds, a1});
            // calibration_coeffs.insert(std::pair<std::pair<int,int>,std::vector<double>>{detector_crystal,cals});
            cal_map_file.ignore(256,'\n');
        }
    }
    detector_calibrations_loaded = 1;
    cal_map_file.close();

    c4LOG(info, "Stefan Calibration File: " + calibration_file);
};