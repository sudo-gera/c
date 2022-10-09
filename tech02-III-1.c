long syscall(long number, ...);

char space[100];

int main(){
    long len=1;
    while (len){
        len=syscall(0,0,space,100);
        syscall(1,1,space,len);
    }
}

#if !__has_include("d")
void _start(){
    main();
}
#endif
