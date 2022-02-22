#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <iso646.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>


#define bit_get(a, s)                                                          \
  (((a)[(s) / 8 / sizeof((a)[0])] >> (s) % (8 * sizeof((a)[0]))) & 1)
#define bit_set(a, s, d)                                                       \
  {                                                                            \
    (a)[(s) / 8 / sizeof((a)[0])] &= ~(1 << (s) % (8 * sizeof((a)[0])));       \
    (a)[(s) / 8 / sizeof((a)[0])] += (d) << (s) % (8 * sizeof((a)[0]));        \
  }

// union data
//   {
//     uint64_t u64;
//     uint8_t arr[8];
//     uint32_t a32[2];
//   };

void rev(size_t *q) {
  for (size_t w = 0; w < 32; ++w) {
    size_t t = bit_get(q, w);
    bit_set(q, w, bit_get(q, 63 - w));
    bit_set(q, 63 - w, t);
  }
}

union data convert(union data x) {
  rev((size_t *)(&x.u64));
  rev((size_t *)(x.arr));
  rev((size_t *)(x.a32));
  return x;
}
