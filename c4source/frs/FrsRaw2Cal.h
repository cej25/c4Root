#ifndef FrsRaw2Cal_H
#define FrsRaw2Cal_H


#include "TFrsConfiguration.h"
#include "TFRSParameter.h"
#include "FrsData.h"
#include "FrsCalData.h"

#include <vector>


class TClonesArray;
class EventHeader;
typedef UInt_t UInt_t;

class FrsRaw2Cal : public FairTask
{
    public:
        FrsRaw2Cal();
        FrsRaw2Cal(const TString& name, Int_t verbose);
        
        ~FrsRaw2Cal();

        virtual InitStatus Init();
        void SetParameters();

        void Exec(Option_t* option);

        void ProcessScintillators();
        void ProcessTpcs();

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online) { fOnline = set_online; }


    private:
        Bool_t fOnline;
        EventHeader* header;
        Int_t fNEvents = 0;

        TFrsConfiguration const* frs_config;
        TFRSParameter* frs;
        TTPCParameter* tpc;

        // Arrays
        std::vector<FrsTpatItem> const* tpatArray;
        std::vector<FrsSciItem> const* sciArray;
        std::vector<FrsTpcItem> const* tpcArray;
        std::vector<FrsCalSciItem>* calSciArray;
        std::vector<FrsCalTpcItem>* calTpcArray;

        // TAC dE
        const UInt_t* sciDE; //16
        UInt_t de_21l;
        UInt_t de_21r;
        UInt_t de_22l;
        UInt_t de_22r;
        UInt_t de_31l;
        UInt_t de_31r;
        UInt_t de_41l;
        UInt_t de_41r;
        UInt_t de_42l;
        UInt_t de_42r;
        UInt_t de_43l;
        UInt_t de_43r;
        UInt_t de_81l;
        UInt_t de_81r;

        // TAC dT
        const UInt_t* sciDT; // 16
        UInt_t dt_21l_21r;
        UInt_t dt_22l_22r;
        UInt_t dt_41l_41r;
        UInt_t dt_42l_42r;
        UInt_t dt_43l_43r;
        UInt_t dt_81l_81r;
        UInt_t dt_21l_41l;
        UInt_t dt_21r_41r;
        UInt_t dt_42r_21r;
        UInt_t dt_42l_21l;
        UInt_t dt_21l_81l;
        UInt_t dt_21r_81r;
        UInt_t dt_22l_41l;
        UInt_t dt_22r_41r;
        UInt_t dt_22l_81l;
        UInt_t dt_22r_81r;

        // MHTDC
        const std::vector<Int_t>* sciMHTDC; // 16
        std::vector<Int_t> sci11_hits;
        std::vector<Int_t> sci21l_hits;
        std::vector<Int_t> sci21r_hits;
        std::vector<Int_t> sci22l_hits;
        std::vector<Int_t> sci22r_hits;
        std::vector<Int_t> sci31l_hits;
        std::vector<Int_t> sci31r_hits;
        std::vector<Int_t> sci41l_hits;
        std::vector<Int_t> sci41r_hits;
        std::vector<Int_t> sci42l_hits;
        std::vector<Int_t> sci42r_hits;
        std::vector<Int_t> sci43l_hits;
        std::vector<Int_t> sci43r_hits;
        std::vector<Int_t> sci81l_hits;
        std::vector<Int_t> sci81r_hits;


        // TPC
        const UInt_t (*adcData)[8]; // 7, 8
        const std::vector<UInt_t>* tdcData;



        /*  -------- v1190 channel mappings ----------*/
        Int_t v1190_channel_dt[7][4];
        Int_t v1190_channel_lt[7][2];
        Int_t v1190_channel_rt[7][2];
        Int_t v1190_channel_timeref[8];
        Int_t v1190_channel_calibgrid[7];
        /* ------------------------------------------ */

        Int_t tpc_a[7][4] = {0};
        Int_t tpc_l[7][2] = {0};
        Int_t tpc_r[7][2] = {0};
        std::vector<Int_t> tpc_calibgrid[7];
        std::vector<Int_t> tpc_timeref[8];
        Bool_t b_tpc_timeref[8] = {0};
        Int_t tpc_timeref_s[8] = {0};

        std::vector<Int_t> tpc_dt[7][4];
        std::vector<Int_t> tpc_lt[7][2];
        std::vector<Int_t> tpc_rt[7][2];
        Int_t tpc_dt_s[7][4] = {0};
        Int_t tpc_lt_s[7][2] = {0};
        Int_t tpc_rt_s[7][2] = {0};
        Float_t tpc_de[7] = {0};
        Bool_t b_tpc_de[7] = {0};

        Int_t tpc_csum[7][4];
        Bool_t b_tpc_xy[7];
        
        //Int_t tpc_csum[7][4] = {-9999999};
        Bool_t b_tpc_csum[7][4] = {false};
        
        Float_t tpc_x[7] = {0};
        Float_t tpc_y[7] = {0};

        Int_t tpc_xraw[7][2] = {0};
        Int_t tpc_yraw[7][4] = {0};
        Float_t tpc_dx12[7] = {0};

        //Bool_t b_tpc_xy[7] = {0};

        //TPCs 21 & 22 @ S2 focus
        Float_t tpc_x_s2_foc_21_22 = -999;
        Float_t tpc_y_s2_foc_21_22 = -999;
        Float_t tpc_angle_x_s2_foc_21_22 = -999;
        Float_t tpc_angle_y_s2_foc_21_22 = -999;

        //TPCs 23 & 24 @ S2 focus
        Float_t tpc_x_s2_foc_23_24 = -999;
        Float_t tpc_y_s2_foc_23_24 = -999;
        Float_t tpc_angle_x_s2_foc_23_24 = -999;
        Float_t tpc_angle_y_s2_foc_23_24 = -999;

        //TPCs 22 & 24 @ S2 focus
        Float_t tpc_x_s2_foc_22_24 = -999;
        Float_t tpc_y_s2_foc_22_24 = -999;
        Float_t tpc_angle_x_s2_foc_22_24 = -999;
        Float_t tpc_angle_y_s2_foc_22_24 = -999;

        //TPCs 3 & 4 @ S2 focus (old tracking)
        Float_t tpc_x_s2_foc = -999;
        Float_t tpc_y_s2_foc = -999;
        Float_t tpc_angle_x_s2_foc = -999;
        Float_t tpc_angle_y_s2_foc = -999;

        //TPCs 41 & 42 @ s4 focus
        Float_t tpc_x_s4 = -999;
        Float_t tpc_y_s4 = -999;
        Float_t tpc_angle_x_s4 = -999;
        Float_t tpc_angle_y_s4 = -999;

        //TPCs 5 & 6 @ S4 OTPC (exp s388)
        Float_t tpc_x_s4_target2 = -999;
        Float_t tpc_y_s4_target2 = -999;

        Float_t tpc21_22_sc21_x = -999; /* SC21 x                    */
        Float_t tpc21_22_sc21_y = -999; /* SC21 y                    */
        Float_t tpc23_24_sc21_x = -999; /* SC21 x                    */
        Float_t tpc23_24_sc21_y = -999; /* SC21 y                    */
        Float_t tpc22_24_sc21_x = -999; /* SC21 x                    */
        Float_t tpc22_24_sc21_y = -999; /* SC21 y                    */

        Float_t tpc21_22_sc22_x = -999; /* SC22 x                    */
        Float_t tpc21_22_sc22_y = -999; /* SC22 y                    */
        Float_t tpc23_24_sc22_x = -999; /* SC22 x                    */
        Float_t tpc23_24_sc22_y = -999; /* SC22 x                    */
        Float_t tpc22_24_sc22_x = -999; /* SC22 x                    */
        Float_t tpc22_24_sc22_y = -999; /* SC22 x                    */

        Float_t tpc21_22_s2target_x = -999; /* S2TARGET x                    */
        Float_t tpc21_22_s2target_y = -999; /* S2TARGET y                    */
        Float_t tpc23_24_s2target_x = -999; /* S2TARGET x                    */
        Float_t tpc23_24_s2target_y = -999; /* S2TARGET y                    */
        Float_t tpc22_24_s2target_x = -999; /* S2TARGET x                    */
        Float_t tpc22_24_s2target_y = -999; /* S2TARGET y                    */
    
        //TPCs 3 & 4 @ S2 first Si tracking detector (exp s388)
        Float_t tpc_x_s2_target1 = -999;
        Float_t tpc_y_s2_target1 = -999;

        Float_t tpc_sc41_x = -999; /* SC41 x */
        Float_t tpc_sc41_y = -999; /* SC41 y */
        Float_t tpc_sc42_x = -999; /* SC42 x */
        Float_t tpc_sc42_y = -999; /* SC42 y */
        Float_t tpc_sc43_x = -999; /* SC43 x */
        Float_t tpc_sc43_y = -999; /* SC43 y */
        Float_t tpc_music41_x = -999; /* MUSIC41 x                    */
        Float_t tpc_music41_y = -999; /* MUSIC41 y                    */
        Float_t tpc_music42_x = -999; /* MUSIC42 x                    */
        Float_t tpc_music42_y = -999; /* MUSIC42 y                    */
        Float_t tpc_music43_x = -999; /* MUSIC43 x                    */
        Float_t tpc_music43_y = -999; /* MUSIC43 y                    */
        Float_t tpc_s4target_x = -999; /* S4 target x                    */
        Float_t tpc_s4target_y = -999; /* S4 target y                    */

        Float_t music1_x1 = -999; /* parameters to calibrate  */
        Float_t music1_x2 = -999; /* parameters to calibrate  */
        Float_t music1_x3 = -999; /* parameters to calibrate  */
        Float_t music1_x4 = -999; /* parameters to calibrate  */
        Float_t music1_y1 = -999; /* parameters to calibrate  */
        Float_t music1_y2 = -999; /* parameters to calibrate  */
        Float_t music1_y3 = -999; /* parameters to calibrate  */
        Float_t music1_y4 = -999; /* parameters to calibrate  */
        Float_t music2_x = -999;  /* MUSIC1,2 positions */



    public:
        ClassDef(FrsRaw2Cal, 1);

};


#endif