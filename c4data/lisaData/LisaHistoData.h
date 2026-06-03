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

#ifndef LisaHistoData_H
#define LisaHistoData_H

#include "TObject.h"
#include <vector>
#include "TString.h"
#include "TVector.h"


class LisaHistoItem : public TObject
{
    public:
        LisaHistoItem();

        void SetNonGated(std::vector<int> layers,
                    std::vector<int> x_positions,
                    std::vector<int> y_positions,
                    std::vector<Float_t> aoq_s1s2_mhtdc,
                    std::vector<Float_t> aoq_s2s4_mhtdc,
                    std::vector<Float_t> aoq_s1s2_selected_mhtdc,
                    std::vector<Float_t> aoq_s2s4_selected_mhtdc,
                    std::vector<Float_t> z21_mhtdc,
                    std::vector<Float_t> z41_mhtdc,
                    std::vector<Float_t> z42_mhtdc,
                    std::vector<Float_t> z21_selected_mhtdc,
                    std::vector<Float_t> z42_selected_mhtdc,
                    std::vector<std::vector<Float_t>> e_layer,
                    std::vector<std::vector<Float_t>> e_MWD_layer);

        void SetGated(std::vector<Float_t> aoqs1s2_s1s2_mhtdc,
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
                    std::vector<std::vector<Float_t>> e_layer_gated,
                    std::vector<std::vector<Float_t>> e_MWD_layer_gated);


        void ResetNonGated();
        void ResetGated();
     
        // LISA position
        // int layer;
        // int xpos;
        // int ypos;
        std::vector<int> layers;
        std::vector<int> xpositions;
        std::vector<int> ypositions;
    
        std::vector<int> layers_gated;
        std::vector<int> xpositions_gated;
        std::vector<int> ypositions_gated;

        // Ungated but still in corrleations with LISA!
        std::vector<Float_t> AoQ_s1s2_mhtdc;
        std::vector<Float_t> AoQ_s2s4_mhtdc;
        std::vector<Float_t> AoQ_s1s2_selected_mhtdc;
        std::vector<Float_t> AoQ_s2s4_selected_mhtdc;
        std::vector<Float_t> Z21_mhtdc;
        std::vector<Float_t> Z41_mhtdc;
        std::vector<Float_t> Z42_mhtdc;
        std::vector<Float_t> Z21_selected_mhtdc;
        std::vector<Float_t> Z42_selected_mhtdc;
   
        // FRS Gated
        std::vector<Float_t> AoQs1s2_s1s2_mhtdc;
        std::vector<Float_t> AoQs1s2_s1s2s4_mhtdc;
        std::vector<Float_t> AoQs2s4_s1s2s4_mhtdc;
        std::vector<Float_t> Z21_s1s2_mhtdc;
        std::vector<Float_t> Z21_s1s2s4_mhtdc;
        std::vector<Float_t> Z42_s1s2s4_mhtdc;

        std::vector<Float_t> AoQs1s2_selected_s1s2_mhtdc;
        std::vector<Float_t> AoQs1s2_selected_s1s2s4_mhtdc;
        std::vector<Float_t> AoQs2s4_selected_s1s2s4_mhtdc;
        std::vector<Float_t> Z21_selected_s1s2_mhtdc;
        std::vector<Float_t> Z21_selected_s1s2s4_mhtdc;
        std::vector<Float_t> Z42_selected_s1s2s4_mhtdc;

        std::vector<std::vector<Float_t>> energy_layer;
        std::vector<std::vector<Float_t>> energy_layer_gated;
        std::vector<std::vector<Float_t>> energy_MWD_layer;
        std::vector<std::vector<Float_t>> energy_MWD_layer_gated;

        ClassDef(LisaHistoItem, 1);

};

#endif