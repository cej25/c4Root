// FairRoot
#include "FairTask.h"
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaTwinpeaksData.h"
#include "FatimaTwinpeaksCalData.h"
#include "TFatimaTwinpeaksConfiguration.h"
#include "TimeMachineData.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include <chrono>

#include "H10MCPRaw2Cal.h"

/*
empty constructor required for FairRoot.
*/
H10MCPRaw2Cal::H10MCPRaw2Cal()
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE)
{
   mcp_config = TH10MCPConfiguration::GetInstance();
}

/*
Named constructor with verbosity level.
*/
H10MCPRaw2Cal::H10MCPRaw2Cal(const TString& name, Int_t verbose) 
    :   FairTask()
    ,   fNEvents(0)
    ,   header(nullptr)
    ,   fOnline(kFALSE) 
{
    mcp_config = TH10MCPConfiguration::GetInstance();
}
/*
Clearing old constructed objects.
*/
H10MCPRaw2Cal::~H10MCPRaw2Cal()
{
    c4LOG(info, "Deleting H10MCPRaw2Cal task");
}


/*
Initializer called by the FairRoot manager. Gets the required FairRootManager objects to read and register the data to be written to the tree.
*/
InitStatus H10MCPRaw2Cal::Init()
{  
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");


    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    // looooad mcp

    return kSUCCESS;
};
       

/*
The event loop executable. This is where the events are analyzed. Only used implicitly by FairRoot during Run().

Further the hits are matched slow + fast and assigned from the internal Twinpeaks channnel number to the detector number if DetectorMap is loaded.
Assumes that fast hits always preceedes slow hits. 

If no detector map is set then be careful with how the mapping happens: tamex module id * number of tamex modules + channel id.

Writes the times in ns!
*/
void H10MCPRaw2Cal::Exec(Option_t* option)
{
    auto start = std::chrono::high_resolution_clock::now();
    
    // do stuff init



    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    total_time_microsecs += duration.count();

}


void H10MCPRaw2Cal::FinishEvent()
{
    // reset output array
};

/*
Some stats are written when finishing.
*/
void H10MCPRaw2Cal::FinishTask()
{
    c4LOG(info, Form("Wrote %i events.",fNEvents));
    c4LOG(info, Form("%i events are unmatched (not written).",fNunmatched));
    c4LOG(info, "Average execution time: " << (double)total_time_microsecs/fExecs << " microseconds.");
}


ClassImp(H10MCPRaw2Cal)
