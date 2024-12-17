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
 *                              C.E. Jones                                    *
 *                               25.11.24                                     *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FatimaGermaniumCorrelations.h"
#include "EventHeader.h"
#include "FatimaTwinpeaksData.h"
#include "FatimaTwinpeaksCalData.h"
#include "FrsGate.h"
#include "FrsHitData.h"
#include "TFatimaTwinpeaksConfiguration.h"

#include "c4Logger.h"


#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TGraph.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TDirectory.h"

FatimaGermaniumCorrelations::FatimaGermaniumCorrelations() 
    : FatimaGermaniumCorrelations("FatimaGermaniumCorrelations")
{
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
    germanium_configuration = TGermaniumConfiguration::GetInstance();

}

FatimaGermaniumCorrelations::FatimaGermaniumCorrelations(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatima(NULL)
    , fNEvents(0)
    , header(nullptr)
{    
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
    germanium_configuration = TGermaniumConfiguration::GetInstance();
}

FatimaGermaniumCorrelations::~FatimaGermaniumCorrelations()
{
    c4LOG(info, "Deleting FatimaGermaniumCorrelation.");
    if (fHitFatima)
        delete fHitFatima;
    if (fHitGermanium)
        delete fHitGermanium;
}


InitStatus FatimaGermaniumCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance();

    header = mgr->InitObjectAs<decltype(header)>("EventHeader.");
    c4LOG_IF(fatal, !header, "Branch EventHeader. not found!");

    fHitFatima = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatima, "Branch FatimaTwinpeaksCalData not found!");

    fHitGermanium = (TClonesArray*)mgr->GetObject("GermaniumCalData");
    c4LOG_IF(fatal, !fHitGermanium, "Branch FrsHitData not found!");


    // look for correlations

    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_fatima_germanium = gDirectory->mkdir(TString("Germanium-Fatima coincidences"));
    gDirectory->cd(TString("Germanium-Fatima coincidences"));


    dir_fatima_germanium->cd();




    dir_fatima_germanium->cd();
    gDirectory = tmp;

    return kSUCCESS;
}


void FatimaGermaniumCorrelations::Exec(Option_t* option)
{
    
    fNEvents += 1;
}

void FatimaGermaniumCorrelations::FinishEvent()
{
    if (fHitFatima)
    {
        fHitFatima->Clear();
    }
    if (fHitGermanium){
        fHitGermanium->Clear();
    }
}

void FatimaGermaniumCorrelations::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    
    TDirectory* tmp = gDirectory;
    FairRootManager::Instance()->GetOutFile()->cd();
    dir_fatima_germanium->Write();
    gDirectory = tmp;
    c4LOG(info, "Germanium-Fatima histograms written to file.");
}

ClassImp(FatimaGermaniumCorrelations)
