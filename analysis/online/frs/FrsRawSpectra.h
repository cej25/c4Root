#ifndef FrsRawSpectra_H
#define FrsRawSpectra_H

#include "FairTask.h"
#include "FrsData.h"

#include "TDirectory.h"
#include "TFolder.h"
#include "TH1.h"
#include "TH2.h"

class TClonesArray;
class EventHeader;
class TFolder;
class TDirectory;
class TCanvas;
class TH1F;
class TH2F;
class TH1I;
class TH2I;


class FrsRawSpectra : public FairTask
{
    public:
        FrsRawSpectra();

        FrsRawSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsRawSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        // ResetHisto

    private:

        std::vector<FrsSciItem> const* sciArray;
        std::vector<FrsMusicItem> const* musicArray;
        std::vector<FrsTpcItem> const* tpcArray;


        EventHeader* header;
        Int_t fNEvents;

        // Directories
        TFolder* histograms;
        TDirectory* dir_frs;
        TDirectory* dir_frs_raw;
        TDirectory* dir_sci;
        TDirectory* dir_music;
        TDirectory* dir_tpc;
        TDirectory* dir_sci_de; 
        TDirectory* dir_sci_dt;
        TDirectory* dir_sci_mhtdc;
        TDirectory* dir_music_n[2];
        TDirectory* dir_tpc_adc;
        TDirectory* dir_tpc_n_adc[7];
        TDirectory* dir_tpc_tdc;
        
        // Histograms
        TH1* h1_sci_de[16];
        TH1* h1_sci_dt[16];
        TH1* h1_sci_mhtdc[16];
        TH1* h1_music_anode[2][8];
        TH1* h1_tpc_adc[7][8];
        TH1* h1_tpc_tdc[128];
       
    
        // Canvases
        TCanvas* c_sci_de;
        TCanvas* c_sci_dt;
        TCanvas* c_sci_mhtdc;
        TCanvas* c_music_n[2];
        TCanvas* c_tpc_n_adc[7];
        TCanvas* c_tpc_tdc;


        // Variables
        
    
    public:
        ClassDef(FrsRawSpectra, 1)

};

#endif