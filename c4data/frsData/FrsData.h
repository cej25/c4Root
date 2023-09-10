#ifndef FrsData_H
#define FrsData_H
#include "TObject.h"

class FrsData : public TObject
{
    public:
        // Default Constructor
        FrsData();

        FrsData(Float_t Z,
                  Float_t AoQ,
                  Float_t a2,
                  Float_t a4,
                  Float_t x2,
                  Float_t x4,
                  Float_t beta);

        // Destructor
        virtual ~FrsData() {}

        // Getters
        inline const Float_t GetZ() const { return fZ; }
        inline const Float_t GetAoQ() const { return fAoQ; }
        inline const Float_t GetA2() const { return fA2; }
        inline const Float_t GetA4() const { return fA4; }
        inline const Float_t GetX2() const { return fX2; }
        inline const Float_t GetX4() const { return fX4; }
        inline const Float_t GetBeta() const { return fBeta; }
        //inline const Double_t GetBrho0() const { return fBrho0; }
        //inline const Double_t GetBhro1() const { return fBrho1; }

        // Setters
        void SetZ(Float_t v) { fZ = v; }
        void SetAoQ(Float_t v) { fAoQ = v; }
        void SetA2(Float_t v) { fA2 = v; }
        void SetA4(Float_t v) { fA4 = v; }
        void SetX2(Float_t v) { fX2 = v; }
        void SetX4(Float_t v) { fX4 = v; }
        void SetBeta(Float_t v) { fBeta = v; }
        //void SetBrho0(Float_t v) { fBrho0 = v; }
        //void SetBrho1(Float_t v) { fBrho1 = v; }


    protected:
        Float_t fZ;
        Float_t fAoQ, fA2, fA4, fX2, fX4;
        Float_t fBeta;//, fBrho0, fBrho1;


    public:
        ClassDef(FrsData, 1)
};

#endif
