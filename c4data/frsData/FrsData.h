#ifndef FrsData_H
#define FrsData_H
#include "TObject.h"

class FrsData : public TObject
{
    public:
        // Default Constructor
        FrsData();

        FrsData(int sc1, UInt_t ScFrs, int sc2, UInt_t ScMain);

        // Destructor
        virtual ~FrsData() {}

        // Getters
        inline const UInt_t GetScFrs() const { return fScFrs; }
        inline const UInt_t GetScMain() const { return fScMain; }
       
        // Setters
        void SetScFrs(UInt_t v) { fScFrs = v; }
        void SetScMain(UInt_t v) { fScMain = v; }



    protected:
        int iScFrs, iScMain;
        UInt_t fScFrs, fScMain;


    public:
        ClassDef(FrsData, 1)
};

#endif
