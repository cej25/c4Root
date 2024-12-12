// FairRoot
#include "FairLogger.h"
#include "FairRootManager.h"
#include "FairRunAna.h"
#include "FairRunOnline.h"
#include "FairRuntimeDb.h"

// c4
#include "FrsRawSpectra.h"
#include "EventHeader.h"
#include "c4Logger.h"
#include "AnalysisTools.h"

// ROOT
#include "TCanvas.h"
#include "TClonesArray.h"
#include "THttpServer.h"
#include "TMath.h"
#include "TRandom.h"
#include <vector>

FrsRawSpectra::FrsRawSpectra()
    :   FrsRawSpectra("FrsRawSpectra", 1)
{
}

FrsRawSpectra::FrsRawSpectra(const TString& name, Int_t iVerbose)
    :   FairTask(name, iVerbose)
    ,   fNEvents(0)
    ,   header(nullptr) 
    ,   sciArray(nullptr)
    ,   musicArray(nullptr)
    ,   tpcArray(nullptr)
{
}

FrsRawSpectra::~FrsRawSpectra()
{
    c4LOG(info, "");
}

InitStatus FrsRawSpectra::Init()
{
    FairRootManager* mgr = FairRootManager::Instance();
    c4LOG_IF(fatal, NULL == mgr, "FairRootManager not found");

    FairRunOnline* run = FairRunOnline::Instance();
    run->GetHttpServer()->Register("", this);

    header = (EventHeader*)mgr->GetObject("EventHeader.");
    c4LOG_IF(error, !header, "Branch EventHeader. not found");

    sciArray = mgr->InitObjectAs<decltype(sciArray)>("FrsSciData");
    c4LOG_IF(fatal, !sciArray, "Branch FrsSciData not found!");
    musicArray = mgr->InitObjectAs<decltype(musicArray)>("FrsMusicData");
    c4LOG_IF(fatal, !musicArray, "Branch FrsMusicData not found!");
    tpcArray = mgr->InitObjectAs<decltype(tpcArray)>("FrsTpcData");
    c4LOG_IF(fatal, !tpcArray, "Branch FrsTpcData not found!");

    histograms = (TFolder*)mgr->GetObject("Histograms");
    
    TDirectory::TContext ctx(nullptr);

    // look for FRS directory, create it if not found
    dir_frs = (TDirectory*)mgr->GetObject("FRS");
    if (dir_frs == nullptr) 
    {
        LOG(info) << "Creating FRS Online Directory";
        dir_frs = new TDirectory("FRS Online", "FRS Online", "", 0);
        mgr->Register("FRS", "FRS Online Directory", dir_frs, false); // allow other tasks to find this
        histograms->Add(dir_frs);
    }
    
    dir_frs_raw = dir_frs->mkdir("FRS Raw Spectra");
    dir_sci = dir_frs_raw->mkdir("Scintillators");
    dir_music = dir_frs_raw->mkdir("MUSICs");
    dir_tpc = dir_frs_raw->mkdir("TPCs");

    // ::: SCI ::::: 
    dir_sci_de = dir_sci->mkdir("dE");
    dir_sci_dt = dir_sci->mkdir("dT");
    dir_sci_mhtdc = dir_sci->mkdir("MHTDC T");
    
    // TAC dE
    c_sci_de = new TCanvas("c_sci_de", "Scintillator dE spectra", 650, 350);
    c_sci_de->Divide(4, 4);
    for (int ihist = 0; ihist < 16; ihist++)
    {
        c_sci_de->cd(ihist+1);
        h1_sci_de[ihist] = MakeTH1(dir_sci_de, "F", Form("h1_sci_de_%i", ihist), Form("Scintillator dE Channel %i", ihist), 4096, 0, 4096);
        h1_sci_de[ihist]->Draw();
    }
    c_sci_de->cd(0);
    dir_sci_de->Append(c_sci_de);

    // TAC dT
    c_sci_dt = new TCanvas("c_sci_dt", "Scintillator dT spectra", 650, 350);
    c_sci_dt->Divide(4, 4);
    for (int ihist = 0; ihist < 16; ihist++)
    {
        c_sci_dt->cd(ihist+1);
        h1_sci_dt[ihist] = MakeTH1(dir_sci_dt, "F", Form("h1_sci_dt_%i", ihist), Form("Scintillator dT Channel %i", ihist), 2000, 0, 2000); // need to figure out ranges
        h1_sci_dt[ihist]->Draw();
    }
    c_sci_dt->cd(0);
    dir_sci_dt->Append(c_sci_dt);

    // MHTDC T
    c_sci_mhtdc = new TCanvas("c_sci_mhtdc", "Scintillator MHTDC T spectra", 650, 350);
    c_sci_mhtdc->Divide(4, 4);
    for (int ihist = 0; ihist < 16; ihist++)
    {
        c_sci_mhtdc->cd(ihist+1);
        h1_sci_mhtdc[ihist] = MakeTH1(dir_sci_mhtdc, "F", Form("h1_sci_mhtdc_%i", ihist), Form("Scintillator MHTDC T Channel %i", ihist), 2000, 0, 2000); // need to figure out ranges
        h1_sci_mhtdc[ihist]->Draw();
    }
    c_sci_mhtdc->cd(0);
    dir_sci_mhtdc->Append(c_sci_mhtdc);

    
    // ::: MUSIC :::::: 
    for (int j = 0; j < 2; j++)
    {
        dir_music_n[j] = dir_music->mkdir(Form("MUSIC %i", j));

        c_music_n[j] = new TCanvas(Form("c_music_%i", j), Form("MUSIC %i Anode spectra", j), 650, 350);
        c_music_n[j]->Divide(2, 4);
        for (int ihist = 0; ihist < 8; ihist++)
        {
            c_music_n[j]->cd(ihist+1);
            h1_music_anode[j][ihist] = MakeTH1(dir_music_n[j], "F", Form("h1_music_%i_anode_%i", j, ihist), Form("MUSIC %i Anode %i", j, ihist), 2000, 0, 2000); // need to figure out ranges
            h1_music_anode[j][ihist]->Draw();
        }
        c_music_n[j]->cd(0);
        dir_music_n[j]->Append(c_music_n[j]);
    }

    
    // ::: TPCs :::::
    dir_tpc_adc = dir_tpc->mkdir("ADC");
    dir_tpc_tdc = dir_tpc->mkdir("TPC");

    for (int j = 0; j < 7; j++)
    {
        dir_tpc_n_adc[j] = dir_tpc_adc->mkdir(Form("TPC %i ADCs", j));

        c_tpc_n_adc[j] = new TCanvas(Form("c_tpc_%i_adc", j), Form("TPC %i ADC Spectra", j) , 650, 350);
        c_tpc_n_adc[j]->Divide(2, 4);
        for (int ihist = 0; ihist < 8; ihist++)
        {
            c_tpc_n_adc[j]->cd(ihist+1);
            h1_tpc_adc[j][ihist] = MakeTH1(dir_tpc_n_adc[j], "F", Form("dir_tpc_%i_adc_%i", j, ihist), Form("TPC %i ADC Channel %i", j, ihist), 2000, 0, 2000);
            h1_tpc_adc[j][ihist]->Draw();
        }
        c_tpc_n_adc[j]->cd(0);
        dir_tpc_n_adc[j]->Append(c_tpc_n_adc[j]);
    }

    c_tpc_tdc = new TCanvas("c_tpc_tdc", "TPC TDC Spectra", 650, 350);
    c_tpc_tdc->Divide(8, 16); // this will obviously look insane
    for (int ihist = 0; ihist < 128; ihist++)
    {
        c_tpc_tdc->cd(ihist+1);
        h1_tpc_tdc[ihist] = MakeTH1(dir_tpc_tdc, "F", Form("h1_tpc_tdc_%i", ihist), Form("TPC TDC Channel %i", ihist), 2000, 0, 2000);
        h1_tpc_tdc[ihist]->Draw();
    }
    c_tpc_tdc->cd(0);
    dir_tpc_tdc->Append(c_tpc_tdc);




    return kSUCCESS;

}


void FrsRawSpectra::Exec(Option_t* option)
{
    

}

void FrsRawSpectra::FinishEvent()
{

}


void FrsRawSpectra::FinishTask()
{

}

ClassImp(FrsRawSpectra)
