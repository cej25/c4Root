/** BEGIN_REVOKE *******************************************************
 *
 * Event revoker for EVENT.
 *
 * Do not edit - automatically generated.
 */

// EVENT
int unpack_event::__revoke_subevent(subevent_header *__header)
  // fatima = fatima_tamex_subev(type=10,subtype=1,procid=75,control=20);
  // bplast = bplast_subev(type=10,subtype=1,procid=80,control=20);
  // ignore_unknown_subevent;
{
  int __match_no = 0;
  MATCH_SUBEVENT_DECL(788,__match_no,1,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_procid==75)),fatima);
  MATCH_SUBEVENT_DECL(789,__match_no,2,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==20)&&(VES10_1_procid==80)),bplast);
  if (!__match_no) return 0;
  switch (__match_no)
  {
    case 1:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(788,fatima_tamex_subev,fatima,0);
      REVOKE_SUBEVENT_DECL(788,0,fatima_tamex_subev,fatima);
      break;
    case 2:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(789,bplast_subev,bplast,1);
      REVOKE_SUBEVENT_DECL(789,0,bplast_subev,bplast);
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
