#include <iostream>
#include <vector>
#include "TFile.h"
#include "TCutG.h"
#include "TSystem.h"

void ReadGates(const char* type, const std::vector<std::string>& filenames, std::vector<TCutG*>& cutgVector, std::string& path)
{   
    for (const auto& filename : filenames)
    {
        std::string totpath = (".L " + path + filename).c_str();
        std::cout << totpath << std::endl;
        gROOT->ProcessLine((".L " + path + filename).c_str()); // Load the macro file
        TCutG* cutg = dynamic_cast<TCutG*>(gROOT->FindObject(filename.c_str()));
        if (cutg)
        {
            if (strcmp(type,"ZvsAoQ") == 0)
            {
                cutg->SetVarX("AoQ");
                cutg->SetVarY("Z");
            }
            else if (strcmp(type, "Z1vsZ2") == 0)
            {
                cutg->SetVarX("Z1");
                cutg->SetVarY("Z2");
            }
            else if (strcmp(type, "x2vsAoQ") == 0)
            {
                cutg->SetVarX("AoQ");
                cutg->SetVarY("x2");
            }
            else if (strcmp(type,"x4vsAoQ") == 0)
            {
                cutg->SetVarX("AoQ");
                cutg->SetVarY("x4");
            }
            else if (strcmp(type, "dEdegvsZ") == 0)
            {
                cutg->SetVarX("Z");
                cutg->SetVarY("dEdeg");
            }

            cutgVector.push_back(cutg);
            std::cout << "Added TCutG from file " << filename << ": " << cutg->GetName() << std::endl;
        }
        else
        {
            std::cerr << "Error: No TCutG object found in file " << filename << std::endl;
        }
    }
}