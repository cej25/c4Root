#ifndef FatimaVmeReader_H
#define FatimaVmeReader_H

#include "c4Reader.h"
#include "FatimaVmeData.h"
#include "../../config/setup.h"
#include <unordered_map>
#include <map>
#include <set>

#include <Rtypes.h>
#include <vector>
#include <iostream>

extern "C"
{
    #include "ext_h101_fatimavme.h"
}

class TClonesArray;
class FatimaVmeData;
// class vector;

struct EXT_STR_h101_fatimavme_t;
typedef struct EXT_STR_h101_fatimavme_t EXT_STR_h101_fatimavme;
typedef struct EXT_STR_h101_fatimavme_onion_t EXT_STR_h101_fatimavme_onion;
class ext_data_struct_info;

// struct
// jesus fatima reader got weird

class FatimaVmeReader : public c4Reader
{
    public:
        FatimaVmeReader(EXT_STR_h101_fatimavme_onion*, size_t);

        virtual ~FatimaVmeReader();

        virtual Bool_t Init(ext_data_struct_info*) override;

        virtual Bool_t Read() override;

        virtual void Reset() override;

        void SetOnline(Bool_t option) { fOnline = option; }
        void Set_Allocation(TString& filepath);

        std::vector<int> Get_Channels(Int_t channel_mask);

        // FT Calib?

        // GetFT?

        // misc...........


    private:

        Int_t fNEvent = 0;
        Bool_t fOnline;

        EXT_STR_h101_fatimavme_onion* fData;
        size_t fOffset;

        TClonesArray* fArray;

        std::map<std::pair<int, int>, int> dets_qdc;
        std::map<std::pair<int, int>, int> dets_tdc;
        std::set<int> extra_signals = {TM_U, TM_D, SC41L_A, SC41R_A, SC41L_D, SC41R_D};
        int num_qdc_boards;
        int num_tdc_boards;

        // bunch of stuff we might need
        
        /*
        std::vector<uint32_t> v1290_channel;
        std::vector<uint32_t> v1290_data;
        std::vector<uint32_t> v1290_lot;
        */

        // change to vectors when we figure this nonsense out.
        /*
        double Qlong[60] = {0};
        double Qlong_raw[60] = {0};
        double Qshort_raw[60] = {0};

        ULong64_t QDC_Time_Coarse[60] = {0};
        double QDC_Time_Fine[60] = {0};

        ULong64_t TDC_Time_raw[60] = {0};
        double TDC_Time_ns[60] = {0};

        int det_ids_QDC[60] = {0};
        int det_ids_TDC[60] = {0};

        double Scaler_Data[32] = {0}; // 32 = max scalers

        int det_ID_QDC[100][100] = {0}; //mhm
        int det_ID_TDC[100][100] = {0};


        int Fat_QDC_ID;
        int Fat_TDC_ID_sing;
        int Fat_TDC_ID[48];
        int Fat_TDC_multi[51];
        bool TimID[51];
        bool EnID[51];
        int counter = 0;

        // initialise in header, reset in Reset();
        Double_t dummy_qdc_E[51];
        Double_t dummy_qdc_E_raw[51];
        Long64_t dummy_qdc_t_coarse[51];
        Double_t dummy_qdc_t_fine[51];
        
        Double_t dummy_tdc_t[51];
        Double_t dummy_tdc_t_raw[51];

        int dummy_qdc_id[51];
        int dummy_tdc_id[51];

        int dummytdcmult = 0;
        int dummyqdcmult = 0;
        int matchedmult = 0;

        int sc40count = 0;
        int sc41count = 0;

        int FatVmeTMCh1_count = 0;
        int FatVmeTMCh2_count = 0;

        int singlesqdcmult = 0;
        int singlestdcmult = 0;

        bool tdc_multi_hit_exclude[100];
        bool qdc_multi_hit_exclude[100];
        */

        // number of QDC boards. etc

        uint64_t wr_t;


    public:
        ClassDefOverride(FatimaVmeReader, 1);

};


#endif