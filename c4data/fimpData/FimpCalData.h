#ifndef FimpCalData_H
#define FimpCalData_H

#include "TObject.h"

class FimpCalItem : public TObject
{
    public:
        FimpCalItem();

        void SetAll();
        void Reset();

        ClassDefNV(FimpCalItem, 2);
    
    private:
        // members
};


#endif