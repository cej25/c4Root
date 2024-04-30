// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "EventHeader.h"
#include "FimpOnlineSpectra.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <string>

FimpOnlineSpectra::FimpOnlineSpectra()
{
    fimp_config = TFimpConfiguration::GetInstance();
}

FimpOnlineSpectra::FimpOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fNEvents(0)
    , header(nullptr)
{
    
}

FimpOnlineSpectra::~FimpOnlineSpectra()
{
    c4LOG(info, "");
}

InitStatus FimpOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fimpCalArray = mgr->InitObjectAs<decltype(fimpCalArray)>("FimpCalData");
    c4LOG_IF(fatal, !fimpCalArray, "Branch FimpCalData not found!");

    auto const & detector_mapping = fimp_config->Mapping();

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_fimp = new TDirectory("FIMP", "FIMP", "", 0);
    mgr->Register("FIMP", "FIMP Directory", dir_fimp, false);
    histograms->Add(dir_fimp);

    dir_fimp->cd();
    dir_stats = dir_fimp->mkdir("Stats");

    run->GetHttpServer()->RegisterCommand("Reset_Fimp_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void FimpOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
}

void FimpOnlineSpectra::Exec(Option_t* option)
{   
    fNEvents += 1;
}

void FimpOnlineSpectra::FinishEvent()
{

}

void FimpOnlineSpectra::FinishTask()
{

}

ClassImp(FimpOnlineSpectra)
