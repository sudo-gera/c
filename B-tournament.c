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

// struct array_s {
//  size_t mem_size;
//  size_t el_count;
//  char data[0];
// };

// static inline size_t len(void *arr) {
//  if (arr == NULL) {
//    return 0;
//  }
//  return ((struct array_s *)(arr))[-1].el_count;
// }

// static inline void del(void *arr) {
//  if (arr != NULL) {
//    free(((struct array_s *)(arr)) - 1);
//  }
// }

// static inline struct array_s *resize_f(struct array_s **vp, size_t el_size,
// size_t n) {  if (*vp == NULL) {    *vp = (struct array_s *)calloc(1,
// sizeof(struct array_s));     *vp += 1;
//  }
//  struct array_s *arr = *vp - 1;
//  assert(arr->data == *(char **)vp);
//  if (arr->mem_size < n + 1) {
//    size_t cur_size = arr->mem_size * el_size;
//    size_t new_size;
//    if (arr->mem_size * 2 > n) {
//      new_size = arr->mem_size * 2 * el_size;
//    } else {
//      new_size = (n + 1) * el_size;
//    }
//    arr = (struct array_s *)realloc(arr, sizeof(struct array_s) +
// new_size);     memset(arr->data + arr->mem_size * el_size, 0, new_size - cur_size);
//    arr->mem_size = new_size / el_size;
//  }
//  arr->el_count = n;
//  *vp = arr + 1;
//  return arr + 1;
// }
// /////// resize(arr, n) is resize_f(&arr, sizeof(arr[0]), n)
// #define resize(arr, ...) (resize_f((struct array_s **)&(arr), sizeof((arr)[0]),
// (__VA_ARGS__))) #define append(arr, ...) (resize((arr), len(arr) + 1), (arr)[len(arr) -
// 1] = (__VA_ARGS__)) #define pop(arr) (resize((arr), len(arr) - 1), (arr)[len(arr)])
// #define back(arr) (arr[len(arr)-1])

// static inline int64_t getint() {
//  int sign = 1;
//  int c;
//  size_t res = 0;
//  while (c = getchar_unlocked(), isspace(c))
//    ;
//  if (c == '-') {
//    sign = -1;
//  } else {
//    res = c - '0';
//  }
//  while (c = getchar_unlocked(), isdigit(c)) {
//    res *= 10;
//    res += c - '0';
//  }
//  return (int64_t)(res)*sign;
// }

// static inline void putint(uint64_t out) {
//  if (out > (1LLU << 63) - 1) {
//    putchar_unlocked('-');
//    out = 1 + ~out;
//  }
//  char data[44];
//  char *dend = data;
//  while (out) {
//    *++dend = (unsigned)('0') + out % 10;
//    out /= 10;
//  }
//  if (dend == data) {
//    putchar_unlocked('0');
//  }
//  for (; dend != data; --dend) {
//    putchar_unlocked(*dend);
//  }
// }

// static inline void print(uint64_t out) {
//  putint(out);
//  putchar('\n');
// }

// static inline void write(uint64_t out) {
//  putint(out);
//  putchar(' ');
// }

// #define min(arr,s) ((arr)<(s)?(arr):(s))
// #define max(arr,s) ((arr)>(s)?(arr):(s))

typedef int (*cmp_f_t)(const void *, const void *);

///////////////////////////////////////////////////end of lib

typedef struct att {
	char name[44];
	int score;
	int time;
} att;

long cmpl1(att *q, att *w) {
	long tmp = strcmp(q->name, w->name);
	if (tmp) {
		return tmp;
	}
	if (q->score != w->score) {
		return -q->score + w->score;
	}
	return q->time - w->time;
}

int cmp1(att *q, att *w) {
	long tmp = cmpl1(q, w);
	if (tmp < 0) {
		return -1;
	}
	if (tmp > 0) {
		return 1;
	}
	return 0;
}

long cmpl2(att *q, att *w) {
	if (q->score != w->score) {
		return -q->score + w->score;
	}
	return q->time - w->time;
}

int cmp2(att *q, att *w) {
	long tmp = cmpl2(q, w);
	if (tmp < 0) {
		return -1;
	}
	if (tmp > 0) {
		return 1;
	}
	return 0;
}

int main() {
	long m, n;
	scanf("%li%li", &m, &n);
	att *arr = (att *)calloc(sizeof(att), n);
	for (long w = 0; w < n; ++w) {
		scanf("%42s", arr[w].name);
		scanf("%i", &(arr[w].score));
		arr[w].time = w;
	}
	qsort(arr, n, sizeof(arr[0]), (cmp_f_t)cmp1);
	long uniq_len = 1;
	for (long w = 1; w < n; ++w) {
		if (strcmp(arr[w].name, arr[uniq_len - 1].name)) {
			arr[uniq_len++] = arr[w];
		}
	}
	// assert(uniq_len == m);
	qsort(arr, uniq_len, sizeof(arr[0]), (cmp_f_t)cmp2);
	for (long w = 0; w < uniq_len; ++w) {
		printf("%s\n", arr[w].name);
	}
	free(arr);
}
