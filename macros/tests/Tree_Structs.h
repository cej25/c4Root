// class FrsHitItem : public TObject
// {
//     public:
//         FrsHitItem();

//         void SetAll(uint64_t wr_t,
//                     uint16_t tpat,
//                     uint64_t wr_travmus,
//                     Float_t x2,
//                     Float_t y2,
//                     Float_t x4,
//                     Float_t y4,
//                     Float_t a2,
//                     Float_t b2,
//                     Float_t a4,
//                     Float_t b4,
//                     Float_t AoQ,
//                     Float_t AoQ_corr,
//                     Float_t z,
//                     Float_t z2,
//                     Float_t z_travmus,
//                     Float_t beta,
//                     Float_t dEdeg,
//                     Float_t dEdegoQ,
//                     Float_t* rho,
//                     Float_t* brho,
//                     Float_t* music_dE,
//                     Float_t* music_dE_cor,
//                     Float_t travmusic_dE,
//                     Float_t travmusic_dE_cor,
//                     Float_t* sci_e,
//                     Float_t* sci_l,
//                     Float_t* sci_r,
//                     Float_t* sci_x,
//                     Float_t* sci_tof,
//                     Float_t* sci_tof_calib,
//                     Float_t sci_tof2,
//                     uint32_t time_in_ms,
//                     uint32_t ibin_for_s,
//                     uint32_t ibin_for_100ms,
//                     uint32_t ibin_for_spill,
//                     uint32_t* increase_sc_temp_main,
//                     uint32_t* increase_sc_temp_user,
//                     uint32_t increase_sc_temp2,
//                     uint32_t increase_sc_temp3,
//                     uint32_t extraction_time_ms,
//                     uint32_t ibin_clean_for_s,
//                     uint32_t ibin_clean_for_100ms,
//                     uint32_t ibin_clean_for_spill);
//         void Reset();

//         uint64_t Get_wr_t() const;
//         uint16_t Get_tpat() const;
//         uint64_t Get_wr_travmus() const;
//         Float_t Get_ID_x2() const; //
//         Float_t Get_ID_y2() const; //
//         Float_t Get_ID_x4() const;
//         Float_t Get_ID_y4() const;
//         Float_t Get_ID_a2() const;
//         Float_t Get_ID_b2() const;
//         Float_t Get_ID_a4() const;
//         Float_t Get_ID_b4() const;
//         Float_t Get_ID_AoQ() const;
//         Float_t Get_ID_AoQ_corr() const;
//         Float_t Get_ID_z() const; //
//         Float_t Get_ID_z2() const; //
//         Float_t Get_ID_z_travmus() const; //
//         Float_t Get_ID_beta() const;
//         Float_t Get_ID_dEdeg() const;
//         Float_t Get_ID_dEdegoQ() const;
//         Float_t Get_ID_rho(int index) const;
//         Float_t Get_ID_brho(int index) const; 
//         Float_t Get_music_dE(int index) const; //index 0 = music 1
//         Float_t Get_music_dE_cor(int index) const; 
//         Float_t Get_travmusic_dE() const; //
//         Float_t Get_travmusic_dE_cor() const;
//         Float_t Get_sci_e(int index) const;
//         Float_t Get_sci_l(int index) const;
//         Float_t Get_sci_r(int index) const;
//         Float_t Get_sci_x(int index) const;
//         Float_t Get_sci_tof(int index) const;
//         Float_t Get_sci_tof_calib(int index) const;
       

//         ClassDefNV(FrsHitItem, 2);

//     private:

//         uint64_t fwr_t;
//         uint16_t ftpat;
//         uint64_t fwr_travmus;

//         // ids
//         Float_t fID_x2;
//         Float_t fID_y2;
//         Float_t fID_x4;
//         Float_t fID_y4;
//         Float_t fID_a2;
//         Float_t fID_b2;
//         Float_t fID_a4;
//         Float_t fID_b4;
//         Float_t fID_AoQ;
//         Float_t fID_AoQ_corr;
//         Float_t fID_z;
//         Float_t fID_z2;
//         Float_t fID_z_travmus;
//         Float_t fID_beta;
//         Float_t fID_dEdeg;
//         Float_t fID_dEdegoQ;
//         Float_t fID_rho[2]; // [2]
//         Float_t fID_brho[2]; // [2]

//         // scitillators / energy loss
//         // we can't store this stuff in a tree as a pointer.....
//         Float_t fmusic_dE[2]; // [2] // CEJ: 2? 3 for more musics?
//         Float_t fmusic_dE_cor[2]; // [2]
//         Float_t ftravmusic_dE;
//         Float_t ftravmusic_dE_cor;
//         Float_t fsci_e[6]; // [6] // CEJ: by chance we need [6]. 5->2 but 10->5 (so 6 elements)
//         Float_t fsci_l[6]; // [6]
//         Float_t fsci_r[6]; // [6]
//         Float_t fsci_x[6]; // [6]
//         Float_t fsci_tof2; // should we look at passing all the tof calcs?
//         Float_t fsci_tof[6]; // [6]
//         Float_t fsci_tof_calib[6]; // [6]

//         // scalers
//         uint32_t ftime_in_ms;
//         uint32_t fibin_for_s;
//         uint32_t fibin_for_100ms;
//         uint32_t fibin_for_spill;
//         uint32_t fincrease_sc_temp_main[32]; // [32]
//         uint32_t fincrease_sc_temp_user[32]; // [32]
//         uint32_t fincrease_sc_temp2;
//         uint32_t fincrease_sc_temp3;
//         uint32_t fextraction_time_ms;
//         uint32_t fibin_clean_for_s;
//         uint32_t fibin_clean_for_100ms;
//         uint32_t fibin_clean_for_spill;

// };
