#ifndef LisaHit2Histo_H
#define LisaHit2Histo_H

#include "TClonesArray.h"
#include "EventHeader.h"
#include "TLisaConfiguration.h"
#include "TFrsConfiguration.h"
#include "TExperimentConfiguration.h"
#include "LisaData.h"
#include "LisaCalData.h"
#include "LisaAnaData.h"
#include "LisaHitData.h"
#include "LisaHistoData.h"
#include "FrsData.h"
#include "FrsCalData.h"
#include <map>
#include <vector>
#include "TVector.h"
#include "FairTask.h"

#include "LisaGate.h"
#include "FrsGate.h"

class EventHeader;
class LisaItem;
class LisaCalItem;
class LisaAnaItem;
class LisaHistoItem;
class FrsHitItem;
class FrsMultiHitItem;

class LisaHit2Histo : public FairTask
{
    public:
        LisaHit2Histo();
        LisaHit2Histo(std::vector<FrsGate*> fg);
        LisaHit2Histo(std::vector<LisaGate*> lg);
        LisaHit2Histo(std::vector<FrsGate*> fg, std::vector<LisaGate*> lg);
        LisaHit2Histo(const TString& name, Int_t verbose = 1);


        virtual ~LisaHit2Histo();

        virtual InitStatus Init();

        virtual void Exec (Option_t* option);

        virtual void SetOnline(Bool_t option) { fOnline = option; }

        virtual void FinishEvent();
        virtual void FinishTask();

    private:
        TLisaConfiguration const* lisa_config;
        TFrsConfiguration const* frs_config;
        TExperimentConfiguration const* exp_config;
        TFRSParameter* frs;
        TIDParameter* id;
    
        std::vector<FrsGate*> FrsGates;
        std::vector<LisaGate*> febex_gates;
        std::vector<LisaGate*> mwd_gates;

        int ncorr = 0;
        int tot_pass_s2s4[2] = {0};
        int nbreak = 0;
        int nmultihit[2] = {0};
        int nmultihit_gated[2] = {0};
        int nnobreak[2] = {0};
        int aoq = 0;
        int layer1count = 0;
        int layer2count = 0;
        int bothlayerseen = 0;
        bool layer1seen = false;
        bool layer2seen = false;
        int gate1 = 0;
        int gate2 = 0;
        int bothgate = 0;
        int sanity_check = 0;

        int gate_number = 0;
        int mwd_gate_number = 0;

        int pair_count = 0;
        int pair_count_MWD = 0;


        int** mh_counter_passed_s1s2_seq;
        int** mh_counter_passed_s2s4_seq;
        int** mh_counter_passed_s1s2_seq_mwd;
        int** mh_counter_passed_s2s4_seq_mwd;

        std::vector<LisaItem> const* lisaArray;
        std::vector<LisaAnaItem> const* lisaAnaArray;
        std::vector<LisaCalItem> const* lisaCalArray; // needed?
        std::vector<LisaHitItem>* lisaHitArray;
        std::vector<std::vector<LisaHistoItem>*> lisaHistoArray;
        std::vector<FrsHitItem> const* frsHitArray;
        std::vector<FrsMultiHitItem> const* multihitArray;
      

        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

        uint64_t wr_t;
        int64_t wr_LISA;
        int64_t wr_FRS;
        int64_t wr_travMUSIC;
        int64_t wr_LISA_FRS;
        int64_t wr_LISA_travMUSIC;
        int64_t wr_travMUSIC_FRS;

        int layer_number;

        std::map<std::pair<int,int>, std::pair<std::pair<int, std::pair<int, int>>,std::pair<float,std::pair<std::string,std::string>>>> detector_mapping; //Debugging.Raplace std:string-> TString ?
        std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> detector_z_calibration;

        Float_t energy_MUSIC_21;
        Float_t energy_MUSIC_41;
        Float_t energy_MUSIC_42;

        std::vector<Float_t> sci21l_s1s2_selected;
        std::vector<Float_t> sci21r_s1s2_selected;
        std::vector<Float_t> sci21l_s2s4_selected;
        std::vector<Float_t> sci21r_s2s4_selected;

        std::vector<std::vector<Float_t>> Z21_passed;
        std::vector<std::vector<Float_t>> Z21_selected_passed;
        std::vector<std::vector<Float_t>> AoQ_s1s2_passed;
        std::vector<std::vector<Float_t>> Z41_passed;
        std::vector<std::vector<Float_t>> Z42_passed;
        std::vector<std::vector<Float_t>> AoQ_s2s4_passed;
        std::vector<std::vector<Float_t>> AoQ_s1s2_selected_passed;
        std::vector<std::vector<Float_t>> Z42_selected_passed;
        std::vector<std::vector<Float_t>> AoQ_s2s4_selected_passed;
        std::vector<std::vector<Float_t>> dEdeg_z41_passed;

        std::vector<std::vector<float>> energy_layer;
        std::vector<std::vector<float>> energy_MWD_layer;
        std::vector<std::vector<std::vector<float>>> energy_layer_gated;
        std::vector<std::vector<std::vector<float>>> energy_MWD_layer_gated;
        std::vector<std::vector<std::vector<std::vector<std::vector<float>>>>> energy_xy_gated;
        std::vector<std::vector<std::vector<std::vector<std::vector<float>>>>> energy_MWD_xy_gated;


        double slope_z;
        double intercept_z;
        float de_dx_corr;

        std::set<std::tuple<int, int, int>> excluded;




    public:
        ClassDef(LisaHit2Histo, 1)

};



#endif