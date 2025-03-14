#ifndef FrsGate_H
#define FrsGate_H

#include "TCutG.h"

class FrsGate
{
    public:
        FrsGate(std::string gate_name, std::string file_name);

        virtual ~FrsGate();

        std::string GetName();
        bool PassedGate(double Z41, double Z2, double x2, double x4, double AoQs2s4, double dEdegZ41, double sci42E);
        bool Passed_Z41vsAoQs2s4(double Z41, double AoQs2s4);
        bool Passed_Z41vsZ42(double Z41, double Z42);
        bool Passed_x2vsAoQs2s4(double x2, double AoQs2s4);
        bool Passed_x4vsAoQs2s4(double x4, double AoQs2s4);
        bool Passed_dEdegZ41vsZ41(double Z41, double dEdegZ41);
        bool Passed_sci42EvsZ41(double Z41, double sci42E);
        bool Passed_Z41vsAoQs2s4_driftcorr(double Z41_driftcorr, double AoQs2s4_driftcorr);
        bool cut_Z41vsAoQs2s4_exists() {  return cut_Z41_AoQs2s4 != nullptr; } 
        bool cut_Z41vsZ42_exists() {  return cut_Z41_Z42 != nullptr; } 
        bool cut_x2vsAoQs2s4_exists() {  return cut_x2_AoQs2s4 != nullptr; } 
        bool cut_x4vsAoQs2s4_exists() {  return cut_x4_AoQs2s4 != nullptr; } 
        bool cut_dEvsZ41_exists() {  return cut_dEdegZ41_Z41 != nullptr; } 
        bool cut_sci42E_exists() {  return cut_sci42E_Z41 != nullptr; } 
        bool cut_ZvsAoQ_driftcorr_exists() {  return cut_Z41_AoQs2s4_driftcorr != nullptr; } 


    public:
        std::string gate_name;

        TCutG* cut_Z41_AoQs2s4;
        TCutG* cut_Z41_Z42;
        TCutG* cut_x2_AoQs2s4;
        TCutG* cut_x4_AoQs2s4;
        TCutG* cut_dEdegZ41_Z41;
        TCutG* cut_sci42E_Z41;
        TCutG* cut_Z41_AoQs2s4_driftcorr;

    public:
        ClassDef(FrsGate, 1)
};

#endif