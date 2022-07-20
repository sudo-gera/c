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

static inline size_t len(void *matrix) {
  if (matrix == NULL) {
    return 0;
  }
  return ((struct array_s *)(matrix))[-1].el_count;
}

static inline void del(void *matrix) {
  if (matrix != NULL) {
    free(((struct array_s *)(matrix)) - 1);
  }
}

static inline struct array_s *resize_f(struct array_s **vp, size_t el_size, size_t n) {
  if (*vp == NULL) {
    *vp = (struct array_s *)calloc(1, sizeof(struct array_s));
    *vp += 1;
  }
  struct array_s *matrix = *vp - 1;
  assert(matrix->data == *(char **)vp);
  if (matrix->mem_size < n) {
    size_t cur_size = matrix->mem_size * el_size;
    size_t new_size;
    if (matrix->mem_size * 2 > n) {
      new_size = matrix->mem_size * 2 * el_size;
    } else {
      new_size = (n + 1) * el_size;
    }
    matrix = (struct array_s *)realloc(matrix, sizeof(struct array_s) + new_size);
    memset(matrix->data + matrix->mem_size * el_size, 0, new_size - cur_size);
    matrix->mem_size = new_size / el_size;
  }
  matrix->el_count = n;
  *vp = matrix + 1;
  return matrix + 1;
}
/////// resize(matrix, n) is resize_f(&matrix, sizeof(matrix[0]), n)
#define resize(matrix, n) (resize_f((struct array_s **)&(matrix), sizeof((matrix)[0]), (n)))
#define append(matrix, v) (resize((matrix), len(matrix) + 1), (matrix)[len(matrix) - 1] = (v))
#define pop(matrix) (resize((matrix), len(matrix) - 1), (matrix)[len(matrix)])

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
	uint64_t m=getint();
	int64_t**matrix=0;
	resize(matrix,n);
	for (uint64_t w=0;w<n;++w){
		resize(matrix[w],m);
		for (uint64_t e=0;e<m;++e){
			matrix[w][e]=getint();
		}
	}
	for (uint64_t q=0;q<n+m;++q){
		for (uint64_t w=0;w<n;++w){
			int64_t sum=0;
			for (uint64_t e=0;e<m;++e){
				sum+=matrix[w][e];
			}
			if (sum<0){
				printf("l ");
				print(w);
				for (uint64_t e=0;e<m;++e){
					matrix[w][e]*=-1;
				}
			}
		}
		for (uint64_t w=0;w<m;++w){
			int64_t sum=0;
			for (uint64_t e=0;e<n;++e){
				sum+=matrix[e][w];
			}
			if (sum<0){
				printf("c ");
				print(w);
				for (uint64_t e=0;e<n;++e){
					matrix[e][w]*=-1;
				}
			}
		}
	}
  for (uint64_t q=0;q<len(matrix);++q){
    del(matrix[q]);
  }
  del(matrix);
}
