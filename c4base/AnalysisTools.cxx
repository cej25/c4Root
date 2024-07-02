#include "AnalysisTools.h"
#include "c4Logger.h"

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
            int xbins, double xmin, double xmax, int ybins, int ymin, int ymax)
{
    dir->cd();

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
            int xbins, double xmin, double xmax, int ybins, int ymin, int ymax,
            const char* xtitle, const char* ytitle)
{
    dir->cd();

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

// SetPalette? "Z" title?