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
// #define perr

///////////////////////////////////////////////////end of lib


extern size_t read_data_and_count(size_t N, int in[N]){

    int epoll_fd = epoll_create1(0);  // no flags
perr

    for (int w=0;w<N;++w){
        fcntl(in[w], F_SETFL, O_NONBLOCK);
perr
    }

    for (int i = 0; i < N; ++i) {
        struct epoll_event event = {
            .events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP | EPOLLET | EPOLLOUT | EPOLLRDHUP,
            .data.fd = in[i]
        };

        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, in[i], &event);
perr
    }


    int c=0;

    int pc=N;

    while (pc) {
        struct epoll_event events[1024];
        int n=epoll_wait(epoll_fd, events, sizeof(events)/sizeof(events[0]), -1);
perr

        for (int q=0;q<n;++q){
            struct epoll_event event=events[q];
            if (event.events & EPOLLIN){
                    char data[1024];
                    int l=0;
                    while((l=read(event.data.fd,data,sizeof(data)))>0){
perr
                        c+=l;
                    }
perr
            }
            if (event.events & (EPOLLRDHUP | EPOLLHUP)) {
perr
                _1:
				epoll_ctl(epoll_fd, EPOLL_CTL_DEL, event.data.fd, NULL);
perr
				close(event.data.fd);
perr
                pc-=1;
			}
        }
    }

    close(epoll_fd);
<<<<<<< HEAD

    return (c);

}

#if __has_include("d")
int main(){
    int fds[]={
        0,
    };
    print(read_data_and_count(sizeof(fds)/sizeof(fds[0]),fds));
}
#endif








=======
    
    dprintf(2, "Exiting...\n");
    
    return 0;
}
>>>>>>> 6c41edb8cb72140f06046a7db5ec66178a965571
