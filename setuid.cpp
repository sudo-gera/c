#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
<<<<<<< HEAD
#include <sys/types.h>
=======
>>>>>>> 608c69325bff3bcd0c8993a9d8ab7cbec3b23e30

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

int main(int argc, char **argv, char*const* env) {
<<<<<<< HEAD
    const char* args_a[argc+1];
    const char** args = args_a;
    memmove(args, argv, sizeof(argv[0]) * (argc+1));
    if (!args[0][0]){
        help:
        #ifdef COMMAND
            puts("was compiled with COMMAND=" TOSTRING(COMMAND));
        #else
            puts("was compiled without COMMAND");
        #endif
        return 0;
    }
    args[0] = TOSTRING(COMMAND);
    #ifndef COMMAND
        args += 1;
        #warning "use -DCOMMAND to specify path to executable binary. Now compiling to behave like sudo."
    #endif
    uid_t id = geteuid();
    setuid(id);
    setgid(id);
    execve(args[0], (char**)args, env);
    if (errno){
        perror("execve failed (it requres full path)");
        goto help;
    }
=======
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
>>>>>>> 608c69325bff3bcd0c8993a9d8ab7cbec3b23e30
}
