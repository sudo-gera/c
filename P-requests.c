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

typedef struct tree{
	long*data;
	long (*f)(long,long);
	uint64_t p;
	uint64_t b;
	uint64_t e;
}tree;

long*tree_access(tree*t){
	assert(t->b<t->e and t->e<=t->p);
	return t->data+(t->p+t->b)/(t->e-t->b);
}

long tree_init(tree*t){
	uint64_t b=t->b;
	uint64_t e=t->e;
	assert(b<e and e<=t->p);
	long r=0;
	if (b+1==e){
		r=tree_access(t)[0];
	}else{
		uint64_t c=(b+e)/2;
		t->b=b;
		t->e=c;
		long z=tree_init(t);
		t->b=c;
		t->e=e;
		long x=tree_init(t);
		r=t->f(z,x);
		t->b=b;
		t->e=e;
		tree_access(t)[0]=r;
	}
	t->b=b;
	t->e=e;
	return r;
}

tree*tree_create(uint64_t n,long*s,long (*f)(long,long)){
	uint64_t p=1;
	uint64_t g=n;
	while (n){
		n/=2;
		p*=2;
	}
	n=g;
	tree*q=(tree*)calloc(1,sizeof(tree));
	q->f=f;
	q->p=p;
	q->b=0;
	q->e=p;
	resize(q->data,p*2);
	if (s){
		memcpy(q->data+p,s,g*sizeof(s[0]));
	}
	tree_init(q);
	assert(q->b==0);
	assert(q->e==p);
	return q;
}

void tree_del(tree*t){
	if (t){
		del(t->data);
		free(t);
	}
}

void tree_add(uint64_t u,long v,tree*t){
	uint64_t b=t->b;
	uint64_t e=t->e;
	assert(b<=u and u<e and e<=t->p);
	long*l=tree_access(t);
	if (b+1==e){
		l[0]=t->f(l[0],v);
	}else{
		uint64_t c=(b+e)/2;
		l[0]=t->f(l[0],v);
		if (u<c){
			t->b=b;
			t->e=c;
			tree_add(u,v,t);
			assert(t->b==b);
			assert(t->e==c);
		}else{
			t->b=c;
			t->e=e;
			tree_add(u,v,t);
			assert(t->b==c);
			assert(t->e==e);
		}
	}
	t->b=b;
	t->e=e;
}

void tree_add(uint64_t ub,uint64_t ue,long v,tree*t){
	uint64_t b=t->b;
	uint64_t e=t->e;
	assert(b<=ub and ub<=ue and ue<=e and e<=t->p);
	long*l=tree_access(t);
	if (b+1==e){
		l[0]=t->f(l[0],v);
	}else{
		uint64_t c=(b+e)/2;
		l[0]=t->f(l[0],v);
		if (u<c){
			t->b=b;
			t->e=c;
			tree_add(u,v,t);
			assert(t->b==b);
			assert(t->e==c);
		}else{
			t->b=c;
			t->e=e;
			tree_add(u,v,t);
			assert(t->b==c);
			assert(t->e==e);
		}
	}
	t->b=b;
	t->e=e;
}

long tree_get(uint64_t ub,uint64_t ue,tree*t){
	uint64_t b=t->b;
	uint64_t e=t->e;
	uint64_t c=(b+e)/2;
	long r=0;
	if (ub==ue){
		r=0;
	}else
	if (ub==b and ue==e){
		t->b=b;
		t->e=e;
		r=tree_access(t)[0];
	}else
	if (b<=ub and ue<=c){
		t->b=b;
		t->e=c;
		r=tree_get(ub,ue,t);
		assert(t->b==b);
		assert(t->e==c);
	}else
	if (c<=ub and ue<=e){
		t->b=c;
		t->e=e;
		r=tree_get(ub,ue,t);
		assert(t->b==c);
		assert(t->e==e);
	}else{
		t->b=b;
		t->e=c;
		long z=tree_get(ub,c,t);
		assert(t->b==b);
		assert(t->e==c);
		t->b=c;
		t->e=e;
		long x=tree_get(c,ue,t);
		assert(t->b==c);
		assert(t->e==e);
		r=t->f(z,x);
	}
	t->b=b;
	t->e=e;
	return r;
}

void tree_set(uint64_t u,long v,tree*t){
	uint64_t b=t->b;
	uint64_t e=t->e;
	assert(b<=u and u<e and e<=t->p);
	long z=tree_get(b,u,t);
	assert(t->b==b);
	assert(t->e==e);
	long x=tree_get(u+1,e,t);
	assert(t->b==b);
	assert(t->e==e);
	long*l=tree_access(t);
	l[0]=t->f(t->f(z,v),x);
	uint64_t c=(b+e)/2;
	if (b+1!=e){
		if (u<c){
			t->b=b;
			t->e=c;
			tree_set(u,v,t);
			assert(t->b==b);
			assert(t->e==c);
		}else{
			t->b=c;
			t->e=e;
			tree_set(u,v,t);
			assert(t->b==c);
			assert(t->e==e);
		}
	}
	t->b=b;
	t->e=e;
}

long _xor(long q,long e){
	return q^e;
}

long _max(long q,long e){
	return max(q,e);
}

int main(){
	uint64_t n=getint();
	uint64_t m=getint();
	long*v=0;
	resize(v,n);
	for (uint64_t w=0;w<n;++w){
		v[w]=getint();
	}
	tree*maxt=tree_create(n,v,_max);
	tree*xort=tree_create(n,v,_xor);
	for (uint64_t w=0;w<m;++w){
		// for (uint64_t r=0;r<n;++r){
		// 	write(tree_get(r,r+1,maxt));
		// }
		// putchar('\n');
		// for (uint64_t r=0;r<n;++r){
		// 	write(tree_get(r,r+1,xort));
		// }
		// putchar('\n');
		uint64_t q=getint();
		if (q==1){
			uint64_t l=getint(),r=getint()+1;
			print(tree_get(l,r,xort));
		}
		if (q==2){
			uint64_t l=getint(),r=getint()+1;
			print(tree_get(l,r,maxt));
		}
		if (q==3){
			uint64_t l=getint();
			long v=getint();
			tree_set(l,v,maxt);
			tree_set(l,v,xort);
			// long h=tree_get(l,l+1,xort);
			// h^=v;
			// tree_add(l,h,xort);
		}
	}
	del(v);
	tree_del(maxt);
	tree_del(xort);
}
