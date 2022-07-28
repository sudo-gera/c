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

#define END 1024

int main() {
  char a[END + 1];
  char s[END + 1];
  a[END] = 0;
  s[END] = 0;
  scanf("%s", a);
  scanf("%s", s);
  size_t la = strlen(a);
  size_t ls = strlen(s);
  for (size_t w = 0; w * 2 < la; ++w) {
    char t = a[w];
    a[w] = a[la - 1 - w];
    a[la - 1 - w] = t;
  }
  for (size_t w = 0; w * 2 < ls; ++w) {
    char t = s[w];
    s[w] = s[ls - 1 - w];
    s[ls - 1 - w] = t;
  }
  for (size_t w = la; w < END; ++w) {
    a[w] = '0';
  }
  for (size_t w = ls; w < END; ++w) {
    s[w] = '0';
  }
  for (size_t w = 0; w < END; ++w) {
    if (a[w] == '$') {
      a[w] = '/';
    }
  }
  for (size_t w = 0; w < END; ++w) {
    if (s[w] == '$') {
      s[w] = '/';
    }
  }
  long buff = 0;
  for (size_t w = 0; w < END; ++w) {
    buff += a[w] - '0';
    buff += s[w] - '0';
    if ((buff % 3 + 3) % 3 == 2) {
      a[w] = -1;
    } else {
      a[w] = (buff % 3 + 3) % 3;
    }
    buff -= a[w];
    a[w] += '0';
    buff /= 3;
  }
  la = END;
  for (size_t w = END - 1; w >= 1; --w) {
    // assert(w >= 0);
    assert(w < END);
    if (a[w] != '0') {
      break;
    }
    la = w;
  }
  a[la] = 0;
  for (size_t w = 0; w * 2 < la; ++w) {
    char t = a[w];
    a[w] = a[la - 1 - w];
    a[la - 1 - w] = t;
  }
  for (size_t w = 0; w < END; ++w) {
    if (a[w] == '/') {
      a[w] = '$';
    }
  }
  printf("%s\n", a);
}
