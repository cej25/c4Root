#ifndef FrsCalSpectra_H
#define FrsCalSpectra_H 1

#include "FairTask.h"
#include "FrsHitData.h"
#include "FrsMainCalData.h"
#include "FrsTPCData.h"
#include "FrsTPCCalData.h"
#include "FrsUserCalData.h"
#include "FrsTpatData.h"

#include "TDirectory.h"
#include "TFolder.h"
#include "TH1.h"
#include "TH2.h"
#include <vector>

class TFolder;
class TDirectory;
class TClonesArray;
class EventHeader;
class FrsHitData;
class FrsMainCalData;
class FrsUserCalData;
class FrsTPCData;
class FrsTPCCalData;
class FrsVFTXCalData;
class TCanvas;
class TH1F;
class TH2F;

class FrsCalSpectra : public FairTask
{
    public:
        FrsCalSpectra();

        FrsCalSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsCalSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();


    private:

        std::vector<FrsTPCV7X5Item> const* v7x5array;
        std::vector<FrsTPCV1190Item> const* v1190array;
        std::vector<FrsMainCalScalerItem> const* mainScalerArray;
        std::vector<FrsMainCalSciItem> const* mainSciArray;
        std::vector<FrsMainCalMusicItem> const* mainMusicArray;
        std::vector<FrsTPCCalItem> const* tpcCalArray;
        std::vector<FrsUserCalScalerItem> const* userScalerArray;
        std::vector<FrsUserCalSciItem> const* userSciArray;
        std::vector<FrsUserCalMusicItem> const* userMusicArray;
        std::vector<FrsTpatItem> const* tpatArray;

   
        // check for trigger should be done globally, somewhere else
        EventHeader* header;
        Int_t fNEvents;

        TFolder* histograms;
        TDirectory* dir_frs;
        TDirectory* dir_frs_cal;
        TDirectory* dir_frs_cal_main;
        TDirectory* dir_frs_cal_tpc;
        TDirectory* dir_frs_cal_user;
        //TDirectory* dir_frs_cal_vftx;
        // Canvas

        //SCI delta E
        TH1D* h1_sci21_x;
         
         
        TH1D* h_sci_21l_de;
        TH1D* h_sci_21r_de;
        TH1D* h_sci_22l_de;
        TH1D* h_sci_22r_de;
        TH1D* h_sci_41l_de;
        TH1D* h_sci_41r_de;
        TH1D* h_sci_42l_de;
        TH1D* h_sci_42r_de;
        TH1D* h_sci_43l_de;
        TH1D* h_sci_43r_de;
        TH1D* h_sci_81l_de;
        TH1D* h_sci_81r_de;
        //SCI t
        TH1D* h_sci_21l_t;
        TH1D* h_sci_21r_t;
        TH1D* h_sci_22l_t;
        TH1D* h_sci_22r_t;
        TH1D* h_sci_41l_t;
        TH1D* h_sci_41r_t;
        TH1D* h_sci_42l_t;
        TH1D* h_sci_42r_t;
        TH1D* h_sci_43l_t;
        TH1D* h_sci_43r_t;
        TH1D* h_sci_81l_t;
        TH1D* h_sci_81r_t;

        //MUSIC timing:
        TH2D* h_music41_t;
        TH2D* h_music42_t;


        //TPC timings from v1190 in the tpc crate:
        TH2D* h_tpc_timings_lead;
        TH2D* h_tpc_timings_trail;

        // TPC derived values, tracking:
        int number_of_tpcs = 7;
        int number_of_anodes_per_tpc = 4;
        TH2D* h_tpc_check_sums;

        TH1D* h_tpc_angle_x_s2_foc_21_22;
        TH1D* h_tpc_angle_y_s2_foc_21_22;
        TH1D* h_tpc_x_s2_foc_21_22;
        TH1D* h_tpc_y_s2_foc_21_22;
        TH1D* h_tpc21_22_sc21_x;
        TH1D* h_tpc21_22_sc22_x;
        TH1D* h_tpc_angle_x_s2_foc_23_24;
        TH1D* h_tpc_angle_y_s2_foc_23_24;
        TH1D* h_tpc_x_s2_foc_23_24;
        TH1D* h_tpc_y_s2_foc_23_24;
        TH1D* h_tpc23_24_sc21_x;
        TH1D* h_tpc23_24_sc21_y;
        TH1D* h_tpc23_24_sc22_x;
        TH1D* h_tpc23_24_sc22_y;
        TH1D* h_tpc_angle_x_s2_foc_22_24;
        TH1D* h_tpc_angle_y_s2_foc_22_24;
        TH1D* h_tpc_x_s2_foc_22_24;
        TH1D* h_tpc_y_s2_foc_22_24;
        TH1D* h_tpc_angle_x_s4;
        TH1D* h_tpc_angle_y_s4;
        TH1D* h_tpc_x_s4;
        TH1D* h_tpc_y_s4;
        TH1D* h_tpc_sc41_x;
        TH1D* h_tpc_sc41_y;
        TH1D* h_tpc_sc42_x;
        TH1D* h_tpc_sc42_y;
        TH1D* h_tpc_sc43_x;
        TH1D* h_tpc_music41_x;
        TH1D* h_tpc_music42_x;
        TH1D* h_tpc_music43_x;


        //User crate:
        //uint32_t * dt_array;
        TH2D* h_music41_e;
        TH2D* h_music42_e;
        TH1D* h_tac_user_dt_21l_21r;
        TH1D* h_tac_user_dt_41l_41r;
        TH1D* h_tac_user_dt_42l_42r;
        TH1D* h_tac_user_dt_43l_43r;
        TH1D* h_tac_user_dt_81l_81r;
        TH1D* h_tac_user_dt_21l_41l;
        TH1D* h_tac_user_dt_21r_41r;
        TH1D* h_tac_user_dt_42r_21r;
        TH1D* h_tac_user_dt_42l_21l;
        TH1D* h_tac_user_dt_21l_81l;
        TH1D* h_tac_user_dt_21r_81r;
        TH1D* h_tac_user_dt_22l_22r;
        TH1D* h_tac_user_dt_22l_41l;
        TH1D* h_tac_user_dt_22r_41r;
        TH1D* h_tac_user_dt_22l_81l;
        TH1D* h_tac_user_dt_22r_81r;
        
    public:
        ClassDef(FrsCalSpectra, 1)

};

#endif
