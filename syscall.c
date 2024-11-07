#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#define TEXT_AS_STR(x) #x
#define VALUE_AS_STR(x) TEXT_AS_STR(x)
#define SYSCALL for (errno = 0;;({if (errno) {perror("SYSCALL ERROR: " __FILE__ ":" VALUE_AS_STR(__LINE__));}break;}))

// int main(){
//     SYSCALL write(4, "hello\n", 6);
// }
