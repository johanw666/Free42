/*****************************************************************************
 * Free42 -- an HP-42S calculator simulator
 * Copyright (C) 2004-2026  Thomas Okken
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see http://www.gnu.org/licenses/.
 *****************************************************************************/

#ifndef FREE42_H
#define FREE42_H 1


//////////////////////////////////////////////////////////////////////////
///// NOTE: THE FP_DECNUM TARGET IS NOT FULLY FUNCTIONAL YET!        /////
///// It's still missing the trigonometric and hyperbolic functions, /////
///// and a few others.                                              /////
//////////////////////////////////////////////////////////////////////////

/*
 * Build options:
 *
 * FP_INTEL: Decimal build using the Intel Decimal Floating-Point Math Library
 * FP_DECNUM: Decimal build using Mike Cowlishaw's decNumber library
 * FP_BINARY_INTEL: Binary build, but still using the Intel library for the
 *                  BASE->FLOAT conversions and for reading decimal state files
 * FP_BINARY: Binary build without any decimal library dependencies
 *
 * Note that the FP_BINARY target is currently incapable of reading decimal
 * state files, and both FP_BINARY and FP_DECNUM are missing some of the
 * BASE->FLOAT conversion functions. The goal is to at least eliminate all the
 * deficiencies of the FP_DECNUM target; if I can also make the FP_BINARY
 * target complete, that will eliminate the need for the FP_BINARY_INTEL
 * target, but I consider this last goal a very low priority.
 *
 * The old BCD_MATH option is still supported, and if none of the FP_* options
 * are used, the FP_BINARY_INTEL target will be selected if BCD_MATH is unset,
 * and the FP_INTEL target is selected if BCD_MATH is set.
 * If any of the FP_* options is used, BCD_MATH will be set for FP_INTEL and
 * FP_DECNUM, and unset for FP_BINARY_INTEL and FP_BINARY, overriding any
 * explicitly set value.
 *
 * The BCD_MATH macro is still used throughout the source code for conditional
 * compilation of decimal code, in those cases where it doesn't matter exactly
 * which decimal library is being used -- which is most of the time.
 */


#if (defined(FP_INTEL) + defined(FP_DECNUM) + defined(FP_BINARY_INTEL) + defined(FP_BINARY)) > 1
#error "Only one of FP_INTEL, FP_DECNUM, FP_BINARY_INTEL, or FP_BINARY should be defined."
#elif !defined(FP_INTEL) && !defined(FP_DECNUM) && !defined(FP_BINARY_INTEL) && !defined(FP_BINARY)
#if defined(BCD_MATH)
#define FP_INTEL 1
#else
#define FP_BINARY_INTEL 1
#endif
#endif

#if defined(FP_INTEL) || defined(FP_DECNUM)
#define BCD_MATH 1
#else
#undef BCD_MATH
#endif


#ifndef BCD_MATH
#include <math.h>
#endif

#define int2 short
#define uint2 unsigned short
#define int4 int
#define uint4 unsigned int
#define int8 long long
#define uint8 unsigned long long

#pragma STDC FP_CONTRACT OFF

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
/* I have tested big-endian state file compatibility in Fedora 12
 * running on qemu-system-ppc. I found that I needed to explicitly
 * set F42_BIG_ENDIAN for it to work; apparently the __BYTE_ORDER__
 * macro is not defined in such old compilers.
 * Also see the comment about setting BID_BIG_ENDIAN in
 * gtk/build-intel-lib.sh.
 */
#define F42_BIG_ENDIAN 1
#ifdef FP_DECNUM
#define DECLITEND 1
#endif
#endif

/* Magic number "24kF" for the state file. */
#define FREE42_MAGIC 0x466b3432
#define FREE42_MAGIC_STR "24kF"


#endif
