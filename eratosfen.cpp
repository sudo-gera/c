#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <iso646.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define get(index) ((a[(index) / 8] >> (index) % 8) & 1)

#define add(index)                                                             \
  { a[(index) / 8] |= 1 << (index) % 8; }

#define del(index)                                                             \
  {                                                                            \
    a[(index) / 8] |= 1 << (index) % 8;                                        \
    a[(index) / 8] -= 1 << (index) % 8;                                        \
  }

int main() {
  size_t pc = 0;
  size_t n;
  scanf("%zu", &n);
  uint8_t *a = (uint8_t *)malloc((n + 1) / 8 + 8);
  for (size_t i = 0; i < n + 1; i++)
    add(i) for (size_t p = 2; p < n + 1; p++) {
      if (get(p) != 0) {
        pc += 1;
        for (size_t j = p * p; j < n + 1; j += p){
          del(j)
        }
      }
    }
  printf("%zu\n", pc);
}
