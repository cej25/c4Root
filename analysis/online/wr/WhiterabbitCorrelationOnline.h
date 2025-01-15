#ifndef WhiterabbitCorrelationOnline_H
#define WhiterabbitCorrelationOnline_H

#include "FairTask.h"
#include "TAidaConfiguration.h"
#include "TFatimaTwinpeaksConfiguration.h"
#include "TGermaniumConfiguration.h"

#include "AidaHitData.h"
#include "AidaData.h"
#include "FatimaVmeCalData.h"
#include "BB7VmeCalData.h"
#include "TimeMachineData.h"
#include "FatimaTwinpeaksCalData.h"
#include "bPlastTwinpeaksCalData.h"
#include "GermaniumCalData.h"
#include "FrsHitData.h"
#include "EventHeader.h"

#include "TH1.h"
#include "TFolder.h"
#include "TDirectory.h"
#include <vector>

class TClonesArray;
class EventHeader;
class TimeMachineData;
class TFolder;
class TDirectory;
class TCanvas;
class TH1;
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

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);
        
        virtual void FinishEvent();

        virtual void FinishTask();

        virtual void Reset_Histo();

        virtual void Snapshot_Histo();

        // range setters

    
    private:
        TAidaConfiguration const* aida_config;
        TFatimaTwinpeaksConfiguration const* fatima_config;
        TGermaniumConfiguration const* ge_config;

        TClonesArray* fHitFatimaTwinpeaks;
        //TClonesArray* fHitFatimaVme;
        std::vector<FatimaVmeTDCCalItem> const* fatVmeArray;
        TClonesArray* fHitbPlastTwinpeaks;
        TClonesArray* fHitGe;
        std::vector<AidaHit> const* fAidaDecays;
        std::vector<AidaHit> const* fAidaImplants;
        std::vector<AidaUnpackScalerItem> const* fAidaScalers;
        std::vector<FrsHitItem> const* hitArrayFrs;
        std::vector<BB7VmeDecayItem> const* fBB7Decays;
        std::vector<BB7VmeImplantItem> const* fBB7Implants;

        std::vector<TString> fDetectorSystems;
        int fNumDetectorSystems;

        // Header
        EventHeader* fEventHeader;
        Int_t fNEvents;
        int total_time_microsecs = 0;
        int frs_and_aida = 0;
        int frsEvents = 0;
        int implantEvents = 0;

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

        //Folders and directories
        TFolder* histograms;
        TDirectory* dir_whiterabbit;
        TDirectory* dir_whiterabbit_correlation;
        TDirectory* dir_whiterabbit_trigger1;
        TDirectory* dir_whiterabbit_trigger3;
        TDirectory* dir_whiterabbit_time_differences;
        TFile* file_whiterabbit_snapshot;

        
        // Histograms
        TH1* h1_whiterabbit_correlation_aida_frs;
        TH1* h1_whiterabbit_correlation_fatima_frs;
        TH1* h1_whiterabbit_correlation_bplast_frs;
        TH1* h1_whiterabbit_correlation_germanium_frs;
        TH1* h1_whiterabbit_correlation_bb7_frs;

        TH1* h1_whiterabbit_correlation_aida_fatima;
        TH1* h1_whiterabbit_trigger1_aida_fatima;
        TH1* h1_whiterabbit_trigger3_aida_fatima;

        TH1* h1_whiterabbit_correlation_aida_fatimavme;
        TH1* h1_whiterabbit_trigger1_aida_fatimavme;
        TH1* h1_whiterabbit_trigger3_aida_fatimavme;

        TH1* h1_whiterabbit_correlation_aida_bplast;
        TH1* h1_whiterabbit_trigger1_aida_bplast;
        TH1* h1_whiterabbit_trigger3_aida_bplast;

        TH1* h1_whiterabbit_correlation_aida_germanium;
        TH1* h1_whiterabbit_trigger1_aida_germanium;
        TH1* h1_whiterabbit_trigger3_aida_germanium;

        TH1* h1_whiterabbit_correlation_fatima_fatimavme;
        TH1* h1_whiterabbit_trigger1_fatima_fatimavme;
        TH1* h1_whiterabbit_trigger3_fatima_fatimavme;

        TH1* h1_whiterabbit_correlation_fatima_bplast;
        TH1* h1_whiterabbit_trigger1_fatima_bplast;
        TH1* h1_whiterabbit_trigger3_fatima_bplast;

        TH1* h1_whiterabbit_correlation_fatima_ge;
        TH1* h1_whiterabbit_trigger1_fatima_ge;
        TH1* h1_whiterabbit_trigger3_fatima_ge;

        TH1* h1_whiterabbit_correlation_fatimavme_bplast;
        TH1* h1_whiterabbit_trigger1_fatimavme_bplast;
        TH1* h1_whiterabbit_trigger3_fatimavme_bplast;

        TH1* h1_whiterabbit_correlation_fatimavme_ge;
        TH1* h1_whiterabbit_trigger1_fatimavme_ge;
        TH1* h1_whiterabbit_trigger3_fatimavme_ge;

        TH1* h1_whiterabbit_correlation_bplast_ge;
        TH1* h1_whiterabbit_trigger1_bplast_ge;
        TH1* h1_whiterabbit_trigger3_bplast_ge;

        TH1* h1_whiterabbit_correlation_bb7_fatima;
        TH1* h1_whiterabbit_correlation_bb7_fatimavme;
        TH1* h1_whiterabbit_correlation_bb7_germanium;
        TH1* h1_whiterabbit_correlation_bb7_bplast;

        TH1* h1_whiterabbit_trigger;

        // time differences
        TH1* h1_whiterabbit_dt_germanium;
        TH1* h1_whiterabbit_dt_bplast;
        TH1* h1_whiterabbit_dt_fatima;
        TH1* h1_whiterabbit_dt_fatimavme;
        TH1* h1_whiterabbit_dt_bb7;
        // frs? aida?

        int64_t last_wr_aida;
        int64_t last_wr_germanium;
        int64_t last_wr_bplast;
        int64_t last_wr_fatima;
        int64_t last_wr_fatimavme;
        int64_t last_wr_bb7;


    public:
        ClassDef(WhiterabbitCorrelationOnline, 1)
};

#endif
