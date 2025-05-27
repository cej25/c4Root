/******************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2024 Members of HISPEC/DESPEC Collaboration                *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************
 *                             J.E.L. Larsson                                 *
 *                                06.05.25                                    *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "BGONearlineSpectra.h"
#include "EventHeader.h"
#include "BGOTwinpeaksCalData.h"
#include "GermaniumCalData.h"
#include "TGermaniumConfiguration.h"
#include "TBGOTwinpeaksConfiguration.h"

#include "AnalysisTools.h"
#include "c4Logger.h"

#include "TClonesArray.h"
#include "TGraph.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"

BGONearlineSpectra::BGONearlineSpectra() : BGONearlineSpectra("BGONearlineSpectra")
{
    germanium_configuration = TGermaniumConfiguration::GetInstance();
    BGO_configuration = TBGOTwinpeaksConfiguration::GetInstance();
}

BGONearlineSpectra::BGONearlineSpectra(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitGe(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    germanium_configuration = TGermaniumConfiguration::GetInstance();
    BGO_configuration = TBGOTwinpeaksConfiguration::GetInstance();
}

BGONearlineSpectra::~BGONearlineSpectra()
{
    c4LOG(info, "");
    if (fHitGe)
        delete fHitGe;
}

InitStatus BGONearlineSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitGe = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fHitGe, "Branch GermaniumCalData not found!");

    fHitBGO = (TClonesArray*)mgr->GetObject("BGOTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitBGO, "Branch BGOTwinpeaksData not found!");

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_bgo = gDirectory->mkdir("BGO");
    gDirectory->cd("BGO");

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
    //dir_bgo_energy->cd();
    h1_bgo_energy.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h1_bgo_energy[ihist] = MakeTH1(dir_bgo_energy, "F", Form("h1_bgo_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("BGO uncal energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high, "Energy [a.u]", kSpring, kBlue+2);
        //h1_bgo_energy[ihist] = new TH1F(Form("h1_bgo_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("BGO uncal energy spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        //h1_bgo_energy[ihist]->GetXaxis()->SetTitle("energy (arb.)");
    }
    
    // time spectra:
    //dir_bgo_time->cd();
    h1_bgo_time.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h1_bgo_time[ihist] = MakeTH1(dir_bgo_time, "F", Form("h1_bgo_time_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("BGO time spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,1e12, "Time [ns]");
        //h1_bgo_time[ihist] = new TH1F(Form("h1_bgo_time_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("BGO time spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,1e12);
        //h1_bgo_time[ihist]->GetXaxis()->SetTitle("time (ns)");
    }

    //dir_bgo_germanium_veto_energy->cd();
    // energy spectra:
    h1_germanium_bgo_veto_energy.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h1_germanium_bgo_veto_energy[ihist] = MakeTH1(dir_bgo_germanium_veto_energy, "F", Form("h1_germanium_bgo_veto_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c - BGO vetoed",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,3e3, "Energy [keV]", kOrange-3, kBlue+2);
        //h1_germanium_bgo_veto_energy[ihist] = new TH1F(Form("h1_germanium_bgo_veto_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c - BGO vetoed",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,3e3);
        //h1_germanium_bgo_veto_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
    }

    //dir_bgo_germanium_vetotrue_energy->cd();
    h1_germanium_bgo_vetotrue_energy.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h1_germanium_bgo_vetotrue_energy[ihist] = MakeTH1(dir_bgo_germanium_vetotrue_energy, "F", Form("h1_germanium_bgo_vetotrue_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c - BGO veto = true",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,3e3, "Energy [keV]", kSpring, kBlue+2);
        //h1_germanium_bgo_vetotrue_energy[ihist] = new TH1F(Form("h1_germanium_bgo_vetotrue_energy_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("DEGAS energy spectrum detector %d crystal %c - BGO veto = true",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e3,0,3e3);
        //h1_germanium_bgo_vetotrue_energy[ihist]->GetXaxis()->SetTitle("energy (keV)");
    }

    // time differences spectra:
    //dir_bgo_germanium_veto_time_differences->cd();
    h1_germanium_bgo_veto_timedifferences.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++)
    {
        h1_germanium_bgo_veto_timedifferences[ihist] = MakeTH1(dir_bgo_germanium_veto_time_differences, "F", Form("h1_germanium_bgo_veto_timedifferences_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("BGO-DEGAS time spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e2,-10e3,10e3, "Time BGO-Ge [ns]", kMagenta, kBlue+2);
        //h1_germanium_bgo_veto_timedifferences[ihist] = new TH1F(Form("h1_germanium_bgo_veto_timedifferences_%d_%d",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("BGO-DEGAS time spectrum detector %d crystal %c",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),10e2,-10e3,10e3);
        //h1_germanium_bgo_veto_timedifferences[ihist]->GetXaxis()->SetTitle("time BGO-Ge (ns)");
    }

    dir_bgo->cd();
    gDirectory = tmp;

    return kSUCCESS;
}

void BGONearlineSpectra::Exec(Option_t* option)
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

                
                    //if (detector_id_bgo2 == detector_id_ge && crystal_id_ge == crystal_id_bgo2){
                        int64_t dt = hit2->Get_wr_t() - hit_ge->Get_wr_t();
                        h1_germanium_bgo_veto_timedifferences[crystal_index_bgo2]->Fill(dt);    
                        if (TMath::Abs(dt)<BGO_Germanium_wr_coincidence_window + BGO_Germanium_wr_coincidence_window_offset){
                            //VETO!
                            veto = true;
                        }
                   // } 
                }
            }
            if (!veto) h1_germanium_bgo_veto_energy[crystal_index_ge]->Fill(energy_ge);
            else h1_germanium_bgo_vetotrue_energy[crystal_index_ge]->Fill(energy_ge);
        }
    }
    
    
    fNEvents += 1;
}

void BGONearlineSpectra::FinishEvent()
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

void BGONearlineSpectra::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_bgo->Write();
    gDirectory = tmp;
}

ClassImp(BGONearlineSpectra)
