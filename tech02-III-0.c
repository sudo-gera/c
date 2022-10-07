long syscall(long number,...);
#define hw "Hello, World!"
int main(){
    syscall(1,1,hw,sizeof(hw)-1);
    syscall(60,0);
}
#if !__has_include("d")
void _start(){
    main();
}

#endif