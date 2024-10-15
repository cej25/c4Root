#ifndef BetaIonTrees_H
#define BetaIonTrees_H

#include "AidaCalData.h"
#include "AidaData.h"
#include "AidaHitData.h"

#include "GermaniumCalData.h"

#include "TGermaniumConfiguration.h"
#include "TAidaConfiguration.h"
#include "TFrsConfiguration.h"
#include "TbPlastConfiguration.h"

#include "FrsGate.h"
#include "FrsHitData.h"

#include "FairTask.h"
#include <array>
#include <vector>

class TClonesArray;
class EventHeader;
class EventData;
class TCanvas;
class TH1F;
class TH2F;

using ImplantMap = std::multimap<int64_t, std::pair<AidaHit, std::vector<std::pair<AidaHit, std::vector<GermaniumCalData>>>>>;

class BetaIonTrees : public FairTask
{
    public:
        BetaIonTrees();
        BetaIonTrees(std::vector<FrsGate*> fgs);
        BetaIonTrees(const TString& name, Int_t verbose = 1); // used for online, generally not an online task

        virtual ~BetaIonTrees();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        double CalcLL(double, double);
        
        virtual void FinishEvent();

        virtual void FinishTask();


    private:

        TGermaniumConfiguration const* germanium_config;
        TFrsConfiguration const* frs_config;
        TbPlastConfiguration const* bplast_config;
        TAidaConfiguration const* aida_config;

        std::vector<FrsGate*> FrsGates;

        TClonesArray* fHitbPlastTwinpeaks;
        TClonesArray* fHitGe;
        std::vector<AidaHit> const* implantHitArray;
        std::vector<AidaHit> const* decayHitArray;
        std::vector<FrsHitItem> const* hitArrayFrs;

        TDirectory* dir_corrs;
        TDirectory* dir_beta_gamma;
        bool found_dir_corrs = true;

     

      

        std::multimap<int64_t , AidaHit> implantMap;
        std::multimap<int64_t, std::pair<AidaHit, std::vector<std::pair<AidaHit,std::vector<GermaniumCalData*>>>>> implant_map;
        std::multimap<int64_t, AidaHit> implantMapBkg;
        std::multimap<int64_t, std::pair<AidaHit, std::vector<AidaHit>>> CandidateMap; 
        //std::multimap<int64_t, std::pair<AidaHit, AidaHit>> implant_decay_map;
        std::multimap<int64_t, std::pair<AidaHit, std::pair<AidaHit,std::vector<GermaniumCalData*>>>> implant_decay_map;

        // can read these values from correlations.dat if needed
        Int_t WR_AIDA_GE_LO = -18000;
        Int_t WR_AIDA_GE_HI = -12000;

        Int_t AidaFB_dTcond = 3000;
        Int_t AidaFB_dEcond = 200;
        Int_t FrontBack_dT = 3000;
        Int_t FrontBack_dE = 200;

        double corrTime = 75e9;
        double longBkg = 200e9;

        // ns->s * n_halflives * halflife
        int64_t correlation_window;
        // halflife / ln(2)
        int64_t mean_lifetime;

        int nImplants = 0;
        int nDecays = 0;
        int nDecaysTotal = 0;
        int nGammas = 0;
        int nPass = 0;
        int nID_Pairs = 0;

        int nGammasInRange = 0;
        int nGammasOutOfRange = 0;


        Int_t fNEvents;
        EventHeader* header;


    public:
        ClassDef(BetaIonTrees, 1)
};

#endif
