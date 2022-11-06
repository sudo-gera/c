#include <sys/syscall.h>
long syscall(long number, ...);

char space[100];



void _start(){
    long len=0;
    len=syscall(SYS_read,0,space,100);
    while(len){
        syscall(SYS_write,1,space,len);
        len=syscall(SYS_read,0,space,100);
    }
    syscall(SYS_exit,0);
}