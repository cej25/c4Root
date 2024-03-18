#include "CorrelationsMap.h"

#include <iostream>
#include <fstream>
#include <sstream>

CorrelationsMap::CorrelationsMap(std::string& filename)
{
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string firstWord;
        iss >> firstWord;

        if (!firstWord.empty())
        {
            int value;
            std::vector<int> values;
            while (iss >> value) values.push_back(value);

            if (!values.empty())
            {
                if (firstWord == "FRS_AIDA") (*this)["FRS-AIDA"] = values;
                else if (firstWord == "FRS_FATIMA_PROMPT") (*this)["FRS-Fatima Prompt"] = values;
                else if (firstWord == "FRS_FATIMA_LONG") (*this)["FRS-Fatima Long"] = values;
                else if (firstWord == "FRS_FATIMA_LONG_PROMPT") (*this)["FRS-Fatima Long Include Prompt"] = values;
                else if (firstWord == "FRS_FATIMA_LT_ANALYSIS") (*this)["FRS-Fatima Lifetime Analysis"] = values;
                else if (firstWord == "FRS_BPLAST") (*this)["FRS-bPlast"] = values;
                else if (firstWord == "FRS_GERMANIUM_PROMPT") (*this)["FRS-Germanium Prompt"] = values;
                else if (firstWord == "FRS_GERMANIUM_LONG") (*this)["FRS-Germanium Long"] = values;
                else if (firstWord == "SPILL_OFF_GAMMAS") (*this)["Spill-Off Gammas"] = values;
                else if (firstWord == "BETA_DELAY_GAMMAS") (*this)["Beta-Delayed Gammas"] = values;
                else if (firstWord == "BETA_DELAY_GAMMAS_LT_ANALYSIS") (*this)["Beta-Delayed Gamma Lifetime Analysis"] = values;
                else if (firstWord == "FRS_AIDA_WR") (*this)["FRS-AIDA WR Gate"] = values;
                else if (firstWord == "FRS_FATIMA_WR") (*this)["FRS-Fatima WR Gate"] = values;
                else if (firstWord == "FRS_BPLAST_WR") (*this)["FRS-bPlast WR Gate"] = values;
                else if (firstWord == "FRS_GERMANIUM_WR") (*this)["FRS-Germanium WR Gate"] = values;
                else if (firstWord == "AIDA_DECAYS_GERMANIUM_WR") (*this)["AIDA(Decays)-Germanium WR Gate"] = values;
                else if (firstWord == "AIDA_DECAYS_FATIMA_WR") (*this)["AIDA(Decays)-Fatima WR Gate"] = values;
                else if (firstWord == "AIDA_IMPLANTS_BPLAST_WR") (*this)["AIDA(Implants)-bPlast WR Gate"] = values;
                else if (firstWord == "AIDA_DECAYS_BPLAST_WR") (*this)["AIDA(Decays)-bPlast WR Gate"] = values;
                else if (firstWord == "BPLAST_FATIMA_VME_WR") (*this)["bPlast-Fatima(VME) WR Gate"] = values;
                else if (firstWord == "BPLAST_FATIMA_TAMEX_WR") (*this)["bPlast-Fatima(TAMEX) WR Gate"] = values;
                else if (firstWord == "BPLAST_GERMANIUM_WR") (*this)["bPlast-Germanium WR Gate"] = values;
                else if (firstWord == "FATIMA_VME_FATIMA_TAMEX_WR") (*this)["Fatima(VME)-Fatima(TAMEX) WR Gate"] = values;
                else if (firstWord == "FATIMA_VME_GERMANIUM_WR") (*this)["Fatima(VME)-Germanium WR Gate"] = values;
                else if (firstWord == "FATIMA_TAMEX_GERMANIUM_WR") (*this)["Fatima(TAMEX)-Germanium WR Gate"] = values;
                else if (firstWord == "FRS_AIDA_TM") (*this)["FRS-AIDA TM Gate"] = values;
                else if (firstWord == "AIDA_GERMANIUM_TM") (*this)["AIDA-Germanium TM Gate"] = values;
                else if (firstWord == "AIDA_FATIMA_VME_TM") (*this)["AIDA-Fatima(VME) TM Gate"] = values;
                else if (firstWord == "AIDA_FATIMA_TAMEX_TM") (*this)["AIDA-Fatima(TAMEX) TM Gate"] = values;
                else if (firstWord == "AIDA_BPLAST_TM") (*this)["AIDA-bPlast TM Gate"] = values;
                else if (firstWord == "FATIMA_VME_BPLAST_TM") (*this) ["Fatima(VME)-bPlast TM Gate"] = values;
                else if (firstWord == "FATIMA_VME_GERMANIUM_TM") (*this) ["Fatima(VME)-Germanium TM Gate"] = values;
                else if (firstWord == "FATIMA_TAMEX_BPLAST_TM") (*this) ["Fatima(TAMEX)-bPlast TM Gate"] = values;
                else if (firstWord == "FATIMA_TAMEX_GERMANIUM_TM") (*this) ["Fatima(TAMEX)-Germanium TM Gate"] = values;
                else if (firstWord == "BPLAST_GERMANIUM_TM") (*this) ["bPlast-Germanium TM Gate"] = values;
                else if (firstWord == "GAMMA_GAMMA_GERMANIUM_TIME") (*this)["Germanium Gamma-Gamma dT Gate"] = values;
                else if (firstWord == "FRS_GERMANIUM_LONG_DT") (*this)["FRS-Germanium Long dT Gate"] = values;
                else if (firstWord == "GAMMA_GAMMA_FATIMA_TIME") (*this)["Fatima Gamma-Gamma dT Gate"] = values;
                else if (firstWord == "FRS_FATIMA_LONG_DT") (*this)["FRS-Fatima Long dT Gate"] = values;
                else if (firstWord == "FRS_FATIMA_LONG_DT_SCALE") (*this)["FRS-Fatima Long dT Scale"] = values;
                else if (firstWord == "LT_START_STOP_1") (*this)["Lifetime 1 Start-Stop Energies"] = values;
                else if (firstWord == "LT_START_STOP_2") (*this)["Lifetime 2 Start-Stop Energies"] = values;
                else if (firstWord == "LT_START_STOP_3") (*this)["Lifetime 3 Start-Stop Energies"] = values;
                else if (firstWord == "LT_START_STOP_PID") (*this)["Start-Stop Analysis PID"] = values;
                else if (firstWord == "IMPLANT_DECAY_DT") (*this)["Implant-Decay dT Gate"] = values;
                else if (firstWord == "AIDA_FB_DT_DE") (*this)["AIDA Front-Back Conditions"] = values;
                else if (firstWord == "AIDA_MAX_DECAY_E") (*this)["AIDA Max Decay-Energy Gates"] = values;
                else if (firstWord == "BPLAST_TOT_GATE") (*this)["bPlast ToT Gate"] = values;
                else if (firstWord == "BDG_START_STOP_1") (*this)["Beta-Delayed Gamma Lifetime 1 Start-Stop Energies"] = values;
                else if (firstWord == "BDG_START_STOP_2") (*this)["Beta-Delayed Gamma Lifetime 2 Start-Stop Energies"] = values;
                else if (firstWord == "BDG_PID") (*this)["Beta-Delayed Gamma PID"] = values;
            }
        } 
        
    }

}