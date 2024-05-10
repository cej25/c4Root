#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairTask.h"

#include "LisaFrsCorrelations.h"
#include "FrsHitData.h"
#include "LisaCalData.h"
#include "TLisaConfiguration.h" // not here
#include "c4Logger.h"
#include "TFile.h"
#include "THttpServer.h"

LisaFrsCorrelations::LisaFrsCorrelations() 
    : LisaFrsCorrelations("LisaFrsCorrelations")
{

}

LisaFrsCorrelations::LisaFrsCorrelations(std::vector<FrsGate*> fg)
    : LisaFrsCorrelations("LisaFrsCorrelations")
{

}

LisaFrsCorrelations::LisaFrsCorrelations(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   header(nullptr)
    ,   lisaCalArray(nullptr)
    ,   frsHitArray(nullptr)
    ,   fNEvents(0)
{
    lisa_config = TLisaConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
}

LisaFrsCorrelations::~LisaFrsCorrelations()
{
    c4LOG(info, "Destroyed LisaFrsCorrelationsProperly.");
}

InitStatus LisaFrsCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");
    
    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    lisaCalArray = mgr->InitObjectAs<decltype(lisaCalArray)>("LisaCalData");
    c4LOG_IF(fatal, !lisaCalArray, "Branch LisaCalData not found!");
    frsHitArray = mgr->InitObjectAs<decltype(frsHitArray)>("FrsHitData");
    c4LOG_IF(fatal, !frsHitArray, "Branch FrsHitData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_corr = (TDirectory*)mgr->GetObject("Correlations");
    if (dir_corr == nullptr) 
    {   
        c4LOG(info, "Creating Correlations Directory");
        dir_corr = new TDirectory("Correlations", "Correlations", "", 0);
        mgr->Register("Correlations", "Correlations Directory", dir_corr, false); // allow other tasks to find this
        histograms->Add(dir_corr);
    }

    dir_lisa_frs = dir_corr->mkdir("LISA-FRS Correlations");


    //add histo


    return kSUCCESS;

}


// reset histo


void LisaFrsCorrelations::Exec(Option_t* option)
{   
    // reject events without both subsystems
    if (lisaCalArray->size() <= 0 || frsHitArray->size() <= 0) return;

    const auto & frsHitItem = frsHitArray->at(0); // *should* only be 1 FRS subevent per event

    // correlation with main FRS (10, 20, 30, 15)
    for (const auto & lisaCalItem : *lisaCalArray)
    {

        //same lisa online - loop through lisa item when match frs item

    }

    // correlation with travel music - reject if no subevent
    if (frsHitItem.Get_wr_travmus() == 0) return;

    for (const auto & lisaCalItem : *lisaCalArray)
    {

    }

    fNEvents++;

}

void LisaFrsCorrelations::FinishEvent()
{

}

void LisaFrsCorrelations::FinishTask()
{

}


ClassImp(LisaFrsCorrelations)