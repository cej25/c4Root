#ifndef R3BFrsMappedData_H
#define R3BFrsMappedData_H

#include "TObject.h"

class R3BFrsMappedData : public TObject
{
    public:
        R3BFrsMappedData();

        // now this must be understood
        // Float_t Float_t
        R3BFrsMappedData(Float_t Z, Float_t fAoQ_corr, unsigned int fTrigger); 

        virtual ~R3BFrsMappedData() {}

        // Float_t Float_t
        inline const Float_t& GetZ() const { return fZ; }
        inline const Float_t& GetAoQ_corr() const { return fAoQ_corr; }
        inline const unsigned int& GetTrigger() const { return fTrigger; }

    protected:
        // Float_t Float_t
        Float_t fZ; // ?
        Float_t fAoQ_corr; // ?
        unsigned int fTrigger;
    
    public:
        ClassDef(R3BFrsMappedData, 1);

};

#endif
