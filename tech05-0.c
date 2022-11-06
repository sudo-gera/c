#ifndef assert
#include <assert.h>
#endif
#include <ctype.h>
#include <inttypes.h>
#include <iso646.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <tgmath.h>
#include <stddef.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/syscall.h>

size_t get_size(const char*fn){
    struct stat f_stat;
	lstat(fn, &f_stat);
    return f_stat.st_size;
}

char* _memmem(char* q,size_t qs,char* w,size_t ws){
    if (qs*ws==0){
        return NULL;
    }
    if (ws>qs){
        return NULL;
    }
    for (size_t e=0;e<=qs-ws;++e){
        if (memcmp(q+e,w,ws)==0){
            return q+e;
        }
    }
    return NULL;
}

int main(int argc,char**argv){
    int fd=open(argv[1],O_RDONLY);
    size_t fs=get_size(argv[1]);
    char*mmem=(char*)mmap(NULL,fs,PROT_READ,MAP_PRIVATE,fd,0);
    close(fd);
    size_t ss=strlen(argv[2]);
    char*s=mmem;
    s=_memmem(s,fs,argv[2],ss);
    while (s){
        printf("%zu\n",(size_t)(s-mmem));
        ++s;
        s=_memmem(s,fs,argv[2],ss);
    }
    // printf("%s\n",memmem(mmem,fs,argv[2],ss));
    munmap(mmem,fs);
    return 0;
}
