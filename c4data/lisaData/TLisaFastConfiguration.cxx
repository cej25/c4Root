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
 *                        E.Gandolfo & C.E. Jones                             *
 *                                   08.26                                    *
 ******************************************************************************/

#include "TLisaFastConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>
#include "TFile.h"
#include <fstream>
#include <algorithm>

TLisaFastConfiguration* TLisaFastConfiguration::instance = nullptr;
std::string TLisaFastConfiguration::configuration_file = "blank";
std::string TLisaFastConfiguration::calibration_file = "blank";
std::string TLisaFastConfiguration::timeshift_calibration_file = "blank";
std::string TLisaFastConfiguration::promptflash_cut_file = "blank";
std::string TLisaFastConfiguration::gain_shifts_file = "blank";


// Ranges for histos

int TLisaFastConfiguration::slowToT_bin = 500;
int TLisaFastConfiguration::slowToT_min = 0;
int TLisaFastConfiguration::slowToT_max = 1000;


int TLisaFastConfiguration::fastToT_bin = 500;
int TLisaFastConfiguration::fastToT_min = 300;
int TLisaFastConfiguration::fastToT_max = 800;


int TLisaFastConfiguration::energy_bin = 500;
int TLisaFastConfiguration::energy_min = 0;
int TLisaFastConfiguration::energy_max = 1000;


int TLisaFastConfiguration::dt_bin = 1000;
int TLisaFastConfiguration::dt_min = -200;
int TLisaFastConfiguration::dt_max = 200;

int TLisaFastConfiguration::en_gate_width = 20;


TLisaFastConfiguration::TLisaFastConfiguration()
    :   num_labr_detectors(0)
    ,   num_diamond_detectors(0)
    ,   num_diamond_layers(0)
    ,   xmax(0)
    ,   ymax(0)
    ,   num_tamex_boards(0)
    ,   num_tamex_channels(0)
{
    if (configuration_file != "blank") ReadConfiguration();
    if (calibration_file != "blank") ReadCalibrationCoefficients();
    if (timeshift_calibration_file != "blank") ReadTimeshiftCoefficients();
    if (promptflash_cut_file != "blank") ReadPromptFlashCut();
    if (gain_shifts_file != "blank") ReadGainShifts();
}

TLisaFastConfiguration::~TLisaFastConfiguration()
{
    std::set<GainShift*> deleted;

    for (auto& [bc, gain] : gain_shifts)
    {
        if (gain != nullptr && deleted.insert(gain).second)
        {
            delete gain;
        }
    }

    gain_shifts.clear();

    delete prompt_flash_cut;
    prompt_flash_cut = nullptr;
}

// One mapping file with two optional sections: [LaBr] and [Diamond]
void TLisaFastConfiguration::ReadConfiguration()
{

    std::ifstream detector_map_file(configuration_file);
    std::string line;
    std::set<int> tamex_boards;
    //std::set<int> detectors;
    int tamex_channels = 0;

    // LaBr
    std::set<int> labr_detectors;
    // Diamond
    std::set<int> layers, x_positions, y_positions;
    int diamond_detectors = 0;

    if (detector_map_file.fail()) c4LOG(fatal, "Could not open LisaFast mapping file");

    enum class Section { None, LaBr, Diamond };
    Section section = Section::None;
    int line_nr = 0;


    while (std::getline(detector_map_file, line))
    {
        
        line_nr++;
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == std::string::npos || line[first] == '#') continue;
        line = line.substr(first);     

        //Find initial part of [LaBr] or [Diamond]
        if (line[0] == '[')
        {
            std::string tag = line.substr(0, line.find(']') + 1);
            std::transform(tag.begin(), tag.end(), tag.begin(), ::tolower);

            if (tag == "[labr]")         section = Section::LaBr;
            else if (tag == "[diamond]") section = Section::Diamond;
            else c4LOG(fatal, "Unknown section " << tag << " in LisaFast mapping, line " << line_nr);
            continue;
        }
        
        if (section == Section::None) c4LOG(fatal, "Data before any [LaBr]/[Diamond] section in LisaFast mapping, line " << line_nr);
   
        
        std::istringstream iss(line);

        // :::::::::::::::: LaBr ::::::::::::::::
        if (section == Section::LaBr)
        {
            std::string signal;
            int tamex_board, tamex_channel, detector;
            iss >> signal;

            if (isdigit(signal[0])) // detector
            {
                tamex_board = std::stoi(signal);

                iss >> tamex_channel >> detector;

            }
            else // some additional signal
            {
                iss >> tamex_board >> tamex_channel >> detector;
                extra_signals.insert(detector);
            }

            if (iss.fail()) c4LOG(fatal, "Bad [LaBr] line " << line_nr << ": " << line);

            if (tamex_board > -1) tamex_boards.insert(tamex_board);
            if (detector > -1) labr_detectors.insert(detector);
            tamex_channels++;

            labr_mapping.insert({{tamex_board, tamex_channel}, detector});

        }    
        // :::::::::::::::: Diamond ::::::::::::::::   
        else
        {
            int tamex_board, tamex_channel, layer_id, x_pos, y_pos;
            float thickness;
            std::string det_name, det_sn;

            iss >> tamex_board >> tamex_channel >> layer_id >> x_pos >> y_pos
                >> thickness >> det_name >> det_sn;

            if (iss.fail()) c4LOG(fatal, "Bad [Diamond] line " << line_nr << ": " << line);

            std::pair<int,int> tamex_bc = {tamex_board, tamex_channel};
            if (diamond_mapping.count(tamex_bc))
                c4LOG(fatal, "Duplicate diamond TAMEX (" << tamex_board << "," << tamex_channel << "), line " << line_nr);

            layers.insert(layer_id);
            x_positions.insert(x_pos);
            y_positions.insert(y_pos);
            diamond_detectors++;

            tamex_boards.insert(tamex_board);
            tamex_channels++;

            std::pair<int,int> xy = {x_pos, y_pos};
            std::pair<int, std::pair<int,int>> layer_xy = {layer_id, xy};
            std::pair<float, std::pair<std::string,std::string>> info = {thickness, {det_name, det_sn}};

            diamond_mapping.insert({tamex_bc, {layer_xy, info}});      
        }

    }

    num_tamex_boards      = tamex_boards.size();
    num_tamex_channels    = tamex_channels;

    num_labr_detectors    = labr_detectors.size();

    num_diamond_detectors = diamond_detectors;
    num_diamond_layers    = layers.size();
    xmax                  = x_positions.size();
    ymax                  = y_positions.size();

    labr_map_loaded    = !labr_mapping.empty();
    diamond_map_loaded = !diamond_mapping.empty();

    detector_map_file.close();

    if (!labr_map_loaded && !diamond_map_loaded)
        c4LOG(warn, "LisaFast mapping file has no LaBr and no Diamond entries: " + configuration_file);
    else if (!labr_map_loaded)
        c4LOG(info, "LisaFast mapping: no LaBr entries, running with Diamond only");
    else if (!diamond_map_loaded)
        c4LOG(info, "LisaFast mapping: no Diamond entries, running with LaBr only");

    c4LOG(info, "LisaFast Mapping file: " + configuration_file);
    c4LOG(info, "LaBr detectors: " << num_labr_detectors
                << ", Diamond detectors: " << num_diamond_detectors
                << ", Diamond layers: " << num_diamond_layers
                << ", x: " << xmax << ", y: " << ymax);
    
    return;
}

// Energy calibration from slowToT to keV
void TLisaFastConfiguration::ReadCalibrationCoefficients()
{
    std::ifstream calibration_coeff_file(calibration_file);

    if (calibration_coeff_file.fail())
        c4LOG(fatal, "Could not open LisaFast calibration coefficients file.");

    std::string line;
    std::string section;

    while (std::getline(calibration_coeff_file, line))
    {
        // Skip empty lines
        if (line.empty())
            continue;

        // Skip comments
        if (line[0] == '#')
            continue;

        // Check section
        if (line == "[LaBr]")
        {
            section = "LaBr";
            continue;
        }

        if (line == "[Diamond]")
        {
            section = "Diamond";
            continue;
        }

        std::stringstream line_ss(line);

        if (section == "LaBr")
        {
            int detector_id;
            double a0, a1, a2, a3;

            line_ss >> detector_id >> a0 >> a1 >> a2 >> a3;

            if (line_ss.fail())
            {
                c4LOG(error, "Error reading LaBr calibration line: " + line);
                continue;
            }

            labr_calibration_coeffs[detector_id] =
                {a0, a1, a2, a3};
        }
        else if (section == "Diamond")
        {
            int layer;
            int x;
            int y;
            double a0, a1, a2, a3;

            line_ss >> layer >> x >> y >> a0 >> a1 >> a2 >> a3;

            if (line_ss.fail())
            {
                c4LOG(error, "Error reading Diamond calibration line: " + line);
                continue;
            }

            auto key = std::make_tuple(layer, x, y);

            diamond_calibration_coeffs[key] =
                {a0, a1, a2, a3};
        }
    }

    detector_calibrations_loaded = true;

    calibration_coeff_file.close();

    LOG(info) << "LisaFast Calibration coefficients File: "
              << calibration_file;

    LOG(info) << "Loaded "
              << labr_calibration_coeffs.size()
              << " LaBr calibration coefficients.";

    LOG(info) << "Loaded "
              << diamond_calibration_coeffs.size()
              << " Diamond calibration coefficients.";

    return;
}
// void TLisaFastConfiguration::ReadCalibrationCoefficients(){

//     std::ifstream calibration_coeff_file (calibration_file);

//     if (calibration_coeff_file.fail()) c4LOG(fatal, "Could not open LisaFast calibration coefficients file.");


//     int rdetector_id; // temp read variables
    
//     //assumes the first line in the file is num-modules used
//     while(!calibration_coeff_file.eof()){
//         if(calibration_coeff_file.peek()=='#') calibration_coeff_file.ignore(256,'\n');
//         else{
//             double a0,a1,a2,a3;
//             calibration_coeff_file >> rdetector_id >> a0 >> a1 >> a2 >> a3;
//             std::vector<double> cals = {a0,a1,a2,a3};

//             calibration_coeffs.insert(std::pair<int,std::vector<double>>{rdetector_id,cals});
//             calibration_coeff_file.ignore(256,'\n');
//         }
//     }
//     detector_calibrations_loaded = 1;
//     calibration_coeff_file.close();

//     LOG(info) << "LisaFast Calibration coefficients File: " + calibration_file;
//     return; 
// }



// Allign the detector to 0 using a reference cascade with "instantaneus" gammas (i.e. 344 - 788 of 152Eu source)
void TLisaFastConfiguration::ReadTimeshiftCoefficients()
{
    c4LOG(info, "Reading Timeshift coefficients.");
    c4LOG(info, "File reading");
    c4LOG(info, timeshift_calibration_file);

    std::ifstream timeshift_file (timeshift_calibration_file);

    int rdetector_id1, rdetector_id2; // temp read variables
    double timeshift;
    
    //assumes the first line in the file is num-modules used
    while(!timeshift_file.eof()){
        if(timeshift_file.peek()=='#') timeshift_file.ignore(256,'\n');
        else{
            timeshift_file >> rdetector_id1 >> rdetector_id2 >> timeshift;

            timeshift_calibration_coeffs.insert(std::pair<std::pair<int,int>,double>{std::pair<int,int>(rdetector_id1,rdetector_id2),timeshift});
            timeshift_file.ignore(256,'\n');
        }
    }
    timeshift_calibration_coeffs_loaded = 1;
    timeshift_file.close();
    return; 

};

// This is a VETO for the prompt flash. From En vs dTime create a TCut.
void TLisaFastConfiguration::ReadPromptFlashCut()
{
    // must be a root file (not always the case from saving TCuts)
    // must be named "lisafast_prompt_flash_cut"!
    TFile* cut = TFile::Open(TString(promptflash_cut_file),"READ");
    
    if (!cut || cut->IsZombie() || cut->TestBit(TFile::kRecovered))
    {
        c4LOG(warn, "LisaFast prompt flash cut file provided (" << promptflash_cut_file << ") is not a ROOT file.");
        return;
    }
    
    TCutG* cut_from_file =
        dynamic_cast<TCutG*>(cut->Get("lisafast_prompt_flash_cut"));

    if (cut_from_file)
    {
        prompt_flash_cut = dynamic_cast<TCutG*>(cut_from_file->Clone());
        LOG(info) << "LisaFast Prompt flash cut File: " + promptflash_cut_file;
    }
    else
    {
        c4LOG(warn, "LisaFast prompt flash cut does not exist in file: " << promptflash_cut_file);
    }

    cut->Close();
}


// This is a drift correction
void TLisaFastConfiguration::ReadGainShifts()
{
    // LaBr: one GainShift per detector number
    std::map<int, GainShift*> labr_by_det;
    for (const auto& [bc, det] : labr_mapping){
        if (IsDetectorAuxilliary(det)) continue;

        if (!labr_by_det.count(det)){
            TString name = Form("lisafast_gain_shift_det_%i", det);
            c4LOG(info, TString("Creating GainShifts for ") + name + TString(" at ") + TString(gain_shifts_file));
            labr_by_det[det] = new GainShift(name, TString(gain_shifts_file));
        }
        gain_shifts[bc] = labr_by_det[det];
    }

    // Diamond: one GainShift per (layer, x, y)
    for (const auto& [bc, v] : diamond_mapping){
        int layer = v.first.first;
        int x     = v.first.second.first;
        int y     = v.first.second.second;

        TString name = Form("lisafast_gain_shift_diamond_l%i_x%i_y%i", layer, x, y);
        c4LOG(info, TString("Creating GainShifts for ") + name + TString(" at ") + TString(gain_shifts_file));
        gain_shifts[bc] = new GainShift(name, TString(gain_shifts_file));
    }

    gain_shifts_loaded = 1;
}

