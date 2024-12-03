// VME_CAEN_V830_FRS()
// {   
//     MEMBER(DATA32 data[32] ZERO_SUPPRESS);
    
//     UINT32 v830_header NOENCODE
//     {   
//         0_15: trigger_number;
//         16_17: ts;
//         18_23: nwords;
//         24_25: unused;
//         26: 0b1; // distinguish header from 26bit word
//         27_31: geo;
//     };

//     list (0 <= i < v830_header.nwords)
//     {
//         UINT32 data_word NOENCODE
//         {
//             0_31: value;
//             ENCODE(data[i], (value = value)); // c4 assumes the index is the channel number - to be checked.
//         };
//     }
// }


VME_CAEN_V830_FRS(geom)
{
  MEMBER(DATA32 data[32] ZERO_SUPPRESS);

  UINT32 header
    {
      0_15:  event_number;
      16_17: ts;
      18_23: count;
#ifdef VME_CAEN_V830_HEADER_24_25_UNDEFINED
      24_25: undefined;
#endif
      26:    1;
      27_31: geom = MATCH(geom);
    }

  list(0<=index<header.count)
    {
      UINT32 ch_data NOENCODE
	{
	  0_25:  value;
	  26:    0;
	  27_31: channel;

	  ENCODE(data[channel],(value=value));
	}
    }
}