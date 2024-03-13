#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

int main(int argc, char **argv, char*const* env) {
    const char* args[argc+1];
    #ifdef COMMAND
        memmove(args, argv, sizeof(char*)*argc);
        args[argc]=0;
        args[0]=TOSTRING(COMMAND);
    #else
        memmove(args, argv+1, sizeof(char*)*(argc-1));
        args[argc]=0;
        args[argc-1]=0;
        #warning "use -DCOMMAND to specify path to executable binary. Now compiling to behave like sudo."
    #endif
    if (geteuid() == 0) {
        setuid(0);
        setgid(0);
        execve(args[0], (char**)args, env);
    } else {
        puts("You do not have privs");
    }
    return 0;
}
