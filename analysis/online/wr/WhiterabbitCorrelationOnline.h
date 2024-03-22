#ifndef WhiterabbitCorrelationOnline_H
#define WhiterabbitCorrelationOnline_H

#include "FairTask.h"
#include "AidaHitData.h"
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
        TClonesArray* fHitFatimaTwinpeaks;
        TClonesArray* fHitFatimaVme;
        TClonesArray* fHitbPlastTwinpeaks;
        TClonesArray* fHitGe;
        std::vector<AidaHit> const* fAidaDecays;
        TimeMachineData* fWhiterabbitHit;

        std::vector<TString> fDetectorSystems;
        int fNumDetectorSystems;

        // ranges

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* c_whiterabbit_correlation;
        TCanvas* c_whiterabbit_correlation_bplast_fatima;
        TCanvas* c_whiterabbit_correlation_fatima_aida;
        TCanvas* c_whiterabbit_correlation_bplast_ge;
        TCanvas* c_whiterabbit_correlation_fatima_ge;
        TCanvas* c_whiterabbit_correlation_fatimavme_aida;
        TCanvas* c_whiterabbit_correlation_aida_bplast;
        TCanvas* c_whiterabbit_correlation_aida_germanium;
        TCanvas* c_whiterabbit_correlation_fatima_fatimavme;
        TCanvas* c_whiterabbit_correlation_bplast_fatimavme;
        TCanvas* c_whiterabbit_correlation_fatimavme_ge;
        

        //Folders and directories
        TDirectory* dir_whiterabbit;
        TFolder* folder_whiterabbit;
        TFile* file_whiterabbit_snapshot;

        
        // Histograms


        TH1I* h1_whiterabbit_correlation_fatima_aida;
        TH1I* h1_whiterabbit_correlation_fatimavme_aida;
        TH1I* h1_whiterabbit_correlation_aida_bplast;
        TH1I* h1_whiterabbit_correlation_aida_germanium;
        TH1I* h1_whiterabbit_correlation_fatima_fatimavme;
        TH1I* h1_whiterabbit_correlation_bplast_fatima;
        TH1I* h1_whiterabbit_correlation_fatima_ge;
        TH1I* h1_whiterabbit_correlation_bplast_fatimavme;
        TH1I* h1_whiterabbit_correlation_fatimavme_ge;
        TH1I* h1_whiterabbit_correlation_bplast_ge;



    public:
        ClassDef(WhiterabbitCorrelationOnline, 1)
};

#endif
