#ifndef AidaUnpack2Cal_H
#define AidaUnpack2Cal_H

#include "AidaData.h"
#include "AidaCalData.h"
#include "FairTask.h"
#include "TAidaConfiguration.h"
#include <vector>


class AidaUnpack2Cal : public FairTask
{
public:
    AidaUnpack2Cal();
    virtual ~AidaUnpack2Cal();
    virtual void Exec(Option_t* option);
    virtual void SetParContainers();
    virtual InitStatus Init();
    void SetOnline(Bool_t option) { fOnline = option; }

private:
    std::vector<AidaUnpackAdcItem> const* unpackArray;
    std::vector<AidaCalAdcItem>* calArray;

    void SetParameter();
    bool fOnline;

    TAidaConfiguration const* conf;

public:
    ClassDef(AidaUnpack2Cal, 2)
};

#endif /* AidaUnpack2Cal_H */

