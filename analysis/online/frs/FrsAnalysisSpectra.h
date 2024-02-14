#ifndef FrsAnalysisSpectra_H
#define FrsAnalysisSpectra_H

#include "../../../config/frs_config.h"
#include "FairTask.h"
#include "TFRSParameter.h"
#include "TH2.h"
#include "TH1.h"
#include "TCutG.h"

class EventHeader;
class TClonesArray;
class FrsHitData;
class FrsAnalysisData;
class TH2D;
class TH2I;
class TH1I;
class TFolder;
class TCutG;

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
                        TRangeParameter* frange);

        FrsAnalysisSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsAnalysisSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        void ReadGates();

        virtual void FinishEvent();

        virtual void FinishTask();

    private:

        Int_t fNEvents;
        EventHeader* header;
        Bool_t fOnline;

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
        TH2I* h2_Z_vs_AoQ_ZAoQgate[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_ZAoQgate[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_ZAoQgate[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_ZAoQgate[FRS_GATES];
        TH2I* h2_dEdeg_vs_Z_ZAoQgate[FRS_GATES];
        TH2I* h2_dedegoQ_vs_Z_ZAoQgate[FRS_GATES];
        TH1I* h1_a2_ZAoQ_gate[FRS_GATES];
        TH1I* h1_a4_ZAoQ_gate[FRS_GATES];
        TH2I* h2_dEdeg_vs_Z_Z1Z2gate[FRS_GATES];
        TH2I* h2_dEdegoQ_vs_Z_Z1Z2gate[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_Z1Z2gate[FRS_GATES];
        TH1I* h1_a2_Z1Z2gate[FRS_GATES];
        TH1I* h1_a4_Z1Z2gate[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_Z1Z2gate[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_Z1Z2gate[FRS_GATES];
        TH2I* h2_Z_vs_AoQ_Z1Z2gate[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_x2AoQgate[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_x2AoQgate[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_Z1Z2x2AoQgate[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_Z1Z2x2AoQgate[FRS_GATES];
        TH2I* h2_Z_vs_AoQ_Z1Z2x2AoQgate[FRS_GATES];
        TH2I* h2_dEdeg_vs_Z_Z1Z2x2AoQgate[FRS_GATES];
        TH2I* h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate[FRS_GATES];
        TH1I* h1_a2_Z1Z2x2AoQgate[FRS_GATES];
        TH1I* h1_a4_Z1Z2x2AoQgate[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_x4AoQgate[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_x4AoQgate[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_Z1Z2x4AoQgate[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_Z1Z2x4AoQgate[FRS_GATES];
        TH2I* h2_Z_vs_AoQ_Z1Z2x4AoQgate[FRS_GATES];
        TH2I* h2_dEdeg_vs_Z_Z1Z2x4AoQgate[FRS_GATES];
        TH2I* h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate[FRS_GATES];
        TH1I* h1_a2_Z1Z2x4AoQgate[FRS_GATES];
        TH1I* h1_a4_Z1Z2x4AoQgate[FRS_GATES];
        TH2I* h2_Z_vs_AoQ_dEdegZgate[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_dEdegZgate[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_dEdegZgate[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_dEdegZgate[FRS_GATES];
        TH1I* h1_a2_dEdegZgate[FRS_GATES];
        TH1I* h1_a4_dEdegZgate[FRS_GATES];
        TH2I* h2_Z_vs_AoQ_Zsame_dEdegZgate[FRS_GATES];

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
        TH2I* h2_Z_vs_AoQ_ZAoQgate_mhtdc[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_ZAoQgate_mhtdc[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_ZAoQgate_mhtdc[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_ZAoQgate_mhtdc[FRS_GATES];
        TH2I* h2_dEdeg_vs_Z_ZAoQgate_mhtdc[FRS_GATES];
        TH2I* h2_dedegoQ_vs_Z_ZAoQgate_mhtdc[FRS_GATES];
        TH1I* h1_a2_ZAoQ_gate_mhtdc[FRS_GATES];
        TH1I* h1_a4_ZAoQ_gate_mhtdc[FRS_GATES];
        TH2I* h2_dEdeg_vs_Z_Z1Z2gate_mhtdc[FRS_GATES];
        TH2I* h2_dEdegoQ_vs_Z_Z1Z2gate_mhtdc[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_Z1Z2gate_mhtdc[FRS_GATES];
        TH1I* h1_a2_Z1Z2gate_mhtdc[FRS_GATES];
        TH1I* h1_a4_Z1Z2gate_mhtdc[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_Z1Z2gate_mhtdc[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_Z1Z2gate_mhtdc[FRS_GATES];
        TH2I* h2_Z_vs_AoQ_Z1Z2gate_mhtdc[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_x2AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_x2AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_Z1Z2x2AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_Z1Z2x2AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_Z1Z2x2AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_Z_vs_AoQ_Z1Z2x2AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_dEdeg_vs_Z_Z1Z2x2AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_dEdegoQ_vs_Z_Z1Z2x2AoQgate_mhtdc[FRS_GATES];
        TH1I* h1_a2_Z1Z2x2AoQgate_mhtdc[FRS_GATES];
        TH1I* h1_a4_Z1Z2x2AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_x4AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_Z1Z2x4AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_x4AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_Z1Z2x4AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_Z1Z2x4AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_Z_vs_AoQ_Z1Z2x4AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_dEdeg_vs_Z_Z1Z2x4AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_dEdegoQ_vs_Z_Z1Z2x4AoQgate_mhtdc[FRS_GATES];
        TH1I* h1_a2_Z1Z2x4AoQgate_mhtdc[FRS_GATES];
        TH1I* h1_a4_Z1Z2x4AoQgate_mhtdc[FRS_GATES];
        TH2I* h2_Z_vs_dEdeg_dEdegZgate_mhtdc[FRS_GATES];
        TH2I* h2_Z_vs_AoQ_dEdegZgate_mhtdc[FRS_GATES];
        TH2I* h2_Z1_vs_Z2_dEdegZgate_mhtdc[FRS_GATES];
        TH2I* h2_x2_vs_AoQ_dEdegZgate_mhtdc[FRS_GATES];
        TH2I* h2_x4_vs_AoQ_dEdegZgate_mhtdc[FRS_GATES];
        TH1I* h1_a2_dEdegZgate_mhtdc[FRS_GATES];
        TH1I* h1_a4_dEdegZgate_mhtdc[FRS_GATES];
        TH2I* h2_Z_vs_AoQ_Zsame_dEdegZgate_mhtdc[FRS_GATES];

        // Conditions/Cuts - CEJ: figure out how to read from file!!
        TCutG* cID_Z_AoQ[FRS_GATES];
        TCutG* cID_Z_Z2[FRS_GATES];
        TCutG* cID_x2AoQ[FRS_GATES];
        TCutG* cID_x4AoQ[FRS_GATES];
        TCutG* cID_dEdegZ[FRS_GATES];
        TCutG* cID_Z_AoQ_mhtdc[FRS_GATES];
        TCutG* cID_Z_Z2_mhtdc[FRS_GATES];
        TCutG* cID_x2AoQ_mhtdc[FRS_GATES];
        TCutG* cID_x4AoQ_mhtdc[FRS_GATES];
        TCutG* cID_dEdegZ_mhtdc[FRS_GATES];

    public:
        ClassDef(FrsAnalysisSpectra, 1);
};

#endif