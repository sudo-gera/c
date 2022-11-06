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


int main(int argc,char**argv){
    size_t n=atoll(argv[2]);
    size_t w=atoll(argv[3]);
    int fd=open(argv[1],O_CREAT|O_TRUNC|O_RDWR,0777);
    size_t fs=w*n*n+n;
    ftruncate(fd,fs);
    char*mmem=(char*)mmap(NULL,fs,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    for (size_t q=0;q<n;++q){
        for (size_t e=0;e<n;++e){
            if (e>=q and e<n-q){
                sprintf(mmem+e*w+q*(n*w+1),"%*zu\n",w,n*n+1-(n-2*q)*(n-2*q)-q+e);
            }else
            if (e>=q){
                sprintf(mmem+e*w+q*(n*w+1),"%*zu\n",w,n*n-(2*e-n+1)*(2*e-n+1)-e+q);
            }else
            if (e<q and q<n-e){
                sprintf(mmem+e*w+q*(n*w+1),"%*zu\n",w,n*n+1-(n-2*e-2)*(n-2*e-2)-q+e);
            }else
            if (e<q){
                sprintf(mmem+e*w+q*(n*w+1),"%*zu\n",w,n*n-(2*q-n+1)*(2*q-n+1)-e+q);
            }
        }
    }
    munmap(mmem,fs);
    close(fd);
}
