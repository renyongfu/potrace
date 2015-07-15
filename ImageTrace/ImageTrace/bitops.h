/* Copyright (C) 2001-2015 Peter Selinger.
   This file is part of Potrace. It is free software and it is covered
   by the GNU General Public License. See the file COPYING for details. */


/* bits.h: this file defines some macros for bit manipulations. We
   provide a generic implementation, as well as machine- and
   compiler-specific fast implementations */

/* lobit: return the position of the rightmost "1" bit of an int, or
   32 if none. hibit: return 1 + the position of the leftmost "1" bit
   of an int, or 0 if none. Note: these functions work on 32-bit
   integers. */

#ifndef BITOPS_H
#define BITOPS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* ---------------------------------------------------------------------- */
/* machine specific macros */

#if defined(HAVE_I386)

unsigned int lobit(unsigned int x) {
  unsigned int res;
  asm ("bsf	%1,%0\n\t"
       "jnz	0f\n\t"
       "movl	$32,%0\n"
       "0:"
       : "=r" (res)
       : "r" (x)
       : "cc");
  return res;
}

unsigned int hibit(unsigned int x) {
  unsigned int res;					

  asm ("bsr	%1,%0\n\t"
       "jnz	0f\n\t"
       "movl	$-1,%0\n"
       "0:"
       : "=r" (res)
       : "r" (x)
       : "cc");
  return res+1;
}

/* ---------------------------------------------------------------------- */
#else /* generic macros */

unsigned int lobit(unsigned int x) ;

unsigned int hibit(unsigned int x);

#endif 

#endif /* BITOPS_H */
