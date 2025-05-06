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

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsAidaBplastGermaniumCorrelations.h"
#include "EventHeader.h"
#include "TbPlastConfiguration.h"
#include "TFrsConfiguration.h"
#include "TGermaniumConfiguration.h"
#include "TAidaConfiguration.h"
#include "bPlastTwinpeaksCalData.h"
#include "GermaniumFebexData.h"
#include "FrsHitData.h"
#include "AidaData.h"
#include "AidaHitData.h"

#include "c4Logger.h"

#include "TCanvas.h"
#include "TClonesArray.h"
#include "TFolder.h"
#include "TH1F.h"
#include "TH2F.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include "TFile.h"
#include "TDirectory.h"

FrsAidaBplastGermaniumCorrelations::FrsAidaBplastGermaniumCorrelations() : FrsAidaBplastGermaniumCorrelations("bPlastNearlineSpectra")
{
    germanium_config = TGermaniumConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    bplast_config = TbPlastConfiguration::GetInstance();
    aida_config = TAidaConfiguration::GetInstance();
}

FrsAidaBplastGermaniumCorrelations::FrsAidaBplastGermaniumCorrelations(FrsGate* frsgate) : FrsAidaBplastGermaniumCorrelations()
{
    germanium_config = TGermaniumConfiguration::GetInstance();
    frs_config = TFrsConfiguration::GetInstance();
    bplast_config = TbPlastConfiguration::GetInstance();
    aida_config = TAidaConfiguration::GetInstance();

    frsgate = fg;
}

FrsAidaBplastGermaniumCorrelations::FrsAidaBplastGermaniumCorrelations(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitbPlastTwinpeaks(NULL)
    , fHitGe(NULL)
    , implantHitArray(nullptr)
    , decayHitArray(nullptr)
    , fNEvents(0)
    , fEventHeader(nullptr)
{
}

FrsAidaBplastGermaniumCorrelations::~FrsAidaBplastGermaniumCorrelations()
{
    c4LOG(info, "");
    if (fHitbPlastTwinpeaks)
        delete fHitbPlastTwinpeaks;
    if (fHitGe)
        delete fHitGe;
    if (fHitFrs)
        delete fHitFrs;
}

void FrsAidaBplastGermaniumCorrelations::SetParContainers()
{
    FairRuntimeDb *rtdb = FairRuntimeDb::instance();
    c4LOG_IF(fatal, NULL == rtdb, "FairRuntimeDb not found.");
}


InitStatus FrsAidaBplastGermaniumCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunAna* run = FairRunAna::Instance(); // do we need to grab the run? maybe we can add objects to it

    fEventHeader = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !fEventHeader, "Branch EventHeader. not found");

    // Hit data
    implantHitArray = mgr->InitObjectAs<decltype(implantHitArray)>("AidaImplantHits");
    c4LOG_IF(fatal, !implantHitArray, "Branch AidaImplantHits not found!");
    decayHitArray = mgr->InitObjectAs<decltype(decayHitArray)>("AidaDecayHits");
    c4LOG_IF(fatal, !decayHitArray, "Branch AidaDecayHits not found!");
    fHitbPlast = (TClonesArray*)mgr->GetObject("bPlastCalData");
    c4LOG_IF(fatal, !fHitbPlast, "Branch bPlastCalData not found!");
    fHitGe = (TClonesArray*)mgr->GetObject("GermaniumData");
    c4LOG_IF(fatal, !fHitGe, "Branch GermaniumData not found!");
    fHitFrs = (TClonesArray*)mgr->GetObject("FrsHitData");
    c4LOG_IF(fatal, !fHitFrs, "Branch FrsHitData not found!");

    // Configuration
    TbPlastConfiguration const* bplast_conf = TbPlastConfiguration::GetInstance();
    TFrsConfiguration const* frs_conf = TFrsConfiguration::GetInstance();
    TGermaniumConfiguration const* ge_conf = TGermaniumConfiguration::GetInstance();
    TAidaConfiguration const* aida_conf = TAidaConfiguration::GetInstance();


    int xstrips = aida_conf->Wide() ? 386 : 128;
    double xmax = aida_conf->Wide() ? 113.4 : 37.8;

    bplast_map = bplast_conf->Mapping();
    int nDetectors = bplast_conf->NDetectors();
    int nTamexBoards = bplast_conf->NTamexBoards();

    TDirectory::TContext ctx(nullptr);

    folder_germanium = new TFolder(TString("DEGAS-AIDA-bPlast Offspill " + frsgate->GetName()), TString("DEGAS-AIDA-bPlast Offspill " + frsgate->GetName()));

    run->AddObject(folder_germanium);

    // FRS Gated
    c_frs_Z_vs_AoQ_gated = new TCanvas(TString("c_frs_Z_vs_AoQ_gated_" + frsgate->GetName()), TString("c_frs_Z_vs_AoQ_gated_" + frsgate->GetName()), 10, 10, 800, 700);
    h2_frs_Z_vs_AoQ_gated = new TH2F(TString("h2_frs_Z_vs_AoQ_gated_" + frsgate->GetName()), TString("h2_frs_Z_vs_AoQ_gated_" + frsgate->GetName()), 100, 0, 5, 100, 0, 100);
    h2_frs_Z_vs_AoQ_gated->GetXaxis()->SetTitle("A/Q");
    h2_frs_Z_vs_AoQ_gated->GetYaxis()->SetTitle("Z");
    h2_frs_Z_vs_AoQ_gated->Draw("colz");
    c_frs_Z_vs_AoQ_gated->cd(0);
    folder_germanium->Add(c_frs_Z_vs_AoQ_gated);
    folder_germanium->Add(h2_frs_Z_vs_AoQ_gated);

    c_frs_Z_vs_Z2_gated = new TCanvas(TString("c_frs_Z_vs_Z2_gated_" + frsgate->GetName()), TString("c_frs_Z_vs_Z2_gated_" + frsgate->GetName()), 10, 10, 800, 700);
    h2_frs_Z_vs_Z2_gated = new TH2F(TString("h2_frs_Z_vs_Z2_gated_" + frsgate->GetName()), TString("h2_frs_Z_vs_Z2_gated_" + frsgate->GetName()), 100, 0, 100, 100, 0, 100);
    h2_frs_Z_vs_Z2_gated->GetXaxis()->SetTitle("Z2");
    h2_frs_Z_vs_Z2_gated->GetYaxis()->SetTitle("Z");
    h2_frs_Z_vs_Z2_gated->Draw("colz");
    c_frs_Z_vs_Z2_gated->cd(0);
    folder_germanium->Add(c_frs_Z_vs_Z2_gated);
    folder_germanium->Add(h2_frs_Z_vs_Z2_gated);

    c_frs_x2_vs_AoQ_gated = new TCanvas(TString("c_frs_x2_vs_AoQ_gated_" + frsgate->GetName()), TString("c_frs_x2_vs_AoQ_gated_" + frsgate->GetName()), 10, 10, 800, 700);
    h2_frs_x2_vs_AoQ_gated = new TH2F(TString("h2_frs_x2_vs_AoQ_gated_" + frsgate->GetName()), TString("h2_frs_x2_vs_AoQ_gated_" + frsgate->GetName()), 100, -100, 100, 100, 0, 5);
    h2_frs_x2_vs_AoQ_gated->GetXaxis()->SetTitle("A/Q");
    h2_frs_x2_vs_AoQ_gated->GetYaxis()->SetTitle("X2");
    h2_frs_x2_vs_AoQ_gated->Draw("colz");
    c_frs_x2_vs_AoQ_gated->cd(0);
    folder_germanium->Add(c_frs_x2_vs_AoQ_gated);
    folder_germanium->Add(h2_frs_x2_vs_AoQ_gated);

    c_frs_x4_vs_AoQ_gated = new TCanvas(TString("c_frs_x4_vs_AoQ_gated_" + frsgate->GetName()), TString("c_frs_x4_vs_AoQ_gated_" + frsgate->GetName()), 10, 10, 800, 700);
    h2_frs_x4_vs_AoQ_gated = new TH2F(TString("h2_frs_x4_vs_AoQ_gated_" + frsgate->GetName()), TString("h2_frs_x4_vs_AoQ_gated_" + frsgate->GetName()), 100, -100, 100, 100, 0, 5);
    h2_frs_x4_vs_AoQ_gated->GetXaxis()->SetTitle("A/Q");
    h2_frs_x4_vs_AoQ_gated->GetYaxis()->SetTitle("X4");
    h2_frs_x4_vs_AoQ_gated->Draw("colz");
    c_frs_x4_vs_AoQ_gated->cd(0);
    folder_germanium->Add(c_frs_x4_vs_AoQ_gated);
    folder_germanium->Add(h2_frs_x4_vs_AoQ_gated);

    // AIDA Gated
    c_aida_implants_dssd1_frs_gated = new TCanvas(TString("c_aida_implants_dssd1_frs_gated_" + frsgate->GetName()), TString("c_aida_implants_dssd1_frs_gated_" + frsgate->GetName()), 10, 10, 800, 700);
    h2_aida_implants_dssd1_frs_gated = new TH2F(TString("h2_aida_implants_dssd1_frs_gated_" + frsgate->GetName()), TString("h2_aida_implants_dssd1_frs_gated_" + frsgate->GetName()),xstrips,0,xmax,128,0,128);
    h2_aida_implants_dssd1_frs_gated->GetXaxis()->SetTitle("X-strip");
    h2_aida_implants_dssd1_frs_gated->GetYaxis()->SetTitle("Y-strip");
    h2_aida_implants_dssd1_frs_gated->Draw("colz");
    c_aida_implants_dssd1_frs_gated->cd(0);
    folder_germanium->Add(c_aida_implants_dssd1_frs_gated);
    folder_germanium->Add(h2_aida_implants_dssd1_frs_gated);

    c_aida_implants_dssd2_frs_gated = new TCanvas(TString("c_aida_implants_dssd2_frs_gated_" + frsgate->GetName()), TString("c_aida_implants_dssd2_frs_gated_" + frsgate->GetName()), 10, 10, 800, 700);
    h2_aida_implants_dssd2_frs_gated = new TH2F(TString("h2_aida_implants_dssd2_frs_gated_" + frsgate->GetName()), TString("h2_aida_implants_dssd2_frs_gated_" + frsgate->GetName()),xstrips,0,xmax,128,0,128);
    h2_aida_implants_dssd2_frs_gated->GetXaxis()->SetTitle("X-strip");
    h2_aida_implants_dssd2_frs_gated->GetYaxis()->SetTitle("Y-strip");
    h2_aida_implants_dssd2_frs_gated->Draw("colz");
    c_aida_implants_dssd2_frs_gated->cd(0);
    folder_germanium->Add(c_aida_implants_dssd2_frs_gated);
    folder_germanium->Add(h2_aida_implants_dssd2_frs_gated);

    // bPlast summed Slow_ToT
    c_bplast_fast_vs_slow_gated = new TCanvas(TString("c_bplast_fast_vs_slow_gated_" + frsgate->GetName()), TString("c_bplast_fast_vs_slow_gated_" + frsgate->GetName()), 10, 10, 800, 700);
    h2_bplast_fast_vs_slow_gated = new TH2F(TString("h2_bplast_fast_vs_slow_gated_" + frsgate->GetName()), TString("h2_bplast_fast_vs_slow_gated_" + frsgate->GetName()), 1000, 0, 3e3, 1000, 0, 3e3);
    h2_bplast_fast_vs_slow_gated->GetXaxis()->SetTitle("Slow ToT");
    h2_bplast_fast_vs_slow_gated->GetYaxis()->SetTitle("Fast ToT");
    h2_bplast_fast_vs_slow_gated->Draw("colz");
    c_bplast_fast_vs_slow_gated->cd(0);
    folder_germanium->Add(c_bplast_fast_vs_slow_gated);
    folder_germanium->Add(h2_bplast_fast_vs_slow_gated);


    // Germanium spectra

    // TBA lets get the correlations right first



    return kSUCCESS;
    
}


void FrsAidaBplastGermaniumCorrelations::Exec(Option_t* option)
{   
    if (fHitbPlastTwinpeaks && fHitbPlastTwinpeaks->GetEntriesFast() > 0)
    {
        Int_t nHits = fHitbPlastTwinpeaks->GetEntriesFast();
        for (Int_t ihit = 0; ihit < nHits; ihit++) // bplast hits
        {   
            bPlastTwinpeaksCalData* bplasthit = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(ihit);
            if (!bplasthit) continue;
            
            if (bplasthit->Get_detector_id() > NDetectors || bplasthit->Get_detector_id() < 0) continue;

            // Lead and Trail spectra -- empty for now

            // Fast and Slow Tot spectra
            // if (bplasthit->Get_slow_ToT() != 0) h1_bplast_slowToT[bplasthit->Get_detector_id()]->Fill(bplasthit->Get_slow_ToT());
            // if (bplasthit->Get_fast_ToT() != 0) h1_bplast_fastToT[bplasthit->Get_detector_id()]->Fill(bplasthit->Get_fast_ToT());

            // // fast vs slow:
            // if ( (bplasthit->Get_fast_ToT() != 0) && (bplasthit->Get_slow_ToT() != 0) ) h2_bplast_slowToT_vs_fastToT[bplasthit->Get_detector_id()]->Fill(bplasthit->Get_fast_ToT(),bplasthit->Get_slow_ToT());

            // // Hit pattern spectra
            // // the hit pattern spectrum is generated by filling the histogram with the detector ID of the hit

            // if (bplasthit->Get_fast_ToT() != 0) h1_bplast_fast_hitpatterns->Fill(bplasthit->Get_detector_id());
            // if (bplasthit->Get_slow_ToT() != 0) h1_bplast_slow_hitpatterns->Fill(bplasthit->Get_detector_id());

            // // Absolute time spectra
            // if (bplasthit->Get_fast_ToT() !=0 ) h1_bplast_abs_time[bplasthit->Get_detector_id()]->Fill(bplasthit->Get_fast_lead_time());
            // Relative time spectra
            // if(fEventData->Get_Spill_Flag() == false)
            // {
                for (auto const& hit : *decayHitArray)
                {
                    if (bplasthit->Get_detector_id() == 1){
                        Int_t nnHits = fHitbPlastTwinpeaks->GetEntriesFast();
                        for (Int_t i = 0; i < nnHits; i++) // bplast hits
                        {   
                            bPlastTwinpeaksCalData* bplasthitsecond = (bPlastTwinpeaksCalData*)fHitbPlastTwinpeaks->At(i);

                            if (!bplasthitsecond) continue;
                            if (bplasthitsecond->Get_fast_lead_time() == 0 || bplasthit->Get_fast_lead_time() == 0) continue;
                            if (hit.DSSD == 1 && hit.StripX > 81 && hit.StripX < 141 && hit.StripY > 57 && hit.StripY < 97){
                                h1_bplast_rel_time[bplasthitsecond->Get_detector_id()]->Fill(bplasthitsecond->Get_fast_lead_time()-bplasthit->Get_fast_lead_time());
                            } // filling histograms gated on aida
                        } // second loop hits
                    } // SiPM detector 1 condition
                } // aida loop
            // } // spill flag condition
        } // bplast loop
    } // if bplast hits
    fNEvents += 1;
} // exec

void FrsAidaBplastGermaniumCorrelations::FinishEvent()
{
    if (fHitbPlastTwinpeaks)
    {
        fHitbPlastTwinpeaks->Clear();
    }
}

void FrsAidaBplastGermaniumCorrelations::FinishTask()
{
    if (fHitbPlastTwinpeaks)
    {
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_slowToT[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_fastToT[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h2_bplast_slowToT_vs_fastToT[ihist]->Write();
        h1_bplast_fast_hitpatterns->Write();
        h1_bplast_slow_hitpatterns->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_abs_time[ihist]->Write();
        for (int ihist = 0; ihist<NDetectors; ihist++) h1_bplast_rel_time[ihist]->Write();
    }
}

ClassImp(FrsAidaBplastGermaniumCorrelations)
