/* Copyright (c) 2017, Haakan T. Johansson */
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

#ifndef __DPTC_H__
#define __DPTC_H__

#include <stddef.h>
#include <stdint.h>

#ifndef  DPTC_ENABLE_FLIPSIGN
# define DPTC_ENABLE_FLIPSIGN   1
#endif

#ifndef  DPTC_ENABLE_PREDICTOR
# define DPTC_ENABLE_PREDICTOR  0
#endif

#ifndef  DPTC_CHUNK_SIZE
# define DPTC_CHUNK_SIZE        4
#endif

/* For legacy applications. */
#define dptc_compress dptc_compress16
#define dptc_unpack   dptc_unpack16

size_t dptc_compress16(uint16_t *data, size_t ndata,
		       uint32_t *compr, size_t ncompr,
		       int bits
#if DPTC_GET_TOTALBITS
		       , int *totalbits
#endif
		       );

size_t dptc_compress32(uint32_t *data, size_t ndata,
		       uint32_t *compr, size_t ncompr,
		       int bits
#if DPTC_GET_TOTALBITS
		       , int *totalbits
#endif
		       );

size_t dptc_ads_compress32(uint32_t *data, size_t ndata,
			   uint32_t *compr, size_t ncompr,
			   int bits, /* including max_level */
			   int max_level
#if DPTC_GET_TOTALBITS
			   , int *totalbits
#endif
			   );

int dptc_unpack16(uint32_t *compr, size_t ncompr,
		  uint16_t *output, size_t ndata,
		  int bits);

int dptc_unpack32(uint32_t *compr, size_t ncompr,
		  uint32_t *output, size_t ndata,
		  int bits);

int dptc_ads_unpack32(uint32_t *compr, size_t ncompr,
		      uint32_t *output, size_t ndata,
		      int bits, /* including max_level */
		      int max_level);

#endif/*__DPTC_H__*/
