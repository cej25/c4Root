#ifndef FrsGate_H
#define FrsGate_H

#include "TCutG.h"

class FrsGate
{
    public:
        FrsGate(std::string gate_name, std::string file_name);

        ~FrsGate() {};

        std::string GetName();
        bool PassedGate(double Z1, double Z2, double x2, double x4, double AoQ, double dEdeg);

    public:
        std::string gate_name;

        TCutG* cut_Z_AoQ;
        TCutG* cut_Z_Z2;
        TCutG* cut_x2_AoQ;
        TCutG* cut_x4_AoQ;
        TCutG* cut_dEdeg_Z;        


    public:
        ClassDef(FrsGate, 1)
};

#endif