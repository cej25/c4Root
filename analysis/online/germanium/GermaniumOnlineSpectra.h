#ifndef GermaniumOnlineSpectra_H
#define GermaniumOnlineSpectra_H

#include "FairTask.h"

#include "TGermaniumConfiguration.h"

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;

class GermaniumOnlineSpectra : public FairTask
{
    public:
        GermaniumOnlineSpectra();
        GermaniumOnlineSpectra(const TString& name, Int_t verbose = 1);


        void CreateHistograms();

        virtual ~GermaniumOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        virtual void Snapshot_Histo();

        // range setters

    
    private:
        TClonesArray* fHitGe;

        const TGermaniumConfiguration * germanium_configuration;

        // ranges
        int number_of_detectors_to_plot;
        std::vector<std::pair<int,int>> crystals_to_plot;


        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* c_germanium_time;
        TCanvas* c_germanium_energy;
        TCanvas* c_germanium_hitpattern;
        

        TCanvas* c_germanium_snapshot;

        char ** detector_labels;

        // Folder and files
        TDirectory* dir_germanium;
        TFolder* folder_germanium;
        TFolder* folder_germanium_energy;
        TFolder* folder_germanium_time;
        TFolder* folder_germanium_hitpattern;
        TFile* file_germanium_snapshot;

        // Histograms energy
        TH1F ** h1_germanium_energy;

        TH1F * h1_germanium_hitpattern;

        // Histograms time
        TH1F ** h1_germanium_time;


    public:
        ClassDef(GermaniumOnlineSpectra, 1)
};

#endif