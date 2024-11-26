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
    ,   multihitArray(nullptr)
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

    multihitArray = mgr->InitObjectAs<decltype(multihitArray)>("FrsMultiHitData");
    c4LOG_IF(fatal, !multihitArray, "Branch FrsMultiHitData not found!");

    travMusCalArray = mgr->InitObjectAs<decltype(travMusCalArray)>("TravMusCalData");
    c4LOG_IF(fatal, !travMusCalArray, "Branch TravMusCalData not found!");

    travMusAnaArray = mgr->InitObjectAs<decltype(travMusAnaArray)>("TravMusAnaData");
    c4LOG_IF(fatal, !travMusAnaArray, "Branch TravMusAnaData not found!");


   

    FairRootManager::Instance()->GetOutFile()->cd();
    dir_corr = gDirectory->mkdir("FRS-TravMus Correlations");

        
    // hists init                
                        
                    
    
 
    return kSUCCESS;

}



void FrsTravMusCorrelations::Exec(Option_t* option)
{   
    // reject events without both subsystems
    if (frsHitArray->size() <= 0 || travMusAnaArray->size() <= 0) return; // frs and travmus subevent exists

    const auto & frsHitItem = frsHitArray->at(0); // *should* only be 1 FRS subevent per event
    const auto & travMusicHitItem = travMusAnaArray->at(0); 
    
    //const auto & multihitItem = multihitArray->at(0);

    int64_t wr_FRS = frsHitItem.Get_wr_t();
    int64_t wr_travMUSIC = travMusicHitItem.Get_wr_t();

    // Energy from frs
    Float_t energy_MUSIC_1 = frsHitItem.Get_music_dE(0); 
    Float_t energy_MUSIC_2 = frsHitItem.Get_music_dE(1);
    double energy_travMUSIC = travMusicHitItem.Get_travmusic_dE();
    double energy_travMUSIC_driftcorr = travMusicHitItem.Get_travmusic_dE_driftcorr();


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
    c4LOG(info, "Written LISA analysis histograms to file.");
    //c4LOG(info, "Multi hit events when LISA is in the event (correlated) : " <<  multi_evt++ << " LISA-FRS events : " << fNEvents);


}


ClassImp(FrsTravMusCorrelations)