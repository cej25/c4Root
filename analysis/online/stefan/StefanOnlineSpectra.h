#ifndef StefanOnlineSpectra_H
#define StefanOnlineSpectra_H

// FairRoot
#include "FairTask.h"

// c4
#include "StefanHitData.h"
#include "StefanCalData.h"
#include "TStefanConfiguration.h"
#include "H10MCPTwinpeaksAnaData.h"
#include "FrsHitData.h"
#include "TFRSParameter.h"
#include "TH10MCPConfiguration.h"
#include "TFrsConfiguration.h"
#include "FrsGate.h"

// ROOT
#include "TDirectory.h"
#include "TFolder.h"
#include "TCanvas.h"
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
class TCanvas;
class TH1F;
class TH2F;
class StefanHitItem;
class TStefanConfiguration;
class TH10MCPConfiguration;
class TFrsConfiguration;

class StefanOnlineSpectra : public FairTask
{
    public:
        StefanOnlineSpectra();
        StefanOnlineSpectra(std::vector<FrsGate*> fg);
        StefanOnlineSpectra(const TString& name, Int_t verbose = 1);

        virtual ~StefanOnlineSpectra();

        virtual InitStatus Init();

        virtual void Exec(Option_t* option);

        virtual void FinishEvent();

        virtual void FinishTask();

        // HTTP Commands
        virtual void Reset_Histo();

        // range setters


    private:

        TStefanConfiguration const* stefan_config;
        const TH10MCPConfiguration* mcp_config;
        TFrsConfiguration const* frs_config;

        std::vector<FrsGate*> FrsGates;

        std::vector<StefanHitItem> const* StefanHit; 
        std::vector<StefanCalItem> const* calArray;
        TClonesArray* fHitsMCP;
        std::vector<FrsHitItem> const* hitArray;
        std::vector<FrsMultiHitItem> const* multihitArray;

        EventHeader* header;
        Int_t fNEvents;
        int total_time_microsecs = 0;
	std::vector<double> max_energy;

        int nDets = 0;
        int num_frs_gates = 0;

        // Folders and Files
        TFolder* histograms;
        TDirectory* dir_stefan;
        TDirectory** dir_dssd;
        TDirectory** dir_hits;
        TDirectory* dir_corr;
        TDirectory* dir_mcp_stefan;
        TDirectory** dir_mcp_stefan_dssds;
        TDirectory** dir_mcp_stefan_dssds_strips;
        TDirectory* dir_frs_stefan;
        TDirectory* dir_frs_tof_stefan;
        TDirectory* dir_frs_z_stefan;
        TDirectory** dir_frs_tof_stefan_dssds;
        TDirectory** dir_frs_tof_stefan_dssds_strips;
        TDirectory** dir_frs_z_stefan_dssds;
        TDirectory** dir_frs_z_stefan_dssds_strips;
        TDirectory* dir_frs_mcp;
        TDirectory* dir_frs_gated;
        TDirectory** dir_frs_gates;
        std::vector<std::vector<TDirectory*>> dir_raw;
        std::vector<std::vector<TDirectory*>> dir_clusters;
        std::vector<TDirectory*> dir_pixel;
	
	
        TDirectory** dir_stats;
        
        TCanvas* strips4_stefan;
	
	TH1* h1_test; // test histogram
	std::vector<TH1*> h1_DSSSD_energy;
	TH2* h2_dE_E;
	TH2* h2_Z_M;
	
        std::vector<TH2*> h2_hit_strip_xy; // Hit pattern
        std::vector< std::vector<std::vector<TH1*>>> h1_raw_energy; // raw energy spectra
        std::vector< std::vector<std::vector<TH1*>>> h1_energy_clusters; // raw energy spectra
        std::vector< std::vector<TH1*>> h1_pixel_energy; // energy per pixel spectra

        std::vector<TH2*> h2_mcp_tof_vs_e_dssd;
        std::vector<std::vector<TH2*>> h2_mcp_tof_vs_e_vertical_strip;
        std::vector<std::vector<TH2*>> h2_mcp_tof_vs_e_horizontal_strip;

        std::vector<TH2*> h2_s2s4_tof_vs_e_dssd;
        std::vector<std::vector<TH2*>> h2_s2s4_tof_vs_e_vertical_strip;
        std::vector<std::vector<TH2*>> h2_s2s4_tof_vs_e_horizontal_strip;
        std::vector<TH2*> h2_z41_vs_e_dssd;
        std::vector<std::vector<TH2*>> h2_z41_vs_e_vertical_strip;
        std::vector<std::vector<TH2*>> h2_z41_vs_e_horizontal_strip;
        std::vector<TH2*> h2_z42_vs_e_dssd;
        std::vector<std::vector<TH2*>> h2_z42_vs_e_vertical_strip;
        std::vector<std::vector<TH2*>> h2_z42_vs_e_horizontal_strip;

        TH2* h2_s2s4_tof_vs_mcp_tof;
        TH2* h2_z41_vs_mcp_tof;
        TH2* h2_z42_vs_mcp_tof;


        // Counters
        std::set<int>** implant_strips_fired;
        int** implant_side_x_mult;
        int** implant_side_y_mult;
        std::set<int>** decay_strips_fired;
        int** decay_side_x_mult;
        int** decay_side_y_mult;


    public:
        ClassDef(StefanOnlineSpectra, 1)
};

#endif
