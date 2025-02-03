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
// #if __has_include(<sys/epoll.h>)
    #include <sys/epoll.h>
// #endif
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <tgmath.h>
#include <unistd.h>

int unused=0;

int check(const char*place){
    fprintf(stderr,"--> %s\n",place);
    if (errno){
        perror(place);//
        errno=0;//
    }
    return 0;//
}

#define _str(x) #x
#define m_str(x) _str(x)

#define _ check(__FILE__ ":" m_str(__LINE__))

#ifdef print
#undef print
#endif

#ifdef write
#undef write
#endif

struct array_s {
    uint64_t mem_size;//
    uint64_t el_count;//
    char data[0];//
};//

static inline uint64_t len(void *a) {
    if (a == NULL) {_;
        return 0;_;
    }
    return ((struct array_s *)(a))[-1].el_count;_;
}

static inline void del(void *a) {
    if (a != NULL) {_;
        free(((struct array_s *)(a)) - 1);_;
    }
}

static inline struct array_s *resize_f(struct array_s **vp, uint64_t el_size, uint64_t n) {
    if (*vp == NULL) {_;
        *vp = (struct array_s *)calloc(1, sizeof(struct array_s));_;
        assert(*vp);_;
        *vp += 1;_;
    }
    struct array_s *a = *vp - 1;_;
    assert(a->data == *(char **)vp);_;
    if (a->mem_size < n + 1) {_;
        uint64_t cur_size = a->mem_size * el_size;_;
        uint64_t new_size;_;
        if (a->mem_size * 2 > n) {_;
            new_size = a->mem_size * 2 * el_size;_;
        } else {
            new_size = (n + 1) * el_size;_;
        }
        a = (struct array_s *)realloc(a, sizeof(struct array_s) + new_size);_;
        assert(a);_;
        memset(a->data + a->mem_size * el_size, 0, new_size - cur_size);_;
        a->mem_size = new_size / el_size;_;
    }
    a->el_count = n;_;
    *vp = a + 1;_;
    return a + 1;_;
}
/////// resize(a, n) is resize_f(&a, sizeof(a[0]), n)
#ifdef __cplusplus
    template<typename T>
    auto resize(const T& a,uint64_t n){
        return (resize_f((struct array_s **)&(a), sizeof((a)[0]), (n)));_;
    }
    template<typename T,typename Y>
    auto append(const T& a,const Y& s){
        return (resize((a), len(a) + 1), (a)[len(a) - 1] = (s));_;
    }
    template<typename T>
    auto pop(const T& a){
        return (resize((a), len(a) - 1), (a)[len(a)]);_;
    }
    template<typename T>
    auto&back(const T& a){
        return ((a)[len(a)-1]);_;
    }
#else
    #define resize(a, ...) (resize_f((struct array_s **)&(a), sizeof((a)[0]), (__VA_ARGS__)))
    #define append(a, ...) (resize((a), len(a) + 1), (a)[len(a) - 1] = (__VA_ARGS__))
    #define pop(a) (resize((a), len(a) - 1), (a)[len(a)])
    #define back(a) ((a)[len(a)-1])
#endif

#define min(a,s) ((a)<(s)?(a):(s))
#define max(a,s) ((a)>(s)?(a):(s))

typedef int (*cmp_f_t)(const void *, const void *);//

char* get_line(){
    char*str=0;_;
    int c=0;_;
    while ((c=getchar(),c!=EOF)){_;
        append(str,c);_;
    }
    return str;
}

#define elif else if

// #define perr if (errno){perror(__FILE_" " m_str(__LINE__));errno=0;_;}
// #define perr


// #define for(int _perr=0;_perr<1;_;(++_perr,errno)?(perror(__FILE__ ":" m_str(__LINE__)),errno=0):0)

///////////////////////////////////////////////////end of lib

uint64_t hash(uint64_t s){
    return s;_;
}

typedef struct item{
    uint64_t key;//
    int value;//
}item;//

typedef struct dict{
    item**data;//
}dict;//

#define hashlen 59243

dict* dict_create(){
    dict*a=(dict*)calloc(1,sizeof(dict));_;
    resize(a->data,hashlen);_;
    return a;_;
}

bool eq(uint64_t q,uint64_t e){
    return q==e;_;
}

void dict_insert(dict*dp,item*tmp){
    if (dp){_;
        item**a=dp->data+hash(tmp->key)%len(dp->data);_;
        for (uint64_t w=0;w<len(*a);++w){_;
            if (eq(a[0][w].key,tmp->key)){_;
                a[0][w]=*tmp;_;
                return;_;
            }
        }
        append(a[0],*tmp);_;
    }
}

void dict_erase(dict*dp,item*tmp){
    if (dp){_;
        item**a=dp->data+hash(tmp->key)%len(dp->data);_;
        for (uint64_t w=0;w<len(*a);++w){_;
            if (eq(a[0][w].key,tmp->key)){_;
                memmove(a[0]+w,a[0]+w+1,(len(a[0])-w-1)*sizeof(item));_;
                pop(a[0]);_;
                return;_;
            }
        }
    }
}

bool dict_find(dict*dp,item*tmp){
    if (dp){_;
        item**a=dp->data+hash(tmp->key)%len(dp->data);_;
        for (uint64_t w=0;w<len(*a);++w){_;
            if (eq(a[0][w].key,tmp->key)){_;
                *tmp=a[0][w];_;
                return 1;_;
            }
        }
    }
    return 0;_;
}

void dict_del(dict*a){
    if (a){_;
        for (uint64_t w=0;w<len(a->data);w++){_;
            del(a->data[w]);_;
        }
        del(a->data);_;
        free(a);_;
    }
}

int exit_pipe[2]={-1,-1};//

void handler(int sig_num) {
    if (exit_pipe[1]!=-1){_;
        unused=write(exit_pipe[1],&sig_num,1);
        if (errno){
            exit(0);
        }
        close(exit_pipe[1]);
        exit_pipe[1]=-1;
    }
}

void add_to_epoll(int epoll_fd,int fd,int**fds,uint64_t payload,bool non_block){
    assert((payload<<32)==0);_;
    if (non_block){_;
        fcntl(fd, F_SETFL, O_NONBLOCK);_;
    }
    struct epoll_event event = {
        .events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP | EPOLLET | EPOLLOUT | EPOLLRDHUP,
        .data.u64 = payload+(uint32_t)(fd),
    };_;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);_;
    append(fds[0],fd);_;
}

void close_connection(int epoll_fd,uint64_t name,int fd,dict*d){
    item tmp;_;
    tmp.key=name;_;
    if (d){_;
        if (fd==-1){_;
            dict_find(d,&tmp);_;
            fd=tmp.value;_;
        }
        dict_erase(d,&tmp);_;
    }
    shutdown(fd,SHUT_RDWR);_;
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);_;
    close(fd);_;
}

void add_connection(int epoll_fd,uint64_t name,int fd,dict*d,int**fds){
    item tmp;_;
    tmp.key=name;_;
    tmp.value=fd;_;
    dict_insert(d,&tmp);_;
    add_to_epoll(epoll_fd,fd,fds,name,1);_;
}

int main(int argc,char**argv) {
    {
        struct sigaction sa = {
            .sa_handler = handler,
            .sa_flags = SA_RESTART,
        };_;
        sigaction(SIGINT, &sa, NULL);_;
        sigaction(SIGTERM, &sa, NULL);_;
    }

    int epoll_fd = epoll_create1(0);_;  // no flags
    int*fds=0;_;
    append(fds,epoll_fd);_;

    int socket_fd = -1;_;
    assert(argc>1);_;
    if (argc==2){_;
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);_;
        struct sockaddr_in addr = {
            .sin_family = AF_INET,
            .sin_port = htons(atoi(argv[1])),
            .sin_addr.s_addr = INADDR_ANY,
        };_;
        bind(socket_fd, (struct sockaddr*)(&addr), sizeof(addr));_;
        listen(socket_fd, SOMAXCONN);_;
        add_to_epoll(epoll_fd,socket_fd,&fds,0,0);_;
    }

    unused=pipe(exit_pipe);_;
    add_to_epoll(epoll_fd,exit_pipe[0],&fds,0,1);_;
    add_to_epoll(epoll_fd,0,&fds,0,1);_;

    dict* d=dict_create();_;

    char buffer[4096];_;
    uint64_t b_size=0;_;

    while (1){_;
        struct epoll_event events[1024];_;
        int n=epoll_wait(epoll_fd, events, sizeof(events)/sizeof(events[0]), -1);_;

        for (int q=0;q<n;++q){_;
            struct epoll_event event=events[q];_;
            if (event.data.fd==socket_fd){_;
                int client_fd = accept(socket_fd, NULL, NULL);_;
                uint64_t name=len(fds)<<32;_;
                add_connection(epoll_fd,name,client_fd,d,&fds);_;
                {char pd[1024];sprintf(pd,"%24" PRIu64 " %24i\n",name,'n');_;unused=write(1,pd,strlen(pd));}
            }elif(event.events & EPOLLIN){_;
                if (event.data.fd==exit_pipe[0]){_;
                    for (uint64_t q=0;q<len(d->data);++q){_;
                        for (uint64_t w=0;w<len(d->data[q]);++w){_;
                            close_connection(epoll_fd,d->data[q][w].key,d->data[q][w].value,0);_;
                        }
                    }
                    for (uint64_t w=0;w<len(fds);++w){_;
                        close(fds[w]);errno=0;
                    }
                    del(fds);_;
                    dict_del(d);_;
                    exit(0);_;
                }elif (event.data.fd==0){_;
                    char data[8192];_;
                    memmove(data,buffer,b_size);_;
                    uint64_t l=b_size;_;
                    while((l+=read(0,data+l,2048))-b_size-1<1LLU<<63){_;_;
                        while (1){_;
                            if (l>=50){_;
                                uint64_t name;_;
                                int c;_;
                                sscanf(data,"%" PRIu64 "%i",&name,&c);_;
                                assert((name<<32)==0);_;
                                if (c=='n'){_;
                                    l-=50;_;
                                    memmove(data,data+50,l);_;
                                    int client_fd = socket(AF_INET, SOCK_STREAM, 0);_;
                                    struct sockaddr_in addr = {
                                        .sin_family = AF_INET,
                                        .sin_port = htons(atoi(argv[2])),
                                        .sin_addr.s_addr = inet_addr(argv[1]),
                                    };_;
                                    connect(client_fd, (struct sockaddr*)(&addr), sizeof(addr));_;
                                    add_connection(epoll_fd,name,client_fd,d,&fds);_;
                                }
                                if (c=='d'){_;
                                    l-=50;_;
                                    memmove(data,data+50,l);_;
                                    close_connection(epoll_fd,name,-1,d);_;
                                }
                                if (c=='g'){_;
                                    if (l>=75){_;
                                        uint64_t _len=0;_;
                                        sscanf(data+50,"%" PRIu64 "u",&_len);_;
                                        if (l>=75+_len+1){_;
                                            l-=75;_;
                                            memmove(data,data+75,l);_;
                                            item tmp;_;
                                            tmp.key=name;_;
                                            dict_find(d,&tmp);_;
                                            char dec_data[4096];
                                            uint64_t dec_len=0;
                                            for (uint64_t q=0;q<_len;q+=2){
                                                data[q]-='a';
                                                data[q+1]-='a';
                                                dec_data[dec_len++]=((uint8_t)(data[q]))+(((uint8_t)(data[q+1]))<<4);
                                            }
                                            send(tmp.value,dec_data,dec_len,0);_;
                                            l-=_len+1;_;
                                            memmove(data,data+_len+1,l);_;
                                        }else{
                                            break;_;
                                        }
                                    }else{
                                        break;_;
                                    }
                                }
                            }else{
                                break;_;
                            }
                        }
                        memmove(buffer,data,l);_;
                        b_size=l;_;
                    }errno=0;
                }else{
                    char data[1024];_;
                    uint64_t l=0;_;
                    while((l=recv(event.data.fd,data,sizeof(data),0))-1<1LLU<<63){_;
                        uint64_t name=event.data.u64>>32<<32;_;
                        {char pd[1024];sprintf(pd,"%24" PRIu64 " %24i\n",name,'g');_;unused=write(1,pd,strlen(pd));}
                        {char pd[1024];sprintf(pd,"%24" PRIu64 " ",l*2);_;unused=write(1,pd,strlen(pd));}
                        char b16data[2048];
                        uint64_t b16l=0;
                        for (uint64_t q=0;q<l;++q){
                            b16data[b16l++]=(((uint8_t)(data[q]))&0xF)+'a';
                            b16data[b16l++]=(((uint8_t)(data[q]))>>4)+'a';
                        }
                        unused=write(1,b16data,b16l);
                        unused=write(1,"\n",1);
                        // send(event.data.fd,data,l,0);_;
                    }errno=0;
                }
            }
            if (event.events & (EPOLLRDHUP | EPOLLHUP)) {_;
                uint64_t name=event.data.u64>>32<<32;_;
                close_connection(epoll_fd,name,event.data.fd,d);_;
                {char pd[1024];sprintf(pd,"%24" PRIu64 " %24i\n",name,'d');_;unused=write(1,pd,strlen(pd));}
            }
        }
    }
    return unused*0;
}


