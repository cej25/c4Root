// ::::::: Main Crate :::::::::::::::::::
SIGNAL(SPILL_ON, frsmain.spill_on.spillon, DATA8);
SIGNAL(SPILL_OFF, frsmain.spill_off.spilloff, DATA8);

SIGNAL(ZERO_SUPPRESS: SCALERS2_32);
//SIGNAL(SCALERS1_1, frsmain.data.v830.data[0], SCALERS1_32, frsmain.data.v830.data[31], DATA32);
SIGNAL(SCALERS1_1, frsmain.data.v830.scalers[0], SCALERS1_32, frsmain.data.v830.scalers[31], DATA32);

SIGNAL(ZERO_SUPPRESS: SCI_TAC_DE_32);
SIGNAL(SCI_TAC_DE_1, frsmain.data.v792.data[0], SCI_TAC_DE_32, frsmain.data.v792.data[31], DATA24);

SIGNAL(ZERO_SUPPRESS_MULTI(128): SCI_MHTDC_T_32);
SIGNAL(SCI_MHTDC_T_1, frsmain.data.v1290.measurement.data[0], SCI_MHTDC_T_32, frsmain.data.v1290.measurement.data[31], DATA24);
SIGNAL(ZERO_SUPPRESS_MULTI(128): SCI_MHTDC_LOT_32);
SIGNAL(SCI_MHTDC_LOT_1, frsmain.data.v1290.measurement.leadOrTrail[0], SCI_MHTDC_LOT_32, frsmain.data.v1290.measurement.leadOrTrail[31], DATA8);


// MUSIC TIME MOVED FROM MAIN TO USER 2025


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
SIGNAL(TPC_TDC_T_1, frstpc.data.v1190.measurement.data[0], TPC_TDC_T_128, frstpc.data.v1190.measurement.data[127], DATA24);
SIGNAL(ZERO_SUPPRESS_MULTI(128): TPC_TDC_LOT_128);
SIGNAL(TPC_TDC_LOT_1, frstpc.data.v1190.measurement.leadOrTrail[0], TPC_TDC_LOT_128, frstpc.data.v1190.measurement.leadOrTrail[127], DATA8);
// :::::::::::::::::::::::::::::::::::::::

// ::::::: User Crate ::::::::::::::::::::
// SIGNAL(SCALERS2_1, frsuser.data.v830.data[0], SCALERS2_32, frsuser.data.v830.data[31], DATA32);
SIGNAL(SCALERS2_1, frsuser.data.v830.scalers[0], SCALERS2_32, frsuser.data.v830.scalers[31], DATA32);

SIGNAL(ZERO_SUPPRESS: SCI_TAC_DT_32); // 19 possible DT values? I guess we should check before committing..
SIGNAL(SCI_TAC_DT_1, frsuser.data.v785[1].data[0], SCI_TAC_DT_32, frsuser.data.v785[1].data[31], DATA24);

SIGNAL(ZERO_SUPPRESS: MUSIC5_E_8);
SIGNAL(MUSIC1_E_1, frsuser.data.v785[0].data[0], MUSIC1_E_8, frsuser.data.v785[0].data[7], DATA24);
SIGNAL(MUSIC2_E_1, frsuser.data.v785[0].data[8], MUSIC2_E_8, frsuser.data.v785[0].data[15], DATA24);

SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC1_T_8);
SIGNAL(MUSIC1_T_1, frsuser.data.v1290.measurement.data[16], MUSIC1_T_8, frsuser.data.v1290.measurement.data[23], DATA24);
SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC1_LOT_8);
SIGNAL(MUSIC1_LOT_1, frsuser.data.v1290.measurement.leadOrTrail[16], MUSIC1_LOT_8, frsuser.data.v1290.measurement.leadOrTrail[23], DATA8);

SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC2_T_8);
SIGNAL(MUSIC2_T_1, frsuser.data.v1290.measurement.data[24], MUSIC2_T_8, frsuser.data.v1290.measurement.data[31], DATA24);
SIGNAL(ZERO_SUPPRESS_MULTI(128): MUSIC2_LOT_8);
SIGNAL(MUSIC2_LOT_1, frsuser.data.v1290.measurement.leadOrTrail[24], MUSIC2_LOT_8, frsuser.data.v1290.measurement.leadOrTrail[31], DATA8);

// :::::::::::::::::::::::::::::::::::::::

// ::::::: TPAT Crate ::::::::::::::::::::
SIGNAL(WR_ID, frstpat.wr.subsystem_id, DATA12);
SIGNAL(WR_T1, frstpat.wr.t1, DATA16);
SIGNAL(WR_T2, frstpat.wr.t2, DATA16);
SIGNAL(WR_T3, frstpat.wr.t3, DATA16);
SIGNAL(WR_T4, frstpat.wr.t4, DATA16);
SIGNAL(TPAT, frstpat.data.tpat, DATA16);
// :::::::::::::::::::::::::::::::::::::::


// ::::::: TRAVMUS Crate ::::::::::::::::::::
// 4 = 21, 5 = 22 -- fixed
SIGNAL(TM_WR_T1, frstravmus.wr.t1, DATA16);
SIGNAL(TM_WR_T2, frstravmus.wr.t2, DATA16);
SIGNAL(TM_WR_T3, frstravmus.wr.t3, DATA16);
SIGNAL(TM_WR_T4, frstravmus.wr.t4, DATA16);
SIGNAL(MUSIC4_E_1, frstravmus.data.mdpp.adc[0], MUSIC4_E_8, frstravmus.data.mdpp.adc[7], DATA24);
SIGNAL(MUSIC5_E_1, frstravmus.data.mdpp.adc[8], MUSIC5_E_8, frstravmus.data.mdpp.adc[15], DATA24);