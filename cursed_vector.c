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
// #define resize_m(a, ...) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (__VA_ARGS__)))
// #define append(a, ...) (resize((a), len(a) + 1), (a)[len(a) - 1] = (__VA_ARGS__))
// #define pop(a) (resize((a), len(a) - 1), (a)[len(a)])
// #define back(a) ((a)[len(a)-1])

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

// char* get_line(){
//     char*str=0;
//     int c=0;
//     while ((c=getchar(),c!=EOF)){
//         append(str,c);
//     }
//     return str;
// }

#define elif else if

#define _str(x) #x
#define m_str(x) _str(x)
#define perr if (errno){perror(__FILE__ " " m_str(__LINE__));errno=0;}

#define rp_0(n) to_repeat(n)
#define rp_1(n) rp_0(n##0)  rp_0(n##1)
#define rp_2(n) rp_1(n##0)  rp_1(n##1)
#define rp_3(n) rp_2(n##0)  rp_2(n##1)
#define rp_4(n) rp_3(n##0)  rp_3(n##1)
#define rp_5(n) rp_4(n##0)  rp_4(n##1)
#define rp_6(n) rp_5(n##0)  rp_5(n##1)
#define rp_7(n) rp_6(n##0)  rp_6(n##1)
#define rp_8(n) rp_7(n##0)  rp_7(n##1)
#define rp_9(n) rp_8(n##0)  rp_8(n##1)
#define rp_10(n) rp_9(n##0)  rp_9(n##1)
#define repeat(n) rp_##n(0b0)

struct cursed_array_s{
    void* data_;
    size_t el_size_;
    size_t (*size)();
    void* (*data)();
    void (*resize)(size_t);
};

struct cursed_array_s* cursed_arrays[1024];

#define to_repeat(n) size_t cursed_array_size_##n(){return len(cursed_arrays[n]->data_);}
repeat(10)
#undef to_repeat
#define to_repeat(n) void* cursed_array_data_##n(){return (cursed_arrays[n]->data_);}
repeat(10)
#undef to_repeat
#define to_repeat(n) void cursed_array_resize_##n(size_t l){resize_f((struct array_s**)&(cursed_arrays[n]->data_),cursed_arrays[n]->el_size_,l);}
repeat(10)
#undef to_repeat
size_t (*cursed_arrays_size[1024])()={
#define to_repeat(n) cursed_array_size_##n,
repeat(10)
#undef to_repeat
};
void* (*cursed_arrays_data[1024])()={
#define to_repeat(n) cursed_array_data_##n,
repeat(10)
#undef to_repeat
};
void (*cursed_arrays_resize[1024])(size_t)={
#define to_repeat(n) cursed_array_resize_##n,
repeat(10)
#undef to_repeat
};

size_t cursed_array_count=0;

void cursed_array_create(struct cursed_array_s*place,size_t el_size){
    assert(cursed_array_count!=1024);
    cursed_arrays[cursed_array_count]=place;
    place->size=cursed_arrays_size[cursed_array_count];
    place->data=cursed_arrays_data[cursed_array_count];
    place->resize=cursed_arrays_resize[cursed_array_count];
    place->data_=NULL;
    place->el_size_=el_size;
    cursed_array_count+=1;
}

void cursed_array_destroy(struct cursed_array_s*place){
    del(place->data_);
}

int main(){
    struct cursed_array_s vv;
    cursed_array_create(&vv,sizeof(struct cursed_array_s));
    size_t n=getint();
    vv.resize(n);
    struct cursed_array_s* v=(struct cursed_array_s*)vv.data();
    for (size_t q=0;q<vv.size();++q){
        cursed_array_create(v+q,sizeof(size_t));
        v[q].resize(n);
        for (size_t e=0;e<v[q].size();++e){
            ((size_t*)(v[q].data()))[e]=getint();
        }
    }
    for (size_t q=0;q<vv.size();++q){
        for (size_t e=0;e<v[q].size();++e){
            putint(((size_t*)(v[q].data()))[e]);
            putchar(32);
        }
        putchar(10);
        cursed_array_destroy(v+q);
    }
    cursed_array_destroy(&vv);
}


