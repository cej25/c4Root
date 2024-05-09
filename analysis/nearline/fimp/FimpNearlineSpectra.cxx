// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "EventHeader.h"
#include "FimpNearlineSpectra.h"
#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include "TRandom.h"
#include <string>

FimpNearlineSpectra::FimpNearlineSpectra()
{
    fimp_config = TFimpConfiguration::GetInstance();
}

FimpNearlineSpectra::FimpNearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fNEvents(0)
    , header(nullptr)
{
    
}

FimpNearlineSpectra::~FimpNearlineSpectra()
{
    c4LOG(info, "");
}

InitStatus FimpNearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    // FairRunAna?

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fimpCalArray = mgr->InitObjectAs<decltype(fimpCalArray)>("FimpCalData");
    c4LOG_IF(fatal, !fimpCalArray, "Branch FimpCalData not found!");

    auto const & detector_mapping = fimp_config->Mapping();

    TDirectory::TContext ctx(nullptr);

    dir_fimp = new TDirectory("FIMP", "FIMP", "", 0);
    mgr->Register("FIMP", "FIMP Directory", dir_fimp, false);

    dir_fimp->cd();
    dir_stats = dir_fimp->mkdir("Stats");

    return kSUCCESS;
}

void FimpNearlineSpectra::Exec(Option_t* option)
{   
    fNEvents += 1;
}

void FimpNearlineSpectra::FinishEvent()
{

}

void FimpNearlineSpectra::FinishTask()
{
    // write!!
}

ClassImp(FimpNearlineSpectra)
