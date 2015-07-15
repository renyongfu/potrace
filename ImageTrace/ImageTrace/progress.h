/* Copyright (C) 2001-2015 Peter Selinger.
   This file is part of Potrace. It is free software and it is covered
   by the GNU General Public License. See the file COPYING for details. */

/* operations on potrace_progress_t objects, which are defined in
   potracelib.h. Note: the code attempts to minimize runtime overhead
   when no progress monitoring was requested. It also tries to
   minimize excessive progress calculations beneath the "epsilon"
   threshold. */

#ifndef PROGRESS_H
#define PROGRESS_H

/* structure to hold progress bar callback data */
struct progress_s {
  void (*callback)(double progress, void *privdata); /* callback fn */
  void *data;          /* callback function's private data */
  double min, max;     /* desired range of progress, e.g. 0.0 to 1.0 */
  double epsilon;      /* granularity: can skip smaller increments */
  double b;            /* upper limit of subrange in superrange units */
  double d_prev;       /* previous value of d */
};
typedef struct progress_s progress_t;

/* notify given progress object of current progress. Note that d is
   given in the 0.0-1.0 range, which will be scaled and translated to
   the progress object's range. */
void progress_update(double d, progress_t *prog) ;

/* start a subrange of the given progress object. The range is
   narrowed to [a..b], relative to 0.0-1.0 coordinates. If new range
   is below granularity threshold, disable further subdivisions. */
void progress_subrange_start(double a, double b, const progress_t *prog, progress_t *sub) ;

void progress_subrange_end(progress_t *prog, progress_t *sub) ;

#endif /* PROGRESS_H */

