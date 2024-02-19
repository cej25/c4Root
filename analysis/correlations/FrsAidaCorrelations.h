#ifndef FrsAidaCorrelations_H
#define FrsAidaCorrelations_H

#include "TAidaConfiguration.h"
#include "TClonesArray.h"
#include "AidaHitData.h"
#include "../../config/frs_config.h"
#include "../../config/NovTest/setup.hh"

#include "TH1.h"
#include "TH2.h"
#include "TCutG.h"

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

class FrsAidaCorrelations : public FairTask
{
    public:
        FrsAidaCorrelations(std::vector<std::vector<TCutG*>> fFrsGates);

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
        std::vector<TH2I*> h2_AidaImplant_FRS_ZAoQgate_strip_xy[AIDA_DSSDS];
        std::vector<TH1I*> h1_AidaImplant_FRS_ZAoQgate_e[AIDA_DSSDS];
        std::vector<TH2D*> h2_AidaImplant_FRS_ZAoQgate_position[AIDA_DSSDS];
        std::vector<TH2I*> h2_AidaImplant_FRS_Z1Z2gate_strip_xy[AIDA_DSSDS];
        std::vector<TH2D*> h2_AidaImplant_FRS_Z1Z2gate_position[AIDA_DSSDS];
        std::vector<TH2I*> h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy[AIDA_DSSDS];
        std::vector<TH2D*> h2_AidaImplant_FRS_Z1Z2x2AoQgates_position[AIDA_DSSDS];
        std::vector<TH1I*> h1_AidaImplant_FRS_Z1Z2x2AoQgates_e[AIDA_DSSDS];
        std::vector<TH2I*> h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy[AIDA_DSSDS];
        std::vector<TH2D*> h2_AidaImplant_FRS_Z1Z2x4AoQgates_position[AIDA_DSSDS];
        std::vector<TH1I*> h1_AidaImplant_FRS_Z1Z2x4AoQgates_e[AIDA_DSSDS];
        std::vector<TH2I*> h2_AidaImplant_FRS_ZAoQgate_strip_xy_stopped[AIDA_DSSDS];
        std::vector<TH1I*> h1_AidaImplant_FRS_ZAoQgate_e_stopped[AIDA_DSSDS];
        std::vector<TH2D*> h2_AidaImplant_FRS_ZAoQgate_position_stopped[AIDA_DSSDS];
        std::vector<TH2I*> h2_AidaImplant_FRS_Z1Z2gate_strip_xy_stopped[AIDA_DSSDS];
        std::vector<TH2D*> h2_AidaImplant_FRS_Z1Z2gate_position_stopped[AIDA_DSSDS];
        std::vector<TH2I*> h2_AidaImplant_FRS_Z1Z2x2AoQgates_strip_xy_stopped[AIDA_DSSDS];
        std::vector<TH2D*> h2_AidaImplant_FRS_Z1Z2x2AoQgates_position_stopped[AIDA_DSSDS];
        std::vector<TH1I*> h1_AidaImplant_FRS_Z1Z2x2AoQgates_e_stopped[AIDA_DSSDS];
        std::vector<TH2I*> h2_AidaImplant_FRS_Z1Z2x4AoQgates_strip_xy_stopped[AIDA_DSSDS];
        std::vector<TH2D*> h2_AidaImplant_FRS_Z1Z2x4AoQgates_position_stopped[AIDA_DSSDS];
        std::vector<TH1I*> h1_AidaImplant_FRS_Z1Z2x4AoQgates_e_stopped[AIDA_DSSDS];

        // Conditions/Cuts
        std::vector<TCutG*> cutID_Z_AoQ;
        std::vector<TCutG*> cutID_Z_Z2;
        std::vector<TCutG*> cutID_x2AoQ;
        std::vector<TCutG*> cutID_x4AoQ;
        std::vector<TCutG*> cutID_dEdegZ;

    public:
        ClassDef(FrsAidaCorrelations, 1)
};



#endif
