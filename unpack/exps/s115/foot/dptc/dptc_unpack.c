/* Copyright (c) 2017, Haakan T. Johansson */
/* Copyright (c) 2020, Lukas Rahmn */
/* Copyright (c) 2020, Anton Fredriksson */
/* All rights reserved. */

/* Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the authors nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DPTC_IMPL_UNPACK

/* Include this file multiple times to implement the various unpacking
 * functions.
 */

#define DPTC_IMPL_UNPACK  dptc_unpack16
#define DPTC_OUTPUT_TYPE  uint16_t
#include "dptc_unpack.c"
#undef DPTC_IMPL_UNPACK
#undef DPTC_OUTPUT_TYPE

#define DPTC_IMPL_UNPACK  dptc_unpack32
#define DPTC_OUTPUT_TYPE  uint32_t
#include "dptc_unpack.c"
#undef DPTC_IMPL_UNPACK
#undef DPTC_OUTPUT_TYPE

#define DPTC_IMPL_UNPACK  dptc_ads_unpack32
#define DPTC_OUTPUT_TYPE  uint32_t
#define DPTC_IMPL_ADAPTIVE_DOWNSAMPLING 1
#include "dptc_unpack.c"
#undef DPTC_IMPL_UNPACK
#undef DPTC_OUTPUT_TYPE
#undef DPTC_IMPL_ADAPTIVE_DOWNSAMPLING

#else /* DPTC_IMPL_UNPACK */

#include "dptc.h"

#include <unistd.h>

#if DPTC_DEBUG_UNPACK
#include <stdio.h>
#define DPTC_INT_DEBUG(...)  printf(__VA_ARGS__)
#else
#define DPTC_INT_DEBUG(...)  do { } while (0)
#endif

/* If the read pointer has not passed the end of the input buffer,
 * read the next word.  This is protect against buffor overflow on
 * corrupt data that.
 *
 * Then shift the data bits to the correct position in the buffer, and
 * mix them in.
 *
 * If the buffer actually had less than 32 bits available, increment
 * the read pointer.
 */
#define DPTC_INT_FETCH_WORD(src, src_end, src_val,	\
			    buffer, avail)		\
  do {							\
    src_val = 0;					\
    if (((ssize_t) (src - src_end)) < 0)		\
      src_val = ((uint64_t) *src);			\
    buffer |= src_val << avail;				\
    /* The following is equivalent to: */		\
    /* if (avail < 32) { avail += 32; src++; }*/	\
    src += ((~avail) & 0x20) >> 5;			\
    avail |= 0x20;					\
  } while (0)


int DPTC_IMPL_UNPACK(uint32_t *compr, size_t ncompr,
		     DPTC_OUTPUT_TYPE *output, size_t ndata,
		     int bits
#if DPTC_IMPL_ADAPTIVE_DOWNSAMPLING
		     , int max_level
#endif
		     )
{
  /* *** Constants based on the number of bits. *** */

  /* Mask for the data bits. */
  uint32_t mask = ((((uint32_t) 1) << bits)-1);
  /* Signbit for the data. */
  uint32_t signbit   = mask ^ (mask >> 1);

  /* Number of bits required to store the number of bits used in a chunk. */
  /* Only allowing 'bits' values up to 16, we can do log2 with a lookup. */
  uint32_t storebits = (bits-3-1 < 16) ?
    ((0x4444444433332211ll >> ((bits-3-1)*4)) & 0xf) : 5;
  /* Mask for the same. */
  uint32_t storebitsmask = ((((uint32_t) 1) << storebits)-1);

#if DPTC_IMPL_ADAPTIVE_DOWNSAMPLING
  /* Number of bits required to store the inital level. */
  /* TODO: One should consider to just define his to be 3. */
  uint32_t level_bits = (max_level < 16) ?
    ((0x4444444433332211ll >> (max_level*4)) & 0xf) : 5;
  /* Mask for the same. */
  uint32_t level_mask = (1 << level_bits) - 1;
#endif

  /* *** Data source pointers. *** */ 

  /* Pointer to next word to use. */
  uint32_t *src = compr;
  /* Pointer to one after last word to use.  (Will never be read). */
  uint32_t *src_end = compr + ncompr;

  /* *** Local buffer of next bits to use. *** */

  /* Compressed data.  This buffer always contain at least 32 bits of data. */
  uint64_t buffer = 0;
  /* Number of bits currently available. */
  uint32_t avail = 0;
  /* Value of next word in data source. */
  uint64_t src_val;

  /* *** Chunk handling. *** */

  /* Number of bits stored for this chunk. */
  uint32_t numbits;
  /* Temporary value to adjusted wrapped values. */
  uint32_t numbits_wrap;
  /* Number of bits stored in previous chunk. */
  uint32_t prevnumbits;
  /* Loop variables. */
  size_t i, j;

  /* *** Compression handling. *** */
  
  /* Mask for data with number of bits of this chunk. */
  uint32_t storedmask;
  /* Base value (most negative possible) for data within this chunk. */
  uint32_t storedbase;
  /* Actual value stored (recovered after mask and base add). */
  uint32_t stored;

  /* Difference value stored might have had its sign flipped. */
  uint32_t diff_flipped;
  /* Keep track if value is stored with sign change? */
  int flipsign = 0;

  /* Difference value after sign flip correction. */
  uint32_t diff;
  /* Keep track of last three differences. */
  uint32_t d1 = 0, d2 = 0, d3 = 0;

  /* Previous value.  (To undo difference operation.) */
  uint32_t prev = 0;

  /* *** Adaptive downsampling. *** */

#if DPTC_IMPL_ADAPTIVE_DOWNSAMPLING
  /* Number of bits for step code. */
  uint32_t stepbits;
  /* Code for the step (possibly including one extra no-care bit. */
  uint32_t stepcode;
  /* Step (with bias of -1). */
  uint32_t step_plus_1;
  /* Current downsampling level. */
  uint32_t level = 0;
  /* Correction of the previous value when unpacking for a step up. */
  uint32_t l_shift;
  /* Correction of the result value when unpacking for a step down. */
  uint32_t r_shift;
#endif

  if (bits > 8 * sizeof (DPTC_OUTPUT_TYPE))
    {
      DPTC_INT_DEBUG("Cannot handle more bits (%d) than output type (%d).\n",
		     bits, 8 * sizeof (DPTC_OUTPUT_TYPE));
      return 1;
    }

  DPTC_INT_DEBUG("-----------------------------------------------------\n");

  DPTC_INT_FETCH_WORD(src, src_end, src_val, buffer, avail);
  
#if DPTC_DEBUG_UNPACK
      dptc_printbits((uint32_t) buffer, 32);
      DPTC_INT_DEBUG(" %d\n", avail);
#endif

  if (ndata)
    {
#if DPTC_IMPL_ADAPTIVE_DOWNSAMPLING
      level = buffer & level_mask;
      buffer >>= level_bits;
      avail -= level_bits;
      DPTC_INT_DEBUG("init level: %d\n", level);
#endif

      prev = (buffer & mask) ^ signbit;
      d1 = prev;
      flipsign = (prev & signbit);

      *(output++) =
#if DPTC_IMPL_ADAPTIVE_DOWNSAMPLING
	(level << 28) |
#endif
	prev;

      DPTC_INT_DEBUG(" : %04x\n", prev);

      buffer >>= bits;
      avail -= bits;
    }
  
  prevnumbits = bits;

  for (i = 1; i < ndata; )
    {
      DPTC_INT_FETCH_WORD(src, src_end, src_val, buffer, avail);

#if DPTC_DEBUG_UNPACK
      dptc_printbits((uint32_t) buffer, 32);
      DPTC_INT_DEBUG(" %d\n", avail);
#endif

      size_t numstore = DPTC_CHUNK_SIZE;

      if (numstore > ndata - i)
	numstore = ndata - i;

      /* Get the number of bits. */

      numbits = buffer & 0x03;

      buffer >>= 2;
      avail -= 2;

      /* This branch is taken very seldomly.  It is faster to keep it
       * as a branch than to evaluate both paths and assign results
       * using bitmasks.
       */
      if (numbits == 0)
	{
	  numbits = (buffer & storebitsmask);
	  DPTC_INT_DEBUG("long bits: +%d+2 [%d]\n", numbits, storebits);
	  numbits = prevnumbits + numbits + 2;
	  buffer >>= storebits;
	  avail -= storebits;
	}
      else
	{
	  DPTC_INT_DEBUG("short bits: +%d-2\n", numbits);
	  numbits = prevnumbits + numbits + bits - 2;
	}
      DPTC_INT_DEBUG("temp bits: %d\n", numbits);
#if 1
      /* This version is generally faster than the modulo operation. */
      numbits_wrap = numbits - bits;
      if (numbits > bits)
	numbits = numbits_wrap;
      numbits_wrap = numbits - bits;
      if (numbits > bits)
	numbits = numbits_wrap;
#else
      /* Modulo is expensive. */
      numbits = ((numbits - 1) % bits) + 1;
#endif

      storedmask = (1 << numbits) - 1;
      storedbase = -((1 << numbits) >> 1);

      DPTC_INT_DEBUG("numbits: %d (mask 0x%04x, base 0x%04x)\n",
		     numbits, storedmask, storedbase);

      for (j = 0; j < numstore; j++)
	{
	  /* Fetch more bits if needed. */
	  DPTC_INT_FETCH_WORD(src, src_end, src_val, buffer, avail);	  

#if DPTC_IMPL_ADAPTIVE_DOWNSAMPLING
#if DPTC_DEBUG_UNPACK
	  dptc_printbits((uint32_t) buffer, 32);
	  DPTC_INT_DEBUG(" %d\n", avail);
#endif

	  /* Get step. */

	  stepbits = (buffer & 1) + 1;
	  stepcode = (buffer & 3);
	  buffer >>= stepbits;
	  avail -= stepbits;

	  /* Stepcode: x0:0, 01:1, 11:-1
	   * Use bias of -1, and all four codes, in pairs of bits:
	   * 11:0, 10:1, 00:1, 01:2, i.e.
	   *  3->0, 2->1, 1->2, 0->1
	   * 00      01    10    01 = 0001 1001 = 0x19
	   */
	  step_plus_1 = ((0x19) >> (stepcode + stepcode)) & 3;
	  level += step_plus_1 - 1;

	  DPTC_INT_DEBUG("step %d, level %d (%d bits)\n",
			 step_plus_1 - 1,
			 level, stepbits);
#endif

#if DPTC_DEBUG_UNPACK
	  dptc_printbits((uint32_t) buffer, 32);
	  DPTC_INT_DEBUG(" %d\n", avail);
#endif

	  /* Get data. */

	  stored = buffer & storedmask;

	  DPTC_INT_DEBUG("%04x+b=%04x", stored, (stored + storedbase) & mask);
	  
	  stored += storedbase;

	  buffer >>= numbits;
	  avail -= numbits;

	  diff_flipped = stored;

#if DPTC_ENABLE_FLIPSIGN
	  /* 0- instead of - to avoid Visual2019 error. */
	  diff = flipsign ? (0-diff_flipped) : diff_flipped;

	  if (diff)
	    flipsign = (diff & signbit);
#else
	  diff = diff_flipped;
#endif

	  DPTC_INT_DEBUG(" unflipped %04x [%d] ",
			 diff & mask, flipsign ? 1 : 0);

	  /* Do the three last differences have the same sign?
	   * A zero value breaks the sequence.
	   * As we never use the full range of an 32-bit int,
	   * we can look for all three values being postive by the
	   * combinded sign bit of their negative representations.
	   */

	  /* It has been tested to first run the unpacking, store the
	   * intermediate differences, and then do the final predictor
	   * calculations.  That is slower.
	   */

#if DPTC_ENABLE_PREDICTOR
	  if (((d1 & d2 & d3) | ((-d1) & (-d2) & (-d3))) & signbit)
	    {
	      DPTC_INT_DEBUG("[%d %d %d] ", d1, d2, d3);
	      diff += d1;
	    }

	  d3 = d2;
	  d2 = d1;
	  d1 = diff;
#endif

#if DPTC_IMPL_ADAPTIVE_DOWNSAMPLING
	  l_shift = (step_plus_1 >> 1); /* 0,1 -> 0; 2->1 */
	  r_shift = (1 >> step_plus_1); /* 0 -> 1; 1,2->0 */

	  prev = (((prev << l_shift) + diff) >> r_shift) & mask;
	  DPTC_INT_DEBUG("[r:%d l:%d]\n", r_shift, l_shift);
#else
	  prev = (prev + diff) & mask;
#endif

	  *(output++) =
#if DPTC_IMPL_ADAPTIVE_DOWNSAMPLING
	    (level << 28) |
#endif
	    prev;

	  DPTC_INT_DEBUG("%04x : %04x\n", diff & mask, prev & mask);

	  /* There is a speed advantage of explicitly unrolling this
	   * loop.  We gain by only fetching into the buffer for every
	   * two values.  Possible as long as we only support 16-bit
	   * values.
	   */
#if 1
	  if (++j >= numstore)
	    break;

	  if (sizeof (DPTC_OUTPUT_TYPE) > 2)
	    {
	      /* We might consume more than 16 bits per cycle,
	       * fetch more bits if needed.
	       */
	      DPTC_INT_FETCH_WORD(src, src_end, src_val, buffer, avail);
	    }

#if DPTC_IMPL_ADAPTIVE_DOWNSAMPLING
#if DPTC_DEBUG_UNPACK
	  dptc_printbits((uint32_t) buffer, 32);
	  DPTC_INT_DEBUG(" %d\n", avail);
#endif
	  /* Get step. */

	  stepbits = (buffer & 1) + 1;
	  stepcode = (buffer & 3);
	  buffer >>= stepbits;
	  avail -= stepbits;

	  step_plus_1 = ((0x19) >> (stepcode + stepcode)) & 3;
	  level += step_plus_1 - 1;

	  DPTC_INT_DEBUG("step %d, level %d (%d bits)\n",
			 step_plus_1 - 1,
			 level, stepbits);
#endif

#if DPTC_DEBUG_UNPACK
	  dptc_printbits((uint32_t) buffer, 32);
	  DPTC_INT_DEBUG(" %d\n", avail);
#endif
	  /* Get data. */

	  stored = buffer & storedmask;

	  DPTC_INT_DEBUG("%04x+b=%04x", stored, (stored + storedbase) & mask);
	  
	  stored += storedbase;

	  buffer >>= numbits;
	  avail -= numbits;

	  diff_flipped = stored;

#if DPTC_ENABLE_FLIPSIGN
	  diff = flipsign ? (0-diff_flipped) : diff_flipped;

	  if (diff)
	    flipsign = (diff & signbit);
#else
	  diff = diff_flipped;
#endif

	  DPTC_INT_DEBUG(" unflipped %04x [%d] ",
			 diff & mask, flipsign ? 1 : 0);

#if DPTC_ENABLE_PREDICTOR
	  if (((d1 & d2 & d3) | ((-d1) & (-d2) & (-d3))) & signbit)
	    {
	      DPTC_INT_DEBUG("[%d %d %d] ", d1, d2, d3);
	      diff += d1;
	    }

	  d3 = d2;
	  d2 = d1;
	  d1 = diff;
#endif
      
#if DPTC_IMPL_ADAPTIVE_DOWNSAMPLING
	  l_shift = (step_plus_1 >> 1);
	  r_shift = (1 >> step_plus_1);

	  prev = (((prev << l_shift) + diff) >> r_shift) & mask;
	  DPTC_INT_DEBUG("[r:%d l:%d]\n", r_shift, l_shift);
#else
	  prev = (prev + diff) & mask;
#endif

	  *(output++) =
#if DPTC_IMPL_ADAPTIVE_DOWNSAMPLING
	    (level << 28) |
#endif
	    prev;

	  DPTC_INT_DEBUG("%04x : %04x\n", diff & mask, prev & mask);
#endif
	}

      i += numstore;

      prevnumbits = numbits;
    }

  DPTC_INT_DEBUG("%zd \n", src - compr);

  if (buffer)
    {
      DPTC_INT_DEBUG("non-zero bits left in buffer!: 0x%016llx\n", buffer);
      return 1;
    }

  if (((ssize_t) (src - src_end)) < 0)
    {
      DPTC_INT_DEBUG("words left in input: %zd\n", src_end - src);
      return 1;
    }

  return 0;
}

#undef DPTC_INT_DEBUG

#endif/*DPTC_IMPL_UNPACK*/
