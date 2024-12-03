SIGNAL(SPILL_ON, frsmain.spill_on.spillon, DATA8);
SIGNAL(SPILL_OFF, frsmain.spill_off.spilloff, DATA8);

// maybe rename since they could become "{other crate}scalers i suppose?"
SIGNAL(ZERO_SUPPRESS: MAIN_SCALERS_32);
SIGNAL(ZERO_SUPPRESS: SCI_DE_TAC_32);
SIGNAL(ZERO_SUPPRESS_MULTI(128): SCI_T_MHTDC_16);
SIGNAL(ZERO_SUPPRESS_MULTI(128): SCI_LOT_MHTDC_16);
SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC1_T_8);
SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC1_LOT_T_8);
SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC2_T_8);
SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC2_LOT_T_8);

SIGNAL(MAIN_SCALERS_1, frsmain.data.v830.data[0], MAIN_SCALERS_32, frsmain.data.v830.data[31], DATA32);
SIGNAL(SCI_DE_TAC_1, frsmain.data.v792.data[0], SCI_DE_TAC_32, frsmain.data.v792.data[31], DATA32);
SIGNAL(SCI_DE_GEO, frsmain.data.v792.geo, DATA8);
SIGNAL(SCI_T_MHTDC_1, frsmain.data.v1290.data[0], SCI_T_MHTDC_16, frsmain.data.v1290.data[15], DATA24);
SIGNAL(SCI_LOT_MHTDC_1, frsmain.data.v1290.leadOrTrail[0], SCI_LOT_MHTDC_16, frsmain.data.v1290.leadOrTrail[15], DATA8);
SIGNAL(MUSIC1_T_1, frsmain.data.v1290.data[16], MUSIC1_T_8, frsmain.data.v1290.data[23], DATA24);
SIGNAL(MUSIC1_LOT_T_1, frsmain.data.v1290.leadOrTrail[16], MUSIC1_LOT_T_8, frsmain.data.v1290.leadOrTrail[23], DATA8);
SIGNAL(MUSIC2_T_1, frsmain.data.v1290.data[24], MUSIC2_T_8, frsmain.data.v1290.data[31], DATA24);
SIGNAL(MUSIC2_LOT_T_1, frsmain.data.v1290.leadOrTrail[24], MUSIC2_LOT_T_8, frsmain.data.v1290.leadOrTrail[31], DATA8);