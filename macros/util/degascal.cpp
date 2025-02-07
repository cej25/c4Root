// Macro for calibration of germanium detectors with DEGAS

#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <tuple>

#include "TCanvas.h"
#include "TMath.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TEnv.h"
#include "TKey.h"
#include "TLine.h"
#include "TSpectrum.h"
#include "TVirtualFitter.h"
#include "Math/Functor.h"
#include "Minuit2/Minuit2Minimizer.h"

using namespace std;

// Declarations

vector<double> defreturn;
vector <vector<double> > defreturn2;
double frange = 50;
double resolution = 1; // TSpectrum resolution
double thresholdCo = 0.8; // TSpectrum Max Peak to Peak ratio - between 0 and 1, lower means able to find smaller peaks
double thresholdEu = 0.7; // TSpectrum Max Peak to Peak ratio - between 0 and 1, lower means able to find smaller peaks
double thresholdBa = 0.7; // TSpectrum Max Peak to Peak ratio - between 0 and 1, lower means able to find smaller peaks
double range[2] = {0, 3000};
TCanvas* ca;
TCanvas* ca2;
TCanvas* ca3;
TCanvas* ca4;

bool draw = false;

// Raw peak data

vector<double> CoPeaks = {1173.2, 1332.5};
vector<double> BaPeaks = {80.998, 276.399, 302.851, 356.013, 383.849};
vector<double> EuPeaks = {121.78, 244.70, 344.28, 411.12, 443.96, /* 563.99,*/ 586.26, /* 678.00,*/ 688.67, 778.90, 867.37, 964.08, 1085.9, 1112.1, 1408.0};

// Calibration files - change this to read different files 
// There is a hard declaration of the the TH1 name like "h1_germanium_energy_X_Y" where X and Y are the cluster and crystal number at various places in the code  

char* fileCo = (char*)"60Co_0025keV_S100.root";
char* fileEu = (char*)"152Eu_0025keV_S100.root";
char* fileBa = (char*)"133Ba_0025keV_S100.root";

TFile *f_fitEu = new TFile("FitSpecEu.root", "recreate"); //output

// Fitting functions declarations

Double_t fgammagaussbg(Double_t *x, Double_t *par);
Double_t fgammabg(Double_t *x, Double_t *par);
Double_t fgammastep(Double_t *x, Double_t *par);
Double_t fgammagaus(Double_t *x, Double_t *par);
Double_t fgammagausnostep(Double_t *x, Double_t *par);
Double_t flinear(Double_t *x, Double_t *par);

// Fitting procedure declarations

vector<double> fitCo(TH1F* h, bool bg = true, bool draw = false);
vector<double> fitCo2(TH1F* h, vector< vector<double> > &CoPar, bool bg = true, bool draw = false);
vector< vector<double> > fitCopeak(TH1F* h, vector< vector<double> > &peaks, bool bg = true, bool draw = false);
vector<double> fitCoBa(TH1F* h, double rough, vector< vector<double> > CoPar, bool bg = true, bool draw = false);
vector< vector<double> > fitCoBa2(TH1F* h, double rough, vector< vector<double> > CoPar, bool bg = true, bool draw = false);
vector<vector<double> > fitEu(TH1F* h, double rough, bool bg = true, bool draw = false);


// Range setting for fitting procedure

void SetRange(double low, double hig){
  range[0] = low;
  range[1] = hig;
}

//////////////////////////////////////////
//          Fitting Procedures          //
//////////////////////////////////////////

// Fitting procedure function for 60Co

vector<double> fitCo(TH1F* h, bool bg, bool draw) {
    defreturn.push_back(-1);
    h->GetXaxis()->SetRangeUser(range[0], range[1]);
    if (h->Integral() < 10)
        return defreturn;

    TSpectrum* sp = new TSpectrum(3, resolution);
    sp->SetResolution(resolution);
    Int_t nfound = 0;

    if (draw)
        nfound = sp->Search(h, resolution, "nobackground", thresholdCo);
    else
        nfound = sp->Search(h, resolution, "nobackgroundgoff", thresholdCo);

    if (nfound != 2) {
        cout << "Found " << nfound << " peaks in spectrum, not 2, try again" << endl;
        TH1F* hc = (TH1F*)h->Clone("testclone");
        // hc->Rebin(2);
        hc->GetXaxis()->SetRangeUser(range[0], range[1]);
        nfound = 0;
        if (draw)
            nfound = sp->Search(hc, resolution, "nobackground", thresholdCo);
        else
            nfound = sp->Search(hc, resolution, "nobackgroundgoff", thresholdCo);

        if (nfound != 2) {
            cout << "Found " << nfound << " peaks in spectrum, not 2, aborting" << endl;
            if (draw)
                hc->DrawCopy();
            return defreturn;
        }
    }

    Double_t* xpeaks = sp->GetPositionX();
    Double_t* ypeaks = sp->GetPositionY();

    if (draw) {
        for (int p = 0; p < nfound; p++) {
            cout << xpeaks[p] << "\t" << ypeaks[p] << endl;
        }
        ca = new TCanvas("ca", "ca", 600, 600);
        ca->Divide(2, 2);
        ca->cd(1);
        h->DrawCopy();
    }

    // Check if the first peak is lower in energy, otherwise swap them
    if (xpeaks[0] > xpeaks[1]) {
        Double_t temp = xpeaks[1];
        xpeaks[1] = xpeaks[0];
        xpeaks[0] = temp;
        temp = ypeaks[1];
        ypeaks[1] = ypeaks[0];
        ypeaks[0] = temp;
    }

    TF1* fu[2];
    TF1* fus[2][3];
    for (int p = 0; p < nfound; p++) {
        h->GetXaxis()->SetRangeUser(xpeaks[p] - frange, xpeaks[p] + frange);
        fu[p] = new TF1(Form("f%s_p%d", h->GetName(), p), fgammagaussbg, xpeaks[p] - frange, xpeaks[p] + frange, 6);
        fu[p]->SetLineColor(3);
        fu[p]->SetLineWidth(1);
        fu[p]->SetParameter(0, 0); // bg const
        fu[p]->SetParameter(1, 0); // bg slope
        if (!bg) {
            fu[p]->FixParameter(0, 0); // bg const
            fu[p]->FixParameter(1, 0); // bg slope
        }
        fu[p]->SetParameter(2, h->Integral(xpeaks[p] - frange, xpeaks[p] + frange)); // norm
        fu[p]->SetParameter(3, xpeaks[p]); // mean
        fu[p]->SetParLimits(3, xpeaks[p] - 5, xpeaks[p] + 5); // mean
        fu[p]->SetParameter(4, 2); // sigma
        fu[p]->SetParLimits(4, 1, frange); // sigma
        fu[p]->SetParameter(5, h->GetBinContent(h->FindBin(xpeaks[p] - frange))); // step
        if (draw)
            h->Fit(fu[p], "Rn");
        else
            h->Fit(fu[p], "Rqn");

        // Draw results
        if (draw) {
            ca->cd(2 + p);
            h->DrawCopy();
            fu[p]->Draw("same");
            fus[p][0] = new TF1(Form("f%s_p%d_bg", h->GetName(), p), fgammabg, xpeaks[p] - frange, xpeaks[p] + frange, 6);
            fus[p][1] = new TF1(Form("f%s_p%d_st", h->GetName(), p), fgammastep, xpeaks[p] - frange, xpeaks[p] + frange, 6);
            fus[p][2] = new TF1(Form("f%s_p%d_ga", h->GetName(), p), fgammagaus, xpeaks[p] - frange, xpeaks[p] + frange, 6);

            fus[p][0]->SetLineColor(5);
            fus[p][1]->SetLineColor(4);
            fus[p][2]->SetLineColor(2);
            for (int k = 0; k < 3; k++) {
                fus[p][k]->SetLineWidth(1);
                for (int l = 0; l < 6; l++)
                    fus[p][k]->SetParameter(l, fu[p]->GetParameter(l));
                fus[p][k]->Draw("same");
            }
            cout << "New frange=" << frange << endl;
        }
    }

    if (draw) {
        ca->cd(nfound + 2);
        double y[2] = {1173.2, 1332.5};
        double x[2] = {fu[0]->GetParameter(3), fu[1]->GetParameter(3)};
        double e[2] = {fu[0]->GetParError(3), fu[1]->GetParError(3)};
        TGraphErrors* g = new TGraphErrors(2, x, y, e);
        g->Draw("AP");
        g->GetXaxis()->SetTitle("ADC channel [arb.]");
        g->GetYaxis()->SetTitle("Energy [keV]");
        g->Fit("pol1");
        cout << "New frange=" << frange << endl;
    }

    double a = (1332.5 - 1173.2) / (fu[1]->GetParameter(3) - fu[0]->GetParameter(3));
    double b = (1332.5 + 1173.2 - a * (fu[1]->GetParameter(3) + fu[0]->GetParameter(3))) / 2;
    cout << a << "\t" << b << "\t" << a * fu[0]->GetParameter(4) << "\t" << a * fu[1]->GetParameter(4) << "\t" << h->GetName() << endl;

    vector<double> rv;
    rv.push_back(a);
    rv.push_back(b);
    rv.push_back(a * fu[0]->GetParameter(4));
    rv.push_back(a * fu[1]->GetParameter(4));
    return rv;
}

// 1st iteration of fitting procedure for 60Co-133Ba

vector<double> fitCo2(TH1F* h, vector<vector<double>>& peaks, bool bg, bool draw) {
    peaks.resize(6);
    defreturn.push_back(-1);
    h->GetXaxis()->SetRangeUser(range[0], range[1]);
    if (h->Integral() < 10)
        return defreturn;

    TSpectrum *sp = new TSpectrum(3, resolution);
    sp->SetResolution(resolution);
    Int_t nfound = 0;

    if (draw)
        nfound = sp->Search(h, resolution, "nobackground", thresholdCo);
    else
        nfound = sp->Search(h, resolution, "nobackgroundgoff", thresholdCo);

    if (nfound != 2) {
        cout << "Found " << nfound << " peaks in spectrum, not 2, try again" << endl;
        TH1F* hc = (TH1F*)h->Clone("testclone");
        // hc->Rebin(2);
        hc->GetXaxis()->SetRangeUser(range[0], range[1]);
        nfound = 0;

        if (draw)
            nfound = sp->Search(hc, resolution, "nobackground", thresholdCo);
        else
            nfound = sp->Search(hc, resolution, "nobackgroundgoff", thresholdCo);

        if (nfound != 2) {
            cout << "Found " << nfound << " peaks in spectrum, not 2, aborting" << endl;
            if (draw)
                hc->DrawCopy();
            return defreturn;
        }
    }

    Double_t *xpeaks = sp->GetPositionX();
    Double_t *ypeaks = sp->GetPositionY();

    if (draw) {
        for (int p = 0; p < nfound; p++) {
            cout << xpeaks[p] << "\t" << ypeaks[p] << endl;
        }

        ca = new TCanvas("ca", "ca", 900, 900);
        ca->Divide(2, 2);
        ca->cd(1);
        h->DrawCopy();
    }

    // Check if the first peak is lower in energy, otherwise swap them
    if (xpeaks[0] > xpeaks[1]) {
        Double_t temp = xpeaks[1];
        xpeaks[1] = xpeaks[0];
        xpeaks[0] = temp;

        temp = ypeaks[1];
        ypeaks[1] = ypeaks[0];
        ypeaks[0] = temp;
    }

    TF1 *fu[2];
    TF1 *fus[2][3];

    for (int p = 0; p < nfound; p++) {
        h->GetXaxis()->SetRangeUser(xpeaks[p] - frange, xpeaks[p] + frange);
        fu[p] = new TF1(Form("f%s_p%d", h->GetName(), p), fgammagaussbg, xpeaks[p] - frange, xpeaks[p] + frange, 6);
        fu[p]->SetLineColor(3);
        fu[p]->SetLineWidth(1);
        fu[p]->SetParameter(0, 0); // bg const
        fu[p]->SetParameter(1, 0); // bg slope

        if (!bg) {
            fu[p]->FixParameter(0, 0); // bg const
            fu[p]->FixParameter(1, 0); // bg slope
        }

        fu[p]->SetParameter(2, h->Integral(xpeaks[p] - frange, xpeaks[p] + frange)); // norm
        fu[p]->SetParLimits(2, 0, 5e6); // norm
        fu[p]->SetParameter(3, xpeaks[p]); // mean
        fu[p]->SetParLimits(3, xpeaks[p] - 5, xpeaks[p] + 5); // mean
        fu[p]->SetParameter(4, 2); // sigma
        fu[p]->SetParLimits(4, 0.1, frange); // sigma
        fu[p]->SetParameter(5, h->GetBinContent(h->FindBin(xpeaks[p] - frange))); // step

        if (draw)
            h->Fit(fu[p], "Rn");
        else
            h->Fit(fu[p], "Rqn");

        // Draw results
        if (draw) {
            ca->cd(2 + p);
            h->DrawCopy();
            fu[p]->Draw("same");

            fus[p][0] = new TF1(Form("f%s_p%d_bg", h->GetName(), p), fgammabg, xpeaks[p] - frange, xpeaks[p] + frange, 6);
            fus[p][1] = new TF1(Form("f%s_p%d_st", h->GetName(), p), fgammastep, xpeaks[p] - frange, xpeaks[p] + frange, 6);
            fus[p][2] = new TF1(Form("f%s_p%d_ga", h->GetName(), p), fgammagaus, xpeaks[p] - frange, xpeaks[p] + frange, 6);

            fus[p][0]->SetLineColor(5);
            fus[p][1]->SetLineColor(4);
            fus[p][2]->SetLineColor(2);

            for (int k = 0; k < 3; k++) {
                fus[p][k]->SetLineWidth(1);
                for (int l = 0; l < 6; l++)
                    fus[p][k]->SetParameter(l, fu[p]->GetParameter(l));
                fus[p][k]->Draw("same");
            }

            cout << "New frange=" << frange << endl;
            ca->WaitPrimitive();
        }
    }

    double y[2] = {1173.2, 1332.5};
    double inten[2] = {99.85, 99.9826};
    if (draw) {
        ca->cd(nfound + 2);
        double x[2] = {fu[0]->GetParameter(3), fu[1]->GetParameter(3)};
        double e[2] = {fu[0]->GetParError(3), fu[1]->GetParError(3)};
 
        TGraphErrors *g = new TGraphErrors(2, x, y, e);
        g->Draw("AP*");
        g->GetXaxis()->SetTitle("ADC channel [arb.]");
        g->GetYaxis()->SetTitle("Energy [keV]");
        g->Fit("pol1");
        cout << "New frange=" << frange << endl;
    }

    for (int ij = 0; ij < 2; ij++) {
        peaks.at(0).push_back(fu[ij]->GetParameter(3)); // mean
        peaks.at(1).push_back(fu[ij]->GetParError(3)); // error mean
        peaks.at(2).push_back(fu[ij]->GetParameter(4)); // sigma
        peaks.at(3).push_back(fu[ij]->GetParameter(2) / h->GetBinWidth(1)); // content
        peaks.at(4).push_back(fu[ij]->GetParError(2) / h->GetBinWidth(1)); // content error
        peaks.at(5).push_back(y[ij]);
        // peaks.at(6).push_back(fu[ij]->GetParameter(2)/fu[ij]->GetParameter(4) / inten[ij]); // FWHM
        // peaks.at(7).push_back(fu[ij]->GetParError(2)/fu[ij]->GetParameter(4) / inten[ij]); // FWHM error
    }

    double a = (1332.5 - 1173.2) / (fu[1]->GetParameter(3) - fu[0]->GetParameter(3));
    double b = (1332.5 + 1173.2 - a * (fu[1]->GetParameter(3) + fu[0]->GetParameter(3))) / 2;
    cout << a << "\t" << b << "\t" << a * fu[0]->GetParameter(4) << "\t" << a * fu[1]->GetParameter(4) << "\t" << h->GetName() << endl;

    vector<double> rv;
    rv.push_back(a);
    rv.push_back(b);
    rv.push_back(a * fu[0]->GetParameter(4));
    rv.push_back(a * fu[1]->GetParameter(4));

    return rv;
}

// 60Co fitting procedure - returns peaks

vector<vector<double>> fitCopeak(TH1F* h, vector<vector<double>>& peaks, bool bg, bool draw) {

    defreturn2.resize(4);
    defreturn2[0].push_back(-1);

    if (h->Integral() < 10)
        return defreturn2;

    peaks.resize(8);

    for (int i = 0; i < 8; i++)
        peaks.at(i).clear();

    h->GetXaxis()->SetRangeUser(range[0], range[1]);

    TSpectrum *sp = new TSpectrum(3, resolution);
    sp->SetResolution(resolution);
    Int_t nfound = 0;

    if (draw)
        nfound = sp->Search(h, resolution, "nobackground", thresholdCo);
    else
        nfound = sp->Search(h, resolution, "nobackgroundgoff", thresholdCo);

    if (nfound != 2) {
        cout << "Found " << nfound << " peaks in spectrum, not 2, try again" << endl;
        TH1F* hc = (TH1F*)h->Clone("testclone");
        // hc->Rebin(2);
        hc->GetXaxis()->SetRangeUser(range[0], range[1]);
        nfound = 0;

        if (draw)
            nfound = sp->Search(hc, resolution, "nobackground", thresholdCo);
        else
            nfound = sp->Search(hc, resolution, "nobackgroundgoff", thresholdCo);

        if (nfound != 2) {
            cout << "Found " << nfound << " peaks in spectrum, not 2, aborting" << endl;
            if (draw)
                hc->DrawCopy();
            return defreturn2;
        }
    }

    Double_t *xpeaks = sp->GetPositionX();
    Double_t *ypeaks = sp->GetPositionY();
    
    if (draw) {
        ca = new TCanvas("ca", "ca", 900, 900);
        ca->Divide(2, 2);
        ca->cd(1);
        h->DrawCopy();
    }

    // Check if the first peak is lower in energy, otherwise swap them
    if (xpeaks[0] > xpeaks[1]) {
        Double_t temp = xpeaks[1];
        xpeaks[1] = xpeaks[0];
        xpeaks[0] = temp;

        temp = ypeaks[1];
        ypeaks[1] = ypeaks[0];
        ypeaks[0] = temp;
    }

    TF1 *fu;
    TF1 *fus[3];

    double y[2] = {1173.2, 1332.5};
    double inten[2] = {99.85, 99.9826};

    for (int p = 0; p < nfound; p++) {
        h->GetXaxis()->SetRangeUser(xpeaks[p] - frange, xpeaks[p] + frange);
        fu = new TF1(Form("f%s_p%d", h->GetName(), p), fgammagaussbg, xpeaks[p] - frange, xpeaks[p] + frange, 6);
        fu->SetLineColor(3);
        fu->SetLineWidth(1);
        fu->SetParameter(0, 0); // bg const
        fu->SetParameter(1, 0); // bg slope

        if (!bg) {
            fu->FixParameter(0, 0); // bg const
            fu->FixParameter(1, 0); // bg slope
        }

        fu->SetParameter(2, h->Integral(xpeaks[p] - frange, xpeaks[p] + frange)); // norm
        fu->SetParameter(3, xpeaks[p]); // mean
        fu->SetParLimits(3, xpeaks[p] - 5, xpeaks[p] + 5); // mean
        fu->SetParameter(4, 2); // sigma
        fu->SetParLimits(4, 0.1, frange); // sigma
        fu->SetParameter(5, h->GetBinContent(h->FindBin(xpeaks[p] - frange))); // step

        if (draw)
            h->Fit(fu, "Rn");
        else
            h->Fit(fu, "Rqn");

        // Draw results
        if (draw) {
            ca->cd(p+2);
            h->DrawCopy();
            fu->Draw("same");

            fus[0] = new TF1(Form("f%s_p%d_bg", h->GetName(), p), fgammabg, xpeaks[p] - frange, xpeaks[p] + frange, 6);
            fus[1] = new TF1(Form("f%s_p%d_st", h->GetName(), p), fgammastep, xpeaks[p] - frange, xpeaks[p] + frange, 6);
            fus[2] = new TF1(Form("f%s_p%d_ga", h->GetName(), p), fgammagaus, xpeaks[p] - frange, xpeaks[p] + frange, 6);

            fus[0]->SetLineColor(5);
            fus[1]->SetLineColor(4);
            fus[2]->SetLineColor(2);

            for (int k = 0; k < 3; k++) {
                fus[k]->SetLineWidth(1);
                for (int l = 0; l < 6; l++)
                    fus[k]->SetParameter(l, fu->GetParameter(l));
                fus[k]->Draw("same");
            }
        }

        peaks.at(0).push_back(fu->GetParameter(3)); // mean
        peaks.at(1).push_back(fu->GetParError(3)); // error mean
        peaks.at(2).push_back(fu->GetParameter(4)); // sigma
        peaks.at(3).push_back(fu->GetParameter(2) / h->GetBinWidth(1)); // content
        peaks.at(4).push_back(fu->GetParError(2) / h->GetBinWidth(1)); // content error
        peaks.at(5).push_back(y[p]);
        peaks.at(6).push_back(fu->GetParameter(2)/fu->GetParameter(4) / inten[p]); // FWHM
        peaks.at(7).push_back(fu->GetParError(2)/fu->GetParameter(4) / inten[p]); // FWHM error
    }

    if (draw) {
        ca->cd(nfound + 2);
 
        TGraphErrors *g = new TGraphErrors(2, &peaks.at(0)[0], &peaks.at(5)[0], &peaks.at(1)[0] );
        g->Draw("AP*");
        g->GetXaxis()->SetTitle("ADC channel [arb.]");
        g->GetYaxis()->SetTitle("Energy [keV]");
        g->Fit("pol1");

        ca->WaitPrimitive();
    }

    return peaks;
}

// Fitting procedure for 133Ba - returns calibration

vector<double> fitCoBa(TH1F* h, double rough, vector<vector<double>> CoPar, bool bg, bool draw) {
    cout << "CoPar.size()=" << CoPar.size() << endl;

    TSpectrum *sp = new TSpectrum(2, resolution);
    sp->SetResolution(resolution);
    const int n = 5;

    ifstream intensity;
    intensity.open("./Badecay_NNDC.dat");
    intensity.ignore(1000, '\n');

    double en[n], inten[n];

    if (draw) {
        ca = new TCanvas("ca", "ca", 900, 900);
        ca->Divide(4, 3);
    }

    vector<vector<double>> peaks;
    peaks.resize(6);

    for (int i = 0; i < 6; i++)
        peaks.at(i).clear();

    for (int p = 0; p < n; p++) {
        intensity >> en[p] >> inten[p];
        cout << en[p] << "\t" << en[p] / rough - frange << "\t" << en[p] / rough + frange << endl;

        h->GetXaxis()->SetRangeUser(en[p] / rough - frange, en[p] / rough + frange);

        Int_t nfound = 0;

        if (draw) {
            ca->cd(1 + p);
            nfound = sp->Search(h, resolution, "nobackground", thresholdBa);
        } else {
            nfound = sp->Search(h, resolution, "nobackgroundgoff", thresholdBa);
        }

        if (draw) {
            ca->cd(1 + p);
            h->DrawCopy();
        }

        if (nfound != 1) {
            cout << "Found " << nfound << " peaks in spectrum, not 1" << endl;
            continue;
        }

        Double_t *xpeaks = sp->GetPositionX();
        TF1 *fu;
        TF1 *fus[3];

        h->GetXaxis()->SetRangeUser(xpeaks[0] - 3, xpeaks[0] + 3);
        double rms = h->GetRMS();
        h->GetXaxis()->SetRangeUser(xpeaks[0] - frange, xpeaks[0] + frange);

        double norm, mean;
        fu = new TF1(Form("f%s_p%d", h->GetName(), p), "gaus", xpeaks[0] - rms, xpeaks[0] + rms);
        fu->SetParameter(0, h->Integral(xpeaks[0] - frange, xpeaks[0] + frange)); // norm
        fu->SetParameter(1, xpeaks[0]); // mean
        fu->SetParLimits(1, xpeaks[0] - frange / 2., xpeaks[0] + frange / 2.); // mean
        fu->SetParameter(2, rms); // sigma
        fu->SetParLimits(2, rms / 2., rms * 2); // sigma

        h->Fit(fu, "Rqn");
        norm = fu->GetParameter(0);
        mean = fu->GetParameter(1);
        rms = fu->GetParameter(2);

        delete fu;

        fu = new TF1(Form("f%s_p%d", h->GetName(), p), fgammagausnostep, xpeaks[0] - frange, xpeaks[0] + frange, 6);
        fu->SetLineColor(3);
        fu->SetLineWidth(1);
        fu->SetParameter(0, 0); // bg const
        fu->SetParameter(1, 0); // bg slope

        if (!bg) {
            fu->FixParameter(0, 0); // bg const
            fu->FixParameter(1, 0); // bg slope
        }

        fu->SetParameter(2, norm); // norm
        fu->SetParameter(3, mean); // mean
        fu->SetParLimits(3, mean - 2, mean + 2); // mean
        fu->SetParameter(4, rms); // sigma
        fu->SetParLimits(4, rms - 4, rms + 4); // sigma

        if (draw)
            h->Fit(fu, "Rn");
        else
            h->Fit(fu, "Rqn");

        // Draw results
        if (draw) {
            ca->cd(1 + p);
            h->DrawCopy();
            fu->Draw("same");

            fus[0] = new TF1(Form("f%s_p%d_bg", h->GetName(), p), fgammabg, xpeaks[0] - frange, xpeaks[0] + frange, 6);
            fus[1] = new TF1(Form("f%s_p%d_ga", h->GetName(), p), fgammagaus, xpeaks[0] - frange, xpeaks[0] + frange, 6);

            fus[0]->SetLineColor(5);
            fus[1]->SetLineColor(2);

            for (int k = 0; k < 2; k++) {
                fus[k]->SetLineWidth(1);
                for (int l = 0; l < 6; l++)
                    fus[k]->SetParameter(l, fu->GetParameter(l));
                fus[k]->Draw("same");
            }
        }

        // Store peak information in peaks vector
        (peaks.at(0)).push_back(fu->GetParameter(3)); // mean
        (peaks.at(1)).push_back(fu->GetParError(3));  // error mean
        (peaks.at(2)).push_back(fu->GetParameter(4)); // sigma
        (peaks.at(3)).push_back(fu->GetParameter(2) / h->GetBinWidth(1)); // content
        (peaks.at(4)).push_back(fu->GetParError(2) / h->GetBinWidth(1)); // content error 
        (peaks.at(5)).push_back(en[p]);
    }

    cout << "CoPar.size()=" << CoPar.size() << endl;

    for (int j = 0; j < CoPar.size(); j++) {
        cout << "CoPar.at(0).size()=" << CoPar.at(0).size() << endl;
        for (int i = 0; i < CoPar.at(0).size(); i++)
            (peaks.at(j)).push_back(CoPar.at(j).at(i));
    }

    TGraphErrors *g = new TGraphErrors(peaks.at(0).size(), &peaks.at(0)[0], &peaks.at(5)[0], &peaks.at(1)[0]);
    TF1 *fl = new TF1("fl", "pol1", 0, 5000);
    fl->SetParameters(0.004, 1);
    cout << "fl->GetParameter(0)=" << fl->GetParameter(0) << " fl->GetParameter(1)=" << fl->GetParameter(1) << endl;

    g->Fit(fl, "Rn");

    if (draw) {
        ca->cd(n + 1);
        g->Draw("AP*");
        g->GetXaxis()->SetTitle("Rough Energy Gain Bin [keV]");
        g->GetYaxis()->SetTitle("Calibrated Energy Bin [keV]");
        g->Fit(fl);
        ca->cd(n + 2);
        ca->Update();
        ca->SetName(h->GetName());
        f_fitEu->cd();
        ca->Write();
        ca->WaitPrimitive();
    }

    cout << "write parameters peaks.at(0).size()=" << peaks.at(0).size() << endl;
    double a = fl->GetParameter(1);
    double b = fl->GetParameter(0);
    cout << a << "\t" << b << "\t" << peaks.at(0).size() << " " << h->GetName() << endl;

    vector<double> rv;
    rv.push_back(a);
    rv.push_back(b);
    rv.push_back(a * (peaks.at(0)).at(0));
    rv.push_back(a * (peaks.at(0)).at((peaks.at(0)).size() - 1));

    return rv;
}

// Fitting procedure function for 133Ba - returns peaks

vector<vector<double>> fitCoBa2(TH1F* h, double rough, vector<vector<double>> CoPar, bool bg, bool draw) {
    cout << "CoPar.size()=" << CoPar.size() << endl;

    TSpectrum *sp = new TSpectrum(2, resolution);
    sp->SetResolution(resolution);
    const int n = 5;

    ifstream intensity;
    intensity.open("./Badecay_NNDC.dat");
    intensity.ignore(1000, '\n');

    double en[n], inten[n];

    if (draw) {
        ca = new TCanvas("ca", "ca", 900, 900);
        ca->Divide(4, 3);
    }

    vector<vector<double>> peaks;
    peaks.resize(8);

    for (int i = 0; i < 8; i++)
        peaks.at(i).clear();

    for (int p = 0; p < n; p++) {
        intensity >> en[p] >> inten[p];
        cout << en[p] << "\t" << en[p] / rough - frange << "\t" << en[p] / rough + frange << endl;

        h->GetXaxis()->SetRangeUser(en[p] / rough - frange, en[p] / rough + frange);

        Int_t nfound = 0;

        if (draw) {
            ca->cd(1 + p);
            nfound = sp->Search(h, resolution, "nobackground", thresholdBa);
        } else {
            nfound = sp->Search(h, resolution, "nobackgroundgoff", thresholdBa);
        }

        if (draw) {
            ca->cd(1 + p);
            h->DrawCopy();
        }

        if (nfound != 1) {
            cout << "Found " << nfound << " peaks in spectrum, not 1" << endl;
            continue;
        }

        Double_t *xpeaks = sp->GetPositionX();
        TF1 *fu;
        TF1 *fus[3];

        h->GetXaxis()->SetRangeUser(xpeaks[0] - 3, xpeaks[0] + 3);
        double rms = h->GetRMS();
        h->GetXaxis()->SetRangeUser(xpeaks[0] - frange, xpeaks[0] + frange);

        double norm, mean;
        fu = new TF1(Form("f%s_p%d", h->GetName(), p), "gaus", xpeaks[0] - rms, xpeaks[0] + rms);
        fu->SetParameter(0, h->Integral(xpeaks[0] - frange, xpeaks[0] + frange)); // norm
        fu->SetParameter(1, xpeaks[0]); // mean
        fu->SetParLimits(1, xpeaks[0] - frange / 2., xpeaks[0] + frange / 2.); // mean
        fu->SetParameter(2, rms); // sigma
        fu->SetParLimits(2, rms / 2., rms * 2); // sigma

        h->Fit(fu, "Rqn");
        norm = fu->GetParameter(0);
        mean = fu->GetParameter(1);
        rms = fu->GetParameter(2);

        delete fu;

        fu = new TF1(Form("f%s_p%d", h->GetName(), p), fgammagausnostep, xpeaks[0] - frange, xpeaks[0] + frange, 6);
        fu->SetLineColor(3);
        fu->SetLineWidth(1);
        fu->SetParameter(0, 0); // bg const
        fu->SetParameter(1, 0); // bg slope

        if (!bg) {
            fu->FixParameter(0, 0); // bg const
            fu->FixParameter(1, 0); // bg slope
        }

        fu->SetParameter(2, norm); // norm
        fu->SetParameter(3, mean); // mean
        fu->SetParLimits(3, mean - 2, mean + 2); // mean
        fu->SetParameter(4, rms); // sigma
        fu->SetParLimits(4, rms - 4, rms + 4); // sigma

        if (draw)
            h->Fit(fu, "Rn");
        else
            h->Fit(fu, "Rqn");

        // Draw results
        if (draw) {
            ca->cd(1 + p);
            h->DrawCopy();
            fu->Draw("same");

            fus[0] = new TF1(Form("f%s_p%d_bg", h->GetName(), p), fgammabg, xpeaks[0] - frange, xpeaks[0] + frange, 6);
            fus[1] = new TF1(Form("f%s_p%d_ga", h->GetName(), p), fgammagaus, xpeaks[0] - frange, xpeaks[0] + frange, 6);

            fus[0]->SetLineColor(5);
            fus[1]->SetLineColor(2);

            for (int k = 0; k < 2; k++) {
                fus[k]->SetLineWidth(1);
                for (int l = 0; l < 6; l++)
                    fus[k]->SetParameter(l, fu->GetParameter(l));
                fus[k]->Draw("same");
            }
        }

        // Store peak information in peaks vector
        (peaks.at(0)).push_back(fu->GetParameter(3)); // mean
        (peaks.at(1)).push_back(fu->GetParError(3));  // error mean
        (peaks.at(2)).push_back(fu->GetParameter(4)); // sigma
        (peaks.at(3)).push_back(fu->GetParameter(2) / h->GetBinWidth(1)); // content
        (peaks.at(4)).push_back(fu->GetParError(2) / h->GetBinWidth(1)); // content error 
        (peaks.at(5)).push_back(en[p]);
        (peaks.at(6)).push_back(fu->GetParameter(2) / h->GetBinWidth(1) / inten[p]);
        (peaks.at(7)).push_back(fu->GetParError(2) / h->GetBinWidth(1) / inten[p]);
    }

    TGraphErrors *g = new TGraphErrors(peaks.at(0).size(), &peaks.at(0)[0], &peaks.at(5)[0], &peaks.at(1)[0]);
    TF1 *fl = new TF1("fl", "pol1", 0, 5000);
    fl->SetParameters(0.004, 1);
    cout << "fl->GetParameter(0)=" << fl->GetParameter(0) << " fl->GetParameter(1)=" << fl->GetParameter(1) << endl;

    g->Fit(fl, "Rn");

    if (draw){
        ca->cd(n + 1);
        g->Draw("AP*");
        g->GetXaxis()->SetTitle("Rough Energy Gain Bin [keV]");
        g->GetYaxis()->SetTitle("Calibrated Energy Bin [keV]");
        g->Fit(fl);
        ca->cd(n + 2);
        ca->Update();
        ca->SetName(h->GetName());
        f_fitEu->cd();
        ca->Write();
        ca->WaitPrimitive();
    }

    return peaks;
}

// Fitting procedure function for 152Eu - returns peaks

vector<vector<double>> fitEu(TH1F* h, double rough, bool bg, bool draw) {
    defreturn2.resize(4);
    defreturn2[0].push_back(-1);
    if (h->Integral() < 10)
        return defreturn2;

    TSpectrum* sp = new TSpectrum(2, resolution);
    sp->SetResolution(resolution);
    const int n = 13;
    ifstream intensity;
    intensity.open("Eudecay.dat");
    intensity.ignore(1000, '\n');
    double en[n], inten[n];

    if (draw) {
        ca = new TCanvas("ca", "ca", 900, 900);
        ca->Divide(5, 4);
    }

    vector<vector<double>> peaks;
    peaks.resize(8);
    for (int i = 0; i < 8; i++)
        peaks.at(i).clear();


    for (int p = 0; p < n; p++) {
        intensity >> en[p] >> inten[p];
        cout << en[p] << "\t" << en[p] / rough - frange << "\t" << en[p] / rough + frange << endl;
        h->GetXaxis()->SetRangeUser(en[p] / rough - frange, en[p] / rough + frange);
        Int_t nfound = 0;

        // Skipping peaks for specific histograms with bad fits
        if (strcmp(h->GetName(), "h1_germanium_energy_2_0") == 0 && (p == 6)){
            frange = 2;
        }
        if(p == 6){
            frange = 3;
        }
        else{
            frange = 5;
        }


        if (draw) {
            ca->cd(1 + p);
            nfound = sp->Search(h, resolution, "nobackground", thresholdEu);
        } else {
            nfound = sp->Search(h, resolution, "nobackgroundgoff", thresholdEu);
        }

        if (draw) {
            ca->cd(1 + p);
            h->DrawCopy();
        }

        if (nfound != 1) {
            cout << "Found " << nfound << " peaks in spectrum, not 1" << endl;
            continue;
        }

        Double_t* xpeaks = sp->GetPositionX();
        TF1* fu;
        TF1* fus[3];
        h->GetXaxis()->SetRangeUser(xpeaks[0] - 3, xpeaks[0] + 3);
        double rms = h->GetRMS();

        h->GetXaxis()->SetRangeUser(xpeaks[0] - frange, xpeaks[0] + frange);

        // Initial Gaussian fit to estimate parameters
        double norm, mean;
        fu = new TF1(Form("f%s_p%d", h->GetName(), p), "gaus", xpeaks[0] - rms, xpeaks[0] + rms);
        fu->SetParameter(0, h->Integral(xpeaks[0] - frange, xpeaks[0] + frange)); // norm
        fu->SetParameter(1, xpeaks[0]); // mean
        fu->SetParLimits(1, xpeaks[0] - frange / 2., xpeaks[0] + frange / 2.); // mean
        fu->SetParameter(2, rms); // sigma
        fu->SetParLimits(2, rms / 2., rms * 2); // sigma
        h->Fit(fu, "Rqn");
        norm = fu->GetParameter(0);
        mean = fu->GetParameter(1);
        rms = fu->GetParameter(2);

        delete fu;

        // Final fit with Gaussian function
        fu = new TF1(Form("f%s_p%d", h->GetName(), p), fgammagausnostep, xpeaks[0] - frange, xpeaks[0] + frange, 6);
        fu->SetLineColor(3);
        fu->SetLineWidth(1);
        fu->SetParameter(0, 0); // bg const
        fu->SetParameter(1, 0); // bg slope
        if (!bg) {
            fu->FixParameter(0, 0); // bg const
            fu->FixParameter(1, 0); // bg slope
        }
        fu->SetParameter(2, norm); // norm
        fu->SetParameter(3, mean); // mean
        fu->SetParLimits(3, mean - 2, mean + 2); // mean
        fu->SetParameter(4, rms); // sigma
        fu->SetParLimits(4, rms - 4, rms + 4); // sigma

        if (draw)
            h->Fit(fu, "Rn");
        else
            h->Fit(fu, "Rqn");

        // Draw results
        if (draw) {
            ca->cd(1 + p);
            h->DrawCopy();
            fu->Draw("same");
            fus[0] = new TF1(Form("f%s_p%d_bg", h->GetName(), p), fgammabg, xpeaks[0] - frange, xpeaks[0] + frange, 6);
            fus[1] = new TF1(Form("f%s_p%d_ga", h->GetName(), p), fgammagaus, xpeaks[0] - frange, xpeaks[0] + frange, 6);

            fus[0]->SetLineColor(5);
            fus[1]->SetLineColor(2);
            for (int k = 0; k < 2; k++) {
                fus[k]->SetLineWidth(1);
                for (int l = 0; l < 6; l++)
                    fus[k]->SetParameter(l, fu->GetParameter(l));
                fus[k]->Draw("same");
            }
        }

        peaks.at(0).push_back(fu->GetParameter(3)); // mean
        peaks.at(1).push_back(fu->GetParError(3));  // error mean
        peaks.at(2).push_back(fu->GetParameter(4)); // sigma
        peaks.at(3).push_back(fu->GetParameter(2) / h->GetBinWidth(1)); // content
        peaks.at(4).push_back(fu->GetParError(2) / h->GetBinWidth(1)); // content error
        peaks.at(5).push_back(en[p]);
        peaks.at(6).push_back(fu->GetParameter(2) / h->GetBinWidth(1) / inten[p]);
        peaks.at(7).push_back(fu->GetParError(2) / h->GetBinWidth(1) / inten[p]);
    }

    if (draw) {
        ca->cd(1+n);
        TGraphErrors* g = new TGraphErrors(peaks.at(0).size(), &peaks.at(0)[0], &peaks.at(5)[0], &peaks.at(1)[0]);
        g->Draw("AP*");
        g->GetXaxis()->SetTitle("Rough Gain Energy Bin [keV]");
        g->GetYaxis()->SetTitle("Calibrated Energy Bin [keV]");
        g->Fit("pol1");

        ca->cd(2+n);
        TGraphErrors* ge = new TGraphErrors(peaks.at(0).size(), &peaks.at(5)[0], &peaks.at(6)[0], 0, &peaks.at(7)[0]);
        ge->GetXaxis()->SetTitle("Energy [keV]");
        ge->GetYaxis()->SetTitle("Intensity [arb.]");
        ge->Draw("AP*");

        ca->SetName(h->GetName());
        f_fitEu->cd();
        ca->Write();
        ca->WaitPrimitive();
    }

    return peaks;
}

//////////////////////////////////////////
//        Calibration Procedures         //
//////////////////////////////////////////

// 60Co calibration procedures

void CalibGeCo(double threshold, bool draw) {
    frange = 15;
    thresholdCo = threshold;
    TEnv* cf = new TEnv(Form("%s.cal", fileCo));
    TFile* f = new TFile(fileCo);
    TIter next(f->GetListOfKeys());
    TKey* key;

    // Check if the file is a zombie
    if (f->IsZombie()) {
        cout << "Error opening file: " << fileCo << endl;
        return;
    }

    vector<double> gain;
    vector<double> offs;
    vector<double> res0;
    vector<double> res1;

    while((key = (TKey*)next())) {
        TObject* obj = key->ReadObj();

        TH1F* h = (TH1F*)f->Get(key->GetName());
        if (h == NULL)cout << "Error opening histogram: " << h->GetName() << endl;

        frange = 20;
        SetRange(300, 2500);

        vector<double> r = fitCo(h, 1, draw);

        if (r[2] < 1)
            cout << " Problem with fit of: " << h->GetName() << endl;
        if (r[0] < 0)
            continue;

        gain.push_back(r[0]);
        offs.push_back(r[1]);
        res0.push_back(r[2]);
        res1.push_back(r[3]);

        cf->SetValue(Form("%s_Gain: ",h->GetName()), r[0]);
        cf->SetValue(Form("%s_Offset: ",h->GetName()), r[1]);


    }

    cout << "Finished!" << endl;
    cf->SaveLevel(kEnvLocal);

    ca = new TCanvas("ca", "ca", 900, 400);
    ca->Divide(2, 1);
    ca->cd(1);

    TGraph* g = new TGraph(gain.size(), &gain[0], &offs[0]);
    g->GetXaxis()->SetTitle("Gain");
    g->GetYaxis()->SetTitle("Offset");
    g->Draw("AP*");

    ca->cd(2);
    TGraph* gr = new TGraph(res0.size(), &res0[0], &res1[0]);
    gr->GetXaxis()->SetTitle("Resolution 1173 keV");
    gr->GetYaxis()->SetTitle("Resolution 1332 keV");
    gr->Draw("AP*");

    gain.clear();
    offs.clear();
    res0.clear();
    res1.clear();
    resolution = 2;

    cf->SaveLevel(kEnvLocal);
}

// 133Ba 60Co calibration procedure

void CalibGeCoBa(double threshold1, double threshold2, bool draw) {
    frange = 15;
    thresholdCo = threshold1;
    thresholdBa = threshold2;
    TEnv* cf = new TEnv(Form("%s.cal", fileBa));
    TFile* fco = new TFile(fileCo);
    TFile* fba = new TFile(fileBa);
    TIter next(fco->GetListOfKeys());
    TKey* key;
    TIter next2(fba->GetListOfKeys());
    TKey* key2;

    // Check if files are Zombies
    if (fco->IsZombie()) {
        cout << "Error opening file: " << fileCo << endl;
        return;
    }
    
    if (fba->IsZombie()) {
        cout << "Error opening file: " << fileBa << endl;
        return;
    }

    vector<double> gain;
    vector<double> offs;
    vector<double> res0;
    vector<double> res1;

    ca = new TCanvas("ca", "ca", 900, 400);
    ca->Divide(2, 1);

    // Loop over 60Co file histograms and 133Ba doing the calibration only when considering the same histograms


    // Iterate through the keys in the first file
    while ((key = (TKey*)next())) {
        TObject* obj = key->ReadObj();

        // Reset the second iterator for each key in the first file
        next2 = TIter(fba->GetListOfKeys());

        // Iterate through the keys in the second file
        while ((key2 = (TKey*)next2())) {
            TObject* obj2 = key2->ReadObj();

            // Only perform calibration on the same histograms
            if (strcmp(key->GetName(), key2->GetName()) != 0) continue;

            // Retrieve histograms from both files
            TH1F* h = (TH1F*)fco->Get(key->GetName());
            TH1F* h2 = (TH1F*)fba->Get(key2->GetName());

            if (h == NULL || h2 == NULL) {
                cout << "Error opening histogram: " << key->GetName() << endl;
                continue;
            }

            frange = 50;
            SetRange(300, 2500);
            vector<vector<double>> CoPar;

            cout << "Performing rough 60Co gain calibration" << endl;
            vector<double> r = fitCo2(h, CoPar, 1, draw);
            cout << "Rough gain = " << r[0] << endl;

            frange = 20;
            SetRange(20,600);
            cout << "Performing 133Ba calibration" << endl;
            vector<double> r2 = fitCoBa(h2, r[0], CoPar, 1, draw);
            cout << "Fitted! " << r2[0] << endl;

            if (r2[2] < 1) {
                cout << "Problem with fit of: " << key->GetName() << endl;
            }
            if (r2[0] < 0) {
                continue;
            }

            gain.push_back(r2[0]);
            offs.push_back(r2[1]);
            res0.push_back(r2[2]);
            res1.push_back(r2[3]);

            cf->SetValue(Form("%s_Gain", h->GetName()), r2[0]);
            cf->SetValue(Form("%s_Offset", h->GetName()), r2[1]);
        }
    }
    
    ca->cd(1);
    cout << gain.size() << endl;
    TGraph* gs = new TGraph(gain.size(), &gain[0], &offs[0]);
    gs->GetXaxis()->SetTitle("Gain");
    gs->GetYaxis()->SetTitle("Offset");
    gs->Draw("AP*");

    ca->cd(2);
    TGraph* grs = new TGraph(res0.size(), &res0[0], &res1[0]);
    grs->GetXaxis()->SetTitle("Resolution 1");
    grs->GetYaxis()->SetTitle("Resolution 2");
    grs->Draw("AP*");

    cf->SaveLevel(kEnvLocal);
}

void CalibGeCoEu(double threshold1, double threshold2, double threshold3,bool draw){
    frange = 30;
    thresholdCo = threshold1;
    thresholdBa = threshold2;
    thresholdEu = threshold3;
    TFile *fco = new TFile(fileCo);
    TFile *fba = new TFile(fileBa);                                                 
    TFile *feu = new TFile(fileEu);                                                  
    TEnv *cf = new TEnv(Form("%s.cal", fileEu));

    vector<double> gain;
    vector<double> offs;

    TIter next(fco->GetListOfKeys());
    TKey *key;
    TIter next2(feu->GetListOfKeys());
    TKey *key2;
    TIter next3(fba->GetListOfKeys());
    TKey *key3;

    if(fco->IsZombie()){
        cout << "Error opening file: " << fileCo << endl;
        return;
    }
    if(fba->IsZombie()){
        cout << "Error opening file: " << fileBa << endl;
        return;
    }
    if(feu->IsZombie()){
        cout << "Error opening file: " << fileEu << endl;
        return;
    }

    ca = new TCanvas("ca", "ca", 1200, 800);
    ca->Divide(12, 3);

    // Iterate through the keys in the first file
    while((key = (TKey*)next())){
        TObject* obj = key->ReadObj();

        // Reset the second iterator for each key in the first file
        next2 = TIter(feu->GetListOfKeys());

        while((key2 = (TKey*)next2())){
            TObject* obj2 = key2->ReadObj();

            // Only perform calibration on the same histograms
            if(strcmp(key->GetName(), key2->GetName()) != 0)
                continue;

            // Retrieve histograms from both files
            TH1F* h = (TH1F*)fco->Get(key->GetName());
            TH1F* h2 = (TH1F*)feu->Get(key2->GetName());

            if(h == NULL || h2 == NULL){
                cout << "Error opening histogram: " << key->GetName() << endl;
                continue;
            }

            frange = 20;
            SetRange(300, 2500);

            cout << "Performing rough 60Co gain calibration" << endl;
            vector<double> r = fitCo(h, 1, draw);
            cout << "Rough gain = " << r[0] << endl;

            frange = 5;
            SetRange(20, 2000);
            cout << "Performing 152Eu calibration" << endl;
            vector<vector<double>> r2 = fitEu(h2, r[0], 1, draw);
            cout << "Fitted! " << h2->GetName() << endl;

            // Make linear calibration for 152Eu spectrum
            TGraphErrors *g = new TGraphErrors(r2.at(0).size(), &r2.at(0)[0], &r2.at(5)[0], &r2.at(1)[0]);
            TF1 *fl = new TF1("fl", "pol1", 0, 5000);
            fl->SetParameters(0.004, 1);
            g->Fit(fl, "Rn");

            cout << "Write parameters peaks = " << r2.at(0).size() << endl;

            double a = fl->GetParameter(1);
            double b = fl->GetParameter(0);
            
            gain.push_back(a);
            offs.push_back(b);

            // Save calibration parameters
            cf->SetValue(Form("%s_Gain", h2->GetName()), a);
            cf->SetValue(Form("%s_Offset", h2->GetName()), b);
        }
    }

    cf->SaveLevel(kEnvLocal);
    f_fitEu->Close();

    TCanvas *ca4 = new TCanvas("ca4", "ca4", 600, 300);
    ca4->cd();
    TGraph* g = new TGraph(gain.size(), &gain[0], &offs[0]);
    g->Draw("AP*");
}


// 152Eu, 133Ba calibration procedure

void CalibGeBaEu(double threshold1, double threshold2, double threshold3, bool draw) {
    frange = 15;
    thresholdCo = threshold1;
    thresholdBa = threshold2;
    thresholdEu = threshold3;

    TFile *fco = new TFile(fileCo);
    TFile *fba = new TFile(fileBa);                                                 
    TFile *feu = new TFile(fileEu);                                                  
    TEnv *cf = new TEnv(Form("%s.cal", fileEu));

    vector<double> gain;
    vector<double> offs;

    TIter next(fco->GetListOfKeys());
    TKey *key;
    TIter next2(feu->GetListOfKeys());
    TKey *key2;
    TIter next3(fba->GetListOfKeys());
    TKey *key3;

    if (fco->IsZombie()) {
        cout << "Error opening file: " << fileCo << endl;
        return;
    }
    if (fba->IsZombie()) {
        cout << "Error opening file: " << fileBa << endl;
        return;
    }
    if (feu->IsZombie()) {
        cout << "Error opening file: " << fileEu << endl;
        return;
    }

    ca = new TCanvas("ca", "ca", 1200, 800);
    ca->Divide(12, 3);

    // Iterate through the keys in the first file
    while ((key = (TKey*)next())) {
        TObject* obj = key->ReadObj();

        // Reset the second and third iterators for each key in the first file
        next2 = TIter(feu->GetListOfKeys());
        

        while ((key2 = (TKey*)next2())) {
            TObject* obj2 = key2->ReadObj();

            // Only perform calibration on the same histograms
            if (strcmp(key->GetName(), key2->GetName()) != 0)
                continue;

            next3 = TIter(fba->GetListOfKeys());

            while ((key3 = (TKey*)next3())) {
                TObject* obj3 = key3->ReadObj();

                // Only perform calibration on the same histograms
                if (strcmp(key->GetName(), key3->GetName()) != 0)
                    continue;

                // Retrieve histograms from both files
                TH1F* h = (TH1F*)fco->Get(key->GetName());
                TH1F* h2 = (TH1F*)feu->Get(key2->GetName());
                TH1F* h3 = (TH1F*)fba->Get(key3->GetName());

                if (h == NULL || h2 == NULL || h3 == NULL) {
                    cout << "Error opening histogram: " << key->GetName() << endl;
                    continue;
                }

                vector<vector<double>> BaPar;
                frange = 15;
                SetRange(300, 2500);

                cout << "Performing 60Co gain calibration for 133Ba" << endl;
                vector<double> rco = fitCo2(h, BaPar, 1, draw);

                frange = 5;
                SetRange(20, 600);
                vector<vector<double>> rba = fitCoBa2(h3, rco[0], BaPar, 1, draw);

                cout << "133Ba fitted!" << endl;

                frange = 20;
                SetRange(300, 2500);
                vector<vector<double>> CoPar;

                cout << "Performing rough 60Co gain calibration" << endl;
                vector<double> r = fitCo(h, 1, draw);
                cout << "Rough gain = " << r[0] << endl;

                frange = 5;
                SetRange(20, 2000);
                cout << "Performing 152Eu calibration" << endl;
                vector<vector<double>> reu = fitEu(h2, r[0], 1, draw);
                cout << "Fitted! " << h2->GetName() << endl;


                // Combine reu and rba vectors element by element

                // Ensure reu and rba have the same size
                if (reu.size() != rba.size()) {
                    cout << "Error: reu and rba have different sizes" << endl;
                    return;
                }

                // Combine reu and rba element by element
                vector<vector<double>> combined;
                for (size_t i = 0; i < reu.size(); ++i) {
                    vector<double> combinedElement;
                    combinedElement.insert(combinedElement.end(), reu[i].begin(), reu[i].end());
                    combinedElement.insert(combinedElement.end(), rba[i].begin(), rba[i].end());
                    combined.push_back(combinedElement);
                }
                
                // // Make linear calibration for combined 152Eu and 133Ba spectrum
                TGraphErrors *g = new TGraphErrors(combined.at(0).size(), &combined.at(0)[0], &combined.at(5)[0], &combined.at(1)[0]);
                TF1 *fl = new TF1("fl", "pol1", 0, 5000);
                fl->SetParameters(0.004, 1);
                g->Fit(fl, "Rn");

                cout << "Writing 152Eu + 133Ba calibration parameters" << endl;

                double a = fl->GetParameter(1);
                double b = fl->GetParameter(0);
                
                gain.push_back(a);
                offs.push_back(b);

                // Save calibration parameters
                cf->SetValue(Form("%s_Gain", h2->GetName()), a);
                cf->SetValue(Form("%s_Offset", h2->GetName()), b);
            }
        }
    }

    cf->SaveLevel(kEnvLocal);
    fco->Close();
    fba->Close();
    feu->Close();

    ca4 = new TCanvas("ca4", "ca4", 600, 600);
    ca4->cd();
    TGraph* g = new TGraph(gain.size(), &gain[0], &offs[0]);
    g->Draw("AP*");
}

// 152Eu, 133Ba, 60Co calibration procedure

void CalibGeCoBaEu(double threshold1, double threshold2, double threshold3, bool draw) {
    frange = 15;
    thresholdCo = threshold1;
    thresholdBa = threshold2;
    thresholdEu = threshold3;

    TFile *fco = new TFile(fileCo);
    TFile *fba = new TFile(fileBa);                                                 
    TFile *feu = new TFile(fileEu);                                                  
    TEnv *cf = new TEnv(Form("%s.cal", fileEu));
    TEnv *fitdat = new TEnv(Form("%s.fit", fileEu));
    TEnv *res = new TEnv(Form("%s.res", fileEu));

    vector<double> gain;
    vector<double> offs;
    TH1F* hResiduals = new TH1F("hResiduals", "Fit Residuals", 100, -10, 10);
    vector<double> res0;
    vector<double> residuals;

    TIter next(fco->GetListOfKeys());
    TKey *key;
    TIter next2(feu->GetListOfKeys());
    TKey *key2;
    TIter next3(fba->GetListOfKeys());
    TKey *key3;

    if (fco->IsZombie()) {
        cout << "Error opening file: " << fileCo << endl;
        return;
    }
    if (fba->IsZombie()) {
        cout << "Error opening file: " << fileBa << endl;
        return;
    }
    if (feu->IsZombie()) {
        cout << "Error opening file: " << fileEu << endl;
        return;
    }

    ca = new TCanvas("ca", "ca", 1200, 800);
    ca->Divide(12, 3);

    // Iterate through the keys in the first file
    while ((key = (TKey*)next())) {
        TObject* obj = key->ReadObj();

        // Reset the second and third iterators for each key in the first file
        next2 = TIter(feu->GetListOfKeys());
        

        while ((key2 = (TKey*)next2())) {
            TObject* obj2 = key2->ReadObj();

            // Only perform calibration on the same histograms
            if (strcmp(key->GetName(), key2->GetName()) != 0)
                continue;

            next3 = TIter(fba->GetListOfKeys());

            while ((key3 = (TKey*)next3())) {
                TObject* obj3 = key3->ReadObj();

                // Only perform calibration on the same histograms
                if (strcmp(key->GetName(), key3->GetName()) != 0)
                    continue;

                // Retrieve histograms from both files
                TH1F* h = (TH1F*)fco->Get(key->GetName());
                TH1F* h2 = (TH1F*)feu->Get(key2->GetName());
                TH1F* h3 = (TH1F*)fba->Get(key3->GetName());

                if (h == NULL || h2 == NULL || h3 == NULL) {
                    cout << "Error opening histogram: " << key->GetName() << endl;
                    continue;
                }

                vector<vector<double>> BaPar;
                frange = 5;
                SetRange(300, 2500);

                cout << "Performing 60Co-Ba gain calibration on: " << key->GetName()  << endl;
                vector<double> rco = fitCo2(h, BaPar, 1, false);

                frange = 5;
                SetRange(20, 700);
                vector<vector<double>> rba = fitCoBa2(h3, rco[0], BaPar, 1, draw);


                frange = 5;
                SetRange(300, 2500);
                vector<vector<double>> CoPar;

                cout << "Performing rough 60Co-Eu gain calibration on: " << key->GetName() << endl;
                vector<double> r = fitCo(h, 1, false);
                cout << "Rough gain = " << r[0] << endl;

                if (strcmp(h2->GetName(), "h1_germanium_energy_2_0") == 0 ) {
                    frange = 3;
                    SetRange(30, 600);
                }
                else {
                    frange = 5;
                }

                frange = 5;
                SetRange(20, 2000);
                vector<vector<double>> reu = fitEu(h2, r[0], 1, draw);
                cout << "Fitted! " << h2->GetName() << endl;

                frange = 5;
                SetRange(300, 2500);
                vector<vector<double>> CoPeaks;
                cout << "Performing 60Co calibration on: " << key->GetName() << endl;
                vector<vector<double>> copeaks = fitCopeak(h,CoPeaks, 1, draw);


                // Combine reu and rba vectors element by element

                // Ensure reu and rba have the same size
                if (reu.size() != rba.size() && reu.size() != copeaks.size()) {
                    cout << "Error: reu and rba or reu and copeaks have different sizes" << endl;
                    return;
                }

                // Combine reu, rba and copeaks element by element
                vector<vector<double>> combined;
                for (size_t i = 0; i < reu.size(); ++i) {
                    vector<double> combinedElement;
                    combinedElement.insert(combinedElement.end(), reu[i].begin(), reu[i].end());
                    combinedElement.insert(combinedElement.end(), rba[i].begin(), rba[i].end());
                    combinedElement.insert(combinedElement.end(), copeaks[i].begin(), copeaks[i].end());
                    combined.push_back(combinedElement);
                }
                
                // Make linear calibration for combined 152Eu, 133Ba and 60Co spectrum
                TGraphErrors *g = new TGraphErrors(combined.at(0).size(), &combined.at(0)[0], &combined.at(5)[0], &combined.at(1)[0]);
                TF1 *fl = new TF1("fl", "pol2", 0, 5000);
                fl->SetParameters(0.004, 1);
                g->Fit(fl, "Rn");

                //Save energy, centroid and residuals of the combined results

                for (int i = 0; i < combined.at(0).size(); i++) {
                    double residual = combined.at(5).at(i) - fl->Eval(combined.at(0).at(i));

                    residuals.push_back(residual);
                    res0.push_back(combined.at(5).at(i));


                    std::ostringstream ossEn;
                    ossEn << std::fixed << std::setprecision(15) << combined.at(5).at(i);
                    std::string strEn = ossEn.str();

                    std::ostringstream ossCent;
                    ossCent << std::fixed << std::setprecision(15) << combined.at(0).at(i);
                    std::string strCent = ossCent.str();

                    std::ostringstream ossRes;
                    ossRes << std::fixed << std::setprecision(15) << residual;
                    std::string strRes = ossRes.str();

                    fitdat->SetValue(Form("%s_Centroid_%f", h2->GetName(), combined.at(5).at(i)), strCent.c_str());
                    // fitdat->SetValue(Form("%s_Energy_%f", h2->GetName(), combined.at(5).at(i)), strEn.c_str());
                    fitdat->SetValue(Form("%s_Residual_%f", h2->GetName(),combined.at(5).at(i)), strRes.c_str());
                }

                double a = fl->GetParameter(1);
                double b = fl->GetParameter(0);

                std::ostringstream ossA;
                ossA << std::fixed << std::setprecision(15) << a;
                std::string strA = ossA.str();

                std::ostringstream ossB;
                ossB << std::fixed << std::setprecision(15) << b;
                std::string strB = ossB.str();

                gain.push_back(a);
                offs.push_back(b);

                // Save calibration parameters
                cf->SetValue(Form("%s_Gain", h2->GetName()), strA.c_str());
                cf->SetValue(Form("%s_Offset", h2->GetName()), strB.c_str());

                
            }
        }
    }

    cf->SaveLevel(kEnvLocal);
    fitdat->SaveLevel(kEnvLocal);
    fco->Close();
    fba->Close();
    feu->Close();

    TCanvas *ca4 = new TCanvas("ca4", "ca4", 600, 300);
    ca4->cd();
    TGraph* g = new TGraph(gain.size(), &gain[0], &offs[0]);
    g->GetXaxis()->SetTitle("Gain");
    g->GetYaxis()->SetTitle("Offset");
    g->Draw("AP*");

    TCanvas *ca6 = new TCanvas("ca6", "ca6", 600, 300);
    ca6->cd();
    TGraph* gr = new TGraph(res0.size(), &res0[0], &residuals[0]);
    gr->GetXaxis()->SetTitle("Energy [keV]");
    gr->GetYaxis()->SetTitle("Residuals");
    gr->Draw("AP*");

}


//////////////////////////////////////////
//         Fitting Functions            //
//////////////////////////////////////////

// Gaussian with background

Double_t fgammagaussbg(Double_t *x, Double_t *par){
  static Float_t sqrt2pi = TMath::Sqrt(2*TMath::Pi()), sqrt2 = TMath::Sqrt(2.);
  Double_t arg;
  Double_t result = par[0] + par[1]*x[0];
  
  Double_t norm  = par[2];
  Double_t mean  = par[3];
  Double_t sigma = par[4];

  Double_t step = par[5];

  arg = (x[0]-mean)/(sqrt2*sigma);
  result += 1/(sqrt2pi*sigma) * norm * exp(-arg*arg);

  result += step/pow(1+exp(sqrt2*arg),2);

  return result;

}

// Background 

Double_t fgammabg(Double_t *x, Double_t *par){
  Double_t result = par[0] + par[1]*x[0]; 
  
  return result;

}

// Step function

Double_t fgammastep(Double_t *x, Double_t *par){
  static Float_t sqrt2 = TMath::Sqrt(2.);
  Double_t arg;
  Double_t result = 0;
  
  //  Double_t norm  = par[2];
  Double_t mean  = par[3];
  Double_t sigma = par[4];

  Double_t step = par[5];
  arg = (x[0]-mean)/(sqrt2*sigma);
  result += step/pow(1+exp(sqrt2*arg),2);

  return result;

}

// Standard Gaussian

Double_t fgammagaus(Double_t *x, Double_t *par){
  static Float_t sqrt2pi = TMath::Sqrt(2*TMath::Pi()), sqrt2 = TMath::Sqrt(2.);
  Double_t arg;

  Double_t norm  = par[2];
  Double_t mean  = par[3];
  Double_t sigma = par[4];


  arg = (x[0]-mean)/(sqrt2*sigma);
  Double_t result = 1/(sqrt2pi*sigma) * norm * exp(-arg*arg);

  return result;

}

// Gaussian with no step function

Double_t fgammagausnostep(Double_t *x, Double_t *par){
  static Float_t sqrt2pi = TMath::Sqrt(2*TMath::Pi()), sqrt2 = TMath::Sqrt(2.);
  Double_t arg;

  Double_t result = par[0] + par[1]*x[0]; 

  Double_t norm  = par[2];
  Double_t mean  = par[3];
  Double_t sigma = par[4];

  arg = (x[0]-mean)/(sqrt2*sigma);
  result += 1/(sqrt2pi*sigma) * norm * exp(-arg*arg);

  return result;

}

// Linear Function

Double_t flinear(Double_t *x, Double_t *par){
  return x[0]*par[0] + par[1];

}

// Fitting double Gaussian with background
Double_t f2gammagaussbg(Double_t *x, Double_t *par){
  static Float_t sqrt2pi = TMath::Sqrt(2*TMath::Pi()), sqrt2 = TMath::Sqrt(2.);
  Double_t arg;
  Double_t result = par[0] + par[1]*x[0];
  
  Double_t norm1  = par[2];
  Double_t mean1  = par[3];
  Double_t sigma1 = par[4];
  Double_t norm2  = par[5];
  Double_t mean2  = par[6];
  Double_t sigma2 = par[7];

  Double_t step = par[8];

  arg = (x[0]-mean1)/(sqrt2*sigma1);
  result += 1/(sqrt2pi*sigma1) * norm1 * exp(-arg*arg);
  result += step/pow(1+exp(sqrt2*arg),2);
  arg = (x[0]-mean2)/(sqrt2*sigma2);
  result += 1/(sqrt2pi*sigma2) * norm2 * exp(-arg*arg);
  result += step/pow(1+exp(sqrt2*arg),2);

  return result;

}

// Miscellaeneous functions

// Calib to .txt

void WriteCalParams(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    std::ofstream outFile(outputFile);
    
    // Get the current date and time
    std::time_t now = std::time(nullptr);
    std::tm* currentDateTime = std::localtime(&now);

    // Format the date and time string
    char dateTimeString[100];
    std::strftime(dateTimeString, sizeof(dateTimeString), "%Y-%m-%d %H:%M:%S", currentDateTime);

    outFile << "# Calibration made on: " << dateTimeString << "\n";
    outFile << "# detector crystal a1 a0\n";

    std::map<int, std::map<std::string, std::pair<double, double>>> calData;

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string paramName;
        double gain;

        if (iss >> paramName >> gain) {
            // Extract the detector and crystal numbers from the parameter name
            size_t pos1 = paramName.find("energy_");
            size_t pos2 = paramName.find('_', pos1 + 7);
            std::string detectorStr = paramName.substr(pos1 + 7, pos2 - pos1 - 7);
            std::string crystal = paramName.substr(pos2 + 1, paramName.find('_', pos2 + 1) - pos2 - 1);

            // Convert detector number to integer
            int detector = std::stoi(detectorStr);

            // Get the offset from the next line
            if (std::getline(inFile, line)) {
                std::istringstream iss2(line);
                std::string paramName2;
                double offset;
                if (iss2 >> paramName2 >> offset) {
                    // Store the gain and offset in the map
                    calData[detector][crystal] = std::make_pair(gain / 1000, offset);
                }
            }
        }
    }

    // Write the data to the output file in the desired order
    for (const auto& detectorData : calData) {
        for (const auto& crystalData : detectorData.second) {
            int detector = detectorData.first;
            const std::string& crystal = crystalData.first;
            double gain = crystalData.second.first;
            double offset = crystalData.second.second;

            outFile << std::fixed << std::setprecision(15);
            outFile << detector << ' ' << crystal << ' ' << gain << ' ' << offset << '\n';
        }
    }
}

// Read calibration parameters and save the gain and offset for each histogram

std::map<std::pair<int, int>, std::pair<double, double>> ReadCalParams(const std::string& inputFile) {
    std::ifstream inFile(inputFile);

    // Map to store the calibration parameters
    std::map<std::pair<int, int>, std::pair<double, double>> params;

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string paramName;
        double value;

        if (iss >> paramName >> value) {
            // Extract the detector and crystal numbers from the parameter name
            size_t pos1 = paramName.find("energy_");
            size_t pos2 = paramName.find('_', pos1 + 7);
            int detector = std::stoi(paramName.substr(pos1 + 7, pos2 - pos1 - 7));
            int crystal = std::stoi(paramName.substr(pos2 + 1, paramName.find('_', pos2 + 1) - pos2 - 1));

            // Check if this is a gain or an offset
            if (paramName.find("Gain") != std::string::npos) {
                params[{detector, crystal}].first = value;
            } else if (paramName.find("Offset") != std::string::npos) {
                params[{detector, crystal}].second = value;
            }
        }
    }

    return params;
}


// Read fit parameters from file and save the energy, centroid and residual for each histogram

std::map<std::tuple<int, int, double>, std::pair<double, double>> ReadFitParams(const std::string& inputFile) {
    std::ifstream inFile(inputFile);

    // Map to store the fit parameters
    std::map<std::tuple<int, int, double>, std::pair<double, double>> params;

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string paramName;
        double value;

        if (iss >> paramName >> value) {
            // Extract the detector, crystal numbers, and energy from the parameter name
            size_t pos1 = paramName.find("energy_");
            size_t pos2 = paramName.find('_', pos1 + 7);
            int detector = std::stoi(paramName.substr(pos1 + 7, pos2 - pos1 - 7));
            int crystal = std::stoi(paramName.substr(pos2 + 1, paramName.find('_', pos2 + 1) - pos2 - 1));
            double energy = std::stod(paramName.substr(paramName.find_last_of('_') + 1));

            // Check if this is a centroid or a residual
            if (paramName.find("Centroid") != std::string::npos) {
                params[{detector, crystal, energy}].first = value;
            } else if (paramName.find("Residual") != std::string::npos) {
                params[{detector, crystal, energy}].second = value;
            }
        }
    }
    // Print the parameters
    for (const auto& param : params) {
        int detector = std::get<0>(param.first);
        int crystal = std::get<1>(param.first);
        double energy = std::get<2>(param.first);
        double centroid = param.second.first;
        double residual = param.second.second;

        std::cout << "Detector: " << detector << " Crystal: " << crystal << " Energy: " << energy << " Centroid: " << centroid << " Residual: " << residual << std::endl;
    }
    return params;
}

// Checking the residuals of the fit and writing the histogram if it meets a certain criteria

void ResidualCheck(double resid, const std::map<std::tuple<int, int, double>, std::pair<double, double>>& fitparams) {
    
    // Create a new vector to store all peaks
    std::vector<double> allPeaks;

    // Insert all peaks from CoPeaks, BaPeaks, and EuPeaks into allPeaks
    allPeaks.insert(allPeaks.end(), CoPeaks.begin(), CoPeaks.end());
    allPeaks.insert(allPeaks.end(), BaPeaks.begin(), BaPeaks.end());
    allPeaks.insert(allPeaks.end(), EuPeaks.begin(), EuPeaks.end());

    TFile* f_fitEu = new TFile("fitcheck.root", "RECREATE");

    // Vectors to store the energies and residuals of the peaks
    std::vector<double> rescheck;
    std::vector<double> res;
    std::vector<double> enecheck;
    std::vector<double> ene;

    // TGraphError to show residuals

    std::map<std::pair<int, int>, TGraphErrors*> graphs;\
    std::map<std::pair<int, int>, TCanvas*> canvases;

    int prev_crystal = -1;
    int prev_detector = -1;

    // Iterate through the fit parameters
    for (const auto& fitparam : fitparams) {
        int detector = std::get<0>(fitparam.first);
        int crystal = std::get<1>(fitparam.first);
        double energy = std::get<2>(fitparam.first);
        double centroid = fitparam.second.first;
        double residual = fitparam.second.second;

    // Create a new TGraphErrors and TCanvas if this is a new detector and crystal combination
    if (detector != prev_detector || crystal != prev_crystal) {
        graphs[std::make_pair(detector, crystal)] = new TGraphErrors();
        canvases[std::make_pair(detector, crystal)] = new TCanvas(Form("c_%d_%d", detector, crystal), Form("Detector %d, Crystal %d", detector, crystal), 600, 600);
        prev_detector = detector;
        prev_crystal = crystal;
    }

        // Draw the residual on the TGraph
        graphs[std::make_pair(detector, crystal)]->SetPoint(graphs[std::make_pair(detector, crystal)]->GetN(), energy, residual);

        // Check if the residual is within the acceptable range
        if (residual < -0.5 || residual > 0.5) {
            std::cout << "Warning: Unacceptable residual " << residual << " for detector " << detector << ", crystal " << crystal << ", and energy " << energy << "." << std::endl;
        }

        // Store the data for each crystal in a vector
        if (detector == prev_detector && crystal == prev_crystal) {
            rescheck.push_back(residual);
            enecheck.push_back(energy);
        } else {
            if (prev_detector != -1 && prev_crystal != -1) {
                // Check that all the peaks have been fitted
                for (const auto& peak : allPeaks) {
                    if (std::find(enecheck.begin(), enecheck.end(), peak) == enecheck.end()) {
                        std::cout << "Warning: Peak at energy " << peak << " has not been fitted for detector " << prev_detector << " and crystal " << prev_crystal << "." << std::endl;
                    }
                }
            }

            // Clear the vectors for the next crystal
            rescheck.clear();
            enecheck.clear();
            rescheck.push_back(residual);
            enecheck.push_back(energy);
        }
        prev_crystal = crystal;
        prev_detector = detector;
    }

    // Check for the last detector and crystal
    for (const auto& peak : allPeaks) {
        if (std::find(enecheck.begin(), enecheck.end(), peak) == enecheck.end()) {
            std::cout << "Warning: Peak at energy " << peak << " has not been fitted for detector " << prev_detector << " and crystal " << prev_crystal << "." << std::endl;
        }
    }
    // Draw the TGraphs on their respective canvases
    for (auto& graph : graphs) {
        TCanvas* c = new TCanvas(Form("c_%d_%d", graph.first.first, graph.first.second), Form("Detector %d, Crystal %d", graph.first.first, graph.first.second), 1200, 1200);
        graph.second->Draw("AP*");
        graph.second->GetXaxis()->SetTitle("Energy [keV]");
        graph.second->GetYaxis()->SetTitle("Residuals");
        c->Update();
        c->Modified();
        std::cout << "Press Enter to continue to the next graph...\n";
        std::cin.get();
        delete c; // delete the canvas
    }
}


// Function for doing the fit and entering the correct centroid

void CentroidWrite(const std::map<std::tuple<int, int, double>, std::pair<double, double>>& fitparams) {
    
    // Create a new vector to store all peaks
    std::vector<double> allPeaks;
    TEnv *fitcheck = new TEnv("fitcheck.fit");
    // Insert all peaks from CoPeaks, BaPeaks, and EuPeaks into allPeaks
    allPeaks.insert(allPeaks.end(), CoPeaks.begin(), CoPeaks.end());
    allPeaks.insert(allPeaks.end(), BaPeaks.begin(), BaPeaks.end());
    allPeaks.insert(allPeaks.end(), EuPeaks.begin(), EuPeaks.end());

    TFile* f_fitEu = new TFile("fitcheck.root", "RECREATE");

    // Vectors to store the energies and residuals of the peaks
    std::vector<double> rescheck;
    std::vector<double> res;
    std::vector<double> enecheck;
    std::vector<double> ene;

    int prev_crystal = -1;
    int prev_detector = -1;
    double prev_centroid = 0;
    // Iterate through the fit parameters
    for (const auto& fitparam : fitparams) {
        int detector = std::get<0>(fitparam.first);
        int crystal = std::get<1>(fitparam.first);
        double energy = std::get<2>(fitparam.first);
        double centroid = fitparam.second.first;
        double residual = fitparam.second.second;
        fitcheck->SetValue(Form("h1_germanium_energy_%d_%d_Centroid_%f", detector, crystal, energy), centroid);

        // Check if the residual is within an acceptable range
        if(residual < -0.5 || residual > 0.5){
            cout << "Detector: " << prev_detector << " Crystal: " << prev_crystal << " Energy: " << energy << " Residual: " << residual << " Centroid: " << centroid << endl;

            //Prompt the user to enter the peak
            cout << "Enter the centroid: ";
            double newPeak;
            std::cin >> newPeak;

            // Write the new peak in the following format h1_germanium_energy_1_0_Centroid_39.910000: 41.611640928823761
            fitcheck->SetValue(Form("h1_germanium_energy_%d_%d_Centroid_%f", prev_detector, prev_crystal, energy), newPeak);
        }

        // Store the data for each crystal in a vector
        if (detector == prev_detector && crystal == prev_crystal) {
            rescheck.push_back(residual);
            enecheck.push_back(energy);
        } else {
            if (prev_detector != -1 && prev_crystal != -1) {
                // Check that all the peaks have been fitted
                for (const auto& peak : allPeaks) {
                    if (std::find(enecheck.begin(), enecheck.end(), peak) == enecheck.end()) {
                        // Output which histogram is being checked
                        cout << "Detector: " << prev_detector << " Crystal: " << prev_crystal << " Energy: " << peak << endl;
                        //Prompt the user to enter the peak
                        cout << "Enter the centroid: ";
                        double newPeak;
                        std::cin >> newPeak;

                        // Write the new peak in the following format h1_germanium_energy_1_0_Centroid_39.910000: 41.611640928823761
                        fitcheck->SetValue(Form("h1_germanium_energy_%d_%d_Centroid_%f", prev_detector, prev_crystal, peak), newPeak);
                    }
                }
            }

            // Clear the vectors for the next crystal
            rescheck.clear();
            enecheck.clear();
            rescheck.push_back(residual);
            enecheck.push_back(energy);
        }
        prev_crystal = crystal;
        prev_detector = detector;
    }

    // Check for the last detector and crystal
    for (const auto& peak : allPeaks) {
        if (std::find(enecheck.begin(), enecheck.end(), peak) == enecheck.end()) {
            // Output which histogram is being checked
            cout << "Detector: " << prev_detector << " Crystal: " << prev_crystal << " Energy: " << peak << endl;
            //Prompt the user to enter the peak
            cout << "Enter the centroid: ";
            double newPeak;
            std::cin >> newPeak;

            // Write the new peak in the following format h1_germanium_energy_1_0_Centroid_39.910000: 41.611640928823761
            fitcheck->SetValue(Form("h1_germanium_energy_%d_%d_Centroid_%f", prev_detector, prev_crystal, peak), newPeak);
        }
    }

    fitcheck->SaveLevel(kEnvLocal);
}

// Functiong for saving the parameters for the previous crystal

void SaveParameters(int detector, int crystal, const vector<double>& ene, const vector<double>& cent, TEnv* fitdat, TEnv* finalfitcal) {
    // Make linear regression
    TGraphErrors *g = new TGraphErrors(cent.size(), &cent[0], &ene[0]);
    TF1 *fl = new TF1("fl", "pol1", 0, 5000);
    fl->SetParameters(0.1, 1);
    g->Fit(fl, "Rn");

    // Save centroid, energy and residuals of the combined results
    for (int i = 0; i < cent.size(); i++) {
        double residual = ene.at(i) - fl->Eval(cent.at(i));

        std::ostringstream ossCent;
        ossCent << std::fixed << std::setprecision(15) << cent.at(i);
        std::string strCent = ossCent.str();

        std::ostringstream ossEn;
        ossEn << std::fixed << std::setprecision(15) << ene.at(i);
        std::string strEn = ossEn.str();

        std::ostringstream ossRes;
        ossRes << std::fixed << std::setprecision(15) << residual;
        std::string strRes = ossRes.str();

        fitdat->SetValue(Form("h1_germanium_energy_%d_%d_Centroid_%f",detector, crystal, ene.at(i)), strCent.c_str());
        fitdat->SetValue(Form("h1_germanium_energy_%d_%d_Residual_%f", detector, crystal, ene.at(i)), strRes.c_str());
    }

    double a = fl->GetParameter(1);
    double b = fl->GetParameter(0);

    std::ostringstream ossA;
    ossA << std::fixed << std::setprecision(15) << a;
    std::string strA = ossA.str();
    std::ostringstream ossB;
    ossB << std::fixed << std::setprecision(15) << b;
    std::string strB = ossB.str();

    finalfitcal->SetValue(Form("h1_germanium_energy_%d_%d_Gain", detector, crystal), strA.c_str());
    finalfitcal->SetValue(Form("h1_germanium_energy_%d_%d_Offset", detector, crystal), strB.c_str());
}

// Function for redoing the calibration and checking the residuals

void FitRedo(const std::map<std::tuple<int, int, double>, std::pair<double, double>>& fitparams) {

    TEnv *fitdat = new TEnv("fitcheckfinal.fit");
    TEnv *finalfitcal = new TEnv("finalfit.cal");

    vector<double> ene;
    vector<double> cent;
    int crystal_next = 0;
    int detector_next = 0; // Add this line to keep track of the current detector

    for (const auto& fitparam : fitparams) {
        int detector = std::get<0>(fitparam.first);
        int crystal = std::get<1>(fitparam.first);
        double energy = std::get<2>(fitparam.first);
        double centroid = fitparam.second.first;

        std::cout << "Current detector: " << detector << std::endl;
        std::cout << "Current centroid: " << centroid << std::endl;
        std::cout << "Current energy: " << energy << std::endl;
        std::cout << "Current crystal: " << crystal << std::endl;
        if((crystal != crystal_next || detector != detector_next) && !ene.empty()){
            // Save parameters for the previous crystal
            std::cout << "Saving parameters for the previous detector" << detector_next << std::endl;
            std::cout << "Saving parameters for the previous crystal" << crystal_next << std::endl;
            SaveParameters(detector_next, crystal_next, ene, cent, fitdat, finalfitcal);

            // Clear the vectors for the next crystal
            ene.clear();
            cent.clear();
        }

        // Add the current energy and centroid to the vectors
        ene.push_back(energy);
        cent.push_back(centroid);

        crystal_next = crystal;
        detector_next = detector; // Update the current detector
    }
    std::cout << "Saving parameters for the last crystal" << crystal_next << std::endl;
    // Save parameters for the last crystal
    int last_detector = std::get<0>(fitparams.rbegin()->first);
    int last_crystal = std::get<1>(fitparams.rbegin()->first);
    SaveParameters(last_detector, last_crystal, ene, cent, fitdat, finalfitcal);

    fitdat->SaveLevel(kEnvLocal);
    finalfitcal->SaveLevel(kEnvLocal);
}

// Function that performs a minimization of the residuals and centroids
/*

double objectiveFunction(const double* centroid, const std::vector<double>& ene, const std::vector<double>& residual) {
    double sumSqResiduals = 0;

    // Make linear regression for each point
    for (size_t i = 0; i < ene.size(); ++i) {
        TGraphErrors *g = new TGraphErrors(1, centroid, &ene[i], 0, 0);
        TF1 *fl = new TF1("fl", "pol1", 0, 5000);
        fl->SetParameters(*centroid, 1);
        g->Fit(fl, "Rn");

        // Calculate the sum of the squares of the residuals
        double calculatedResidual = ene[i] - fl->Eval(*centroid);
        sumSqResiduals += calculatedResidual * calculatedResidual;

        // Add the square of the difference between the calculated and actual residual
        sumSqResiduals += (residual[i] - fl->Eval(*centroid)) * (residual[i] - fl->Eval(*centroid));
    }

    return sumSqResiduals;
}

void minimizeResiduals(const std::string& inputFile) {
    // Read the fit parameters from the file
    std::map<std::tuple<int, int, std::vector<double>>, std::pair<std::vector<double>, std::vector<double>>> params = ReadFitParams(inputFile);

    // Loop over each entry in the map
    for (auto& param : params) {
        // Extract the detector, crystal, energy, centroid, and residual
        int detector = std::get<0>(param.first);
        int crystal = std::get<1>(param.first);
        std::vector<double> energy = std::get<2>(param.first);
        std::vector<double> centroid = param.second.first;
        std::vector<double> residual = param.second.second;

        // Print the initial centroid
        for (const auto& c : centroid) {
            std::cout << "Initial centroid: " << c << std::endl;
        }

        // Define the objective function
        ROOT::Math::Functor f([&](const double* x) { return objectiveFunction(x, energy, residual); }, 1);

        // Create the minimizer
        ROOT::Minuit2::Minuit2Minimizer min(ROOT::Minuit2::kMigrad);

        // Set the function to minimize and the initial values
        min.SetFunction(f);
        for (size_t i = 0; i < centroid.size(); ++i) {
            min.SetVariable(i, "Centroid", centroid[i], 0.01);
        }

        // Perform the minimization
        min.Minimize();

        // Update the centroid with the optimized value
        const double* xs = min.X();
        for (size_t i = 0; i < centroid.size(); ++i) {
            param.second.first[i] = xs[i];
        }

        // Print the optimized centroid
        for (size_t i = 0; i < centroid.size(); ++i) {
            std::cout << "Optimized centroid: " << xs[i] << std::endl;
        }
        for (const auto& r : residual) {
            std::cout << "Residual: " << r << std::endl;
        }
    }
}

*/


// Now we use the ReadFitParams function to read the residuals and centroids from the .fit file

void FitCheck(const std::string& fitfile, bool check,bool write, bool redo) {
    // Read the fit parameters from the file
    std::map<std::tuple<int, int, double>, std::pair<double, double>> fitparams = ReadFitParams(fitfile); 


    // Check the residuals of the fit
    if (check == true) {
        ResidualCheck(0.5, fitparams);
    }

    // Write the centroids to the fitcheck.fit file
    if (write == true) {
        CentroidWrite(fitparams);
    }

    // Redo the calibration and check the residuals
    if (redo == true) {
        // Read the fit parameters from the fitcheck.fit file
        std::map<std::tuple<int, int, double>, std::pair<double, double>> fitredo = ReadFitParams("fitcheck.fit");
        FitRedo(fitredo);
    }

}

// Use calibration parameters to calibrate a histogram

void CalibrateHistogram(const std::string& histofile , const std::string& infile) {

    // Load histograms
    TFile* f = new TFile(histofile.c_str());
    TIter next(f->GetListOfKeys());
    TKey* key;
    
    // Make a new calibration output .root file

    TFile* outfile = new TFile("Calibrated Spectrum", "RECREATE");

    TRandom* rand = new TRandom();
    // Load calibration co-efficients
    std::map<std::pair<int, int>, std::pair<double, double>> calparams = ReadCalParams(infile);

    // Summed histogram

    TH1F* hsum = new TH1F("sum", "sum", 1500, 1, 1500);
    hsum->GetXaxis()->SetTitle("Energy [keV]");
    hsum->GetYaxis()->SetTitle("Counts");

    // Loop over the histograms and apply the calibrations to each with the matching map from calparams drawing the result on a new histogram

    while ((key = (TKey*)next())) {
        TObject* obj = key->ReadObj();
        TH1F* h = (TH1F*)f->Get(key->GetName());
        if (h == NULL) {
            cout << "Error opening histogram: " << key->GetName() << endl;
            continue;
        }
        
        // Make new calibrated histogram

        TH1F* h2 = new TH1F(Form("calibrated_%s", h->GetName()), Form("calibrated_%s", h->GetName()), 1500, 1, 1500);
        h2->GetXaxis()->SetTitle("Energy [keV]");
        h2->GetYaxis()->SetTitle("Counts");

        // Extract the detector and crystal numbers from the histogram name
        size_t pos1 = std::string(h->GetName()).find("energy_");
        size_t pos2 = std::string(h->GetName()).find('_', pos1 + 7);
        int detector = std::stoi(std::string(h->GetName()).substr(pos1 + 7, pos2 - pos1 - 7));
        int crystal = std::stoi(std::string(h->GetName()).substr(pos2 + 1, std::string(h->GetName()).find('_', pos2 + 1) - pos2 - 1));

        // Check if the calibration parameters exist for this histogram
        if (calparams.find({detector, crystal}) != calparams.end()) {
            double gain = calparams[{detector, crystal}].first;
            double offset = calparams[{detector, crystal}].second;

            cout << "Calibrating histogram: " << h->GetName() << " with gain = " << gain << " and offset = " << offset << endl;

            // Apply the calibration to the histogram
            for (int i = 0; i <= h->GetNbinsX(); i++) {
                double energy = gain * h->GetBinCenter(i) + offset + rand->Uniform(0,1) - 0.5;
                h2->Fill(energy, h->GetBinContent(i));
                hsum->Fill(energy, h->GetBinContent(i));
            }

            // Rename the histogram
            h2->SetName(Form("calibrated_%s", h->GetName()));

            // Draw the calibrated histogram on a new canvas
            TCanvas* ca = new TCanvas(Form("ca_%s", h->GetName()), Form("ca_%s", h->GetName()), 800, 600);
            ca->Divide(1, 2);
            ca->cd(1);
            h2->Draw("HIST");
            ca->cd(2);
            hsum->Draw("HIST");
            ca->WaitPrimitive();

            // Write the calibrated histogram to the output file
            h2->Write();
        }
    }
}


// Grabbing histograms from a file

void processDirectory(TDirectory* dir, TFile* outFile, double threshold, int peaksupper, int peakslower, double resolution = 1.0) {
    // Save the current directory
    TDirectory* savedDir = gDirectory;

    // Change to the target directory
    dir->cd();

    // Iterate over the keys in the directory
    TIter next(dir->GetListOfKeys());
    TKey* key;
    while ((key = (TKey*)next())) {
        TObject* obj = key->ReadObj();

        // Check if the object is a histogram, process it

                if (obj->InheritsFrom("TH1")) {
                    TH1* hist = (TH1*)obj;

                    // Clone histogram

                    TH1* histClone = (TH1*)hist->Clone();

                    // Check if the histogram is a calibration spectrum using TSpectrum
                    TSpectrum spectrum;
                    int nPeaks = spectrum.Search(histClone, resolution, "", threshold);

                    // Write histogram to the output ROOT file if it has an expected number of calibration peaks
                    if(nPeaks > peakslower && nPeaks < peaksupper){
                        outFile->cd();
                        hist->Write();
                    }

                } else {
                    std::cerr << "Warning: Unsupported object type " << obj->ClassName() << std::endl;
                }
    }

    // Return to the original directory
    savedDir->cd();
}

void processRootFile(const char* filename, const char* targetDir, const char* outRootFile, double threshold, int peaksupper, int peakslower) {
    // Open the ROOT file
    TFile* rootFile = TFile::Open(filename, "READ");
    if (!rootFile || rootFile->IsZombie()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Open the output ROOT file for saving fitted histograms
    TFile* outputFile = new TFile(outRootFile, "RECREATE");
    if (!outputFile || outputFile->IsZombie()) {
        std::cerr << "Error: Could not create output file " << outRootFile << std::endl;
        rootFile->Close();
        delete rootFile;
        return;
    }

    // Navigate to the "DEGAS" directory
    TDirectory* degasDir = (TDirectory*)rootFile->Get("DEGAS");
    if (!degasDir) {
        std::cerr << "Error: Directory DEGAS not found in file " << filename << std::endl;
        rootFile->Close();
        delete rootFile;
        outputFile->Close();
        delete outputFile;
        return;
    }

    // Navigate to the "Calibrated Energy Spectra" subdirectory
    TDirectory* targetDirectory = (TDirectory*)degasDir->Get(targetDir);
    if (!targetDirectory) {
        std::cerr << "Error: Directory " << targetDir << " not found in DEGAS directory" << std::endl;
        rootFile->Close();
        delete rootFile;
        outputFile->Close();
        delete outputFile;
        return;
    }

    // Process the target directory
    processDirectory(targetDirectory, outputFile, threshold, peaksupper, peakslower);

    // Close the ROOT file and the text file
    rootFile->Close();
    delete rootFile;
    outputFile->Close();
    delete outputFile;
}


// Macro entry point
void yoink(const char* filename, const char* outRootFile, const char* element) {
    double threshold;
    int peaksupper;
    int peakslower;
    if(strcmp(element, "Co") == 0){
        threshold = 0.1;
        peaksupper = 5;
        peakslower = 1;
    }
    else if(strcmp(element, "Ba") == 0){
        threshold = 0.01;
        peaksupper = 30;
        peakslower = 2;
    }
    else if(strcmp(element, "Eu") == 0){
        threshold = 0.01;
        peaksupper = 30;
        peakslower = 2;
    }
    else{
        std::cerr << "Error: Invalid element specified" << std::endl;
        return;
    }
    processRootFile(filename, "Calibrated Energy Spectra", outRootFile, threshold , peaksupper, peakslower);
}

void man(){
    cout << "\n\n==================== Manual for DegasCal.C ====================\n" << endl;
    cout << "Usage:\n" << endl;
    cout << "Calibration elements available: Co, Ba, Eu\n" << endl;
    cout << ".root files for Germanium histograms are hard declarations found at the top of the macro, fileCo, fileBa, fileEu\n" << endl;
    cout << "Functions:\n" << endl;
    cout << "1. yoink(\"filename\", \"outputfilename\", \"element\") - Reads calibration histograms from c4Root nearline histogram procedure and makes a .root file with the relevant histograms\n" << endl;
    cout << "2. WriteCalParams(\"inputfile\", \"outputfile\") - Writes calibration parameters to a .txt file\n" << endl;
    cout << "3. ReadCalParams(\"inputfile\") - Reads calibration parameters from a .txt file\n" << endl;
    cout << "4. ReadFitParams(\"inputfile\") - Reads fit parameters from a .fit file\n" << endl;
    cout << "5. ResidualCheck(double resid, const std::map<std::tuple<int, int, double>, std::pair<double, double>>& fitparams) - Checks the residuals of the fit\n" << endl;
    cout << "6. CentroidWrite(const std::map<std::tuple<int, int, double>, std::pair<double, double>>& fitparams) - Writes the centroids to the fitcheck.fit file\n" << endl;
    cout << "7. FitRedo(const std::map<std::tuple<int, int, double>, std::pair<double, double>>& fitparams) - Redoes the calibration and checks the residuals\n" << endl;
    cout << "8. FitCheck(const std::string& fitfile, bool check,bool write, bool redo) - Checks the residuals of the fit, writes the centroids to the fitcheck.fit file, and redoes the calibration and checks the residuals\n" << endl;
    cout << "9. CalibrateHistogram(\"histofile\", \"calibrationfile\") - Calibrates histograms using calibration parameters -- USE WITH CAUTION !!!\n" << endl;
    cout << "10. CalibGeCo(double threshold1, double threshold2, double threshold3, bool draw) - Performs calibration on 60Co spectra\n" << endl;
    cout << "11. CalibGeCoEu(double threshold1, double threshold2, double threshold3, bool draw) - Performs calibration on 60Co and 152Eu spectra\n" << endl;
    cout << "12. CalibGeCoBa(double threshold1, double threshold2, double threshold3, bool draw) - Performs calibration on 60Co and 133Ba spectra\n" << endl;
    cout << "13. CalibGeBaEu(double threshold1, double threshold2, double threshold3, bool draw) - Performs calibration on 133Ba and 152Eu spectra\n" << endl;
    cout << "14. CalibGeCoBaEu(double threshold1, double threshold2, double threshold3, bool draw) - Performs calibration on 60Co, 133Ba and 152Eu spectra\n" << endl;
    cout << "\nThresholds are the minimum peak-to-peak height for the TSpectrum search - number between 0 and 1\n" << endl;
    cout << "Recommended thresholds: Co = 0.7, Ba = 0.77, Eu = 0.8-0.9 \n" << endl;
    cout << "draw is a boolean value to determine if the intermediate fitting is drawn\n" << endl;
    cout << "\n==============================================================\n" << endl;
}