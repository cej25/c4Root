// c4
#include "NewTask.h"


NewTask::NewTask() 
    : FairTask()
{
}


NewTask::NewTask(const TString& name, Int_t verbose) 
    :   FairTask(name, verbose)
{
}

NewTask::~NewTask()
{
    c4LOG(info, "Deleting NewTask Task.");
}

InitStatus NewTask::Init()
{  
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    

    return kSUCCESS;
};

void NewTask::Exec(Option_t* option)
{
}

void NewTask::FinishEvent()
{
}

void NewTask::FinishTask()
{
}


ClassImp(NewTask)
