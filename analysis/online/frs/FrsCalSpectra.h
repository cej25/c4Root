#ifndef FrsCalSpectra_H
#define FrsCalSpectra_H 1

#include "FairTask.h"
#include "FrsCalData.h"

#include "TDirectory.h"
#include "TFolder.h"
#include "TH1.h"
#include "TH2.h"
#include <vector>

typedef Int_t Int_t;

class TFolder;
class TDirectory;
class TClonesArray;
class EventHeader;
class FrsHitData;
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

        std::vector<FrsCalSciItem> const* calSciArray;
        std::vector<FrsCalTpcItem> const* calTpcArray;

   
        // check for trigger should be done globally, somewhere else
        EventHeader* header;
        Int_t fNEvents;

        TFolder* histograms;
        TDirectory* dir_frs;
        TDirectory* dir_frs_cal;
        TDirectory* dir_cal_sci;
        TDirectory* dir_sci_tac;
        TDirectory* dir_sci_tac_de;
        TDirectory* dir_sci_tac_dt;
        TDirectory* dir_sci_mhtdc;
        TDirectory* dir_sci_mhtdc_t;
        TDirectory* dir_sci_mhtdc_dt;
        TDirectory* dir_cal_tpc;
        TDirectory* dir_frs_cal_main;
        TDirectory* dir_frs_cal_tpc;
        TDirectory* dir_frs_cal_user;
        // Canvas

 
        // Histograms

        // TAC dE         
        TH1* h1_sci_tac_de_21l;
        TH1* h1_sci_tac_de_21r;
        TH1* h1_sci_tac_de_22l;
        TH1* h1_sci_tac_de_22r;
        TH1* h1_sci_tac_de_31l;
        TH1* h1_sci_tac_de_31r;
        TH1* h1_sci_tac_de_41l;
        TH1* h1_sci_tac_de_41r;
        TH1* h1_sci_tac_de_42l;
        TH1* h1_sci_tac_de_42r;
        TH1* h1_sci_tac_de_43l;
        TH1* h1_sci_tac_de_43r;
        TH1* h1_sci_tac_de_81l;
        TH1* h1_sci_tac_de_81r;

        // TAC dT    
        TH1* h1_sci_tac_dt_21l_21r;
        TH1* h1_sci_tac_dt_41l_41r;
        TH1* h1_sci_tac_dt_42l_42r;
        TH1* h1_sci_tac_dt_43l_43r;
        TH1* h1_sci_tac_dt_81l_81r;
        TH1* h1_sci_tac_dt_21l_41l;
        TH1* h1_sci_tac_dt_21r_41r;
        TH1* h1_sci_tac_dt_42r_21r;
        TH1* h1_sci_tac_dt_42l_21l;
        TH1* h1_sci_tac_dt_21l_81l;
        TH1* h1_sci_tac_dt_21r_81r;
        TH1* h1_sci_tac_dt_22l_22r;
        TH1* h1_sci_tac_dt_22l_41l;
        TH1* h1_sci_tac_dt_22r_41r;
        TH1* h1_sci_tac_dt_22l_81l;
        TH1* h1_sci_tac_dt_22r_81r;
        
        // MHTDC T
        TH1* h1_sci_mhtdc_t_21l;
        TH1* h1_sci_mhtdc_t_21r;
        TH1* h1_sci_mhtdc_t_22l;
        TH1* h1_sci_mhtdc_t_22r;
        TH1* h1_sci_mhtdc_t_41l;
        TH1* h1_sci_mhtdc_t_41r;
        TH1* h1_sci_mhtdc_t_42l;
        TH1* h1_sci_mhtdc_t_42r;
        TH1* h1_sci_mhtdc_t_43l;
        TH1* h1_sci_mhtdc_t_43r;
        TH1* h1_sci_mhtdc_t_81l;
        TH1* h1_sci_mhtdc_t_81r;

        // MHTDC dT
        TH1* h1_sci_mhtdc_dt_21l_21r;
        TH1* h1_sci_mhtdc_dt_22l_22r;
        TH1* h1_sci_mhtdc_dt_41l_41r;
        TH1* h1_sci_mhtdc_dt_42l_42r;    
        TH1* h1_sci_mhtdc_dt_22l_21l;    
        TH1* h1_sci_mhtdc_dt_22r_21r;    
        TH1* h1_sci_mhtdc_dt_41l_21l;    
        TH1* h1_sci_mhtdc_dt_41r_21r;    
        TH1* h1_sci_mhtdc_dt_42l_21l;    
        TH1* h1_sci_mhtdc_dt_42r_21r;    
        TH1* h1_sci_mhtdc_dt_41l_22l;    
        TH1* h1_sci_mhtdc_dt_41r_22r;    
        TH1* h1_sci_mhtdc_dt_42l_22l;    
        TH1* h1_sci_mhtdc_dt_42r_22r;    
        TH1* h1_sci_mhtdc_dt_42l_41l;    
        TH1* h1_sci_mhtdc_dt_42r_41r;    

        // TPC
        int number_of_tpcs = 7;
        int number_of_anodes_per_tpc = 4;
        TH2* h2_tpc_check_sums;
        TH1* h1_tpc_angle_x_s2_foc_21_22;
        TH1* h1_tpc_angle_y_s2_foc_21_22;
        TH1* h1_tpc_x_s2_foc_21_22;
        TH1* h1_tpc_y_s2_foc_21_22;
        TH1* h1_tpc21_22_sc21_x;
        TH1* h1_tpc21_22_sc22_x;
        TH1* h1_tpc_angle_x_s2_foc_23_24;
        TH1* h1_tpc_angle_y_s2_foc_23_24;
        TH1* h1_tpc_x_s2_foc_23_24;
        TH1* h1_tpc_y_s2_foc_23_24;
        TH1* h1_tpc23_24_sc21_x;
        TH1* h1_tpc23_24_sc21_y;
        TH1* h1_tpc23_24_sc22_x;
        TH1* h1_tpc23_24_sc22_y;
        TH1* h1_tpc_angle_x_s2_foc_22_24;
        TH1* h1_tpc_angle_y_s2_foc_22_24;
        TH1* h1_tpc_x_s2_foc_22_24;
        TH1* h1_tpc_y_s2_foc_22_24;
        TH1* h1_tpc_angle_x_s4;
        TH1* h1_tpc_angle_y_s4;
        TH1* h1_tpc_x_s4;
        TH1* h1_tpc_y_s4;
        TH1* h1_tpc_sc41_x;
        TH1* h1_tpc_sc41_y;
        TH1* h1_tpc_sc42_x;
        TH1* h1_tpc_sc42_y;
        TH1* h1_tpc_sc43_x;
        TH1* h1_tpc_music41_x;
        TH1* h1_tpc_music42_x;
        
    public:
        ClassDef(FrsCalSpectra, 1)

};

#endif
