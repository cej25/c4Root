#ifndef FrsCal2Hit_H
#define FrsCal2Hit_H

#include "FairTask.h"
#include "TFRSParameter.h"
#include "TClonesArray.h"
#include "FrsCalData.h"
#include "FrsHitData.h"

class TClonesArray;
class FrsCalData;
class FrsHitData;
class EventHeader;

class FrsCal2Hit : public FairTask
{
    public:
        FrsCal2Hit();
        FrsCal2Hit(const TString& name, Int_t verbose);

        virtual ~FrsCal2Hit();
        
        virtual InitStatus Init();
        virtual InitStatus ReInit();

        virtual void Exec(Option_t* option); // virtual?
        
        void SetParameters();
        virtual void SetParContainers();

        Bool_t Check_WinCond(Float_t P, Float_t* V);

        void FinishEvent();
        void FinishTask();
        
        
        void SetOnline(Bool_t option) { fOnline = option; }
    
    private:

        Bool_t fOnline;

        TClonesArray* fCalArray;
        TClonesArray* fHitArray;

        FrsCalData* fCalHit;
        FrsHitData* fFrsHit;

        /* ----------------------------------------------- */
        // Intermediate variables
        /* ----------------------------------------------- */
        const std::vector<uint32_t>* tdc_array;
        const uint32_t* de_array;
        const uint32_t* dt_array; // not coded in raw->cal yet
        Float_t de[3];
        Float_t de_cor[3];
        uint32_t sci_l[6]; // may change when i know the actual dimensions necessary
        uint32_t sci_r[6];
        uint32_t sci_tx[6];
        uint32_t sci_e[6];
        uint32_t sci_x[6];
        Bool_t sci_b_l[12]; // size may be reduced
        Bool_t sci_b_r[12]; // size may be reduced
        Bool_t sci_b_e[12]; // size may be reduced
        Bool_t sci_b_tx[12]; // size may be reduced
        Bool_t sci_b_x[12]; // size may be reduced
        Bool_t sci_b_tofll2;
        Bool_t sci_b_tofrr2;
        Float_t cSCI_L[2]; // these get read from file? should it be a pointer?
        Float_t cSCI_R[2]; // read in for file etc.
        Float_t cSCI_E[2];
        Float_t cSCI_Tx[2];
        Float_t cSCI_X[2];
        Float_t cID_x2[2];
        Float_t cID_x4[2];
        Float_t cID_Z_Z[2];
        Bool_t b_tpc_xy[7];
        Bool_t b_tpc_de[7];
        Bool_t b_tpc_timeref[8];
        Bool_t b_tpc_csum[7][4];
        Float_t tpc_x_s4;
        Float_t tpc_y_s4;
        Float_t tpc_angle_x_s4;
        Float_t tpc_angle_y_s4;
        Bool_t id_b_x2;
        Bool_t id_b_x4;
        Bool_t id_b_AoQ;
        Bool_t id_b_z;
        Bool_t id_b_z2;
        Bool_t id_b_z3;
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

        /* ----------------------------------------------- */
        //Hit variables
        /* ----------------------------------------------- */
        uint64_t WR_TS;

        Float_t id_x2;
        Float_t id_y2;
        Float_t id_a2;
        Float_t id_b2;
        Float_t id_x4;
        Float_t id_y4;
        Float_t id_a4;
        Float_t id_b4;
        Float_t id_x8;
        Float_t id_y8;
        Float_t id_a8;
        Float_t id_b8;
        Float_t id_rho[2];
        Float_t id_brho[2];
        Float_t id_beta;
        Float_t id_gamma;
        Float_t id_AoQ;
        Float_t id_AoQ_corr;
        Float_t id_v_cor;
        Float_t id_v_cor2;
        Float_t id_v_cor3;
        Float_t id_z;
        Float_t id_z2;
        Float_t id_z3;
        Float_t id_gamma_ta_s2;
        Float_t id_dEdegoQ;
        Float_t id_dEdeg;

        // parameters from FRS setup // need to figure out how to load with steering macro?
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

        EventHeader* header;
        Int_t fNEvents = 0;

        // analysis stuff..

    public:
        ClassDef(FrsCal2Hit, 1);

};

#endif