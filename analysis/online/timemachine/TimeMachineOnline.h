#ifndef TimeMachineOnline_H
#define TimeMachineOnline_H

#include "FairTask.h"
#include "TFolder.h"
#include <vector>
#include <map>
#include "TCorrelationsConfiguration.h"

class TClonesArray;
class EventHeader;
class TimeMachineData;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;

class TimeMachineOnline : public FairTask
{
    public:
        TimeMachineOnline();
        TimeMachineOnline(const TString& name, Int_t verbose = 1);


        void SetDetectorSystems(std::vector<TString> detectorsystems);

        int* GetGateValues(std::string name1, std::string name2);

        virtual ~TimeMachineOnline();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();
        
        virtual void Reset_Histo();

        virtual void Snapshot_Histo();


    
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

        // Canvas
        TCanvas* c_time_undelayed;
        TCanvas* c_time_delayed;
        TCanvas* c_time_diff;
        TCanvas* c_time_corrs;
        TCanvas* c_whiterabbit_time_diff;
        TCanvas* c_time_machine_time_snapshot;

        // Folders and Files
        TFolder* folder_time_machine;
        TFolder* folder_time_machine_undelayed;
        TFolder* folder_time_machine_delayed;
        TFolder* folder_time_machine_diff;
        TFolder* folder_time_machine_corrs;
        TFile* file_time_machine_snapshot;

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
        ClassDef(TimeMachineOnline, 1)
};

#endif