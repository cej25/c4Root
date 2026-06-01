#include "FrsStructures.h"
#include <iostream>
#include "c4Logger.h"

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


void ParticleID::CalculateTOF_S1S2()
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

void ParticleID::CalculateTOF_S2S4()
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

void ParticleID::CalculateBetas()
{
    // Beta

    if (TOFS_S1S2S4.size() > 0)
    {
        // both S1S2 and S2S4
        for (int i = 0; i < TOFS_S1S2S4.size(); i++)
        {
            Double_t beta_s1s2 = Length_S1S2 / TOFS_S1S2S4.at(i).first / speed_light;
            Double_t beta_s2s4 = Length_S2S4 / TOFS_S1S2S4.at(i).second / speed_light;
            if (beta_s1s2 > 0.0 && beta_s1s2 < 1.0 && beta_s2s4 > 0.0 && beta_s2s4 < 1.0)
            {
                Betas_S1S2S4.emplace_back(std::make_pair(beta_s1s2, beta_s2s4));

                Double_t gamma_s1s2 = (1. / sqrt(1. - TMath::Power(beta_s1s2, 2)));
                Double_t gamma_s2s4 = (1. / sqrt(1. - TMath::Power(beta_s2s4, 2)));

                Gammas_S1S2S4.emplace_back(std::make_pair(gamma_s1s2, gamma_s2s4));
            }
        }
    }
    else if (TOF_S1S2.size() > 0)
    {
        // only S1S2
        for (int i = 0; i < TOF_S1S2.size(); i++)
        {
            Double_t beta_s1s2 = Length_S1S2 / TOF_S1S2.at(i) / speed_light;
            if (beta_s1s2 > 0.0 && beta_s1s2 < 1.0)
            {
                Beta_S1S2.emplace_back(beta_s1s2);

                Double_t gamma_s1s2 = (1. / sqrt(1. - TMath::Power(beta_s1s2, 2)));

                Gamma_S1S2.emplace_back(gamma_s1s2);
            }
        }
    }
    else if (TOF_S2S4.size() > 0)
    {
        // only S2S4
        for (int i = 0; i < TOF_S2S4.size(); i++)
        {
            Double_t beta_s2s4 = Length_S2S4 / TOF_S2S4.at(i) / speed_light;
            if (beta_s2s4 > 0.0 && beta_s2s4 < 1.0)
            {
                Beta_S2S4.emplace_back(beta_s2s4);

                Double_t gamma_s2s4 = (1. / sqrt(1. - TMath::Power(beta_s2s4, 2)));

                Gamma_S2S4.emplace_back(gamma_s2s4);
            }
        }
    }
};

void ParticleID::CalculateAoQs()
{

    for (int i = 0; i < Betas_S1S2S4.size(); i++)
    {
        if (Position_S2 > -200 && Position_S2 < 200 && Position_S1 > -120 && Position_S1 < 120) // dunno yet
        {
            if (UseSciS1_x == 0) delta = Position_S2 / (-1.0 * dispersion_0 * 1000.0);
            else if (UseSciS1_x == 1) delta = (Position_S2 - (Position_S1 * magnification_5)) / (-1.0 * dispersion_5 * 1000.0);
            else c4LOG(fatal, "Invalid SciS1_X use selection. Check FRS setup file!");

            // beta conditional already true - tof condition already true
            // S1_x
            // S1_a
            // S2_S1S2_x
            // S2_S1S2_a
            // TOF_S1S2
            // BETA_S1S2
            // AoQ = mean_brho_s1s2 * (1. + id_mhtdc_delta_s1s2[i]) * temp_tm_to_MeV / (temp_mu * temp_id_mhtdc_beta_s1s2[i] * id_mhtdc_gamma_s1s2[i])
            // AoQ_corr = AoQ - id->a1AoQCorr * id_a2;
            // selected L/R hits --> can we strip based on beta selections? 
        }
    }

    for (int i = 0; i < hits_in_s1s2; i++)
    {
        //int count = i * hits_in_s1x_tofs1s2_selected + j;

        if (temp_s2x_mhtdc[i] > -200 && temp_s2x_mhtdc[i] < 200 && temp_s1x_mhtdc[i] > -120 && temp_s1x_mhtdc[i] < 120)
        {
            if (id->use_sc11x == 0) id_mhtdc_delta_s1s2[i] = temp_s2x_mhtdc[i] / (-1.0 * frs->dispersion[0] * 1000.0); //1000 is dispertsion from meter to mm. -1.0 is sign definition.
            else if (id->use_sc11x == 1) id_mhtdc_delta_s1s2[i] = (temp_s2x_mhtdc[i]  - (temp_s1x_mhtdc[i] * frs->magnification[5])) / (-1.0 * frs->dispersion[5] * 1000.0); //1000 is dispertsion from meter to mm. -1.0 is sign definition.
            else c4LOG(fatal, "Invalid Sc11 use selection. Check FRS setup file!");

            if (temp_id_mhtdc_beta_s1s2[i] > 0.0 && temp_id_mhtdc_beta_s1s2[i] < 1.0 && temp_id_mhtdc_tof_s1s2[i] > 0.0)
            {
                // c4LOG(info, " id_a2 = " << id_a2); 
                s1x_mhtdc.emplace_back(temp_s1x_mhtdc[i]);
                s1a_mhtdc.emplace_back(temp_a1);
                s2x_s1s2_mhtdc.emplace_back(temp_s2x_mhtdc[i]);
                s2a_s1s2_mhtdc.emplace_back(temp_a2);
                id_mhtdc_tof_s1s2.emplace_back(temp_id_mhtdc_tof_s1s2[i]);
                id_mhtdc_beta_s1s2.emplace_back(temp_id_mhtdc_beta_s1s2[i]);
                id_mhtdc_aoq_s1s2.emplace_back(mean_brho_s1s2 * (1. + id_mhtdc_delta_s1s2[i]) * temp_tm_to_MeV / (temp_mu * temp_id_mhtdc_beta_s1s2[i] * id_mhtdc_gamma_s1s2[i]));
                id_mhtdc_aoq_corr_s1s2.emplace_back(id_mhtdc_aoq_s1s2.back() - id->a1AoQCorr * id_a2);
                sci21l_hits_tofs1s2_pos_selected.emplace_back(sci21l_hits_tofs1s2_selected[i]);
                sci21r_hits_tofs1s2_pos_selected.emplace_back(sci21r_hits_tofs1s2_selected[i]);
                
            }
        }  
    }

};

// void ParticleID::CalculateZs()
// {

// }


// we need to hold the X associated with correct positions.. 
// we need to hold everything together
// we need... 
// std::vector<std::tuple<avg_ts, position_x1, position_x2, beta_s1s2, aoq_s1s2, z_music21>
// std::vector<std::tuple<avg_ts, position_x2, position_x4, beta_s2s4, aoq_s2s4, z_music41, z_music42>
// std::vector<std::tuple<avg_ts, position_x1, position_x2, position_x4, beta_s1s2, beta_s2s4, aoq_s1s2, aoq_s2s4, z_music21, z_music41, z_music42>