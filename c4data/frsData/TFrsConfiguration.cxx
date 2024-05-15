// c4
#include "TFrsConfiguration.h"

TFrsConfiguration* TFrsConfiguration::instance = nullptr;
std::string TFrsConfiguration::config_path = "blank";

TFRSParameter* TFrsConfiguration::ffrs;
TMWParameter* TFrsConfiguration::fmw;
TTPCParameter* TFrsConfiguration::ftpc;
TMUSICParameter* TFrsConfiguration::fmusic;
TLABRParameter* TFrsConfiguration::flabr;
TSCIParameter* TFrsConfiguration::fsci;
TIDParameter* TFrsConfiguration::fid;
TSIParameter* TFrsConfiguration::fsi;
TMRTOFMSParameter* TFrsConfiguration::fmrtof;
TRangeParameter* TFrsConfiguration::frange;

Double_t TFrsConfiguration::fMin_Z = 0., TFrsConfiguration::fMax_Z = 100.;
Double_t TFrsConfiguration::fMin_AoQ = 2., TFrsConfiguration::fMax_AoQ = 3.;
Double_t TFrsConfiguration::fMin_x2 = -100., TFrsConfiguration::fMax_x2 = 100.;
Double_t TFrsConfiguration::fMin_x4 = -100., TFrsConfiguration::fMax_x4 = 100.;
Double_t TFrsConfiguration::fMin_a2 = -100., TFrsConfiguration::fMax_a2 = 100.;
Double_t TFrsConfiguration::fMin_a4 = -100., TFrsConfiguration::fMax_a4 = 100.;
Double_t TFrsConfiguration::fMin_y2 = -100., TFrsConfiguration::fMax_y2 = 100.;
Double_t TFrsConfiguration::fMin_y4 = -100., TFrsConfiguration::fMax_y4 = 100.;
Double_t TFrsConfiguration::fMin_b2 = -100., TFrsConfiguration::fMax_b2 = 100.;
Double_t TFrsConfiguration::fMin_b4 = -100., TFrsConfiguration::fMax_b4 = 100.;
Double_t TFrsConfiguration::fMin_dE = 10., TFrsConfiguration::fMax_dE = 100.;
Double_t TFrsConfiguration::fMin_dEoQ = 0.1, TFrsConfiguration::fMax_dEoQ = 0.8;
Double_t TFrsConfiguration::fMin_dE_Music1 = 0., TFrsConfiguration::fMax_dE_Music1 = 4000.;
Double_t TFrsConfiguration::fMin_dE_Music2 = 0., TFrsConfiguration::fMax_dE_Music2 = 4000.;

//travMUSIC
Double_t TFrsConfiguration::fMin_dE_travMusic = 0., TFrsConfiguration::fMax_dE_travMusic = 60000.;

TFrsConfiguration::TFrsConfiguration()
{

}

void TFrsConfiguration::SetParameters(
        TFRSParameter* frs,
        TMWParameter* mw,
        TTPCParameter* tpc,
        TMUSICParameter* music,
        TLABRParameter* labr,
        TSCIParameter* sci,
        TIDParameter* id,
        TSIParameter* si,
        TMRTOFMSParameter* mrtof,
        TRangeParameter* range)
{
    ffrs = frs;
    fmw = mw;
    ftpc = tpc;
    fmusic = music;
    flabr = labr;
    fsci = sci;
    fid = id;
    fsi = si;
    fmrtof = mrtof;
    frange = range;
}

void TFrsConfiguration::Set_Z_range(Double_t min, Double_t max)
{
    fMin_Z = min;
    fMax_Z = max;
}

void TFrsConfiguration::Set_AoQ_range(Double_t min, Double_t max)
{
    fMin_AoQ = min;
    fMax_AoQ = max;
}

void TFrsConfiguration::Set_x2_range(Double_t min, Double_t max)
{
    fMin_x2 = min;
    fMax_x2 = max;
}

void TFrsConfiguration::Set_y2_range(Double_t min, Double_t max)
{
    fMin_y2 = min;
    fMax_y2 = max;
}

void TFrsConfiguration::Set_a2_range(Double_t min, Double_t max)
{
    fMin_a2 = min;
    fMax_a2 = max;
}

void TFrsConfiguration::Set_b2_range(Double_t min, Double_t max)
{
    fMin_b2 = min;
    fMax_b2 = max;
}

void TFrsConfiguration::Set_x4_range(Double_t min, Double_t max)
{
    fMin_x4 = min;
    fMax_x4 = max;
}

void TFrsConfiguration::Set_y4_range(Double_t min, Double_t max)
{
    fMin_y4 = min;
    fMax_y4 = max;
}

void TFrsConfiguration::Set_a4_range(Double_t min, Double_t max)
{
    fMin_a4 = min;
    fMax_a4 = max;
}
void TFrsConfiguration::Set_b4_range(Double_t min, Double_t max)
{
    fMin_b4 = min;
    fMax_b4 = max;
}

void TFrsConfiguration::Set_dEdeg_range(Double_t min, Double_t max)
{
    fMin_dE = min;
    fMax_dE = max;
}

void TFrsConfiguration::Set_dEdegoQ_range(Double_t min, Double_t max)
{
    fMin_dEoQ = min;
    fMax_dEoQ = max;
}

void TFrsConfiguration::Set_dE_Music1_range(Double_t min, Double_t max)
{
    fMin_dE_Music1 = min;
    fMax_dE_Music1 = max;
}
void TFrsConfiguration::Set_dE_Music2_range(Double_t min, Double_t max)
{
    fMin_dE_Music2 = min;
    fMax_dE_Music2 = max;
}


// read files and stuff