#include "TLisaConfiguration.h"
#include "TExperimentConfiguration.h"

#include "c4Logger.h"
#include "TCutG.h"
#include "TFile.h"
#include "FairLogger.h"


#include <iostream>
#include <sstream>
#include <string>

TLisaConfiguration* TLisaConfiguration::instance = nullptr;

std::string TLisaConfiguration::MWD_file = "blank";
std::string TLisaConfiguration::mapping_file = "blank";
std::string TLisaConfiguration::gain_matching_file = "blank";
std::string TLisaConfiguration::calibration_file = "blank";

//WR enable setting - X7 data = 0, S2 data = 1
bool TLisaConfiguration::wr_enable = 1;

// ::: Trace amplitude
int TLisaConfiguration::AmplitudeMin = 7000;
int TLisaConfiguration::AmplitudeMax = 16000;

// ::: Energy
int TLisaConfiguration::min_energy = 0;
int TLisaConfiguration::max_energy = 10000000;
int TLisaConfiguration::bin_energy = 900;

int TLisaConfiguration::min_energy_GM = 0;
int TLisaConfiguration::max_energy_GM = 10000;
int TLisaConfiguration::bin_energy_GM = 500;

// ::: WR
int TLisaConfiguration::min_wr_diff = 0;
int TLisaConfiguration::max_wr_diff = 200;
int TLisaConfiguration::bin_wr_diff = 50;

// ::: Traces time 
int TLisaConfiguration::min_traces = 0;
int TLisaConfiguration::max_traces = 2000;
int TLisaConfiguration::bin_traces = 900;

// ::: Gates
int TLisaConfiguration::fMin_dE_LISA1_gate = 1070, TLisaConfiguration::fMax_dE_LISA1_gate = 1100;

int TLisaConfiguration::frun_num = 0;

// ::: Board number !!only for TraceAnalysis!!
int TLisaConfiguration:: board_num = 0;     // number of boards for the file
int TLisaConfiguration:: event_ana = 0;     // event to analyze for MWD trace


TLisaConfiguration::TLisaConfiguration()
    :   num_layers(0)
    ,   num_detectors(0)
    ,   num_febex_boards(0)
{
    ReadMWDParameters();
    ReadMappingFile();
    ReadGMFile();
    //ReadCalibrationCoefficients();

}


void TLisaConfiguration::ReadMWDParameters()
{       
    std::ifstream MWD_parameters_file(MWD_file);
    std::string line;

    if (MWD_parameters_file.fail()) c4LOG(warn, "Could not open LISA MWD parameters file.");

    std::cout << "::: Parameters MDW ::: " << "\n";        
    while (std::getline(MWD_parameters_file, line))
    {
        if (line.empty() || line[0] == '#') continue; 
        
        std::istringstream iss(line);
        std::string parameter;
        double value;

        if (!(iss >> parameter >> value)) 
        {
            c4LOG(warn, "Malformed line in MWD parameters file: " + line);
            continue;
        }

        //iss >> parameter >> value;

        if( parameter == "test_constant1") test_const1 = value;
        else if( parameter == "test_constant2") test_const2 = value;
        else if( parameter == "test_constant3") test_const3 = value;
        else if( parameter == "test_constant4") test_const4 = value;
    
        std::cout << parameter << " : " << value <<  "\n";
    }
    
    MWD_parameters_loaded = 1;
    MWD_parameters_file.close();

    c4LOG(info, "Lisa MWD Parameters: " + MWD_file);
    return;

}

void TLisaConfiguration::ReadMappingFile()
{   
    std::set<int> febex_boards;
    std::set<int> layers;
    std::set<int> x_positions;
    std::set<int> y_positions;
    std::set<std::string> det_names;
    int detectors = 0;
    
    std::ifstream detector_map_file(mapping_file);
    std::string line;

    if (detector_map_file.fail()) c4LOG(warn, "Could not open Lisa mapping file"); //return;

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
            //std::cout << " Mapping : l "<< layer_id << " x " << x_pos << " y " << y_pos << "\n";


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
    //std::cout<<"num layers:"<<num_layers<<std::endl;
    
    detector_mapping_loaded = 1;
    detector_map_file.close();

    c4LOG(info, "Lisa Configuration File: " + mapping_file);
    return;

}


void TLisaConfiguration::ReadGMFile()
{   
    //std::cout<<"due elefanti"<<std::endl;
    //std::set<int> layers;
    //std::set<int> x_positions;
    //std::set<int> y_positions;
    
    std::ifstream gain_matching_coeff_file (gain_matching_file);
    std::string line;

    if (gain_matching_coeff_file.fail()) c4LOG(warn, "Could not open LISA calibration coefficients file.");

    while (std::getline(gain_matching_coeff_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        int layer_id, x_pos, y_pos;
        double slope, intercept;
        std::pair<int, int> xy;
        std::pair<int, std::pair<int, int>> layer_xy;
        std::pair<double, double> gm_coeff;

        iss >> layer_id >> x_pos >> y_pos >> slope >> intercept;

        gm_coeff = std::make_pair(slope, intercept);

        xy = std::make_pair(x_pos, y_pos);
        layer_xy = std::make_pair(layer_id, xy);

        gain_matching_coeffs.insert(std::make_pair(layer_xy, gm_coeff));

        std::cout << " l "<< layer_id << " x " << x_pos << " y " << y_pos << " slope " << slope << " intercept " << intercept << "\n";
    }
    
    gain_matching_loaded = 1;
    gain_matching_coeff_file.close();

    c4LOG(info, "Lisa Gain Matching File: " + gain_matching_file);
    return;

}


void TLisaConfiguration::ReadCalibrationCoefficients()
{
    /*
    std::ifstream cal_map_file (calibration_file);
    if (cal_map_file.fail()) c4LOG(warn, "Could not open Lisa calibration coefficients"); return; 

    */
};
