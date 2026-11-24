#ifndef bPlastDegasCorrelations_H
#define bPlastDegasCorrelations_H

#include "FairTask.h"
#include "TDirectory.h"
#include "TFolder.h"
#include "TFile.h"
#include <vector>
#include "TH1.h"
#include "TClonesArray.h"

#include "bPlastTwinpeaksCalData.h"
#include "TbPlastConfiguration.h"
#include "DegasCalData.h"
#include "TDegasConfiguration.h"

class TClonesArray;
class EventHeader;
class TDirectory;
class TH1F;

class bPlastDegasCorrelations : public FairTask
{
    public:
        bPlastDegasCorrelations();
        bPlastDegasCorrelations(const TString& name, Int_t verbose = 1);

        virtual ~bPlastDegasCorrelations();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();


    private:
        TDegasConfiguration const* degas_config;
        TbPlastConfiguration const* bplast_config;

        TClonesArray* fHitbPlastTwinpeaks;
        TClonesArray* fHitDegas;

        EventHeader* header;
        Int_t fNEvents;

        TDirectory* dir_degas;
        TDirectory* dir_bplast_degas_corrs;

        std::vector<TH1F*> h1_degas_energy_bplast_corr;
        TH1F* h1_degas_energy_bplast_corr_sum;

        std::vector<std::pair<int,int>> crystals_to_plot;

        int number_of_detectors_to_plot;

        int fenergy_nbins = 1500;
        int fenergy_bin_low = 0;
        int fenergy_bin_high = 1500;


    public:
        ClassDef(bPlastDegasCorrelations, 1)
};


#endif
