/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                             C.E. Jones                                     *
 *                              06.05.25                                      *
 ******************************************************************************/

#include "FrsGate.h"

#include "TFile.h"
#include "TCutG.h"
#include "c4Logger.h"

FrsGate::FrsGate(std::string gn, std::string file_name)
{
// read gates here.
    gate_name = gn;

    TFile* infile = TFile::Open(TString(file_name),"READ");

    // S1-S2
    cut_Z21_AoQs1s2 = (TCutG*)infile->Get("cut_Z21_AoQs1s2");
    cut_x2_AoQs1s2 = (TCutG*)infile->Get("cut_x2_AoQs1s2");

    // S2-S4
    cut_Z41_AoQs2s4 = (TCutG*)infile->Get("cut_Z41_AoQs2s4");
    cut_Z42_AoQs2s4 = (TCutG*)infile->Get("cut_Z42_AoQs2s4");
    cut_x2_AoQs2s4 = (TCutG*)infile->Get("cut_x2_AoQs2s4");
    cut_x4_AoQs2s4 = (TCutG*)infile->Get("cut_x4_AoQs2s4");
    cut_Z41_Z42 = (TCutG*)infile->Get("cut_Z41_Z4");
    cut_dEdegZ41_Z41 = (TCutG*)infile->Get("cut_dEdeg_Z41");
    cut_sci42E_Z41 = (TCutG*)infile->Get("cut_sci42E_Z41");

    // Both
    cut_Z21_Z41 = (TCutG*)infile->Get("cut_Z21_Z41");

    // I think this can be handled better.
    c4LOG(info, Form("PID gate %s loaded with cuts on Z21/AoQs1s2 = %i, Z41/AoQs2s4 = %i, Z42/AoQs2s4 = %i, Z21/Z41 = %i, Z41/Z42 = %i, x2/AoQs2s4 = %i, x4/AoQs2s4 = %i, x2/AoQs1s2 = %i, dEdegZ41/Z41 = %i, sci42E/Z41 = %i",
    gate_name.c_str(),
    cut_Z21_AoQs1s2!=nullptr,
    cut_Z41_AoQs2s4!=nullptr,
    cut_Z42_AoQs2s4!=nullptr,
    cut_Z21_Z41!=nullptr,
    cut_Z41_Z42!=nullptr,
    cut_x2_AoQs2s4!=nullptr,
    cut_x4_AoQs2s4!=nullptr,
    cut_x2_AoQs1s2!=nullptr,
    cut_dEdegZ41_Z41!=nullptr,
    cut_sci42E_Z41!=nullptr));

    //::: Drift corrected
    cut_Z41_AoQs2s4_driftcorr = (TCutG*)infile->Get("cut_Z41_AoQs2s4_driftcorr");
    
    if (cut_Z41_AoQs2s4_driftcorr)
    {
        c4LOG(info, Form("PID gate cut_Z41_AoQs2s4_driftcorr loaded with cuts on Z41/AoQs2s4 = %i",
        cut_Z41_AoQs2s4_driftcorr!=nullptr));
    }

    infile->Close();
};

FrsGate::~FrsGate()
{
    
}


std::string FrsGate::GetName()
{
    return gate_name;
};


bool FrsGate::PassedS1S2(double Z21, double x2, double AoQs1s2)
{
    bool passed_gate_cut_Z21_AoQs1s2 = false;
    bool passed_gate_cut_x2_AoQs1s2 = false;

    if (cut_Z21_AoQs1s2 != nullptr) passed_gate_cut_Z21_AoQs1s2 = cut_Z21_AoQs1s2->IsInside(AoQs1s2, Z21);
    else passed_gate_cut_Z21_AoQs1s2 = true;

    if (cut_x2_AoQs1s2 != nullptr) passed_gate_cut_x2_AoQs1s2 = cut_x2_AoQs1s2->IsInside(AoQs1s2, x2);
    else passed_gate_cut_x2_AoQs1s2 = true;

    return (passed_gate_cut_Z21_AoQs1s2 && passed_gate_cut_x2_AoQs1s2);
}

bool FrsGate::PassedS2S4(double Z41, double Z42, double x2, double x4, double AoQs2s4, double dEdegZ41, double sci42E)
{
    bool passed_gate_cut_Z41_AoQs2s4 = false;
    bool passed_gate_cut_Z42_AoQs2s4 = false;
    bool passed_gate_cut_Z41_Z42 = false;
    bool passed_gate_cut_x2_AoQs2s4 = false;
    bool passed_gate_cut_x4_AoQs2s4 = false;
    bool passed_gate_cut_dEdegZ41_Z41 = false;
    bool passed_gate_cut_sci42E_Z41 = false;

    if (cut_Z41_AoQs2s4 != nullptr) passed_gate_cut_Z41_AoQs2s4 = cut_Z41_AoQs2s4->IsInside(AoQs2s4,Z41);
    else passed_gate_cut_Z41_AoQs2s4 = true;

    if (cut_Z42_AoQs2s4 != nullptr) passed_gate_cut_Z42_AoQs2s4 = cut_Z42_AoQs2s4->IsInside(AoQs2s4,Z42);
    else passed_gate_cut_Z42_AoQs2s4 = true;

    if (cut_Z41_Z42 != nullptr) passed_gate_cut_Z41_Z42 = cut_Z41_Z42->IsInside(Z42,Z41);
    else passed_gate_cut_Z41_Z42 = true;

    if (cut_x2_AoQs2s4 != nullptr) passed_gate_cut_x2_AoQs2s4 = cut_x2_AoQs2s4->IsInside(AoQs2s4,x2);
    else passed_gate_cut_x2_AoQs2s4 = true;

    if (cut_x4_AoQs2s4 != nullptr) passed_gate_cut_x4_AoQs2s4 = cut_x4_AoQs2s4->IsInside(AoQs2s4,x4);
    else passed_gate_cut_x4_AoQs2s4 = true;

    if (cut_dEdegZ41_Z41 != nullptr) passed_gate_cut_dEdegZ41_Z41 = cut_dEdegZ41_Z41->IsInside(dEdegZ41,Z41);
    else passed_gate_cut_dEdegZ41_Z41 = true;

    if (cut_sci42E_Z41 != nullptr) passed_gate_cut_sci42E_Z41 = cut_sci42E_Z41->IsInside(sci42E,Z41);
    else passed_gate_cut_sci42E_Z41 = true;
    
    return (passed_gate_cut_Z41_AoQs2s4 && passed_gate_cut_Z42_AoQs2s4 && passed_gate_cut_Z41_Z42 && passed_gate_cut_x2_AoQs2s4 && passed_gate_cut_x4_AoQs2s4 && passed_gate_cut_dEdegZ41_Z41 && passed_gate_cut_sci42E_Z41);

}

bool FrsGate::PassedAllGates(double Z21, double AoQs1s2, double x2, double Z41, double Z42, double x4, double AoQs2s4, double dEdegZ41, double sci42E)
{
    bool passed_s1s2 = false;
    bool passed_s2s4 = false;
    bool passed_gate_cut_Z21_Z41 = false;

    passed_s1s2 = PassedS1S2(Z21, x2, AoQs1s2);
    passed_s2s4 = PassedS2S4(Z41, Z42, x2, x4, AoQs2s4, dEdegZ41, sci42E);
    if (cut_Z21_Z41 != nullptr) passed_gate_cut_Z21_Z41 = cut_Z21_Z41->IsInside(Z21, Z41);
    else passed_gate_cut_Z21_Z41 = true;

    return (passed_s1s2 && passed_s2s4 && passed_gate_cut_Z21_Z41);
}


bool FrsGate::PassedGate(/*double Z21,*/ double Z41, double Z42, double x2, double x4, double AoQs2s4, /*double AoQs1s2,*/ double dEdegZ41, double sci42E)
{
    //bool passed_gate_cut_Z21_AoQs1s2 = false;
    bool passed_gate_cut_Z41_AoQs2s4 = false;
    //bool passed_gate_cut_Z21_Z41 = false;
    bool passed_gate_cut_Z41_Z42 = false;
    bool passed_gate_cut_x2_AoQs2s4 = false;
    bool passed_gate_cut_x4_AoQs2s4 = false;
    //bool passed_gate_cut_x2_AoQs1s2 = false;
    bool passed_gate_cut_dEdegZ41_Z41 = false;
    bool passed_gate_cut_sci42E_Z41 = false;

    //NB ORDER OF GATES!!
    // if (cut_Z21_AoQs1s2 != nullptr) {
    //     passed_gate_cut_Z21_AoQs1s2 = cut_Z21_AoQs1s2->IsInside(AoQs1s2,Z21);
    // }else{
    //     passed_gate_cut_Z21_AoQs1s2 = true;
    // }

    if (cut_Z41_AoQs2s4 != nullptr) {
        passed_gate_cut_Z41_AoQs2s4 = cut_Z41_AoQs2s4->IsInside(AoQs2s4,Z41);
    }else{
        passed_gate_cut_Z41_AoQs2s4 = true;
    }

    // if (cut_Z21_Z41 != nullptr) {
    //     passed_gate_cut_Z21_Z41 = cut_Z21_Z41->IsInside(Z41,Z21);
    // }else{
    //     passed_gate_cut_Z21_Z41 = true;
    // }

    if (cut_Z41_Z42 != nullptr) {
        passed_gate_cut_Z41_Z42 = cut_Z41_Z42->IsInside(Z42,Z41);
    }else{
        passed_gate_cut_Z41_Z42 = true;
    }

    if (cut_x2_AoQs2s4 != nullptr) {
        passed_gate_cut_x2_AoQs2s4 = cut_x2_AoQs2s4->IsInside(AoQs2s4,x2);
    }else{
        passed_gate_cut_x2_AoQs2s4 = true;
    }

    if (cut_x4_AoQs2s4 != nullptr) {
        passed_gate_cut_x4_AoQs2s4 = cut_x4_AoQs2s4->IsInside(AoQs2s4,x4);
    }else{
        passed_gate_cut_x4_AoQs2s4 = true;
    }

    // if (cut_x2_AoQs1s2 != nullptr) {
    //     passed_gate_cut_x2_AoQs1s2 = cut_x2_AoQs1s2->IsInside(AoQs1s2,x2);
    // }else{
    //     passed_gate_cut_x2_AoQs1s2 = true;
    // }

    if (cut_dEdegZ41_Z41 != nullptr) {
        passed_gate_cut_dEdegZ41_Z41 = cut_dEdegZ41_Z41->IsInside(dEdegZ41,Z41);
    }else{
        passed_gate_cut_dEdegZ41_Z41 = true;
    }

    if (cut_sci42E_Z41 != nullptr) {
        passed_gate_cut_sci42E_Z41 = cut_sci42E_Z41->IsInside(sci42E,Z41);
    }else{
        passed_gate_cut_sci42E_Z41 = true;
    }


    return /*passed_gate_cut_Z21_AoQs1s2 &&*/ passed_gate_cut_Z41_AoQs2s4 && /*passed_gate_cut_Z21_Z41 &&*/ passed_gate_cut_Z41_Z42 && passed_gate_cut_x2_AoQs2s4 && passed_gate_cut_x4_AoQs2s4 && /*passed_gate_cut_x2_AoQs1s2 &&*/ passed_gate_cut_dEdegZ41_Z41 && passed_gate_cut_sci42E_Z41;
};

bool FrsGate::Passed_Z21vsAoQs1s2(double Z21, double AoQs1s2)
{
    bool passed_gate_cut_Z21_AoQs1s2 = false;
    if (cut_Z21_AoQs1s2 != nullptr) passed_gate_cut_Z21_AoQs1s2 = cut_Z21_AoQs1s2->IsInside(AoQs1s2, Z21);
    else passed_gate_cut_Z21_AoQs1s2 = true;
    
    return passed_gate_cut_Z21_AoQs1s2;
}

bool FrsGate::Passed_Z41vsAoQs2s4(double Z41, double AoQs2s4)
{
    bool passed_gate_cut_Z41_AoQs2s4 = false;
    if (cut_Z41_AoQs2s4 != nullptr) passed_gate_cut_Z41_AoQs2s4 = cut_Z41_AoQs2s4->IsInside(AoQs2s4, Z41);
    else passed_gate_cut_Z41_AoQs2s4 = true;
    
    return passed_gate_cut_Z41_AoQs2s4;
}

bool FrsGate::Passed_Z42vsAoQs2s4(double Z42, double AoQs2s4)
{
    bool passed_gate_cut_Z42_AoQs2s4 = false;
    if (cut_Z42_AoQs2s4 != nullptr) passed_gate_cut_Z42_AoQs2s4 = cut_Z42_AoQs2s4->IsInside(AoQs2s4, Z42);
    else passed_gate_cut_Z42_AoQs2s4 = true;
    
    return passed_gate_cut_Z42_AoQs2s4;
}

bool FrsGate::Passed_Z21vsZ41(double Z21, double Z41)
{
    bool passed_gate_cut_Z21_Z41 = false;
    if (cut_Z21_Z41 != nullptr) passed_gate_cut_Z21_Z41 = cut_Z21_Z41->IsInside(Z41, Z21);
    else passed_gate_cut_Z21_Z41 = true;
    
    return passed_gate_cut_Z21_Z41;
}

bool FrsGate::Passed_Z41vsZ42(double Z41, double Z42)
{
    bool passed_gate_cut_Z41_Z42 = false;
    if (cut_Z41_Z42 != nullptr) passed_gate_cut_Z41_Z42 = cut_Z41_Z42->IsInside(Z42, Z41);
    else passed_gate_cut_Z41_Z42 = true;
    
    return passed_gate_cut_Z41_Z42;
}

bool FrsGate::Passed_x2vsAoQs2s4(double x2, double AoQs2s4)
{
    bool passed_gate_cut_x2_AoQs2s4 = false;
    if (cut_x2_AoQs2s4 != nullptr) passed_gate_cut_x2_AoQs2s4 = cut_x2_AoQs2s4->IsInside(AoQs2s4, x2);
    else passed_gate_cut_x2_AoQs2s4 = true;
    
    return passed_gate_cut_x2_AoQs2s4;
}

bool FrsGate::Passed_x4vsAoQs2s4(double x4, double AoQs2s4)
{
    bool passed_gate_cut_x4_AoQs2s4 = false;
    if (cut_x4_AoQs2s4 != nullptr) passed_gate_cut_x4_AoQs2s4 = cut_x4_AoQs2s4->IsInside(AoQs2s4, x4);
    else passed_gate_cut_x4_AoQs2s4 = true;
    
    return passed_gate_cut_x4_AoQs2s4;
}

bool FrsGate::Passed_x2vsAoQs1s2(double x2, double AoQs1s2)
{
    bool passed_gate_cut_x2_AoQs1s2 = false;
    if (cut_x2_AoQs1s2 != nullptr) passed_gate_cut_x2_AoQs1s2 = cut_x2_AoQs1s2->IsInside(AoQs1s2, x2);
    else passed_gate_cut_x2_AoQs1s2 = true;
    
    return passed_gate_cut_x2_AoQs1s2;
}

bool FrsGate::Passed_dEdegZ41vsZ41(double Z41, double dEdegZ41)
{
    bool passed_gate_cut_dEdegZ41_Z41 = false;
    if (cut_dEdegZ41_Z41 != nullptr) passed_gate_cut_dEdegZ41_Z41 = cut_dEdegZ41_Z41->IsInside(dEdegZ41, Z41);
    else passed_gate_cut_dEdegZ41_Z41 = true;
    
    return passed_gate_cut_dEdegZ41_Z41;
}

bool FrsGate::Passed_sci42EvsZ41(double Z41, double sci42E)
{
    bool passed_gate_cut_sci42E_Z41 = false;
    if (cut_sci42E_Z41 != nullptr) passed_gate_cut_sci42E_Z41 = cut_sci42E_Z41->IsInside(sci42E, Z41);
    else passed_gate_cut_sci42E_Z41 = true;
    
    return passed_gate_cut_sci42E_Z41;
}

bool FrsGate::Passed_Z41vsAoQs2s4_driftcorr(double Z41_driftcorr, double AoQs2s4_driftcorr)
{
    bool passed_gate_cut_Z41_AoQs2s4_driftcorr = false;
    if (cut_Z41_AoQs2s4_driftcorr != nullptr) passed_gate_cut_Z41_AoQs2s4_driftcorr = cut_Z41_AoQs2s4_driftcorr->IsInside(AoQs2s4_driftcorr, Z41_driftcorr);
    else passed_gate_cut_Z41_AoQs2s4_driftcorr = true;
    
    return passed_gate_cut_Z41_AoQs2s4_driftcorr;
}


ClassImp(FrsGate)
