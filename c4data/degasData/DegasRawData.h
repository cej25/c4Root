#ifndef DEGAS_RAW_DATA_H
#define DEGAS_RAW_DATA_H

#include "FebexRawData.h"

#include <vector>

// One detector object per event, with one collection per electronics chain.
class DegasRawData : public TObject
{
public:
    std::vector<FebexRawData> FEBEX;

    ClassDef(DegasRawData, 1);
};

#endif
