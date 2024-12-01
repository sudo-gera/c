#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

int main(int argc, char **argv, char*const* env) {
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
        uid_t id = geteuid();
        if (errno){perror("geteuid failed");} else{
            printf("having geteuid() = %lli (note: cp command erases setuid)\n", (long long int)(id));
        }
        return 0;
    }
    args[0] = TOSTRING(COMMAND);
    #ifndef COMMAND
        args += 1;
        #warning "use -DCOMMAND to specify path to executable binary. Now compiling to behave like sudo."
    #endif
    uid_t id = geteuid();
    if (errno){perror("geteuid failed");goto help;}
    setuid(id);
    if (errno){perror("setuid failed");goto help;}
    setgid(id);
    if (errno){perror("setuid failed");goto help;}
    execve(args[0], (char**)args, env);
    if (errno){perror("execve failed (note: it requres full path)");goto help;}
}
