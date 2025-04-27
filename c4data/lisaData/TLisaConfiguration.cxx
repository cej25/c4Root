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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25.11.24                                     *
 ******************************************************************************/

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
std::string TLisaConfiguration::gain_matching_file_MWD = "blank";
std::string TLisaConfiguration::calibration_file = "blank";
std::string TLisaConfiguration::gate_ranges_file = "blank";
std::string TLisaConfiguration::gate_ranges_MWD_file = "blank";

//WR enable setting - X7 data = 0, S2 data = 1
bool TLisaConfiguration::wr_enable = 1;

// ::: Trace amplitude
int TLisaConfiguration::amplitude_bin = 1000;
int TLisaConfiguration::amplitude_min = 7000;
int TLisaConfiguration::amplitude_max = 16000;

// ::: Energy
int TLisaConfiguration::min_energy = 0;
int TLisaConfiguration::max_energy = 10000000;
int TLisaConfiguration::bin_energy = 900;

int TLisaConfiguration::min_energy_MWD = 0;
int TLisaConfiguration::max_energy_MWD = 10000000;
int TLisaConfiguration::bin_energy_MWD = 900;

int TLisaConfiguration::min_energy_GM = 0;
int TLisaConfiguration::max_energy_GM = 10000;
int TLisaConfiguration::bin_energy_GM = 500;

int TLisaConfiguration::min_energy_MWD_GM = 0;
int TLisaConfiguration::max_energy_MWD_GM = 10000;
int TLisaConfiguration::bin_energy_MWD_GM = 500;

// ::: WR
long TLisaConfiguration::min_wr_diff = 0;
long TLisaConfiguration::max_wr_diff = 200;
int TLisaConfiguration::bin_wr_diff = 50;
int TLisaConfiguration::min_wr_rate = 0;
int TLisaConfiguration::max_wr_rate = 200;
int TLisaConfiguration::bin_wr_rate = 50;

// ::: Traces time 
int TLisaConfiguration::min_traces = 0;
int TLisaConfiguration::max_traces = 2000;
int TLisaConfiguration::bin_traces = 2000;

// ::: Gates
int TLisaConfiguration::fMin_dE_LISA1_gate = 1070, TLisaConfiguration::fMax_dE_LISA1_gate = 1100;

int TLisaConfiguration::frun_num = 0;

// ::: Board number !!only for TraceAnalysis!!
int TLisaConfiguration::board_num = 0;     // number of boards for the file
int TLisaConfiguration::event_ana = 0;     // event to analyze for MWD trace

// ::: EVTno for En vs Evtno when WR is not availabòe
int TLisaConfiguration::start_evtno = 0;
int TLisaConfiguration::stop_evtno = 0;

// ::: Enable trace writing in histos
int TLisaConfiguration::trace_on = 1;

// ::: Set detector to analyze for gates
int TLisaConfiguration::xpos_gate = 0;
int TLisaConfiguration::ypos_gate = 0;

// ::: Set time ranges fro drift
int TLisaConfiguration::drift_min = 0;
int TLisaConfiguration::drift_max = 10;




TLisaConfiguration::TLisaConfiguration()
    :   num_layers(0)
    ,   num_detectors(0)
    ,   num_febex_boards(0)
{
    ReadMWDParameters();
    ReadMappingFile();
    ReadGMFile();
    ReadGMFileMWD();
    ReadLISAGateFebexFile();
    ReadLISAGateMWDFile();
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

        if( parameter == "Smoothing_L[ns]")                         smoothing_L = value;
        else if( parameter == "Trapez_moving_window_length[ns]")    MWD_length = value;
        else if( parameter == "Decaytime_ch0[ns]")                  decay_time[0] = value;
        else if( parameter == "Decaytime_ch1[ns]")                  decay_time[1] = value;
        else if( parameter == "Trapez_amp_calc_window_0[ns]")       MWD_amp_start = value;
        else if( parameter == "Trapez_amp_calc_window_1[ns]")       MWD_amp_stop = value;
        else if( parameter == "Sampling[ns]")                       sampling = value;
        else if( parameter == "Trapez_sample_window_0[ns]")         MWD_trace_start = value;
        else if( parameter == "Trapez_sample_window_1[ns]")         MWD_trace_stop = value;
        else if( parameter == "Trapez_baseline_window_0[ns]")       MWD_baseline_start = value;
        else if( parameter == "Trapez_baseline_window_1[ns]")       MWD_baseline_stop = value;


    
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
    std::cout<<"num layers:"<<num_layers<<std::endl;
    
    detector_mapping_loaded = 1;
    detector_map_file.close();

    //c4LOG(info, "Lisa Configuration File: " + mapping_file);
    return;

}


void TLisaConfiguration::ReadGMFile()
{       
    std::ifstream gain_matching_coeff_file (gain_matching_file);
    std::string line;

    if (gain_matching_coeff_file.fail()) c4LOG(warn, "Could not open LISA GM - calibration coefficients file.");

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

        std::cout << " Febex GM -> lxy : "<< layer_id << x_pos << y_pos << " slope " << slope << " intercept " << intercept << "\n";
    }
    
    gain_matching_loaded = 1;
    gain_matching_coeff_file.close();

    c4LOG(info, "Lisa Gain Matching File: " + gain_matching_file);
    return;

}

void TLisaConfiguration::ReadGMFileMWD()
{   
    //std::cout<<"due elefanti"<<std::endl;
    //std::set<int> layers;
    //std::set<int> x_positions;
    //std::set<int> y_positions;
    
    std::ifstream gain_matching_coeff_file_MWD (gain_matching_file_MWD);
    std::string line;

    if (gain_matching_coeff_file_MWD.fail()) c4LOG(warn, "Could not open LISA MWD GM - calibration coefficients file.");

    while (std::getline(gain_matching_coeff_file_MWD, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        int layer_id, x_pos, y_pos;
        double slope_MWD, intercept_MWD;
        std::pair<int, int> xy;
        std::pair<int, std::pair<int, int>> layer_xy;
        std::pair<double, double> gm_MWD_coeff;

        iss >> layer_id >> x_pos >> y_pos >> slope_MWD >> intercept_MWD;

        gm_MWD_coeff = std::make_pair(slope_MWD, intercept_MWD);

        xy = std::make_pair(x_pos, y_pos);
        layer_xy = std::make_pair(layer_id, xy);

        gain_matching_MWD_coeffs.insert(std::make_pair(layer_xy, gm_MWD_coeff));

        std::cout << " MWD GM -> lxy : "<< layer_id << x_pos << y_pos << " slope " << slope_MWD << " intercept " << intercept_MWD << "\n";
    }
    
    gain_matching_MWD_loaded = 1;
    gain_matching_coeff_file_MWD.close();

    c4LOG(info, "Lisa Gain Matching MWD File: " + gain_matching_file_MWD);
    return;

}

void TLisaConfiguration::ReadLISAGateFebexFile()
{       
    std::ifstream gate_ranges(gate_ranges_file);
    std::string line;

    if (gate_ranges.fail()) c4LOG(warn, "Could not open LISA Febex Gates file");

    while (std::getline(gate_ranges, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        int layer_id;
        double gate_min, gate_max;
        std::pair<double, double> gate_min_max;

        iss >> layer_id >> gate_min >> gate_max;

        gate_min_max = std::make_pair(gate_min, gate_max);

        gate_LISA_febex.insert(std::make_pair(layer_id, gate_min_max));

        std::cout << " Layer ID : "<< layer_id << " Gate Min : " << gate_min << " Gate Max : " << gate_max << "\n";
    }
    
    gates_febex_loaded = 1;
    gate_ranges.close();

    c4LOG(info, "Lisa Febex Gates: " + gate_ranges_file);
    return;
}

void TLisaConfiguration::ReadLISAGateMWDFile()
{       
    std::ifstream gate_ranges_MWD(gate_ranges_MWD_file);
    std::string line;

    if (gate_ranges_MWD.fail()) c4LOG(warn, "Could not open LISA MWD Gates file");

    while (std::getline(gate_ranges_MWD, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        int layer_id;
        double gate_MWD_min, gate_MWD_max;
        std::pair<double, double> gate_MWD_min_max;

        iss >> layer_id >> gate_MWD_min >> gate_MWD_max;

        gate_MWD_min_max = std::make_pair(gate_MWD_min, gate_MWD_max);

        gate_LISA_MWD.insert(std::make_pair(layer_id, gate_MWD_min_max));

        std::cout << " Layer ID : "<< layer_id << " Gate MWD Min : " << gate_MWD_min << " Gate MWD Max : " << gate_MWD_max << "\n";
    }
    
    gates_MWD_loaded = 1;
    gate_ranges_MWD.close();

    c4LOG(info, "Lisa MWD Gates: " + gate_ranges_MWD_file);
    return;
}


void TLisaConfiguration::ReadCalibrationCoefficients()
{
    /*
    std::ifstream cal_map_file (calibration_file);
    if (cal_map_file.fail()) c4LOG(warn, "Could not open Lisa calibration coefficients"); return; 

    */
};
