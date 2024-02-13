#ifndef FrsHitData_H
#define FrsHitData_H

#include "../../config/frs_config.h"
#include <vector>
#include "TObject.h"

class FrsHitData : public TObject
{
    public:
        FrsHitData();

        // I think some of this spill stuff should be floats
        FrsHitData(uint64_t WR_TS,
                uint32_t time_in_ms, 
                uint32_t ibin_for_s, 
                uint32_t ibin_for_100ms,
                uint32_t ibin_for_spill,
                uint32_t* increase_sc_temp_main,
                uint32_t* increase_sc_temp_user, 
                uint32_t increase_sc_temp2,
                uint32_t increase_sc_temp3,
                uint32_t extraction_time_ms, 
                uint32_t ibin_clean_for_s, 
                uint32_t ibin_clean_for_100ms,
                uint32_t ibin_clean_for_spill,
                Float_t id_x2,
                Float_t id_x4,
                Float_t id_AoQ,
                Float_t id_AoQ_corr,
                Float_t id_z,
                Float_t id_z2,
                Float_t id_beta);

        ~FrsHitData();

        inline const uint64_t Get_WR() const { return fWR_TS; }
        inline const Float_t Get_ID_x2() const { return fID_x2; }
        inline const Float_t Get_ID_y2() const { return fID_x2; }
        inline const Float_t Get_ID_a2() const { return fID_a2; }
        inline const Float_t Get_ID_b2() const { return fID_b2; }
        inline const Float_t Get_ID_x4() const { return fID_x4; }
        inline const Float_t Get_ID_y4() const { return fID_y4; }
        inline const Float_t Get_ID_a4() const { return fID_a4; }
        inline const Float_t Get_ID_b4() const { return fID_b4; }
        inline const Float_t Get_ID_AoQ() const { return fID_AoQ; }
        inline const Float_t Get_ID_AoQ_corr() const { return fID_AoQ_corr; }
        inline const Float_t Get_ID_z() const { return fID_z; }
        inline const Float_t Get_ID_z2() const { return fID_z2; }
        inline const Float_t Get_ID_beta() const { return fID_beta; }
        inline const Float_t Get_ID_dEdegoQ() const { return fID_dEdegoQ; }
        inline const Float_t Get_ID_dEdeg() const { return fID_dEdeg; }

        // CEJ: does this stuff come from hit or cal? check
        inline const Float_t Get_music_dE(int channel) const { return fmusic_dE[channel]; }
        inline const Float_t Get_sci_e(int channel) const { return fsci_e[channel]; }
        inline const Float_t Get_sci_tof2() const { return fsci_tof2; }
        inline const Float_t Get_sci_l(int channel) const { return fsci_l[channel]; }
        inline const Float_t Get_sci_r(int channel) const { return fsci_r[channel]; }

        // MHTDC
        inline const Float_t Get_ID_z_mhtdc(int mhit) const { return fID_z_mhtdc[mhit]; }
        inline const Float_t Get_ID_z2_mhtdc(int mhit) const { return fID_z2_mhtdc[mhit]; }
        inline const Float_t Get_ID_AoQ_mhtdc(int mhit) const { return fID_AoQ_mhtdc[mhit]; }
        inline const Float_t Get_ID_AoQ_corr_mhtdc(int mhit) const { return fID_AoQ_corr_mhtdc[mhit]; }
        inline const Float_t Get_ID_dEdeg_mhtdc(int mhit) const { return fID_dEdeg_mhtdc[mhit]; }
        inline const Float_t Get_ID_dEdegoQ_mhtdc(int mhit) const { return fID_dEdegoQ_mhtdc[mhit]; }

        inline uint32_t Get_time_in_ms() { return ftime_in_ms; }
        inline uint32_t Get_ibin_for_s() { return fibin_for_s; }
        inline uint32_t Get_ibin_for_100ms() { return fibin_for_100ms; }
        inline uint32_t Get_ibin_for_spill() { return fibin_for_spill; }
        inline uint32_t* Get_increase_sc_temp_main() { return fincrease_sc_temp_main; }
        inline uint32_t* Get_increase_sc_temp_user() { return fincrease_sc_temp_user; }
        inline uint32_t Get_increase_sc_temp2() { return fincrease_sc_temp2; }
        inline uint32_t Get_increase_sc_temp3() { return fincrease_sc_temp3; }
        inline uint32_t Get_extraction_time_ms() { return fextraction_time_ms; }
        inline uint32_t Get_ibin_clean_for_s() { return fibin_clean_for_s; }
        inline uint32_t Get_ibin_clean_for_100ms() { return fibin_clean_for_100ms; }
        inline uint32_t Get_ibin_clean_for_spill() { return fibin_clean_for_spill; }

    protected:

        uint64_t fWR_TS;
        Float_t fID_x2;
        Float_t fID_y2;
        Float_t fID_x4;
        Float_t fID_y4;
        Float_t fID_a2;
        Float_t fID_b2;
        Float_t fID_a4;
        Float_t fID_b4;
        Float_t fID_AoQ;
        Float_t fID_AoQ_corr;
        Float_t fID_z;
        Float_t fID_z2;
        Float_t fID_beta;
        Float_t fID_dEdegoQ;
        Float_t fID_dEdeg;
       
        Float_t fmusic_dE[2]; // CEJ: 2? 3 for more musics?
        Float_t fsci_e[6]; // CEJ: 6???? check!!
        Float_t fsci_tof2;
        Float_t fsci_l[3];
        Float_t fsci_r[3];

        // MHTDC
        // these are going to be vectors....damn it
        std::vector<Float_t> fID_z_mhtdc;//[MAX_MHTDC_MULT];
        std::vector<Float_t> fID_z2_mhtdc;
        std::vector<Float_t> fID_AoQ_mhtdc;//[MAX_MHTDC_MULT];
        std::vector<Float_t> fID_AoQ_corr_mhtdc;//[MAX_MHTDC_MULT];
        std::vector<Float_t> fID_dEdeg_mhtdc;
        std::vector<Float_t> fID_dEdegoQ_mhtdc;

        uint32_t ftime_in_ms;
        uint32_t fibin_for_s;
        uint32_t fibin_for_100ms;
        uint32_t fibin_for_spill;
        uint32_t fincrease_sc_temp_main[32];
        uint32_t fincrease_sc_temp_user[32];
        uint32_t fincrease_sc_temp2;
        uint32_t fincrease_sc_temp3;
        uint32_t fextraction_time_ms;
        uint32_t fibin_clean_for_s;
        uint32_t fibin_clean_for_100ms;
        uint32_t fibin_clean_for_spill;
    
    public:
        ClassDef(FrsHitData, 1)

};


#endif