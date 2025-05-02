#ifndef LisaGate_H
#define LisaGate_H

#include "TCutG.h"
#include <map>

class LisaGate
{
    public:
        LisaGate(std::string name, std::string file);

        virtual ~LisaGate();

        std::string GetName() { return gate_name; }
        bool PassedGate(int layer, double energy);

        std::string gate_name;
    
        std::map<int, std::pair<double, double>> gate;

    public:
        ClassDef(LisaGate, 1)
};

#endif