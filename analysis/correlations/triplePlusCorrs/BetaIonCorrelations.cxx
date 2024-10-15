// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BetaIonCorrelations.h"
#include "EventHeader.h"
#include "bPlastTwinpeaksCalData.h"
#include "GermaniumFebexData.h"
#include "FrsHitData.h"
#include "AidaData.h"
#include "AidaHitData.h"

#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TDirectory.h"

BetaIonCorrelations::BetaIonCorrelations() : BetaIonCorrelations("BetaIonCorrelations")
{
    germanium_config = TGermaniumConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    bplast_config = TbPlastConfiguration::GetInstance();
    aida_config = TAidaConfiguration::GetInstance();
}

BetaIonCorrelations::BetaIonCorrelations(std::vector<FrsGate*> fgs) : BetaIonCorrelations("BetaIonCorrelations")
{
    germanium_config = TGermaniumConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    bplast_config = TbPlastConfiguration::GetInstance();
    aida_config = TAidaConfiguration::GetInstance();

    FrsGates = fgs;
}

BetaIonCorrelations::BetaIonCorrelations(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitbPlastTwinpeaks(NULL)
    , fHitGe(NULL)
    , implantHitArray(nullptr)
    , decayHitArray(nullptr)
    , fNEvents(0)
    , header(nullptr)
{
}

BetaIonCorrelations::~BetaIonCorrelations()
{
    c4LOG(info, "");
    if (fHitbPlastTwinpeaks)
        delete fHitbPlastTwinpeaks;
    if (fHitGe)
        delete fHitGe;
   
}


InitStatus BetaIonCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance(); // do we need to grab the run? maybe we can add objects to it

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    // Hit data
    implantHitArray = mgr->InitObjectAs<decltype(implantHitArray)>("AidaImplantHits");
    c4LOG_IF(fatal, !implantHitArray, "Branch AidaImplantHits not found!");
    decayHitArray = mgr->InitObjectAs<decltype(decayHitArray)>("AidaDecayHits");
    c4LOG_IF(fatal, !decayHitArray, "Branch AidaDecayHits not found!");
    // fHitbPlastTwinpeaks = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksCalData");
    // c4LOG_IF(fatal, !fHitbPlastTwinpeaks, "Branch bPlastTwinpeaksCalData not found!");
    fHitGe = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fHitGe, "Branch GermaniumCalData not found!");
    hitArrayFrs = mgr->InitObjectAs<decltype(hitArrayFrs)>("FrsHitData");
    c4LOG_IF(fatal, !hitArrayFrs, "Branch FrsHitData not found!");

    dir_corrs = (TDirectory*)mgr->GetObject("Correlations");
    if (dir_corrs == nullptr) 
    {
        LOG(info) << "Creating Correlations Directory";
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_corrs = gDirectory->mkdir("Correlations");
        mgr->Register("Correlations", "Correlations Directory", dir_corrs, false); // allow other tasks to find this
        found_dir_corrs = false;
    }


    // get correlations folder?
    dir_beta_gamma = dir_corrs->mkdir("Beta-Gamma");

    int xstrips = aida_config->Wide() ? 386 : 128;
    double xmax = aida_config->Wide() ? 113.4 : 37.8;

    nGates = FrsGates.size();

   // h1_implant_decay_dt.resize(nGates);
   // for (int i = 0; i < nGates; i++) h1_implant_decay_dt[i] = MakeTH1(dir_beta_gamma, "F", Form("h1_implant_decay_dt_gate%i", i), Form("Implant-Decay dT - Gate %i", i), 2000, 0, 2000);
    
    int half_lifes[8];
    half_lifes[0] = 25.6;
    int half_life = 25.6;
    // ns->s * n_halflives * half_life
    correlation_window = 1e9 * 3 * half_life;
    // ns->s * half_life / ln(2)
    mean_lifetime = 1e9 * half_life / 0.69314718056;


  

    c4LOG(info, "Success");

    return kSUCCESS;
    
}


void BetaIonCorrelations::Exec(Option_t* option)
{
    fNEvents += 1;

    if (hitArrayFrs->size() > 0)
    {
        

    } // some FRS hit exists
    else nNoFrs++;


    if (fNEvents % 1000000 == 0)
    {
        std::cout << "Processed " << fNEvents << " events.\n";
    }

}

// in progress
double BetaIonCorrelations::CalcLL(double time, double lifetime)
{   
    // BAD, INCORRECT CALCULATION THAT RETURNS THE SAME RESULT FOR NOW

    double likelihood = 1 / TMath::Abs(time - lifetime);
    return likelihood;
}

void BetaIonCorrelations::FinishEvent()
{

}

void BetaIonCorrelations::FinishTask()
{
    c4LOG(info, "TERMINATION: " << fNEvents << " EVENTS PROCESSED!");
    c4LOG(info, "Total FRS hits: " << nFrsHitsAll);
    if (!FrsGates.empty()) for (int gate = 0; gate < FrsGates.size(); gate++) c4LOG(info, "Hits inside gate " << gate << ": " << nPassFrsGate[gate]);
    c4LOG(info, "Rejected for no FRS: " << nNoFrs);
    c4LOG(info, "Total implants: " << totalImplants);
    if (!FrsGates.empty()) for (int gate = 0; gate < FrsGates.size(); gate++) c4LOG(info, "Implants correlated to gate " << gate << ": " << nImplants[gate]);

    c4LOG(info, "Correlated: " << nCorrelated);

    if (found_dir_corrs == false) // && FairRunOnline::Instance() == NULL 
    {
        std::cout << "we should now be writing to file.. " << std::endl;
        TDirectory* tmp = gDirectory;
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_corrs->Write();
        gDirectory = tmp;
        c4LOG(info, "Written Beta-Ion Correlations histograms to file.");
    }
}

ClassImp(BetaIonCorrelations)


// so should we erase an implant from the map once we determine which decay its paired with?