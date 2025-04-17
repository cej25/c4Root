// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "GermaniumFebexData.h"
#include "GermaniumCalData.h"
#include "TGermaniumConfiguration.h"
#include "TimeMachineData.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "StefanRaw2Cal.h"

/*
Empty constructor for FairRoot.
*/
StefanRaw2Cal::StefanRaw2Cal()
    :   FairTask() 
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    // OTHER STUFF 
    // ,   ftime_machine_array(new TClonesArray("TimeMachineData"))
{
    stefan_config = TStefanConfiguration::GetInstance();
}

/*
Named constructor with verbosity level.
*/
StefanRaw2Cal::StefanRaw2Cal(const TString& name, Int_t verbose) 
    :   FairTask() 
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
    // OTHER STUFF 
    // ,   ftime_machine_array(new TClonesArray("TimeMachineData"))
{
    stefan_config = TStefanConfiguration::GetInstance();
}

StefanRaw2Cal::~StefanRaw2Cal()
{
    c4LOG(info, "Deleting StefanRaw2Cal task");
}



void StefanRaw2Cal::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

/*
Init - register data to output tree and gets input data.
*/
InitStatus StefanRaw2Cal::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

 
    // needs to have the name of the detector subsystem here:
    // register stefan etc
    // FairRootManager::Instance()->Register("StefanTimeMachineData", "Time Machine Data", ftime_machine_array, !fOnline);

    // do we need TM for stefan lol
    
    // fcal_data->Clear();

    return kSUCCESS;
}


/*
Analysis event loop. 
Fatal error if detector map is not set. If calibration coeffs are not written, simply the uncalibrated energies are written.

Picks out the TimeMachine.
*/
void StefanRaw2Cal::Exec(Option_t* option)
{
    // process stuff, we can re-steal from germ or bb7 but...better to leave blank rn
}

/*
Very important function - all TClonesArray must be cleared after each event.
*/
void StefanRaw2Cal::FinishEvent()
{
    // clear
};



ClassImp(StefanRaw2Cal)