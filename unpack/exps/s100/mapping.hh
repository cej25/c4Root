// ::::::: Main Crate :::::::::::::::::::
SIGNAL(SPILL_ON, frsmain.spill_on.spillon, DATA8);
SIGNAL(SPILL_OFF, frsmain.spill_off.spilloff, DATA8);

SIGNAL(ZERO_SUPPRESS: SCALERS1_32);
SIGNAL(SCALERS1_1, frsmain.data.v830.data[0], SCALERS1_32, frsmain.data.v830.data[31], DATA32);

SIGNAL(ZERO_SUPPRESS: SCI_TAC_DE_32);
SIGNAL(SCI_TAC_DE_1, frsmain.data.v792.data[0], SCI_TAC_DE_32, frsmain.data.v792.data[31], DATA32);

SIGNAL(ZERO_SUPPRESS_MULTI(128): SCI_MHTDC_T_16);
SIGNAL(SCI_MHTDC_T_1, frsmain.data.v1290.data[0], SCI_MHTDC_T_16, frsmain.data.v1290.data[15], DATA24);
SIGNAL(ZERO_SUPPRESS_MULTI(128): SCI_MHTDC_LOT_16);
SIGNAL(SCI_MHTDC_LOT_1, frsmain.data.v1290.leadOrTrail[0], SCI_MHTDC_LOT_16, frsmain.data.v1290.leadOrTrail[15], DATA8);

SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC1_T_8);
SIGNAL(MUSIC1_T_1, frsmain.data.v1290.data[16], MUSIC1_T_8, frsmain.data.v1290.data[23], DATA24);
SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC1_LOT_8);
SIGNAL(MUSIC1_LOT_1, frsmain.data.v1290.leadOrTrail[16], MUSIC1_LOT_8, frsmain.data.v1290.leadOrTrail[23], DATA8);

SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC2_T_8);
SIGNAL(MUSIC2_T_1, frsmain.data.v1290.data[24], MUSIC2_T_8, frsmain.data.v1290.data[31], DATA24);
SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC2_LOT_8);
SIGNAL(MUSIC2_LOT_1, frsmain.data.v1290.leadOrTrail[24], MUSIC2_LOT_8, frsmain.data.v1290.leadOrTrail[31], DATA8);
// :::::::::::::::::::::::::::::::::::::::

// ::::::: TPC Crate :::::::::::::::::::::
// order preserved from FRS Go4
// 0: TPC21, 1: TPC22, 2: TPC23, 3: TPC24, 4: TPC24
// 7: TPC31
// 5: TPC41, 6: TPC42
SIGNAL(ZERO_SUPPRESS: TPC_ADC7_32); // 0 = S2, 1 = S3, 2 = S4
SIGNAL(TPC_ADC1_1, frstpc.data.v775.data[0], TPC_ADC1_8, frstpc.data.v775.data[7], DATA24);
SIGNAL(TPC_ADC2_1, frstpc.data.v775.data[8], TPC_ADC2_8, frstpc.data.v775.data[15], DATA24);
SIGNAL(TPC_ADC3_1, frstpc.data.v775.data[16], TPC_ADC3_8, frstpc.data.v775.data[23], DATA24);
SIGNAL(TPC_ADC4_1, frstpc.data.v775.data[24], TPC_ADC4_8, frstpc.data.v775.data[31], DATA24);
SIGNAL(TPC_ADC5_1, frstpc.data.v785.data[0], TPC_ADC5_8, frstpc.data.v785.data[7], DATA24);
SIGNAL(TPC_ADC6_1, frstpc.data.v785.data[8], TPC_ADC6_8, frstpc.data.v785.data[15], DATA24);
SIGNAL(TPC_ADC7_1, frstpc.data.v785.data[16], TPC_ADC7_8, frstpc.data.v785.data[23], DATA24);

SIGNAL(ZERO_SUPPRESS_MULTI(128): TPC_TDC_T_128);
SIGNAL(TPC_TDC_T_1, frstpc.data.v1190.data[0], TPC_TDC_T_128, frstpc.data.v1190.data[127], DATA24);
SIGNAL(ZERO_SUPPRESS_MULTI(128): TPC_TDC_LOT_128);
SIGNAL(TPC_TDC_LOT_1, frstpc.data.v1190.leadOrTrail[0], TPC_TDC_LOT_128, frstpc.data.v1190.leadOrTrail[127], DATA8);

// ::::::: User Crate :::::::::::::::::::

// ::::::: TPAT Crate :::::::::::::::::::
