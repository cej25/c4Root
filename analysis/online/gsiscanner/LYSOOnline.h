#ifndef LYSOOnline_H
#define LYSOOnline_H

#include "FairTask.h"

#include "TDirectory.h"
#include "TFolder.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TText.h"
#include <vector>
#include <chrono>

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TFile;
class TFolder;
class TDirectory;
class TH1;

class LYSOOnline : public FairTask
{
    public:
        LYSOOnline();
        LYSOOnline(const TString& name, Int_t verbose = 1);

        virtual ~LYSOOnline();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();
        virtual void ResetAllHisto();


    private:
        TClonesArray* fHitsLYSO;
        TClonesArray* fHitsQDC;


        // ranges
        int number_of_boards = 2;
        int number_of_channels_per_board = 32;
        int number_of_channels = number_of_boards * number_of_channels_per_board;
        
        
        int funcal_nbins = 2000;
        int funcal_bin_low = 0;
        int funcal_bin_high = 2000;

        EventHeader* header;
        Int_t fNEvents;

        
        // Folder and files
        TFolder* histograms;
        TDirectory* dir_qdc;
        TDirectory* dir_lyso;


        TCanvas * c_charge;
        TH1F ** h1_charge;

        TCanvas * c_pos;
        TH2F * h2_pos;
        
        TCanvas * c_energy;
        TH1F ** h1_energy;



    public:
        ClassDef(LYSOOnline, 1)
};

#endif