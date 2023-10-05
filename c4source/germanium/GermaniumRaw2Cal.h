#ifndef GermaniumRaw2Cal_H
#define GermaniumRaw2Cal_H

#include "FairTask.h"

#include "GermaniumFebexCalData.h"
#include "GermaniumFebexData.h"

#include <TRandom.h>

class TClonesArray;

class GermaniumRaw2Cal : public FairTask
{
    public:
        GermaniumRaw2Cal();

        virtual ~GermaniumRaw2Cal();

        virtual void Exec(Option_t* option);

        virtual void Reset();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual InitStatus ReInit();

        void SetOnline(Bool_t option) { fOnline = option; }

    private:
        void SetParameter();

        GermaniumFebexData* funcal_hit;
        GermaniumFebexCalData* funcal_hit;

        EventHeader * header;
        Int_t fNEvents;

        // stuff for Germaniums
        Int_t fNumCrystals;
        Int_t fNumDets;

        double *** calibration_coefficients; // [detector_id][cluster_id][a0,a1,a2...]

        // private Calibration Data method

    public:
        ClassDef(GermaniumRaw2Cal, 1)
};

#endif /* GermaniumRaw2Cal_H */

