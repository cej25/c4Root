#ifndef FRS_STRUCTURES_H
#define FRS_STRUCTURES_H

// Test file for some data structures
#include <vector>
#include <Rtypes.h>
#include <algorithm>
#include <cstddef>
#include "TMath.h"
#include <TRandom3.h>
#include <tuple>
#include "TObject.h"

/* ----------- Detectors ---------------- */
class Scintillator : public TObject
{
    public:

        void Apply_T_gates(Double_t low, Double_t high); // remove hits outside T window
        void Apply_dT_gates(Double_t threshold); // pair up hits that conform to dT window

        // Raw hits - T strips hits that aren't within gate
        std::vector<Float_t> raw_left_hits;
        std::vector<Float_t> raw_right_hits;

        // Pairs of hits that pass dT - potential for many combinations
        std::vector<std::pair<Float_t, Float_t>> hit_pairs;

        // Averages of pairs of hits
        std::vector<Float_t> hit_times; 

        ClassDef(Scintillator, 1);

};

class MUSIC : public TObject
{
    public:

        Double_t dE;
        Double_t dE_corr; // no idee
};

/* ----------------------------------------- */

// names are shit need changing blah blah
struct ParticleS1S2
{
    Double_t ts_s1;
    Double_t ts_s2;
    Double_t xpos_s1;
    Double_t xpos_s2;
    Double_t beta_s1s2;
    Double_t aoq_s1s2;
    Double_t z_music21;
};

struct ParticleS2S4
{
    Double_t ts_s2;
    Double_t ts_s4;
    Double_t xpos_s2;
    Double_t xpos_s4;
    Double_t beta_s2s4;
    Double_t aoq_s2s4;
    Double_t z_music41;
    Double_t z_music42;
};

struct ParticleData
{
    Double_t ts_s1;
    Double_t ts_s2;
    Double_t ts_s4;
    Double_t xpos_s1;
    Double_t xpos_s2;
    Double_t xpos_s4;
    Double_t beta_s1s2;
    Double_t beta_s2s4;
    Double_t aoq_s1s2;
    Double_t aoq_s2s4;
    Double_t z_music21;
    Double_t z_music41;
    Double_t z_music42;
};

class Particle
{
    public:
        Double_t ts_s1;
        Double_t ts_s2;
        Double_t ts_s4;
        Double_t xpos_s1;
        Double_t xpos_s2;
        Double_t xpos_s4;
        Double_t beta_s1s2;
        Double_t beta_s2s4;
        Double_t aoq_s1s2;
        Double_t aoq_s2s4;
        Double_t z_music21;
        Double_t z_music41;
        Double_t z_music42;
};

class MultihitPID
{
    public:

        // Calculator Functions
        void CalculateTOF_S1S2(); // do these need to be separate ? not sure
        void CalculateTOF_S2S4();
        void CalculateBetas();
        void CalculateAoQs();
        void CalculateZs();

        // Detectors
        Scintillator SciS1;
        Scintillator SciS2;
        Scintillator SciS4;
        MUSIC music21;
        MUSIC music41;
        MUSIC music42;

        Bool_t UseSciS1_x = false;

        // Gate markers - these are for TOFs...
        Double_t Low_S1S2;
        Double_t High_S1S2;
        Double_t Low_S2S4;
        Double_t High_S2S4;

        Double_t Offset_S1S2;
        Double_t Offset_S2S4;

        // TOFS
        std::vector<std::pair<Double_t, Double_t>> Hits_S1S2;
        std::vector<Double_t> TOF_S1S2;
        std::vector<std::pair<Double_t, Double_t>> Hits_S2S4;
        std::vector<Double_t> TOF_S2S4;
        std::vector<std::tuple<Double_t, Double_t, Double_t>> Hits_S1S24;
        std::vector<std::pair<Double_t, Double_t>> TOFS_S1S2S4;

        // Filters
        Bool_t Gate_S1S2 = false;
        Bool_t Gate_S2S4 = false;

        Double_t Length_S1S2;
        Double_t Length_S2S4;

        // Betas
        std::vector<Double_t> Beta_S1S2;
        std::vector<Double_t> Beta_S2S4;
        std::vector<std::pair<Double_t, Double_t>> Betas_S1S2S4;

        // Gammas
        std::vector<Double_t> Gamma_S1S2;
        std::vector<Double_t> Gamma_S2S4;
        std::vector<std::pair<Double_t, Double_t>> Gammas_S1S2S4;


        // AoQ
        // Delta etc


        // Z

        // structures... hate this naming
        std::vector<ParticleS1S2> ids_s1s2;
        std::vector<ParticleS2S4> ids_s2s4;

        std::vector<Particle> ID;




        // Constants
        TRandom3 random3;
        Float_t rand3;

        Float_t aoq_factor = 931.4940 / 299.792458;
        Float_t speed_light = 0.299792458; // m/ns
        Float_t temp_tm_to_MeV = 299.792458;
        Float_t temp_mu = 931.4940954; // MeV

};


#endif