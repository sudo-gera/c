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

struct array_s {
  size_t mem_size;
  size_t el_count;
  char data[0];
};

size_t len(void *a) {
  if (a == NULL) {
    return 0;
  }
  return ((struct array_s *)(a))[-1].el_count;
}

void del(void *a) {
  if (a != NULL) {
    free(((struct array_s *)(a)) - 1);
  }
}

struct array_s *resize_f(struct array_s **vp, size_t el_size, size_t n) {
  if (*vp == NULL) {
    *vp = (struct array_s *)calloc(1, sizeof(struct array_s));
    *vp += 1;
  }
  struct array_s *a = *vp - 1;
  assert(a->data == *(char **)vp);
  if (a->mem_size < n) {
    size_t cur_size = a->mem_size * el_size;
    size_t new_size;
    if (a->mem_size * 2 > n) {
      new_size = a->mem_size * 2 * el_size;
    } else {
      new_size = (n + 1) * el_size;
    }
    a = (struct array_s *)realloc(a, sizeof(struct array_s) + new_size);
    memset(a->data + a->mem_size * el_size, 0, new_size - cur_size);
    a->mem_size = new_size / el_size;
  }
  a->el_count = n;
  *vp = a + 1;
  return a + 1;
}
/////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
#define resize(a, n) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (n)))
#define append(a, v) (resize((a), len(a) + 1), (a)[len(a) - 1] = (v))
#define pop(a) (resize((a), len(a) - 1), (a)[len(a)])

int64_t getint() {
  int sign = 1;
  int c;
  size_t res = 0;
  while (c = getchar_unlocked(), isspace(c))
    ;
  if (c == '-') {
    sign = -1;
  } else {
    res = c - '0';
  }
  while (c = getchar_unlocked(), isdigit(c)) {
    res *= 10;
    res += c - '0';
  }
  return (int64_t)(res)*sign;
}

void putint(uint64_t out) {
  if (out > (1LLU << 63) - 1) {
    putchar_unlocked('-');
    out = 1 + ~out;
  }
  char data[44];
  char *dend = data;
  while (out) {
    *++dend = (unsigned)('0') + out % 10;
    out /= 10;
  }
  if (dend == data) {
    putchar_unlocked('0');
  }
  for (; dend != data; --dend) {
    putchar_unlocked(*dend);
  }
}

void print(uint64_t out) {
  putint(out);
  putchar('\n');
}

void write(uint64_t out) {
  putint(out);
  putchar(' ');
}

int main() {
  size_t *a = 0;
  for (uint64_t w = 0; w < 4; ++w) {
    append(a, getint());
  }
  print(len(a));
  for (uint64_t w = 0; w < len(a); ++w) {
    print(a[w]);
  }
  del(a);
}
