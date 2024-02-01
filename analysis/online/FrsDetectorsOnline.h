#ifndef FrsDetectorsOnline_H
#define FrsDetectorsOnline_H 1

#include "FairTask.h"
#include "TH1.h"
#include "TH2.h"

class TClonesArray;
class EventHeader;
class FrsHitData;
class FrsMainCalData;
class FrsUserCalData;
class FrsTPCCalData;
class FrsVFTXCalData;
class TCanvas;
class TH1F;
class TH2F;

class FrsDetectorsOnline : public FairTask
{
    public:
        FrsDetectorsOnline();

        FrsDetectorsOnline(const TString& name, Int_t verbose = 1);

        virtual ~FrsDetectorsOnline();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();


    private:
        TClonesArray* fFrsUserCalArray; // array with hit items
        TClonesArray* fFrsMainCalArray; // array with hit items
        TClonesArray* fFrsTPCCalArray; // array with hit items
        TClonesArray* fFrsVFTXCalArray; // array with hit items

        FrsUserCalData* fHitFrsUserCal; // array with hit items
        FrsMainCalData* fHitFrsMainCal; // array with hit items
        FrsTPCCalData* fHitFrsTPCCal; // array with hit items
        FrsVFTXCalData* fHitFrsVFTXCal; // array with hit items

   
        // check for trigger should be done globally, somewhere else
        EventHeader* header;
        Int_t fNEvents;

        // Canvas

        // Histograms for detecors:

        //SCI delta E
        TH1D * h_sci_21l_de;
        TH1D * h_sci_21r_de;
        TH1D * h_sci_22l_de;
        TH1D * h_sci_22r_de;
        TH1D * h_sci_41l_de;
        TH1D * h_sci_41r_de;
        TH1D * h_sci_42l_de;
        TH1D * h_sci_42r_de;
        TH1D * h_sci_43l_de;
        TH1D * h_sci_43r_de;
        TH1D * h_sci_81l_de;
        TH1D * h_sci_81r_de;
        //SCI t
        TH1D * h_sci_21l_t;
        TH1D * h_sci_21r_t;
        TH1D * h_sci_22l_t;
        TH1D * h_sci_22r_t;
        TH1D * h_sci_41l_t;
        TH1D * h_sci_41r_t;
        TH1D * h_sci_42l_t;
        TH1D * h_sci_42r_t;
        TH1D * h_sci_43l_t;
        TH1D * h_sci_43r_t;
        TH1D * h_sci_81l_t;
        TH1D * h_sci_81r_t;

        //MUSIC timing:
        TH2D * h_music41_t;
        TH2D * h_music42_t;



    public:
        ClassDef(FrsDetectorsOnline, 1)

};

#endif