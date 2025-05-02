#include "LisaGate.h"

#include "TFile.h"
#include "TCutG.h"
#include "c4Logger.h"

LisaGate::LisaGate(std::string name, std::string file)
{
    gate_name = name;

    std::ifstream gate_file(file);
    std::string line;
   
    while (std::getline(gate_file, line))
    {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        int layer_id;
        double gate_min, gate_max;

        iss >> layer_id >> gate_min >> gate_max;

        gate[layer_id] = std::make_pair(gate_min, gate_max);
            
    }

    c4LOG(info, "Loaded Gates from: " + file);  
    gate_file.close();
};

LisaGate::~LisaGate()
{
    
}

bool LisaGate::PassedGate(int layer, double energy)
{
    if (energy > gate[layer].first && energy < gate[layer].second) return true;
    else return false;
};


ClassImp(LisaGate)
