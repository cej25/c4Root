#include "TFatimaVmeConfiguration.h"

#include "c4Logger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

TFatimaVmeConfiguration* TFatimaVmeConfiguration::instance = nullptr;
std::string TFatimaVmeConfiguration::filepath = "Fatima_VME_allocation.txt";

TFatimaVmeConfiguration::TFatimaVmeConfiguration()
    :   detectors(0)
    ,   num_qdc_boards(0)
    ,   num_tdc_boards(0)
{
    ReadConfiguration();
}

void TFatimaVmeConfiguration::ReadConfiguration()
{
    std::ifstream detector_map_file(filepath);
    std::string line;
    std::set<int> qdc_boards;
    std::set<int> tdc_boards;

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

            extra_signals.insert(det);
        }

        if (qdc_board > -1) qdc_boards.insert(qdc_board);
        if (tdc_board > -1) tdc_boards.insert(tdc_board);

        dets_qdc[std::make_pair(qdc_board, qdc_chan)] = det;
        dets_tdc[std::make_pair(tdc_board, tdc_chan)] = det;

    }

    DetectorMap_loaded = 1;
    num_qdc_boards = qdc_boards.size();
    num_tdc_boards = tdc_boards.size();
    detector_map_file.close();
    return;
}