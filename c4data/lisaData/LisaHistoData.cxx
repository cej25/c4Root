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
 *                       E.M. Gandolfo, C.E. Jones                            *
 *                               25.11.24                                     *
 ******************************************************************************/

#include "LisaHistoData.h"
#include "TString.h"
#include "TVector.h"



LisaHistoItem::LisaHistoItem()
{

}

void LisaHistoItem::SetNonGated(std::vector<Float_t> aoq_s1s2_mhtdc,
                            std::vector<Float_t> aoq_s2s4_mhtdc,
                            std::vector<Float_t> aoq_s1s2_selected_mhtdc,
                            std::vector<Float_t> aoq_s2s4_selected_mhtdc,
                            std::vector<Float_t> z21_mhtdc,
                            std::vector<Float_t> z41_mhtdc,
                            std::vector<Float_t> z42_mhtdc,
                            std::vector<Float_t> z21_selected_mhtdc,
                            std::vector<Float_t> z42_selected_mhtdc,
                            std::vector<std::vector<float>> e_layer,
                            std::vector<std::vector<float>> e_MWD_layer)
{
    AoQ_s1s2_mhtdc = aoq_s1s2_mhtdc;
    AoQ_s2s4_mhtdc = aoq_s2s4_mhtdc;
    AoQ_s1s2_selected_mhtdc = aoq_s1s2_selected_mhtdc;
    AoQ_s2s4_selected_mhtdc = aoq_s2s4_selected_mhtdc;
    Z21_mhtdc = z21_mhtdc;
    Z41_mhtdc = z41_mhtdc;
    Z42_mhtdc = z42_mhtdc;
    Z21_selected_mhtdc = z21_selected_mhtdc;
    Z42_selected_mhtdc = z42_selected_mhtdc;

    energy_layer = e_layer;
    energy_MWD_layer = e_MWD_layer;

};

void LisaHistoItem::SetGated(std::vector<Float_t> aoqs1s2_s1s2_mhtdc,
                    std::vector<Float_t> aoqs1s2_s1s2s4_mhtdc,
                    std::vector<Float_t> aoqs2s4_s1s2s4_mhtdc,
                    std::vector<Float_t> z21_s1s2_mhtdc,
                    std::vector<Float_t> z21_s1s2s4_mhtdc,
                    std::vector<Float_t> z42_s1s2s4_mhtdc, 
                    std::vector<Float_t> aoqs1s2_selected_s1s2_mhtdc,
                    std::vector<Float_t> aoqs1s2_selected_s1s2s4_mhtdc,
                    std::vector<Float_t> aoqs2s4_selected_s1s2s4_mhtdc,
                    std::vector<Float_t> z21_selected_s1s2_mhtdc,
                    std::vector<Float_t> z21_selected_s1s2s4_mhtdc,
                    std::vector<Float_t> z42_selected_s1s2s4_mhtdc,
                    std::vector<std::vector<float>> e_layer_gated,
                    std::vector<std::vector<float>> e_MWD_layer_gated)
{
    AoQs1s2_s1s2_mhtdc = aoqs1s2_s1s2_mhtdc;
    AoQs1s2_s1s2s4_mhtdc = aoqs1s2_s1s2s4_mhtdc;
    AoQs2s4_s1s2s4_mhtdc = aoqs2s4_s1s2s4_mhtdc;
    Z21_s1s2_mhtdc = z21_s1s2_mhtdc;
    Z21_s1s2s4_mhtdc = z21_s1s2s4_mhtdc;
    Z42_s1s2s4_mhtdc = z42_s1s2s4_mhtdc;

    AoQs1s2_selected_s1s2_mhtdc = aoqs1s2_selected_s1s2_mhtdc;
    AoQs1s2_selected_s1s2s4_mhtdc = aoqs1s2_selected_s1s2s4_mhtdc;
    AoQs2s4_selected_s1s2s4_mhtdc = aoqs2s4_selected_s1s2s4_mhtdc;
    Z21_selected_s1s2_mhtdc = z21_selected_s1s2_mhtdc;
    Z21_selected_s1s2s4_mhtdc = z21_selected_s1s2s4_mhtdc;
    Z42_selected_s1s2s4_mhtdc = z42_selected_s1s2s4_mhtdc;

    energy_layer_gated = e_layer_gated;
    energy_MWD_layer_gated = e_MWD_layer_gated;
}


void LisaHistoItem::ResetNonGated()
{   
    AoQ_s1s2_mhtdc = {};
    AoQ_s2s4_mhtdc = {};
    AoQ_s1s2_selected_mhtdc = {};
    AoQ_s2s4_selected_mhtdc = {};
    Z21_mhtdc = {};
    Z41_mhtdc = {};
    Z42_mhtdc = {};
    Z21_selected_mhtdc = {}; 
    Z42_selected_mhtdc = {}; 

    energy_layer = {};
    energy_MWD_layer = {};

};

void LisaHistoItem::ResetGated()
{   
    AoQs1s2_s1s2_mhtdc = {};
    AoQs1s2_s1s2s4_mhtdc = {};
    AoQs2s4_s1s2s4_mhtdc = {};
    Z21_s1s2_mhtdc = {};
    Z21_s1s2s4_mhtdc = {};
    Z42_s1s2s4_mhtdc = {};

    AoQs1s2_selected_s1s2_mhtdc = {};
    AoQs1s2_selected_s1s2s4_mhtdc = {};
    AoQs2s4_selected_s1s2s4_mhtdc = {};
    Z21_selected_s1s2_mhtdc = {};
    Z21_selected_s1s2s4_mhtdc = {};
    Z42_selected_s1s2s4_mhtdc = {};

    energy_layer_gated = {};
    energy_MWD_layer_gated = {};
};

ClassImp(LisaHistoItem)
