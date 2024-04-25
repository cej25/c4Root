#ifndef FrsBplastCorrelations_H
#define FrsBplastCorrelations_H

#include "FairTask.h"
#include "TH2D.h"

#include "TbPlastConfiguration.h"
#include "TFrsConfiguration.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH2D;
class TFile;
class TFolder;
class FrsGate;

class FrsBplastCorrelations : public FairTask
{
    public:
        FrsBplastCorrelations();
        FrsBplastCorrelations(FrsGate* frsgate);
        FrsBplastCorrelations(const TString& name, Int_t verbose = 1);

        virtual ~FrsBplastCorrelations();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();


    
    private:
        TClonesArray* fHitbPlast;
        TClonesArray* fHitFrs;

        TbPlastConfiguration const* bplast_config;
        TFrsConfiguration const* frs_config;
        
        FrsGate* frsgate;

        EventHeader* header;
        Int_t fNEvents;

        TDirectory* dir_frs;
        TDirectory* dir_frs_bplast_corrs;
        
        TH2D* h2_Z_vs_slowToT;

        bool frs_dir_found = true;

    public:
        ClassDef(FrsBplastCorrelations, 1)
};

#endif