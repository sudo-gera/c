#include <algorithm>
#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <iostream>
#include <iso646.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>
using namespace std;

static inline int64_t getint() {
  long n;
  cin >> n;
  return n;
}

static inline void putint(uint64_t out) {
  long n = long(out);
  cout << n;
}

static inline void print(uint64_t out) {
  putint(out);
  putchar('\n');
}

typedef int (*cmp_f_t)(const void *, const void *);

///////////////////////////////////////////////////end of lib

static long n = 0;
static long s = 0;
static long *a;
static long *b;
static long *c;
static long *z;

static long get(long _c) {
  for (long w = 0; w < n; w++) {
    if (c[w] >= _c) {
      z[w] = a[w];
    } else {
      z[w] = b[w];
    }
  }
  sort(z, z + n);
  long _s = 0;
  for (long w = 0; w < n and w < _c; w++) {
    _s += z[w];
  }
  if (_s > s) {
    return 1;
  } else {
    return 0;
  }
}

int main() {
  n = getint();
  s = getint();
  a = new long[unsigned(n)];
  b = new long[unsigned(n)];
  c = new long[unsigned(n)];
  z = new long[unsigned(n)];
  for (long w = 0; w < n; w++) {
    a[w] = getint();
    b[w] = getint();
    c[w] = getint();
  }
  long k;
  {
    int64_t __begin = 0;
    int64_t __end = n + 1;
    assert(__begin <= __end);
    while (__begin + 1 < __end) {
      int64_t __center = (__begin + __end) / 2;
      if (get(__center)) {
        __end = __center;
      } else {
        __begin = __center;
      }
    }
    int64_t __center = __begin;
    if (__begin != __end and (get(__center))) {
      __end = __center;
    }
    k = __end;
  }

  print(static_cast<unsigned long>(k - 1));
}
