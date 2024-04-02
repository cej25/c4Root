#include "TCorrelationsConfiguration.h"

#include "c4Logger.h"
#include "FairLogger.h"

#include <iostream>
#include <sstream>
#include <string>
#include <set>

TCorrelationsConfiguration* TCorrelationsConfiguration::instance = nullptr;
std::string TCorrelationsConfiguration::filepath = "correlations.dat";

TCorrelationsConfiguration::TCorrelationsConfiguration()
{
    ReadCorrelationsFile();
}

void TCorrelationsConfiguration::ReadCorrelationsFile()
{
    std::ifstream file(filepath);
    std::string line;

    if (file.fail()) c4LOG(warn, "Cannot open correlations.dat file!");
    
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
                std::vector<int> reverse_values;
                if (values.size() > 1)
                {
                    reverse_values.push_back(-values[1]);
                    reverse_values.push_back(values[0]);
                }

                if (firstWord == "FRS_AIDA") correlations_map["FRS-AIDA"] = values;
                else if (firstWord == "FRS_FATIMA_PROMPT") correlations_map["FRS-Fatima Prompt"] = values;
                else if (firstWord == "FRS_FATIMA_LONG") correlations_map["FRS-Fatima Long"] = values;
                else if (firstWord == "FRS_FATIMA_LONG_PROMPT") correlations_map["FRS-Fatima Long Include Prompt"] = values;
                else if (firstWord == "FRS_FATIMA_LT_ANALYSIS") correlations_map["FRS-Fatima Lifetime Analysis"] = values;
                else if (firstWord == "FRS_BPLAST") correlations_map["FRS-bPlast"] = values;
                else if (firstWord == "FRS_GERMANIUM_PROMPT") correlations_map["FRS-Germanium Prompt"] = values;
                else if (firstWord == "FRS_GERMANIUM_LONG") correlations_map["FRS-Germanium Long"] = values;
                else if (firstWord == "SPILL_OFF_GAMMAS") correlations_map["Spill-Off Gammas"] = values;
                else if (firstWord == "BETA_DELAY_GAMMAS") correlations_map["Beta-Delayed Gammas"] = values;
                else if (firstWord == "BETA_DELAY_GAMMAS_LT_ANALYSIS") correlations_map["Beta-Delayed Gamma Lifetime Analysis"] = values;
                else if (firstWord == "FRS_AIDA_WR") correlations_map["FRS-AIDA WR Gate"] = values;
                else if (firstWord == "FRS_FATIMA_WR") correlations_map["FRS-Fatima WR Gate"] = values;
                else if (firstWord == "FRS_BPLAST_WR") correlations_map["FRS-bPlast WR Gate"] = values;
                else if (firstWord == "FRS_GERMANIUM_WR") correlations_map["FRS-Germanium WR Gate"] = values;
                else if (firstWord == "AIDA_DECAYS_GERMANIUM_WR") correlations_map["AIDA(Decays)-Germanium WR Gate"] = values;
                else if (firstWord == "AIDA_DECAYS_FATIMA_WR") correlations_map["AIDA(Decays)-Fatima WR Gate"] = values;
                else if (firstWord == "AIDA_IMPLANTS_BPLAST_WR") correlations_map["AIDA(Implants)-bPlast WR Gate"] = values;
                else if (firstWord == "AIDA_DECAYS_BPLAST_WR") correlations_map["AIDA(Decays)-bPlast WR Gate"] = values;
                else if (firstWord == "BPLAST_FATIMA_VME_WR") correlations_map["bPlast-Fatima(VME) WR Gate"] = values;
                else if (firstWord == "BPLAST_FATIMA_TAMEX_WR") correlations_map["bPlast-Fatima(TAMEX) WR Gate"] = values;
                else if (firstWord == "BPLAST_GERMANIUM_WR") correlations_map["bPlast-Germanium WR Gate"] = values;
                else if (firstWord == "FATIMA_VME_FATIMA_TAMEX_WR") correlations_map["Fatima(VME)-Fatima(TAMEX) WR Gate"] = values;
                else if (firstWord == "FATIMA_VME_GERMANIUM_WR") correlations_map["Fatima(VME)-Germanium WR Gate"] = values;
                else if (firstWord == "FATIMA_TAMEX_GERMANIUM_WR") correlations_map["Fatima(TAMEX)-Germanium WR Gate"] = values;
                else if (firstWord == "GAMMA_GAMMA_GERMANIUM_TIME") correlations_map["Germanium Gamma-Gamma dT Gate"] = values;
                else if (firstWord == "FRS_GERMANIUM_LONG_DT") correlations_map["FRS-Germanium Long dT Gate"] = values;
                else if (firstWord == "GAMMA_GAMMA_FATIMA_TIME") correlations_map["Fatima Gamma-Gamma dT Gate"] = values;
                else if (firstWord == "FRS_FATIMA_LONG_DT") correlations_map["FRS-Fatima Long dT Gate"] = values;
                else if (firstWord == "FRS_FATIMA_LONG_DT_SCALE") correlations_map["FRS-Fatima Long dT Scale"] = values;
                else if (firstWord == "LT_START_STOP_1") correlations_map["Lifetime 1 Start-Stop Energies"] = values;
                else if (firstWord == "LT_START_STOP_2") correlations_map["Lifetime 2 Start-Stop Energies"] = values;
                else if (firstWord == "LT_START_STOP_3") correlations_map["Lifetime 3 Start-Stop Energies"] = values;
                else if (firstWord == "LT_START_STOP_PID") correlations_map["Start-Stop Analysis PID"] = values;
                else if (firstWord == "IMPLANT_DECAY_DT") correlations_map["Implant-Decay dT Gate"] = values;
                else if (firstWord == "AIDA_FB_DT_DE") correlations_map["AIDA Front-Back Conditions"] = values;
                else if (firstWord == "AIDA_MAX_DECAY_E") correlations_map["AIDA Max Decay-Energy Gates"] = values;
                else if (firstWord == "BPLAST_TOT_GATE") correlations_map["bPlast ToT Gate"] = values;
                else if (firstWord == "BDG_START_STOP_1") correlations_map["Beta-Delayed Gamma Lifetime 1 Start-Stop Energies"] = values;
                else if (firstWord == "BDG_START_STOP_2") correlations_map["Beta-Delayed Gamma Lifetime 2 Start-Stop Energies"] = values;
                else if (firstWord == "BDG_PID") correlations_map["Beta-Delayed Gamma PID"] = values;

                // time machine map - we should use {all capitals} only for FRS. We can standardise this after dryrun
                
                else if (firstWord == "FRS_AIDA_TM")
                {
                    timemachine_map["FRS-Aida TM Gate"] = values;
                    timemachine_map["Aida-FRS TM Gate"] = reverse_values;
                }
                else if (firstWord == "AIDA_FATIMA_TAMEX_TM")
                {
                    timemachine_map["Aida-Fatima TM Gate"] = values;
                    timemachine_map["Fatima-Aida TM Gate"] = reverse_values;
                }
                else if (firstWord == "AIDA_FATIMA_VME_TM")
                {
                    timemachine_map["Aida-FatimaVme TM Gate"] = values;
                    timemachine_map["FatimaVme-Aida TM Gate"] = reverse_values;
                }
                else if (firstWord == "AIDA_BPLAST_TM")
                {
                    timemachine_map["Aida-bPlast TM Gate"] = values;
                    timemachine_map["bPlast-Aida TM Gate"] = reverse_values;
                }
                else if (firstWord == "AIDA_GERMANIUM_TM")
                {
                    timemachine_map["Aida-Germanium TM Gate"] = values;
                    timemachine_map["Germanium-Aida TM Gate"] = reverse_values;
                }
                else if (firstWord == "FATIMA_TAMEX_FATIMA_VME_TM")
                {
                    timemachine_map["Fatima-FatimaVme TM Gate"] = values;
                    timemachine_map["FatimaVme-Fatima TM Gate"] = reverse_values;
                }
                else if (firstWord == "FATIMA_TAMEX_BPLAST_TM")
                {
                    timemachine_map["Fatima-bPlast TM Gate"] = values;
                    timemachine_map["bPlast-Fatima TM Gate"] = reverse_values;
                }
                else if (firstWord == "FATIMA_TAMEX_GERMANIUM_TM")
                {
                    timemachine_map["Fatima-Germanium TM Gate"] = values;
                    timemachine_map["Germanium-Fatima TM Gate"] = reverse_values;
                }
                else if (firstWord == "FATIMA_VME_BPLAST_TM")
                {
                    timemachine_map["FatimaVme-bPlast TM Gate"] = values;
                    timemachine_map["bPlast-FatimaVme TM Gate"] = reverse_values;
                }
                else if (firstWord == "FATIMA_VME_GERMANIUM_TM")
                {
                    timemachine_map["FatimaVme-Germanium TM Gate"] = values;
                    timemachine_map["Germanium-FatimaVme TM Gate"] = reverse_values;
                }
                else if (firstWord == "BPLAST_GERMANIUM_TM")
                {
                    timemachine_map["bPlast-Germanium TM Gate"] = values;
                    timemachine_map["Germanium-bPlast TM Gate"] = reverse_values;
                }

            }
        }
    }

    LOG(info) <<  "Correlations File: " + filepath;
}
