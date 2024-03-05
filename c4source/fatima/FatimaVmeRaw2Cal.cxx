// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaVmeData.h"
//#include "FatimaVmeCalData.h"
//#include "TimeMachineData.h" // ? maybe
#include "c4Logger.h"

#include "TClonesArray.h"

#include "FatimaVmeRaw2Cal.h"

FatimaVmeRaw2Cal::FatimaVmeRaw2Cal()
    :   FairTask
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    //,

{
}

// named constructor
FatimaVmeRaw2Cal::FatimaVmeRaw2Cal(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    //,
{
}

FatimaVmeRaw2Cal::~FatimaVmeRaw2Cal()
{
    c4LOG(info, "Deleting FatimaVmeRaw2Cal task");

    // delete
    
}

InitStatus FatimaVmeRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    funcal_data = (TClonesArray*)mgr->GetObject("FatimaVmeData");
    c4LOG_IF(fatal, !funcal_data, "Fatima branch of FatimaVmeData not found!");

    mgr->Register("FatimaVmeCalData", "FatimaVmeCalDataFolder", fcal_data, !fOnline);
    // time machine?

    fcal_data->Clear();

    return kSUCCESS;
 
}



void FatimaVmeRaw2Cal::Exec(Option_t* option)
{
    // if (funcal_data && funcal_data->GetEntriesFast() > )

    int Fat_QDC_ID;
    int Fat_TDC_ID_single;
    int Fat_TDC_ID[48];// ? why 
    int Fat_TDC_multi[51]// max VME channels?
    bool TimID[51];
    bool EnID[51];
    int counter = 0;
    int dummy_qdc_id[51];
    Double_t dummy_qdc_E[51];
    Double_t dummy_qdc_E_raw[51];
    Long64_t dummy_qdc_t_coarse[51];
    Double_t dummy_qdc_t_fine[51]; // do these even get used
    int dummy_tdc_id[51];
    Double_t dummy_tdc_t[51];
    Double_t dummy_tdc_t_raw[51];

    int dum_qdc_id[51];
    int dum_tdc_id[51];

    int dummyqdcmult = 0;
    int dummytdcmult = 0;
    int matchedmult = 0;
    int sc40count = 0;
    int sc41count = 0;



   
}
