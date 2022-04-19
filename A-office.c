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

static inline size_t len(void *h) {
  if (h == NULL) {
    return 0;
  }
  return ((struct array_s *)(h))[-1].el_count;
}

static inline void del(void *h) {
  if (h != NULL) {
    free(((struct array_s *)(h)) - 1);
  }
}

static inline struct array_s *resize_f(struct array_s **vp, size_t el_size, size_t n) {
  if (*vp == NULL) {
    *vp = (struct array_s *)calloc(1, sizeof(struct array_s));
    *vp += 1;
  }
  struct array_s *h = *vp - 1;
  assert(h->data == *(char **)vp);
  if (h->mem_size < n) {
    size_t cur_size = h->mem_size * el_size;
    size_t new_size;
    if (h->mem_size * 2 > n) {
      new_size = h->mem_size * 2 * el_size;
    } else {
      new_size = (n + 1) * el_size;
    }
    h = (struct array_s *)realloc(h, sizeof(struct array_s) + new_size);
    memset(h->data + h->mem_size * el_size, 0, new_size - cur_size);
    h->mem_size = new_size / el_size;
  }
  h->el_count = n;
  *vp = h + 1;
  return h + 1;
}
/////// resize(h, n) is resize_f(&h, sizeof(h[0]), n)
#define resize(h, n) (resize_f((struct array_s **)&(h), sizeof((h)[0]), (n)))
#define append(h, v) (resize((h), len(h) + 1), (h)[len(h) - 1] = (v))
#define pop(h) (resize((h), len(h) - 1), (h)[len(h)])

static inline int64_t getint() {
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

static inline void putint(uint64_t out) {
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

static inline void print(uint64_t out) {
  putint(out);
  putchar('\n');
}

static inline void write(uint64_t out) {
  putint(out);
  putchar(' ');
}

typedef int (*cmp_f_t)(const void *, const void *);

///////////////////////////////////////////////////end of lib

int main(){
	uint64_t n=getint();
	int64_t*entered=0;
	resize(entered,86420);
	int64_t*exited=0;
	resize(exited,86420);
	for (uint64_t w=0;w<n;++w){
		int64_t h,m,s;
		int c=0;
		while (not isdigit(c=getchar())){}
		h=(c-'0')*10;
		h+=(getchar()-'0');
		getchar();
		m=(getchar()-'0')*10;
		m+=(getchar()-'0');
		getchar();
		s=(getchar()-'0')*10;
		s+=(getchar()-'0');
		entered[h*3600+m*60+s]++;
		while (not isdigit(c=getchar())){}
		h=(c-'0')*10;
		h+=(getchar()-'0');
		getchar();
		m=(getchar()-'0')*10;
		m+=(getchar()-'0');
		getchar();
		s=(getchar()-'0')*10;
		s+=(getchar()-'0');
		exited[h*3600+m*60+s]++;
	}
	int64_t now=0;
	int64_t max_now=0;
	for (uint64_t w=0;w<86420;++w){
		now+=entered[w];
		if (now>max_now){
			max_now=now;
		}
		now-=exited[w];
	}
	putint(max_now);
  del(entered);
  del(exited);
}
