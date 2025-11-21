#ifndef FrsRawNearlineSpectra_H
#define FrsRawNearlineSpectra_H

#include "FairTask.h"
#include "FrsData.h"

#include "TFrsConfiguration.h"
#include "TExperimentConfiguration.h"
#include "TDirectory.h"
#include "TFolder.h"
#include "TH1.h"
#include "TH2.h"

class TFrsConfiguration;
class TExperimentConfiguration;

typedef UInt_t UInt_t;
typedef Int_t Int_t;

class TClonesArray;
class EventHeader;
class TFolder;
class TDirectory;
class TCanvas;
class TH1F;
class TH2F;
class TH1I;
class TH2I;


class FrsRawNearlineSpectra : public FairTask
{
    public:
        FrsRawNearlineSpectra();

        FrsRawNearlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~FrsRawNearlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        // ResetHisto

    private:

        TFrsConfiguration const* frs_config;

        TExperimentConfiguration const* exp_config;

        TFRSParameter* frs;
        TMWParameter* mw;
        TTPCParameter* tpc;
        TMUSICParameter* music;
        TLABRParameter* labr;
        TSCIParameter* sci;
        TIDParameter* id;
        TSIParameter* si;
        TMRTOFMSParameter* mrtof;
        TRangeParameter* range;

        std::vector<FrsSciItem> const* sciArray;
        std::vector<FrsMusicItem> const* musicArray;
        std::vector<FrsTpcItem> const* tpcArray;


        EventHeader const* header;
        Int_t fNEvents;

        // Directories
        bool found_dir_frs = true;
        TDirectory* dir_frs;
        TDirectory* dir_frs_raw;
        TDirectory* dir_sci;
        TDirectory* dir_music;
        TDirectory* dir_tpc;
        TDirectory* dir_sci_de; 
        TDirectory* dir_sci_dt;
        TDirectory* dir_sci_mhtdc;
        TDirectory* dir_music_e;
        TDirectory* dir_music_n_e[2];
        TDirectory* dir_music_t;
        TDirectory* dir_music_n_t[2];
        TDirectory* dir_tpc_adc;
        TDirectory* dir_tpc_n_adc[7];
        TDirectory* dir_tpc_tdc;
        
        // Histograms
        TH1* h1_sci_de[32];
        TH1* h1_sci_dt[32];
        TH1* h1_sci_mhtdc[32];
        TH1* h1_music_anode_e[5][8];
        TH1* h1_music_anode_t[5][8];
        TH1* h1_tpc_adc[7][8];
        TH1* h1_tpc_tdc[128];

        TH1* h1_sci_mhtdc_11la;
        TH1* h1_sci_mhtdc_11lb;
        TH1* h1_sci_mhtdc_11lc;
        TH1* h1_sci_mhtdc_11ld;
        TH1* h1_sci_mhtdc_21l;
        TH1* h1_sci_mhtdc_22l;
        TH1* h1_sci_mhtdc_31l;
        TH1* h1_sci_mhtdc_41l;
        TH1* h1_sci_mhtdc_42l;
        TH1* h1_sci_mhtdc_43l;
        TH1* h1_sci_mhtdc_81l;
        TH1* h1_sci_mhtdc_11ra;
        TH1* h1_sci_mhtdc_11rb;
        TH1* h1_sci_mhtdc_11rc;
        TH1* h1_sci_mhtdc_11rd;
        TH1* h1_sci_mhtdc_21r;
        TH1* h1_sci_mhtdc_22r;
        TH1* h1_sci_mhtdc_31r;
        TH1* h1_sci_mhtdc_41r;
        TH1* h1_sci_mhtdc_42r;
        TH1* h1_sci_mhtdc_43r;
        TH1* h1_sci_mhtdc_81r;
    
        // Canvases
        TCanvas* c_sci_de;
        TCanvas* c_sci_dt;
        TCanvas* c_sci_mhtdc;
        TCanvas* c_music_n_e[2];
        TCanvas* c_music_n_t[2];
        TCanvas* c_tpc_n_adc[7];
        TCanvas* c_tpc_tdc;


        // Variables
        const UInt_t* sciDE; //32
        const UInt_t* sciDT; //32
        const std::vector<Int_t>* sciMHTDC; // 32

        const UInt_t (*musicE)[8]; // 5, 8
        const UInt_t (*musicT)[8]; // 5, 8

        const UInt_t (*adcData)[8]; // 7, 8
        const std::vector<UInt_t>* tdcData;


        
    
    public:
        ClassDef(FrsRawNearlineSpectra, 1)

};

#endif