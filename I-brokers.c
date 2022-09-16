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

int cmp1(uint64_t*a, uint64_t*b){
	if (*a<*b){
		return 1;
	}
	if (*a>*b){
		return -1;
	}
	return 0;
}

typedef long T;

typedef struct heap {
	T *data;
	size_t size;
	bool (*F)();
} heap;

heap heap_c(bool (*f)(), T *d) {
	heap t;
	t.data = d;
	t.size = 0;
	t.F = f;
	return t;
}

void insert(heap *t, T q) {
	t->data[t->size++] = q;
	t->data--;
	size_t current = t->size;
	while (current > 1 and t->F(t->data[current], t->data[current / 2])) {
		T _t = t->data[current];
		t->data[current] = t->data[current / 2];
		t->data[current / 2] = _t;
		current = current / 2;
	}
	t->data++;
}
void erase(heap *t) {
	assert(t->size);
	t->data[0] = t->data[t->size - 1];
	t->data--;
	size_t current = 1;
	while (2 * current + 1 < t->size and
				 (t->F(t->data[2 * current], t->data[current]) or
					t->F(t->data[2 * current + 1], t->data[current]))) {
		if (t->F(t->data[2 * current], t->data[2 * current + 1])) {
			T _t = t->data[current];
			t->data[current] = t->data[current * 2];
			t->data[current * 2] = _t;
			current = current * 2;
		} else {
			T _t = t->data[current];
			t->data[current] = t->data[current * 2 + 1];
			t->data[current * 2 + 1] = _t;
			current = current * 2 + 1;
		}
	}
	if (2 * current < t->size and t->F(t->data[2 * current], t->data[current])) {
		T _t = t->data[current];
		t->data[current] = t->data[current * 2];
		t->data[current * 2] = _t;
		current = current * 2;
	}
	t->data++;
	t->size--;
}

bool is_greater(long q, long w) { return q > w; }

bool is_less(long q, long w) { return q < w; }

int main(){
	uint64_t n = getint();
	heap c = heap_c(is_less, malloc(sizeof(long) * 1000000));
	for (uint64_t i=0; i<n; i++){
		insert(&c,getint());
	}
	uint64_t res=0;
	while (c.size>1){
		uint64_t tmp=*c.data;
		erase(&c);
		tmp+=*c.data;
		erase(&c);
		insert(&c,tmp);
		res+=tmp;
	}
	printf("%.2f\n",res/100.);
	free(c.data);
}
