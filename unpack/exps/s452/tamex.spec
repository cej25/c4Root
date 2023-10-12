TAMEX_WINDOW()
{
    MEMBER(DATA16 pre_trig_window);
    MEMBER(DATA16 post_trig_window);
    UINT32 window NOENCODE
    {
        0_15: pre;
        16_31: post;
        ENCODE(pre_trig_window, (value = pre));
        ENCODE(post_trig_window, (value = post));
    }
}

TAMEX_PADDING()
{
    UINT32 pads NOENCODE
    {
        0_19: reserved;
        20_31: 0xADD;
    }
}

TAMEX_TIME_DATA()
{
    // CEJ: writing unpack w/ ZS increases memory used
    // but unpacking is faster without writing.
    MEMBER(DATA12 coarse_time[33][2]);
    MEMBER(DATA12 fine_time[33][2]);
    UINT32 time_data// NOENCODE
    {
        0_10: coarse_time;
        11: edge;
        12_21: fine_time;
        22_27: channel;
        28_31: 0x8; //?
        ENCODE(coarse_time[channel][edge], (value = coarse_time));
        ENCODE(fine_time[channel][edge], (value = fine_time));
    }
}

TAMEX_DATA(card)
{
    MEMBER(DATA8 am_fired);
    MEMBER(DATA32 epochs[33]); // channel 0 is trigger

    UINT32 indicator NOENCODE
    {
        0_7: 0x34;
        8_11: trig;
        12_15: sfp; 
        16_23: card = MATCH(card);
        24_31: 0;
    };

    UINT32 fired NOENCODE
    {
        0_11: amount;
        12_31: reserved;
        ENCODE(am_fired, (value = amount));
    };

    UINT32 header NOENCODE
    {
        0_15: event_counter;
        16: buf;
        17_19: reserved;
        20_23: trigger_type;
        24_31: 0xAA;
    };

    list (0 <= i < (fired.amount / 4 - 3)/2)
    {
        optional UINT32 epoch NOENCODE
        {
            0_27: counter;
            28_31: 0x6;
        }

        select several
        {
            data = TAMEX_TIME_DATA();
        };

        ENCODE(epochs[data.time_data.channel], (value=epoch.counter));
    };

    UINT32 err NOENCODE
    {
        0_23: error_info;
        24_31: 0xEE;
    };

    UINT32 trailer NOENCODE
    {
        0_15: event_counter;
        16: buf;
        17_19: reserved;
        20_23: trigger_type;
        24_31: 0xBB;
    };

}