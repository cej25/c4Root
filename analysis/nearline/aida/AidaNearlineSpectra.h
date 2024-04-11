#ifndef AidaNearlineSpectra_H
#define AidaNearlineSpectra_H

// FairRoot
#include "FairTask.h"

// c4
#include "AidaCalData.h"
#include "AidaData.h"
#include "AidaHitData.h"
#include "TAidaConfiguration.h"

// ROOT
#include "TDirectory.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "TClonesArray.h"
#include <array>
#include <deque>
#include <map>
#include <vector>

class EventHeader;

class TClonesArray;
class TDirectory;
class TFolder;
class TGraph;
class TH1F;
class TH2F;

class AidaNearlineSpectra : public FairTask
{
    public:
        AidaNearlineSpectra();
        AidaNearlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~AidaNearlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();


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
        int total_time_microsecs = 0;


        // Folders and Files
        TFolder* histograms;
        TDirectory* dir_aida;
        TDirectory* dir_implant;
        TDirectory* dir_stopped_implant;
        TDirectory* dir_decay;
        TDirectory* dir_scalers;
        std::vector<TDirectory*> dir_implant_dssd;
        std::vector<TDirectory*> dir_stopped_implant_dssd;
        std::vector<TDirectory*> dir_decay_dssd;

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
        // Stopped Implant Histograms
        std::vector<TH2F*> h_implant_strip_xy_stopped;
        std::vector<TH2F*> h_implant_pos_xy_stopped;
        std::vector<TH1F*> h_implant_e_stopped;
        std::vector<TH2F*> h_implant_x_ex_stopped;
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
        std::vector<std::deque<int>> aida_implant_stopped_scaler_queue;
        std::vector<TGraph*> aida_implant_stopped_scaler_graph;
        std::vector<std::deque<int>> aida_decay_scaler_queue;
        std::vector<int> aida_decay_scaler_cur_sec;
        std::vector<TGraph*> aida_decay_scaler_graph;

        // Deadtime

    public:
        ClassDef(AidaNearlineSpectra, 1)
};

#endif
