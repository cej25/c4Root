#ifndef TimeMachineOnline_H
#define TimeMachineOnline_H

#include "FairTask.h"
#include "TFolder.h"
#include <vector>
#include "CorrelationsMap.h"

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
        TimeMachineOnline(CorrelationsMap* fCorrel);
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
        TClonesArray ** fTimeMachine;
        TimeMachineData* fTimeMachineHit;

        // Number of detector systems
        std::vector<TString> fDetectorSystems;
        int fNumDetectorSystems;

        EventHeader* header;

        CorrelationsMap* Correl;

        // Canvas
        TCanvas* c_time_undelayed;
        TCanvas* c_time_delayed;
        TCanvas* c_time_diff;
        TCanvas* c_time_corrs;
        TCanvas* c_whiterabbit_time_diff;
        TCanvas* c_time_machine_time_snapshot;

        // Folders and Files
        TFolder* folder_time_machine;
        TFile* file_time_machine_snapshot;

        // Histograms 
        TH1F * h1_time_undelayed[20];
        TH1F * h1_time_delayed[20];
        TH1F * h1_time_diff[20];

        TH2F * h2_time_diff_corrs[20*19];

        // Initial variables
        int fNEvents = 0;

        double delayed_time = 0;
        double undelayed_time = 0;

        double diffs[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

        // 20?
        uint64_t wr[20] = {0};

        int tm_gate_low;
        int tm_gate_high;
        int* tm_gate;


    public:
        ClassDef(TimeMachineOnline, 1)
};

#endif