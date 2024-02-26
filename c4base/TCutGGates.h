#ifndef TCutGGates_H
#define TCutGGates_H

#include <vector>
#include "TCutG.h"

struct Point
{
    int index;
    double x;
    double y;
    
};

class TCutGGates : public TNamed
{
    public:
        TCutGGates(const std::string& type,
                const std::vector<std::string>& gate_files,
                const std::string& path);

        ~TCutGGates() {};

    public:

        std::vector<TCutG*> Gates;
        std::string Type;


    public:
        ClassDef(TCutGGates, 1)
};

#endif