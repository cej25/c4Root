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

#include "AnalysisTools.h"
#include "c4Logger.h"
#include "TStyle.h"

// basic TH1
TH1* MakeTH1(TDirectory* dir, const char* type, const char* name, 
            const char* title, int bins, double xmin, double xmax)
{   
    dir->cd();

    TH1* h1;

    if (*type == 'I') h1 = new TH1I(name, title, bins, xmin, xmax);
    else if (*type == 'F') h1 = new TH1F(name, title, bins, xmin, xmax);
    else if (*type == 'D') h1 = new TH1D(name, title, bins, xmin, xmax);
    else h1 = new TH1I(name, title, bins, xmin, xmax);

    return h1;
}

// TH1 with axis labels
TH1* MakeTH1(TDirectory* dir, const char* type, const char* name, 
                    const char* title, int bins, double xmin, double xmax,
                    const char* xtitle)
{
    dir->cd();

    TH1* h1;
    
    if (*type == 'I') h1 = new TH1I(name, title, bins, xmin, xmax);
    else if (*type == 'F') h1 = new TH1F(name, title, bins, xmin, xmax);
    else if (*type == 'D') h1 = new TH1D(name, title, bins, xmin, xmax);
    else h1 = new TH1I(name, title, bins, xmin, xmax);
    
    h1->GetXaxis()->SetTitle(xtitle);

    return h1;
}

// TH1 with axis labels and specified colours
TH1* MakeTH1(TDirectory* dir, const char* type, const char* name, 
                    const char* title, int bins, double xmin, double xmax,
                    const char* xtitle, int fillColour, int lineColour)
{
    dir->cd();

    TH1* h1;
    
    if (*type == 'I') h1 = new TH1I(name, title, bins, xmin, xmax);
    else if (*type == 'F') h1 = new TH1F(name, title, bins, xmin, xmax);
    else if (*type == 'D') h1 = new TH1D(name, title, bins, xmin, xmax);
    else h1 = new TH1I(name, title, bins, xmin, xmax);
    
    h1->GetXaxis()->SetTitle(xtitle);
    h1->SetFillColor(fillColour);
    h1->SetLineColor(lineColour);

    return h1;
}

// basic TH2
TH2* MakeTH2(TDirectory* dir, const char* type, const char* name, const char* title, 
            int xbins, double xmin, double xmax, int ybins, double ymin, double ymax)
{
    dir->cd();
    gStyle->SetPalette(kDarkBodyRadiator);

    TH2* h2;
    
    if (*type == 'I') h2 = new TH2I(name, title, xbins, xmin, xmax, ybins, ymin, ymax);
    else if (*type == 'F') h2 = new TH2F(name, title, xbins, xmin, xmax, ybins, ymin, ymax);
    else if (*type == 'D') h2 = new TH2D(name, title, xbins, xmin, xmax, ybins, ymin, ymax);
    else h2 = new TH2I(name, title, xbins, xmin, xmax, ybins, ymin, ymax);

    h2->SetOption("COLZ"); // default for now.

    return h2;
}

// TH2 with axis titles
TH2* MakeTH2(TDirectory* dir, const char* type, const char* name, const char* title, 
            int xbins, double xmin, double xmax, int ybins, double ymin, double ymax,
            const char* xtitle, const char* ytitle)
{
    dir->cd();
    gStyle->SetPalette(kDarkBodyRadiator);

    TH2* h2;
    
    if (*type == 'I') h2 = new TH2I(name, title, xbins, xmin, xmax, ybins, ymin, ymax);
    else if (*type == 'F') h2 = new TH2F(name, title, xbins, xmin, xmax, ybins, ymin, ymax);
    else if (*type == 'D') h2 = new TH2D(name, title, xbins, xmin, xmax, ybins, ymin, ymax);
    else h2 = new TH2I(name, title, xbins, xmin, xmax, ybins, ymin, ymax);

    h2->GetXaxis()->SetTitle(xtitle);
    h2->GetYaxis()->SetTitle(ytitle);
    h2->SetOption("COLZ"); // default for now.
    
    return h2;
}

TH3* MakeTH3(TDirectory* dir, const char* type, const char* name, const char* title, 
            int xbins, double xmin, double xmax, int ybins, double ymin, double ymax, 
            int zbins, double zmin, double zmax)
{
    dir->cd();
    gStyle->SetPalette(kDarkBodyRadiator);

    TH3* h3;
    
    if (*type == 'I') h3 = new TH3I(name, title, xbins, xmin, xmax, ybins, ymin, ymax, zbins, zmin, zmax);
    else if (*type == 'F') h3 = new TH3F(name, title, xbins, xmin, xmax, ybins, ymin, ymax, zbins, zmin, zmax);
    else if (*type == 'D') h3 = new TH3D(name, title, xbins, xmin, xmax, ybins, ymin, ymax, zbins, zmin, zmax);
    else h3 = new TH3I(name, title, xbins, xmin, xmax, ybins, ymin, ymax, zbins, zmin, zmax);

    h3->SetOption("COLZ"); // default for now.

    return h3;
}




void ResetHistogramsInDirectory(TDirectory* dir) {
    if (!dir) return;

    TList* histList = dir->GetList();
    if (!histList) {
        c4LOG(error, "Failed to get list of histograms from directory.");
        return;
    }

    TIter next(histList);
    TObject* obj;

    while ((obj = next())) {
        if (obj->InheritsFrom(TDirectory::Class())) {
            // Recursively process subdirectories
            TDirectory* subdir = dynamic_cast<TDirectory*>(obj);
            if (subdir) {
                ResetHistogramsInDirectory(subdir);
            }
        } else if (obj->InheritsFrom(TH1::Class())) {
            // Reset histograms
            TH1* hist = dynamic_cast<TH1*>(obj);
            if (hist) {
                std::cout << "Resetting histogram: " << hist->GetName() << std::endl;
                hist->Reset();
            }
        }
    }
}

/*
TGraph* MakeTGraph()
{
    // some option
    // I think TGraphs have to be appended.
}
*/

enum c4Color 
{
    kNapoli,
};
