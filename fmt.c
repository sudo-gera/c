#ifndef assert
#include <assert.h>
#endif
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <iso646.h>
#include <memory.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if __has_include(<sys/epoll.h>)
    #include <sys/epoll.h>
#endif
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <tgmath.h>
#include <unistd.h>

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
        assert(*vp);
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
        assert(a);
        memset(a->data + a->mem_size * el_size, 0, new_size - cur_size);
        a->mem_size = new_size / el_size;
    }
    a->el_count = n;
    *vp = a + 1;
    return a + 1;
}
/////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
#ifdef __cplusplus
    template<typename T>
    auto resize(const T& a,uint64_t n){
        return (resize_f((struct array_s **)&(a), sizeof((a)[0]), (n)));
    }
    template<typename T,typename Y>
    auto append(const T& a,const Y& s){
        return (resize((a), len(a) + 1), (a)[len(a) - 1] = (s));
    }
    template<typename T>
    auto pop(const T& a){
        return (resize((a), len(a) - 1), (a)[len(a)]);
    }
    template<typename T>
    auto&back(const T& a){
        return ((a)[len(a)-1]);
    }
#else
    #define resize(a, ...) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (__VA_ARGS__)))
    #define append(a, ...) (resize((a), len(a) + 1), (a)[len(a) - 1] = (__VA_ARGS__))
    #define pop(a) (resize((a), len(a) - 1), (a)[len(a)])
    #define back(a) ((a)[len(a)-1])
#endif

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

#define min(a,s) ((a)<(s)?(a):(s))
#define max(a,s) ((a)>(s)?(a):(s))

typedef int (*cmp_f_t)(const void *, const void *);

char* get_line(){
    char*str=0;
    int c=0;
    while ((c=getchar(),c!=EOF)){
        append(str,c);
    }
    return str;
}

#define elif else if

#define _str(x) #x
#define m_str(x) _str(x)
#define perr if (errno){perror(__FILE__ " " m_str(__LINE__));errno=0;}

///////////////////////////////////////////////////end of lib

// #define fmt(...) __VA_OPT__()

// #define fmt_(...) (({ \
//  struct { char fmt__data[65536]; } fmt__data;\
//  memset(fmt__data.fmt__data, 0, sizeof(fmt__data.fmt__data)); \
//  snprintf(fmt__data.fmt__data + strlen(fmt__data.fmt__data), sizeof(fmt__data.fmt__data) - strlen(fmt__data.fmt__data), __VA_ARGS__); \
//  snprintf(fmt__data.fmt__data + strlen(fmt__data.fmt__data), sizeof(fmt__data.fmt__data) - strlen(fmt__data.fmt__data), __VA_ARGS__); \
//  snprintf(fmt__data.fmt__data + strlen(fmt__data.fmt__data), sizeof(fmt__data.fmt__data) - strlen(fmt__data.fmt__data), __VA_ARGS__); \
//  fmt__data; \
// }).fmt__data)

// int main(){
//  write(1, fmt("%d", 20));
// }

// #define macro_map(...)                      __VA_OPT__(              macro_map_00(__VA_ARGS__))
// #define macro_map_00(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_01(__VA_ARGS__))
// #define macro_map_01(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_02(__VA_ARGS__))
// #define macro_map_02(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_03(__VA_ARGS__))
// #define macro_map_03(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_04(__VA_ARGS__))
// #define macro_map_04(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_05(__VA_ARGS__))
// #define macro_map_05(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_06(__VA_ARGS__))
// #define macro_map_06(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_07(__VA_ARGS__))
// #define macro_map_07(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_08(__VA_ARGS__))
// #define macro_map_08(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_09(__VA_ARGS__))
// #define macro_map_09(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_10(__VA_ARGS__))
// #define macro_map_10(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_11(__VA_ARGS__))
// #define macro_map_11(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_12(__VA_ARGS__))
// #define macro_map_12(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_13(__VA_ARGS__))
// #define macro_map_13(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_14(__VA_ARGS__))
// #define macro_map_14(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_15(__VA_ARGS__))
// #define macro_map_15(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_16(__VA_ARGS__))
// #define macro_map_16(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_17(__VA_ARGS__))
// #define macro_map_17(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_18(__VA_ARGS__))
// #define macro_map_18(x, ...) macro_map_f(x) __VA_OPT__(macro_map_sep macro_map_19(__VA_ARGS__))
// ___
// #define macro_map_f(...) [__VA_ARGS__]
// #define macro_map_sep -
// macro_map(0,1,2)
// #undef macro_map_f
// #undef macro_map_sep
// #define macro_map_f(...) {__VA_ARGS__}
// #define macro_map_sep =
// macro_map(0,1,2)
// ___

#define fmt_code_to_ds(...)                 
    (({                                             \
        char fmtd[65537];
        memset(fmtd, 0, sizeof(fmtd));
        __VA_ARGS__;
        struct {
            char d[sizeof(fmtd)];
        } {fmtd};
    }))