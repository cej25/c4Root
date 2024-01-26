#ifndef FrsVFTXData_H
#define FrsVFTXData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class TClonesArray;

class FrsVFTXData : public TObject
{
    public:
        FrsVFTXData();

        //FrsVFTXData(/*overload*/);
        
        virtual ~FrsVFTXData() {}

        // Getters

        // Setters
    
    private:

    public:
        ClassDef(FrsVFTXData, 1)
};


#endif