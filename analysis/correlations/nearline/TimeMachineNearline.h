#ifndef TimeMachineNearline_H
#define TimeMachineNearline_H

#include "FairTask.h"
#include "TCorrelationsConfiguration.h"

#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include <vector>
#include <map>

class TClonesArray;
class EventHeader;
class TimeMachineData;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class TDirectory;

class TimeMachineNearline : public FairTask
{
    public:
        TimeMachineNearline();
        TimeMachineNearline(const TString& name, Int_t verbose = 1);

        void SetDetectorSystems(std::vector<TString> detectorsystems);

        int* GetGateValues(std::string name1, std::string name2);

        virtual ~TimeMachineNearline();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();


    
    private:

        TCorrelationsConfiguration const* correl_config;

        std::map<std::string, std::vector<int>> Correl;
        std::map<std::string, std::vector<int>> TMGates;

        TClonesArray ** fTimeMachine;
        TimeMachineData* fTimeMachineHit;

        // Number of detector systems
        std::vector<TString> fDetectorSystems;
        int fNumDetectorSystems;

        EventHeader* header;
        Int_t fNEvents;

        // Folders and Files
        TDirectory* dir_time_machine;
        TDirectory* dir_time_machine_undelayed;
        TDirectory* dir_time_machine_delayed;
        TDirectory* dir_time_machine_diff;
        TDirectory* dir_time_machine_corrs;

        // Histograms
        // would also be nice to set this up from the detector setup
        std::vector<TH1F*> h1_time_undelayed;
        std::vector<TH1F*> h1_time_delayed;
        std::vector<TH1F*> h1_time_diff;
        std::vector<TH2F*> h2_time_diff_corrs;

        double delayed_time = 0;
        double undelayed_time = 0;

        double diffs[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

        // 20? - show the diffs 20 times
        uint64_t wr[20] = {0};


    public:
        ClassDef(TimeMachineNearline, 1)
};

#endif