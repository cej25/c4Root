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


class Scintillator
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

};

// don't love the name
class TimeOfFlight
{
    public:

        void CalculateTOF_S1S2();
        void CalculateTOF_S2S4();
        // void CalculateTOF_S1S3();
        // void CalculateTOF_S4S8();

        // potentially need to be pointers
        Scintillator SciS1;
        Scintillator SciS2;
        Scintillator SciS4;
        // Scintillator SciS3;
        // Scintillator SciS8;

        // Gate markers
        Double_t Low_S1S2;
        Double_t High_S1S2;
        Double_t Low_S2S4;
        Double_t High_S2S4;

        Double_t Offset_S1S2;
        Double_t Offset_S2S4;

        std::vector<std::pair<Double_t, Double_t>> Hits_S1S2;
        std::vector<Double_t> TOF_S1S2;
        std::vector<std::pair<Double_t, Double_t>> Hits_S2S4;
        std::vector<Double_t> TOF_S2S4;
        std::vector<std::tuple<Double_t, Double_t, Double_t>> Hits_S1S24;
        std::vector<std::pair<Double_t, Double_t>> TOFS_S1S2S4;

        // Filters
        Bool_t Gate_S1S2 = false;
        Bool_t Gate_S2S4 = false;

        TRandom3 random3;
        Float_t rand3;

};

#endif