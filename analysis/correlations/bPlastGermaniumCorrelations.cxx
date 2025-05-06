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
 *                                C.E. Jones                                  *
 *                                 06.05.25                                   *
 ******************************************************************************/

#include "bPlastGermaniumCorrelations.h"

// FairROOT
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"

// c4
#include "bPlastGermaniumCorrelations.h"
#include "EventHeader.h"
#include "c4Logger.h"

#include <map>

bPlastGermaniumCorrelations::bPlastGermaniumCorrelations()
    :   FairTask()
    ,   header(nullptr)
    ,   fNEvents(0)
{
    germanium_config = TGermaniumConfiguration::GetInstance();
    bplast_config = TbPlastConfiguration::GetInstance();
}

bPlastGermaniumCorrelations::bPlastGermaniumCorrelations(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   header(nullptr)
    ,   fNEvents(0)
{
    germanium_config = TGermaniumConfiguration::GetInstance();
    bplast_config = TbPlastConfiguration::GetInstance();
}

bPlastGermaniumCorrelations::~bPlastGermaniumCorrelations()
{

}

InitStatus bPlastGermaniumCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitbPlastTwinpeaks = (TClonesArray*)mgr->GetObject("bPlastTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitbPlastTwinpeaks, "Branch bPlastTwinpeaksCalData not found!");

    fHitGermanium = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fHitGermanium, "Branch GermaniumCalData not found!");

    dir_germanium = (TDirectory*)mgr->GetObject("DEGAS");

    crystals_to_plot.clear();
    std::map<std::pair<int,int>,std::pair<int,int>> gmap = germanium_config->Mapping();

    for (auto it_mapping = gmap.begin(); it_mapping != gmap.end(); ++it_mapping){
        if (it_mapping->second.first >= 0) crystals_to_plot.emplace_back(std::pair<int,int>(it_mapping->second.first,it_mapping->second.second));
    }

    number_of_detectors_to_plot = crystals_to_plot.size();



    dir_bplast_germanium_corrs = dir_germanium->mkdir("bPlast Correlations");

    dir_bplast_germanium_corrs->cd();

    //h1_germanium_energy_bplast_corr = new TH1F*[number_of_detectors_to_plot];
    h1_germanium_energy_bplast_corr.resize(number_of_detectors_to_plot);
    for (int ihist = 0; ihist < number_of_detectors_to_plot; ihist++){
        h1_germanium_energy_bplast_corr[ihist] = new TH1F(Form("h1_germanium_energy_%d_%d_bplast_corr",crystals_to_plot.at(ihist).first,crystals_to_plot.at(ihist).second),Form("Ge E - Det %d Cryst %c - Off-spill correlation w/ bPlast hit",crystals_to_plot.at(ihist).first,(char)(crystals_to_plot.at(ihist).second+65)),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_germanium_energy_bplast_corr[ihist]->GetXaxis()->SetTitle("energy [keV]");
    }
    h1_germanium_energy_bplast_corr_sum = new TH1F("h1_germanium_energy_bplast_corr_summed","Summed Ge E Off-spill correlation w/ bPlast hit",fenergy_nbins,fenergy_bin_low,fenergy_bin_high);

    dir_germanium->cd();

    return kSUCCESS;

}

void bPlastGermaniumCorrelations::Exec(Option_t* option)
{
    if (header->GetSpillFlag() == 1) return; // skip on-spill
    if (fHitbPlastTwinpeaks->GetEntriesFast() == 0 || fHitGermanium->GetEntriesFast() == 0) return;

    if (fHitGermanium && fHitGermanium->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitGermanium->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {
            GermaniumCalData* GeHit = (GermaniumCalData*)fHitGermanium->At(ihit);
            if (!GeHit) continue;

            int detector_id = GeHit->Get_detector_id();
            int crystal_id = GeHit->Get_crystal_id();
            double energy = GeHit->Get_channel_energy();
            double time = GeHit->Get_channel_trigger_time();

            if ((germanium_config->IsDetectorAuxilliary(detector_id))) continue; // skip residuals

            int crystal_index = std::distance(crystals_to_plot.begin(), std::find(crystals_to_plot.begin(),crystals_to_plot.end(),std::pair<int,int>(detector_id,crystal_id)));
            if (crystal_index >= crystals_to_plot.size()) continue;
            h1_germanium_energy_bplast_corr[crystal_index]->Fill(energy);
            h1_germanium_energy_bplast_corr_sum->Fill(energy);

        }

    }

}

void bPlastGermaniumCorrelations::FinishEvent()
{

}

void bPlastGermaniumCorrelations::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_bplast_germanium_corrs->Write();
    gDirectory = tmp;
}