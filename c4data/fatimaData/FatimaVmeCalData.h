#ifndef FatimaVmeCalData_H
#define FatimaVmeCalData_H

#include "TObject.h"
#include "../../config/setup.h"

class FatimaVmeCalData : public TObject
{
    public:
        FatimaVmeCalData();

        FatimaVmeCalData(uint64_t wr_t);

        virtual ~FatimaVmeCalData() {}

        // Getters

        // Setters
        

    protected:

        // stuff

        // board number != geo/board_id
        uint64_t fwr_t;


    public:
        ClassDef(FatimaVmeCalData, 1)
};

#endif