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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25..11.24                                    *
 ******************************************************************************/

#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairTask.h"

#include "AnalysisTools.h"
#include "FrsTravMusCorrelations.h"
#include "c4Logger.h"
#include "TFile.h"
#include "THttpServer.h"
#include "TCanvas.h"

FrsTravMusCorrelations::FrsTravMusCorrelations() 
    : FrsTravMusCorrelations("FrsTravMusCorrelations")
{

}

FrsTravMusCorrelations::FrsTravMusCorrelations(std::vector<FrsGate*> fg)
    : FrsTravMusCorrelations("FrsTravMusCorrelations")
{
    FrsGates = fg;
}

FrsTravMusCorrelations::FrsTravMusCorrelations(const TString& name, Int_t verbose)
    :   FairTask(name, verbose)
    ,   header(nullptr)
    ,   frsHitArray(nullptr)
    ,   frsMultihitArray(nullptr)
    ,   travMusCalArray(nullptr)
    ,   travMusAnaArray(nullptr)
    ,   fNEvents(0)

{
    frs_config = TFrsConfiguration::GetInstance();
}

FrsTravMusCorrelations::~FrsTravMusCorrelations()
{
    c4LOG(info, "Destroyed FrsTravMusCorrelationsProperly.");
}

InitStatus FrsTravMusCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    frsHitArray = mgr->InitObjectAs<decltype(frsHitArray)>("FrsHitData");
    c4LOG_IF(fatal, !frsHitArray, "Branch FrsHitData not found!");

    frsMultihitArray = mgr->InitObjectAs<decltype(frsMultihitArray)>("FrsMultiHitData");
    c4LOG_IF(fatal, !frsMultihitArray, "Branch FrsMultiHitData not found!");

    travMusCalArray = mgr->InitObjectAs<decltype(travMusCalArray)>("TravMusCalData");
    c4LOG_IF(fatal, !travMusCalArray, "Branch TravMusCalData not found!");

    travMusAnaArray = mgr->InitObjectAs<decltype(travMusAnaArray)>("TravMusAnaData");
    c4LOG_IF(fatal, !travMusAnaArray, "Branch TravMusAnaData not found!");


   
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_corr = gDirectory->mkdir("FRS-TravMus Correlations");
 
    // correlations + Z from SC1
    // h2_travmus_vs_Z = MakeTH2(dir_tac_2d, "D", "h2_travmus_vs_Z", "Z (Travel MUSIC) vs Z (MUSIC 1)", 750, frs_config->fMin_Z, frs_config->fMax_Z, 750, frs_config->fMin_Z, frs_config->fMax_Z, "Z (Travel MUSIC)", "Z (MUSIC 1)");

    // correlations + Z from SC1
    // h2_travmus_vs_Z_mhtdc = MakeTH2(dir_mhtdc_2d, "D", "h2_travmus_vs_Z_mhtdc", "Z (Trav) vs. Z1 (MHTDC)", 1000, frs_config->fMin_Z, frs_config->fMax_Z, 400, frs_config->fMin_Z, frs_config->fMax_Z, "Z (Travel MUSIC)", "Z (MUSIC 1)");
             
    h2_Z_vs_AoQ_driftcorr_trav_gate = MakeTH2(dir_corr, "D", "h2_Z_vs_AoQ_tac_driftcorr_trav_gate", "Z1 vs. A/Q (DriftCorr)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);                       
    h2_Z_vs_AoQ_tac_trav_gate_driftcorr = MakeTH2(dir_corr, "D", "h2_Z_vs_AoQ_tac_trav_gate_driftcorr", "Z1 vs. A/Q (TAC) DriftCorr", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);
    h2_Z_vs_AoQ_mhtdc_trav_gate = MakeTH2(dir_corr, "D", "h2_Z_vs_AoQ_mhtdc_trav_gate", "Z1 vs. A/Q (MHTDC)", 1500, frs_config->fMin_AoQ, frs_config->fMax_AoQ, 1000, frs_config->fMin_Z, frs_config->fMax_Z);

 
    return kSUCCESS;

}



void FrsTravMusCorrelations::Exec(Option_t* option)
{   
    // reject events without both subsystems
    if (frsHitArray->size() <= 0 || travMusAnaArray->size() <= 0) return; // frs and travmus subevent exists

    const auto & frsHitItem = frsHitArray->at(0); // *should* only be 1 FRS subevent per event
    const auto & travMusicHitItem = travMusAnaArray->at(0); 

    int64_t wr_FRS = frsHitItem.Get_wr_t();
    int64_t wr_travMUSIC = travMusicHitItem.Get_wr_t();

    // Energy from frs
    Float_t energy_MUSIC_1 = frsHitItem.Get_music_dE(0); 
    Float_t energy_MUSIC_2 = frsHitItem.Get_music_dE(1);
    double energy_travMUSIC = travMusicHitItem.Get_travmusic_dE();
    double energy_travMUSIC_driftcorr = travMusicHitItem.Get_travmusic_dE_driftcorr();

    // need S1 scintillator
    // if (wr_travMUSIC > 0 && hitItem.Get_ID_z_travmus() > 0) h1_Z_travmus->Fill(hitItem.Get_ID_z_travmus());

    // need S1 scintillator
    // if (wr_travMUSIC > 0 && multihitItem.Get_ID_z_travmus_mhtdc() > 0) h1_z_travmus_mhtdc->Fill(multihitItem.Get_ID_z_travmus_mhtdc());
    
    // need S1 scintillator
    // if (hitItem.Get_ID_z_travmus() > 0 && FRS_time_mins > 0) h2_Ztrav_vs_T->Fill(FRS_time_mins, hitItem.Get_ID_z_travmus());


    if(travMusicHitItem.Get_travmusic_dE() >= frs_config->fMin_dE_travMus_gate && travMusicHitItem.Get_travmusic_dE() <= frs_config->fMax_dE_travMus_gate)
    {
        h2_Z_vs_AoQ_driftcorr_trav_gate->Fill(frsHitItem.Get_ID_AoQ_driftcorr(), frsHitItem.Get_ID_z_driftcorr());
    }

    if(travMusicHitItem.Get_travmusic_dE_driftcorr() >= frs_config->fMin_dE_travMus_gate && travMusicHitItem.Get_travmusic_dE_driftcorr() <= frs_config->fMax_dE_travMus_gate)
    {
        h2_Z_vs_AoQ_tac_trav_gate_driftcorr->Fill(frsHitItem.Get_ID_AoQ_driftcorr(), frsHitItem.Get_ID_z_driftcorr());
    }


    for (auto const & multihitItem : *frsMultihitArray)
    {
        if(travMusicHitItem.Get_travmusic_dE() >= frs_config->fMin_dE_travMus_gate && travMusicHitItem.Get_travmusic_dE() <= frs_config->fMax_dE_travMus_gate)
        {
            h2_Z_vs_AoQ_mhtdc_trav_gate->Fill(multihitItem.Get_ID_AoQ_mhtdc(), multihitItem.Get_ID_z_mhtdc());
        }
    }

    fNEvents++;

}

void FrsTravMusCorrelations::FinishEvent()
{

}

void FrsTravMusCorrelations::FinishTask()
{
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_corr->Write();
    c4LOG(info, "Written FRS-TravMus analysis histograms to file.");


}


ClassImp(FrsTravMusCorrelations)