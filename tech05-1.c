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

struct Item {
  int value;
  uint32_t next_pointer;
};

int main(int argc,char**argv){
    int fd=open(argv[1],O_RDONLY);
    size_t fs=get_size(argv[1]);
    if (fs>=sizeof(struct Item)){
        struct Item data;
        char*mmem=(char*)mmap(NULL,fs,PROT_READ,MAP_PRIVATE,fd,0);
        size_t p=0;
        memmove(&data,mmem+p,sizeof(data));
        printf("%i\n",data.value);
        p=data.next_pointer;
        while (p){
            memmove(&data,mmem+p,sizeof(data));
            printf("%i\n",data.value);
            p=data.next_pointer;
        }
        munmap(mmem,fs);
    }
    close(fd);
}
