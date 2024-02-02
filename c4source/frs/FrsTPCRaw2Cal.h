#ifndef FrsTPCRaw2Cal_H
#define FrsTPCRaw2Cal_H

#include "TFRSParameter.h"
#include "FrsTPCCalData.h"
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
        void SetFRSParameters();

        virtual InitStatus Init();

        void Exec(Option_t* option);

        void ZeroArrays();
        void ZeroVariables();
        void ClearVectors();

        void FinishEvent();
        void FinishTask();

        void SetOnline(Bool_t set_online) { fOnline = set_online; }

    private:
        Bool_t fOnline;

        TClonesArray* fCalArray;
        TClonesArray* fRawArray;

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
        
        Int_t tpc_csum[7][4] = {0};
        Bool_t b_tpc_csum[7][4] = {0};

        Float_t tpc_x[7] = {0};
        Float_t tpc_y[7] = {0};

        Int_t tpc_xraw[7][2] = {0};
        Int_t tpc_yraw[7][4] = {0};
        Float_t tpc_dx12[7] = {0};

        Bool_t b_tpc_xy[7] = {0};

        //TPCs 21 & 22 @ S2 focus
        Float_t tpc_x_s2_foc_21_22 = 0;
        Float_t tpc_y_s2_foc_21_22 = 0;
        Float_t tpc_angle_x_s2_foc_21_22 = 0;
        Float_t tpc_angle_y_s2_foc_21_22 = 0;

        //TPCs 23 & 24 @ S2 focus
        Float_t tpc_x_s2_foc_23_24 = 0;
        Float_t tpc_y_s2_foc_23_24 = 0;
        Float_t tpc_angle_x_s2_foc_23_24 = 0;
        Float_t tpc_angle_y_s2_foc_23_24 = 0;

        //TPCs 22 & 24 @ S2 focus
        Float_t tpc_x_s2_foc_22_24 = 0;
        Float_t tpc_y_s2_foc_22_24 = 0;
        Float_t tpc_angle_x_s2_foc_22_24 = 0;
        Float_t tpc_angle_y_s2_foc_22_24 = 0;

        //TPCs 3 & 4 @ S2 focus (old tracking)
        Float_t tpc_x_s2_foc = 0;
        Float_t tpc_y_s2_foc = 0;
        Float_t tpc_angle_x_s2_foc = 0;
        Float_t tpc_angle_y_s2_foc = 0;

        //TPCs 41 & 42 @ s4 focus
        Float_t tpc_x_s4 = 0;
        Float_t tpc_y_s4 = 0;
        Float_t tpc_angle_x_s4 = 0;
        Float_t tpc_angle_y_s4 = 0;

        //TPCs 5 & 6 @ S4 OTPC (exp s388)
        Float_t tpc_x_s4_target2 = 0;
        Float_t tpc_y_s4_target2 = 0;

        Float_t tpc21_22_sc21_x = 0; /* SC21 x                    */
        Float_t tpc21_22_sc21_y = 0; /* SC21 y                    */
        Float_t tpc23_24_sc21_x = 0; /* SC21 x                    */
        Float_t tpc23_24_sc21_y = 0; /* SC21 y                    */
        Float_t tpc22_24_sc21_x = 0; /* SC21 x                    */
        Float_t tpc22_24_sc21_y = 0; /* SC21 y                    */

        Float_t tpc21_22_sc22_x; /* SC22 x                    */
        Float_t tpc21_22_sc22_y; /* SC22 y                    */
        Float_t tpc23_24_sc22_x; /* SC22 x                    */
        Float_t tpc23_24_sc22_y; /* SC22 x                    */
        Float_t tpc22_24_sc22_x; /* SC22 x                    */
        Float_t tpc22_24_sc22_y; /* SC22 x                    */

        Float_t tpc21_22_s2target_x; /* S2TARGET x                    */
        Float_t tpc21_22_s2target_y; /* S2TARGET y                    */
        Float_t tpc23_24_s2target_x; /* S2TARGET x                    */
        Float_t tpc23_24_s2target_y; /* S2TARGET y                    */
        Float_t tpc22_24_s2target_x; /* S2TARGET x                    */
        Float_t tpc22_24_s2target_y; /* S2TARGET y                    */
    
        //TPCs 3 & 4 @ S2 first Si tracking detector (exp s388)
        Float_t tpc_x_s2_target1;
        Float_t tpc_y_s2_target1;

        Float_t tpc_sc41_x; /* SC41 x */
        Float_t tpc_sc41_y; /* SC41 y */
        Float_t tpc_sc42_x; /* SC42 x */
        Float_t tpc_sc42_y; /* SC42 y */
        Float_t tpc_sc43_x; /* SC43 x */
        Float_t tpc_sc43_y; /* SC43 y */
        Float_t tpc_music41_x; /* MUSIC41 x                    */
        Float_t tpc_music41_y; /* MUSIC41 y                    */
        Float_t tpc_music42_x; /* MUSIC42 x                    */
        Float_t tpc_music42_y; /* MUSIC42 y                    */
        Float_t tpc_music43_x; /* MUSIC43 x                    */
        Float_t tpc_music43_y; /* MUSIC43 y                    */
        Float_t tpc_s4target_x; /* S4 target x                    */
        Float_t tpc_s4target_y; /* S4 target y                    */

        Float_t music1_x1; /* parameters to calibrate  */
        Float_t music1_x2; /* parameters to calibrate  */
        Float_t music1_x3; /* parameters to calibrate  */
        Float_t music1_x4; /* parameters to calibrate  */
        Float_t music1_y1; /* parameters to calibrate  */
        Float_t music1_y2; /* parameters to calibrate  */
        Float_t music1_y3; /* parameters to calibrate  */
        Float_t music1_y4; /* parameters to calibrate  */
        Float_t music2_x;  /* MUSIC1,2 positions */
        

        std::vector<Int_t> v1190_lead_hits[128];

        // Output


        EventHeader* header;
        Int_t fNEvents = 0;

    public:
        ClassDef(FrsTPCRaw2Cal, 1);
};

#endif