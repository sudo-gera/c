#ifndef assert
#include <assert.h>
#endif
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
		assert(*vp);
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
		assert(a);
		memset(a->data + a->mem_size * el_size, 0, new_size - cur_size);
		a->mem_size = new_size / el_size;
	}
	a->el_count = n;
	*vp = a + 1;
	return a + 1;
}
/////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
#ifdef __cplusplus
	template<typename T>
	auto resize(const T& a,uint64_t n){
		return (resize_f((struct array_s **)&(a), sizeof((a)[0]), (n)));
	}
	template<typename T,typename Y>
	auto append(const T& a,const Y& s){
		return (resize((a), len(a) + 1), (a)[len(a) - 1] = (s));
	}
	template<typename T>
	auto pop(const T& a){
		return (resize((a), len(a) - 1), (a)[len(a)]);
	}
	template<typename T>
	auto&back(const T& a){
		return ((a)[len(a)-1]);
	}
#else
	#define resize(a, ...) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (__VA_ARGS__)))
	#define append(a, ...) (resize((a), len(a) + 1), (a)[len(a) - 1] = (__VA_ARGS__))
	#define pop(a) (resize((a), len(a) - 1), (a)[len(a)])
	#define back(a) ((a)[len(a)-1])
#endif

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

uint64_t f(uint64_t x){
	return x&(x+1);
}

uint64_t g(uint64_t x){
	return x|(x+1);
}

long prefix(uint64_t x,uint64_t y,long**fen){
	long s = 0;
	for (uint64_t w=x;w<len(fen);w=f(w)-1){
		for (uint64_t e=y;e<len(fen[w]);e=f(e)-1){
			s += fen[w][e];
		}
	}
	return s;
}

void add(uint64_t x,uint64_t y,long**fen,int v) {
	for (uint64_t w = x; w < len(fen); w = g(w)) {
		for (uint64_t e = y; e < len(fen[w]); e = g(e)) {
			fen[w][e] += v;
		}
	}
}

int main(){
	char com[30];
	long**fen=0;
	resize(fen,1000);
	for (uint64_t w=0;w<len(fen);++w){
		resize(fen[w],1000);
	}
	long**a=0;
	resize(a,1000);
	for (uint64_t w=0;w<len(fen);++w){
		resize(a[w],1000);
	}
	while (1){
		com[0]=0;
		scanf(" %c",com);
		if (com[0]=='A'){
			long v,x,y;
			scanf("DD %li AT %li %li",&v,&x,&y);
			add(x,y,fen,v);
			a[x][y]+=v;
		}else
		if (com[0]=='R'){
			long x,y;
			scanf("EMOVE %li %li",&x,&y);
			add(x,y,fen,-a[x][y]);
			a[x][y]=0;
		}else
		if (com[0]=='C'){
			long v,x,y;
			scanf("HANGE AT %li %li TO %li",&x,&y,&v);
			add(x,y,fen,-a[x][y]+v);
			a[x][y]=v;
		}else
		if (com[0]=='S'){
			long x1,x2,y1,y2;
			scanf("UM FROM %li %li TO %li %li",&x1,&y1,&x2,&y2);
			print(
				 prefix(x2+0,y2+0,fen)
				-prefix(x1-1,y2+0,fen)
				-prefix(x2+0,y1-1,fen)
				+prefix(x1-1,y1-1,fen)
			);
		}else{
			break;
		}
		// while((com[0]=getchar())!='\n'){
		// }
	}
	for(uint64_t w=0;w<len(a);++w){
		del(a[w]);
	}
	del(a);
	for(uint64_t w=0;w<len(fen);++w){
		del(fen[w]);
	}
	del(fen);
}
