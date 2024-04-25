#ifndef FrsTPCRaw2Cal_H
#define FrsTPCRaw2Cal_H

#include "TFrsConfiguration.h"
#include "TFRSParameter.h"
#include "FrsTPCCalData.h"
#include "FrsTPCData.h"
#include <vector>

class TClonesArray;
class EventHeader;
class FrsTPCData;
class FrsTPCCalData;

class FrsTPCRaw2Cal : public FairTask
{
    public:
        FrsTPCRaw2Cal();

        FrsTPCRaw2Cal(const TString& name, Int_t verbose);

        ~FrsTPCRaw2Cal();

        void SetParameters();

        virtual InitStatus Init();

        void Exec(Option_t* option);

        void ZeroArrays();
        void ZeroVariables();
        void ClearVectors();

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online) { fOnline = set_online; }

    private:
        TFrsConfiguration const* frs_config;

        Bool_t fOnline;

        std::vector<FrsTPCV7X5Item> const* v7x5array;
        std::vector<FrsTPCV1190Item> const* v1190array;
        std::vector<FrsTPCCalItem>* tpcCalArray;

        FrsTPCData* fRawHit;

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

        std::vector<uint32_t>* v7x5_geo;
        std::vector<uint32_t>* v7x5_channel;
        std::vector<uint32_t>* v7x5_data;

        std::vector<uint32_t> v1190_channel;
        std::vector<uint32_t> v1190_data;
        std::vector<uint32_t> v1190_lot;

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

        Int_t** tpc_csum;
        Bool_t* b_tpc_xy;
        
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

        EventHeader* header;
        Int_t fNEvents = 0;

    public:
        ClassDef(FrsTPCRaw2Cal, 1);
};

#endif