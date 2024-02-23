#ifndef AidaOnlineSpectra_H
#define AidaOnlineSpectra_H

#include "AidaCalData.h"
#include "AidaData.h"
#include "AidaHitData.h"
#include "FairTask.h"
#include "TAidaConfiguration.h"
#include <array>
#include <deque>
#include <map>
#include <vector>

class TClonesArray;
class EventHeader;
class TCanvas;
class TFolder;
class TGraph;
class TH1F;
class TH2F;

class AidaOnlineSpectra : public FairTask
{
    public:
        AidaOnlineSpectra();
        AidaOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~AidaOnlineSpectra();

        virtual void SetParContainers();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        // HTTP Commands
        virtual void Reset_Histo();

        virtual void Snapshot_Histo();

        void Reset_Scalers();

        // range setters


    private:
        // Data from AIDA Classes
        std::vector<AidaUnpackAdcItem> const* adcArray;
        std::vector<AidaUnpackFlowItem> const* flowArray;
        std::vector<AidaUnpackScalerItem> const* scalerArray;
        std::vector<AidaCalAdcItem> const* implantCalArray;
        std::vector<AidaCalAdcItem> const* decayCalArray;
        std::vector<AidaHit> const* implantHitArray;
        std::vector<AidaHit> const* decayHitArray;

        // AIDA Config
        TAidaConfiguration const* conf;

        EventHeader* header;
        Int_t fNEvents;

        // Canvas
        TCanvas* c_aida_snapshots;

        // Folders
        TFolder* folder_aida;
        TFolder* folder_implant;
        TFolder* folder_stopped_implant;
        TFolder* folder_decay;
        TFolder* folder_scalers;
        std::vector<TFolder*> folder_implant_dssd;
        std::vector<TFolder*> folder_stopped_implant_dssd;
        std::vector<TFolder*> folder_decay_dssd;

        // Histograms
        // Implant Histograms
        std::vector<TH2F*> h_implant_strip_xy;
        std::vector<TH2F*> h_implant_pos_xy;
        std::vector<TH1F*> h_implant_e;
        std::vector<TH2F*> h_implant_e_xy;
        std::vector<TH2F*> h_implant_strip_1d_energy;
        std::vector<TH2F*> h_implant_strip_1d;
        std::vector<TH2F*> h_implant_x_ex;
        std::vector<TH2F*> h_implant_y_ey;
        std::vector<TH1F*> h_implant_time_delta;
        std::vector<TH2F*> h_implant_strip_xy_stopped;
        // Decay Histograms
        std::vector<TH2F*> h_decay_strip_xy;
        std::vector<TH2F*> h_decay_pos_xy;
        std::vector<TH1F*> h_decay_e;
        std::vector<TH2F*> h_decay_e_xy;
        std::vector<TH2F*> h_decay_strip_1d_energy;
        std::vector<TH1F*> h_decay_time_delta;

        // Scalers
        std::map<int, std::deque<int>> aida_scaler_queue;
        std::map<int, int> aida_scaler_cur_sec;
        std::map<int, TGraph*> aida_scaler_graph;
        std::vector<std::deque<int>> aida_implant_scaler_queue;
        std::vector<int> aida_implant_scaler_cur_sec;
        std::vector<TGraph*> aida_implant_scaler_graph;
        std::vector<std::deque<int>> aida_decay_scaler_queue;
        std::vector<int> aida_decay_scaler_cur_sec;
        std::vector<TGraph*> aida_decay_scaler_graph;

        // Deadtime

    public:
        ClassDef(AidaOnlineSpectra, 1)
};

#endif
