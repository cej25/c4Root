#ifndef FrsAidaCorrelationsOnline_H
#define FrsAidaCorrelationsOnline_H

#include "TAidaConfiguration.h"
#include "TFrsConfiguration.h"
#include "TCorrelationsConfiguration.h"
#include "AidaHitData.h"
#include "../../config/setup.h"
#include "FrsGate.h"

#include "TClonesArray.h"
#include "TH1.h"
#include "TH2.h"
#include "TCutG.h"
#include "TFolder.h"
#include <vector>
#include <map>

class TClonesArray;
class EventHeader;
class AidaHit;
class TH1I;
class TH2I;
class TH2F;
class TH2D;
class FrsHitData;
class TAidaConfiguration;
class TFrsConfiguration;
class TCorrelationsConfiguration;
class TFolder;
class TDirectory;
class FrsGate;

class FrsAidaCorrelationsOnline : public FairTask
{
    public:
        FrsAidaCorrelationsOnline(std::vector<FrsGate*> fg);

        FrsAidaCorrelationsOnline(const TString& name, Int_t verbose);

        virtual ~FrsAidaCorrelationsOnline();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();

    private:

        TAidaConfiguration const* aida_config;
        TFrsConfiguration const* frs_config;
        TCorrelationsConfiguration const* correl_config;
        std::map<std::string, std::vector<int>> Correl;

        std::vector<FrsGate*> FrsGates;

        TClonesArray* fFrsHitArray;
        std::vector<AidaHit> const* fAidaImplants;

        Int_t fNEvents;
        EventHeader* header;

        TFolder* histograms;
        TDirectory* dir_frs;
        TDirectory* dir_frs_aida_corr;
        // TDirectory* 

        TH1I* h1_stopped_implanted_passed_gate;
        int** stopped_implant_passed_gate_count;


       
        

    public:
        ClassDef(FrsAidaCorrelationsOnline, 1)
};



#endif
