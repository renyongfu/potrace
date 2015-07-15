
#include <stdio.h>
#include "auxiliary.h"

/* convert point_t to dpoint_t */
dpoint_t dpoint(point_t p) {
  dpoint_t res;
  res.x = p.x;
  res.y = p.y;
  return res;
}

/* range over the straight line segment [a,b] when lambda ranges over [0,1] */
dpoint_t interval(double lambda, dpoint_t a, dpoint_t b) {
  dpoint_t res;

  res.x = a.x + lambda * (b.x - a.x);
  res.y = a.y + lambda * (b.y - a.y);
  return res;
}

/* ---------------------------------------------------------------------- */
/* some useful macros. Note: the "mod" macro works correctly for
   negative a. Also note that the test for a>=n, while redundant,
   speeds up the mod function by 70% in the average case (significant
   since the program spends about 16% of its time here - or 40%
   without the test). The "floordiv" macro returns the largest integer
   <= a/n, and again this works correctly for negative a, as long as
   a,n are integers and n>0. */

/* integer arithmetic */

int mod(int a, int n) {
  return a>=n ? a%n : a>=0 ? a : n-1-(-1-a)%n;
}

int floordiv(int a, int n) {
  return a>=0 ? a/n : -1-(-1-a)/n;
}
