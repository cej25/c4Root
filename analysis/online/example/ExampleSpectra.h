#ifndef ExampleSpectra_H
#define ExampleSpectra_H

#include "EventHeader.h"
#include "FatimaTwinpeaksCalData.h"
#include "FairTask.h"
#include "TH1.h"
#include <Rtypes.h>
#include "TFolder.h"
#include "TClonesArray.h"
#include "TDirectory.h"

class TH1;
class TDirectory;
class TFolder;
class TClonesArray;

class ExampleSpectra : public FairTask
{
    public:
        // Constructors
        ExampleSpectra();
        ExampleSpectra(const TString& name, Int_t verbose = 1);

        // Destructor
        virtual ~ExampleSpectra();
        
        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        void FinishEvent();

        void FinishTask();

    private:

        EventHeader* header;
        Int_t fNEvents;

        // Data branches
        TClonesArray* fatimaCalData;

        // Directories;
        TFolder* histograms;
        TDirectory* dir_example;

        // Histograms
        TH1* h1_fat_energy;

};



#endif