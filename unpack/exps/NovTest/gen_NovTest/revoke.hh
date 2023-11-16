/** BEGIN_REVOKE *******************************************************
 *
 * Event revoker for EVENT.
 *
 * Do not edit - automatically generated.
 */

// EVENT
int unpack_event::__revoke_subevent(subevent_header *__header)
  // revisit aida = aida_subev(type=10,subtype=1,procid=90,control=37);
  // germanium = febex_subev(type=10,subtype=1,procid=60,control=20);
  // fatima = fatima_tamex_subev(type=10,subtype=1,procid=75,control=20,
                              // subcrate=0);
  // bplast = bplast_subev(type=10,subtype=1,procid=80,control=20,subcrate=0);
  // ignore_unknown_subevent;
{
  int __match_no = 0;
  MATCH_SUBEVENT_DECL(593,__match_no,1,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==37)&&(VES10_1_procid==90)),aida);
  MATCH_SUBEVENT_DECL(594,__match_no,2,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_procid==60)),germanium);
  MATCH_SUBEVENT_DECL(596,__match_no,3,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_subcrate==0)&&(VES10_1_procid==75)),fatima);
  MATCH_SUBEVENT_DECL(597,__match_no,4,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_subcrate==0)&&(VES10_1_procid==80)),bplast);
  if (!__match_no) return 0;
  switch (__match_no)
  {
    case 1:
      REVOKE_SUBEVENT_DECL(593,0,aida_subev,aida);
      break;
    case 2:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(594,febex_subev,germanium,0);
      REVOKE_SUBEVENT_DECL(594,0,febex_subev,germanium);
      break;
    case 3:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(596,fatima_tamex_subev,fatima,1);
      REVOKE_SUBEVENT_DECL(596,0,fatima_tamex_subev,fatima);
      break;
    case 4:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(597,bplast_subev,bplast,2);
      REVOKE_SUBEVENT_DECL(597,0,bplast_subev,bplast);
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
