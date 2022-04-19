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

uint64_t merge_count(int64_t*b,int64_t*e){
	uint64_t n=e-b;
	if (n<2){
		return 0;
	}
	int64_t*c=b+n/2;
	uint64_t res=0;
	res+=merge_count(b,c);
	res+=merge_count(c,e);
	int64_t*tmp=0;
	int64_t*l=b,*r=c;
	for (;l!=c and r!=e;){
		if (*l>*r){
			res+=c-l;
			append(tmp,*r);
			r++;
		}else{
			append(tmp,*l);
			l++;
		}
	}
	while (l!=c){
		append(tmp,*l);
		l++;
	}
	while (r!=e){
		res+=c-l;
		append(tmp,*r);
		r++;
	}
	memcpy(b,tmp,len(tmp)*sizeof(tmp[0]));
	del(tmp);
	return res;
}

int main(){
	uint64_t n=getint();
	int64_t*a=0;
	resize(a,n);
	for (uint64_t l=0;l<n;++l){
		a[l]=getint();
	}
	print(merge_count(a,a+len(a)));
	del(a);
}
