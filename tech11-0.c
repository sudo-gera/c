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
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define perr if (errno){perror(__FILE__ " " m_str(__LINE__));errno=0;}

///////////////////////////////////////////////////end of lib

int exit_pipe[2];


void handler(int sig) {
    char msg[] = "123";
    write(exit_pipe[1], msg, sizeof(msg));
}


int main() {
    pipe(exit_pipe);

    dprintf(2, "signal\n");
    struct sigaction sa = {
        .sa_handler = handler,
        .sa_flags = SA_RESTART
    };
    
    sigaction(SIGINT, &sa, NULL);
    
    int epoll_fd = epoll_create1(0);  // no flags
    
    fcntl(exit_pipe[0], F_SETFL, O_NONBLOCK);
    fcntl(0, F_SETFL, O_NONBLOCK);
    
    int fifo_fd = open("test_fifo", O_RDONLY);
    fcntl(fifo_fd, F_SETFL, O_NONBLOCK);
    
    dprintf(2, "epoll_ctl...\n");
    int all_fds[] = {exit_pipe[0], 0, fifo_fd};
    for (int i = 0; i < 3; ++i) {
        struct epoll_event event = {
            .events = EPOLLIN,
            .data.fd = all_fds[i]
        };
        
        // Будем ожидать готовности на чтение
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, all_fds[i], &event);
    }
    
    dprintf(2, "Main loop\n");
    while (1) {
        struct epoll_event event;
        int N = epoll_wait(epoll_fd, &event, /*maxevents=*/ 1, /*timeout=*/ 1000);
        
        if (N <= 0) {
            sched_yield();
            continue;
        }
        
        int fd = event.data.fd;
        
        if (fd == exit_pipe[0]) {
            break;
        }
        
        char buffer[1024];
        size_t len = read(fd, buffer, sizeof(buffer));
        write(1, buffer, len);
    }
    
    dprintf(2, "Closing all\n");
    
    for (int i = 0; i < 3; ++i) {
        close(all_fds[i]);
    }
    
    close(epoll_fd);
    
    dprintf(2, "Exiting...\n");
    
    return 0;
}
