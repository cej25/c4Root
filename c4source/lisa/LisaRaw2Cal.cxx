// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "LisaRaw2Cal.h"
#include "c4Logger.h"

// ROOT
#include "TClonesArray.h"
#include <vector>

LisaRaw2Cal::LisaRaw2Cal()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
    ,   fOnline(kFALSE)
    ,   fLisaArray(new TClonesArray("LisaData"))
    ,   fLisaCalArray(new TClonesArray("LisaCalData"))
    //,   fTimeMachineArray(new TClonesArray("TimeMachineData"))
{
    lisa_config = TLisaConfiguration::GetInstance();
    detector_mapping = lisa_config->Mapping();
}

LisaRaw2Cal::~LisaRaw2Cal()
{
    if (fLisaArray) delete fLisaArray;
    if (fLisaCalArray) delete fLisaCalArray;
    //if (fTimeMachineArray) delete fTimeMachineArray;
}

InitStatus LisaRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fLisaArray = (TClonesArray*)mgr->GetObject("LisaData");
    c4LOG_IF(fatal, !fLisaArray, "Lisa branch of LisaData not found.");
    
    FairRootManager::Instance()->Register("LisaCalData", "Lisa Cal Data", fLisaCalArray, !fOnline);
    //FairRootManager::Instance()->Register("LisaTimeMachineData", "Lisa TimeMachine Data", fTimeMachineArray, !fOnline);

    fLisaArray->Clear();
    fLisaCalArray->Clear();

    return kSUCCESS;
}

void LisaRaw2Cal::Exec(Option_t* option)
{
    if (fLisaArray && fLisaArray->GetEntriesFast() > 0)
    {
        Int_t nHits = fLisaArray->GetEntriesFast() > 0;
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            LisaData* lisa_item = (LisaData*)fLisaArray->At(ihit);
            if (!lisa_item) continue;

            // get boards, channel ids (vectors)
            // loop through boards, channels
                // if mapping is loaded do mapping
                    // create std::pair<int, int> of board, channel
                    // if (mapping.count(unmapped) > 0)
                        // extract layer, x, y
                        // add to vector
                        // add e, traces etc to new vector
            

                // calibration of energy whatever ...
            
            LisaCalData* lisa_cal_item = new LisaCalData();

            // set layer, x, y, e, traces etc. vectors into new caldata_item

            new ((*fLisaCalArray)[fLisaCalArray->GetEntriesFast()]) LisaCalData(*lisa_cal_item);
            
        }
    }


}



void LisaRaw2Cal::FinishEvent()
{
    fLisaArray->Clear();
    fLisaCalArray->Clear();
    //fTimeMachineArray->Clear();
}

void LisaRaw2Cal::FinishTask()
{
}