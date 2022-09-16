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
	if (a->mem_size < n + 1) {
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

size_t get(int l,int64_t**a,int64_t**b,int i,int j){
	size_t z=0,x,c,v=l-1;
	while(v-z>2){
		x=(z+z+v)/3;
		c=(z+v+v)/3;
		int64_t _b=a[i-1][x]>b[j-1][x]?a[i-1][x]:b[j-1][x];
		int64_t _n=a[i-1][c]>b[j-1][c]?a[i-1][c]:b[j-1][c];
		if (_b<_n){
			v=c;
		}
		if (_b>_n){
			z=x;
		}
		if (_b==_n){
			z=x;
			v=c;
		}
	}
	size_t m=1000000000000000;
	size_t k=0;
	for (size_t e=z;e<v+1;++e){
		int64_t z=a[i-1][e]>b[j-1][e]?a[i-1][e]:b[j-1][e];
		if (z<m){
			k=e+1;
			m=z;
		}
	}
	return k;
}

int main(){
	int n=getint(),m=getint(),l=getint();
	int64_t**a=0;
	resize(a,n);
	for (size_t w=0;w<n;++w){
		resize(a[w],l);
		for (size_t e=0;e<l;++e){
			a[w][e]=getint();
			a[w][e]*=10000;
			a[w][e]+=e;
		}
	}
	int64_t**b=0;
	resize(b,m);
	for (size_t w=0;w<m;++w){
		resize(b[w],l);
		for (size_t e=0;e<l;++e){
			b[w][e]=getint();
			b[w][e]*=10000;
			b[w][e]+=999-e;
		}
	}
	int q=getint();
	for (size_t w=0;w<q;++w){
		int i=getint(),j=getint();
		print(get_k(l,a,b,i,j));
	}
	for (size_t w=0;w<n;++w){
		del(a[w]);
	}
	del(a);
	for (size_t w=0;w<m;++w){
		del(b[w]);
	}
	del(b);
}
