#ifndef FrsCal2Ana_H
#define FrsCal2Ana_H

#include "TFrsConfiguration.h"
#include "TExperimentConfiguration.h"

// #include "../../config/setup.h"
#include "FairTask.h"
#include "TFRSParameter.h"
#include "FrsData.h"
#include "FrsCalData.h"
#include "FrsHitData.h" // maybe
#include <TRandom3.h>
#include "TClonesArray.h"

//#include "GainShift.h"

class TClonesArray;
class FrsHitItem;
class EventHeader;
class EventData;

class FrsCal2Ana : public FairTask
{
    public:
        FrsCal2Ana();

        FrsCal2Ana(const TString& name, Int_t verbose);

        virtual ~FrsCal2Ana();
        
        virtual InitStatus Init();
        virtual InitStatus ReInit();

        virtual void Exec(Option_t* option); // virtual?

        void ProcessScalers();
        void ProcessSciTAC();
        void ProcessSciMHTDC();
        void ProcessMusic();
        void ProcessTpcs();
        
        void ProcessIDs();


        void Setup_Conditions(std::string path_to_config_files);
        void FRS_GainMatching();
        void FRS_TM_Drift();

        Bool_t Check_WinCond(Float_t P, Float_t* V);
        Bool_t Check_WinCond_Multi(Float_t P, Float_t V[8][2], int cond_num);
        Float_t rand3();


        void FinishEvent();
        void FinishTask();
        
        void SetOnline(Bool_t option) { fOnline = option; }
    
    private:

        TFrsConfiguration const* frs_config;
        TExperimentConfiguration const* exp_config;
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
        std::string pathToConfigFiles;

        Bool_t fOnline;
        Int_t fNEvents;
        EventHeader* header;
        int total_time_microsecs = 0;

        bool conditions_files_read = false;

        std::vector<FrsTpatItem> const* tpatArray;
        std::vector<FrsScalerItem> const* scalerArray;
        std::vector<FrsCalSciItem> const* calSciArray;
        std::vector<FrsMusicItem> const* musicArray;
        std::vector<FrsCalTpcItem> const* calTpcArray;
        std::vector<FrsHitItem>* hitArray;
        std::vector<FrsMultiHitItem>* multihitArray;


     
        // Setup variables.. ideally simply remove.. hard code?
        Float_t lim_csum[4][7][2];
        Float_t lim_xsum[13][2];
        Float_t lim_ysum[13][2];
        Float_t cMusic1_E[8][2];
        Float_t cMusic2_E[8][2];
        Float_t cMusic3_E[4][2];
        Float_t cMusic1_T[8][2];
        Float_t cMusic2_T[8][2];
        Float_t cMusic3_T[4][2];
        Float_t cMusicTRAV_E[8][2];
        Float_t cMusicTRAV_T[8][2];
        Float_t cMusic3_dec[2];
        Float_t cSCI_L[2];
        Float_t cSCI_R[2];
        Float_t cSCI_E[2];
        Float_t cSCI_Tx[2];
        Float_t cSCI_X[2];
        Float_t cSCI_LL2[2];
        Float_t cSCI_RR2[2];
        Float_t cSCI_LL3[2];
        Float_t cSCI_RR3[2];
        Float_t cSCI_LL4[2];
        Float_t cSCI_RR4[2];
        Float_t cSCI_LL5[2];
        Float_t cSCI_RR5[2];
        Float_t cSCI_LL6[2];
        Float_t cSCI_RR6[2];
        Float_t cID_x2[2];
        Float_t cID_x4[2];
        Float_t cID_Z_Z[2];

        /* ----------------------------------------------- */
        // Intermediate variables
        /* ----------------------------------------------- */

        TRandom3 random3;

        float FRS_time_mins = 0;
        int Z_Shift_array;
        Float_t FRS_WR_a[200];
        Float_t FRS_WR_b[200];
        Float_t Z1_shift_value[200];
        Float_t Z2_shift_value[200];
        int AoQ_Shift_array;
        Float_t FRS_WR_i[200];
        Float_t FRS_WR_j[200];
        Float_t AoQ_shift_value[200];
        Float_t AoQ_shift_TPC_value[200];
        Float_t AoQ_shift_Sci21_value[200];
        Float_t AoQ_shift_Sci22_value[200];
        Int_t ts_mins;


    public:
        ClassDef(FrsCal2Ana, 1);

};

#endif
