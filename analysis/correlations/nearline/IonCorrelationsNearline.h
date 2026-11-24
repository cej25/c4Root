#ifndef ION_CORRELATIONS_NEARLINE_H
#define ION_CORRELATIONS_NEARLINE_H

#include "IonCorrelations.h"

class IonCorrelationsNearline : public IonCorrelations
{
public:
    explicit IonCorrelationsNearline(const char* name = "IonCorrelationsNearline");
    ClassDefOverride(IonCorrelationsNearline, 0);
};

#endif
