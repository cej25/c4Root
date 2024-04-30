#include "TLisaConfiguration.h"

#include "c4Logger.h"
#include "TCutG.h"
#include "TFile.h"
#include "FairLogger.h"


#include <iostream>
#include <sstream>
#include <string>

TLisaConfiguration* TLisaConfiguration::instance = nullptr;
std::string TLisaConfiguration::mapping_file = "blank";
std::string TLisaConfiguration::calibration_file = "blank";


TLisaConfiguration::TLisaConfiguration()
    :   num_layers(0)
    ,   num_detectors(0)
    ,   num_febex_boards(0)
{
    ReadMappingFile();
    //ReadCalibrationCoefficients();

}


void TLisaConfiguration::ReadMappingFile()
{   
    std::cout<<"un elefante"<<std::endl;
    std::set<int> febex_boards;
    std::set<int> layers;
    std::set<int> x_positions;
    std::set<int> y_positions;
    std::set<std::string> det_names;
    int detectors = 0;
    
    std::ifstream detector_map_file(mapping_file);
    std::string line;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open Lisa mapping file"); //return;

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal;
        std::string det_name;
        int febex_board, febex_channel, layer_id, x_pos, y_pos;
        std::pair<int, int> xy;
        std::pair<int, std::pair<int, int>> layer_xy;
        std::pair<int, std::string> layer_det_name;
        std::pair<std::pair<int,std::string>, std::pair<int,int>> layer_det_name_xy; //include det names
        std::pair<int, int> febex_bc;

        iss >> signal;
    

        if (isdigit(signal[0])) // detector
        {
            febex_board = std::stoi(signal);

            iss >> febex_channel >> layer_id >> x_pos >> y_pos >> det_name;

            // count only real layers, detectors
            layers.insert(layer_id);
            x_positions.insert(x_pos);
            y_positions.insert(y_pos);
            detectors++;

        }
        else
        {
            iss >> febex_board >> febex_channel >> layer_id >> x_pos >> y_pos >>det_name;

            if (signal == "TimeMachineU") tm_undelayed = layer_id;
            else if (signal == "TimeMachineD") tm_delayed = layer_id;
            else if (signal == "SC41L_D") sc41l_d = layer_id;
            else if (signal == "SC41R_D") sc41r_d = layer_id;

            // looking for extra signals we check if layer_id is in extra_signals
            // so use unique layer_id for anything extra
            extra_signals.insert(layer_id);
        }
        
        // count all febex boards, useful scaler monitor?
        febex_boards.insert(febex_board);

        febex_bc = std::make_pair(febex_board, febex_channel);

        xy = std::make_pair(x_pos, y_pos);
        layer_xy = std::make_pair(layer_id, xy);
        layer_det_name = std::make_pair(layer_id,det_name);
        layer_det_name_xy = std::make_pair(layer_det_name, xy);

        //detector_mapping.insert(std::make_pair(febex_bc, layer_xy));
        detector_mapping.insert(std::make_pair(febex_bc, layer_det_name_xy));

    }

    num_layers = layers.size();
    xmax = x_positions.size();
    ymax = y_positions.size();
    num_detectors = detectors;
    num_febex_boards = febex_boards.size();
    
    detector_mapping_loaded = 1;
    detector_map_file.close();

    c4LOG(info, "Lisa Configuration File: " + mapping_file);
    return;

}



void TLisaConfiguration::ReadCalibrationCoefficients()
{
    /*
    std::ifstream cal_map_file (calibration_file);
    if (cal_map_file.fail()) c4LOG(warn, "Could not open Lisa calibration coefficients"); return; 

    */
};
