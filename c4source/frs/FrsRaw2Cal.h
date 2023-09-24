
#ifndef FrsRaw2Cal_H
#define FrsRaw2Cal_H 1

// FairRoot
#include "FairTask.h"

// c4
#include "FrsCalData.h"

#include <Rtypes.h>

class TClonesArray;
class FrsMappingPar; // ??

class FrsRaw2Cal : public FairTask
{
  public:
    /** Default constructor **/
    FrsRaw2Cal();

    /** Standard constructor **/
    FrsRaw2Cal(const TString& name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FrsRaw2Cal();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* option) override;

    /** Virtual method Reset **/
    virtual void Reset();

    virtual void SetParContainers() override;

    // Fair specific
    /** Virtual method Init **/
    virtual InitStatus Init() override;

    /** Virtual method ReInit **/
    virtual InitStatus ReInit() override;

    // Method to setup online mode
    void SetOnline(Bool_t option) { fOnline = option; }

  private:
    void SetParameter();
    int GetCol(int reg, int dcol, int ads);
    int GetRow(int ads);

    Bool_t fOnline; // Don't store data for online

    FrsMappingPar* fMap_Par; // Par container (setup.C?)
    TClonesArray* fFrsData;
    TClonesArray* fFrsCalData;

    // Private method AddCalData
    FrsCalData* AddCalData(UShort_t senId, Int_t col, Int_t row);

  public:
    // Class definition
    ClassDefOverride(FrsRaw2Cal, 1)
};

#endif /*  FrsRaw2Cal_H */
