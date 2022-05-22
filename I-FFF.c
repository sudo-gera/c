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
#include <stddef.h>

#ifdef print
#undef print
#endif

#ifdef write
#undef write
#endif

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
#define resize(a, ...) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (__VA_ARGS__)))
#define append(a, ...) (resize((a), len(a) + 1), (a)[len(a) - 1] = (__VA_ARGS__))
#define pop(a) (resize((a), len(a) - 1), (a)[len(a)])
#define back(a) ((a)[len(a)-1])

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

#include <map>
#include <algorithm>

int prefix(uint64_t x, uint64_t y, uint64_t z) {
	int s = 0;
	for (uint64_t lx = x; lx < 128; lx = f(lx) - 1) {
		for (uint64_t ly = y; ly < 128; ly = f(ly) - 1) {
			for (uint64_t lz = z; lz < 128; lz = f(lz) - 1) {
				s += fen[lx][ly][lz];
			}
		}
	}
	return s;
}

void add(uint64_t x,uint64_t y,int v,uint64_t*d,) {
	for (uint64_t lx = x; lx < 128; lx = g(lx)) {
		for (uint64_t ly = y; ly < 128; ly = g(ly)) {
			for (uint64_t lz = z; lz < 128; lz = g(lz)) {
				fen[lx][ly][lz] += v;
			}
		}
	}
}


int main(){
	uint64_t n=getint();
	uint64_t*a=0;
	resize(a,n*3);
	for (uint64_t w=0;w<3*n;++w){
		a[w]=getint();
	}
	// uint64_t*unzip_x=0;
	// uint64_t*unzip_y=0;
	// resize(unzip_x,n);
	// resize(unzip_y,n);
	// for (uint64_t w=0;w<n;++w){
	// 	unzip_x[w]=a[3*w+0];
	// 	unzip_y[w]=a[3*w+1];
	// }
	// std::sort(unzip_x,unzip_x+len(unzip_x));
	// std::sort(unzip_y,unzip_y+len(unzip_y));
	// std::map<uint64_t,uint64_t> zip_x;
	// std::map<uint64_t,uint64_t> zip_y;
	// for (uint64_t w=0;w<n;++w){
	// 	zip_x[unzip_x[w]]=w;
	// }
	// for (uint64_t w=0;w<n;++w){
	// 	zip_y[unzip_y[w]]=w;
	// }
	// for (uint64_t w=0;w<n;++w){
	// 	a[w*3+0]=zip_x[a[w*3+0]];
	// 	a[w*3+1]=zip_y[a[w*3+1]];
	// }
	uint64_t m=getint();
	char com[30];
	for (uint64_t w=0;w<m;++w){
		scanf("%20s",com);
		uint64_t c=getint(),v=getint();

	}
}
