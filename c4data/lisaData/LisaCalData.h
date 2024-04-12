#ifndef LisaCalData_H
#define LisaCalData_H

#include "TObject.h"
#include <vector>

class LisaCalData : public TObject
{
    public:
        LisaCalData();
        
        virtual ~LisaCalData() {};

        // Getters
        inline uint64_t Get_wr_t() const { return fwr_t; }
        


        // Setters
        inline void Set_wr_t(uint64_t wr) { fwr_t = wr; }

    protected:

        // variables
        uint64_t fwr_t;


    
    public:
        ClassDef(LisaCalData, 1);
};


#endif