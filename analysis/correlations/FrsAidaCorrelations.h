#ifndef FrsAidaCorrelations_H
#define FrsAidaCorrelations_H

#include "TAidaConfiguration.h"
#include "TFrsConfiguration.h"
#include "TCorrelationsConfiguration.h"
#include "AidaHitData.h"
#include "FrsHitData.h"

#include "TClonesArray.h"
#include "TH1.h"
#include "TH2.h"
#include "FrsGate.h"
#include "TDirectory.h"
#include <map>
#include <vector>

class TClonesArray;
class EventHeader;
class AidaHit;
class TH1I;
class TH2I;
class TH2F;
class TH2D;
class TCutG;
class FrsHitData;
class FrsAnalysisData;
class TAidaConfiguration;
class TFrsConfiguration;
class TCorrelationsConfiguration;
class TFolder;
class TDirectory;
class FrsGate;

class FrsAidaCorrelations : public FairTask
{
    public:
        FrsAidaCorrelations(std::vector<FrsGate*> fg);

        FrsAidaCorrelations(const TString& name, Int_t verbose);

        virtual ~FrsAidaCorrelations();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();

    private:
        TAidaConfiguration const* aida_config;
        TFrsConfiguration const* frs_config;
        TCorrelationsConfiguration const* correl_config;
        std::map<std::string, std::vector<int>> Correl;

        std::vector<FrsHitItem> const* hitArrayFrs;
        std::vector<AidaHit> const* fAidaImplants;

        Int_t fNEvents;
        EventHeader* header;

        bool found_dir_frs = true;

        std::vector<FrsGate*> FrsGates;

        TDirectory* dir_frs;
        TDirectory* dir_frs_aida_corrs;
        TDirectory* dir_implant_corrs;
        TDirectory* dir_stopped_implant_corrs;
        TDirectory* dir_implant_corrs_ZvsAoQ;
        TDirectory* dir_implant_corrs_Z1vsZ2;
        TDirectory* dir_implant_corrs_x2vsAoQ;
        TDirectory* dir_implant_corrs_x4vsAoQ;
        TDirectory* dir_implant_corrs_ZvsAoQ_stopped;
        TDirectory* dir_implant_corrs_Z1vsZ2_stopped;
        TDirectory* dir_implant_corrs_x2vsAoQ_stopped;
        TDirectory* dir_implant_corrs_x4vsAoQ_stopped;
        TDirectory* dir_implant_corrs_Z1Z2_x2vsAoQ;
        TDirectory* dir_implant_corrs_Z1Z2_x4vsAoQ;
        TDirectory* dir_implant_corrs_Z1Z2_x2vsAoQ_stopped;
        TDirectory* dir_implant_corrs_Z1Z2_x4vsAoQ_stopped;

    

        bool frs_dir_found = true;

        // Variables
        Long64_t AidaLastWR;

        // Histograms
        TH1I* h1_AidaImplant_Deadtime;
        TH1I* h1_AidaImplant_FRS_dT;
        TH2F* h2_AidaImplant_FRS_x_vs_x4;
        std::vector<std::vector<TH2I*>> h2_AidaImplant_FRS_ZAoQgate_strip_xy;
        std::vector<std::vector<TH1I*>> h1_AidaImplant_FRS_ZAoQgate_e;
        std::vector<std::vector<TH2D*>> h2_AidaImplant_FRS_ZAoQgate_position;
        std::vector<std::vector<TH2I*>> h2_AidaImplant_FRS_Z1Z2gate_strip_xy;
        std::vector<std::vector<TH2D*>> h2_AidaImplant_FRS_Z1Z2gate_position;
        std::vector<std::vector<TH2I*>> h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy;
        std::vector<std::vector<TH2D*>> h2_AidaImplant_FRS_Z1Z2x2AoQgates_position;
        std::vector<std::vector<TH1I*>> h1_AidaImplant_FRS_Z1Z2x2AoQgates_e;
        std::vector<std::vector<TH2I*>> h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy;
        std::vector<std::vector<TH2D*>> h2_AidaImplant_FRS_Z1Z2x4AoQgates_position;
        std::vector<std::vector<TH1I*>> h1_AidaImplant_FRS_Z1Z2x4AoQgates_e;
        std::vector<std::vector<TH2I*>> h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped;
        std::vector<std::vector<TH1I*>> h1_AidaImplant_FRS_ZAoQgate_e_stopped;
        std::vector<std::vector<TH2D*>> h2_AidaImplant_FRS_ZAoQgate_position_stopped;
        std::vector<std::vector<TH2I*>> h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped;
        std::vector<std::vector<TH2D*>> h2_AidaImplant_FRS_Z1Z2gate_position_stopped;
        std::vector<std::vector<TH2I*>> h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped;
        std::vector<std::vector<TH2D*>> h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped;
        std::vector<std::vector<TH1I*>> h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped;
        std::vector<std::vector<TH2I*>> h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped;
        std::vector<std::vector<TH2D*>> h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped;
        std::vector<std::vector<TH1I*>> h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped;

    public:
        ClassDef(FrsAidaCorrelations, 1)
};



#endif
