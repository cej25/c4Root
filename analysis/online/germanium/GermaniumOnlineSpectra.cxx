// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "GermaniumOnlineSpectra.h"
#include "EventHeader.h"
#include "GermaniumFebexData.h"
#include "GermaniumCalData.h"
#include "TGermaniumConfiguration.h"

#include "c4Logger.h"
#include "AnalysisTools.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TF1.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include <sstream>

GermaniumOnlineSpectra::GermaniumOnlineSpectra() : GermaniumOnlineSpectra("GermaniumOnlineSpectra")
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

GermaniumOnlineSpectra::GermaniumOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

GermaniumOnlineSpectra::~GermaniumOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitGe)
        delete fHitGe;
}

void GermaniumOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus GermaniumOnlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    run->GetHttpServer()->RegisterCommand("Reset_Ge_Histo", Form("/Objects/%s/->Reset_Ge_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_Ge_Histo", Form("/Objects/%s/->Snapshot_Ge_Histo()", GetName()));
    

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitGe = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fHitGe, "Branch GermaniumCalData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");


    crystals_to_plot.clear();
    std::map<std::pair<int,int>,std::pair<int,int>> gmap = germanium_configuration->Mapping();

    for (auto it_mapping = gmap.begin(); it_mapping != gmap.end(); ++it_mapping){
        if (it_mapping->second.first >= 0) crystals_to_plot.emplace_back(std::pair<int,int>(it_mapping->second.first,it_mapping->second.second));
    }

    number_of_detectors_to_plot = crystals_to_plot.size();
    
    TDirectory::TContext ctx(nullptr);

    dir_germanium = new TDirectory("DEGAS", "DEGAS", "", 0);
    mgr->Register("DEGAS", "DEGAS Directory", dir_germanium, false);
    histograms->Add(dir_germanium);

    dir_germanium_energy = dir_germanium->mkdir("Calibrated Energy Spectra");
    dir_germanium_time = dir_germanium->mkdir("Time Spectra");
    dir_germanium_hitpattern = dir_germanium->mkdir("Hit Pattern");
    dir_germanium_multiplicity = dir_germanium->mkdir("Multiplicity");
    dir_germanium_sci41 = dir_germanium->mkdir("SCI41");
    dir_germanium_resolution = dir_germanium->mkdir("Resolutions");
    dir_germanium_rates = dir_germanium->mkdir("Rate Monitors");

    detector_labels = new const char*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        detector_labels[ihist] = Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65));
    }
    

    // energy spectra:
    dir_germanium_energy->cd();
    c_germanium_energy  = new TCanvas("c_germanium_energy","Calibrated Germanium spectra",650,350);
    c_germanium_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_energy = new TH1F*[number_of_detectors_to_plot];
    //h1_germanium_energy.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_germanium_energy->cd(ihist+1);
        h1_germanium_energy[ihist] = new TH1F(Form("h1_germanium_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_germanium_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy[ihist]->Draw();
    }
    c_germanium_energy->cd(0);
    dir_germanium_energy->Append(c_germanium_energy);

    // time spectra:
    dir_germanium_time->cd();
    c_germanium_time  = new TCanvas("c_germanium_time","Calibrated Germanium spectra",650,350);
    c_germanium_time->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_time = new TH1F*[number_of_detectors_to_plot];
    //h1_germanium_time.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_germanium_time->cd(ihist+1);
        h1_germanium_time[ihist] = new TH1F(Form("h1_germanium_time_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS time spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,1e16);
        h1_germanium_time[ihist]->GetXaxis()->SetTitle("time (ns)");
        h1_germanium_time[ihist]->Draw();
    }
    c_germanium_time->cd(0);

    c_germanium_energy_vs_detidx = new TCanvas("c_germanium_energy_vs_detidx","Calibrated Germanium spectra vs. detector index",650,350);
    h2_germanium_energy_vs_detidx = new TH2F("h2_germanium_energy_vs_detidx","Calibrated Germanium spectra vs. detector index",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    h2_germanium_energy_vs_detidx->GetXaxis()->SetTitle("energy (keV)");
    h2_germanium_energy_vs_detidx->GetYaxis()->SetTitle("detector index");
    h2_germanium_energy_vs_detidx->Draw("COLZ");
    c_germanium_energy_vs_detidx->cd(0);
    dir_germanium_energy->Append(c_germanium_energy_vs_detidx);

    c_germanium_energy_summed = new TCanvas("c_germanium_energy_summed","Calibrated Germanium spectra summed all dets",650,350);
    h1_germanium_energy_summed = new TH1F("h1_germanium_energy_summed","Calibrated Germanium spectra summed all dets",fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_germanium_energy_summed->GetXaxis()->SetTitle("energy (keV)");
    h1_germanium_energy_summed->GetYaxis()->SetTitle("counts");
    h1_germanium_energy_summed->Draw();
    c_germanium_energy_summed->cd(0);
    dir_germanium_energy->Append(c_germanium_energy_summed);

    // Spectra relating to SCI41:
    dir_germanium_sci41->cd();
    c_germanium_energy_summed_vetosci41 = new TCanvas("c_germanium_energy_summed_vetosci41","Calibrated Germanium spectra summed all dets veto sci41",650,350);
    h1_germanium_energy_summed_vetosci41 = new TH1F("h1_germanium_energy_summed_vetosci41","Calibrated Germanium spectra summed all dets veto sci 41",fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_germanium_energy_summed_vetosci41->GetXaxis()->SetTitle("energy (keV)");
    h1_germanium_energy_summed_vetosci41->GetYaxis()->SetTitle("counts");
    h1_germanium_energy_summed_vetosci41->Draw();
    c_germanium_energy_summed_vetosci41->cd(0);
    dir_germanium_sci41->Append(c_germanium_energy_summed_vetosci41);
    
    c_germanium_energy_summed_vs_tsci41 = new TCanvas("c_germanium_energy_summed_vs_tsci41","Calibrated Germanium spectra summed all energyies vs t(det) - t(sci41)",650,350);
    h2_germanium_energy_summed_vs_tsci41 = new TH2F("h2_germanium_energy_summed_vs_tsci41","Calibrated Germanium spectra summed all energyies vs t(det) - t(sci41)",1000,-500,5000,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_energy_summed_vs_tsci41->GetXaxis()->SetTitle("time difference (ns)");
    h2_germanium_energy_summed_vs_tsci41->GetYaxis()->SetTitle("energy (keV)");
    h2_germanium_energy_summed_vs_tsci41->Draw("COLZ");
    c_germanium_energy_summed_vs_tsci41->cd(0);
    dir_germanium_sci41->Append(c_germanium_energy_summed_vs_tsci41);

    c_germanium_energy_summed_vs_tsci41_cut = new TCanvas("c_germanium_energy_summed_vs_tsci41_cut","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",650,350);
    h1_germanium_energy_summed_vs_tsci41_cut = new TH1F("h1_germanium_energy_summed_vs_tsci41_cut","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_germanium_energy_summed_vs_tsci41_cut->GetXaxis()->SetTitle("energy (keV)");
    h1_germanium_energy_summed_vs_tsci41_cut->Draw("COLZ");
    c_germanium_energy_summed_vs_tsci41_cut->cd(0);
    dir_germanium_sci41->Append(c_germanium_energy_summed_vs_tsci41_cut);

    c_germanium_energy_energy_vetosci41 = new TCanvas("c_germanium_energy_energy_vetosci41","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",650,350);
    h2_germanium_energy_energy_vetosci41 = new TH2F("h2_germanium_energy_energy_vetosci41","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_energy_energy_vetosci41->GetXaxis()->SetTitle("energy (keV)");
    h2_germanium_energy_energy_vetosci41->Draw("COLZ");
    c_germanium_energy_energy_vetosci41->cd(0);
    dir_germanium_sci41->Append(c_germanium_energy_energy_vetosci41);

    c_germanium_energy_energy_sci41_cut = new TCanvas("c_germanium_energy_energy_sci41_cut","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",650,350);
    h2_germanium_energy_energy_sci41_cut = new TH2F("h2_germanium_energy_energy_sci41_cut","Calibrated Germanium spectra summed all energyies, t(det) - t(sci41) > 200 ns",fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_germanium_energy_energy_sci41_cut->GetXaxis()->SetTitle("energy (keV)");
    h2_germanium_energy_energy_sci41_cut->Draw("COLZ");
    c_germanium_energy_energy_sci41_cut->cd(0);
    dir_germanium_sci41->Append(c_germanium_energy_energy_sci41_cut);



    dir_germanium_multiplicity->cd();
    c_germanium_multiplicity = new TCanvas("c_germanium_multiplicity","Multiplicity of Germanium events",650,350);
    h1_germanium_multiplicity = new TH1F("h1_germanium_multiplicity","Multiplicity of Germanium events",number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    h1_germanium_multiplicity->GetXaxis()->SetTitle("event multiplicity");
    h1_germanium_multiplicity->GetYaxis()->SetTitle("counts");
    h1_germanium_multiplicity->Draw();
    dir_germanium_multiplicity->Append(c_germanium_multiplicity);


    //time differences!
    number_reference_detectors = dt_reference_detectors.size();
    dir_germanium_time_differences.resize(number_reference_detectors);

    h1_germanium_time_differences = new TH1F ** [number_reference_detectors];
    h2_germanium_time_differences_vs_energy = new TH2F ** [number_reference_detectors];
    //h1_germanium_time_differences.resize(number_reference_detectors);
    //h2_germanium_time_differences_vs_energy.resize(number_reference_detectors);
    for (int ihist = 0; ihist < number_reference_detectors; ihist++)
    {
        std::stringstream name;
        name << "time_differences_rel_" << dt_reference_detectors.at(ihist).first << "_" << dt_reference_detectors.at(ihist).second << "_energy_gate_" << (int)dt_reference_detectors_energy_gates.at(ihist).first << "_" << (int)dt_reference_detectors_energy_gates.at(ihist).second;
        dir_germanium_time_differences[ihist] = dir_germanium->mkdir(name.str().c_str());
        dir_germanium_time_differences[ihist]->cd();
    
        c_germanium_time_differences  = new TCanvas(Form("c_germanium_time_differences_rel_det_%d_%d_energy_gate_%d_%d",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),"germanium relative time differences",650,350);
        c_germanium_time_differences->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
        h1_germanium_time_differences[ihist] = new TH1F*[number_of_detectors_to_plot];
        //h1_germanium_time_differences[ihist].resize(number_of_detectors_to_plot);

        for (int detid_idx = 0; detid_idx < number_of_detectors_to_plot; detid_idx++)
        {
            c_germanium_time_differences->cd(detid_idx+1);
            h1_germanium_time_differences[ihist][detid_idx] = new TH1F(Form("h1_germanium_rel_time_det_%d_%d_to_det_%d_%d_energy_gate_%d_%d",crystals_to_plot.at(detid_idx).first,crystals_to_plot.at(detid_idx).second,dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("Germanium delta time t(%d%c) - t(%d%c) gated %d and %d",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),1000,-1000,1000); 
            h1_germanium_time_differences[ihist][detid_idx]->GetXaxis()->SetTitle(Form("dt t(%d%c) - t(%d%c) (ns)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)));
            h1_germanium_time_differences[ihist][detid_idx]->Draw();
        }
        c_germanium_time_differences->cd(0);
        dir_germanium_time_differences[ihist]->Append(c_germanium_time_differences);

        c_germanium_time_differences_vs_energy  = new TCanvas(Form("c_germanium_time_differences_rel_det_%d_%d_vs_energy_energy_gate_%d_%d",dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),"germanium relative time differences vs energy",650,350);
        c_germanium_time_differences_vs_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
        h2_germanium_time_differences_vs_energy[ihist] = new TH2F*[number_of_detectors_to_plot];
        //h2_germanium_time_differences_vs_energy[ihist].resize(number_of_detectors_to_plot);

        for (int detid_idx = 0; detid_idx < number_of_detectors_to_plot; detid_idx++)
        {
            c_germanium_time_differences_vs_energy->cd(detid_idx+1);
            h2_germanium_time_differences_vs_energy[ihist][detid_idx] = new TH2F(Form("h1_germanium_rel_time_det_%d_%d_to_det_%d_%d_vs_energy_energy_gate_%d_%d",crystals_to_plot.at(detid_idx).first,crystals_to_plot.at(detid_idx).second,dt_reference_detectors.at(ihist).first,dt_reference_detectors.at(ihist).second,(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),Form("germanium delta time t(%d%c) - t(%d%c) vs energy, energy gate %d, %d",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65),(int)dt_reference_detectors_energy_gates.at(ihist).first,(int)dt_reference_detectors_energy_gates.at(ihist).second),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,500,-20000,20000); 
            h2_germanium_time_differences_vs_energy[ihist][detid_idx]->GetYaxis()->SetTitle(Form("dt t(%d%c) - t(%d%c) (ns)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65),dt_reference_detectors.at(ihist).first,(char)(dt_reference_detectors.at(ihist).second+65)));
            h2_germanium_time_differences_vs_energy[ihist][detid_idx]->GetXaxis()->SetTitle(Form("energy det %d%c (keV)",crystals_to_plot.at(detid_idx).first,(char)(crystals_to_plot.at(detid_idx).second+65)));
            h2_germanium_time_differences_vs_energy[ihist][detid_idx]->Draw("COLZ");
            
        }
        c_germanium_time_differences_vs_energy->cd(0);
        dir_germanium_time_differences[ihist]->Append(c_germanium_time_differences_vs_energy);

    }

    detector_counters = new int[number_of_detectors_to_plot];
    detector_rates = new int[number_of_detectors_to_plot];
    h1_germanium_rates = new TH1*[number_of_detectors_to_plot];
    for (int i = 0; i < number_of_detectors_to_plot; i++) h1_germanium_rates[i] = MakeTH1(dir_germanium_rates, "I", Form("h1_germanium_rates_det%i_crystal%i", crystals_to_plot.at(i).first, crystals_to_plot.at(i).second), Form("DEGAS Rate Detector %i Crystal %i", crystals_to_plot.at(i).first, crystals_to_plot.at(i).second), 1800, 0, 1800, "Time [2s]", kCyan, kBlack);

    
    dir_germanium_hitpattern->cd();
    c_germanium_hitpattern = new TCanvas("c_germanium_hitpattern","Hit pattern DEGAS",650,350);
        
    h1_germanium_hitpattern = new TH1F("h1_germanium_hitpattern","Hit pattern of DEGAS",number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        h1_germanium_hitpattern->GetXaxis()->SetBinLabel(ihist+1,Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
    }
    h1_germanium_hitpattern->GetXaxis()->SetAlphanumeric();
    h1_germanium_hitpattern->GetXaxis()->LabelsOption("a");
    h1_germanium_hitpattern->GetXaxis()->SetTitle("crystal");
    

    h1_germanium_hitpattern->GetYaxis()->SetTitle("counts");
    h1_germanium_hitpattern->SetStats(0);
    h1_germanium_hitpattern->Draw();
    c_germanium_hitpattern->cd(0);
    dir_germanium_hitpattern->Append(c_germanium_hitpattern);
    dir_germanium->cd();


    // RESOLUTIONS:
    
    dir_germanium_resolution->cd();

    f1_gaussian = new TF1("f1_gaussian","gaus",centroid_resolution-width_resolution,centroid_resolution+width_resolution);


    c1_germanium_energy_last  = new TCanvas("c1_germanium_energy_last","Calibrated Germanium spectra",650,350);
    c1_germanium_energy_last->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_energy_last = new TH1F*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c1_germanium_energy_last->cd(ihist+1);
        h1_germanium_energy_last[ihist] = new TH1F(Form("h1_germanium_energy_last_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_germanium_energy_last[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy_last[ihist]->Draw();
    }
    c1_germanium_energy_last->cd(0);

    dir_germanium_resolution->Append(c1_germanium_energy_last);

    c1_germanium_energy_last_fitted  = new TCanvas("c1_germanium_energy_last_fitted","Calibrated Germanium spectra",650,350);
    c1_germanium_energy_last_fitted->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_energy_last_fitted = new TH1F*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c1_germanium_energy_last_fitted->cd(ihist+1);
        h1_germanium_energy_last_fitted[ihist] = new TH1F(Form("h1_germanium_energy_last_fitted_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_germanium_energy_last_fitted[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_energy_last_fitted[ihist]->Draw();
    }
    c1_germanium_energy_last_fitted->cd(0);
    dir_germanium_resolution->Append(c1_germanium_energy_last_fitted);

    dir_germanium_resolution->cd();
    c_last_resolutions_FWHM = new TCanvas("c_last_resolutions_FWHM",Form("Last measurement of the resolution at E = %i keV DEGAS",(int)centroid_resolution),650,350);
    c_last_resolutions_FWHM->Divide(3);
    c_last_resolutions_FWHM->cd(1);
    
    h1_last_resolutions_FWHM = new TH1F("h1_last_resolutions_FWHM",Form("Last measurement of the FWHM at E = %i keV DEGAS",(int)centroid_resolution),number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        h1_last_resolutions_FWHM->GetXaxis()->SetBinLabel(ihist+1,Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
    }

    h1_last_resolutions_FWHM->GetXaxis()->SetAlphanumeric();
    h1_last_resolutions_FWHM->GetXaxis()->LabelsOption("a");
    h1_last_resolutions_FWHM->GetXaxis()->SetTitle("crystal");
    
    h1_last_resolutions_FWHM->GetYaxis()->SetTitle("FWHM (keV)");
    h1_last_resolutions_FWHM->SetStats(0);
    h1_last_resolutions_FWHM->Draw("HIST");

    c_last_resolutions_FWHM->cd(2);    
    h1_last_resolutions_FWTM = new TH1F("h1_last_resolutions_FWTM",Form("Last measurement of the FWTM at E = %i keV DEGAS",(int)centroid_resolution),number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        h1_last_resolutions_FWTM->GetXaxis()->SetBinLabel(ihist+1,Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
    }

    h1_last_resolutions_FWTM->GetXaxis()->SetAlphanumeric();
    h1_last_resolutions_FWTM->GetXaxis()->LabelsOption("a");
    h1_last_resolutions_FWTM->GetXaxis()->SetTitle("crystal");
    
    h1_last_resolutions_FWTM->GetYaxis()->SetTitle("counts");
    h1_last_resolutions_FWTM->SetStats(0);
    h1_last_resolutions_FWTM->Draw("HIST");
    
    c_last_resolutions_FWHM->cd(3);    
    h1_last_resolutions_gratio = new TH1F("h1_last_resolutions_gratio",Form("Last measurement of the FWTM at E = %i keV DEGAS",(int)centroid_resolution),number_of_detectors_to_plot,0,number_of_detectors_to_plot);
    
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        h1_last_resolutions_gratio->GetXaxis()->SetBinLabel(ihist+1,Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
    }

    h1_last_resolutions_gratio->GetXaxis()->SetAlphanumeric();
    h1_last_resolutions_gratio->GetXaxis()->LabelsOption("a");
    h1_last_resolutions_gratio->GetXaxis()->SetTitle("crystal");
    h1_last_resolutions_gratio->GetYaxis()->SetTitle("counts");
    h1_last_resolutions_gratio->SetStats(0);
    h1_last_resolutions_gratio->Draw("HIST");

    dir_germanium_resolution->Append(c_last_resolutions_FWHM);

    
    c_resolutions_FWHM  = new TCanvas("c_resolutions_FWHM","Resolutions",650,350);
    c_resolutions_FWHM->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    g1_resolutions_FWHM = new TGraph*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_resolutions_FWHM->cd(ihist+1);
        g1_resolutions_FWHM[ihist] = new TGraph(1);
        g1_resolutions_FWHM[ihist]->SetName(Form("g1_resolutions_FWHM_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
        g1_resolutions_FWHM[ihist]->SetTitle(Form("DEGAS resolution FWHM detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
        g1_resolutions_FWHM[ihist]->GetXaxis()->SetTitle("time since start (sec)");
        g1_resolutions_FWHM[ihist]->GetYaxis()->SetTitle("FWHM (keV)");
        g1_resolutions_FWHM[ihist]->Draw("ALP");
        dir_germanium_resolution->Append(g1_resolutions_FWHM[ihist]);
    }
    c_resolutions_FWHM->cd(0);
    dir_germanium_resolution->Append(c_resolutions_FWHM);


    c_resolutions_FWTM  = new TCanvas("c_resolutions_FWTM","Resolutions",650,350);
    c_resolutions_FWTM->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    g1_resolutions_FWTM = new TGraph*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_resolutions_FWTM->cd(ihist+1);
        g1_resolutions_FWTM[ihist] = new TGraph(1);
        g1_resolutions_FWTM[ihist]->SetName(Form("g1_resolutions_FWTM_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
        g1_resolutions_FWTM[ihist]->SetTitle(Form("DEGAS resolution FWTM detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
        g1_resolutions_FWTM[ihist]->GetXaxis()->SetTitle("time since start (sec)");
        g1_resolutions_FWTM[ihist]->GetYaxis()->SetTitle("FWTM (keV)");
        g1_resolutions_FWTM[ihist]->Draw("ALP");
        dir_germanium_resolution->Append(g1_resolutions_FWTM[ihist]);
    }
    c_resolutions_FWTM->cd(0);
    dir_germanium_resolution->Append(c_resolutions_FWTM);


    c_resolutions_gratio  = new TCanvas("c_resolutions_gratio","Resolutions",650,350);
    c_resolutions_gratio->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    g1_resolutions_gratio = new TGraph*[number_of_detectors_to_plot];
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_resolutions_gratio->cd(ihist+1);
        g1_resolutions_gratio[ihist] = new TGraph(1);
        g1_resolutions_gratio[ihist]->SetName(Form("g1_resolutions_gratio_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
        g1_resolutions_gratio[ihist]->SetTitle(Form("DEGAS resolution gratio detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)));
        g1_resolutions_gratio[ihist]->GetXaxis()->SetTitle("time since start (sec)");
        g1_resolutions_gratio[ihist]->GetYaxis()->SetTitle("gratio (keV)");
        g1_resolutions_gratio[ihist]->Draw("ALP");
        dir_germanium_resolution->Append(g1_resolutions_gratio[ihist]);

    }
    c_resolutions_gratio->cd(0);
    dir_germanium_resolution->Append(c_resolutions_gratio);



    dir_germanium->cd();


    return kSUCCESS;
}

void GermaniumOnlineSpectra::Reset_Ge_Histo()
{
    c4LOG(info, "Resetting DEGAS histograms.");
    for (int i = 0; i < number_reference_detectors; i++){
       for (int ihist = 0; ihist<number_of_detectors_to_plot; ihist++) 
        {
            h1_germanium_time_differences[i][ihist]->Reset();
            h2_germanium_time_differences_vs_energy[i][ihist]->Reset();
        }
    }
    for (int ihist = 0; ihist<number_of_detectors_to_plot; ihist++) 
    {
        h1_germanium_energy[ihist]->Reset();
        h1_germanium_time[ihist]->Reset();
    }

    h1_germanium_multiplicity->Reset();
    h1_germanium_hitpattern->Reset();
    h2_germanium_energy_vs_detidx->Reset();
    h1_germanium_energy_summed->Reset();
    h1_germanium_energy_summed_vetosci41->Reset();
    h2_germanium_energy_summed_vs_tsci41->Reset();
    h1_germanium_energy_summed_vs_tsci41_cut->Reset();
    h2_germanium_energy_energy_vetosci41->Reset();
    h2_germanium_energy_energy_sci41_cut->Reset();

    c4LOG(info, "DEGAS histograms reset.");
}

void GermaniumOnlineSpectra::Snapshot_Ge_Histo()
{
    c4LOG(info, "Snapshotting DEGAS histograms.");
    //date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    //make folder with date and time
    const char* snapshot_dir = Form("DEGAS_snapshot_%d_%d_%d_%d_%d_%d",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec);
    gSystem->cd(screenshot_path);
    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    // save histograms to canvases
    c_germanium_snapshot = new TCanvas("c","c",650,350);

    for (int ihist = 0; ihist<number_of_detectors_to_plot; ihist++)
    {
        if(h1_germanium_energy[ihist]->GetEntries()!=0)
        {
            h1_germanium_energy[ihist]->Draw();
            c_germanium_snapshot->SaveAs(Form("h1_germanium_energy_%d_%d.png",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
            c_germanium_snapshot->Clear();
            h1_germanium_time[ihist]->Draw();
            c_germanium_snapshot->SaveAs(Form("h1_germanium_time_%d_%d.png",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
            c_germanium_snapshot->Clear();
        }
        for(int i = 0; i < number_reference_detectors; i++)
        {
            if(h1_germanium_time_differences[i][ihist]->GetEntries()!=0)
            {
                h1_germanium_time_differences[i][ihist]->Draw();
                c_germanium_snapshot->SaveAs(Form("h1_germanium_time_differences_%d_%d_to_%d_%d.png",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second,dt_reference_detectors.at(i).first,dt_reference_detectors.at(i).second));
                c_germanium_snapshot->Clear();
                h2_germanium_time_differences_vs_energy[i][ihist]->Draw();
                c_germanium_snapshot->SaveAs(Form("h2_germanium_time_differences_vs_energy_%d_%d_to_%d_%d.png",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second,dt_reference_detectors.at(i).first,dt_reference_detectors.at(i).second));
                c_germanium_snapshot->Clear();
            }
        }
    }
    h1_germanium_multiplicity->Draw();
    c_germanium_snapshot->SaveAs("h1_germanium_multiplicity.png");
    c_germanium_snapshot->Clear();
    h1_germanium_hitpattern->Draw();
    c_germanium_snapshot->SaveAs("h1_germanium_hitpattern.png");
    c_germanium_snapshot->Clear();
    h2_germanium_energy_vs_detidx->Draw();
    c_germanium_snapshot->SaveAs("h2_germanium_energy_vs_detidx.png");
    c_germanium_snapshot->Clear();
    h1_germanium_energy_summed->Draw();
    c_germanium_snapshot->SaveAs("h1_germanium_energy_summed.png");
    c_germanium_snapshot->Clear();
    h1_germanium_energy_summed_vetosci41->Draw();
    c_germanium_snapshot->SaveAs("h1_germanium_energy_summed_vetosci41.png");
    c_germanium_snapshot->Clear();
    h2_germanium_energy_summed_vs_tsci41->Draw();
    c_germanium_snapshot->SaveAs("h2_germanium_energy_summed_vs_tsci41.png");
    c_germanium_snapshot->Clear();
    h1_germanium_energy_summed_vs_tsci41_cut->Draw();
    c_germanium_snapshot->SaveAs("h1_germanium_energy_summed_vs_tsci41_cut.png");
    c_germanium_snapshot->Clear();
    h2_germanium_energy_energy_vetosci41->Draw();
    c_germanium_snapshot->SaveAs("h2_germanium_energy_energy_vetosci41.png");
    c_germanium_snapshot->Clear();
    h2_germanium_energy_energy_sci41_cut->Draw();
    c_germanium_snapshot->SaveAs("h2_germanium_energy_energy_sci41_cut.png");
    c_germanium_snapshot->Clear();

    delete c_germanium_snapshot;
    
    // commented out for now. directories are not working :(())
    // // snapshot .root file with data and time
    // file_germanium_snapshot = new TFile(Form("Germanium_snapshot_%d_%d_%d_%d_%d_%d.root",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec),"RECREATE");
    // file_germanium_snapshot->cd();
    // dir_germanium->Write();
    // file_germanium_snapshot->Close();
    // delete file_germanium_snapshot;

    gSystem->cd("..");
    c4LOG(info, "DEGAS snapshots saved to: " << screenshot_path + snapshot_dir);
}

void GermaniumOnlineSpectra::Exec(Option_t* option){

    if (fHitGe && fHitGe->GetEntriesFast() > 0){

        if (first_time == 0){
            first_time = ((GermaniumCalData*)fHitGe->At(0))->Get_wr_t();
        }
    
        Int_t nHits = fHitGe->GetEntriesFast();
        int event_multiplicity = 0;
        int64_t germanium_wr = 0;
        
        
        bool sci41_seen = false; // off-spill raw spectra

        for (Int_t ihit = 0; ihit < nHits; ihit++){ // core loop for basic detector spectra and simple conincidences.
            
            GermaniumCalData* hit1 = (GermaniumCalData*)fHitGe->At(ihit);
            if (!hit1) continue;
            if (ihit == 0) current_wr = hit1->Get_wr_t();
            int detector_id1 = hit1->Get_detector_id();
            int crystal_id1 = hit1->Get_crystal_id();
            double energy1 = hit1->Get_channel_energy();
            double time1 = hit1->Get_channel_trigger_time();
            

            
            if (!(germanium_configuration->IsDetectorAuxilliary(detector_id1))) event_multiplicity ++; // count only physical events in germaniums

            if (detector_id1 == germanium_configuration->SC41L() || detector_id1 == germanium_configuration->SC41R()) sci41_seen = true;
            
            int crystal_index1 = std::distance(crystals_to_plot.begin(), std::find(crystals_to_plot.begin(),crystals_to_plot.end(),std::pair<int,int>(detector_id1,crystal_id1)));

            detector_counters[crystal_index1]++; // for rates
            germanium_wr = hit1->Get_wr_t();

            if (crystal_index1 >= crystals_to_plot.size()) continue;
            
            h1_germanium_energy[crystal_index1]->Fill(energy1);
            h1_germanium_energy_last[crystal_index1]->Fill(energy1);
            h2_germanium_energy_vs_detidx->Fill(hit1->Get_channel_energy(),crystal_index1);
            h1_germanium_time[crystal_index1]->Fill(time1);
            h1_germanium_hitpattern->Fill(Form("%d%c",crystals_to_plot.at(crystal_index1).first,(char)(crystals_to_plot.at(crystal_index1).second+65)),1);
            if (!(germanium_configuration->IsDetectorAuxilliary(detector_id1))) h1_germanium_energy_summed->Fill(energy1);


            if (nHits >= 2 && dt_reference_detectors.size()>=0){ // reference detector id loop.
                for (int ihit2 = 0; ihit2 < nHits; ihit2++){
                    if (ihit == ihit2) continue;
                    GermaniumCalData * hit2 = (GermaniumCalData*)fHitGe->At(ihit2);
                    int detector_id2 = hit2->Get_detector_id();
                    int crystal_id2 = hit2->Get_crystal_id();
                    double energy2 = hit2->Get_channel_energy();
                    double time2 = hit2->Get_channel_trigger_time();

                    int crystal_index2 = std::distance(dt_reference_detectors.begin(), std::find(dt_reference_detectors.begin(),dt_reference_detectors.end(),std::pair<int,int>(detector_id2,crystal_id2)));                   
                    if (crystal_index2 >= dt_reference_detectors.size()) continue;

                    while (crystal_index2 < dt_reference_detectors.size()){

                    if (dt_reference_detectors_energy_gates.at(crystal_index2).first > 0 && dt_reference_detectors_energy_gates.at(crystal_index2).second > 0){
                        if ((TMath::Abs(energy2 - dt_reference_detectors_energy_gates.at(crystal_index2).first) < energygate_width) && (TMath::Abs(energy1 - dt_reference_detectors_energy_gates.at(crystal_index2).second) < energygate_width)){
                            h1_germanium_time_differences[crystal_index2][crystal_index1]->Fill(time1 - time2);
                            h2_germanium_time_differences_vs_energy[crystal_index2][crystal_index1]->Fill(energy1,time1-time2);
                        }
                    }else{ // no gates
                        h1_germanium_time_differences[crystal_index2][crystal_index1]->Fill(time1 - time2);
                        h2_germanium_time_differences_vs_energy[crystal_index2][crystal_index1]->Fill(energy1,time1-time2);
                    }

                    crystal_index2 = std::distance(dt_reference_detectors.begin()+crystal_index2+1, std::find(dt_reference_detectors.begin()+crystal_index2+1,dt_reference_detectors.end(),std::pair<int,int>(detector_id2,crystal_id2)))+crystal_index2+1; 
                    }
                }
            }
        }


        if (!sci41_seen){ // sci41 vetoed spectra:
            for (Int_t ihit = 0; ihit < nHits; ihit++)
            {   
                GermaniumCalData* hit1 = (GermaniumCalData*)fHitGe->At(ihit);
                if (!hit1) continue;
                int detector_id1 = hit1->Get_detector_id();
                int crystal_id1 = hit1->Get_crystal_id();
                double energy1 = hit1->Get_channel_energy();
                double time1 = hit1->Get_channel_trigger_time();
                if (germanium_configuration->IsDetectorAuxilliary(detector_id1)) continue;

                h1_germanium_energy_summed_vetosci41->Fill(energy1);

                if (nHits >= 2){
                    for (Int_t ihit2 = 0; ihit2 < nHits; ihit2++)
                    {   
                        if (ihit2 == ihit) continue;
                        GermaniumCalData* hit2 = (GermaniumCalData*)fHitGe->At(ihit2);
                        if (!hit2) continue;
                        int detector_id2 = hit2->Get_detector_id();
                        int crystal_id2 = hit2->Get_crystal_id();
                        double energy2 = hit2->Get_channel_energy();
                        double time2 = hit2->Get_channel_trigger_time();

                        if (germanium_configuration->IsDetectorAuxilliary(detector_id2) && detector_id1 != detector_id2) continue;
                        if (TMath::Abs(time2 - time1) < 200) {
                            h2_germanium_energy_energy_vetosci41->Fill(energy1,energy2);
                        }
                    }

                }
            }
        }


        // Spectra with respect to SCI41:
        if (nHits >= 2 && sci41_seen){
        for (int ihit1 = 0; ihit1 < nHits; ihit1 ++){

            GermaniumCalData* hit_sci41 = (GermaniumCalData*)fHitGe->At(ihit1);
            if (!hit_sci41) continue;
            int detector_id_sci41 = hit_sci41->Get_detector_id();
            int crystal_id_sci41 = hit_sci41->Get_crystal_id();
            double energy_sci41 = hit_sci41->Get_channel_energy();
            double time_sci41 = hit_sci41->Get_channel_trigger_time();

            // after this test we have the sci41 hit.
            if (detector_id_sci41 != germanium_configuration->SC41L() && detector_id_sci41 != germanium_configuration->SC41R()) continue;

            for (int ihit2 = 0; ihit2 < nHits; ihit2 ++){
                GermaniumCalData* hit2 = (GermaniumCalData*)fHitGe->At(ihit2);
                if (!hit2) continue;
                int detector_id1 = hit2->Get_detector_id();
                int crystal_id1 = hit2->Get_crystal_id();
                double energy1 = hit2->Get_channel_energy();
                double time1 = hit2->Get_channel_trigger_time();

                if (germanium_configuration->IsDetectorAuxilliary(detector_id1)) continue;

                double timediff = time1 - time_sci41 - germanium_configuration->GetTimeshiftCoefficient(detector_id1,crystal_id1);
                
                h2_germanium_energy_summed_vs_tsci41->Fill(timediff ,energy1);

                if ((TMath::Abs(time1-time_sci41 > 0)) || (germanium_configuration->IsInsidePromptFlashCut(timediff ,energy1)==false) ) h1_germanium_energy_summed_vs_tsci41_cut->Fill(energy1);

                for (int ihit3 = ihit2+1; ihit3 < nHits; ihit3 ++){
                GermaniumCalData* hit3 = (GermaniumCalData*)fHitGe->At(ihit3);
                if (!hit3) continue;
                int detector_id2 = hit3->Get_detector_id();
                int crystal_id2 = hit3->Get_crystal_id();
                double energy2 = hit3->Get_channel_energy();
                double time2 = hit3->Get_channel_trigger_time();

                if (germanium_configuration->IsDetectorAuxilliary(detector_id2)) continue;

                if (TMath::Abs(time1 - time2) < 500) h2_germanium_energy_energy_sci41_cut->Fill(energy1,energy2);
                }
            }
            break;
        }
        }
        


        h1_germanium_multiplicity->Fill(event_multiplicity);

        int64_t wr_dt = (germanium_wr - saved_germanium_wr) / 1e9; // conv to s
        if (wr_dt > 2) 
        {
            if (saved_germanium_wr != 0)
            {
                for (int i = 0; i < number_of_detectors_to_plot; i++)
                {
                    detector_rates[i] = detector_counters[i] / wr_dt;
                    h1_germanium_rates[i]->SetBinContent(rate_running_count, detector_rates[i]);
                }
            }
            
            saved_germanium_wr = germanium_wr;
            rate_running_count++;
            for (int i = 0; i < number_of_detectors_to_plot; i++) detector_counters[i] = 0;
            if (rate_running_count == 1800) rate_running_count = 0;
        }
    }

    fNEvents += 1;
}

void GermaniumOnlineSpectra::FinishEvent()
{   
    /*
    if (first_time > 0)
    {
        if (((int64_t)current_wr - (int64_t)last_time_resolution_was_measured)/1e9 > seconds_to_collect_resolution){
            // c4LOG(info, "Finding resolutions"); // CEJ: commenting out for now
            h1_last_resolutions_FWHM->Reset();
            h1_last_resolutions_FWTM->Reset();
            h1_last_resolutions_gratio->Reset();


            // measure resolutions:
            for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
                f1_gaussian->SetParameter(0,1e3);
                f1_gaussian->SetParameter(1,centroid_resolution);
                f1_gaussian->SetParameter(2,width_resolution);

                c1_germanium_energy_last_fitted->cd(ihist+1);

                TString name = h1_germanium_energy_last_fitted[ihist]->GetName();
                if (h1_germanium_energy_last_fitted[ihist] != nullptr){
                    delete h1_germanium_energy_last_fitted[ihist];
                }
                h1_germanium_energy_last_fitted[ihist] = (TH1F*)h1_germanium_energy_last[ihist]->Clone(name);
                
                Int_t fitresult = h1_germanium_energy_last_fitted[ihist]->Fit(f1_gaussian,"QRL");


                if (fitresult == 0){

                h1_germanium_energy_last_fitted[ihist]->Draw();
                //f1_gaussian->Draw();

                double fwhm = f1_gaussian->GetParameter(2)*2.355;
                
                double tenthmaximum = f1_gaussian->Eval(f1_gaussian->GetParameter(1))/10.0;
        
                int binnr1 = h1_germanium_energy[ihist]->FindBin(centroid_resolution-50);
                int binnr2 = h1_germanium_energy[ihist]->FindBin(centroid_resolution+50);
                int binlow = h1_germanium_energy_last_fitted[ihist]->FindFirstBinAbove(tenthmaximum,1,binnr1,binnr2);
                int binhigh = h1_germanium_energy_last_fitted[ihist]->FindLastBinAbove(tenthmaximum,1,binnr1,binnr2);

                double fwtm = h1_germanium_energy_last_fitted[ihist]->GetBinCenter(binhigh) - h1_germanium_energy_last_fitted[ihist]->GetBinCenter(binlow);

                c_resolutions_FWHM->cd(ihist+1);
                g1_resolutions_FWHM[ihist]->AddPoint(((int64_t)current_wr - (int64_t)first_time)/1e9, fwhm);
                g1_resolutions_FWHM[ihist]->Draw("ALP");
                
                c_resolutions_FWTM->cd(ihist+1);
                g1_resolutions_FWTM[ihist]->AddPoint(((int64_t)current_wr - (int64_t)first_time)/1e9, fwtm);
                g1_resolutions_FWTM[ihist]->Draw("ALP");
                
                c_resolutions_gratio->cd(ihist+1);
                g1_resolutions_gratio[ihist]->AddPoint(((int64_t)current_wr - (int64_t)first_time)/1e9, fwtm/fwhm);
                g1_resolutions_gratio[ihist]->Draw("ALP");
                //c_resolutions_FWHM->cd(0);
                
                c_last_resolutions_FWHM->cd(1);
                h1_last_resolutions_FWHM->Fill(Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fwhm);
                h1_last_resolutions_FWHM->Draw("HIST");
                c_last_resolutions_FWHM->cd(2);
                h1_last_resolutions_FWTM->Fill(Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fwtm);
                h1_last_resolutions_FWTM->Draw("HIST");
                c_last_resolutions_FWHM->cd(3);
                h1_last_resolutions_gratio->Fill(Form("%d%c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fwtm/fwhm);
                h1_last_resolutions_gratio->Draw("HIST");
                c_last_resolutions_FWHM->cd(0);

                }

                last_time_resolution_was_measured = current_wr;

                h1_germanium_energy_last[ihist]->Reset();
            }
        }
    }
    */

    if (fHitGe){
        fHitGe->Clear();
    }



}

void GermaniumOnlineSpectra::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    if (fHitGe)
    {
        c4LOG(info, "DEGAS histograms written to file.");
    }
}

ClassImp(GermaniumOnlineSpectra)
