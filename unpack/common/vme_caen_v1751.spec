// chrome-extension://efaidnbmnnnibpcajpcglclefindmkaj/http://npg.dl.ac.uk/MIDAS/MIDASWebServices/VME/docs/UM3356_V1751_UserManual_rev16.pdf

// channel mask is provided
// one option is simply to encode this mask value
// analyse it for fired channels later? 
// not sure its possible in ucesb .spec

#define TRACE_LENGTH 120


VME_CAEN_V1751(board)
{
    MEMBER(DATA8 board_id);
    MEMBER(DATA8 channels);
    MEMBER(DATA32 board_time);
    MEMBER(DATA32 channel_time[64] NO_INDEX_LIST);
    MEMBER(DATA16 chan_ext_time[64] NO_INDEX_LIST);
    MEMBER(DATA12 chan_fine_time[64] NO_INDEX_LIST);
    MEMBER(DATA16 qshort[64] NO_INDEX_LIST);
    MEMBER(DATA16 qlong[64] NO_INDEX_LIST);
    MEMBER(DATA16 extras);
    MEMBER(DATA16 dm);

    MEMBER(DATA16 chan_baseline[64] NO_INDEX_LIST);
    MEMBER(DATA16 chan_midscale[64] NO_INDEX_LIST);
    MEMBER(DATA16 chan_sazc[64] NO_INDEX_LIST);
    MEMBER(DATA16 chan_sbzc[64] NO_INDEX_LIST);

    MEMBER(DATA16 sample_one[8][TRACE_LENGTH] ZERO_SUPPRESS);
    MEMBER(DATA16 sample_two[8][TRACE_LENGTH] ZERO_SUPPRESS);
    MEMBER(DATA16 sample_three[8][TRACE_LENGTH] ZERO_SUPPRESS);

    UINT32 board_agg_size NOENCODE
    {
        0_27: event_size;
        28_31: 0xA;
    };

    UINT32 board_details NOENCODE
    {
        0_7: channels; // channel_mask
        8_23: pattern;
        24_25: empty;
        26: board_fail;
        27_31: id = MATCH(board); // "geo"
        ENCODE(channels, (value = channels));
        ENCODE(board_id, (value = id));
    };

    UINT32 board_agg_counter NOENCODE
    {
        0_22: counter;
        23_31: empty;
    };

    UINT32 board_agg_timetag NOENCODE
    {
        0_31: time_tag;
        ENCODE(board_time, (value = time_tag));
    };

    // --- end of first four words, always present --- //

    if (board_agg_size.event_size > 4)
    {

        list (0 <= index < (board_agg_size.event_size - 4) / (6+TRACE_LENGTH)) // ah, this is not correct. 
        {

            // loop over channel aggregates
            // format size
            UINT32 channel_agg_size NOENCODE
            {   
                0_21: size;
                22_27: empty; 
                28_31: format;
                
            };

            UINT32 format_one NOENCODE
            {
                0_15: no_wave_samples; // per 12 words
                16_17: empty;
                18: ed; // digital probe enabled
                19_21: dp1; // digital probe 1
                22_24: dp2; // digital probe 2
                25_26: ap; // analogue probe
                27: es; // waveform enabled
                28: ee; // extras enabled
                29: et; // timetag enabled
                30: eq; // charge enabled
                31: dt; // dual trace enabled
            };

            if (channel_agg_size.format == 0b0100)
            {
                UINT32 format_two NOENCODE
                {
                    0_2: ex; // extras option enabled flag
                    3: pp; //  pulse polarity: 0 = trig on rising, 1 = trig on falling
                    4: dm; // discrimination mode: 0 = leading edge, 1 = constant fraction
                    5_7: interp; // interpolation points for cfd or led
                    8_31: empty; 
                    ENCODE(extras,(value=ex));
                    ENCODE(dm, (value=dm));
                };

                if (format_one.et == 0b1)
                {
                    UINT32 channel_time_tag NOENCODE
                    {
                        0_31: time_tag;
                        ENCODE(channel_time APPEND_LIST, (value = time_tag));
                    };
                }

                if (format_one.es == 1) // waveform stuff
                {
                    list (0 <= i < TRACE_LENGTH)
                    {
                        UINT32 sample NOENCODE
                        {
                            0_9: one;
                            10_19: two;
                            20_29: three;
                            // 11_20: two;
                            // 21: n2;
                            // 22_31: three;
                            30_31: trig_cond;
                            ENCODE(sample_one[index][i], (value=one));
                            ENCODE(sample_two[index][i], (value=two));
                            ENCODE(sample_three[index][i], (value=three));
                        }
                    }
                }

                if (format_one.ee == 0b1 && channel_agg_size.format == 0b0100)
                {
                    if (format_two.ex == 0b000)
                    {
                        UINT32 extras NOENCODE
                        {   
                            0_15: baseline;
                            16_31: ext_time;
                            ENCODE(chan_baseline APPEND_LIST, (value = baseline));
                            ENCODE(chan_ext_time APPEND_LIST, (value = ext_time));
                        };
                    }
                    else if (format_two.ex == 0b001)
                    {
                        UINT32 extras NOENCODE
                        {   
                            0_15: flags;
                            16_31: ext_time;
                            ENCODE(chan_ext_time APPEND_LIST, (value = ext_time));
                        };
                    }
                    else if (format_two.ex == 0b010)
                    {
                        UINT32 extras NOENCODE
                        {
                            0_9: fine_time;
                            10_15: flags;
                            16_31: ext_time;
                            ENCODE(chan_fine_time APPEND_LIST, (value = fine_time));
                            ENCODE(chan_ext_time APPEND_LIST, (value = ext_time));
                        };
                    }
                    else if (format_two.ex == 0b100)
                    {
                        UINT32 extras NOENCODE
                        {
                            0_15: baseline;
                            16_26: fine_time;
                            27_31: flags;
                            ENCODE(chan_baseline APPEND_LIST, (value = baseline));
                            ENCODE(chan_fine_time APPEND_LIST, (value = fine_time));
                        };
                    }
                    else if (format_two.ex == 0b101)
                    {   
                        UINT32 extras NOENCODE
                        {
                            0_9: midscale;
                            10_19: sazc; // nth sample after zero crossing
                            20_29: sbzc; // nth sample before zero crossing
                            30: pp; // pulse polarity
                            31: dm; // discrimination mode
                            ENCODE(chan_midscale APPEND_LIST, (value = midscale));
                            ENCODE(chan_sazc APPEND_LIST, (value = sazc));
                            ENCODE(chan_sbzc APPEND_LIST, (value = sbzc));
                        }
                    }

                } // end of extras enabled/options
                
            }
            else
            {
                if (format_one.et == 0b1)
                {
                    UINT32 channel_time_tag NOENCODE
                    {
                        0_31: time_tag;
                        ENCODE(channel_time APPEND_LIST, (value = time_tag));
                    };
                }

                if (format_one.es == 1) // waveform stuff
                {
                    list (0 <= i < TRACE_LENGTH)
                    {
                        UINT32 sample NOENCODE
                        {
                            0_9: one;
                            10_19: two;
                            20_29: three;
                            // 11_20: two;
                            // 21: n2;
                            // 22_31: three;
                            30_31: trig_cond;
                            ENCODE(sample_one[index][i], (value=one));
                            ENCODE(sample_two[index][i], (value=two));
                            ENCODE(sample_three[index][i], (value=three));
                        }
                    }
                }
            }

            if (format_one.eq == 0b1)
            {
                UINT32 qdata NOENCODE
                {
                    0_14: qshort;
                    15: empty; // = MATCH(0x1); // for testing
                    16_31: qlong;
                    ENCODE(qshort APPEND_LIST, (value = qshort));
                    ENCODE(qlong APPEND_LIST, (value = qlong));
                }
            }

        }

    } // size > 4
    
}

