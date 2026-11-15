/** BEGIN_REVOKE *******************************************************
 *
 * Event revoker for EVENT.
 *
 * Do not edit - automatically generated.
 */

// EVENT
int unpack_event::__revoke_subevent(subevent_header *__header)
  // lisafast = lisa_tamex_subev(type=10,subtype=1,procid=100,control=9,
                              // subcrate=0);
{
  int __match_no = 0;
  MATCH_SUBEVENT_DECL(288,__match_no,1,((VES10_1_type==10)&&(VES10_1_subtype==1)&&(VES10_1_control==9)&&(VES10_1_subcrate==0)&&(VES10_1_procid==100)),lisafast);
  if (!__match_no) return 0;
  switch (__match_no)
  {
    case 1:
      UNPACK_SUBEVENT_CHECK_NO_REVISIT(288,lisa_tamex_subev,lisafast,0);
      REVOKE_SUBEVENT_DECL(288,0,lisa_tamex_subev,lisafast);
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
