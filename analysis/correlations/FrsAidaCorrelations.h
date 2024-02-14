#ifndef FrsAidaCorrelations_H
#define FrsAidaCorrelations_H

#include "TAidaConfiguration.h"
#include "TClonesArray.h"
#include "AidaHitData.h"
#include "../../config/frs_config.h"
#include "../../config/NovTest/setup.hh"

#include "TH1.h"
#include "TH2.h"

class TClonesArray;
class EventHeader;
class AidaHit;
class TH1I;
class TH2I;
class TH2F;
class TH2D;
class FrsHitData;
class FrsAnalysisData;
class TAidaConfiguration;

class FrsAidaCorrelations : public FairTask
{
    public:
        FrsAidaCorrelations();

        FrsAidaCorrelations(const TString& name, Int_t verbose);

        virtual ~FrsAidaCorrelations();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();
        virtual void FinishTask();

    private:

        TClonesArray* fFrsHitArray;
        TClonesArray* fFrsAnalysisArray;
        TClonesArray* fFrsAidaCorrelation;
        std::vector<AidaHit>* fAidaImplants;

        Int_t fNEvents;
        EventHeader* header;
        Bool_t fOnline;

        // Variables
        Long64_t AidaLastWR;

        // Histograms
        TH1I* h1_AidaImplant_Deadtime;
        TH1I* h1_AidaImplant_FRS_dT;
        TH2F* h2_AidaImplant_FRS_x_vs_x4;
        TH2I* h2_AidaImplant_FRS_ZAoQgate_strip_xy[FRS_GATES][AIDA_DSSDS];
        TH1I* h1_AidaImplant_FRS_ZAoQgate_e[FRS_GATES][AIDA_DSSDS];
        TH2D* h2_AidaImplant_FRS_ZAoQgate_position[FRS_GATES][AIDA_DSSDS];
        TH2I* h2_AidaImplant_FRS_Z1Z2gate_strip_xy[FRS_GATES][AIDA_DSSDS];
        TH2D* h2_AidaImplant_FRS_Z1Z2gate_position[FRS_GATES][AIDA_DSSDS];
        TH2I* h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy[FRS_GATES][AIDA_DSSDS];
        TH2D* h2_AidaImplant_FRS_Z1Z2x2AoQgates_position[FRS_GATES][AIDA_DSSDS];
        TH1I* h1_AidaImplant_FRS_Z1Z2x2AoQgates_e[FRS_GATES][AIDA_DSSDS];
        TH2I* h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy[FRS_GATES][AIDA_DSSDS];
        TH2D* h2_AidaImplant_FRS_Z1Z2x4AoQgates_position[FRS_GATES][AIDA_DSSDS];
        TH1I* h1_AidaImplant_FRS_Z1Z2x4AoQgates_e[FRS_GATES][AIDA_DSSDS];
        TH2I* h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped[FRS_GATES][AIDA_DSSDS];
        TH1I* h1_AidaImplant_FRS_ZAoQgate_e_stopped[FRS_GATES][AIDA_DSSDS];
        TH2D* h2_AidaImplant_FRS_ZAoQgate_position_stopped[FRS_GATES][AIDA_DSSDS];
        TH2I* h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped[FRS_GATES][AIDA_DSSDS];
        TH2D* h2_AidaImplant_FRS_Z1Z2gate_position_stopped[FRS_GATES][AIDA_DSSDS];
        TH2I* h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped[FRS_GATES][AIDA_DSSDS];
        TH2D* h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped[FRS_GATES][AIDA_DSSDS];
        TH1I* h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped[FRS_GATES][AIDA_DSSDS];
        TH2I* h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped[FRS_GATES][AIDA_DSSDS];
        TH2D* h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped[FRS_GATES][AIDA_DSSDS];
        TH1I* h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped[FRS_GATES][AIDA_DSSDS];


    public:
        ClassDef(FrsAidaCorrelations, 1)
};



#endif
