// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "AidaOnlineSpectra.h"
#include "EventHeader.h"
#include "c4Logger.h"
#include "AidaData.h"


#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"

AidaOnlineSpectra::AidaOnlineSpectra()
{
}

AidaOnlineSpectra::AidaOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , adcArray(nullptr)
    , flowArray(nullptr)
    , scalerArray(nullptr)
    , header(nullptr)
    , fNEvents(0)
    // ranges
{
}

AidaOnlineSpectra::~AidaOnlineSpectra()
{
    c4LOG(info, "");
    // do we delete pointers? we didn't create them
}

void AidaOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus AidaOnlineSpectra::Init()
{
    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    adcArray = mgr->InitObjectAs<decltype(adcArray)>("AidaAdcData");
    c4LOG_IF(fatal, !adcArray, "Branch AidaAdcData not found!");
    //flowArray = (flowArray))mgr->GetObject("AidaFlowData");
    //c4LOG_IF(fatal, !adcArray, "Branch AidaFlowData not found!");
    //scalerArray = (decltype(scalerArray))mgr->GetObject("AidaScalerData");
    //c4LOG_IF(fatal, !adcArray, "Branch AidaScalerData not found!");

    TFolder *aidaFold = new TFolder("Aida", "Aida");

    // TODO: use aida config?
    fhAdcs.resize(12);
    for (int i = 0; i < 12; i++)
    {
        TFolder *feeFolder = new TFolder(Form("DSSD%d", i), Form("DSSD%d", i));
        aidaFold->Add(feeFolder);
        
        TFolder* decay = new TFolder("Decay", "Decay");
        feeFolder->Add(decay);
        for (int j = 0; j < 64; j++)
        {
            fhAdcs[i][j][0] = new TH1F(Form("Aida_Decay_DSSD%d_Ch%d", i, j), Form(":)"), 65536, 0, 65536);
            decay->Add(fhAdcs[i][j][0]);
        }
    }

    run->AddObject(aidaFold);

    run->GetHttpServer()->RegisterCommand("Reset_Aida_Hist", Form("/Objects/%s/->Reset_Histo()", GetName()));

    return kSUCCESS;
}

void AidaOnlineSpectra::Reset_Histo()
{
    c4LOG(info, "");
}

void AidaOnlineSpectra::Exec(Option_t* option)
{   
    for (auto const& entry : *adcArray)
    {
        int fee = entry.Fee();
        bool implant = entry.Range();
        int channel = entry.Channel();
        uint16_t value = entry.Value();

        int implantIdx = implant ? 1 : 0;

        if (!implant)
            fhAdcs[fee - 1][channel][implantIdx]->Fill(value);
    }
    fNEvents += 1;
}

void AidaOnlineSpectra::FinishEvent()
{
}

void AidaOnlineSpectra::FinishTask()
{
}

ClassImp(AidaOnlineSpectra)
