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

static inline size_t len(void *a) {
  if (a == NULL) {
    return 0;
  }
  return ((struct array_s *)(a))[-1].el_count;
}

static inline void del(void *a) {
  if (a != NULL) {
    free(((struct array_s *)(a)) - 1);
  }
}

static inline struct array_s *resize_f(struct array_s **vp, size_t el_size, size_t n) {
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

static inline int64_t getint() {
  int sign = 1;
  int count;
  size_t res = 0;
  while (count = getchar_unlocked(), isspace(count))
    ;
  if (count == '-') {
    sign = -1;
  } else {
    res = count - '0';
  }
  while (count = getchar_unlocked(), isdigit(count)) {
    res *= 10;
    res += count - '0';
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

typedef struct ct{
	int64_t count;
	char symbol;
}ct;

int icmp(ct*a,ct*string){
	if (a->count>string->count){
		return -1;
	}
	if (a->count<string->count){
		return 1;
	}
	return a->symbol-string->symbol;
}

int main(){
	char*string=0;
	int ch=0;
	while(!isspace(ch=getchar())){
		append(string,ch);
	}
	ct*count=0;
	resize(count,128);
	for (uint64_t w=0;w<len(count);++w){
		count[w].symbol=w;
		count[w].count=0;
	}
	for (uint64_t w=0;w<len(string);++w){
		count[(uint64_t)(string[w])].count++;
	}
	qsort(count,len(count),sizeof(count[0]),(cmp_f_t)icmp);
	for (uint64_t w=0;w<len(count);++w){
		if (count[w].count){
			printf("%c ",count[w].symbol);
			print(count[w].count);
		}
	}
  del(count);
  del(string);
}
