#ifndef WhiterabbitCorrelationOnline_H
#define WhiterabbitCorrelationOnline_H

#include "FairTask.h"
#include "AidaHitData.h"
#include "AidaData.h"
#include "TAidaConfiguration.h"
#include <vector>

class TClonesArray;
class EventHeader;
class TimeMachineData;
class TCanvas;
class TH1I;
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
        TAidaConfiguration const* conf;

        TClonesArray* fHitFatimaTwinpeaks;
        TClonesArray* fHitFatimaVme;
        TClonesArray* fHitbPlastTwinpeaks;
        TClonesArray* fHitGe;
        std::vector<AidaHit> const* fAidaDecays;
        std::vector<AidaUnpackScalerItem> const* fAidaScalers;

        std::vector<TString> fDetectorSystems;
        int fNumDetectorSystems;

        // Header
        EventHeader* fEventHeader;
        Int_t fNEvents;
        int total_time_microsecs = 0;

        // Canvas
        TCanvas* c_whiterabbit_correlation;
        TCanvas* c_whiterabbit_trigger1;
        TCanvas* c_whiterabbit_trigger3;

        TCanvas* c_whiterabbit_correlation_fatima_bplast;
        TCanvas* c_whiterabbit_trigger1_fatima_bplast;
        TCanvas* c_whiterabbit_trigger3_fatima_bplast;

        TCanvas* c_whiterabbit_correlation_aida_fatima;
        TCanvas* c_whiterabbit_trigger1_aida_fatima;
        TCanvas* c_whiterabbit_trigger3_aida_fatima;

        TCanvas* c_whiterabbit_correlation_bplast_ge;
        TCanvas* c_whiterabbit_trigger1_bplast_ge;
        TCanvas* c_whiterabbit_trigger3_bplast_ge;

        TCanvas* c_whiterabbit_correlation_fatima_ge;
        TCanvas* c_whiterabbit_trigger1_fatima_ge;
        TCanvas* c_whiterabbit_trigger3_fatima_ge;
        
        TCanvas* c_whiterabbit_correlation_aida_fatimavme;
        TCanvas* c_whiterabbit_trigger1_aida_fatimavme;
        TCanvas* c_whiterabbit_trigger3_aida_fatimavme;

        TCanvas* c_whiterabbit_correlation_aida_bplast;
        TCanvas* c_whiterabbit_trigger1_aida_bplast;
        TCanvas* c_whiterabbit_trigger3_aida_bplast;

        TCanvas* c_whiterabbit_correlation_aida_germanium;
        TCanvas* c_whiterabbit_trigger1_aida_germanium;
        TCanvas* c_whiterabbit_trigger3_aida_germanium;

        TCanvas* c_whiterabbit_correlation_fatima_fatimavme;
        TCanvas* c_whiterabbit_trigger1_fatima_fatimavme;
        TCanvas* c_whiterabbit_trigger3_fatima_fatimavme;

        TCanvas* c_whiterabbit_correlation_fatimavme_bplast;
        TCanvas* c_whiterabbit_trigger1_fatimavme_bplast;
        TCanvas* c_whiterabbit_trigger3_fatimavme_bplast;

        TCanvas* c_whiterabbit_correlation_fatimavme_ge;
        TCanvas* c_whiterabbit_trigger1_fatimavme_ge;
        TCanvas* c_whiterabbit_trigger3_fatimavme_ge;
        
        TCanvas* c_whiterabbit_trigger;

        //Folders and directories
        TDirectory* dir_whiterabbit;
        TFolder* folder_whiterabbit;
        TFolder* folder_whiterabbit_correlation;
        TFolder* folder_whiterabbit_trigger1;
        TFolder* folder_whiterabbit_trigger3;
        TFile* file_whiterabbit_snapshot;

        
        // Histograms

        TH1I* h1_whiterabbit_correlation_aida_fatima;
        TH1I* h1_whiterabbit_trigger1_aida_fatima;
        TH1I* h1_whiterabbit_trigger3_aida_fatima;

        TH1I* h1_whiterabbit_correlation_aida_fatimavme;
        TH1I* h1_whiterabbit_trigger1_aida_fatimavme;
        TH1I* h1_whiterabbit_trigger3_aida_fatimavme;

        TH1I* h1_whiterabbit_correlation_aida_bplast;
        TH1I* h1_whiterabbit_trigger1_aida_bplast;
        TH1I* h1_whiterabbit_trigger3_aida_bplast;

        TH1I* h1_whiterabbit_correlation_aida_germanium;
        TH1I* h1_whiterabbit_trigger1_aida_germanium;
        TH1I* h1_whiterabbit_trigger3_aida_germanium;

        TH1I* h1_whiterabbit_correlation_fatima_fatimavme;
        TH1I* h1_whiterabbit_trigger1_fatima_fatimavme;
        TH1I* h1_whiterabbit_trigger3_fatima_fatimavme;

        TH1I* h1_whiterabbit_correlation_fatima_bplast;
        TH1I* h1_whiterabbit_trigger1_fatima_bplast;
        TH1I* h1_whiterabbit_trigger3_fatima_bplast;

        TH1I* h1_whiterabbit_correlation_fatima_ge;
        TH1I* h1_whiterabbit_trigger1_fatima_ge;
        TH1I* h1_whiterabbit_trigger3_fatima_ge;

        TH1I* h1_whiterabbit_correlation_fatimavme_bplast;
        TH1I* h1_whiterabbit_trigger1_fatimavme_bplast;
        TH1I* h1_whiterabbit_trigger3_fatimavme_bplast;

        TH1I* h1_whiterabbit_correlation_fatimavme_ge;
        TH1I* h1_whiterabbit_trigger1_fatimavme_ge;
        TH1I* h1_whiterabbit_trigger3_fatimavme_ge;

        TH1I* h1_whiterabbit_correlation_bplast_ge;
        TH1I* h1_whiterabbit_trigger1_bplast_ge;
        TH1I* h1_whiterabbit_trigger3_bplast_ge;

        TH1I* h1_whiterabbit_trigger;



    public:
        ClassDef(WhiterabbitCorrelationOnline, 1)
};

#endif
