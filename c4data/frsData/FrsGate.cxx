#include "FrsGate.h"

#include "TFile.h"
#include "TCutG.h"
#include "c4Logger.h"

FrsGate::FrsGate(std::string gn, std::string file_name)
{
// read gates here.
    gate_name = gn;

    TFile * infile = TFile::Open(TString(file_name),"READ");
    cut_Z_AoQ = (TCutG*)infile->Get("cut_Z_AoQ");
    cut_Z_Z2 = (TCutG*)infile->Get("cut_Z_Z2");
    cut_x2_AoQ = (TCutG*)infile->Get("cut_x2_AoQ");
    cut_x4_AoQ = (TCutG*)infile->Get("cut_x4_AoQ");
    cut_dEdeg_Z = (TCutG*)infile->Get("cut_dEdeg_Z");

    c4LOG(info, Form("PID gate %s loaded with cuts on Z/AoQ = %i, Z/Z2 = %i, x2/AoQ = %i, x4/AoQ = %i, dEdeg/Z = %i",
    gate_name.c_str(),
    cut_Z_AoQ!=nullptr,
    cut_Z_Z2!=nullptr,
    cut_x2_AoQ!=nullptr,
    cut_x4_AoQ!=nullptr,
    cut_dEdeg_Z!=nullptr));

    infile->Close();


};


std::string FrsGate::GetName()
{
    return gate_name;
};


bool FrsGate::PassedGate(double Z, double Z2, double x2, double x4, double AoQ, double dEdeg)
{
    bool passed_gate_cut_Z_AoQ = false;
    bool passed_gate_cut_Z_Z2 = false;
    bool passed_gate_cut_x2_AoQ = false;
    bool passed_gate_cut_x4_AoQ = false;
    bool passed_gate_cut_dEdeg_Z = false;

    //NB ORDER OF GATES!!
    
    if (cut_Z_AoQ != nullptr) {
        passed_gate_cut_Z_AoQ = cut_Z_AoQ->IsInside(AoQ,Z);
    }else{
        passed_gate_cut_Z_AoQ = true;
    }
    if (cut_Z_Z2 != nullptr) {
        passed_gate_cut_Z_Z2 = cut_Z_Z2->IsInside(Z2,Z);
    }else{
        passed_gate_cut_Z_Z2 = true;
    }
    if (cut_x2_AoQ != nullptr) {
        passed_gate_cut_x2_AoQ = cut_x2_AoQ->IsInside(AoQ,x2);
    }else{
        passed_gate_cut_x2_AoQ = true;
    }
    if (cut_x4_AoQ != nullptr) {
        passed_gate_cut_x4_AoQ = cut_x4_AoQ->IsInside(AoQ,x4);
    }else{
        passed_gate_cut_x4_AoQ = true;
    }
    if (cut_dEdeg_Z != nullptr) {
        passed_gate_cut_dEdeg_Z = cut_dEdeg_Z->IsInside(Z,dEdeg);
    }else{
        passed_gate_cut_dEdeg_Z = true;
    }

    return passed_gate_cut_Z_AoQ && passed_gate_cut_Z_Z2 && passed_gate_cut_x2_AoQ && passed_gate_cut_x4_AoQ && passed_gate_cut_dEdeg_Z;
};

bool FrsGate::Passed_ZvsAoQ(double Z, double AoQ)
{
    bool passed_gate_cut_Z_AoQ = false;
    if (cut_Z_AoQ != nullptr) passed_gate_cut_Z_AoQ = cut_Z_AoQ->IsInside(AoQ, Z);
    else passed_gate_cut_Z_AoQ = true;
    
    return passed_gate_cut_Z_AoQ;
}

bool FrsGate::Passed_ZvsZ2(double Z, double Z2)
{
    bool passed_gate_cut_Z_Z2 = false;
    if (cut_Z_Z2 != nullptr) passed_gate_cut_Z_Z2 = cut_Z_Z2->IsInside(Z2, Z);
    else passed_gate_cut_Z_Z2 = true;
    
    return passed_gate_cut_Z_Z2;
}

bool FrsGate::Passed_x2vsAoQ(double x2, double AoQ)
{
    bool passed_gate_cut_x2_AoQ = false;
    if (cut_x2_AoQ != nullptr) passed_gate_cut_x2_AoQ = cut_x2_AoQ->IsInside(AoQ, x2);
    else passed_gate_cut_x2_AoQ = true;
    
    return passed_gate_cut_x2_AoQ;
}

bool FrsGate::Passed_x4vsAoQ(double x4, double AoQ)
{
    bool passed_gate_cut_x4_AoQ = false;
    if (cut_x4_AoQ != nullptr) passed_gate_cut_x4_AoQ = cut_x4_AoQ->IsInside(AoQ, x4);
    else passed_gate_cut_x4_AoQ = true;
    
    return passed_gate_cut_x4_AoQ;
}

bool FrsGate::Passed_dEdegvsZ(double Z, double dEdeg)
{
    bool passed_gate_cut_dEdeg_Z = false;
    if (cut_dEdeg_Z != nullptr) passed_gate_cut_dEdeg_Z = cut_dEdeg_Z->IsInside(Z, dEdeg);
    else passed_gate_cut_dEdeg_Z = true;
    
    return passed_gate_cut_dEdeg_Z;
}

ClassImp(FrsGate)
