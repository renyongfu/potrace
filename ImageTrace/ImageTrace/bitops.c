
#include "bitops.h"
#if !defined(HAVE_I386)
unsigned int lobit(unsigned int x) {
    unsigned int res = 32;
    while (x & 0xffffff) {
        x <<= 8;
        res -= 8;
    }
    while (x) {
        x <<= 1;
        res -= 1;
    }
    return res;
}

unsigned int hibit(unsigned int x) {
    unsigned int res = 0;
    while (x > 0xff) {
        x >>= 8;
        res += 8;
    }
    while (x) {
        x >>= 1;
        res += 1;
    }
    return res;
}

#endif