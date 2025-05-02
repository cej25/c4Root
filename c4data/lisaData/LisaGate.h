#ifndef LisaGate_H
#define LisaGate_H

#include "TCutG.h"
#include <map>
#include <iostream>


class LisaGate
{
    public:
        LisaGate(std::string name, std::string type, std::string file);

        virtual ~LisaGate();

        std::string GetName() { return gate_name; }
        std::string GetType() { return gate_type; }
        bool PassedGate(int layer, double energy);

        std::string gate_name;
        std::string gate_type;
    
        std::map<int, std::pair<double, double>> gate;

    public:
        ClassDef(LisaGate, 1)
};

#endif