#ifndef WhiterabbitCorrelationOnline_H
#define WhiterabbitCorrelationOnline_H

#include "FairTask.h"

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
        TClonesArray* fHitbPlastTwinpeaks;
        TClonesArray* fHitGe;
        TimeMachineData* fWhiterabbitHit;

        std::vector<TString> fDetectorSystems;
        int fNumDetectorSystems;

        // Header
        EventHeader* fEventHeader;
        Int_t fNEvents;

        // Canvas
        TCanvas* c_whiterabbit_correlation;
        TCanvas* c_whiterabbit_correlation_bplast_fatima;
        TCanvas* c_whiterabbit_trigger1_bplast_fatima;
        TCanvas* c_whiterabbit_trigger3_bplast_fatima;

        TCanvas* c_whiterabbit_correlation_bplast_ge;
        TCanvas* c_whiterabbit_trigger1_bplast_ge;
        TCanvas* c_whiterabbit_trigger3_bplast_ge;

        TCanvas* c_whiterabbit_correlation_fatima_ge;
        TCanvas* c_whiterabbit_trigger1_fatima_ge;
        TCanvas* c_whiterabbit_trigger3_fatima_ge;
        
        TCanvas* c_whiterabbit_trigger;

        //Folders and directories
        TDirectory* dir_whiterabbit;
        TFolder* folder_whiterabbit;
        TFile* file_whiterabbit_snapshot;

        
        // Histograms  
        TH1F* h1_whiterabbit_correlation_bplast_fatima;
        TH2F* h2_whiterabbit_trigger1_bplast_fatima;
        TH2F* h2_whiterabbit_trigger3_bplast_fatima;

        TH1F* h1_whiterabbit_correlation_bplast_ge;
        TH2F* h2_whiterabbit_trigger1_bplast_ge;
        TH2F* h2_whiterabbit_trigger3_bplast_ge;

        TH1F* h1_whiterabbit_correlation_fatima_ge;
        TH2F* h2_whiterabbit_trigger1_fatima_ge;
        TH2F* h2_whiterabbit_trigger3_fatima_ge;

        TH1F* h1_whiterabbit_trigger;



    public:
        ClassDef(WhiterabbitCorrelationOnline, 1)
};

#endif
