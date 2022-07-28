#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <assert.h>
#include <iso646.h>

#define get_int(res)                                                       \
  \
{                                                                     \
    get_sign = 1;                                                          \
    while (get_c = getchar_unlocked(), isspace(get_c)) {                   \
    }                                                                      \
    if (get_c == '-') {                                                    \
      get_sign *= -1;                                                      \
      res = 0;                                                             \
    } else {                                                               \
      res = in_d[get_c];                                                   \
    }                                                                      \
    while (get_c = getchar_unlocked(), get_c != EOF and !isspace(get_c)) { \
      res *= in_base;                                                      \
      res += in_d[get_c];                                                  \
    }                                                                      \
    res *= get_sign;                                                       \
  \
}
int8_t get_sign;
int get_c;
char put_data[44];
unsigned long long put_t;
unsigned put_ds;
#define put_int(q)                                  \
  \
{                                              \
    if (q < 0) {                                    \
      putchar_unlocked('-');                        \
      put_t = -q;                                   \
    } else {                                        \
      put_t = q;                                    \
    }                                               \
    put_ds = 0;                                     \
    while (put_t) {                                 \
      put_data[++put_ds] = out_d[put_t % out_base]; \
      put_t /= out_base;                            \
    }                                               \
    if (put_ds == 0) {                              \
      putchar_unlocked('0');                        \
    }                                               \
    for (; put_ds; --put_ds) {                      \
      putchar_unlocked(put_data[put_ds]);           \
    }                                               \
  \
}

int main() {
  const char* in_d =
  "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11"
  "\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23"
  "\x24\x25\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x00\x01\x02\x03\x04\x05"
  "\x06\x07\x08\x09\x3a\x3b\x3c\x3d\x3e\x3f\x40\x0a\x0b\x0c\x0d\x0e\x0f\x10"
  "\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22"
  "\x23\x5b\x5c\x5d\x5e\x5f\x60\x0a\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14"
  "\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x7b\x7c\x7d"
  "\x7e\x7f";
  const char* out_d = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  long q;
  size_t in_base, out_base;
  scanf("%zu", &in_base);
  get_int(q);
  scanf("%zu", &out_base);
  put_int(q);
  putchar_unlocked('\n');
}
