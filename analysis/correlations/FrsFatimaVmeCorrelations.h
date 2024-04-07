#ifndef FrsFatimaVmeCorrelations_H
#define FrsFatimaVmeCorrelations_H


#include "FairTask.h"

#include "FrsHitData.h"
#include "FatimaVmeCalData.h"
#include "TCorrelationsConfiguration.h"
#include "TFatimaVmeConfiguration.h"

#include "TFolder.h"
#include "TH1.h"
#include "TH2.h"
#include "TClonesArray.h"
#include "TCutG.h"
#include "TCutGGates.h"
#include <vector>
#include <map>

class TClonesArray;
class TFolder;
class TH1F;
class TH1D;
class TH2D;
class EventHeader;
class TCutG;
class TCutGGates;
class FrsHitData;
class FatimaVmeCalData;

class FrsFatimaVmeCorrelations : public FairTask
{
    public:
        FrsFatimaVmeCorrelations(std::vector<TCutGGates*> fFrsGates,
                            TCutGGates* fFatimaPromptGates);
        virtual ~FrsFatimaVmeCorrelations();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        
        virtual void FinishTask();

    private:

        TCorrelationsConfiguration const* correl_config;
        TFatimaVmeConfiguration const* fatima_config;
        std::map<std::string, std::vector<int>> Correl;

        Int_t fNEvents;
        EventHeader* header;

        TClonesArray* fHitFatimaVmeArray;
        TClonesArray* fHitFrsArray;

        // Gates
        std::vector<TCutG*> cutID_Z_AoQ;
        std::vector<TCutG*> cutID_Z_Z2;
        std::vector<TCutG*> cutID_x2AoQ;
        std::vector<TCutG*> cutID_x4AoQ;
        std::vector<TCutG*> cutID_dEdegZ;
        
        std::vector<TCutG*> cutFatVME_EdT;

        // Folders
        TFolder* folder_correlations;
        TFolder* folder_frs_fatimavme_corr;
        TFolder* folder_frs_fatimavme_corr_ZAoQgated;
        TFolder* folder_frs_fatimavme_corr_Z1Z2x2AoQgated;
        TFolder* folder_frs_fatimavme_corr_Z1Z2x4AoQgated;

        // Histograms
        TH1D* h1_FRS_FatVME_LT1_start_stop;
        TH1D* h1_FRS_FatVME_LT1_start_stop_ns;
        TH1D* h1_FRS_FatVME_LT2_start_stop;
        TH1D* h1_FRS_FatVME_LT2_start_stop_ns;
        TH1D* h1_FRS_FatVME_LT3_start_stop;
        TH1D* h1_FRS_FatVME_LT3_start_stop_ns;
        TH1D* h1_FRS_FatVME_LT1_stop_start;
        TH1D* h1_FRS_FatVME_LT1_stop_start_ns;
        TH1D* h1_FRS_FatVME_LT2_stop_start;
        TH1D* h1_FRS_FatVME_LT2_stop_start_ns;
        TH1D* h1_FRS_FatVME_LT3_stop_start;
        TH1D* h1_FRS_FatVME_LT3_stop_start_ns;
        std::vector<TH1F*> h1_FRS_FatVME_E_ZAoQgate;
        std::vector<TH2D*> h2_FRS_FatVME_EvsT_ZAoQgate;
        std::vector<TH2D*> h2_FRS_FatVME_E1vsE2_ZAoQgate;
        std::vector<TH1F*> h1_FRS_FatVME_E_Z1Z2x2AoQgate;
        std::vector<TH2D*> h2_FRS_FatVME_EvsT_Z1Z2x2AoQgate;
        std::vector<TH2D*> h2_FRS_FatVME_E1vsE2_Z1Z2x2AoQgate;
        std::vector<TH1F*> h1_FRS_FatVME_E_Z1Z2x4AoQgate;
        std::vector<TH2D*> h2_FRS_FatVME_EvsT_Z1Z2x4AoQgate;
        std::vector<TH2D*> h2_FRS_FatVME_E1vsE2_Z1Z2x4AoQgate;

        // Variables
        Long64_t FatVME_time_mins;

        

    public:
        ClassDef(FrsFatimaVmeCorrelations, 1)
};

#endif