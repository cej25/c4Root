// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BGOOnlineSpectra.h"
#include "EventHeader.h"
#include "BGOTwinpeaksCalData.h"
#include "GermaniumCalData.h"
#include "TGermaniumConfiguration.h"
#include "TBGOTwinpeaksConfiguration.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"

BGOOnlineSpectra::BGOOnlineSpectra() : BGOOnlineSpectra("BGOOnlineSpectra")
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
    BGO_configuration = TBGOTwinpeaksConfiguration::GetInstance();
}

BGOOnlineSpectra::BGOOnlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    germanium_configuration = TGermaniumConfiguration::GetInstance();
    BGO_configuration = TBGOTwinpeaksConfiguration::GetInstance();
}

BGOOnlineSpectra::~BGOOnlineSpectra()
{
    c4LOG(info, "");
    if (fHitGe)
        delete fHitGe;
}

void BGOOnlineSpectra::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}

InitStatus BGOOnlineSpectra::Init()
{

    // number of crystals, number of dets 

    c4LOG(info, "");
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitGe = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fHitGe, "Branch GermaniumCalData not found!");


    fHitBGO = (TClonesArray*)mgr->GetObject("BGOTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitBGO, "Branch BGOTwinpeaksData not found!");
    
    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_bgo = new TDirectory("BGO", "BGO", "", 0);
    //mgr->Register("BGO", "BGO Directory", dir_bgo, false); // allow other tasks to access directory.
    histograms->Add(dir_bgo);

    dir_bgo_energy = dir_bgo->mkdir("Raw Energy Spectra");
    dir_bgo_time = dir_bgo->mkdir("Time Spectra");
    dir_bgo_germanium_veto_energy = dir_bgo->mkdir("BGO vetoed Germanium spectra");
    dir_bgo_germanium_veto_time_differences = dir_bgo->mkdir("BGO veto time differences");
    dir_bgo_germanium_vetotrue_energy = dir_bgo->mkdir("BGO veto true Germanium spectra");

    crystals_to_plot.clear();
    std::map<std::pair<int,int>,std::pair<int,int>> bgomap = BGO_configuration->Mapping();
    std::map<std::pair<int,int>,std::pair<int,int>> gmap = germanium_configuration->Mapping();

    BGO_Germanium_wr_coincidence_window = BGO_configuration->Window();
    BGO_Germanium_wr_coincidence_window_offset = BGO_configuration->Offset();


    for (auto it_mapping = bgomap.begin(); it_mapping != bgomap.end(); ++it_mapping)
    {
        std::pair<int,int> detector_crystal_pair {it_mapping->second.first,it_mapping->second.second};
        if (it_mapping->second.first >= 0) crystals_to_plot.emplace_back(detector_crystal_pair);
        
        //oh yeah:
        if (std::find_if(gmap.begin(), gmap.end(), [&](const auto& m2_pair) {
            return m2_pair.second == detector_crystal_pair;
        }) != gmap.end()) {
            c4LOG(warning, Form("The following bgo crystal %d%c was not found in the germanium detector map.",detector_crystal_pair.first,(char)(detector_crystal_pair.second+65)));
        }
    }

    number_of_detectors_to_plot = crystals_to_plot.size();

    // energy spectra:
    dir_bgo_energy->cd();
    c_bgo_energy  = new TCanvas("c_bgo_energy","Calibrated bgo spectra",650,350);
    c_bgo_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_bgo_energy.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_bgo_energy->cd(ihist+1);
        h1_bgo_energy[ihist] = new TH1F(Form("h1_bgo_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("BGO uncal energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_bgo_energy[ihist]->GetXaxis()->SetTitle("energy (arb.)");
        h1_bgo_energy[ihist]->Draw();
    }
    c_bgo_energy->cd(0);
    dir_bgo_energy->Append(c_bgo_energy);
    
    // time spectra:
    dir_bgo_time->cd();
    c_bgo_time  = new TCanvas("c_bgo_time","BGO tamex time spectra",650,350);
    c_bgo_time->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_bgo_time.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_bgo_time->cd(ihist+1);
        h1_bgo_time[ihist] = new TH1F(Form("h1_bgo_time_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("BGO time spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,1e12);
        h1_bgo_time[ihist]->GetXaxis()->SetTitle("time (ns)");
        h1_bgo_time[ihist]->Draw();
    }
    c_bgo_time->cd(0);
    dir_bgo_time->Append(c_bgo_time);

    dir_bgo_germanium_veto_energy->cd();
    // energy spectra:
    c_germanium_bgo_veto_energy  = new TCanvas("c_germanium_bgo_veto_energy","Calibrated Germanium spectra vetoed BGO",650,350);
    c_germanium_bgo_veto_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_bgo_veto_energy.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_germanium_bgo_veto_energy->cd(ihist+1);
        h1_germanium_bgo_veto_energy[ihist] = new TH1F(Form("h1_germanium_bgo_veto_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c - BGO vetoed",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,3e3);
        h1_germanium_bgo_veto_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_bgo_veto_energy[ihist]->Draw();
    }
    c_germanium_bgo_veto_energy->cd(0);
    dir_bgo_germanium_veto_energy->Append(c_germanium_bgo_veto_energy);

    dir_bgo_germanium_vetotrue_energy->cd();
    c_germanium_bgo_vetotrue_energy  = new TCanvas("c_germanium_bgo_vetotrue_energy","Cal Germanium E spectra - BGO veto = true",650,350);
    c_germanium_bgo_vetotrue_energy->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_bgo_vetotrue_energy.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_germanium_bgo_vetotrue_energy->cd(ihist+1);
        h1_germanium_bgo_vetotrue_energy[ihist] = new TH1F(Form("h1_germanium_bgo_vetotrue_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c - BGO veto = true",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,3e3);
        h1_germanium_bgo_vetotrue_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
        h1_germanium_bgo_vetotrue_energy[ihist]->Draw();
    }
    c_germanium_bgo_vetotrue_energy->cd(0);
    dir_bgo_germanium_vetotrue_energy->Append(c_germanium_bgo_vetotrue_energy);


    // CEJ: should we cd to timedifference spectra folder?
    // time differences spectra:
    dir_bgo_germanium_veto_time_differences->cd();
    c_germanium_bgo_veto_timedifferences  = new TCanvas("c_germanium_bgo_veto_timedifferences","WR BGO-Germanium time differences",650,350);
    c_germanium_bgo_veto_timedifferences->Divide((number_of_detectors_to_plot<5) ? number_of_detectors_to_plot : 5,(number_of_detectors_to_plot%5==0) ? (number_of_detectors_to_plot/5) : (number_of_detectors_to_plot/5 + 1));
    h1_germanium_bgo_veto_timedifferences.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        c_germanium_bgo_veto_timedifferences->cd(ihist+1);
        h1_germanium_bgo_veto_timedifferences[ihist] = new TH1F(Form("h1_germanium_bgo_veto_timedifferences_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("BGO-DEGAS time spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e2,-10e3,10e3);
        h1_germanium_bgo_veto_timedifferences[ihist]->GetXaxis()->SetTitle("time BGO-Ge (ns)");
        h1_germanium_bgo_veto_timedifferences[ihist]->Draw();
    }
    c_germanium_bgo_veto_timedifferences->cd(0);
    dir_bgo_germanium_veto_time_differences->Append(c_germanium_bgo_veto_timedifferences);

    dir_bgo->cd();

    run->GetHttpServer()->RegisterCommand("Reset_BGO_Histo", Form("/Objects/%s/->Reset_BGO_Histo()", GetName()));
    run->GetHttpServer()->RegisterCommand("Snapshot_BGO_Histo", Form("/Objects/%s/->Snapshot_BGO_Histo()", GetName()));

    return kSUCCESS;
}

void BGOOnlineSpectra::Reset_BGO_Histo()
{
    c4LOG(info, "Reset command received. Clearing histograms.");
    
    for (int ihist = 0; ihist<number_of_detectors_to_plot; ihist++) 
    {
        h1_bgo_energy[ihist]->Reset();
        h1_bgo_time[ihist]->Reset();
        h1_germanium_bgo_veto_energy[ihist]->Reset();
        h1_germanium_bgo_vetotrue_energy[ihist]->Reset();
        h1_germanium_bgo_veto_timedifferences[ihist]->Reset();
    }
}

void BGOOnlineSpectra::Snapshot_BGO_Histo()
{
    c4LOG(info, "");

    //date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    //make folder with date and time
    const char* snapshot_dir = Form("bgo_snapshot_%d_%d_%d_%d_%d_%d",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec);
    gSystem->cd(screenshot_path);
    gSystem->mkdir(snapshot_dir);
    gSystem->cd(snapshot_dir);

    // save histograms to canvases
    c_bgo_snapshot = new TCanvas("c_bgo_snapshot","BGO snapshot",650,350);

    for (int ihist = 0; ihist<number_of_detectors_to_plot; ihist++) 
    {
        h1_bgo_energy[ihist]->Draw();
        c_bgo_snapshot->SaveAs(Form("bgo_energy_%d_%d.png",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
        c_bgo_snapshot->Clear();
        h1_bgo_time[ihist]->Draw();
        c_bgo_snapshot->SaveAs(Form("bgo_time_%d_%d.png",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
        c_bgo_snapshot->Clear();
        h1_germanium_bgo_veto_energy[ihist]->Draw();
        c_bgo_snapshot->SaveAs(Form("germanium_bgo_veto_energy_%d_%d.png",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
        c_bgo_snapshot->Clear();
        h1_germanium_bgo_veto_timedifferences[ihist]->Draw();
        c_bgo_snapshot->SaveAs(Form("germanium_bgo_veto_timedifferences_%d_%d.png",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second));
        c_bgo_snapshot->Clear();
    }

    delete c_bgo_snapshot;

    //commented for now. directories :()
    // // snapshot .root file with data and time
    // file_bgo_snapshot = new TFile(Form("bgo_snapshot_%d_%d_%d_%d_%d_%d.root",ltm->tm_year+1900,ltm->tm_mon,ltm->tm_mday,ltm->tm_hour,ltm->tm_min,ltm->tm_sec),"RECREATE");
    // file_bgo_snapshot->cd();
    // dir_bgo->Write();
    // file_bgo_snapshot->Close();
    // delete file_bgo_snapshot;

    gSystem->cd("..");
    c4LOG(info, "Snapshot saved to:" << snapshot_dir);

}

void BGOOnlineSpectra::Exec(Option_t* option)
{      
    if (fHitBGO && fHitBGO->GetEntriesFast() > 0)
    {
        Int_t nBGOHits = fHitBGO->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nBGOHits; ihit++)
        {   
            BGOTwinpeaksCalData* hit = (BGOTwinpeaksCalData*)fHitBGO->At(ihit);
            if (!hit) continue;
            int detector_id_bgo = hit->Get_detector_id();
            int crystal_id_bgo = hit->Get_crystal_id();
            int crystal_index_bgo = std::distance(crystals_to_plot.begin(), std::find(crystals_to_plot.begin(),crystals_to_plot.end(),std::pair<int,int>(detector_id_bgo,crystal_id_bgo)));
            
            if (crystal_index_bgo >= crystals_to_plot.size()) continue;

            double energy_bgo = hit->Get_energy();
            double time_bgo = hit->Get_fast_lead_time();

            h1_bgo_energy[crystal_index_bgo]->Fill(energy_bgo);
            h1_bgo_time[crystal_index_bgo]->Fill(time_bgo);


        }
    }

    if (fHitGe && fHitGe->GetEntriesFast() > 0)
    {
        Int_t nGeHits = fHitGe->GetEntriesFast();
        int event_multiplicity = 0;
        for (Int_t ihit = 0; ihit < nGeHits; ihit++)
        {   
            GermaniumCalData* hit_ge = (GermaniumCalData*)fHitGe->At(ihit);
            if (!hit_ge) continue;
            int detector_id_ge = hit_ge->Get_detector_id();
            int crystal_id_ge = hit_ge->Get_crystal_id();
            double energy_ge = hit_ge->Get_channel_energy();
            double time_ge = hit_ge->Get_channel_trigger_time();

            int crystal_index_ge = std::distance(crystals_to_plot.begin(), std::find(crystals_to_plot.begin(),crystals_to_plot.end(),std::pair<int,int>(detector_id_ge,crystal_id_ge)));
            if (crystal_index_ge >= crystals_to_plot.size()) continue;
            

            bool veto = false;
            
            int crystal_index_bgo2 = 0;

            
            if (fHitBGO && fHitBGO->GetEntriesFast() > 0){
                Int_t nBGOHits = fHitBGO->GetEntriesFast();
                for (Int_t ihit2 = 0; ihit2 < nBGOHits; ihit2++)
                {   
                    BGOTwinpeaksCalData* hit2 = (BGOTwinpeaksCalData*)fHitBGO->At(ihit);
                    if (!hit2) continue;
                    int detector_id_bgo2 = hit2->Get_detector_id();
                    int crystal_id_bgo2 = hit2->Get_crystal_id();
                    
                    crystal_index_bgo2 = std::distance(crystals_to_plot.begin(), std::find(crystals_to_plot.begin(),crystals_to_plot.end(),std::pair<int,int>(detector_id_bgo2,crystal_id_bgo2)));
                    if (crystal_index_bgo2 >= crystals_to_plot.size()) continue;

                
                    if (detector_id_bgo2 == detector_id_ge && crystal_id_ge == crystal_id_bgo2){
                        int64_t dt = hit2->Get_wr_t() - hit_ge->Get_wr_t();
                        h1_germanium_bgo_veto_timedifferences[crystal_index_bgo2]->Fill(dt);    
                        if (TMath::Abs(dt)<BGO_Germanium_wr_coincidence_window + BGO_Germanium_wr_coincidence_window_offset)
                        {
                            //VETO!
                            veto = true;
                        }
                    } 
                }
            }
            if (!veto) h1_germanium_bgo_veto_energy[crystal_index_ge]->Fill(energy_ge);
            else h1_germanium_bgo_vetotrue_energy[crystal_index_ge]->Fill(energy_ge);
            
        }
    }
    
    
    fNEvents += 1;
}

void BGOOnlineSpectra::FinishEvent()
{
    if (fHitGe)
    {
        fHitGe->Clear();
    }
    if (fHitBGO)
    {
        fHitBGO->Clear();
    }
}

void BGOOnlineSpectra::FinishTask()
{

}

ClassImp(BGOOnlineSpectra)
