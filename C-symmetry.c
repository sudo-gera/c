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
#define back(a) (a[len(a)-1])

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

typedef struct dot{
	long x;
	long y;
	long z;
	long w;
}dot;

long cmp1l(dot*q,dot*e){
	if (q->x!=e->x){
		return q->x-e->x;
	}
	if (q->y!=e->y){
		return q->y-e->y;
	}
	return q->z-e->z;
}

int cmp1(dot*q,dot*e){
	long g=cmp1l(q,e);
	if (g<0){
		return -1;
	}
	if (g>0){
		return 1;
	}
	return 0;
}

#define bisect(b, e, ...)														\
	({																			\
		int64_t __begin = b;													\
		int64_t __end = e;														\
		assert(__begin <= __end);												\
		while (__begin + 1 < __end) {											\
			int64_t __center = (__begin + __end) / 2;							\
			if (__VA_ARGS__) {													\
				__end = __center;												\
			} else {															\
				__begin = __center;												\
			}																	\
		}																		\
		int64_t __center = __begin;												\
		if (__begin != __end and (__VA_ARGS__)) {								\
			__end = __center;													\
		}																		\
		__end;																	\
	})

int main(){
	size_t n=getint();
	dot*a=0;
	resize(a,n);
	for (long w=0;w<n;++w){
		a[w].x=getint();
		a[w].y=getint();
		a[w].z=getint();
		a[w].w=1;
	}
	// ic(itervect(a,a+len(a)))
	qsort(a,len(a),sizeof(a[0]),(cmp_f_t)cmp1);
	size_t e=1;
	for (size_t w=1;w<n;++w){
		if (cmp1(a+e-1,a+w)){
			a[e++]=a[w];
		}else{
			a[e-1].w++;
		}
	}
	resize(a,e);
	// ic(itervect(a,a+len(a)))
	n=e;
	dot doublecenter={.x=a[0].x+back(a).x,.y=a[0].y+back(a).y,.z=a[0].z+back(a).z};
	// ic(doublecenter)
	for (size_t w=0;w<n;++w){
		dot other={.x=doublecenter.x-a[w].x,.y=doublecenter.y-a[w].y,.z=doublecenter.z-a[w].z};
		size_t e=bisect(0,n,({
			bool ret=1;
			if (a[__center].z!=other.z){
				ret=a[__center].z>=other.z;
			}
			if (a[__center].y!=other.y){
				ret=a[__center].y>=other.y;
			}
			if (a[__center].x!=other.x){
				ret=a[__center].x>=other.x;
			}
			ret;
		}));
		// ic(other)
		if (e==n or cmp1(a+e,&other) or a[e].w!=a[w].w){
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
}
