#ifndef FrsFatimaCorrelations_H
#define FrsFatimaCorrelations_H

#include "FairTask.h"

#include "FrsHitData.h"
#include "FatimaTwinpeaksCalData.h"
#include "TCorrelationsConfiguration.h"
#include "TFatimaTwinpeaksConfiguration.h"

#include "TFolder.h"
#include "TH1.h"
#include "TH2.h"
#include "TClonesArray.h"
#include "TCutG.h"
#include "TCutGGates.h"
#include <vector>

class TClonesArray;
class TFolder;
class TH1F;
class TH1D;
class TH2D;
class EventHeader;
class TCutG;
class TCutGGates;
class FrsHitData;
class FatimaTwinpeaksCalData;

class FrsFatimaCorrelations : public FairTask
{
    public:
        FrsFatimaCorrelations(std::vector<TCutGGates*> fFrsGates,
                            TCutGGates* fFatimaPromptGates);
        virtual ~FrsFatimaCorrelations();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        
        virtual void FinishTask();

    private:

        TCorrelationsConfiguration const* correl_config;
        TFatimaTwinpeaksConfiguration const* fatima_config;
        std::map<std::string, std::vector<int>> Correl;

        Int_t fNEvents;
        EventHeader* header;

        TClonesArray* fHitFatimaTwinpeaksArray;
        TClonesArray* fHitFrsArray;

        // Gates
        std::vector<TCutG*> cutID_Z_AoQ;
        std::vector<TCutG*> cutID_Z_Z2;
        std::vector<TCutG*> cutID_x2AoQ;
        std::vector<TCutG*> cutID_x4AoQ;
        std::vector<TCutG*> cutID_dEdegZ;
        
        std::vector<TCutG*> cutFatima_EdT;

        // Folders
        TFolder* folder_correlations;
        TFolder* folder_frs_fatima_corr;
        TFolder* folder_frs_fatima_corr_ZAoQgated;
        TFolder* folder_frs_fatima_corr_Z1Z2x2AoQgated;
        TFolder* folder_frs_fatima_corr_Z1Z2x4AoQgated;

        // Histograms
        TH1D* h1_FRS_Fatima_LT1_start_stop;
        TH1D* h1_FRS_Fatima_LT1_start_stop_ns;
        TH1D* h1_FRS_Fatima_LT2_start_stop;
        TH1D* h1_FRS_Fatima_LT2_start_stop_ns;
        TH1D* h1_FRS_Fatima_LT3_start_stop;
        TH1D* h1_FRS_Fatima_LT3_start_stop_ns;
        TH1D* h1_FRS_Fatima_LT1_stop_start;
        TH1D* h1_FRS_Fatima_LT1_stop_start_ns;
        TH1D* h1_FRS_Fatima_LT2_stop_start;
        TH1D* h1_FRS_Fatima_LT2_stop_start_ns;
        TH1D* h1_FRS_Fatima_LT3_stop_start;
        TH1D* h1_FRS_Fatima_LT3_stop_start_ns;
        std::vector<TH1F*> h1_FRS_FatimaE_ZAoQgate;
        std::vector<TH2D*> h2_FRS_FatimaEvsT_ZAoQgate;
        std::vector<TH2D*> h2_FRS_FatimaE1vsE2_ZAoQgate;
        std::vector<TH1F*> h1_FRS_FatimaE_Z1Z2x2AoQgate;
        std::vector<TH2D*> h2_FRS_FatimaEvsT_Z1Z2x2AoQgate;
        std::vector<TH2D*> h2_FRS_FatimaE1vsE2_Z1Z2x2AoQgate;
        std::vector<TH1F*> h1_FRS_FatimaE_Z1Z2x4AoQgate;
        std::vector<TH2D*> h2_FRS_FatimaEvsT_Z1Z2x4AoQgate;
        std::vector<TH2D*> h2_FRS_FatimaE1vsE2_Z1Z2x4AoQgate;

        // Variables
        Long64_t Fatima_time_mins;

        

    public:
        ClassDef(FrsFatimaCorrelations, 1)
};


#endif
