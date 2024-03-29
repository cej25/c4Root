

#include "TCutGGates.h"

#include "TFile.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TCutG.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <regex>
#include "c4Logger.h"

TCutGGates::TCutGGates(const std::string& type,
                    const std::vector<std::string>& gate_files,
                    const std::string& path)
{
    std::regex pattern("SetPoint\\((\\d+),([\\d.]+),([\\d.]+)\\);");

    Type = type;

    std::string totpath;

    int i = 0;
    for (const auto & filename : gate_files)
    {
        totpath = path + filename;
        std::ifstream file(totpath);
        std::string line;
        std::vector<Point> points;

        if (file.is_open())
        {
            while (std::getline(file, line))
            {
                std::smatch match;
                if (std::regex_search(line, match, pattern))
                {
                    int index = std::stoi(match[1]);
                    double x = std::stod(match[2]);
                    double y = std::stod(match[3]);
                    points.push_back({index, x, y});
                }
            }
            file.close();
        }
        else
        {
            c4LOG(warn, "Unable to open file: " + totpath);
        }

        // change this bit to grab the actual name for use later
        TCutG* cutg = new TCutG(filename.c_str(), points.size());
        for (const auto & point : points)
        {   
            cutg->SetPoint(point.index, point.x, point.y);
        }

        Gates.push_back(cutg);

        i++;
        
    }
}

ClassImp(TCutGGates)