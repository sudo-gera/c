#include <iso646.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv) {
    if (argc == 2 and strlen(argv[1]) == 1 and argv[1][0] == '\xff') {
        printf("++++\n");
    } else {
        printf("----\n");
    }
}
