#ifndef CorrelationsMap_H
#define CorrelationsMap_H

#include <map>
#include <vector>
#include <string>

class CorrelationsMap : public std::map<std::string, std::vector<int>>
{
    public:
        CorrelationsMap(std::string& filename);
        ~CorrelationsMap();
    

};


#endif