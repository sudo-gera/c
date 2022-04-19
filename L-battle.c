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

static inline size_t len(void *hp) {
	if (hp == NULL) {
		return 0;
	}
	return ((struct array_s *)(hp))[-1].el_count;
}

static inline void del(void *hp) {
	if (hp != NULL) {
		free(((struct array_s *)(hp)) - 1);
	}
}

static inline struct array_s *resize_f(struct array_s **vp, size_t el_size, size_t n) {
	if (*vp == NULL) {
		*vp = (struct array_s *)calloc(1, sizeof(struct array_s));
		*vp += 1;
	}
	struct array_s *hp = *vp - 1;
	assert(hp->data == *(char **)vp);
	if (hp->mem_size < n + 1) {
		size_t cur_size = hp->mem_size * el_size;
		size_t new_size;
		if (hp->mem_size * 2 > n) {
			new_size = hp->mem_size * 2 * el_size;
		} else {
			new_size = (n + 1) * el_size;
		}
		hp = (struct array_s *)realloc(hp, sizeof(struct array_s) + new_size);
		memset(hp->data + hp->mem_size * el_size, 0, new_size - cur_size);
		hp->mem_size = new_size / el_size;
	}
	hp->el_count = n;
	*vp = hp + 1;
	return hp + 1;
}
/////// resize(hp, n) is resize_f(&hp, sizeof(hp[0]), n)
#define resize(hp, n) (resize_f((struct array_s **)&(hp), sizeof((hp)[0]), (n)))
#define append(hp, v) (resize((hp), len(hp) + 1), (hp)[len(hp) - 1] = (v))
#define pop(hp) (resize((hp), len(hp) - 1), (hp)[len(hp)])

static inline int64_t getint() {
	int sign = 1;
	int q_hits;
	size_t res = 0;
	while (q_hits = getchar_unlocked(), isspace(q_hits))
		;
	if (q_hits == '-') {
		sign = -1;
	} else {
		res = q_hits - '0';
	}
	while (q_hits = getchar_unlocked(), isdigit(q_hits)) {
		res *= 10;
		res += q_hits - '0';
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

int64_t get_hits(long n,long p,long q,long*hp){
	int64_t b=0;
	int64_t e=(unsigned)(-1);
	while (b+1<e){
		int64_t q_hits=(b+e)/2;
		int64_t p_hits=0;
		for (int64_t w=0;w<n;++w){
			if (p!=q){
				if (hp[w]-q*q_hits>0){
					p_hits+=(hp[w]-q*q_hits)/(p-q);
					if ((hp[w]-q*q_hits)%(p-q)){
						p_hits+=1;
					}
				}
			}else{
				if (hp[w]-q*q_hits>0){
					p_hits=(unsigned)(-1);
				}
			}
		}
		if (p_hits>q_hits){
			b=q_hits;
		}else{
			e=q_hits;
		}
	}
	return e;
}

int main(){
	int64_t n=getint();
	int64_t p=getint();
	int64_t q=getint();
	int64_t*hp=0;
	resize(hp,n);
	for (int64_t w=0;w<n;++w){
		hp[w]=getint();
	}
	print(get_hits(n,p,q,hp));
	del(hp);
}
