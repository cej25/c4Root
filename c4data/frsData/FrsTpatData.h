#ifndef FrsTpatData_H
#define FrsTpatData_H

#include <vector>
#include "TObject.h"
#include "c4Logger.h"

class FrsTpatData : public TObject
{
    public:
        FrsTpatData();

        virtual ~FrsTpatData();

        inline uint64_t Get_wr_t() const { return fwr_t; }
        inline uint16_t Get_tpat() const { return ftpat; }

        inline void Set_wr_t(uint64_t wr) { fwr_t = wr; }
        inline void Set_tpat(uint16_t tpat) { ftpat = tpat; }
        
    private:

        uint64_t fwr_t;
        uint16_t ftpat;

    public:
        ClassDef(FrsTpatData, 1);
    
};


#endif