#include "treap.hpp"

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
	if (c==EOF){return -1;}
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
	uint64_t n=getint();
	std::vector<long> a;
	for (uint64_t w=0;w<n;++w){
		a.push_back(getint());
	}
	uint64_t qq=getint();
	for (uint64_t w=0;w<qq;++w){
		uint64_t q=getint();
		if (q==-1){
			break;
		}
		if (q==1){
			uint64_t l=getint(),r=getint()+1;
			// auto s=a.cut_left(r);
			// auto d=s.cut_left(l);
			// print(s.sum());
			// s.add_left(d);
			// a.add_left(s);
			long s=0;
			for (uint64_t w=l;w<r;w++){
				s+=a[w];
			}
			print(s);
		}
		if (q==2){
			long x=getint();
			uint64_t u=getint();
			a.insert(u+a.begin(),x);
		}
		if (q==3){
			uint64_t u=getint();
			a.erase(a.begin()+u);
		}
		if (q==4){
			long x=getint();
			uint64_t l=getint(),r=getint()+1;
			// auto s=a.cut_left(r);
			// auto d=s.cut_left(l);
			// s.mul(0);
			// s.add(x);
			// s.add_left(d);
			// a.add_left(s);
			for (uint64_t w=l;w<r;w++){
				a[w]=x;
			}
		}
		if (q==5){
			long x=getint();
			uint64_t l=getint(),r=getint()+1;
			// auto s=a.cut_left(r);
			// auto d=s.cut_left(l);
			// s.add(x);
			// s.add_left(d);
			// a.add_left(s);
			for (uint64_t w=l;w<r;w++){
				a[w]+=x;
			}
		}
		if (q==6){
			uint64_t l=getint(),r=getint()+1;
			// auto s=a.cut_left(r);
			// auto d=s.cut_left(l);
			// s.next_permutation();
			// s.add_left(d);
			// a.add_left(s);
			std::next_permutation(a.begin()+l,a.begin()+r);
		}
		if (q==7){
			uint64_t l=getint(),r=getint()+1;
			// auto s=a.cut_left(r);
			// auto d=s.cut_left(l);
			// s.prev_permutation();
			// s.add_left(d);
			// a.add_left(s);
			std::prev_permutation(a.begin()+l,a.begin()+r);
		}
	}
	for (uint64_t w=0;w<a.size();++w){
		write(a[w]);
	}
	putchar(10);
}
