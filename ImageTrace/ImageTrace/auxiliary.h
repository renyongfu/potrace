/* Copyright (C) 2001-2015 Peter Selinger.
   This file is part of Potrace. It is free software and it is covered
   by the GNU General Public License. See the file COPYING for details. */

/* This header file collects some general-purpose macros (and static
   inline functions) that are used in various places. */

#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <stdlib.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* ---------------------------------------------------------------------- */
/* point arithmetic */

#include "potracelib.h"
struct point_s {
  long x;
  long y;
};
typedef struct point_s point_t;

typedef potrace_dpoint_t dpoint_t;

/* convert point_t to dpoint_t */
dpoint_t dpoint(point_t p);

/* range over the straight line segment [a,b] when lambda ranges over [0,1] */
dpoint_t interval(double lambda, dpoint_t a, dpoint_t b);

/* ---------------------------------------------------------------------- */
/* some useful macros. Note: the "mod" macro works correctly for
   negative a. Also note that the test for a>=n, while redundant,
   speeds up the mod function by 70% in the average case (significant
   since the program spends about 16% of its time here - or 40%
   without the test). The "floordiv" macro returns the largest integer
   <= a/n, and again this works correctly for negative a, as long as
   a,n are integers and n>0. */

/* integer arithmetic */

int mod(int a, int n) ;

int floordiv(int a, int n);

/* Note: the following work for integers and other numeric types. */
#undef sign
#undef abs
#undef min
#undef max
#undef sq
#undef cu
#define sign(x) ((x)>0 ? 1 : (x)<0 ? -1 : 0)
#define abs(a) ((a)>0 ? (a) : -(a))
#define min(a,b) ((a)<(b) ? (a) : (b))
#define max(a,b) ((a)>(b) ? (a) : (b))
#define sq(a) ((a)*(a))
#define cu(a) ((a)*(a)*(a))

#endif /* AUXILIARY_H */
