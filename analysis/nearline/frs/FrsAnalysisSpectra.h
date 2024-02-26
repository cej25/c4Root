#ifndef FrsAnalysisSpectra_H
#define FrsAnalysisSpectra_H

#include "../../../config/frs_config.h"
#include "FairTask.h"
#include "TFRSParameter.h"
#include "TH2.h"
#include "TH1.h"
#include "TCutG.h"
#include "TFolder.h"

class EventHeader;
class TClonesArray;
class FrsHitData;
class FrsAnalysisData;
class TH2D;
class TH2I;
class TH1I;
class TFolder;
class TCutG;
class TCutGGates;

class FrsAnalysisSpectra : public FairTask
{
    public:
        FrsAnalysisSpectra(TFRSParameter* ffrs,
                        TMWParameter* fmw,
                        TTPCParameter* ftpc,
                        TMUSICParameter* fmusic,
                        TLABRParameter* flabr,
                        TSCIParameter* fsci,
                        TIDParameter* fid,
                        TSIParameter* fsi,
                        TMRTOFMSParameter* fmrtof,
                        TRangeParameter* frange,
                        std::vector<TCutGGates*> fFrsGates);

        FrsAnalysisSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsAnalysisSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

    private:

        Int_t fNEvents;
        EventHeader* header;

        TClonesArray* fFrsHitArray;
        TClonesArray* fFrsAnalysisArray;

        TFRSParameter* frs;
        TMWParameter* mw;
        TTPCParameter* tpc;
        TMUSICParameter* music;
        TLABRParameter* labr;
        TSCIParameter* sci;
        TIDParameter* id;
        TSIParameter* si;
        TMRTOFMSParameter* mrtof;
        TRangeParameter* range;

        // folders
        TFolder* frs_analysis_hists;
        TFolder* frs_tac_hists;
        TFolder* frs_mhtdc_hists;
        TFolder* frs_ZvsAoQ_hists;
        TFolder* frs_Z1vsZ2_hists;
        TFolder* frs_x2vsAoQ_hists;
        TFolder* frs_x4vsAoQ_hists;
        TFolder* frs_dEdegvsZ_hists;
        TFolder* frs_x2vsAoQ_Z1vsZ2_hists;
        TFolder* frs_x4vsAoQ_Z1vsZ2_hists;
        TFolder* frs_ZvsAoQ_hists_mhtdc;
        TFolder* frs_Z1vsZ2_hists_mhtdc;
        TFolder* frs_x2vsAoQ_hists_mhtdc;
        TFolder* frs_x4vsAoQ_hists_mhtdc;
        TFolder* frs_dEdegvsZ_hists_mhtdc;
        TFolder* frs_x2vsAoQ_Z1vsZ2_hists_mhtdc;
        TFolder* frs_x4vsAoQ_Z1vsZ2_hists_mhtdc;

        // histograms
        TH2D* h2_Z1_vs_T;
        TH2D* h2_AoQ_vs_T;
        TH2D* h2_Z_vs_AoQ;
        TH2D* h2_Z_vs_AoQ_corr;
        TH2D* h2_Z_vs_Z2;
        TH2D* h2_Z_vs_AoQ_Zsame;
        TH2D* h2_x4_vs_AoQ_Zsame;
        TH2D* h2_x2_vs_AoQ_Zsame;
        TH2D* h2_x2_vs_AoQ;
        TH2D* h2_x4_vs_AoQ;
        TH2D* h2_dEdegoQ_vs_Z;
        TH2D* h2_dEdeg_vs_Z;
        TH2D* h2_a2_vs_AoQ;
        TH2D* h2_a4_vs_AoQ;
        TH2D* h2_Z_vs_dE2;
        TH2D* h2_x2_vs_x4;
        TH2D* h2_SC41dE_vs_AoQ;
        TH2D* h2_dE_vs_ToF;
        TH2D* h2_x2_vs_Z;
        TH2D* h2_x4_vs_Z;
        TH2D* h2_dE1_vs_x2;
        TH2D* h2_dE1_vs_x4;
        TH2D* h2_x2_vs_a2;
        TH2D* h2_y2_vs_b2;
        TH2D* h2_x4_vs_a4;
        TH2D* h2_y4_vs_b4;
        TH2D* h2_Z_vs_Sc21E;
        std::vector<TH2I*> h2_Z_vs_AoQ_ZAoQgate;
        std::vector<TH2I*> h2_Z1_vs_Z2_ZAoQgate;
        std::vector<TH2I*> h2_x2_vs_AoQ_ZAoQgate;
        std::vector<TH2I*> h2_x4_vs_AoQ_ZAoQgate;
        std::vector<TH2I*> h2_dEdeg_vs_Z_ZAoQgate;
        std::vector<TH2I*> h2_dedegoQ_vs_Z_ZAoQgate;
        std::vector<TH1I*> h1_a2_ZAoQ_gate;
        std::vector<TH1I*> h1_a4_ZAoQ_gate;
        std::vector<TH2I*> h2_dEdeg_vs_Z_Z1Z2gate;
        std::vector<TH2I*> h2_dEdegoQ_vs_Z_Z1Z2gate;
        std::vector<TH2I*> h2_Z1_vs_Z2_Z1Z2gate;
        std::vector<TH1I*> h1_a2_Z1Z2gate;
        std::vector<TH1I*> h1_a4_Z1Z2gate;
        std::vector<TH2I*> h2_x2_vs_AoQ_Z1Z2gate;
        std::vector<TH2I*> h2_x4_vs_AoQ_Z1Z2gate;
        std::vector<TH2I*> h2_Z_vs_AoQ_Z1Z2gate;
        std::vector<TH2I*> h2_x2_vs_AoQ_x2AoQgate;
        std::vector<TH2I*> h2_Z1_vs_Z2_x2AoQgate;
        std::vector<TH2I*> h2_x2_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2I*> h2_x4_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2I*> h2_Z_vs_AoQ_Z1Z2x2AoQgate;
        std::vector<TH2I*> h2_dEdeg_vs_Z_Z1Z2x2AoQgate;
        std::vector<TH2I*> h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate;
        std::vector<TH1I*> h1_a2_Z1Z2x2AoQgate;
        std::vector<TH1I*> h1_a4_Z1Z2x2AoQgate;
        std::vector<TH2I*> h2_x4_vs_AoQ_x4AoQgate;
        std::vector<TH2I*> h2_Z1_vs_Z2_x4AoQgate;
        std::vector<TH2I*> h2_x2_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2I*> h2_x4_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2I*> h2_Z_vs_AoQ_Z1Z2x4AoQgate;
        std::vector<TH2I*> h2_dEdeg_vs_Z_Z1Z2x4AoQgate;
        std::vector<TH2I*> h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate;
        std::vector<TH1I*> h1_a2_Z1Z2x4AoQgate;
        std::vector<TH1I*> h1_a4_Z1Z2x4AoQgate;
        std::vector<TH2I*> h2_Z_vs_AoQ_dEdegZgate;
        std::vector<TH2I*> h2_Z1_vs_Z2_dEdegZgate;
        std::vector<TH2I*> h2_x2_vs_AoQ_dEdegZgate;
        std::vector<TH2I*> h2_x4_vs_AoQ_dEdegZgate;
        std::vector<TH1I*> h1_a2_dEdegZgate;
        std::vector<TH1I*> h1_a4_dEdegZgate;
        std::vector<TH2I*> h2_Z_vs_AoQ_Zsame_dEdegZgate;

        TH2D* h2_Z1_vs_T_mhtdc;
        TH2D* h2_AoQ_vs_T_mhtdc;
        TH2D* h2_Z_vs_AoQ_mhtdc;
        TH2D* h2_Z_vs_AoQ_corr_mhtdc;
        TH2D* h2_Z_vs_Z2_mhtdc;
        TH2D* h2_Z_vs_AoQ_Zsame_mhtdc;
        TH2D* h2_x4_vs_AoQ_Zsame_mhtdc;
        TH2D* h2_x2_vs_AoQ_Zsame_mhtdc;
        TH2D* h2_x2_vs_AoQ_mhtdc;
        TH2D* h2_x4_vs_AoQ_mhtdc;
        TH2D* h2_dEdegoQ_vs_Z_mhtdc;
        TH2D* h2_dEdeg_vs_Z_mhtdc;
        TH2D* h2_a2_vs_AoQ_mhtdc;
        TH2D* h2_a4_vs_AoQ_mhtdc;
        TH2D* h2_Z_vs_dE2_mhtdc;
        TH2D* h2_x2_vs_x4_mhtdc;
        TH2D* h2_SC41dE_vs_AoQ_mhtdc;
        TH2D* h2_dE_vs_ToF_mhtdc;
        TH2D* h2_x2_vs_Z_mhtdc;
        TH2D* h2_x4_vs_Z_mhtdc;
        TH2D* h2_dE1_vs_x2_mhtdc;
        TH2D* h2_dE1_vs_x4_mhtdc;
        TH2D* h2_Z_vs_Sc21E_mhtdc;
        std::vector<TH2I*> h2_Z_vs_AoQ_ZAoQgate_mhtdc;
        std::vector<TH2I*> h2_Z1_vs_Z2_ZAoQgate_mhtdc;
        std::vector<TH2I*> h2_x2_vs_AoQ_ZAoQgate_mhtdc;
        std::vector<TH2I*> h2_x4_vs_AoQ_ZAoQgate_mhtdc;
        std::vector<TH2I*> h2_dEdeg_vs_Z_ZAoQgate_mhtdc;
        std::vector<TH2I*> h2_dedegoQ_vs_Z_ZAoQgate_mhtdc;
        std::vector<TH1I*> h1_a2_ZAoQ_gate_mhtdc;
        std::vector<TH1I*> h1_a4_ZAoQ_gate_mhtdc;
        std::vector<TH2I*> h2_dEdeg_vs_Z_Z1Z2gate_mhtdc;
        std::vector<TH2I*> h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc;
        std::vector<TH2I*> h2_Z1_vs_Z2_Z1Z2gate_mhtdc;
        std::vector<TH1I*> h1_a2_Z1Z2gate_mhtdc;
        std::vector<TH1I*> h1_a4_Z1Z2gate_mhtdc;
        std::vector<TH2I*> h2_x2_vs_AoQ_Z1Z2gate_mhtdc;
        std::vector<TH2I*> h2_x4_vs_AoQ_Z1Z2gate_mhtdc;
        std::vector<TH2I*> h2_Z_vs_AoQ_Z1Z2gate_mhtdc;
        std::vector<TH2I*> h2_x2_vs_AoQ_x2AoQgate_mhtdc;
        std::vector<TH2I*> h2_Z1_vs_Z2_x2AoQgate_mhtdc;
        std::vector<TH2I*> h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2I*> h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2I*> h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2I*> h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2I*> h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2I*> h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH1I*> h1_a2_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH1I*> h1_a4_Z1Z2x2AoQgate_mhtdc;
        std::vector<TH2I*> h2_x4_vs_AoQ_x4AoQgate_mhtdc;
        std::vector<TH2I*> h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2I*> h2_Z1_vs_Z2_x4AoQgate_mhtdc;
        std::vector<TH2I*> h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2I*> h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2I*> h2_Z_vs_AoQ_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2I*> h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2I*> h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH1I*> h1_a2_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH1I*> h1_a4_Z1Z2x4AoQgate_mhtdc;
        std::vector<TH2I*> h2_Z_vs_dEdeg_dEdegZgate_mhtdc;
        std::vector<TH2I*> h2_Z_vs_AoQ_dEdegZgate_mhtdc;
        std::vector<TH2I*> h2_Z1_vs_Z2_dEdegZgate_mhtdc;
        std::vector<TH2I*> h2_x2_vs_AoQ_dEdegZgate_mhtdc;
        std::vector<TH2I*> h2_x4_vs_AoQ_dEdegZgate_mhtdc;
        std::vector<TH1I*> h1_a2_dEdegZgate_mhtdc;
        std::vector<TH1I*> h1_a4_dEdegZgate_mhtdc;
        std::vector<TH2I*> h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc;

        // Conditions/Cuts
        std::vector<TCutG*> cutID_Z_AoQ;
        std::vector<TCutG*> cutID_Z_Z2;
        std::vector<TCutG*> cutID_x2AoQ;
        std::vector<TCutG*> cutID_x4AoQ;
        std::vector<TCutG*> cutID_dEdegZ;

    public:
        ClassDef(FrsAnalysisSpectra, 1);
};

#endif