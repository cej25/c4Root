#ifndef ION_CORRELATIONS_ONLINE_H
#define ION_CORRELATIONS_ONLINE_H

#include "IonCorrelations.h"

class IonCorrelationsOnline : public IonCorrelations
{
public:
    explicit IonCorrelationsOnline(const char* name = "IonCorrelationsOnline");
    ClassDefOverride(IonCorrelationsOnline, 0);
};

#endif
