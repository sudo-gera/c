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
/*
 * array
 *
 * meta[1] - len of array
 * meta[0] - len of mem
 *
 * always meta[0]>meta[1], so a[len(a)] is accessible
 *
 * array(type,name,len=0) creates array[len] of type
 *
 * interface: len(a), append(a,n), pop(a), resize(a,l), a[i]
 *
 */
#define OFFSET 2
#define arr_meta(q) (((uint64_t *)*(q)) - OFFSET)
#define arr_data(t, q) ((t *)(*q))
uint64_t len(void *a) {
  if (!a) {
    return 0;
  }
  return arr_meta(&a)[1];
}
void *resize_f(void **a, uint64_t s, uint64_t y) {
  void *p = 0;
  if (!a) { // resize_f(0,12);
    a = &p;
  }
  if (!*a) { // int*a=0; resize(a,12);
    *a = OFFSET + (uint64_t *)malloc(s * (y + 1) + OFFSET * sizeof(uint64_t));
    arr_meta(a)[0] = y + 1;
  } else if (arr_meta(a)[0] < y + 1 and y + 1 < 2 * arr_meta(a)[0]) {
    *a = OFFSET +
    (uint64_t *)realloc(arr_meta(a), s * arr_meta(a)[0] * 2 +
                                              OFFSET * sizeof(uint64_t));
    arr_meta(a)[0] *= 2;
  } else if (arr_meta(a)[0] < y + 1) {
    *a = OFFSET + (uint64_t *)realloc(arr_meta(a),
                                      s * (y + 1) + OFFSET * sizeof(uint64_t));
    arr_meta(a)[0] = y + 1;
  } else if (arr_meta(a)[0] > (y + 1) * 4) {
    *a = OFFSET + (uint64_t *)realloc(arr_meta(a),
                                      s * (y + 1) + OFFSET * sizeof(uint64_t));
    arr_meta(a)[0] = y + 1;
  }
  arr_meta(a)[1] = y;
  return *a;
}
#define resize(a, ...) resize_f((void **)(&(a)), sizeof(*(a)), __VA_ARGS__)
void del(void *a) {
  if (!a) {
    return;
  }
  free(arr_meta(&a));
}
#define append(a, ...) ((a)[len(a)] = (__VA_ARGS__), resize((a), len(a) + 1))
#define pop(a, ...) (resize((a), len(a) - 1), (a)[len(a)])
#define array(type, name, ...)                                                 \
  type *name = (type *)resize_f(0, sizeof(type), __VA_ARGS__ - 0);

#define uns unsigned
// typedef unsigned uns;
typedef char *str;

#define make_to_string(type, name, str_, acc, size)                            \
  str to_string_##name(const type q) {                                         \
    array(char, res, size);                                                    \
    sprintf(res, str_, acc);                                                   \
    resize(res, strlen(res));                                                  \
    return res;                                                                \
  }

make_to_string(long long int, int, "%lli", q, 128);
make_to_string(long long unsigned, uns, "%llu", q, 128);
make_to_string(long double, float, "%Lf", q, 128);
make_to_string(str, str, "%s", q ? q : "", q ? 128 + strlen(q) : 128);
make_to_string(char, char, "%c", q, 128);
#undef make_to_string
#define func_name_generator(func)                                              \
  const long long int : func##_int,                                            \
                        const long int : func##_int,                           \
                                         const int : func##_int,               \
                                                     const long long uns       \
      : func##_uns,                                                            \
        const long uns : func##_uns,                                           \
                         const uns : func##_uns,                               \
                                     const long double : func##_float,         \
                                                         const double          \
      : func##_float,                                                          \
        const float : func##_float,                                            \
                      const char : func##_int,                                 \
                                   const char *const                           \
      : func##_str,                                                            \
        const char * : func##_str,                                             \
                       long long int : func##_int,                             \
                                       long int : func##_int,                  \
                                                  int : func##_int,            \
                                                        long long uns          \
      : func##_int,                                                            \
        long uns : func##_int,                                                 \
                   uns : func##_int,                                           \
                         long double : func##_float,                           \
                                       double : func##_float,                  \
                                                float : func##_float,          \
                                                        char : func##_int,     \
                                                               char *const     \
      : func##_str,                                                            \
        char * : func##_str

#define to_str(q) _Generic((q), func_name_generator(to_string))(q)

#define mkinput(type, name, str, acc)                                          \
  type input_##name() {                                                        \
    type q = 0;                                                                \
    scanf(str, acc);                                                           \
    return q;                                                                  \
  }
mkinput(long long int, int, "%lli", &q);
mkinput(long long uns, uns, "%llu", &q);
mkinput(long double, float, "%Lf", &q);
mkinput(char, char, "%c", &q);
#undef mkinput
str input_str() {
<<<<<<< HEAD
  static char t[1073741824];
=======
  static char t[1024];
>>>>>>> edd1a72a29bdf481718ea43e7194f3dbec21102a
  scanf("%s", t);
  return to_str(t);
}

#define read(type, name)                                                       \
  type name = _Generic(name, func_name_generator(input))();
#define write(q)                                                               \
  {                                                                            \
    str __t = to_str(q);                                                       \
    printf("%s ", __t);                                                        \
    del(__t);                                                                  \
  }
#define print(q)                                                               \
  {                                                                            \
    str __t = to_str(q);                                                       \
    printf("%s\n", __t);                                                       \
    del(__t);                                                                  \
  }
#define put(q)                                                                 \
  {                                                                            \
    str __t = to_str(q);                                                       \
    printf("%s", __t);                                                         \
    del(__t);                                                                  \
  }

#define bit_get(a, s)                                                          \
  (((a)[(s) / 8 / sizeof((a)[0])] >> (s) % (8 * sizeof((a)[0]))) & 1)
#define bit_set(a, s, d)                                                       \
  {                                                                            \
    (a)[(s) / 8 / sizeof((a)[0])] &= ~(1 << (s) % (8 * sizeof((a)[0])));       \
    (a)[(s) / 8 / sizeof((a)[0])] += (d) << (s) % (8 * sizeof((a)[0]));        \
  }

int main() {
  read(size_t, v);
  read(size_t, n);
  array(size_t, a, v);
  array(size_t, s, v);
  for (size_t w = 0; w < v; ++w) {
    a[w] = input_int();
    s[w] = a[w];
  }
  size_t r = 0;
  // size_t p=0;
  while (1) {
    size_t min = -1;
    for (size_t w = 0; w < v; ++w) {
      min = a[w] < min ? a[w] : min;
    }
    if (min >= n) {
      break;
    }
    r++;
    // p=min;
    for (size_t w = 0; w < v; ++w) {
      if (a[w] == min) {
        a[w] += s[w];
        s[w]++;
      }
    }
  }
  print(r)
  del(a);
  del(s);
}
