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

#ifdef print
#undef print
#endif
#ifdef write
#undef write
#endif
static inline void print(uint64_t);
void _assert(bool f){
	while (!f){
		print(0);
	}
}

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
		_assert(*vp);
		*vp += 1;
	}
	struct array_s *a = *vp - 1;
	assert(a->data == *(char **)vp);
	if (a->mem_size < n + 1) {
		size_t cur_size = a->mem_size * el_size;
		size_t new_size;
		if (a->mem_size * 2 > n) {
			new_size = a->mem_size * 2 * el_size;
		} else {
			new_size = (n + 1) * el_size;
		}
		a = (struct array_s *)realloc(a, sizeof(struct array_s) + new_size);
		_assert(a);
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

#define min(a,s) ((a)<(s)?(a):(s))
#define max(a,s) ((a)>(s)?(a):(s))

typedef int (*cmp_f_t)(const void *, const void *);

///////////////////////////////////////////////////end of lib



int main(){
	// perf();
	uint64_t n=getint();
	uint64_t m=getint();
	int**a=0;
	resize(a,1);
	resize(a[0],n);
	for (uint64_t w=0;w<n;++w){
		a[0][w]=getint();
	}
	uint64_t la=0;
	uint64_t j=n;
	while (j){
		j/=2;
		la++;
	}
	resize(a,la);
	for (uint64_t k=1;;k++){
		uint64_t p=1LLU<<(k-1);
		if (p*2>n){
			break;
		}
		// p/=2;
		int*ak_1=a[k-1];
		uint64_t lak_1p=len(ak_1)-p;
		// if (lak_1p>n){
		// 	break;
		// }
		resize(a[k],lak_1p);
		int*ak=a[k];
		for (uint64_t w=0,t=p;w<lak_1p;++w,++t){
			ak[w]=max(ak_1[w],ak_1[t]);
		}
	}
	// perf();
	for (uint64_t w=0;w<m;++w){
		uint64_t x=getint(),y=getint()+1;
		uint64_t k=-1;
		uint64_t d=y-x;
		while(d){
			k++;
			d/=2;
		}
		int*ak=a[k];
		print(max(ak[x],ak[y-(1<<k)]));
	}
	// perf();
	for (uint64_t w=0;w<len(a);++w){
		del(a[w]);
	}
	del(a);
}
