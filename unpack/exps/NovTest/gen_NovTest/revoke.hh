/** BEGIN_REVOKE *******************************************************
 *
 * Event revoker for EVENT.
 *
 * Do not edit - automatically generated.
 */

// EVENT
int unpack_event::__revoke_subevent(subevent_header *__header)
  // revisit aida = aida_subev(type=10,subtype=1,procid=90,control=37);
  // bplast = bplast_subev(type=10,subtype=1,procid=80,control=20,subcrate=0);
  // frsmain = frs_main_subev(procid=10);
  // frstpc = frs_tpc_subev(procid=20);
  // frsuser = frs_user_subev(procid=30);
  // frsvftx = frs_vftx_subev(procid=40);
  // ignore_unknown_subevent;
{
  int __match_no = 0;
  MATCH_SUBEVENT_DECL(1228,__match_no,1,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==37)&&(VES10_1_procid==90)),aida);
  MATCH_SUBEVENT_DECL(1232,__match_no,2,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_subcrate==0)&&(VES10_1_procid==80)),bplast);
  MATCH_SUBEVENT_DECL(1234,__match_no,3,((VES10_1_procid==10)),frsmain);
  MATCH_SUBEVENT_DECL(1235,__match_no,4,((VES10_1_procid==20)),frstpc);
  MATCH_SUBEVENT_DECL(1236,__match_no,5,((VES10_1_procid==30)),frsuser);
  MATCH_SUBEVENT_DECL(1237,__match_no,6,((VES10_1_procid==40)),frsvftx);
  if (!__match_no) return 0;
  switch (__match_no)
  {
    case 1:
      REVOKE_SUBEVENT_DECL(1228,0,aida_subev,aida);
      break;
    case 2:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(1232,bplast_subev,bplast,0);
      REVOKE_SUBEVENT_DECL(1232,0,bplast_subev,bplast);
      break;
    case 3:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(1234,frs_main_subev,frsmain,1);
      REVOKE_SUBEVENT_DECL(1234,0,frs_main_subev,frsmain);
      break;
    case 4:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(1235,frs_tpc_subev,frstpc,2);
      REVOKE_SUBEVENT_DECL(1235,0,frs_tpc_subev,frstpc);
      break;
    case 5:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(1236,frs_user_subev,frsuser,3);
      REVOKE_SUBEVENT_DECL(1236,0,frs_user_subev,frsuser);
      break;
    case 6:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(1237,frs_vftx_subev,frsvftx,4);
      REVOKE_SUBEVENT_DECL(1237,0,frs_vftx_subev,frsvftx);
      break;
  }
  return 0;
}

/** END_REVOKE ********************************************************/
/** BEGIN_REVOKE *******************************************************
 *
 * Event revoker for EVENT.
 *
 * Do not edit - automatically generated.
 */

// STICKY_EVENT
int unpack_sticky_event::__revoke_subevent(subevent_header *__header)
{
  int __match_no = 0;
  if (!__match_no) return 0;
  switch (__match_no)
  {
  }
  return 0;
}

/** END_REVOKE ********************************************************/
