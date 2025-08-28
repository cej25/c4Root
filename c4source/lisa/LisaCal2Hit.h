#ifndef LisaCal2Hit_H
#define LisaCal2Hit_H

#include "TClonesArray.h"
#include "EventHeader.h"
#include "TLisaConfiguration.h"
#include "TFrsConfiguration.h"
#include "TExperimentConfiguration.h"
#include "LisaData.h"
#include "LisaCalData.h"
#include "LisaAnaData.h"
#include "LisaHitData.h"
#include "FrsData.h"
#include "FrsCalData.h"
#include "FrsHitData.h"
#include <map>
#include <vector>
#include "TVector.h"

class EventHeader;
class LisaItem;
class LisaCalItem;
class LisaAnaItem;
class LisaHitItem;
class FrsHitItem;
class FrsMultiHitItem;

class LisaCal2Hit : public FairTask
{
    public:
        LisaCal2Hit();

        virtual ~LisaCal2Hit();

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
    
        std::vector<LisaItem> const* lisaArray;
        std::vector<LisaAnaItem> const* lisaAnaArray;
        std::vector<LisaCalItem> const* lisaCalArray;
        std::vector<LisaHitItem>* lisaHitArray;
        std::vector<FrsHitItem> const* frsHitArray;
        std::vector<FrsMultiHitItem> const* multihitArray;
      

        EventHeader* header;
        Bool_t fOnline;
        Int_t fNEvents;

        uint64_t wr_t;

        int layer_number;

        std::map<std::pair<int,int>, std::pair<std::pair<int, std::pair<int, int>>,std::pair<float,std::pair<std::string,std::string>>>> detector_mapping; //Debugging.Raplace std:string-> TString ?
        std::map<std::pair<int,std::pair<int,int>>, std::pair<double,double>> detector_z_calibration;

        float conv_coeff = 931.494; //Conversion coefficient form mass to MeV 
        int m_layer1 = 0;
        int m_layer2 = 0;
        int m_layer3 = 0;
        int m_layer4 = 0;
        int m_layer5 = 0;

        float gamma_after1 = 0;

        
        std::vector<Float_t> aoq0;
        std::vector<Float_t> z0;

        std::vector<Float_t> beta0;
        std::vector<Float_t> beta1;
        std::vector<Float_t> beta2;
        std::vector<Float_t> beta3;
        std::vector<Float_t> beta4;
        std::vector<Float_t> beta5;

        std::vector<Float_t> gamma0;
        std::vector<Float_t> gamma1;
        std::vector<Float_t> gamma2;
        std::vector<Float_t> gamma3;
        std::vector<Float_t> gamma4;
        std::vector<Float_t> gamma5;

        std::vector<Float_t> beta_en0;
        std::vector<Float_t> beta_en1;
        std::vector<Float_t> beta_en2;
        std::vector<Float_t> beta_en3;
        std::vector<Float_t> beta_en4;
        std::vector<Float_t> beta_en5;

        std::vector<Int_t> xpos_1;
        std::vector<Int_t> ypos_1;
        std::vector<Int_t> thickness_1;
        std::vector<Int_t> thickness_2;

        double slope_z;
        double intercept_z;
        float de_dx_corr;
        std::vector<float> z_lisa;


    public:
        ClassDef(LisaCal2Hit, 1)

};



#endif