long syscall(long number, ...);

char space[100];



void _start(){
    long len=0;
    len=syscall(0,0,space,100);
    while(len){
        syscall(1,1,space,len);
        len=syscall(0,0,space,100);
    }
    syscall(60,0);
}