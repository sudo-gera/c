#include <sys/syscall.h>
long syscall(long number,...);
char hw[]="Hello, World!";
int main(){
    syscall(SYS_write,1,hw,sizeof(hw)-1);
    syscall(SYS_exit,0);
}
#if !__has_include("d")
void _start(){
    main();
}
#endif
