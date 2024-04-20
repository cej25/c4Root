#ifndef LisaOnlineSpectra_H
#define LisaOnlineSpectra_H

#include "FairTask.h"
#include "TLisaConfiguration.h"
#include <vector>
#include <memory>

class TClonesArray;
class EventHeader;
class TCanvas;
class TH1F;
class TH2F;
class TH1I;

class LisaOnlineSpectra : public FairTask
{
    public:
        LisaOnlineSpectra();
        LisaOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~LisaOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        // range setters

    
    private:
        TLisaConfiguration const* lisa_config;
        TClonesArray* fHitLisa;


        int layer_number;
        int det_number;
        // ranges
        //Double_t

        EventHeader* header;
        Int_t fNEvents;
        

        // Canvas
        TCanvas* c_channelID;
        TCanvas* c_multiplicity;
        TCanvas* c_multiplicity_layer;
        std::vector<TCanvas*> c_energy_layer_ch;
        std::vector<TCanvas*> c_traces_layer_ch;
        TCanvas* c_energy_layer0;
        TCanvas* c_traces_layer0;
        

        // Histograms
        TH1I* h1_channelID;
        TH1I* h1_multiplicity;
        std::vector<TH1I*> h1_multiplicity_layer; 
        TH1F* h1_energy_layer0;
        std::vector<std::vector<std::vector<TH1F*>>> h1_energy_layer_ch;
        TH2F* h2_traces_layer0;
        std::vector<std::vector<TH2F*>> h2_traces_layer_ch;

    public:
        ClassDef(LisaOnlineSpectra, 1)
};

#endif
