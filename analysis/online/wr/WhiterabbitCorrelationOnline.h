#ifndef WhiterabbitCorrelationOnline_H
#define WhiterabbitCorrelationOnline_H

#include "FairTask.h"
#include "AidaHitData.h"
#include <vector>

class TClonesArray;
class EventHeader;
class TimeMachineData;
class TCanvas;
class TH1F;
class TH2F;
class TFile;


class WhiterabbitCorrelationOnline : public FairTask
{
    public:
        WhiterabbitCorrelationOnline();
        WhiterabbitCorrelationOnline(const TString& name, Int_t verbose = 1);

        void SetDetectorSystems(std::vector<TString> detectorsystems);

        void CreateHistograms();

        virtual ~WhiterabbitCorrelationOnline();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        virtual void Snapshot_Histo();

        // range setters

    
    private:
        TClonesArray* fHitFatimaTwinpeaks;
        TClonesArray* fHitFatimaVme;
        TClonesArray* fHitbPlastTwinpeaks;
        TClonesArray* fHitGe;
        std::vector<AidaHit> const* fAidaDecays;
        TimeMachineData* fWhiterabbitHit;

        std::vector<TString> fDetectorSystems;
        int fNumDetectorSystems;

        // Header
        EventHeader* fEventHeader;
        Int_t fNEvents;

        // Canvas
        TCanvas* c_whiterabbit_correlation;
        TCanvas* c_whiterabbit_correlation_bplast_fatima;
<<<<<<< HEAD
        TCanvas* c_whiterabbit_trigger1_bplast_fatima;
        TCanvas* c_whiterabbit_trigger3_bplast_fatima;

=======
        TCanvas* c_whiterabbit_correlation_fatima_aida;
>>>>>>> main
        TCanvas* c_whiterabbit_correlation_bplast_ge;
        TCanvas* c_whiterabbit_trigger1_bplast_ge;
        TCanvas* c_whiterabbit_trigger3_bplast_ge;

        TCanvas* c_whiterabbit_correlation_fatima_ge;
<<<<<<< HEAD
        TCanvas* c_whiterabbit_trigger1_fatima_ge;
        TCanvas* c_whiterabbit_trigger3_fatima_ge;
        
        TCanvas* c_whiterabbit_trigger;
=======
        TCanvas* c_whiterabbit_correlation_fatimavme_aida;
        TCanvas* c_whiterabbit_correlation_aida_bplast;
        TCanvas* c_whiterabbit_correlation_aida_germanium;
        TCanvas* c_whiterabbit_correlation_fatima_fatimavme;
        TCanvas* c_whiterabbit_correlation_bplast_fatimavme;
        TCanvas* c_whiterabbit_correlation_fatimavme_ge;
        
>>>>>>> main

        //Folders and directories
        TDirectory* dir_whiterabbit;
        TFolder* folder_whiterabbit;
        TFile* file_whiterabbit_snapshot;

        
        // Histograms


        TH1F* h1_whiterabbit_correlation_fatima_aida;
        TH1F* h1_whiterabbit_correlation_fatimavme_aida;
        TH1F* h1_whiterabbit_correlation_aida_bplast;
        TH1F* h1_whiterabbit_correlation_aida_germanium;
        TH1F* h1_whiterabbit_correlation_fatima_fatimavme;
        TH1F* h1_whiterabbit_correlation_bplast_fatima;
<<<<<<< HEAD
        TH2F* h2_whiterabbit_trigger1_bplast_fatima;
        TH2F* h2_whiterabbit_trigger3_bplast_fatima;

        TH1F* h1_whiterabbit_correlation_bplast_ge;
        TH2F* h2_whiterabbit_trigger1_bplast_ge;
        TH2F* h2_whiterabbit_trigger3_bplast_ge;

        TH1F* h1_whiterabbit_correlation_fatima_ge;
        TH2F* h2_whiterabbit_trigger1_fatima_ge;
        TH2F* h2_whiterabbit_trigger3_fatima_ge;

        TH1F* h1_whiterabbit_trigger;
=======
        TH1F* h1_whiterabbit_correlation_fatima_ge;
        TH1F* h1_whiterabbit_correlation_bplast_fatimavme;
        TH1F* h1_whiterabbit_correlation_fatimavme_ge;
        TH1F* h1_whiterabbit_correlation_bplast_ge;
>>>>>>> main



    public:
        ClassDef(WhiterabbitCorrelationOnline, 1)
};

#endif
