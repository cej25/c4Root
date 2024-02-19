#ifndef TimeMachineOnline_H
#define TimeMachineOnline_H

#include "FairTask.h"
#include "TFolder.h"
#include <vector>

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



    public:
        ClassDef(TimeMachineOnline, 1)
};

#endif