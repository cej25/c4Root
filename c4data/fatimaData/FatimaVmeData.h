#ifndef FatimaVmeData_H
#define FatimaVmeData_H

#include "TObject.h"

class FatimaVmeData : public TObject
{
    public:
        FatimaVmeData();

        FatimaVmeData(uint64_t wr_t);

        virtual ~FatimaVmeData() {}

        // Getters

        // Setters

    protected:

        // stuff

        uint64_t fwr_t;

    public:
        ClassDef(FatimaVmeData, 1)
};

#endif