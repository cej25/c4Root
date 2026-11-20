// Expand into the subevent so UCESB keeps ts, trigger_window, padding, and
// tamex[] directly under the existing EVENT member. Each caller lists its cards.
#define S100_TAMEX_PAYLOAD(wr_id, ...) \
    select optional { ts = TIMESTAMP_WHITERABBIT(id = wr_id); }; \
    select optional { trigger_window = TAMEX4_HEADER(); }; \
    select several { padding = TAMEX4_PADDING(); }; \
    select several { __VA_ARGS__ };
