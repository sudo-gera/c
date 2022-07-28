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

int main() {
  char a[1024];
  scanf("%s", a);
  double r = 0, p = 1;
  size_t df = 0;
  size_t la = strlen(a);
  for (size_t w = 0; w < la; ++w) {
    if (a[w] == '.') {
      df = 1;
    } else {
      r *= 2;
      r += a[w] - '0';
      if (df) {
        p *= 2;
      }
    }
  }
  r /= p;
  printf("%.12f\n", r);
}
