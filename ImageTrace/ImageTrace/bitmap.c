#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "bitmap.h"

/* free the given bitmap. Leaves errno untouched. */
void bm_free(potrace_bitmap_t *bm) {
  if (bm) {
    free(bm->map);
  }
  free(bm);
}

/* return new un-initialized bitmap. NULL with errno on error.
   Assumes w, h >= 0. */
potrace_bitmap_t *bm_new(int w, int h) {
  potrace_bitmap_t *bm;
  int dy = w == 0 ? 0 : (w - 1) / BM_WORDBITS + 1;
  size_t size = (size_t)dy * (size_t)h * (size_t)BM_WORDSIZE;

  /* check for overflow error */
  if (size < 0 || size / h / dy != BM_WORDSIZE) {
    errno = ENOMEM;
    return NULL;
  }

  bm = (potrace_bitmap_t *) malloc(sizeof(potrace_bitmap_t));
  if (!bm) {
    return NULL;
  }
  bm->w = w;
  bm->h = h;
  bm->dy = dy;
  bm->map = (potrace_word *) malloc(size);
  if (!bm->map) {
    free(bm);
    return NULL;
  }
  return bm;
}

/* clear the given bitmap. Set all bits to c. */
void bm_clear(potrace_bitmap_t *bm, int c) {
  /* Note: if the bitmap was created with bm_new, then it is
     guaranteed that size will fit into the size_t type. */
  size_t size = (size_t)bm->dy * (size_t)bm->h * (size_t)BM_WORDSIZE;
  memset(bm->map, c ? -1 : 0, size);
}

/* duplicate the given bitmap. Return NULL on error with errno set. */
potrace_bitmap_t *bm_dup(const potrace_bitmap_t *bm) {
  potrace_bitmap_t *bm1 = bm_new(bm->w, bm->h);
  size_t size = (size_t)bm->dy * (size_t)bm->h * (size_t)BM_WORDSIZE;
  if (!bm1) {
    return NULL;
  }
  memcpy(bm1->map, bm->map, size);
  return bm1;
}

/* invert the given bitmap. */
void bm_invert(potrace_bitmap_t *bm) {
  size_t i;
  size_t size = (size_t)bm->dy * (size_t)bm->h;

  for (i = 0; i < size; i++) {
    bm->map[i] ^= BM_ALLBITS;
  }
}