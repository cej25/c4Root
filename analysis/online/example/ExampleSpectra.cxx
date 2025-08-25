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
 *                               C.E. Jones                                   *
 *                                06.05.25                                    *
 ******************************************************************************/

#include "ExampleSpectra.h"

#include "FairRootManager.h"

#include "c4Logger.h"
#include "AnalysisTools.h"

ExampleSpectra::ExampleSpectra()
    : ExampleSpectra("ExampleSpectra")
{
    
}

ExampleSpectra::ExampleSpectra(const TString& name, Int_t iVerbose)
    : FairTask(name, iVerbose)
    , fNEvents(0)
    , header(nullptr)
    , fatimaCalData(nullptr)
{
}

ExampleSpectra::~ExampleSpectra()
{

}

InitStatus ExampleSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");
    
    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");
    
    fatimaCalData = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fatimaCalData, "Branch FatimaTwinpeaksCalData not found!");
    
    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_example = new TDirectory("Example Spectra", "Example Spectra", "", 0);
    histograms->Add(dir_example);

    // make histograms
    h1_fat_energy = MakeTH1(dir_example, "F", "h1_fat_energy", "Fatima Energy (Example)", 1000, 0, 2000, "Energy [keV]", kSpring, kBlue+2);

    return kSUCCESS;

}

void ExampleSpectra::Exec(Option_t* option)
{   
    // check fatima hits exist
    if (fatimaCalData && fatimaCalData->GetEntriesFast() > 0)
    {   
        // loop through all fatima hits
        Int_t nHits = fatimaCalData->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++)
        {   
            FatimaTwinpeaksCalData* hit = (FatimaTwinpeaksCalData*)fatimaCalData->At(ihit);
            if (!hit) continue;

            double energy1 = hit->Get_energy();
            int detector_id1 = hit->Get_detector_id();

            if (detector_id1 == 1) h1_fat_energy->Fill(energy1);

        }
    }

    fNEvents++;
}

void ExampleSpectra::FinishEvent()
{
    // in this basic task we don't need to use this function
}

void ExampleSpectra::FinishTask()
{
    // this is an online task, so we don't write histograms
}


