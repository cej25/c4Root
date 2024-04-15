#ifndef WhiterabbitCorrelationNearline_H
#define WhiterabbitCorrelationNearline_H

#include "FairTask.h"
#include "TAidaConfiguration.h"
#include "AidaHitData.h"
#include "AidaData.h"

#include "TFolder.h"
#include "TDirectory.h"
#include <vector>

class TClonesArray;
class EventHeader;
class TimeMachineData;
class TFolder;
class TDirectory;
class TCanvas;
class TH1I;
class TH2F;
class TFile;


class WhiterabbitCorrelationNearline : public FairTask
{
    public:
        WhiterabbitCorrelationNearline();
        WhiterabbitCorrelationNearline(const TString& name, Int_t verbose = 1);

        void SetDetectorSystems(std::vector<TString> detectorsystems);

        void CreateHistograms();

        virtual ~WhiterabbitCorrelationNearline();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

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

        //Folders and directories
        TDirectory* dir_whiterabbit;
        TDirectory* dir_whiterabbit_correlation;
        TDirectory* dir_whiterabbit_trigger1;
        TDirectory* dir_whiterabbit_trigger3;

        
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
        ClassDef(WhiterabbitCorrelationNearline, 1)
};

#endif
