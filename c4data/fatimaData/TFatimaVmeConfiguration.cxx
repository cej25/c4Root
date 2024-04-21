#include "TFatimaVmeConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

TFatimaVmeConfiguration* TFatimaVmeConfiguration::instance = nullptr;
std::string TFatimaVmeConfiguration::mapfilepath = "Fatima_VME_allocation.txt";
std::string TFatimaVmeConfiguration::qdc_e_calfilepath = "";
std::string TFatimaVmeConfiguration::qdc_t_calfilepath = "";
std::string TFatimaVmeConfiguration::tdc_t_calfilepath = "";

TFatimaVmeConfiguration::TFatimaVmeConfiguration()
    :   num_detectors(0)
    ,   num_qdc_boards(0)
    ,   num_tdc_boards(0)
{
    ReadConfiguration();
    Read_QDC_E_Calibration();
    Read_QDC_T_Calibration();
    Read_TDC_T_Calibration();
}

void TFatimaVmeConfiguration::ReadConfiguration()
{
    std::ifstream detector_map_file(mapfilepath);
    std::string line;
    std::set<int> detector_ids;
    std::set<int> qdc_boards;
    std::set<int> tdc_boards;

    if (detector_map_file.fail()) c4LOG(warn, "Could not open Fatima VME configuration map");

    while (std::getline(detector_map_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string signal;

        int det, qdc_board, qdc_chan, tdc_board, tdc_chan;

        iss >> signal;

        if (isdigit(signal[0])) // detector
        {
            det = std::stoi(signal);
            
            iss >> qdc_board >> qdc_chan >> tdc_board >> tdc_chan;

            if (det > -1) detector_ids.insert(det);
            
        }
        else // some additional signal
        {
            iss >> det >> qdc_board >> qdc_chan >> tdc_board >> tdc_chan;

            if (signal == "TimeMachineU") tm_undelayed = det;
            else if (signal == "TimeMachineD") tm_delayed = det;
            else if (signal == "SC41L_D") sc41l_d = det;
            else if (signal == "SC41R_D") sc41r_d = det;
            else if (signal == "SC41L_A") sc41l_a = det;
            else if (signal == "SC41R_A") sc41r_a = det;
            else if (signal == "BPLAST_UP") bplast_up = det;
            else if (signal == "BPLAST_DOWN") bplast_down = det;
            else if (signal == "BPLAST_COINC") bplast_coinc = det;
            else if (signal == "FRS_ACCEPT") frs_accept = det;
            else if (signal == "BPLAST_ACCEPT") bplast_accept = det;
            else if (signal == "BPLAST_FREE") bplast_free = det;

	  std::cout << "signal: " << signal << " - detector: " << det << std::endl;

            extra_signals.insert(det);
	  detector_ids.insert(det);
        }

        //if (det > -1) detector_ids.insert(det);
        if (qdc_board > -1) qdc_boards.insert(qdc_board);
        if (tdc_board > -1) tdc_boards.insert(tdc_board);

        dets_qdc[std::make_pair(qdc_board, qdc_chan)] = det;
        dets_tdc[std::make_pair(tdc_board, tdc_chan)] = det;

    }

    DetectorMap_loaded = 1;
    num_detectors = detector_ids.size();
    num_qdc_boards = qdc_boards.size();
    num_tdc_boards = tdc_boards.size();
    detector_map_file.close();
    return;
}

void TFatimaVmeConfiguration::Read_QDC_E_Calibration()
{
    std::ifstream calfile(qdc_e_calfilepath);
    std::string line;

    const char* format = "%d %lf %lf %lf %lf %lf";
    calib_coeffs_QDC_E = new double*[100];
    for (int i = 0; i < 100; i++) calib_coeffs_QDC_E[i] = new double[5];
    original_calib_coeffs_QDC_E = new double*[100];
    for (int i = 0; i < 100; i++) original_calib_coeffs_QDC_E[i] = new double[5];

    if (calfile.fail()) c4LOG(warn, "Could not open Fatima VME QDC E calibration file.");

    double tmp_coeffs[5] = {0, 0, 0, 0, 0};
    int det_id = 0;

    while (calfile.good())
    {
        std::getline(calfile, line, '\n');
        if (line[0] == '#' || line.empty()) continue;

        sscanf(line.c_str(), format, &det_id, &tmp_coeffs[0], &tmp_coeffs[1], &tmp_coeffs[2], &tmp_coeffs[3], &tmp_coeffs[4]);
        
        for (int i = 0; i < 5; i++)
        {
            calib_coeffs_QDC_E[det_id][i] = tmp_coeffs[i];
            original_calib_coeffs_QDC_E[det_id][i] = tmp_coeffs[i];
        }
    }
}

void TFatimaVmeConfiguration::Read_QDC_T_Calibration()
{
    const char* format = "%d %lf";
    calib_coeffs_QDC_T = new double[100];

    std::ifstream calfile(qdc_t_calfilepath);
    std::string line;

    if (calfile.fail()) c4LOG(warn, "Could not find Fatima VME QDC T Calibration file");
    
    double tmp_coeffs;
    int det_id = 0;

    while (calfile.good())
    {
        std::getline(calfile, line, '\n');
        if (line[0] == '#' || line.empty()) continue;
        
        sscanf(line.c_str(), format, &det_id, &tmp_coeffs);

        calib_coeffs_QDC_T[det_id] = tmp_coeffs;
    }
}

void TFatimaVmeConfiguration::Read_TDC_T_Calibration()
{
    const char* format = "%d %lf";
    calib_coeffs_TDC_T = new double[100];

    std::ifstream calfile(tdc_t_calfilepath);
    std::string line;

    if (calfile.fail()) c4LOG(warn, "Could not find Fatima (VME) TDC Time Calibration file");

    double tmp_coeffs;
    int det_id = 0;

    while (calfile.good())
    {
        std::getline(calfile, line, '\n');
        if (line[0] == '#' || line.empty()) continue;
        
        sscanf(line.c_str(), format, &det_id, &tmp_coeffs);

        calib_coeffs_TDC_T[det_id] = tmp_coeffs;
    }
}

