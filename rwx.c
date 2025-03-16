#include <stdio.h>
#include <stdlib.h>

const char* data[] = {
    "---",
    "--x",
    "-w-",
    "-wx",
    "r--",
    "r-x",
    "rw-",
    "rwx",
};

int main(){
    printf("%s", data[(getchar() - '0') % 8]);
    printf("%s", data[(getchar() - '0') % 8]);
    printf("%s", data[(getchar() - '0') % 8]);
    printf("\n");
}
