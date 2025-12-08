#include "FrsStructures.h"
#include <iostream>

void Scintillator::Apply_T_gates(Double_t low, Double_t high)
{
    auto outside_gate =[low, high] (Double_t t) { return (t < low || t > high); /* remove hits outside gate */ };

    raw_left_hits.erase(std::remove_if(raw_left_hits.begin(), raw_left_hits.end(), outside_gate), raw_left_hits.end());
    raw_right_hits.erase(std::remove_if(raw_right_hits.begin(), raw_right_hits.end(), outside_gate), raw_right_hits.end());

};

void Scintillator::Apply_dT_gates(Double_t threshold)
{
    hit_pairs.clear();
    hit_times.clear();

    // Reserve approximate capacity
    hit_pairs.reserve(raw_left_hits.size());
    hit_times.reserve(raw_left_hits.size());

    for (size_t i = 0; i < raw_left_hits.size(); ++i)
    {
        for (size_t j = 0; j < raw_right_hits.size(); ++j)
        {
            Double_t L = raw_left_hits[i];
            Double_t R = raw_right_hits[j];
            Double_t dT = L - R;

            // Correct: symmetric gate |dT| < threshold
            if (TMath::Abs(dT) < threshold)
            {
                hit_pairs.push_back(std::make_pair(L, R));

                // average timestamp
                Double_t t_avg = 0.5 * (L + R);
                hit_times.push_back(t_avg);
            }
        }
    }
};


void TimeOfFlight::CalculateTOF_S1S2()
{
    for (int i = 0; i < SciS1.hit_times.size(); i++)
    {
        for (int j = 0; j < SciS2.hit_times.size(); j++)
        {
            rand3 = random3.Uniform(-0.5,0.5) * 0.025;
            Double_t TOF = SciS2.hit_times.at(j) - SciS1.hit_times.at(i) + rand3 + Offset_S1S2;

            if (Gate_S1S2)
            {
                if (TOF > Low_S1S2 && TOF < High_S1S2)
                {
                    Hits_S1S2.emplace_back(std::make_pair(SciS1.hit_times.at(i), SciS2.hit_times.at(j)));
                    TOF_S1S2.emplace_back(TOF);
                }
            }
            else
            {
                Hits_S1S2.emplace_back(std::make_pair(SciS1.hit_times.at(i), SciS2.hit_times.at(j)));
                TOF_S1S2.emplace_back(TOF);
            }
        }
    }

    return;
};

void TimeOfFlight::CalculateTOF_S2S4()
{
    if (SciS1.hit_times.size() > 0)
    {
        for (int i = 0; i < TOF_S1S2.size(); i++)
        {
            for (int j = 0; j < SciS4.hit_times.size(); j++)
            {
                rand3 = random3.Uniform(-0.5,0.5) * 0.025;
                Double_t TOF = SciS4.hit_times.at(j) - Hits_S1S2.at(i).second + rand3 + Offset_S2S4;

                if (Gate_S2S4)
                {
                    if (TOF > Low_S2S4 && TOF < High_S2S4)
                    {
                        Hits_S2S4.emplace_back(std::make_pair(Hits_S1S2.at(i).second, SciS4.hit_times.at(j)));
                        TOF_S2S4.emplace_back(TOF);
                        Hits_S1S24.emplace_back(std::make_tuple(Hits_S1S2.at(i).first, Hits_S1S2.at(i).second, SciS4.hit_times.at(j)));
                        TOFS_S1S2S4.emplace_back(std::make_pair(TOF_S1S2.at(i), TOF));
                    }
                }
                else
                {
                    Hits_S2S4.emplace_back(std::make_pair(Hits_S1S2.at(i).second, SciS4.hit_times.at(j)));
                    TOF_S2S4.emplace_back(TOF);
                    Hits_S1S24.emplace_back(std::make_tuple(Hits_S1S2.at(i).first, Hits_S1S2.at(i).second, SciS4.hit_times.at(j)));
                    TOFS_S1S2S4.emplace_back(std::make_pair(TOF_S1S2.at(i), TOF));
                }
            }
        } 
    }
    else
    {
        for (int i = 0; i < SciS2.hit_times.size(); i++)
        {
            
            for (int j = 0; j < SciS4.hit_times.size(); j++)
            {
                rand3 = random3.Uniform(-0.5,0.5) * 0.025;
                Double_t TOF = SciS4.hit_times.at(j) - SciS2.hit_times.at(i) + rand3 + Offset_S2S4;

                if (Gate_S2S4)
                {
                    if (TOF > Low_S2S4 && TOF < High_S2S4)
                    {
                        Hits_S2S4.emplace_back(std::make_pair(SciS2.hit_times.at(i), SciS4.hit_times.at(j)));
                        TOF_S2S4.emplace_back(TOF);
                    }
                }
                else
                {
                    Hits_S2S4.emplace_back(std::make_pair(SciS2.hit_times.at(i), SciS4.hit_times.at(j)));
                    TOF_S2S4.emplace_back(TOF);
                }
            }
        }
    }

    return;
       
};
