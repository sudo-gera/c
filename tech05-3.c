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
#include <errno.h>


extern void* my_malloc(size_t size);

extern void my_free(void *ptr);

char*mmem=0;
int fd;

extern void myalloc_initialize(int _fd){
    fd=_fd;
    ftruncate(fd,1024);
    mmem=(char*)mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
    memset(mmem,'+',1024);
}

extern void myalloc_finalize(){
    
}


#if __has_include("d")
int main(int argc,char**argv){
    int fd=open(argv[1],O_RDWR);
    myalloc_initialize(fd);
    myalloc_finalize();
    close(fd);
}
#endif

