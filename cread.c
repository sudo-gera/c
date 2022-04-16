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

size_t len(void *a) {
	if (a == NULL) {
		return 0;
	}
	return ((struct array_s *)(a))[-1].el_count;
}

void del(void *a) {
	if (a != NULL) {
		free(((struct array_s *)(a)) - 1);
	}
}

struct array_s *resize_f(struct array_s **vp, size_t el_size, size_t n) {
	if (*vp == NULL) {
		*vp = calloc(1, sizeof(struct array_s));
		*vp += 1;
	}
	struct array_s *a = *vp - 1;
	assert(a->data == *(char **)vp);
	if (a->mem_size < n) {
		if (a->mem_size * 2 > n) {
			a = realloc(a, sizeof(struct array_s) + el_size * a->mem_size * 2);
			memset(a->data + a->mem_size * el_size, 0, a->mem_size * el_size);
			a->mem_size *= 2;
		} else {
			size_t cur_size = a->mem_size * el_size;
			size_t new_size = (n + 1) * el_size;
			a = realloc(a, sizeof(struct array_s) + new_size);
			memset(a->data + a->mem_size * el_size, 0, new_size - cur_size);
			a->mem_size = n + 1;
		}
	}
	a->el_count = n;
	*vp = a + 1;
	return a + 1;
}
/////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
#define resize(a, n) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (n)))
#define append(a, v) (resize((a), len(a) + 1), (a)[len(a) - 1] = (v))
#define pop(a) (resize((a), len(a) - 1), (a)[len(a)])

int64_t get() {
	int sign = 1;
	int c;
	while (c = getchar_unlocked(), isspace(c))
		;
	size_t res = 0;
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

void put(uint64_t t) {
	if (t > (1LLU << 63) - 1) {
		putchar_unlocked('-');
		t = 1 + ~t;
	}
	char data[44];
	char* dp = data;
	while (t) {
		*++dp = (unsigned)('0') + t % 10;
		t /= 10;
	}
	if (dp == data) {
		putchar_unlocked('0');
	}
	for (; dp != data; --dp) {
		putchar_unlocked(*dp);
	}
}

void print(uint64_t t) {
	put(t);
	putchar('\n');
}

void write(uint64_t t) {
	put(t);
	putchar(' ');
}

int main() {
	size_t *a = 0;
	for (uint64_t w = 0; w < 4; ++w) {
		append(a, get());
	}
	printf("%zu\n", len(a));
	for (uint64_t w = 0; w < len(a); ++w) {
		print(a[w]);
	}
	del(a);
}
