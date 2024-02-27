// chrome-extension://efaidnbmnnnibpcajpcglclefindmkaj/http://npg.dl.ac.uk/MIDAS/MIDASWebServices/VME/docs/UM3356_V1751_UserManual_rev16.pdf

// channel mask is provided
// one option is simply to encode this mask value
// analyse it for fired channels later? 
// not sure its possible in ucesb .spec

VME_CAEN_V1751()
{
    MEMBER(DATA8 board_id);
    MEMBER(DATA8 channels);
    MEMBER(DATA32 data[64] NO_INDEX_LIST);

    // there are four header words
    // then data

    UINT32 header1 NOENCODE
    {
        0_27: event_size;
        28_31: check_a;

    };

    if (header1.check_a == 10 && header1.event_size == 4)
    {

        UINT32 word2 NOENCODE;

        UINT32 word3 NOENCODE;

        UINT32 word4 NOENCODE;
    }
    else if (header1.check_a == 10)
    {
        // do real stuff?
        UINT32 header2 NOENCODE
        {   
            0_7: channels; // channel_mask
            8_23: pattern;
            24_25: empty;
            26: board_fail;
            27_31: board_id; // "geo"
        };
        ENCODE(channels, (value = header2.channels));
        ENCODE(board_id, (value = header2.board_id));

        UINT32 header3 NOENCODE
        {
            0_23: event_counter;
            24_31: no_idea;
        };

        // "coarse" time
        UINT32 header4 NOENCODE
        {
            0_31: trigger_tag;
        }

        list (0 <= i < header1.event_size - 4)
        {
            UINT32 qdcval NOENCODE
            {
                0_31: q;
            }
            ENCODE(data APPEND_LIST, (value = qdcval.q));
        }

    }


}