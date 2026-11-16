#include "foot_ext.hh"

#include "error.hh"

/*---------------------------------------------------------------------------*/

#include "structures.hh"

/*---------------------------------------------------------------------------*/

#include "dptc/dptc.h"

#if defined(UNPACKER_IS_foot_640)
#       define N_CHANNELS 640
#else
#       define N_CHANNELS 320
#endif

// 11 header words, 5 trailer words
#define N_WORDS (N_CHANNELS + 16)

EXT_FOOT::EXT_FOOT()
{
}

EXT_FOOT::~EXT_FOOT()
{
}

void EXT_FOOT::__clean()
{
  avail.value = 0;
  data.__clean();
}

union EXT_FOOT_ch_data
{
  struct
  {
#if __BYTE_ORDER == __LITTLE_ENDIAN
    uint32 adc1_1 : 8;
    uint32 adc1_2 : 8;
    uint32 adc2_1 : 8;
    uint32 adc2_2 : 8;
#endif
#if __BYTE_ORDER == __BIG_ENDIAN
    uint32 adc2_2 : 8;
    uint32 adc2_1 : 8;
    uint32 adc1_2 : 8;
    uint32 adc1_1 : 8;
#endif
  };
  uint32  u32;
};

EXT_DECL_DATA_SRC_FCN(void,EXT_FOOT::__unpack)
{
  // First words:
  //  Raw: [0]>0 = count
  //  Compressed: [0]=0, [1]>0 = count

  uint32 ev = 0;
  __buffer.get_uint32(&ev);

  uint32 count = 0;
  __buffer.get_uint32(&count);
  bool is_comp = 0x80000000 & count;
  count &= 0x7fffffff;

  // Check event payload.

  if (sizeof(uint32) + __buffer.left() < sizeof(uint32) * count)
    ERROR("Count (%ddw = %d bytes) larger than data space left (%d).",
	  count,(int) (sizeof(uint32) * count),
	  (int) __buffer.left());

  uint32 raw[N_WORDS];
  memset(raw, 0xaa, sizeof raw);
  uint32 *rp;

  if (is_comp)
    {
      // Compressed.

      uint32 comp[N_WORDS];
      memset(comp, 0xbb, sizeof comp);
      uint32 *cp = comp;

      for (unsigned i = 0; i < count; ++i, ++cp)
        __buffer.get_uint32(cp);

      dptc_unpack16(comp, count, (uint16_t *)raw, countof(raw) * 2, 16);
    }
  else
    {
      // Raw.

      rp = raw;
      *rp++ = count;

      for (unsigned i = 0; i < count - 1; ++i, ++rp)
        __buffer.get_uint32(rp);
    }

  rp = raw;

  uint32 header;

  header = *rp++;
  if (16 + N_CHANNELS != header)
    ERROR("Invalid event size %u", header);

  header = *rp++;
  if (0xeadebaba != header)
    ERROR("Invalid header2 %08x", header);

  header = *rp++;
  if (0xd451d451 != header)
    ERROR("Invalid header3 %08x", header);

  // Event counter.
  header = *rp++;

  // TS 32 LSB.
  ts_lo.value = *rp++;

  // TS 32 MSB.
  ts_hi.value = *rp++;

  header = *rp++;
  if (N_CHANNELS + 8 != header)
    ERROR("Invalid header7 %08x", header);

  header = *rp++;
  if (0x4ead0501 != header)
    ERROR("Invalid header8 %08x", header);

  header = *rp++;
  if (0x4ead1502 != header)
    ERROR("Invalid header9 %08x", header);

  header = *rp++;
  if (0x4ead2503 != header)
    ERROR("Invalid header10 %08x", header);

  header = *rp++;
  if (0x4ead3504 != header)
    ERROR("Invalid header11 %08x", header);

  for (unsigned i = 0; i < N_CHANNELS; ++i)
    {
      EXT_FOOT_ch_data ch_data;

      ch_data.u32 = *rp++;

      // Compressed data is already unswizzled, but raw not.

      unsigned j = 2 * i;
      unsigned k = j;
      if (!is_comp) k = 64 * (j % 10) + j / 10;
      DATA16 &item1 = data.insert_index(-1, k);
      item1.value = (uint16_t)(ch_data.adc1_2 << 8 | ch_data.adc1_1) / 4;

      k = ++j;
      if (!is_comp) k = 64 * (j % 10) + j / 10;
      DATA16 &item2 = data.insert_index(-1, k);
      item2.value = (uint16_t)(ch_data.adc2_2 << 8 | ch_data.adc2_1) / 4;
    }

  uint32 footer;

  footer = *rp++;
  if (0xf007e501 != footer)
    ERROR("Invalid footer1 %08x", footer);

  footer = *rp++;
  if (0xf007e502 != footer)
    ERROR("Invalid footer2 %08x", footer);

  footer = *rp++;
  if (0xf007e503 != footer)
    ERROR("Invalid footer3 %08x", footer);

  // Rataclock status and sync check value is baked into old footer.
  footer = *rp++;
  if (0x0000fafe != (0x0000ffff & footer))
    ERROR("Invalid footer4 %08x", footer);
  ts_status.value = 0xfff & static_cast<uint16_t>(footer >> 24);
  sync_check.value = 0xf & static_cast<uint8_t>(footer >> 16);

  footer = *rp++;
  if (0xbacca000 != footer)
    ERROR("Invalid footer5 %08x", footer);

  avail.value = 1;
}
EXT_FORCE_IMPL_DATA_SRC_FCN(void,EXT_FOOT::__unpack)

EXT_DECL_DATA_SRC_FCN(bool,EXT_FOOT::__match)
{
  uint32 count;

  GET_BUFFER_UINT32(count);

  count &= 0x7fffffff;
  if (count <= N_WORDS)
    return true;

  return false;
}
EXT_FORCE_IMPL_DATA_SRC_FCN(bool,EXT_FOOT::__match)

/*---------------------------------------------------------------------------*/
