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
 *                               17.12.24                                     *
 ******************************************************************************/

// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsFatimaCorrelations.h"
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

FrsFatimaCorrelations::FrsFatimaCorrelations() : FrsFatimaCorrelations("FrsFatimaCorrelations")
{
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
    frs_configuration = TFrsConfiguration::GetInstance();

}

FrsFatimaCorrelations::FrsFatimaCorrelations(FrsGate * fg) : FrsFatimaCorrelations("FrsFatimaCorrelations")
{
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
    frsgate = fg;
    frs_configuration = TFrsConfiguration::GetInstance();
}

FrsFatimaCorrelations::FrsFatimaCorrelations(const TString& name, Int_t verbose)
    : FairTask(name, verbose)
    , fHitFatima(NULL)
    , hitArrayFrs(nullptr)
    , fNEvents(0)
    , header(nullptr)
{    
    fatima_configuration = TFatimaTwinpeaksConfiguration::GetInstance();
}

FrsFatimaCorrelations::~FrsFatimaCorrelations()
{
    c4LOG(info, "");
    if (fHitFatima)
        delete fHitFatima;

}


InitStatus FrsFatimaCorrelations::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline * run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    fHitFatima = (TClonesArray*)mgr->GetObject("FatimaTwinpeaksCalData");
    c4LOG_IF(fatal, !fHitFatima, "Branch FatimaTwinpeaksCalData not found!");
    hitArrayFrs = mgr->InitObjectAs<decltype(hitArrayFrs)>("FrsHitData");
    c4LOG_IF(fatal, !hitArrayFrs, "Branch FrsHitData not found!");
    //Multihit vetos:
    mainSciArray = mgr->InitObjectAs<decltype(mainSciArray)>("FrsMainCalSciData");
    c4LOG_IF(fatal, !mainSciArray, "Branch FrsMainCalSciData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    histograms = (TFolder*)mgr->GetObject("Histograms");

    TDirectory::TContext ctx(nullptr);

    dir_corr = (TDirectory*)mgr->GetObject("Correlations");
    if (dir_corr == nullptr) 
    {
        LOG(info) << "Creating Correlations Directory";
        FairRootManager::Instance()->GetOutFile()->cd();
        dir_corr = gDirectory->mkdir("Correlations");
        mgr->Register("Correlations", "Correlations Directory", dir_corr, false); // allow other tasks to find this
        histograms->Add(dir_corr);
    }

    TString dirname = "FATIMA - FRS Gated: " + frsgate->GetName();
    dir_fatima = dir_corr->mkdir(dirname);

    dir_fatima->cd();

    //Implant rate
    c_frs_rate = new TCanvas(TString("c_frs_fatima_rate_monitor_gated_")+frsgate->GetName(),TString("Implant rate gated on ")+frsgate->GetName());
    g_frs_rate = new TGraph();
    g_frs_rate->SetName(TString("g_frs_fatima_rate_monitor_gated_")+frsgate->GetName());
    g_frs_rate->SetTitle(TString("FRS identified ions per second, avg 60 secs"));
    g_frs_rate->GetXaxis()->SetTitle("seconds");
    g_frs_rate->Draw("ALP");
    dir_fatima->Append(c_frs_rate);

    c_frs_total = new TCanvas(TString("c_frs_fatima_total_monitor_gated_")+frsgate->GetName(),TString("Implanted total ions gated on ")+frsgate->GetName());
    g_frs_total = new TGraph();
    g_frs_total->SetName(TString("g_frs_fatima_total_monitor_gated_")+frsgate->GetName());
    g_frs_total->SetTitle(TString("FRS identified ions in total"));
    g_frs_total->GetXaxis()->SetTitle("seconds");
    g_frs_total->Draw("ALP");
    dir_fatima->Append(c_frs_total);

    c_frs_Z_vs_AoQ_gated = new TCanvas(TString("c_frs_fatima_Z_vs_AoQ_gated_")+frsgate->GetName(),TString("Z vs AoQ plot gated on FRS ")+frsgate->GetName());
    h2_frs_Z_vs_AoQ_gated = new TH2F(TString("h2_frs_fatima_Z_vs_AoQ_gated_")+frsgate->GetName(),TString("Z vs AoQ plot gated on FRS ")+frsgate->GetName(),1000,frs_configuration->fMin_AoQ,frs_configuration->fMax_AoQ,1000,frs_configuration->fMin_Z,frs_configuration->fMax_Z);
    h2_frs_Z_vs_AoQ_gated->GetXaxis()->SetTitle("A/Q");
    h2_frs_Z_vs_AoQ_gated->GetYaxis()->SetTitle("Z");
    h2_frs_Z_vs_AoQ_gated->Draw("COLZ");
    c_frs_Z_vs_AoQ_gated->cd(0);
    dir_fatima->Append(c_frs_Z_vs_AoQ_gated);

    c_frs_Z_vs_Z2_gated = new TCanvas(TString("c_frs_fatima_Z_vs_Z2_gated_")+frsgate->GetName(),TString("Z1 vs Z2 plot gated on FRS ")+frsgate->GetName());
    h2_frs_Z_vs_Z2_gated = new TH2F(TString("h2_frs_fatima_Z_vs_Z2_gated_")+frsgate->GetName(),TString("Z1 vs Z2 plot gated on FRS ")+frsgate->GetName(),1000,frs_configuration->fMin_Z,frs_configuration->fMax_Z,1000,frs_configuration->fMin_Z,frs_configuration->fMax_Z);
    h2_frs_Z_vs_Z2_gated->GetXaxis()->SetTitle("Z1");
    h2_frs_Z_vs_Z2_gated->GetYaxis()->SetTitle("Z2");
    h2_frs_Z_vs_Z2_gated->Draw("COLZ");
    c_frs_Z_vs_Z2_gated->cd(0);
    dir_fatima->Append(c_frs_Z_vs_Z2_gated);


    c_frs_x2_vs_AoQ_gated = new TCanvas(TString("c_frs_fatima_x2_vs_AoQ_gated_")+frsgate->GetName(),TString("x2 vs AoQ plot gated on FRS ")+frsgate->GetName());
    h2_frs_x2_vs_AoQ_gated = new TH2F(TString("h2_frs_fatima_x2_vs_AoQ_gated_")+frsgate->GetName(),TString("x2 vs AoQ plot gated on FRS ")+frsgate->GetName(),1000,frs_configuration->fMin_AoQ,frs_configuration->fMax_AoQ,1000,frs_configuration->fMin_x2,frs_configuration->fMax_x2);
    h2_frs_x2_vs_AoQ_gated->GetYaxis()->SetTitle("x2");
    h2_frs_x2_vs_AoQ_gated->GetXaxis()->SetTitle("A/Q");
    h2_frs_x2_vs_AoQ_gated->Draw("COLZ");
    c_frs_x2_vs_AoQ_gated->cd(0);
    dir_fatima->Append(c_frs_x2_vs_AoQ_gated);

    c_frs_x4_vs_AoQ_gated = new TCanvas(TString("c_frs_fatima_x4_vs_AoQ_gated_")+frsgate->GetName(),TString("x4 vs AoQ plot gated on FRS ")+frsgate->GetName());
    h2_frs_x4_vs_AoQ_gated = new TH2F(TString("h2_frs_fatima_x4_vs_AoQ_gated_")+frsgate->GetName(),TString("x4 vs AoQ plot gated on FRS ")+frsgate->GetName(),1000,frs_configuration->fMin_AoQ,frs_configuration->fMax_AoQ,1000,frs_configuration->fMin_x4,frs_configuration->fMax_x4);
    h2_frs_x4_vs_AoQ_gated->GetXaxis()->SetTitle("A/Q");
    h2_frs_x4_vs_AoQ_gated->GetYaxis()->SetTitle("x4");
    h2_frs_x4_vs_AoQ_gated->Draw("COLZ");
    c_frs_x4_vs_AoQ_gated->cd(0);
    dir_fatima->Append(c_frs_x4_vs_AoQ_gated);
    

    c_frs_Z_vs_dEdeg_gated = new TCanvas(TString("c_frs_fatima_Z_vs_dEdeg_gated_")+frsgate->GetName(),TString("Z vs dEdeg plot gated on FRS ")+frsgate->GetName());
    h2_frs_Z_vs_dEdeg_gated = new TH2F(TString("h2_frs_fatima_Z_vs_dEdeg_gated_")+frsgate->GetName(),TString("Z vs dEdeg plot gated on FRS ")+frsgate->GetName(),1000,40,60,1000,frs_configuration->fMin_Z,frs_configuration->fMax_Z);
    h2_frs_Z_vs_dEdeg_gated->GetXaxis()->SetTitle("dEdeg");
    h2_frs_Z_vs_dEdeg_gated->GetYaxis()->SetTitle("Z");
    h2_frs_Z_vs_dEdeg_gated->Draw("COLZ");
    c_frs_Z_vs_dEdeg_gated->cd(0);
    dir_fatima->Append(c_frs_Z_vs_dEdeg_gated);


    c_frs_Z_vs_sci42E_gated = new TCanvas(TString("c_frs_fatima_Z_vs_sci42E_gated_")+frsgate->GetName(),TString("Z vs sci42 E plot gated on FRS ")+frsgate->GetName());
    h2_frs_Z_vs_sci42E_gated = new TH2F(TString("h2_frs_fatima_Z_vs_sci42E_gated_")+frsgate->GetName(),TString("Z vs sci42 E plot gated on FRS ")+frsgate->GetName(),1000,0,3000,1000,frs_configuration->fMin_Z,frs_configuration->fMax_Z);
    h2_frs_Z_vs_sci42E_gated->GetXaxis()->SetTitle("sci42E");
    h2_frs_Z_vs_sci42E_gated->GetYaxis()->SetTitle("Z");
    h2_frs_Z_vs_sci42E_gated->Draw("COLZ");
    c_frs_Z_vs_sci42E_gated->cd(0);
    dir_fatima->Append(c_frs_Z_vs_sci42E_gated);


    
    c_fatima_energy_vs_tsci41 = new TCanvas(TString("c_fatima_summed_vs_tsci41_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det) - t(sci41), short lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_energy_vs_tsci41 = new TH2F(TString("h2_fatima_energy_vs_tsci41_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det) - t(sci41), short lifetime,  gated FRS on "+frsgate->GetName()),10000,-2000,stop_short_lifetime_collection,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_vs_tsci41->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_energy_vs_tsci41->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_vs_tsci41->Draw("COLZ");
    c_fatima_energy_vs_tsci41->cd(0);
    dir_fatima->Append(c_fatima_energy_vs_tsci41);
    
    
    c_fatima_energy_vs_sci41_mult1 = new TCanvas(TString("c_fatima_energy_vs_sci41_mult1_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41) short lifetime, multiplicity 1, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_energy_vs_sci41_mult1 = new TH2F(TString("h2_fatima_energy_vs_sci41_mult1_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41) short lifetime, multiplicity 1, gated FRS on "+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_vs_sci41_mult1->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_energy_vs_sci41_mult1->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_vs_sci41_mult1->Draw("COLZ");
    c_fatima_energy_vs_sci41_mult1->cd(0);
    dir_fatima->Append(c_fatima_energy_vs_sci41_mult1);

    c_fatima_energy_vs_sci41_mult2 = new TCanvas(TString("c_fatima_energy_vs_sci41_mult2_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41) short lifetime, multiplicity 2, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_energy_vs_sci41_mult2 = new TH2F(TString("h2_fatima_energy_vs_sci41_mult2_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41) short lifetime, multiplicity 2, gated FRS on "+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_vs_sci41_mult2->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_energy_vs_sci41_mult2->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_vs_sci41_mult2->Draw("COLZ");
    c_fatima_energy_vs_sci41_mult2->cd(0);
    dir_fatima->Append(c_fatima_energy_vs_sci41_mult2);
    
    
    c_fatima_energy_vs_sci41_mult3 = new TCanvas(TString("c_fatima_energy_vs_sci41_mult3_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41) short lifetime, multiplicity 3, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_energy_vs_sci41_mult3 = new TH2F(TString("h2_fatima_energy_vs_sci41_mult3_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41) short lifetime, multiplicity 3, gated FRS on "+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_vs_sci41_mult3->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_energy_vs_sci41_mult3->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_vs_sci41_mult3->Draw("COLZ");
    c_fatima_energy_vs_sci41_mult3->cd(0);
    dir_fatima->Append(c_fatima_energy_vs_sci41_mult3);

    c_fatima_energy_vs_sci41_mult4p = new TCanvas(TString("c_fatima_energy_vs_sci41_mult4p_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41) short lifetime, multiplicity 3, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_energy_vs_sci41_mult4p = new TH2F(TString("h2_fatima_energy_vs_sci41_mult4p_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41) short lifetime, multiplicity 3, gated FRS on "+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_vs_sci41_mult4p->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_energy_vs_sci41_mult4p->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_vs_sci41_mult4p->Draw("COLZ");
    c_fatima_energy_vs_sci41_mult4p->cd(0);
    dir_fatima->Append(c_fatima_energy_vs_sci41_mult4p);
    

    c_fatima_energy_promptflash_cut_mult1 = new TCanvas(TString("c_fatima_energy_promptflash_cut_mult1_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 1, short lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut_mult1 = new TH1F(TString("h1_fatima_energy_promptflash_cut_mult1_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 1, short lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut_mult1->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut_mult1->Draw("COLZ");
    c_fatima_energy_promptflash_cut_mult1->cd(0);
    dir_fatima->Append(c_fatima_energy_promptflash_cut_mult1);

    c_fatima_energy_promptflash_cut_mult2 = new TCanvas(TString("c_fatima_energy_promptflash_cut_mult2_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 2, short lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut_mult2 = new TH1F(TString("h1_fatima_energy_promptflash_cut_mult2_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 2, short lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut_mult2->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut_mult2->Draw("COLZ");
    c_fatima_energy_promptflash_cut_mult2->cd(0);
    dir_fatima->Append(c_fatima_energy_promptflash_cut_mult2);

    c_fatima_energy_promptflash_cut_mult3 = new TCanvas(TString("c_fatima_energy_promptflash_cut_mult3_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 3, short lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut_mult3 = new TH1F(TString("h1_fatima_energy_promptflash_cut_mult3_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 3, short lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut_mult3->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut_mult3->Draw("COLZ");
    c_fatima_energy_promptflash_cut_mult3->cd(0);
    dir_fatima->Append(c_fatima_energy_promptflash_cut_mult3);

    c_fatima_energy_promptflash_cut_mult4p = new TCanvas(TString("c_fatima_energy_promptflash_cut_mult4p_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 4+, short lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut_mult4p = new TH1F(TString("h1_fatima_energy_promptflash_cut_mult4p_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 4+, short lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut_mult4p->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut_mult4p->Draw("COLZ");
    c_fatima_energy_promptflash_cut_mult4p->cd(0);
    dir_fatima->Append(c_fatima_energy_promptflash_cut_mult4p);

    c_fatima_multiplicity_vs_tsci41 = new TCanvas(TString("c_fatima_multiplicity_vs_tsci41_frs_gate_"+frsgate->GetName()),TString("Fatima multiplicity vs t(det) - t(sci41), short lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_multiplicity_vs_tsci41 = new TH2F(TString("h2_fatima_multiplicity_vs_tsci41_frs_gate_"+frsgate->GetName()),TString("Fatima multiplicity vs t(det) - t(sci41), short lifetime,  gated FRS on "+frsgate->GetName()),10000,-2000,stop_short_lifetime_collection,36,0,36);
    h2_fatima_multiplicity_vs_tsci41->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_multiplicity_vs_tsci41->GetYaxis()->SetTitle("multiplicity");
    h2_fatima_multiplicity_vs_tsci41->Draw("COLZ");
    c_fatima_multiplicity_vs_tsci41->cd(0);
    dir_fatima->Append(c_fatima_multiplicity_vs_tsci41);
    dir_fatima->Append(c_fatima_energy_vs_tsci41);

    
    c_fatima_energy_promptflash_cut = new TCanvas(TString("c_fatima_energy_promptflash_cut_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, short lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut = new TH1F(TString("h1_fatima_energy_promptflash_cut_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, short lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut->Draw("COLZ");
    c_fatima_energy_promptflash_cut->cd(0);
    dir_fatima->Append(c_fatima_energy_promptflash_cut);


    c_fatima_energy_energy_promptflash_cut = new TCanvas(TString("c_fatima_energy_energy_promptflash_cut_frs_gate_"+frsgate->GetName()),TString(Form("Fatima energy vs energy, |t(det1)-t(det2)|<%i ns, prompt flash cut out, short lifetime, gated FRS on ",fatima_coincidence_gate)+frsgate->GetName()),650,350);
    h2_fatima_energy_energy_promptflash_cut = new TH2F(TString("h2_fatima_energy_energy_promptflash_cut_frs_gate_"+frsgate->GetName()),TString(Form("Fatima energy vs energy, |t(det1)-t(det2)|<%i ns, prompt flash cut out, short lifetime, gated FRS on ",fatima_coincidence_gate)+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_energy_promptflash_cut->GetXaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_energy_promptflash_cut->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_energy_promptflash_cut->Draw("COLZ");
    c_fatima_energy_energy_promptflash_cut->cd(0);
    dir_fatima->Append(c_fatima_energy_energy_promptflash_cut);


    c_fatima_energy_vs_sci41_wr_long = new TCanvas(TString("c_fatima_energy_vs_sci41_wr_long_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_energy_vs_sci41_wr_long = new TH2F(TString("h2_fatima_energy_vs_sci41_wr_long_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, gated FRS on "+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_vs_sci41_wr_long->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_energy_vs_sci41_wr_long->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_vs_sci41_wr_long->Draw("COLZ");
    c_fatima_energy_vs_sci41_wr_long->cd(0);
    dir_fatima->Append(c_fatima_energy_vs_sci41_wr_long);

    c_fatima_multiplicity_vs_sci41_wr_long = new TCanvas(TString("c_fatima_multiplicity_vs_sci41_wr_long_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_multiplicity_vs_sci41_wr_long = new TH2F(TString("h2_fatima_multiplicity_vs_sci41_wr_long_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, gated FRS on "+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh,36,0,36);
    h2_fatima_multiplicity_vs_sci41_wr_long->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_multiplicity_vs_sci41_wr_long->GetYaxis()->SetTitle("multiplicity");
    h2_fatima_multiplicity_vs_sci41_wr_long->Draw("COLZ");
    c_fatima_multiplicity_vs_sci41_wr_long->cd(0);
    dir_fatima->Append(c_fatima_multiplicity_vs_sci41_wr_long);

    
    c_fatima_energy_promptflash_cut_long = new TCanvas(TString("c_fatima_energy_promptflash_cut_long_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, long lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut_long = new TH1F(TString("h1_fatima_energy_promptflash_cut_long_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, long lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut_long->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut_long->Draw("COLZ");
    c_fatima_energy_promptflash_cut_long->cd(0);
    dir_fatima->Append(c_fatima_energy_promptflash_cut_long);
    
    
    c_fatima_energy_vs_sci41_wr_long_mult1 = new TCanvas(TString("c_fatima_energy_vs_sci41_wr_long_mult1_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, multiplicity 1, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_energy_vs_sci41_wr_long_mult1 = new TH2F(TString("h2_fatima_energy_vs_sci41_wr_long_mult1_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, multiplicity 1, gated FRS on "+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_vs_sci41_wr_long_mult1->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_energy_vs_sci41_wr_long_mult1->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_vs_sci41_wr_long_mult1->Draw("COLZ");
    c_fatima_energy_vs_sci41_wr_long_mult1->cd(0);
    dir_fatima->Append(c_fatima_energy_vs_sci41_wr_long_mult1);

    c_fatima_energy_vs_sci41_wr_long_mult2 = new TCanvas(TString("c_fatima_energy_vs_sci41_wr_long_mult2_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, multiplicity 2, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_energy_vs_sci41_wr_long_mult2 = new TH2F(TString("h2_fatima_energy_vs_sci41_wr_long_mult2_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, multiplicity 2, gated FRS on "+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_vs_sci41_wr_long_mult2->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_energy_vs_sci41_wr_long_mult2->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_vs_sci41_wr_long_mult2->Draw("COLZ");
    c_fatima_energy_vs_sci41_wr_long_mult2->cd(0);
    dir_fatima->Append(c_fatima_energy_vs_sci41_wr_long_mult2);
    
    
    c_fatima_energy_vs_sci41_wr_long_mult3 = new TCanvas(TString("c_fatima_energy_vs_sci41_wr_long_mult3_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, multiplicity 3, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_energy_vs_sci41_wr_long_mult3 = new TH2F(TString("h2_fatima_energy_vs_sci41_wr_long_mult3_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, multiplicity 3, gated FRS on "+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_vs_sci41_wr_long_mult3->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_energy_vs_sci41_wr_long_mult3->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_vs_sci41_wr_long_mult3->Draw("COLZ");
    c_fatima_energy_vs_sci41_wr_long_mult3->cd(0);
    dir_fatima->Append(c_fatima_energy_vs_sci41_wr_long_mult3);

    c_fatima_energy_vs_sci41_wr_long_mult4p = new TCanvas(TString("c_fatima_energy_vs_sci41_wr_long_mult4p_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, multiplicity 3, gated FRS on "+frsgate->GetName()),650,350);
    h2_fatima_energy_vs_sci41_wr_long_mult4p = new TH2F(TString("h2_fatima_energy_vs_sci41_wr_long_mult4p_frs_gate_"+frsgate->GetName()),TString("Fatima energies vs t(det,wr) - t(sci41,wr) long lifetime, multiplicity 3, gated FRS on "+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_vs_sci41_wr_long_mult4p->GetXaxis()->SetTitle("time difference (ns)");
    h2_fatima_energy_vs_sci41_wr_long_mult4p->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_vs_sci41_wr_long_mult4p->Draw("COLZ");
    c_fatima_energy_vs_sci41_wr_long_mult4p->cd(0);
    dir_fatima->Append(c_fatima_energy_vs_sci41_wr_long_mult4p);


    c_fatima_energy_promptflash_cut_long_mult1 = new TCanvas(TString("c_fatima_energy_promptflash_cut_long_mult1_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 1, long lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut_long_mult1 = new TH1F(TString("h1_fatima_energy_promptflash_cut_long_mult1_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 1, long lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut_long_mult1->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut_long_mult1->Draw("COLZ");
    c_fatima_energy_promptflash_cut_long_mult1->cd(0);
    dir_fatima->Append(c_fatima_energy_promptflash_cut_long_mult1);

    c_fatima_energy_promptflash_cut_long_mult2 = new TCanvas(TString("c_fatima_energy_promptflash_cut_long_mult2_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 2, long lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut_long_mult2 = new TH1F(TString("h1_fatima_energy_promptflash_cut_long_mult2_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 2, long lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut_long_mult2->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut_long_mult2->Draw("COLZ");
    c_fatima_energy_promptflash_cut_long_mult2->cd(0);
    dir_fatima->Append(c_fatima_energy_promptflash_cut_long_mult2);

    c_fatima_energy_promptflash_cut_long_mult3 = new TCanvas(TString("c_fatima_energy_promptflash_cut_long_mult3_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 3, long lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut_long_mult3 = new TH1F(TString("h1_fatima_energy_promptflash_cut_long_mult3_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 3, long lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut_long_mult3->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut_long_mult3->Draw("COLZ");
    c_fatima_energy_promptflash_cut_long_mult3->cd(0);
    dir_fatima->Append(c_fatima_energy_promptflash_cut_long_mult3);

    c_fatima_energy_promptflash_cut_long_mult4p = new TCanvas(TString("c_fatima_energy_promptflash_cut_long_mult4p_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 4+, long lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_energy_promptflash_cut_long_mult4p = new TH1F(TString("h1_fatima_energy_promptflash_cut_long_mult4p_frs_gate_"+frsgate->GetName()),TString("Fatima energy, prompt flash cut out, multiplicity 4+, long lifetime, gated FRS on "+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h1_fatima_energy_promptflash_cut_long_mult4p->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_energy_promptflash_cut_long_mult4p->Draw("COLZ");
    c_fatima_energy_promptflash_cut_long_mult4p->cd(0);
    dir_fatima->Append(c_fatima_energy_promptflash_cut_long_mult4p);


    c_fatima_energy_energy_promptflash_cut_long = new TCanvas(TString("c_fatima_energy_energy_promptflash_cut_long_frs_gate_"+frsgate->GetName()),TString(Form("Fatima energy vs energy, |t(det1)-t(det2)|<%i ns, prompt flash cut out, long lifetime, gated FRS on ",fatima_coincidence_gate)+frsgate->GetName()),650,350);
    h2_fatima_energy_energy_promptflash_cut_long = new TH2F(TString("h2_fatima_energy_energy_promptflash_cut_long_frs_gate_"+frsgate->GetName()),TString(Form("Fatima energy vs energy, |t(det1)-t(det2)|<%i ns, prompt flash cut out, long lifetime, gated FRS on ",fatima_coincidence_gate)+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
    h2_fatima_energy_energy_promptflash_cut_long->GetXaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_energy_promptflash_cut_long->GetYaxis()->SetTitle("energy (keV)");
    h2_fatima_energy_energy_promptflash_cut_long->Draw("COLZ");
    c_fatima_energy_energy_promptflash_cut_long->cd(0);
    dir_fatima->Append(c_fatima_energy_energy_promptflash_cut_long);
    

    
    c_fatima_sci41_hits = new TCanvas(TString("c_fatima_sci41_hits_frs_gate_"+frsgate->GetName()),TString("Hits in sci41, long lifetime, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_sci41_hits = new TH1F(TString("h1_fatima_sci41_hits_frs_gate_"+frsgate->GetName()),TString("Hits in sci41, long lifetime, gated FRS on "+frsgate->GetName()),10,0,10);
    h1_fatima_sci41_hits->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_sci41_hits->Draw("COLZ");
    c_fatima_sci41_hits->cd(0);
    dir_fatima->Append(c_fatima_sci41_hits);

    c_fatima_sci41_energy = new TCanvas(TString("c_fatima_sci41_energy_frs_gate_"+frsgate->GetName()),TString("Energy in sci41, gated FRS on "+frsgate->GetName()),650,350);
    h1_fatima_sci41_energy = new TH1F(TString("h1_fatima_sci41_energy_frs_gate_"+frsgate->GetName()),TString("Energy in sci41, gated FRS on "+frsgate->GetName()),3000,0,1500);
    h1_fatima_sci41_energy->GetXaxis()->SetTitle("energy (keV)");
    h1_fatima_sci41_energy->Draw("COLZ");
    c_fatima_sci41_energy->cd(0);
    dir_fatima->Append(c_fatima_sci41_energy);
    

    //energy-gated spectra:
    dir_energy_gated = new TDirectory*[gamma_energies_of_interest.size()];

    c_fatima_tsci41_energy_gated = new TCanvas*[gamma_energies_of_interest.size()];
    h1_fatima_tsci41_energy_gated = new TH1F*[gamma_energies_of_interest.size()];
        
    c_fatima_energy_promptflash_cut_energy_gated = new TCanvas*[gamma_energies_of_interest.size()];
    h1_fatima_energy_promptflash_cut_energy_gated = new TH1F*[gamma_energies_of_interest.size()];
        
    //long:
    c_fatima_energy_promptflash_cut_long_energy_gated = new TCanvas*[gamma_energies_of_interest.size()];
    h1_fatima_energy_promptflash_cut_long_energy_gated = new TH1F*[gamma_energies_of_interest.size()];

    c_fatima_twr_sci41_energy_gated = new TCanvas*[gamma_energies_of_interest.size()];
    h1_fatima_twr_sci41_energy_gated = new TH1F*[gamma_energies_of_interest.size()];

    c_fatima_energy_gated_energy_vs_dt_prompt_flash_cut = new TCanvas*[gamma_energies_of_interest.size()];
    h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut = new TH2F*[gamma_energies_of_interest.size()];
    
    c_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long = new TCanvas*[gamma_energies_of_interest.size()];
    h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long = new TH2F*[gamma_energies_of_interest.size()];
        
    
    for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++)
    {
        dirname = "Energy gated coincidence spectra, Eg = " + (int)gamma_energies_of_interest.at(idx_gamma_gate);
        dir_energy_gated[idx_gamma_gate] = dir_fatima->mkdir(dirname);
        dir_energy_gated[idx_gamma_gate]->cd();

        c_fatima_tsci41_energy_gated[idx_gamma_gate] = new TCanvas(TString(Form("c_fatima_tsci41_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("t(det) - t(sci41) gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()));
        h1_fatima_tsci41_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_fatima_tsci41_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("t(det) - t(sci41) gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),10000,-2e3,stop_short_lifetime_collection);
        h1_fatima_tsci41_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("time (ns)");
        h1_fatima_tsci41_energy_gated[idx_gamma_gate]->Draw();
        c_fatima_tsci41_energy_gated[idx_gamma_gate]->cd(0);
        dir_energy_gated[idx_gamma_gate]->Append(c_fatima_tsci41_energy_gated[idx_gamma_gate]);

        c_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate] = new TCanvas(TString(Form("c_fatima_energy_promptflash_cut_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gammas gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()));
        h1_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_fatima_energy_promptflash_cut_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gammas gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("Energy (keV)");
        h1_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate]->Draw();
        c_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate]->cd(0);
        dir_energy_gated[idx_gamma_gate]->Append(c_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate]);

        c_fatima_twr_sci41_energy_gated[idx_gamma_gate] = new TCanvas(TString(Form("c_fatima_twr_sci41_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("WR t(det) - t(sci41) gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()));
        h1_fatima_twr_sci41_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_fatima_twr_sci41_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("WR t(det) - t(sci41) gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),10000,long_lifetime_binlow,long_lifetime_binhigh);
        h1_fatima_twr_sci41_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("time (ns)");
        h1_fatima_twr_sci41_energy_gated[idx_gamma_gate]->Draw();
        c_fatima_twr_sci41_energy_gated[idx_gamma_gate]->cd(0);
        dir_energy_gated[idx_gamma_gate]->Append(c_fatima_twr_sci41_energy_gated[idx_gamma_gate]);

        c_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate] = new TCanvas(TString(Form("c_fatima_energy_promptflash_cut_long_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gammas gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()));
        h1_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate] = new TH1F(TString(Form("h1_fatima_energy_promptflash_cut_long_energy_gated_%i_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gammas gated on E = %i keV, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate))+frsgate->GetName()),fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h1_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]->GetXaxis()->SetTitle("Energy (keV)");
        h1_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]->Draw();
        c_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]->cd(0);
        dir_energy_gated[idx_gamma_gate]->Append(c_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]);

        c_fatima_energy_gated_energy_vs_dt_prompt_flash_cut [idx_gamma_gate] = new TCanvas(TString(Form("c_fatima_energy_gated_%i_energy_vs_dt_prompt_flash_cut_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gamma with start Ey1 = %i keV, Ey2 vs t(Ey1)-t(Ey2), short isomer,  gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName());
        h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut[idx_gamma_gate] = new TH2F(TString(Form("h2_fatima_energy_gated_%i_energy_vs_dt_prompt_flash_cut_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gamma with start Ey1 = %i keV, Ey2 vs t(Ey1)-t(Ey2), short isomer,  gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),ftime_coincidence_nbins,ftime_coincidence_low,ftime_coincidence_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut[idx_gamma_gate]->GetXaxis()->SetTitle("time between gammas (ns)");
        h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut[idx_gamma_gate]->GetYaxis()->SetTitle("energy of start gamma (keV)");
        h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut[idx_gamma_gate]->Draw("COLZ");
        c_fatima_energy_gated_energy_vs_dt_prompt_flash_cut[idx_gamma_gate]->cd(0);
        dir_energy_gated[idx_gamma_gate]->Append(c_fatima_energy_gated_energy_vs_dt_prompt_flash_cut[idx_gamma_gate]);

        c_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long[idx_gamma_gate] = new TCanvas(TString(Form("c_fatima_energy_gated_%i_energy_vs_dt_prompt_flash_cut_long_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gamma with start Ey1 = %i keV, Ey2 vs t(Ey1)-t(Ey2), long isomer, gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName());
        h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long[idx_gamma_gate] = new TH2F(TString(Form("h2_fatima_energy_gated_%i_energy_vs_dt_prompt_flash_cut_long_frs_gate_",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),TString(Form("Coincident gamma with start Ey1 = %i keV, Ey2 vs t(Ey1)-t(Ey2), long isomer , gated FRS on ",(int)gamma_energies_of_interest.at(idx_gamma_gate)))+frsgate->GetName(),ftime_coincidence_nbins,ftime_coincidence_low,ftime_coincidence_high,fenergy_nbins,fenergy_bin_low,fenergy_bin_high);
        h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long[idx_gamma_gate]->GetXaxis()->SetTitle("time between gammas (ns)");
        h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long[idx_gamma_gate]->GetYaxis()->SetTitle("energy of start gamma (keV)");
        h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long[idx_gamma_gate]->Draw("COLZ");
        c_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long[idx_gamma_gate]->cd(0);
        dir_energy_gated[idx_gamma_gate]->Append(c_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long[idx_gamma_gate]);


    }
    

    
    return kSUCCESS;
}


int FrsFatimaCorrelations::CountMultiplicity(TClonesArray* fHitFatimaArray, int idx){
    
    int multiplicity = 1;

    FatimaTwinpeaksCalData* hit1 = (FatimaTwinpeaksCalData*)fHitFatimaArray->At(idx);

    int detector_id1 = hit1->Get_detector_id();
    double energy1 = hit1->Get_energy();
    double time1 = hit1->Get_fast_lead_time();
    int64_t epoch1 = hit1->Get_fast_lead_epoch();

    for (int i = 0; i<fHitFatimaArray->GetEntries(); i++){
        if (i == idx) continue;
        FatimaTwinpeaksCalData* hit2 = (FatimaTwinpeaksCalData*)fHitFatimaArray->At(i);
        int detector_id2 = hit2->Get_detector_id();
        double energy2 = hit2->Get_energy();
        double time2 = hit2->Get_fast_lead_time();
        int64_t epoch2 = hit2->Get_fast_lead_epoch();

        if (fatima_configuration->IsDetectorAuxilliary(detector_id2) == true ) continue;

        double dt = (epoch2 - epoch1) + (time2 - time1) - fatima_configuration->GetTimeshiftCoefficient(detector_id1,detector_id2);

        if (dt*dt < fatima_coincidence_gate*fatima_coincidence_gate){
            multiplicity ++;
        }
    }

    return multiplicity;
}

int FrsFatimaCorrelations::CountMultiplicityOutsidePromptFlashSCI41(TClonesArray* fHitFatimaArray, int idx, double time_sci41, int64_t epoch_sci41){
    // assumed hit at idx is outside prompt flash already checked.
    int multiplicity = 1;

    FatimaTwinpeaksCalData* hit1 = (FatimaTwinpeaksCalData*)fHitFatimaArray->At(idx);

    int detector_id1 = hit1->Get_detector_id();
    double energy1 = hit1->Get_energy();
    double time1 = hit1->Get_fast_lead_time();
    int64_t epoch1 = hit1->Get_fast_lead_epoch();

    for (int i = 0; i<fHitFatimaArray->GetEntries(); i++){
        if (i == idx) continue;
        FatimaTwinpeaksCalData* hit2 = (FatimaTwinpeaksCalData*)fHitFatimaArray->At(i);
        int detector_id2 = hit2->Get_detector_id();
        double energy2 = hit2->Get_energy();
        double time2 = hit2->Get_fast_lead_time();
        int64_t epoch2 = hit2->Get_fast_lead_epoch();

        if (fatima_configuration->IsDetectorAuxilliary(detector_id2) == true ) continue;
        
        double dt_sci41 = (double)(epoch2 - epoch_sci41) + time2 - time_sci41 - fatima_configuration->GetTimeshiftCoefficient(1,detector_id2);

        if (fatima_configuration->IsInsidePromptFlashCut(dt_sci41,energy2) == true) continue;
        if (!(dt_sci41 < stop_short_lifetime_collection && dt_sci41 > - 300)) continue;

        double dt = (epoch2 - epoch1) + (time2 - time1) - fatima_configuration->GetTimeshiftCoefficient(detector_id1,detector_id2);

        if (dt*dt < fatima_coincidence_gate*fatima_coincidence_gate){
            multiplicity ++;
        }
    }

    return multiplicity;
}

int FrsFatimaCorrelations::CountMultiplicityOutsidePromptFlashWR(TClonesArray* fHitFatimaArray, int idx, int64_t wr_t_last_hit_frs){
    // assumed hit at idx is outside prompt flash already checked.
    int multiplicity = 1;

    FatimaTwinpeaksCalData* hit1 = (FatimaTwinpeaksCalData*)fHitFatimaArray->At(idx);

    int detector_id1 = hit1->Get_detector_id();
    double energy1 = hit1->Get_energy();
    double time1 = hit1->Get_fast_lead_time();
    int64_t epoch1 = hit1->Get_fast_lead_epoch();

    for (int i = 0; i<fHitFatimaArray->GetEntries(); i++){
        if (i == idx) continue;
        FatimaTwinpeaksCalData* hit2 = (FatimaTwinpeaksCalData*)fHitFatimaArray->At(i);
        int detector_id2 = hit2->Get_detector_id();
        double energy2 = hit2->Get_energy();
        double time2 = hit2->Get_fast_lead_time();
        int64_t epoch2 = hit2->Get_fast_lead_epoch();
        int64_t abs_time2 = (int64_t) hit2->Get_absolute_event_time();

        if (fatima_configuration->IsDetectorAuxilliary(detector_id2) == true ) continue;
        
        if (abs_time2 - (int64_t)wr_t_last_hit_frs - fatima_configuration->GetTimeshiftCoefficient(1,detector_id2) < start_long_lifetime_collection) continue;
        if (abs_time2 - (int64_t)wr_t_last_hit_frs - fatima_configuration->GetTimeshiftCoefficient(1,detector_id2) < stop_long_lifetime_collection) continue; 

        double dt = (epoch2 - epoch1) + (time2 - time1) - fatima_configuration->GetTimeshiftCoefficient(detector_id1,detector_id2);

        if (dt*dt < fatima_coincidence_gate*fatima_coincidence_gate){
            multiplicity ++;
        }
    }

    return multiplicity;
}

void FrsFatimaCorrelations::Exec(Option_t* option)
{

    if (hitArrayFrs->size() == 0 || hitArrayFrs->size() > 1) return;
    positive_PID = false;
    auto const & frshit = hitArrayFrs->at(0);

    int64_t wr_t = frshit.Get_wr_t();
    if(wr_t_first_frs_hit == 0) wr_t_first_frs_hit = wr_t;
    double ID_x2 = frshit.Get_ID_x2();
    double ID_y2 = frshit.Get_ID_y2();
    double ID_x4 = frshit.Get_ID_x4();
    double ID_AoQ = frshit.Get_ID_AoQ_corr();
    double ID_z = frshit.Get_ID_z();
    double ID_z2 = frshit.Get_ID_z2();
    double ID_dEdeg = frshit.Get_ID_dEdeg();
    double ID_sci42E = frshit.Get_sci_e(3);

    // this must pass all gates given to FrsGate:
    positive_PID = frsgate->PassedGate(ID_z, ID_z2, ID_x2, ID_x4, ID_AoQ, ID_dEdeg, ID_sci42E);
    if (positive_PID)
    {
        wr_t_last_frs_hit = wr_t;
        frs_rate_implanted ++;
        frs_total_implanted ++;

        h2_frs_Z_vs_AoQ_gated->Fill(ID_AoQ,ID_z);
        h2_frs_Z_vs_Z2_gated->Fill(ID_z,ID_z2);
        h2_frs_x2_vs_AoQ_gated->Fill(ID_AoQ,ID_x2);
        h2_frs_x4_vs_AoQ_gated->Fill(ID_AoQ,ID_x4);
        h2_frs_Z_vs_dEdeg_gated->Fill(ID_dEdeg,ID_z);
        h2_frs_Z_vs_sci42E_gated->Fill(ID_sci42E,ID_z);

        if (wr_t_last_frs_hit - frs_rate_time > 60e9)
        {
            g_frs_rate->AddPoint((wr_t_last_frs_hit - wr_t_first_frs_hit)/1000000000, frs_rate_implanted/60.0);
            g_frs_total->AddPoint((wr_t_last_frs_hit - wr_t_first_frs_hit)/1000000000, frs_total_implanted);
            frs_rate_time = wr_t_last_frs_hit;
            frs_rate_implanted = 0;
        }
    }else{
        //wr_t_last_frs_hit = 0;
    }

    if (fHitFatima && fHitFatima->GetEntriesFast() > 0)
    {
        
        
        Int_t nHits = fHitFatima->GetEntriesFast();
        
        
        bool sci41_seen = false; // off-spill raw spectra
        int sci41_hit_idx = -1; // sci41's hit index, for getting the time
        int sci41_hits = 0;
        int detector_id_sci41 = 0;
        double energy_sci41 = 0;
        double time_sci41 = 0;
        int64_t epoch_sci41 = 0;
        int64_t absolute_time_sci41 = 0;
        int64_t wr_sci41 = 0;

        int sci41r_hits = 0;
        int frs_accept_hit = 0;
        
        //find sci41:
        for (Int_t ihit = 0; ihit < nHits; ihit++){ // find the sci41 hit if it is there.
    
            FatimaTwinpeaksCalData* hit1 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit);
            if (!hit1) continue;
            int detector_id1 = hit1->Get_detector_id();
            if (detector_id1 == fatima_configuration->SC41L() /*|| detector_id1 == fatima_configuration->SC41R()*/) {
                
                if (epoch_sci41 == 0){ // keep the first hit
                    detector_id_sci41 = hit1->Get_detector_id();
                    energy_sci41 = hit1->Get_energy();
                    time_sci41 = hit1->Get_fast_lead_time();
                    epoch_sci41 = hit1->Get_fast_lead_epoch();
                    absolute_time_sci41 = (int64_t)hit1->Get_absolute_event_time();
                    wr_sci41 = hit1->Get_wr_t();
                    sci41_hit_idx = ihit;
                }


                sci41_seen = true;
                sci41_hits++;
            }else if (detector_id1 == fatima_configuration->SC41R()){
                sci41r_hits++;
            }else if (detector_id1 == fatima_configuration->FRS_accept()){
                frs_accept_hit++;
            }
        }

        h1_fatima_sci41_hits->Fill(sci41_hits);
        
        if (sci41_hits != 1) return; // only single hit sci41l
        if (positive_PID && TMath::Abs(wr_t_last_frs_hit-absolute_time_sci41-100) > 100) return; // gate the sci41 hit with the WR on the FRS
        if (frs_accept_hit != 1) return; // remove missing frs accepcted trigger (equivalent to positive PID)
        
        h1_fatima_sci41_energy->Fill(energy_sci41);

        if (energy_sci41 > 1020) return; // veto sci41l pile-up
        if (sci41r_hits != sci41_hits) return; // veto second hit in sci41r

        
        // Spectra with respect to SCI41 - 'short' isomers
        if (nHits >= 2 && sci41_seen && positive_PID){
            for (int ihit2 = 0; ihit2 < nHits; ihit2 ++){
                if (ihit2 == sci41_hit_idx) continue;
                FatimaTwinpeaksCalData* hit2 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit2);
                if (!hit2) continue;
                int detector_id1 = hit2->Get_detector_id();
                double energy1 = hit2->Get_energy();
                double time1 = hit2->Get_fast_lead_time();
                int64_t epoch1 = hit2->Get_fast_lead_epoch();
                int64_t absolute_time1 = (int64_t)hit2->Get_absolute_event_time();
                int64_t wr_t1 = (int64_t)hit2->Get_wr_t();
                

                if (fatima_configuration->IsDetectorAuxilliary(detector_id1) == true) continue;

                int multiplicity1 = CountMultiplicityOutsidePromptFlashSCI41(fHitFatima, ihit2, time_sci41, epoch_sci41);

                double timediff1 = (double)(epoch1-epoch_sci41) + time1 - time_sci41 - fatima_configuration->GetTimeshiftCoefficient(1,detector_id1);
                
                h2_fatima_energy_vs_tsci41->Fill(timediff1 ,energy1);
                h2_fatima_multiplicity_vs_tsci41->Fill(timediff1, multiplicity1);


                if (multiplicity1 == 1){
                    h2_fatima_energy_vs_sci41_mult1->Fill(timediff1, energy1);
                }else if (multiplicity1 == 2){
                    h2_fatima_energy_vs_sci41_mult2->Fill(timediff1, energy1);
                }else if (multiplicity1 == 3){
                    h2_fatima_energy_vs_sci41_mult3->Fill(timediff1, energy1);
                }else if (multiplicity1 >= 4){
                    h2_fatima_energy_vs_sci41_mult4p->Fill(timediff1, energy1);
                }

                //after this test, the prompt flash is cut out.
                if ((fatima_configuration->IsInsidePromptFlashCut(timediff1 ,energy1)==true) ) continue;

                
                if (!(timediff1 < stop_short_lifetime_collection && timediff1 > - 300)) continue;

                
                h1_fatima_energy_promptflash_cut->Fill(energy1);


                if (multiplicity1 == 1){
                    h1_fatima_energy_promptflash_cut_mult1->Fill(energy1);

                }else if (multiplicity1 == 2){
                    h1_fatima_energy_promptflash_cut_mult2->Fill(energy1);

                }else if (multiplicity1 == 3){
                    h1_fatima_energy_promptflash_cut_mult3->Fill(energy1);

                }else if (multiplicity1 >= 4){
                    h1_fatima_energy_promptflash_cut_mult4p->Fill(energy1);
                }

                for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++){
                    if (!(TMath::Abs(energy1 - gamma_energies_of_interest.at(idx_gamma_gate))<gate_width_gamma_energies_of_interest.at(idx_gamma_gate))) continue;
                    
                    //now energy1 fulfills the energy requirement and is outside prompt flash
                    h1_fatima_tsci41_energy_gated[idx_gamma_gate]->Fill(timediff1);
                }
        
                
                if (nHits >= 3){
                
                for (int ihit3 = 0; ihit3<nHits; ihit3 ++){
                    if (ihit3 == sci41_hit_idx) continue;
                    if (ihit3 == ihit2) continue;

                    FatimaTwinpeaksCalData* hit3 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit3);
                    if (!hit3) continue;
                    
                    int detector_id2 = hit3->Get_detector_id();
                    if (detector_id1 == detector_id2) continue; //this is likely a good veto before the add-back is done ... 
                    
                    double energy2 = hit3->Get_energy();
                    double time2 = hit3->Get_fast_lead_time();
                    int64_t epoch2 = hit3->Get_fast_lead_epoch();

                    if (fatima_configuration->IsDetectorAuxilliary(detector_id2) == true) continue;

                    double timediff2 = (double)(epoch2 - epoch_sci41) + time2 - time_sci41 - fatima_configuration->GetTimeshiftCoefficient(1,detector_id2);
                    
                    if ((fatima_configuration->IsInsidePromptFlashCut(timediff2, energy2)==true)) continue;
                    if (!(timediff2 < stop_short_lifetime_collection && timediff2 > - 300)) continue;

                    if (ihit3 > ihit2 && (TMath::Abs((double)(epoch2-epoch1) + time2 - time1 - fatima_configuration->GetTimeshiftCoefficient(detector_id1,detector_id2)) < fatima_coincidence_gate)) h2_fatima_energy_energy_promptflash_cut->Fill(energy1,energy2); // avoid double filling ... 


                    for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++){
                        if (!(TMath::Abs(energy1 - gamma_energies_of_interest.at(idx_gamma_gate))<gate_width_gamma_energies_of_interest.at(idx_gamma_gate))) continue;
                            // energy1 and energy2 are both in coincidence and outside the promptflash here:
                            if (TMath::Abs((double)(epoch2-epoch1) + time2-time1+fatima_configuration->GetTimeshiftCoefficient(detector_id1,detector_id2)) < fatima_coincidence_gate) h1_fatima_energy_promptflash_cut_energy_gated[idx_gamma_gate]->Fill(energy2);
                            
                            h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut[idx_gamma_gate]->Fill((double)(epoch1-epoch2) + time1 - time2 - fatima_configuration->GetTimeshiftCoefficient(detector_id2,detector_id1), energy2);
                        }
                    }
                }
            }
        }

        

        if (nHits >= 1 && wr_t_last_frs_hit != 0){
        //long isomer
        for (int ihit1 = 0; ihit1 < nHits; ihit1 ++){

            FatimaTwinpeaksCalData* hit_long1 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit1);
            if (!hit_long1) continue;
            int detector_id_long = hit_long1->Get_detector_id();
            double energy_long = hit_long1->Get_energy();
            double time_long = hit_long1->Get_fast_lead_time();
            int64_t epoch_long = hit_long1->Get_fast_lead_epoch();
            int64_t fat_wr_long = (int64_t)hit_long1->Get_absolute_event_time();

            if (fatima_configuration->IsDetectorAuxilliary(detector_id_long)==true) continue;


            int multiplicity_long1 = CountMultiplicityOutsidePromptFlashWR(fHitFatima, ihit1, wr_t_last_frs_hit);
            
            h2_fatima_energy_vs_sci41_wr_long->Fill(fat_wr_long - (int64_t)wr_t_last_frs_hit - fatima_configuration->GetTimeshiftCoefficient(1,detector_id_long), energy_long);
            h2_fatima_multiplicity_vs_sci41_wr_long->Fill(fat_wr_long - (int64_t)wr_t_last_frs_hit - fatima_configuration->GetTimeshiftCoefficient(1,detector_id_long), multiplicity_long1);
            
            
            if (multiplicity_long1 == 1){
                h2_fatima_energy_vs_sci41_wr_long_mult1->Fill(fat_wr_long - (int64_t)wr_t_last_frs_hit - fatima_configuration->GetTimeshiftCoefficient(1,detector_id_long), energy_long);
            }else if (multiplicity_long1 == 2){
                h2_fatima_energy_vs_sci41_wr_long_mult2->Fill(fat_wr_long - (int64_t)wr_t_last_frs_hit - fatima_configuration->GetTimeshiftCoefficient(1,detector_id_long), energy_long);
            }else if (multiplicity_long1 == 3){
                h2_fatima_energy_vs_sci41_wr_long_mult3->Fill(fat_wr_long - (int64_t)wr_t_last_frs_hit - fatima_configuration->GetTimeshiftCoefficient(1,detector_id_long), energy_long);
            }else if (multiplicity_long1 >= 4){
                h2_fatima_energy_vs_sci41_wr_long_mult4p->Fill(fat_wr_long - (int64_t)wr_t_last_frs_hit - fatima_configuration->GetTimeshiftCoefficient(1,detector_id_long), energy_long);
            }
            
            
            // cut the prompt flash on the whiterabbit, roughly:
            if (fat_wr_long - (int64_t)wr_t_last_frs_hit - fatima_configuration->GetTimeshiftCoefficient(1,detector_id_long) < start_long_lifetime_collection) continue;

            for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++)
            {
                if (!(TMath::Abs(energy_long - gamma_energies_of_interest.at(idx_gamma_gate))<gate_width_gamma_energies_of_interest.at(idx_gamma_gate))) continue;
                //now energy1 fulfills the energy requirement and is outside prompt flash
                    
                h1_fatima_twr_sci41_energy_gated[idx_gamma_gate]->Fill(fat_wr_long-(int64_t)wr_t_last_frs_hit - fatima_configuration->GetTimeshiftCoefficient(1,detector_id_long));
            }
            
            if (fat_wr_long - (int64_t)wr_t_last_frs_hit - fatima_configuration->GetTimeshiftCoefficient(1,detector_id_long) < stop_long_lifetime_collection) 
            {
                h1_fatima_energy_promptflash_cut_long->Fill(energy_long);

                if (multiplicity_long1 == 1){
                    h1_fatima_energy_promptflash_cut_long_mult1->Fill(energy_long);

                }else if (multiplicity_long1 == 2){
                    h1_fatima_energy_promptflash_cut_long_mult2->Fill(energy_long);

                }else if (multiplicity_long1 == 3){
                    h1_fatima_energy_promptflash_cut_long_mult3->Fill(energy_long);

                }else if (multiplicity_long1 >= 4){
                    h1_fatima_energy_promptflash_cut_long_mult4p->Fill(energy_long);
                }

                        
                if (nHits >= 2)
                {
                
                bool hit1_already_written = false;
                
                for (int ihit2 = 0; ihit2<nHits; ihit2 ++){
                    FatimaTwinpeaksCalData* hit_long2 = (FatimaTwinpeaksCalData*)fHitFatima->At(ihit2);
                    if (!hit_long2) continue;
                    if (ihit1 == ihit2) continue;
                    int detector_id_long2 = hit_long2->Get_detector_id();
                    double energy_long2 = hit_long2->Get_energy();
                    double time_long2 = hit_long2->Get_fast_lead_time();
                    int64_t epoch_long2 = hit_long2->Get_fast_lead_epoch();
                    int64_t fat_wr_long2 = (int64_t)hit_long2->Get_absolute_event_time();


                    if (fatima_configuration->IsDetectorAuxilliary(detector_id_long2) == true) continue;
                    
                    if (fat_wr_long2 - (int64_t)wr_t_last_frs_hit - fatima_configuration->GetTimeshiftCoefficient(1,detector_id_long2) < start_long_lifetime_collection) continue;
                    if (fat_wr_long2 - (int64_t)wr_t_last_frs_hit - fatima_configuration->GetTimeshiftCoefficient(1,detector_id_long2) > stop_long_lifetime_collection) continue;
                    
                    
                    // check coincidence, this should also make it so that the second hit is outside the prompt flash as well...:

                    //avoid double filling:
                    if (ihit2>ihit1 && (TMath::Abs(time_long2 - time_long - fatima_configuration->GetTimeshiftCoefficient(detector_id_long,detector_id_long2)) < fatima_coincidence_gate)) {
                        h2_fatima_energy_energy_promptflash_cut_long->Fill(energy_long,energy_long2);                        
                    }
                    
                    for (int idx_gamma_gate = 0; idx_gamma_gate < gamma_energies_of_interest.size(); idx_gamma_gate++)
                    {
                        if (!(TMath::Abs(energy_long - gamma_energies_of_interest.at(idx_gamma_gate))<gate_width_gamma_energies_of_interest.at(idx_gamma_gate))) continue;
                        //now energy1 fulfills the energy requirement and is outside prompt flash
                        // energy1 and energy2 are both in coincidence and outside the promptflash here:
                        if ((TMath::Abs(time_long2 - time_long - fatima_configuration->GetTimeshiftCoefficient(detector_id_long,detector_id_long2)) < fatima_coincidence_gate)) h1_fatima_energy_promptflash_cut_long_energy_gated[idx_gamma_gate]->Fill(energy_long2);

                        h2_fatima_energy_gated_energy_vs_dt_prompt_flash_cut_long[idx_gamma_gate]->Fill((double)(epoch_long - epoch_long2) + time_long - time_long2 - fatima_configuration->GetTimeshiftCoefficient(detector_id_long2, detector_id_long), energy_long2);
                    }
                    }
                }   
            }
        }
        }
    }

    fNEvents += 1;
}

void FrsFatimaCorrelations::FinishEvent()
{
    if (fHitFatima)
    {
        fHitFatima->Clear();
    }
}

void FrsFatimaCorrelations::FinishTask()
{
    if (fNEvents == 0)
    {
        c4LOG(warning, "No events processed, no histograms written.");
        return;
    }
    if (fHitFatima)
    {
        dir_fatima->Write();
        c4LOG(info, "FATIMA histograms written to file.");
    }
}

ClassImp(FrsFatimaCorrelations)
