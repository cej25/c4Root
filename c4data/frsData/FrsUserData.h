#ifndef FrsUserData_H
#define FrsUserData_H

#include "TObject.h"
#include "TClonesArray.h"
#include <vector>

class TClonesArray;

class FrsUserData : public TObject
{
    public:
        FrsUserData();

        //FrsUserData(/*overload*/);
        
        virtual ~FrsUserData() {}

        // Getters

        // Setters
    
    private:

    public:
        ClassDef(FrsUserData, 1)
};


#endif