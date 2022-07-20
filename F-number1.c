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

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct num{
	char*b;
	char*e;
}num;

num num_cc(char*d){
	num t;
	t.e=d;
	--d;
	while(*d!='\n'){
		--d;
	}
	++d;
	t.b=d;
	return t;
}

num num_c(){
	num t;
	t.b=0;
	t.e=0;
	return t;
}

bool is_less(num q,num e){
	num z=q,x=e;
	while (q.b!=q.e and e.e!=e.b){
		if (q.b[0]!=e.b[0]){
			return q.b[0]<e.b[0];
		}
		q.b+=1;
		e.b+=1;
	}
	if (q.b==q.e and e.b==e.e){
		return false;
	}else
	if (q.b==q.e){
		q=x;
		q.e=q.b+(e.e-e.b);
		return is_less(q,e);
	}else
	if (e.b==e.e){
		e=z;
		e.e=e.b+(q.e-q.b);
		return is_less(q,e);
	}
	return false;
}

int ncmp(num*q,num*e){
	if (is_less(*q,*e)){
		return -1;
	}
	if (is_less(*e,*q)){
		return 1;
	}
	return 0;
}

int cmp1(char**q,char**w){
	for (size_t e=0;e<len(*w)*len(*q);++e){
		if (q[0][e%len(*q)]!=w[0][e%len(*w)]){
			return -q[0][e%len(*q)]+w[0][e%len(*w)];
		}
	}
	return 0;
}

int main(){
	int c;
	char**nums=0;
	size_t b=1;
	while ((c=getchar())!=EOF){
		if (isdigit(c)){
			if (b){
				resize(nums,len(nums)+1);
				nums[len(nums)-1]=0;
				// append(nums,0);
			}
			resize(nums[len(nums)-1],len(nums[len(nums)-1])+1);
			nums[len(nums)-1][len(nums[len(nums)-1])-1]=c;
			// append(nums[len(nums)-1],c);
			b=0;
		}else{
			b=1;
		}
	}
	qsort(nums,len(nums),sizeof(nums[0]),(cmp_f_t)cmp1);
	for (size_t w=0;w<len(nums);w++){
		printf("%s",nums[w]);
	}
	putchar(10);
}
