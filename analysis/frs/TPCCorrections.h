#ifndef TPCCorrections_H
#define TPCCorrections_H 1

#include "FairTask.h"
#include "FrsHitData.h"
#include "FrsMainCalData.h"
#include "FrsTPCData.h"
#include "FrsTPCCalData.h"
#include "FrsUserCalData.h"
#include "FrsTpatData.h"


#include "TFrsConfiguration.h"
#include "../../config/setup.h"

#include "TDirectory.h"
#include "TFolder.h"
#include "TH1.h"
#include "TH2.h"
#include <vector>

#include "TRandom3.h"


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

class TPCCorrections : public FairTask
{
    public:
        TPCCorrections();

        TPCCorrections(const TString& name, Int_t verbose = 1);

        virtual ~TPCCorrections();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();


        Float_t rand3();


    private:

        TFrsConfiguration const* frs_config;
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

        Bool_t fOnline;

        std::vector<FrsMainCalScalerItem> const* mainScalerArray;
        std::vector<FrsMainCalSciItem> const* mainSciArray;
        std::vector<FrsMainCalMusicItem> const* mainMusicArray;
        std::vector<FrsTPCCalItem> const* tpcCalArray;
        std::vector<FrsUserCalScalerItem> const* userScalerArray;
        std::vector<FrsUserCalSciItem> const* userSciArray;
        std::vector<FrsUserCalMusicItem> const* userMusicArray;
        std::vector<FrsTpatItem> const* tpatArray;
        std::vector<FrsHitItem> const* hitArray;


        TRandom3 random3;


        Float_t ch_to_ns = 0.025;

   
        // check for trigger should be done globally, somewhere else
        EventHeader* header;
        Int_t fNEvents;

        TFolder* histograms;
        TDirectory* dir_frs;

        //SCI         
        //SCI dts
        TH1D * h_sci_21l_21r_dt;
        TH1D * h_sci_22l_22r_dt;
        TH1D * h_sci_41l_41r_dt;
        TH1D * h_sci_42l_42r_dt;

        //dx:
        TH1D * h_sci21_x;
        TH1D * h_sci22_x;
        TH1D * h_sci41_x;
        TH1D * h_sci42_x;
        
        //tof:
        TH1D * h_tof_4121;
        TH1D * h_tof_4221;
        TH1D * h_tof_4222;
        TH1D * h_tof_4122;

        TH2D * h_sci21_tpc_x;
        TH2D * h_sci22_tpc_x;
        TH2D * h_sci42_tpc_x;
        TH2D * h_sci41_tpc_x;


        //multiplicities:
        //SCI t
        TH1D* h_sci_21l_hits;
        TH1D* h_sci_21r_hits;
        TH1D* h_sci_22l_hits;
        TH1D* h_sci_22r_hits;
        TH1D* h_sci_41l_hits;
        TH1D* h_sci_41r_hits;
        TH1D* h_sci_42l_hits;
        TH1D* h_sci_42r_hits;
        
        TH2D * h_music41_x;
        TH2D * h_music42_x;
        TH2D * h_music41_x_cor;
        TH2D * h_music42_x_cor;

        double mhtdc_factor_21l_21r = 1;
        double mhtdc_offset_21l_21r = 0;
        double mhtdc_factor_22l_22r = 1;
        double mhtdc_offset_22l_22r = 0;
        double mhtdc_factor_41l_41r = 1;
        double mhtdc_offset_41l_41r = 0;
        double mhtdc_factor_42l_42r = 1;
        double mhtdc_offset_42l_42r = 0;
        double mhtdc_offset_41_21 = 0;
        double mhtdc_offset_41_22 = 0;
        double mhtdc_offset_42_21 = 0;
        double mhtdc_offset_42_22 = 0;

                //SCI         
        //SCI dts
        TH1D * h_sci_21l_21r_dt_tac;
        TH1D * h_sci_22l_22r_dt_tac;
        TH1D * h_sci_41l_41r_dt_tac;
        TH1D * h_sci_42l_42r_dt_tac;

        //dx:
        TH1D * h_sci21_x_tac;
        TH1D * h_sci22_x_tac;
        TH1D * h_sci41_x_tac;
        TH1D * h_sci42_x_tac;
        
        //tof:
        TH1D * h_tof_4121_tac;
        TH1D * h_tof_4221_tac;
        TH1D * h_tof_4222_tac;
        TH1D * h_tof_4122_tac;

        TH2D * h_sci21_tpc_x_tac;
        TH2D * h_sci22_tpc_x_tac;
        TH2D * h_sci42_tpc_x_tac;
        TH2D * h_sci41_tpc_x_tac;
        
        
    public:
        ClassDef(TPCCorrections, 1)

};

#endif
